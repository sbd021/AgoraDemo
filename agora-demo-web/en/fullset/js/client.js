$(document).ready(function(){
  var args = window.location.href.split("?");
  var key = '';
  var channel = "";
  var videoChecked = true;
  var audioChecked = true;
  var username = '';
  var members = 0;
  var videoDpi = '480p';
  var videoFrame = [20, 20];
  var videoBR = [800, 800];
  var dpiList = [['240p', 320, 240], ['480p', 640, 480], ['720p', 1280, 720]]
  if(args.length > 1){
    args = args[1].split("&");
    var data = {};
    for(var i = 0; i < args.length; i ++){
      var temp = args[i].split("=");
      data[temp[0]] = temp[1];
    }
    key = data["key"];
    channel = decodeURI(data["channel"]);
    videoChecked = data["video"] === 'true';
    audioChecked = !(data["audio"] === "false");
    $("#channelSpan").html(channel);
    username = decodeURI(data['username'] || username);
    $(".menu_content .color").first().html(username);
  }
  console.log(channel, key);
  /* 获得已经访问过到channel */
  var channelList = localStorage.getItem("channelList");
  channelList = channelList? channelList.split(","): [];
  if(channelList.indexOf(channel) == -1){
      channelList.push(channel);
  }
  channelList.forEach(function(e, index){
    var $li = '<li data-channel="' + e + '"><img src="images/voice_index_three.png" /><label>' + e;
    if(e === channel){
      $li += '<span class="color">(In Conferencing)</span>';
    }
    $li += '</label></li>'
    $(".menu_content ul").append($li);
  });
  localStorage.setItem("channelList", channelList.join(","))
  var client, localStream, remoteStremList = {};
  var uid = undefined;

  function initLocalStream(id, callback){
      uid = id || uid;
      if(localStream){
        console.log("localStream exists");
        client.unpublish(localStream, function(err){
          console.log("unpublish localStream fail.", err);
        });
        localStream.close();
      }
      localStream = AgoraRTC.createStream({streamID: uid, audio: true, video: videoChecked, screen: false});
      console.log(videoDpi, videoFrame, videoBR);
      if(videoChecked){
        localStream.setVideoResolution(videoDpi);
        localStream.setVideoFrameRate(videoFrame);
        localStream.setVideoBitRate(videoBR);
        //localStream.setVideoResolution('720p');
        //localStream.setVideoFrameRate([15, 15]);
        //localStream.setVideoBitRate([800,800]);
      }
      localStream.init(function() {
        console.log("getUserMedia successfully");
        console.log(localStream);
        if(!videoChecked){
          $(".screen .left div").addClass("waitAudio");
          $("#local div").hide();
          localStream.play('local');
        }
        else{
          if(viewSwitch){
              $(".right ul").html('');
              $(".right ul").append('<li class="remoteVideo"><div id="agora_remote'+localStream.getId()+ '"></div></li>');
              localStream.play('agora_remote'+ localStream.getId());
          }
          else{
            $(".left").html('<div class="" id="local"></div>');
            localStream.play("local");
          }
        }
        client.publish(localStream, function (err) {
          console.log("Publish local stream error: " + err);
        });
        //client.on('stream-published', function (evt) {
          //console.log("Publish local stream successfully");
        //});
        },
        function (err){
          console.log("getUserMedia failed", err);
        });
      return localStream;
  }

  function displayInfo(stream){
    var $p = $('<p id="infoStream' + stream.getId() + '">' + stream.getId() + ' joined the room</p>');
    $(".info").append($p);
    setTimeout(function(){$p.remove();}, 10*1000);
  }
    //document.getElementById("video").disabled = true;
  console.log('Joining channel ' + key + ' : ' + channel);
    client = AgoraRTC.Client({
    });
  /* 初始化之后，加入频道 */
  function initAgoraRTC(){
    client.init(key,function () {
      console.log("AgoraRTC client initialized");
      var token = undefined;
      client.join(channel, undefined, function(uid){
        console.log("User " + uid + " join channel successfully");
        localStream = initLocalStream(uid);
      }, 
      function(err) {
        console.log("Join channel failed", err);
      });
    }, function(err){
        console.log("AgoraRTC client init failed", err);
        alert(err);
        window.location.href = "/fullset";
    });
  }

  initAgoraRTC();
  client.on('stream-added', function (evt) {
    var stream = evt.stream;
    console.log("New stream added: " + stream.getId());
    console.log("Subscribe ", stream);
    client.subscribe(stream, function (err) {
      console.log("Subscribe stream failed", err);
    });
  });
  client.on('peer-leave', function(evt){
    var $p = $('<p id="infoStream' + evt.uid + '">' + evt.uid + 'quit from room</p>');
    $(".info").append($p);
    setTimeout(function(){$p.remove();}, 10*1000);
    delete remoteStremList[evt.uid];
    console.log($("#agora_remote" + evt.uid).length);
    if($("#agora_remote" + evt.uid).length > 0){
      $("#agora_remote" + evt.uid).parent().remove();
    }
    else{
      $("#player_" + evt.uid).remove();
    }
  });
  client.on('stream-removed', function(evt){
    var stream = evt.stream;
    var $p = $('<p id="infoStream' + stream.getId() + '">' + stream.getId() + 'Quit From Room</p>');
    $(".info").append($p);
    setTimeout(function(){$p.remove();}, 10*1000);
    delete remoteStremList[stream.getId()];
    if($("#agora_remote" + stream.getId()).length > 0){
      $("#agora_remote" + stream.getId()).parent().remove();
    }
    else{
      $("#player_" + stream.getId()).remove();
    }
  });
  client.on('stream-subscribed', function (evt) {
    var stream = evt.stream;
    console.log("Catch stream-subscribed event");
    console.log("Subscribe remote stream successfully: " + stream.getId());
    console.log(evt);
    displayInfo(stream);
    remoteStremList[stream.getId()] = stream;
    members = 0;
    for(var key in remoteStremList){
      members += 1 ;
    }
    $(".content").hide();
    members == 1? timedCount(): null;
    var $container = viewSwitch? $(".left ul"):$(".right ul"); 
    if(!videoChecked){
      $(".screen").removeClass("wait").addClass("audio");
      $container.append('<li class="remoteAudio"><div id="agora_remote' + stream.getId() + '"></div><p>'+ stream.getId() + '</p></li>')
      stream.play('agora_remote'+stream.getId());
      $("#agora_remote" + stream.getId() + " div").hide();
      return;
    }
    if(members == 1){
        $(".screen").removeClass("wait").addClass("video single");
    }
    else{
      $(".screen").removeClass("wait single").addClass("video");
      viewSwitch? null:$(".screen").addClass("multi");
    }
    if(stream.video){
      $container.append('<li class="remoteVideo"><div id="agora_remote'+stream.getId()+ '"></div></li>');
    }
    else{
      $container.append('<li class="remoteAudio"><div class="audioImg" id="agora_remote'+stream.getId()+ '"></div><p>'+ stream.getId() + '</p></li>');
      $("#agora_remote" + stream.getId() + " div").hide();
    }
    stream.play('agora_remote'+stream.getId());
  });
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
      setInterval(function(){
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
       $(".audioSwitch div").removeClass("on").addClass("off");
       $(".audioSwitch p").html("Enabled audio");
    }
    else{
        localStream.enableAudio(); 
       $(".audioSwitch div").removeClass("off").addClass("on");
       $(".audioSwitch p").html("Mute");
    }
  });
  /* 打开Camera Off */
  $(".videoSwitch").on("click", function(e){
    disableVideo = !disableVideo;
    if(disableVideo){
      localStream.disableVideo();
      $(".videoSwitch div").removeClass("on").addClass("off");
      $(".videoSwitch p").html("Camera On");
    }
    else{
      localStream.enableVideo();
      $(".videoSwitch div").removeClass("off").addClass("on");
      $(".videoSwitch p").html("Camera Off");
    }
  });
  /* Switch View */
  $(".viewSwitch").on('click', function(e){
    viewSwitch = !viewSwitch;
    var $container = null;
    $(".big_images .cancel").trigger("click");
    if(viewSwitch){
      $(".viewSwitch div").removeClass("on").addClass("off");
      $(".screen").attr("class", "screen video switch");
      $(".screen .left").html('<ul></ul>');
      $container = $(".left ul");
      $(".right ul").html("");
      console.log('localStream', localStream);
      if(localStream.video){
          $(".right ul").append('<li class="remoteVideo"><div id="agora_remote'+ localStream.getId()+ '"></div></li>');
      }
      else{
          $(".right ul").append('<li class="remoteAudio"><div class="audioImg" id="agora_remote'+ localStream.getId()+ '"></div><p>'+ stream.getId() + '</p></li>');
      }
      localStream.play('agora_remote'+ localStream.getId());
    }
    else{
      $(".viewSwitch div").removeClass("off").addClass("on");
      $(".screen").removeClass("switch");
      $(".screen").addClass(members > 1? "multi": "single"); 
      $container = $(".right ul");
      $(".left").html('<div class="" id="local"></div>');
      localStream.play("local");
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
      stream.play('agora_remote'+stream.getId());
    }
  });
  /* dpi 拉动条 */
  var dpiIndex = 0;
  $(".dpi .slider").on('mousedown', function(e){
    var start = e.pageX;
    var $e = $(this);
    var left = parseInt($e.css("left").replace("px", ""));
    $(".Set").bind('mousemove', function(e){
      var pageX = e.pageX;
      if(left >= 0 || left <= 100){
        var newLeft = Math.max(0, Math.min((pageX - start + left), 100));
        var offset = Math.min(parseInt(newLeft/100 * 100/33), 2);
        var dpi = dpiList[offset]; 
        $e.css('left', Math.max(0, Math.min((pageX - start + left), 100)) + 'px');
        $(".dpi_frequency_two").css('width', Math.max(0, Math.min((pageX - start + left), 100)) + '%');
        $(".dpi label").html(dpi[1] + "×" + dpi[2]);
        //localStream.setVideoResolution(dpi[0]);
        videoDpi = dpi[0];
      }
    });
  });
  /* Max. Bitrate */
  $(".Kbps .slider").on('mousedown', function(e){
    var start = e.pageX;
    var $e = $(this);
    var maxKbps = 1536;
    var left = parseInt($e.css("left").replace("px", ""));
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
        videoBR = [Math.min(newLeft * maxKbps / 100, maxKbps), Math.min(newLeft * maxKbps / 100, maxKbps)];
      }
    });
  });
  /* Max. Framerate设置 */
  $(".Hz .slider").on('mousedown', function(e){
    var start = e.pageX;
    var $e = $(this);
    var maxFrameRate = 30;
    var left = parseInt($e.css("left").replace("px", ""));
    $(".Set").bind('mousemove', function(e){
      var pageX = e.pageX;
      if(left >= 0 && left <= 100){
        var newLeft = parseInt(Math.max(0, Math.min((pageX - start + left), 100)));
        $e.css('left', newLeft + 'px');
        $(".Hz_frequency_two").css("width", newLeft + "%");
        $(".Hz label").html(parseInt(newLeft* maxFrameRate / 100));
	var fr = Math.min(newLeft * maxFrameRate / 100, maxFrameRate);
        videoFrame = [Math.floor(fr), Math.ceil(fr)];
      }
    });
  });

  $(".Set").on('mouseup', function(e){$(".Set").unbind('mousemove')});
  /* 切换频道 */
  $("#menu_content ul li").on('click', function(e){
    var $e = $(e.currentTarget);
    var channel = $e.data("channel");
    if(channel)
    {window.location.href = "?channel=" + channel + "&key=" + key + "&video=" + videoChecked;}
    else{
      return false;
    }
  });
  /* 确定修改Video Settings*/
  $(".begin_meeting").on('click', function(e){
    initLocalStream();
    //initAgoraRTC();
    $(".Set_cancel").trigger("click");
  });
  /* 点击右侧视频，切换大小屏幕 */
  $(".right  ul").delegate('.remoteVideo', 'click', function(e){
    if(viewSwitch){
      return false;
    }
    var id = $(this).find('div').attr("id").substring(12);
    var stream = remoteStremList[id] || localStream;
    console.log($(this), id, stream);
    if(stream){
      var leftStream = remoteStremList[$("#local").data("id")] || localStream;
      $(this).html('<div id="agora_remote'+leftStream.getId()+ '"></div>');
      $("#local").html('');
      stream.play("local");
      $("#local").data("id", stream.getId());
      leftStream.play('agora_remote'+ leftStream.getId());
    }
  });
  /* Switch View之后，点击左侧视频，放大 */
  $(".left").delegate('ul .remoteVideo', 'click', function(e){
    if(!viewSwitch){
      return false;
    }
    var id = $(this).find('div').attr("id").substring(12);
    var container = $(this);
    var stream = remoteStremList[id];
    console.log($(this), id, stream);
    if(stream){
      //stream.play("local");
      //localStream.play('agora_remote'+ localStream.getId());
      $(this).html('');
      $(".big_images .bigVideo").attr('id', "agora_remote" + stream.getId())
      $(".big_images").show();
      stream.play("agora_remote" + stream.getId());
      $(".big_images .cancel").on('click', function(e){
        console.log('cancel');
        $(container).html('<div id="agora_remote'+ stream.getId()+ '"></div>');
        $(".big_images .bigVideo").attr("id", '').html("");
        stream.play("agora_remote" + stream.getId());
        $(this).unbind('click');
        $(".big_images").hide();
      });
    }
  });
});
