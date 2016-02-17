$(document).ready(function(){

  /* 删除选中的房间 */
  function deleteFunc(retVal) {
      if (retVal == "Success") {
          $(".selected_option p").each(function(index, e){
             if(e.innerHTML == name){
                e.remove();
             }
          });
          name = '';
          $(".selected_content label").html("查询会议室");
      } 
      else {
        alert("Destroy room failed!");
      }
  }
  /* 查询已有会议室 */
  function queryFunc(retVal) {
    console.log("Query room:", retVal);
    if (retVal.length != 0) {
      var $select = $(".selected_option");
      $select.html("");
      for (var i in retVal) {
        $select.append('<p>' + retVal[i] + '</p>')
      }
    } else {
      //alert("Query room failed!");
      return false;
    }
  }

  $("#vendorkey").on('change', function(e){
    var vkey = $("#vendorkey");
    agoraExt = Agora.Ext({
            vendor_key : $("#vendorkey").val()
          });
    agoraExt.queryMeeting(queryFunc);
  });
  /* 创建新会议室 */
  function createFunc(retVal) {
    console.log("Create room:", retVal);
    if (retVal == "Success") {
      var name = $("#roomName").val();
      var $select = $(".selected_option");
      $select.append('<p>' + name + '</p>')
      $("#roomName").val('');
    } 
    else {
      alert("Create room failed!");
    }
  }
  
  $(".build_room").on('click', function(e){
    var vkey = $("#vendorkey").val();
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
  /* 进入设置页面 */
  $(".into").on('click', function(e){
    var vkey = $("#vendorkey").val();
    //var name = $(".selected").val();
    if(!vkey){
      alert("please input vendor key, try again!");
      return false;
    }
    if(!name){
      alert("please select a room, try again!");
      return false;
    }
    window.location.href="Set_meeting.html?key=" + vkey + "&name=" + name; 
  });
  /* 删除选中的房间 */
  $(".delete").on('click', function(e){
    var vkey = $("#vendorkey").val();
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

  /* 显示已有房间 */
  $(".selected_content").on('click', function(e){
      e.stopPropagation();
      var $e = $(".selected_option");
      $e.is(":hidden")? $e.show(): $e.hide();
  });
  /* 选择房间 */
  $(".selected_option").on('click', function(e){
     //e.stopPropagation();
     name = $(e.target).html();
     $(".selected_content label").html(name);
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
    var href = "start.html?"
    href += "key=" + key + "&";
    href += 'username=' + $("#username").val() + "&";
    href += 'role=' + role + '&';
    href += 'name=' + name + '&';
    href += 'layout=' + layout + '&';
    href += 'display=true';
    window.location.href = href;

  });
  $(".back").on('click', function(e){
    window.history.back();
  });
  /* 显示白板 */
  function display(){
    agoraExt = Agora.Ext({
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
    $(".selected_option").hide();
  });

  $(".exit").on('click', function(e){
    window.location.href = "/ext";
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
  function setting(){
    $(".choose p label").html(name);
    role == "host"? $(".host").trigger("click"): $(".participants").trigger("click");
    $("div[data-layout='" + layout + "']").trigger("click");
    $("#username").val(username);
  }

  var args = window.location.href.split("?");
  var key = '';
  var members = 0;
  var agoraExt = null;
  var role = 'host', layout = "default";
  var username = '', name = '';
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
  agoraExt = Agora.Ext({
          vendor_key : $("#vendorkey").val()
        });
  agoraExt.queryMeeting(queryFunc);
});
