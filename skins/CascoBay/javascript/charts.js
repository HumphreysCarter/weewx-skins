function toggleSidebar() {
    const isCollapsed = localStorage.getItem('sidebarCollapsed') === 'true';
    if (isCollapsed) {
        document.documentElement.classList.remove('sidebar-collapsed');
        document.getElementById('sidebar-toggle').textContent = 'Hide Sidebar';
        localStorage.setItem('sidebarCollapsed', 'false');
    } else {
        document.documentElement.classList.add('sidebar-collapsed');
        document.getElementById('sidebar-toggle').textContent = 'Show Sidebar';
        localStorage.setItem('sidebarCollapsed', 'true');
    }
}

function getCardinalDirection(angle) {
    const directions = ['N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW'];
    const index = Math.round(angle / 45) % 8;
    return directions[index];
}

function setTimeRange(range = 'day') {
    // Update the almanac table
    updateAlmanac(range);

    // Load the graph data
    loadData(range);
}

function updateAlmanac(range) {
    // Get all elements with a class that includes "hilo_"
    const allHiloElements = document.querySelectorAll('[class*="hilo_"]');

    allHiloElements.forEach(el => {
        // Find the first class that starts with "hilo_"
        const hiloClass = Array.from(el.classList).find(c => c.startsWith('hilo_'));
        if (!hiloClass) return;

        const type = hiloClass.replace('hilo_', '');

        // Show/hide based on the current range
        if (range === 'day') {
            el.style.display = (type === 'day') ? 'table-cell' : 'none';
        } else {
            el.style.display = (type === 'day' || type === range) ? 'table-cell' : 'none';
        }
    });
}

async function loadData(range) {
    // Highlight the active button
    const buttons = document.querySelectorAll('.time-range-btn');
    buttons.forEach(btn => {
        if (btn.dataset.range === range) {
            btn.classList.add('border-b-2', 'border-teal-400');
        } else {
            btn.classList.remove('border-b-2', 'border-teal-400');
        }
    });

    // Save selection to local storage
    localStorage.setItem('historySetting', range);

    // Get JSON data for the desired time range
    const response = await fetch(`json/${range}.json`);
    const json = await response.json();

    // Map data for Highcharts (timestamp * 1000 to convert seconds to milliseconds)
    const barometer = json.data.barometer.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const barometerUnits = json.data.barometer.units;
    const outTemp = json.data.outTemp.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const outTempUnits = json.data.outTemp.units;
    const inTemp = json.data.inTemp.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const inTempUnits = json.data.inTemp.units;
    const dewPoint = json.data.dewpoint.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const dewPointUnits = json.data.dewpoint.units;
    const outHumidity = json.data.outHumidity.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const outHumidityUnits = json.data.outHumidity.units;
    const rain = json.data.rain.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const rainUnits = json.data.rain.units;
    const rainRate = json.data.rainRate.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const rainRateUnits = json.data.rainRate.units;
    const windSpeed = json.data.windSpeed.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const windSpeedUnits = json.data.windSpeed.units;
    const windGust = json.data.windGust.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const windGustUnits = json.data.windGust.units;
    const windDir = json.data.windDir.values.map(([timestamp, value]) => [timestamp * 1000, value]);
    const windDirUnits = json.data.windDir.units;

    Highcharts.chart('barometer', {
        title: {text: 'Barometer'},
        xAxis: {type: 'datetime'},
        yAxis: {title: {text: `Pressure (${barometerUnits})`}},
        tooltip: {valueDecimals: 2},
        series: [{
            name: `Pressure (${barometerUnits})`,
            data: barometer,
            color: '#4282b4'
        }],
    });

    Highcharts.chart('temp-dewpoint', {
        title: {text: 'Temperature and Dewpoint'},
        xAxis: {type: 'datetime'},
        tooltip: {
            valueDecimals: 1,
            shared: true
        },
        yAxis: {
            tickInterval: 10,
            title: {text: `Temperature (${outTempUnits})`}
        },
        series: [{
            name: `Air Temperature (${outTempUnits})`,
            data: outTemp,
            color: '#b44242'
        }, {
            name: `Dewpoint Temperature (${dewPointUnits})`,
            data: dewPoint,
            color: '#4282b4'
        }]
    });

    Highcharts.chart('outside-humidity', {
        title: {text: 'Relative Humidity'},
        xAxis: {type: 'datetime'},
        yAxis: {title: {text: `Relative Humidity (${outHumidityUnits})`}},
        tooltip: {valueDecimals: 0},
        series: [{
            name: `Relative Humidity (${outHumidityUnits})`,
            data: outHumidity,
            color: '#4282b4'
        }]
    });

    Highcharts.chart('wind-speed', {
        chart: {type: 'column'},
        title: {text: 'Wind Speed and Gust'},
        xAxis: {type: 'datetime', gridLineWidth: 1},
        yAxis: {
            min: 0,
            softMax: 20,
            tickInterval: 10,
            title: {
                text: `Wind Speed (${windSpeedUnits})`
            },
            gridLineWidth: 1
        },
        tooltip: {
            valueDecimals: 0,
            shared: true
        },
        plotOptions: {
            column: {
                grouping: false,
                pointPadding: 0.2,
                borderWidth: 0
            }
        },
        series: [
            {
                name: `Gust (${windGustUnits})`,
                type: 'column',
                color: '#b44242',
                data: windGust,
                pointPlacement: 0
            },
            {
                name: `Sustained (${windSpeedUnits})`,
                type: 'column',
                color: '#4282b4',
                data: windSpeed,
                pointPlacement: 0
            }
        ]
    });

    Highcharts.chart('wind-direction', {
        title: {text: 'Wind Direction'},
        xAxis: {type: 'datetime'},
        yAxis: {
            min: 0,
            max: 360,
            tickInterval: 90,
            title: {text: `Wind Direction (${windDirUnits})`}
        },
        tooltip: {
            formatter: function () {
                if (this.y !== null) {
                    const cardinal = getCardinalDirection(this.y);
                    return `<b><span style="font-size: 10px">${Highcharts.dateFormat('%A, %e %b, %H:%M', this.x)}</b></span><br/>` +
                        `<span style="color:${this.series.color}">\u25CF</span> ` +
                        `Wind Direction: <b>${Math.round(this.y)}° (${cardinal})</b>`;
                } else {
                    return false;
                }
            }
        },
        series: [{
            name: `Wind Direction (${windDirUnits})`,
            type: 'scatter',
            data: windDir,
            color: '#4282b4',
            marker: {
                radius: 2
            }
        }]
    });

    Highcharts.chart('rain', {
        chart: {type: 'column'},
        title: {text: 'Rainfall Total'},
        xAxis: {type: 'datetime'},
        yAxis: {
            min: 0,
            softMax: 0.25,
            title: {text: `Rainfall (${rainUnits})`}
        },
        tooltip: {valueDecimals: 2},
        series: [{
            name: `Rainfall (${rainUnits})`,
            data: rain,
            color: '#4282b4'
        }]
    });

    Highcharts.chart('rainrate', {
        chart: {type: 'column'},
        title: {text: 'Rainfall Rate'},
        xAxis: {type: 'datetime'},
        yAxis: {
            min: 0,
            softMax: 0.25,
            title: {text: `Rainfall Rate (${rainRateUnits})`}
        },
        tooltip: {valueDecimals: 2},
        series: [{
            name: `Rainfall Rate (${rainRateUnits})`,
            data: rainRate,
            color: '#4282b4'
        }]
    });

    Highcharts.chart('inside-temperature', {
        title: {text: 'Inside Temperature'},
        xAxis: {type: 'datetime'},
        yAxis: {title: {text: `Inside Temperature (${inTempUnits})`}},
        tooltip: {valueDecimals: 1},
        series: [{
            name: `Inside Temperature (${inTempUnits})`,
            data: inTemp,
            color: '#4282b4'
        }]
    });
}

window.addEventListener('DOMContentLoaded', () => {
    // Configure High Charts
    Highcharts.setOptions({
        time: {
            useUTC: false
        },
        chart: {
            backgroundColor: '#1f2937', // dark blue-gray (Tailwind gray-800)
            style: {
                color: '#F3F4F6' // light gray text
            }
        },
        title: {
            style: {
                color: '#F3F4F6'
            }
        },
        xAxis: {
            labels: {
                style: {
                    color: '#D1D5DB' // softer light gray
                }
            },
            lineColor: '#374151',
            tickColor: '#374151',
            gridLineColor: '#374151'
        },
        yAxis: {
            labels: {
                style: {
                    color: '#D1D5DB'
                }
            },
            title: {
                style: {
                    color: '#F3F4F6'
                }
            },
            gridLineColor: '#374151'
        },
        legend: {
            itemStyle: {
                color: '#F3F4F6'
            }
        },
        tooltip: {
            backgroundColor: '#374151',
            style: {
                color: '#F3F4F6'
            }
        }
    });

    // Get history setting from local storage, default to day if null
    const historySetting = localStorage.getItem('historySetting') ?? 'day';

    // Load the initial charts for the past day
    setTimeRange(historySetting);

    // Add event listeners to all the time range buttons
    document.querySelectorAll('.time-range-btn').forEach(button => {
        button.addEventListener('click', () => {
            const range = button.dataset.range;
            setTimeRange(range);
        });
    });

    // Set sidebar toggle button state
    const collapsed = localStorage.getItem('sidebarCollapsed') === 'true';
    if (collapsed) {
        document.getElementById('sidebar-toggle').textContent = 'Show Sidebar';
    } else {
        document.getElementById('sidebar-toggle').textContent = 'Hide Sidebar';
    }

});