 $(document).ready(function() {


var display = function(){

$.get( "/getlog", function(data) {
  $( "#log" ).html(data);
l
});

}
    
window.setInterval(function(){

     display();
  
}, 2000);




});


