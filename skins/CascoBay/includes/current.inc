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

<div class="flex justify-between">
<span>$obs.label.outTemp</span>
<span class="font-semibold">$current.outTemp</span>
</div>
<div class="flex justify-between">
<span>$obs.label.wetBulb</span>
<span class="font-semibold">$WetBulb</span>
</div>
<div class="flex justify-between">
<span>$obs.label.dewpoint</span>
<span class="font-semibold">$current.dewpoint</span>
</div>
<div class="flex justify-between">
<span>$obs.label.outHumidity</span>
<span class="font-semibold">$current.outHumidity</span>
</div>
<div class="flex justify-between">
<span>$obs.label.barometer</span>
<span class="font-semibold">$current.barometer ($trend.barometer.formatted)</span>
</div>

#if $span($time_delta=120).windSpeed.avg.raw >= 2.5
<div class="flex justify-between">
<span>$obs.label.wind</span>
<span class="font-semibold">$span($time_delta=120).windDir.avg.ordinal_compass $span($time_delta=120).windSpeed.avg</span>
</div>
#else
<div class="flex justify-between">
<span>$obs.label.wind</span>
<span class="font-semibold">Calm</span>
</div>
#end if

#if $span($time_delta=120).windSpeed.avg.raw >= 2.5 and $span($time_delta=120).windGust.max.raw > $span($time_delta=120).windSpeed.avg.raw
<div class="flex justify-between">
<span>$obs.label.windGust</span>
<span class="font-semibold">$span($time_delta=120).windGust.max</span>
</div>
#end if

#if $current.rainRate.raw > 0.00
<div class="flex justify-between">
<span>$obs.label.rainRate</span>
<span class="font-semibold">$current.rainRate</span>
</div>
#end if

<div class="flex justify-between">
<span>$obs.label.rain_1hour</span>
<span class="font-semibold">$span($hour_delta=1).rain.sum</span>
</div>
<div class="flex justify-between">
<span>$obs.label.rain_24hour</span>
<span class="font-semibold">$span($hour_delta=24).rain.sum</span>
</div>

#if $day.UV.has_data
<div class="flex justify-between">
<span>$obs.label.UV</span>
<span class="font-semibold">$current.UV</span>
</div>
#end if

#if $day.ET.has_data and $day.ET.sum.raw > 0.0
<div class="flex justify-between">
<span>$obs.label.ET</span>
<span class="font-semibold">$current.ET</span>
</div>
#end if

#if $day.radiation.has_data
<div class="flex justify-between">
<span>$obs.label.radiation</span>
<span class="font-semibold">$current.radiation</span>
</div>
#end if

#if $current.heatindex.degree_F.raw >= 80 and $current.heatindex.raw > $current.outTemp.raw
<div class="flex justify-between">
<span>$obs.label.heatindex</span>
<span class="font-semibold">$current.heatindex</span>
</div>
#end if

#if $current.outTemp.degree_F.raw <= 50 and $current.windSpeed.mile_per_hour.raw >= 2.5 and $current.windchill.raw < $current.outTemp.raw
<div class="flex justify-between">
<span>$obs.label.windchill</span>
<span class="font-semibold">$current.windchill</span>
</div>
#end if

#if $day.inTemp.has_data
<div class="flex justify-between">
<span>$obs.label.inTemp</span>
<span class="font-semibold">$current.inTemp</span>
</div>
#end if

#if $day.extraTemp1.has_data
<div class="flex justify-between">
<span>$obs.label.extraTemp1</span>
<span class="font-semibold">$current.extraTemp1.degree_C</span>
</div>
#end if

#if $day.extraTemp2.has_data
<div class="flex justify-between">
<span>$obs.label.extraTemp2</span>
<span class="font-semibold">$current.extraTemp2</span>
</div>
#end if

#if $day.extraTemp3.has_data
<div class="flex justify-between">
<span>$obs.label.extraTemp3</span>
<span class="font-semibold">$current.extraTemp3</span>
</div>
#end if
