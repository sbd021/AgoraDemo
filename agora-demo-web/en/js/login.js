$(document).ready(function(){
  /* 进入房间 */
  $(".enter_room").on("click", function(e){
    var key = $("#key").val();
    var channel = $("#channel").val();
    document.cookie="key=" + key + ";path=/";
    document.cookie="channel=" + channel + ";path=/";
    if(key && channel){
      window.location.href = "interface_Waiting.html";
    }
  });
  function disableVideo(){
      $(".video_choose img").attr("src", "images/ic_login_checkbox.png");
      $(".video_img img").attr("src", "images/ic_login_cell_video_grey.png");
      $("#video").val("false");
  }
  function enableVideo(){
      $("#video").val("true");
      $(".video_choose img").attr("src", "images/ic_login_checkbox_celected.png");
      $(".video_img img").attr("src", "images/ic_login_cell_video.png");
  }
  function disableAudio(){
      $(".audio_choose img").attr("src", "images/ic_login_checkbox.png");
      $(".audio_img img").attr("src", "images/ic_login_cell_voice.png");
      $("#audio").val("false");
  }
  function enableAudio(){
      $("#audio").val("true");
      $(".audio_choose img").attr("src", "images/ic_login_checkbox_celected.png");
      $(".audio_img img").attr("src", "images/ic_login_cell_voice_blue.png");
  }
  $(".video_choose img").on("click", function(e){
      var $e = $(e.target);
      var value = $("#video").val();
      console.log(value);
      disableAudio();
      if(value === "true"){
        disableVideo();
        enableAudio();
      }
      else{
        enableVideo();
      }
  });
  $(".audio_choose img").on("click", function(e){
      var $e = $(e.target);
      var value = $("#audio").val();
      console.log(value);
      disableVideo();
      if(value === "true"){
        disableAudio();
        enableVideo();
      }
      else{
        enableAudio();
      }
  });
});
