$(document).ready(function(){
  /* 进入房间 */
  $(".enter_room").on("click", function(e){
    var key = $("#key").val();
    var channel = $("#channel").val();
    document.cookie="key=" + key + ";path=/";
    document.cookie="channel=" + channel + ";path=/";
    if(key && channel){
      window.location.href = "/interface_Waiting.html";
    }
  });
  $(".video_choose img").on("click", function(e){
      var $e = $(e.target);
      var value = $("#video").val();
      console.log(value);
      if(value === "true"){
        $(".video_choose img").attr("src", "images/ic_login_checkbox.png");
        $(".video_img img").attr("src", "images/ic_login_cell_video_grey.png");
        $("#video").val("false");
      }
      else{
        $("#video").val("true");
        $(".video_choose img").attr("src", "images/ic_login_checkbox_celected.png");
        $(".video_img img").attr("src", "images/ic_login_cell_video.png");
      }
  });
  $(".audio_choose img").on("click", function(e){
      var $e = $(e.target);
      var value = $("#audio").val();
      console.log(value);
      if(value === "true"){
        $(".audio_choose img").attr("src", "images/ic_login_checkbox.png");
        $(".audio_img img").attr("src", "images/ic_login_cell_voice.png");
        $("#audio").val("false");
      }
      else{
        $("#audio").val("true");
        $(".audio_choose img").attr("src", "images/ic_login_checkbox_celected.png");
        $(".audio_img img").attr("src", "images/ic_login_cell_voice_blue.png");
      }
  });
});
