function postwith (to,p) {
  var myForm = document.createElement("form");
  myForm.method="post" ;
  myForm.action = to ;
  for (var k in p) {
    var myInput = document.createElement("input") ;
    myInput.setAttribute("name", k) ;
    myInput.setAttribute("value", p[k]);
    myForm.appendChild(myInput) ;
  }
  document.body.appendChild(myForm) ;
  myForm.submit() ;
  document.body.removeChild(myForm) ;
}

function definitionAsSeen(){
    var x=document.getElementById("jros_codebeautified").value;
    var term=document.getElementById("glossterm").value;
    var catgram=document.getElementById("catgram").value;
    var acception=document.getElementById("acception").value;
    var acceptionFmt = "";
    var commonlyFmt  = "";
    var widelyFmt  = "";

    // formatting string
    x = x.replace(/\[(.+)\]/g,"[<span class=\"example-fr\">$1</span>]");
    x = x.replace(/(\[.*?) ?: ?(.+?\])/g,"$1</span> : <span class=\"example-oc\">$2");

    x = x.replace(/(\(.+\))/g,"<span class=\"catgram\">$1</span>");
    x = x.replace(/(\{.+\})/g,"<span class=\"localization\">$1</span>");
    x = x.replace(/\*(.+?)\*/g,"<span class=\"prefix\">($1)</span>");
    // feminines
    var suffix = x.match(/,-(.*?) /);

    if (term != ""){
	termFmt = "<span class=\"term\">" + term + "</span> ";
    } 

    if (catgram != ""){
	catgramFmt = "<span class=\"catgram\">" + catgram + "</span> ";
    } 

    if (acception != ""){
	acceptionFmt = "<span class=\"acception\">(" + acception + ")</span> ";
    } 


    x = termFmt + catgramFmt + acceptionFmt + "<span class=\"auv\">" + x + "</span> ";

    return x;
}

if (Drupal.jsEnabled){
    $(document).ready(function(){

	//event
	$("#applybtn").click(
	    function(){
		$("#definition_seen").html(definitionAsSeen());
	    } // function   
	); // event
	$("#submit").click(
	    function(){
		var x = $("#jros_codebeautified").val();
		x = x.replace(/[\n\t]/g,"");
		$("#codeToSave").val(x);
	    } // func
	); // event

	$(".acception_tab").click(function (){
	    var currentId = $(this).attr('id');
	    alert("acception_tab : " + currentId);
	});

	$("#jros_codebeautified").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#jros_codebeautified").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

	$("#acception").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#acception").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

    });
}; // if Js
