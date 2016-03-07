$(document).ready(function(){
  var args = window.location.href.split("?");
  var key = '';
  var channel = "";
  var videoChecked = true;
  var audioChecked = true;
  var members = 0;
  var disableAudio = false, disableVideo = false, viewSwitch = false;
  if(args.length > 1){
    args = args[1].split("&");
    var data = {};
    for(var i = 0; i < args.length; i ++){
      var temp = args[i].split("=");
      data[temp[0]] = temp[1];
    }
    key = data["key"];
    channel = data["channel"];
    videoChecked = data["video"] === 'true';
    audioChecked = !(data["audio"] === "false");
    $("#channelSpan").html(channel);

  }
  console.log(channel, key);
  var client, localStream, remoteStremList = {};

  function bindPlayer(stream) {
    console.log("bindPlayer");
    stream.showing= false;
    stream.show = function (elementID, options) {
      if (stream.hasVideo() || stream.hasScreen()) {
        if (elementID !== undefined) {
          stream.player = new Agora.VideoPlayer({
            id: stream.getId(),
            stream: stream,
            elementID: elementID,
            options: options});
          stream.showing = true;
        }
      } else if (stream.hasAudio()) {
        stream.player = new Agora.AudioPlayer({
          id: stream.getId(),
          stream: stream,
          elementID: elementID,
          options: options});
        stream.showing = true;
      }
    };
    stream.play = stream.show;
  }

    //document.getElementById("video").disabled = true;
  console.log('Joining channel ' + key + ' : ' + channel);
  client = Agora.Client({
  });
  client.init(key, channel, function (err) {
    console.log("Connecting to vocs failed", err);
  });
  client.on('client-initialized', function (evt) {
    var data = evt.attr;
    console.log("Connecting vocs done", JSON.stringify(data['vos_list'][0]));
    var uid = data.uid;
    console.log("Connecting to vos gateway");
    client.connect(function (err) {
      console.log("Join vos gateway failed", err);
    });
    client.on('client-connected', function (evt) {
      console.log("Join vos gateway successfully");
      console.log("Login to vos");
      client.join(function (msg) {
        console.log(msg);
      });
      client.on('join-success', function () {
        console.log("Join vos successfully");
        localStream = Agora.Stream({
          streamID: uid, audio: true, video: videoChecked,
          data: false, screen: false});
        if (videoChecked) {
          localStream.setVideo("sif", [15, 60]);
        }
        localStream.init(function (err) {
          console.log("Media access failed", err);
        });
        localStream.on('access-accepted', function () {
          bindPlayer(localStream);
          console.log("Media access successfully: streamId = ", localStream.getId());
          localStream.show('local');
          //if(!audioChecked){
            ////localStream.disableAudio();
            //$(".audioSwitch").trigger("click");
          //}
          if(!videoChecked){
            $(".screen .left div").addClass("waitAudio");
            $("#local div").hide();
          }
          console.log("Publish local stream");
          client.publish(localStream, function (err) {
            console.log("Publish local stream error: " + err);
          });
          client.on('stream-published', function (evt) {
            var stream = evt.stream;
            console.log("Catch stream-published event");
            console.log(localStream);
          });
        });
      });
      client.on('stream-added', function (evt) {
        console.log("Catch stream-added event");
        var stream = evt.stream;
        console.log("Subscribe ", stream);
        bindPlayer(stream);
        client.subscribe(stream, function (err) {
          console.log("Subscribe failed", err);
        });
      });
      client.on('stream-removed', function(evt){
        console.log("Catch stream-removed event");
        var stream = evt.stream;
        $("#agora_remote" + stream.getId()).parent().remove();
      });
      client.on('overflowchanged', function(evt){
        console.log("stream overflowchanged");
        console.log(evt);
      });
      client.on('stream-subscribed', function (evt) {
        console.log("Catch stream-subscribed event");
        console.log(evt);
        var stream = evt.stream;
        remoteStremList[stream.getId()] = stream;
        members += 1;
        $(".content").hide();
        members == 1? timedCount(): null;
        if(!videoChecked){
          $(".screen").removeClass("wait").addClass("audio");
          $(".right ul").append('<li class="remoteAudio"><div id="agora_remote' + stream.getId() + '"></div><p>'+ stream.getId() + '</p></li>')
          stream.show('agora_remote'+stream.getId());
          $("#agora_remote" + stream.getId() + " div").hide();
          return;
        }
        var $container = viewSwitch? $(".left ul"):$(".right ul"); 
        if(members == 1){
            $(".screen").removeClass("wait").addClass("video single");
            if(stream.video){
              $container.append('<li class="remoteVideo"><div id="agora_remote'+stream.getId()+ '"></div></li>');
            }
            else{
              $container.append('<li class="remoteAudio"><div class="audioImg" id="agora_remote'+stream.getId()+ '"></div><p>'+ stream.getId() + '</p></li>');
              $("#agora_remote" + stream.getId() + " div").hide();
            }
        }
        else{
          $(".screen").removeClass("wait single").addClass("video multi");
            if(stream.video){
              $container.append('<li class="remoteVideo"><div id="agora_remote'+stream.getId()+ '"></div></li>');
            }
            else{
              $container.append('<li class="remoteAudio"><div class="audioImg" id="agora_remote'+stream.getId()+ '"></div><p>'+ stream.getId() + '</p></li>');
              $("#agora_remote" + stream.getId() + " div").hide();
            }
        }
        stream.show('agora_remote'+stream.getId());

      });
    });
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
    window.location.href = "/";
  });
  /* 打开/关闭声音 */
  $(".audioSwitch").on("click", function(e){
     disableAudio = !disableAudio;
    if(disableAudio){
       localStream.disableAudio();
       $(".audioSwitch div").removeClass("on").addClass("off");
       $(".audioSwitch p").html("打开声音");
    }
    else{
        localStream.enableAudio(); 
       $(".audioSwitch div").removeClass("off").addClass("on");
       $(".audioSwitch p").html("静音");
    }
  });
  /* 打开关闭摄像头 */
  $(".videoSwitch").on("click", function(e){
    disableVideo = !disableVideo;
    if(disableVideo){
      localStream.disableVideo();
      $(".videoSwitch div").removeClass("on").addClass("off");
      $(".videoSwitch p").html("打开摄像头");
    }
    else{
      localStream.enableVideo();
      $(".videoSwitch div").removeClass("off").addClass("on");
      $(".videoSwitch p").html("关闭摄像头");
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
});
