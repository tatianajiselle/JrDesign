 $(document).ready(function() {


var display = function(){

$.get( "/getlog", function(data) {
  $( "#log" ).html(data);
  $("log:contains('normal')").css("color", "white");
});

}
    
window.setInterval(function(){

     display();
  
}, 2000);




});


