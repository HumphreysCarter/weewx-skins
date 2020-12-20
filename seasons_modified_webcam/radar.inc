## radar module for weewx skins
## Copyright Tom Keffer, Matthew Wall
## See LICENSE.txt for your rights
#errorCatcher Echo
#encoding UTF-8

#if $Extras.has_key('radar_img')
<div id='radar_widget' class="widget">
  <div class="widget_title">
      #if $Extras.has_key('radar_url')
        <a href="$Extras.radar_url">Radar</a>
      #end if
      #if $Extras.has_key('radar_url') == False
        Radar
      #end if

    <a class="widget_control"
      onclick="toggle_widget('radar')">&diams;</a>
  </div>

  <div class="widget_contents">
    #if $Extras.has_key('radar_url')
    <a  href="$Extras.radar_url">
    #end if
      <img src="$Extras.radar_img" alt="Radar Not Available" />
    #if $Extras.has_key('radar_url')
    </a>
    #end if
  </div>
</div>
#end if
