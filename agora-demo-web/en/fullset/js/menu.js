$(document).ready(function(){
   /*js菜单框按钮选项开始*/
   //var oMenu=document.getElementById("menu_content");
	//var oBtnMenu=document.getElementById("banner_menu");
		//oBtnMenu.onclick=function(){
		//if(oMenu.offsetLeft==0)
//{
			//oMenu.style.left="-250px";
			//}else{
				//oMenu.style.left="0";
				//}
		//}
    $("#slideMenu").on('click', function(e){
      $(".menu_content").slideUp();
    });
    $("#banner_menu").on('click', function(e){
      $(".menu_content").toggle();
    });

   /*js菜单框按钮选项结束*/
   
  /*Expand按钮开始*/
   $(".display").click(function(){
	   $(this).fadeOut();
	   $(".display_select").slideDown(1000); 
	});
  $(".display_close").click(function(){
	  $(".display_select").slideUp(1000);
	  $(".display").slideDown(1800);
	});
  /*暂开按钮结束*/
  
  /*banner 设置按钮开始*/
  $(".banner_selected_option p").click(function(){
	  $(".banner_selected_option,.banner_selected_option_img").hide();
	  $(".Set").show();
    $(".Set_cancel").show();
	});
 $(".Set_cancel").click(function(){
	 $(".Set").hide();
	 })
  /*banner 设置按钮结束*/
   /*banner 按钮开始*/
  
     $(".banner_people,.banner_selected").click(function(){
      $(".banner_selected_option_img,.banner_selected_option,.voice_banner_selected_option").toggle();
	    
	  });
	 
   /*banner 按钮结束*/
   
   /*banner设置按钮开始*/
   $(".banner_selected_option p").click(function(){
	   $(".banner_selected_option,.banner_selected_option_img").hide();
	   $(".Set").show();
})
   $(".Set_cancel").click(function(){
	   $(".Set").hide();
	   })
/*banner 设置按钮结束*/
});

