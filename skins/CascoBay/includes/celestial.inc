## sun/moon rise/set module for weewx skins
## Copyright Tom Keffer, Matthew Wall
## See LICENSE.txt for your rights
#errorCatcher Echo
#encoding UTF-8

## If extended almanac information is available, do extra calculations.
#if $almanac.hasExtras
  #set $sun_altitude = $almanac.sun.alt
  #if $sun_altitude < 0
    #set $sun_None='<i>%s</i>' % $gettext("Always down")
    #set $daylight_str = "00:00"
  #else
    #set $sun_None='<i>%s</i>' % $gettext("Always up")
    #set $daylight_str = "24:00"
  #end if

  #set $sunrise_ts = $almanac.sun.rise.raw
  #set $sunset_ts = $almanac.sun.set.raw
  #if $sunrise_ts and $sunset_ts
    #set $daylight_s = $sunset_ts - $sunrise_ts
    #set $daylight_hours = int($daylight_s / 3600)
    #set $daylight_minutes = int(($daylight_s % 3600) / 60)
    #set $daylight_str = "%02d:%02d" % ($daylight_hours, $daylight_minutes)
  #end if
#end if

  <div>
    <div>
      #if $almanac.hasExtras
      <div class="grid grid-cols-2 gap-4 text-sm font-medium">
        <!-- Sun -->
        <div>
          <h3 class="text-base font-semibold mb-2">
          <svg class="w-6 h-6 text-gray-800 dark:text-white" aria-hidden="true" xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="currentColor" viewBox="0 0 24 24">
          <path fill-rule="evenodd" d="M13 3a1 1 0 1 0-2 0v2a1 1 0 1 0 2 0V3ZM6.343 4.929A1 1 0 0 0 4.93 6.343l1.414 1.414a1 1 0 0 0 1.414-1.414L6.343 4.929Zm12.728 1.414a1 1 0 0 0-1.414-1.414l-1.414 1.414a1 1 0 0 0 1.414 1.414l1.414-1.414ZM12 7a5 5 0 1 0 0 10 5 5 0 0 0 0-10Zm-9 4a1 1 0 1 0 0 2h2a1 1 0 1 0 0-2H3Zm16 0a1 1 0 1 0 0 2h2a1 1 0 1 0 0-2h-2ZM7.757 17.657a1 1 0 1 0-1.414-1.414l-1.414 1.414a1 1 0 1 0 1.414 1.414l1.414-1.414Zm9.9-1.414a1 1 0 0 0-1.414 1.414l1.414 1.414a1 1 0 0 0 1.414-1.414l-1.414-1.414ZM13 19a1 1 0 1 0-2 0v2a1 1 0 1 0 2 0v-2Z" clip-rule="evenodd"/>
        </svg>
          </h3>
          <div class="flex justify-between">
            <span>Rise</span>
            <span class="font-bold">$almanac.sun.rise.format(None_string=$sun_None)</span>
          </div>
          <div class="flex justify-between">
            <span>Set</span>
            <span class="font-bold">$almanac.sun.set.format(None_string=$sun_None)</span>
          </div>
          <div class="flex justify-between">
            <span>Daylight</span>
            <span class="font-bold">$daylight_str</span>
          </div>
        </div>

        <!-- Moon -->
        <div>
          <h3 class="text-base font-semibold mb-2">
          <svg class="w-6 h-6 text-gray-800 dark:text-white" aria-hidden="true" xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="none" viewBox="0 0 24 24">
  <path stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 21a9 9 0 0 1-.5-17.986V3c-.354.966-.5 1.911-.5 3a9 9 0 0 0 9 9c.239 0 .254.018.488 0A9.004 9.004 0 0 1 12 21Z"/>
</svg>

          </h3>
          <div class="flex justify-between">
            <span>Rise</span>
            <span class="font-bold">$almanac.moon.rise</span>
          </div>
          <div class="flex justify-between">
            <span>Set</span>
            <span class="font-bold">$almanac.moon.set</span>
          </div>
          <div class="flex justify-between">
            <span class="invisible">-</span> <!-- alignment -->
            <span class="text-right">
              <span class="font-semibold">$almanac.moon_phase</span><br />
              <span class="text-sm">$almanac.moon_fullness%</span>
            </span>
          </div>
        </div>
      </div>

      #else
        ## No extended almanac information available. Fall back to basic info.
      <table class="celestial">
        <tr>
          <td class="label">$gettext("Sunrise")</td>
          <td class="data">$almanac.sunrise</td>
        </tr>
        <tr>
          <td class="label">$gettext("Sunset")</td>
          <td class="data">$almanac.sunset</td>
        </tr>
        <tr>
          <td class="label">$gettext("Moon Phase")</td>
          <td class="data">$almanac.moon_phase<br/>
            $almanac.moon_fullness%</td>
        </tr>
      </table>
      #end if
    </div>
  </div>
