## current module for weewx skins
## Copyright Tom Keffer, Matthew Wall
## See LICENSE.txt for your rights
#errorCatcher Echo

##Wet bulb and DeltaT calculations
##Adapted from a Weewx-WD template by Ozgreg
 ##
 #try
     #set $Tc = $current.outTemp.degree_C.raw
     #set $RH = $current.outHumidity.raw
     #set $P = $current.pressure.hPa.raw
     #set $Tdc = (($Tc - (14.55 + 0.114 * $Tc) * (1 - (0.01 * $RH)) - ((2.5 + 0.007 * $Tc) * (1 - (0.01 * $RH))) ** 3 - (15.9 + 0.117 * $Tc) * (1 - (0.01 * $RH)) ** 14))
     #set $E = (6.11 * 10 ** (7.5 * $Tdc / (237.7 + $Tdc)))
     #set $WBc = (((0.00066 * $P) * $Tc) + ((4098 * $E) / ((Tdc + 237.7) ** 2) * $Tdc)) / ((0.00066 * $P) + (4098 * $E) / (($Tdc + 237.7) ** 2))
     #if $unit.unit_type.outTemp == "degree_C"
         #set $WetBulb = "%.1f" % $WBc + $unit.label.outTemp
     #else
         #set $WetBulb = "%.1f" % ($WBc*9/5+32) + $unit.label.outTemp
     #end if
 #except
     #set $WetBulb = 'N/A'
 #end try
 ##
 ##End Wet bulb calculations

<div id='current_widget' class="widget">
  <div class="widget_title">
    Current Conditions
    <a class="widget_control"
      onclick="toggle_widget('current')">&diams;</a>
  </div>

  <div class="widget_contents">
  <table>
    <tbody>
      <tr>
        <td class="label">$obs.label.outTemp</td>
        <td class="data">$current.outTemp</td>
      </tr>
      <tr>
       <td class="label">$obs.label.wetBulb</td>
       <td class="data">$WetBulb</td>
     </tr>
      <tr>
        <td class="label">$obs.label.dewpoint</td>
        <td class="data">$current.dewpoint</td>
      </tr>
      <tr>
        <td class="label">$obs.label.outHumidity</td>
        <td class="data">$current.outHumidity</td>
      </tr>
      <tr>
        <td class="label">$obs.label.barometer</td>
        <td class="data">$current.barometer ($trend.barometer.formatted)</td>
      </tr>

      #if $span($time_delta=120).windSpeed.avg.raw >= 2.5
      <tr>
        <td class="label">$obs.label.wind</td>
        <td class="data">$span($time_delta=120).windDir.avg.ordinal_compass $span($time_delta=120).windSpeed.avg</td>
      </tr>
      #else
      <tr>
        <td class="label">$obs.label.wind</td>
        <td class="data">Calm</td>
      </tr>
      #end if

      #if $span($time_delta=120).windSpeed.avg.raw >= 2.5 and $span($time_delta=120).windGust.max.raw > $span($time_delta=120).windSpeed.avg.raw
      <tr>
        <td class="label">$obs.label.gust</td>
        <td class="data">$span($time_delta=120).windGust.max</td>
      </tr>
      #end if

      #if $current.rainRate.raw > 0.00
      <tr>
        <td class="label">$obs.label.rainRate</td>
        <td class="data">$current.rainRate</td>
      </tr>
      #end if


    <tr>
      <td class="label">$obs.label.rain_1hour</td>
      <td class="data">$span($hour_delta=1).rain.sum</td>
    </tr>
    <tr>
      <td class="label">$obs.label.rain_24hour</td>
      <td class="data">$span($hour_delta=24).rain.sum</td>
    </tr>
#if $day.UV.has_data
      <tr>
        <td class="label">$obs.label.UV</td>
        <td class="data">$current.UV</td>
      </tr>
#end if
#if $day.ET.has_data and $day.ET.sum.raw > 0.0
      <tr>
        <td class="label">$obs.label.ET</td>
        <td class="data">$current.ET</td>
      </tr>
#end if
#if $day.radiation.has_data
      <tr>
        <td class="label">$obs.label.radiation</td>
        <td class="data">$current.radiation</td>
      </tr>
#end if
#if $current.heatindex.degree_F.raw >= 80 and $current.heatindex.raw > $current.outTemp.raw
      <tr>
        <td class="label">$obs.label.heatindex</td>
        <td class="data">$current.heatindex</td>
      </tr>
#end if
#if $current.outTemp.degree_F.raw <= 50 and $current.windSpeed.mile_per_hour.raw >= 2.5 and $current.windchill.raw < $current.outTemp.raw
      <tr>
        <td class="label">$obs.label.windchill</td>
        <td class="data">$current.windchill</td>
      </tr>
#end if
#if $day.inTemp.has_data
      <tr>
        <td class="label">$obs.label.inTemp</td>
        <td class="data">$current.inTemp</td>
      </tr>
#end if
#if $day.extraTemp1.has_data
      <tr>
        <td class="label">$obs.label.extraTemp1</td>
        <td class="data">$current.extraTemp1</td>
      </tr>
#end if
#if $day.extraTemp2.has_data
      <tr>
        <td class="label">$obs.label.extraTemp2</td>
        <td class="data">$current.extraTemp2</td>
      </tr>
#end if
#if $day.extraTemp3.has_data
      <tr>
        <td class="label">$obs.label.extraTemp3</td>
        <td class="data">$current.extraTemp3</td>
      </tr>
#end if
    </tbody>
  </table>
  </div>

</div>
