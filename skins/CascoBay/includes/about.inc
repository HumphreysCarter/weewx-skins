## about module for weewx skins
## Copyright Tom Keffer, Matthew Wall
## See LICENSE.txt for your rights
#errorCatcher Echo
#encoding UTF-8

  <div class="flex justify-between">
    <span>$gettext("Hardware")</span>
    <span class="font-semibold">$station.hardware</span>
  </div>
  <div class="flex justify-between">
    <span>$gettext("Latitude")</span>
    <span class="font-semibold">$station.latitude[0]&deg; $station.latitude[1]' $station.latitude[2]"</span>
  </div>
  <div class="flex justify-between">
    <span>$gettext("Longitude")</span>
    <span class="font-semibold">$station.longitude[0]&deg; $station.longitude[1]' $station.longitude[2]"</span>
  </div>
  <div class="flex justify-between">
    <span>$pgettext("Geographical", "Altitude")</span>
    <span class="font-semibold">$station.altitude</span>
  </div>
  <div class="flex justify-between">
    <span>$gettext("Server uptime")</span>
    <span class="font-semibold">$station.os_uptime.long_form</span>
  </div>
  <div class="flex justify-between">
    <span>$gettext("WeeWX uptime")</span>
    <span class="font-semibold">$station.uptime.long_form</span>
  </div>
  <div class="flex justify-between">
    <span>$gettext("WeeWX version")</span>
    <span class="font-semibold">$station.version</span>
  </div>
  <div class="flex justify-between">
    <span>$gettext("Skin")</span>
    <span class="font-semibold">$SKIN_NAME $SKIN_VERSION</span>
  </div>
