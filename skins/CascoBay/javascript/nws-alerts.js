async function getNWSAlerts(lat, lon) {
    const endpoint = `https://api.weather.gov/alerts/active?point=${lat},${lon}`;
    const container = document.getElementById('nws-alerts-container');

    try {
        const response = await fetch(endpoint);
        if (!response.ok) {
            throw new Error(`Error fetching alerts: ${response.status}`);
        }

        const data = await response.json();
        if (data.features.length === 0) {
            console.log('No active alerts.');
            return;
        }

        // Clear old alerts
        document.getElementById('nws-alerts-container').innerHTML = '';

        // Create banners for current alerts
        data.features.forEach(alert => {
            const alertId = alert.id;

            // Skip alert if it has been dismissed
            if (localStorage.getItem(`dismissed-${alertId}`)) {
                return;
            }

            const banner = document.createElement('div');
            banner.classList.add('relative');

            banner.innerHTML = `
                <div class="p-4 mb-4 bg-teal-100 border-t-4 border-teal-500 rounded-b text-teal-900 px-4 py-3 shadow-md" role="alert">
                    <button class="absolute top-0 right-0 mt-2 mr-4 text-teal-700 hover:text-teal-900 font-bold text-xl">&times;</button>
                    <div class="flex">
                        <div class="flex items-center mr-2">
                            <svg xmlns="http://www.w3.org/2000/svg" fill="none" stroke-width="2.0" class="stroke-current h-6 w-6 text-teal-500" viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" d="M12 9v3.75m-9.303 3.376c-.866 1.5.217 3.374 1.948 3.374h14.71c1.73 0 2.813-1.874 1.948-3.374L13.949 3.378c-.866-1.5-3.032-1.5-3.898 0L2.697 16.126ZM12 15.75h.007v.008H12v-.008Z" />
                            </svg>
                        </div>
                        <div>
                            <p class="font-bold">${alert.properties.event}</p>
                            <p class="text-sm">${alert.properties.headline || alert.properties.description}</p>
                        </div>
                    </div>
                </div>
            `;

            // Add dismiss functionality
            banner.querySelector('button').addEventListener('click', () => {
                localStorage.setItem(`dismissed-${alertId}`, 'true');
                banner.remove();
            });

            container.appendChild(banner);
        });

    } catch (error) {
        console.error('Fetch error:', error.message);
    }
}

function toggleAlerts() {
    const showAlerts = localStorage.getItem('showAlerts') === 'true';
    if (showAlerts) {
        document.getElementById('nws-alerts-container').innerHTML = '';
        document.getElementById('alerts-toggle').textContent = 'Show Alerts';
        localStorage.setItem('showAlerts', 'false');
    } else {
        document.getElementById('alerts-toggle').textContent = 'Hide Alerts';
        localStorage.setItem('showAlerts', 'true');

        // Clear storage
        Object.keys(localStorage).forEach(key => {
            if (key.startsWith('dismissed-')) {
                localStorage.removeItem(key);
            }
        });

        // Fetch alerts again
        const {lat, lon} = getLatLon();
        getNWSAlerts(lat, lon);
    }
}

function parseDMS(dmsStr) {
    // Remove parentheses and quotes, then split
    const parts = dmsStr.replace(/[()']/g, '').split(',').map(p => p.trim());
    const degrees = parseFloat(parts[0]);
    const minutes = parseFloat(parts[1]);
    const hemisphere = parts[2];

    if (isNaN(degrees) || isNaN(minutes) || !hemisphere) {
        throw new Error(`Invalid DMS string: ${dmsStr}`);
    }

    let decimal = degrees + (minutes / 60.0);
    if (hemisphere === 'S' || hemisphere === 'W') {
        decimal = -decimal;
    }

    return decimal;
}

function getLatLon() {
    const container = document.getElementById('nws-alerts-container');
    if (!container || !container.dataset.lat || !container.dataset.lon) {
        throw new Error('Missing latitude or longitude data attributes on container.');
    }
    const lat = parseDMS(container.dataset.lat);
    const lon = parseDMS(container.dataset.lon);
    return {lat, lon};
}


document.addEventListener('DOMContentLoaded', () => {
    const showAlerts = localStorage.getItem('showAlerts') === 'true' || true;
    if (showAlerts) {
        localStorage.setItem('showAlerts', 'true');
        const {lat, lon} = getLatLon();
        getNWSAlerts(lat, lon);
    }
});