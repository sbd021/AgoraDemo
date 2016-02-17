$(document).ready(function(window){
  var args = window.location.href.split("?");
  var key = '';
  var channel = "";
  var videoChecked = true;
  var audioChecked = true;
  var members = 0;
  var videoDpi = 'sif';
  var videoFrame = [15, 40];
  var dpiList = [['sif', 320, 240], ['vga', 640, 480], ['hd720p', 1280, 720]]
  var client, localStream, remoteStremList = {};
  var uid = undefined;
  if(args.length > 1){
    args = args[1].split("&");
    var data = {};
    for(var i = 0; i < args.length; i ++){
      var temp = args[i].split("=");
      data[temp[0]] = temp[1];
    }
    key = data["key"];
    channel = data["name"];
  }
  console.log(channel, key);
  if(!channel || !key){
    return false;
  }

  function initLocalStream(id, callback){
      uid = id || uid;
      if(localStream){
        client.unpublish(localStream, function(err){
          console.log("unpublish localStream fail.", err);
        });
        localStream.close();
      }
      localStream = AgoraRTC.createStream({streamID: uid, audio: true, video: videoChecked, screen: false});
      if(videoChecked){
        localStream.setVideoResolution(videoDpi);
        localStream.setVideoFrameRate(videoFrame);
      }
      localStream.init(function() {
          console.log("getUserMedia successfully");
          localStream.play('local');
          //if(!videoChecked){
            //$(".screen .left div").addClass("waitAudio");
            //$("#local div").hide();
          //}
          client.publish(localStream, function (err) {
            console.log("Publish local stream error: " + err);
          });
          client.on('stream-published', function (evt) {
            console.log("Publish local stream successfully");
          });

        },
        function (err){
          console.log("getUserMedia failed", err);
        });
      return localStream;
  }
  window.initLocalStream = initLocalStream;
  window.initAgoraRTC = function(video){
    console.log('Joining channel ' + key + ' : ' + channel);
    videoChecked = video;
    if(client){
      initLocalStream();
      return;
    }
    client = AgoraRTC.Client({
    });
    if(!window.timedInterval){
      timedCount();
    }
    /* 初始化之后，加入频道 */
    client.init(key,function () {
      console.log("AgoraRTC client initialized");
      var token = undefined;
      client.join(token, channel, function(uid){
        console.log("User " + uid + " join channel successfully");
        uid = uid;
        localStream = initLocalStream(uid);
      }, 
      function(err) {
        console.log("Join channel failed", err);
      });
    }, function(err){
        window.location.href = "/fullset";
        console.log("AgoraRTC client init failed", err);
         alert(err);
    });

    client.on('stream-added', function (evt) {
      var stream = evt.stream;
      console.log("New stream added: " + stream.getId());
      console.log("Subscribe ", stream);
      client.subscribe(stream, function (err) {
        console.log("Subscribe stream failed", err);
      });
    });
  client.on('peer-leave', function(evt){
    delete remoteStremList[evt.uid];
    $("#agora_remote" + evt.uid).parent().remove();
  });
  client.on('stream-removed', function(evt){
    var stream = evt.stream;
    delete remoteStremList[stream.getId()];
    $("#agora_remote" + stream.getId()).parent().remove();
  });
    client.on('stream-subscribed', function (evt) {
      console.log("Catch stream-subscribed event");
      console.log(evt);
      var stream = evt.stream;
      remoteStremList[stream.getId()] = stream;
      members += 1;
      if(stream.video){
          $('.display_select .displayRemoteAV').append('<li class="remoteVideo"><div id="agora_remote'+stream.getId()+ '"></div></li>');
      }
      else{
        $('.display_select .displayRemoteAV').append('<li class="display_voice"><div class="audioImg" id="agora_remote'+stream.getId()+ '"></div><img src="images/ic_login_cell_voice.png" alt="100*100" /><p>'+ stream.getId() + '</p></li>');
        $("#agora_remote" + stream.getId()).hide();
      }
      stream.play('agora_remote'+stream.getId());
      return true;
    });
  }

  function unpublish() {
    client.unpublish(localStream, function (err) {
      console.log("unpublish error", err);
    });
  }

  function leave() {
    console.log("leave");
    client.leave();
  }
  
  function timedCount()                                                          
  {                                                                              
      var c = 0;                                                                                                                                  
      var t;                                                                         
      window.timedInterval = setInterval(function(){
        hour = parseInt(c / 3600);// 小时数                                        
        min = parseInt(c / 60);// 分钟数                                           
        if(min>=60){                                                               
            min=min%60                                                             
        }                                                                          
        lastsecs = c % 60;                                                         
        $(".telephone").html( hour + ":" + min + ":" + lastsecs )   
        c=c+1;                                                                     
      },1000);                                         
  }                                                                              
                                                                                  
  $(".leave").on('click', function(){
    client.leave();
    window.location.href = "login_index.html";
  });
  var disableAudio = false, disableVideo = false, viewSwitch = false;
  /* 打开/关闭声音 */
  $(".audioSwitch").on("click", function(e){
     disableAudio = !disableAudio;
    if(disableAudio){
       localStream.disableAudio();
       $(".audioSwitch div").removeClass("on").addClass("off").html("打开声音");
    }
    else{
        localStream.enableAudio(); 
       $(".audioSwitch div").removeClass("off").addClass("on").html("静音");
    }
  });
  /* 打开关闭摄像头 */
  $(".videoSwitch").on("click", function(e){
    disableVideo = !disableVideo;
    if(disableVideo){
      localStream.disableVideo();
      $(".videoSwitch div").removeClass("on").addClass("off").html("打开摄像头");
    }
    else{
      localStream.enableVideo();
      $(".videoSwitch div").removeClass("off").addClass("on").html("关闭摄像头");
    }
  });
  /* 切换视角 */
  $(".viewSwitch").on('click', function(e){
    viewSwitch = !viewSwitch;
    var $container = null;
    if(viewSwitch){
      $(".viewSwitch div").removeClass("on").addClass("off");
      $(".screen").attr("class", "screen video switch");
      $(".screen .left").html('<ul></ul>');
      $container = $(".left ul");
      $(".right ul").html("");
      if(localStream.video){
          $('.right ul').append('<li class="remoteVideo"><div id="agora_remote'+ localStream.getId()+ '"></div></li>');
      }
      else{
          $('.right ul').append('<li class="remoteAudio"><div class="audioImg" id="agora_remote'+ localStream.getId()+ '"></div><p>'+ stream.getId() + '</p></li>');
      }
      localStream.show('agora_remote'+ localStream.getId());
    }
    else{
      $(".viewSwitch div").removeClass("off").addClass("on");
      $(".screen").removeClass("switch");
      $(".screen").addClass(members > 1? "multi": "single"); 
      $container = $(".right ul");
      $(".left").html('<div class="" id="local"></div>');
      localStream.show("local");
    }
    $container.html("");
    for(var key in remoteStremList){
      var stream = remoteStremList[key];
      if(stream.video){
        $container.append('<li class="remoteVideo"><div id="agora_remote'+stream.getId()+ '"></div></li>');
      }
      else{
        $container.append('<li class="remoteAudio"><div class="audioImg" id="agora_remote'+stream.getId()+ '"></div><p>'+ stream.getId() + '</p></li>');
      }
      stream.show('agora_remote'+stream.getId());
    }
  });
  /* dpi 拉动条 */
  var dpiList = [['sif', 320, 240], ['vga', 640, 480], ['hd720p', 1280, 720],]
  $(".dpi .slider").on('mousedown', function(e){
    var start = e.pageX;
    var $e = $(this);
    var left = parseInt($e.css("left").replace("px", ""));
    $(".Set").bind('mousemove', function(e){
      var pageX = e.pageX;
      if(left >= 0 && left <= 100){
        var newLeft = Math.max(0, Math.min((pageX - start + left), 100));
        var offset = Math.min(parseInt(newLeft/100 * 100/33), 2);
        offset = offset < 0? 0: offset;
        var dpi = dpiList[offset]; 
        $e.css('left', Math.max(0, Math.min((pageX - start + left), 100)) + 'px');
        $(".dpi_frequency_two").css('width', Math.max(0, Math.min((pageX - start + left), 100)) + '%');
        $(".dpi label").html(dpi[1] + "×" + dpi[2]);
        //localStream.setVideoResolution(dpi[0]);
        videoDpi = dpi[0];
      }
    });
  });
  /* 最大码率 */
  $(".Kbps .slider").on('mousedown', function(e){
    var start = e.pageX;
    var $e = $(this);
    var left = parseInt($e.css("left").replace("px", ""));
    var maxKbps = 2048;
    $(".Set").bind('mousemove', function(e){
      var pageX = e.pageX;
      if(left >= 0 && left <= 100){
        var newLeft = Math.max(0, Math.min((pageX - start + left), 100));
        if(newLeft < 50){
          $(".Kbps label").html(parseInt(newLeft / 100 * maxKbps) + "  Kbps");
        }
        else{
          $(".Kbps label").html((newLeft / 100 * maxKbps / 1024).toFixed(2) + "  M");
        }
        $e.css('left', newLeft + 'px');
        $(".Kbps_frequency_two").css('width', newLeft + '%');
      }
    });
  });
  /* 最大帧率设置 */
  $(".Hz .slider").on('mousedown', function(e){
    var start = e.pageX;
    var $e = $(this);
    var left = parseInt($e.css("left").replace("px", ""));
    var maxFrameRate = 60;
    $(".Set").bind('mousemove', function(e){
      var pageX = e.pageX;
      if(left >= 0 && left <= 100){
        var newLeft = parseInt(Math.max(0, Math.min((pageX - start + left), 100)));
        $e.css('left', newLeft + 'px');
        $(".Hz_frequency_two").css("width", newLeft + "%");
        $(".Hz label").html(parseInt(newLeft* maxFrameRate / 100));
        videoFrame = [15, Math.min(newLeft * maxFrameRate / 100, maxFrameRate)];
      }
    });
  });

  $(".Set").on('mouseup', function(e){$(".Set").unbind('mousemove')});
}(window));
