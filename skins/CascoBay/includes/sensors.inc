## sensors module for weewx skins
## Copyright Tom Keffer, Matthew Wall
## See LICENSE.txt for your rights
#errorCatcher Echo
#encoding UTF-8

## this is a conditional display of sensor data, including connectivity,
## battery status, and various voltages.  if there are no data available,
## then this degenerates to nothing displayed.

## remember the current time - we will use it more than once.
#import time
#set $now = time.time()

## use this span to determine whether there are any data to consider.
#set $recent=$span($day_delta=30, boundary='midnight')

#def get_battery_status($x)
#if $x is None
<span class="text-gray-400 font-semibold">❓ $gettext('UNKNOWN')</span>
#elif $x == 1
<span class="text-red-500 font-semibold">⚠️ $gettext('LOW')</span>
#else
<span class="text-green-500 font-semibold">$gettext('OK')</span>
#end if
#end def

## provide an indication of how much time has passed since the last sensor
## reading.
#def get_time_delta($last_ts, $now)
  #if $last_ts
    #set $delta = int($now - $last_ts)
    #if $delta < 60
 
#elif $delta < 3600
      #set $minutes = int($delta / 60)
$minutes $gettext('minutes ago')
    #elif $delta < 86400
      #set $hours = int($delta / 3600)
$hours $gettext('hours ago')
    #else
      #set $days = int($delta / 86400)
$days $gettext('days ago')
    #end if
  #else
$gettext('never')
  #end if
#end def


## Get the list of sensor observations from the configuration file, otherwise
## fallback to a very rudimentary set.
#set $sensor_connections = $to_list($DisplayOptions.get('sensor_connections', ['rxCheckPercent']))
#set $sensor_batteries = $to_list($DisplayOptions.get('sensor_batteries', ['outTempBatteryStatus', 'inTempBatteryStatus', 'rainBatteryStatus', 'windBatteryStatus', 'uvBatteryStatus', 'txBatteryStatus']))
#set $sensor_voltages = $to_list($DisplayOptions.get('sensor_voltages', ['consBatteryVoltage', 'heatingVoltage', 'supplyVoltage', 'referenceVoltage']))

## first see what sensor data are available

#set $have_conn = 0
#for $x in $sensor_connections
  #if $getattr($recent, $x).has_data
    #set $have_conn = 1
  #end if
#end for

#set $have_battery = 0
#for $x in $sensor_batteries
  #if $getattr($recent, $x).has_data
    #set $have_battery = 1
  #end if
#end for

#set $have_voltage = 0
#for $x in $sensor_voltages
  #if $getattr($recent, $x).has_data
    #set $have_voltage = 1
  #end if
#end for


## now display the available data only

#if $have_conn or $have_battery or $have_voltage

  #if $have_conn
  <div>
    <h3 class="text-base font-semibold mb-2">$gettext("Connectivity")</h3>
    #for $x in $sensor_connections
      #if $getattr($recent, $x).has_data
        <div class="flex justify-between">
          <span>$obs.label[$x]</span>
          <div class="text-right">
            #set $quality = $getVar('current.' + $x).raw
            #if $quality < 50
              <span class="text-red-400 font-semibold">⚠️ $getVar('current.' + $x)</span>
            #else
              <span class="font-semibold">$getVar('current.' + $x)</span>
            #end if
            <div class="text-xs text-gray-400">$get_time_delta($getattr($recent, $x).lasttime.raw, $now)</div>
          </div>
        </div>
      #end if
    #end for
  </div>
  #end if

  #if $have_battery
  <div>
    <h3 class="text-base font-semibold mb-2">$gettext("Battery Status")</h3>
    #for $x in $sensor_batteries
      #if $getattr($recent, $x).has_data
        <div class="flex justify-between">
          <span>$obs.label[$x]</span>
          <div class="text-right">
            <div class="font-semibold">$get_battery_status($getVar('current.%s.raw' % $x))</div>
            <div class="text-xs text-gray-400">$get_time_delta($getattr($recent, $x).lasttime.raw, $now)</div>
          </div>
        </div>
      #end if
    #end for
  </div>
  #end if

  #if $have_voltage
  <div>
    <h3 class="text-base font-semibold mb-2">$gettext("Voltage")</h3>
    #for $x in $sensor_voltages
      #if $getattr($recent, $x).has_data
        <div class="flex justify-between">
          <span>$obs.label[$x]</span>
          <div class="text-right">
            #set $voltage = $getVar('current.' + $x).raw
            #if $voltage and $voltage < 3.5
              <span class="text-red-500 font-semibold">⚠️ $getVar('current.' + $x)</span>
            #else
              <span class="font-semibold">$getVar('current.' + $x)</span>
            #end if
            <div class="text-xs text-gray-400">$get_time_delta($getattr($recent, $x).lasttime.raw, $now)</div>
          </div>
        </div>
      #end if
    #end for
  </div>
  #end if

#end if
