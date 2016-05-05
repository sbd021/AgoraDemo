$(document).ready(function(){

  /* 删除选中的房间 */
  function deleteFunc(retVal) {
      if (retVal == "Success") {
          $(".selected_options p").each(function(index, e){
             if(e.innerHTML == name){
                e.remove();
             }
          });
          name = '';
          $(".selected label").html("查询会议室");
      } 
      else {
        alert("Destroy room failed!");
      }
  }
  /* 查询已有会议室 */
  function queryFunc(retVal) {
    console.log("QUery room:", retVal);
    if (retVal.length != 0) {
      var $select = $(".selected_options");
      $select.html("");
      for (var i in retVal) {
        $select.append('<p>' + retVal[i] + '</p>')
      }
    } else {
      //alert("Query room failed!");
      return false;
    }
  }

  $("#key").on('change', function(e){
    var vkey = $("#key");
    if (agoraExt == null) {
      if (vkey.val() == "") {
        alert("please input vendor key, try again!");
        return;
      } else {
        agoraExt = Agora.Ext({
          vendor_key : vkey.val()
        });
      }
    }
    agoraExt.queryMeeting(queryFunc);
  });
  /* 创建新会议室 */
  function createFunc(retVal) {
    console.log("Create room:", retVal);
    if (retVal == "Success") {
      var name = $("#roomName").val();
      var $select = $(".selected_options");
      $select.append('<p>' + name + '</p>')
      $("#roomName").val('');
    } 
    else {
      alert("Create room failed!");
    }
  }
  
  $(".create_room").on('click', function(e){
    var vkey = $("#key").val() || $("input[name='key']").val();
    var name = $("#roomName").val();
    if(!vkey || !name){
      return true;
    }
    agoraExt = Agora.Ext({
      vendor_key : vkey
    });
    agoraExt.createMeeting(name, createFunc);
    return false;
  });
  /* 删除选中的房间 */
  $(".delete").on('click', function(e){
    var vkey = $("#key").val() ||$("input[name='key']").val();
    //var name = $(".selected").val();
    if(!vkey){
      alert("please input vendor key, try again!");
      return false;
    }
    if(!name){
      alert("please select a room, try again!");
      return false;
    }
    agoraExt = Agora.Ext({
      vendor_key : vkey
    });
    agoraExt.endMeeting(name, deleteFunc);
  
  });
  /* 进入设置页面 */
  $(".enter").on('click', function(e){
    var vkey = $("#key").val() ||$("input[name='key']").val();
    //var name = $(".selected").val();
    if(!vkey){
      alert("please input vendor key, try again!");
      return false;
    }
    if(!name){
      alert("please select a room, try again!");
      return false;
    }
	$("#name").val(name);
    //window.location.href="Set_meeting.html?key=" + vkey + "&name=" + name; 
	return true;
  });
  /* 显示已有房间 */
  $(".selected").on('click', function(e){
      e.stopPropagation();
      $(".selected_options").toggle()
  });
  /* 选择房间 */
  $(".selected_options").on('click', function(e){
     //e.stopPropagation();
     name = $(e.target).html();
     $(".selected label").html(name);
  });
  /* 选择角色 */
  $(".role").on('click', function(e){
    $(".role img").attr('src', 'images/checkbox.png');
    $(e.currentTarget).find("img").attr('src', 'images/checkbox_selected.png');
    role = $(e.currentTarget).hasClass("host")? 'host': 'attendee';
    console.log('Select role:', role);
  });
  /* 选择布局 */
  $("input[name='username']").on('click', function(e){
    e.stopPropagation();
    return true;
  });
  $(".layout").on('click', function(e){
    var $e = $(e.currentTarget);
    $(".layout img").attr('src', 'images/checkbox.png');
    $(e.currentTarget).find("img").attr('src', 'images/checkbox_selected.png');
    layout = $e.data("layout");
    console.log("Select layout:", layout);
  });
  /* 进入会议室 */
  $(".begin_meeting").on('click', function(e){
    if(!$("#username").val()){
      alert('You must specify a name for the attendee who will be joining the meeting');
      return false;
    }
    username = $("#username").val();
    start = true;
    $(".Set_cancel img").trigger("click");

    $("#menu_content label.color").html(username);
    display();
    window.initAgoraRTC(role == "host");

  });
  $(".back").on('click', function(e){
    window.history.back();
  });
  /* 显示白板 */
  function display(){
    agoraExt = AgoraExt.Ext({
                 vendor_key : key
               });
    $("#win").attr('src', agoraExt.joinMeetingURL(name, username, role, layout));
  }
  /* 设置 */
  $(".select_img").on('click', function(e){
    e.stopPropagation();
    $(".slide").show();
  });
  $("body").on('click', function(e){
    $(".slide").hide();
    $(".selected_options").hide();
  });

  $(".exit").on('click', function(e){
    window.location.href = "/fullset";
  });
  $(".setting").on('click', function(e){
    var href = "/ext/Set_meeting.html?"
    href += "key=" + key + "&";
    href += 'username=' + username + "&";
    href += 'role=' + role + '&';
    href += 'name=' + name + '&';
    href += 'layout=' + layout + '&';
    href += 'setting=true';
    window.location.href = href;
  });
 $(".Set_cancel").click(function(){
   if(start){
    return false;
   }
    window.history.back();
  });
  function setting(){
    //$(".banner_selected_option p").trigger("click");
	  $(".banner_selected_option,.banner_selected_option_img").hide();
	  $(".Set").show();
  }
  /* 左侧显示已存在房间 */
  function queryMeetingLeft(){
  
    agoraExt = agoraExt || AgoraExt.Ext({
      vendor_key : key
    });
    agoraExt.queryMeeting(function(retVal){
      console.log("QUery room:", retVal);
      if (retVal.length != 0) {
        var $select = $("#menu_content ul");
        for (var i in retVal) {
          var $li = '<li data-name="' + retVal[i] + '"><img src="images/voice_index_six.png" />';
          $li += '<label>' + retVal[i] + '</label><span class="color">';
          if(retVal[i] === name){
            $li += '(会议中)';
          }
          $li += "</span></li>"
          $select.append($li);
        }
        $select.find("li").on('click', function(e){
          name = $(e.currentTarget).data("name");
          if(!name){
            //$("#menu_content").slideUp();
            return ;
          }
          $select.find("li span").html('');
          $(e.currentTarget).find(".color").html('(会议中)');
          if( username && name && key && role){
            display();
          }
        });
      } else {
        alert("Query room failed!");
      }
    });
  }


  //var AgoraExt = AgoraExt || Agora;
  var args = window.location.href.split("?");
  var key = '';
  var members = 0;
  var agoraExt = null;
  var role = 'host', layout = "default";
  var username = '', name = '';
  var start = false;
  if(args.length > 1){
    args = args[1].split("&");
    var data = {};
    for(var i = 0; i < args.length; i ++){
      var temp = args[i].split("=");
      data[temp[0]] = temp[1];
    }
    key = data["key"];
    name = decodeURI(data["name"] || name);
    role = data["role"] || role;
    layout = data["layout"] || layout;
    username = decodeURI(data['username'] || username);
    $("#username").val(username);
    queryMeetingLeft();
    if(data["display"] == 'true'){
      display();
    }
    if(data["setting"] == 'true'){
      setting();
    }
  }
  console.log(key, name);
  $(".choose p label").html(name);
  /* 首次进入查询已存在会议室 */
  agoraExt = AgoraExt.Ext({
          vendor_key : $("input[name='key']").val()
        });
  agoraExt.queryMeeting(queryFunc);
});
