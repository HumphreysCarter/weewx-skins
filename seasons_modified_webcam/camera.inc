## camera module for weewx skins
## Copyright Carter Humphreys
#errorCatcher Echo
#encoding UTF-8

#if $Extras.has_key('cam_img')
<div id='camera_widget' class="widget">
  <div class="widget_title">
      #if $Extras.has_key('cam_url')
        <a href="$Extras.cam_url">Camera</a>
      #end if
      #if $Extras.has_key('cam_url') == False
        Camera
      #end if

    <a class="widget_control"
      onclick="toggle_widget('camera')">&diams;</a>
  </div>

  <div class="widget_contents">
    #if $Extras.has_key('cam_url')
    <a  href="$Extras.cam_url">
    #end if
      <img src="$Extras.cam_img" alt="Camera Not Available" />
    #if $Extras.has_key('cam_url')
    </a>
    #end if
  </div>
</div>
#end if
