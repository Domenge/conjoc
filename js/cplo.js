function mafonction(){
    alert("Ma fonction");
}

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
    var x=document.getElementById("basic_codebeautified").value;
    var commonly=document.getElementById("common").value;
    var widely=document.getElementById("widely").value;
    var term=document.getElementById("glossterm").value;
    var catgram=document.getElementById("catgram").value;
    var acception=document.getElementById("acception").value;
    var common_lg=document.getElementById("common_lg").value;
    var acceptionFmt = "";
    var commonlyFmt  = "";
    var commonly_lgFmt  = "";
    var catgramFmt  = "";
    var termFmt  = "";
    var widelyFmt  = "";

    // formatting string
    x = x.replace(/\[(.+)\]/g,"[<span class=\"example-fr\">$1</span>]");
    x = x.replace(/(\[.*?) ?: ?(.+?\])/g,"$1</span> : <span class=\"example-oc\">$2");

    x = x.replace(/<leng>(.+)<\/leng>/,"<div class=\"leng\">[leng] $1</div>");
    x = x.replace(/<gasc>(.+)<\/gasc>/,"<div class=\"gasc\">[gasc] $1</div>");
    x = x.replace(/<prvc>(.+)<\/prvc>/,"<div class=\"prvc\">[prvc] $1</div>");
    x = x.replace(/<auv>(.+)<\/auv>/,"<div class=\"auv\">[auv] $1</div>");
    x = x.replace(/<lim>(.+)<\/lim>/,"<div class=\"lim\">[lim] $1</div>");
    x = x.replace(/<valp>(.+)<\/valp>/,"<div class=\"valp\">[valp] $1</div>");
    x = x.replace(/(\(.+\))/g,"<span class=\"catgram\">$1</span>");
    x = x.replace(/(\{.+\})/g,"<span class=\"localization\">$1</span>");
    x = x.replace(/\*(.+?)\*/g,"<span class=\"prefix\">($1)</span>");
    // feminines
    var suffix = x.match(/,-(.*?) /);

    if (term != ""){
	termFmt = "<span class=\"term\">" + term + "</span>"
    } 

    if (catgram != ""){
	catgramFmt = "<span class=\"term\">" + catgram + "</span>"
    } 

    if (acception != ""){
	acceptionFmt = "<span class=\"acception\">(" + acception + ")</span>"
    } 

    if (commonly != ""){
	commonlyFmt = "<span class=\"common\">" + commonly + "</span>"
    } 

    if (widely != ""){
	widelyFmt = "<span class=\"widely_used\">" + widely + "</span> "
    } 

    if (common_lg != ""){
	common_lgFmt = "<span class=\"common_lg\">" + common_lg + "</span> "
    } 

    x = termFmt + " " + catgramFmt + " "+ acceptionFmt + " " + commonlyFmt + " " + widelyFmt + " " + common_lgFmt + " " + x;

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
		var x = $("#basic_codebeautified").val();
		x = x.replace(/[\n\t]/g,"");
		$("#codeToSave").val(x);
	    } // func
	); // event

	$(".acception_tab").click(function (){
	    var currentId = $(this).attr('id');
	    alert("acception_tab : " + currentId);
	});

	$("#basic_codebeautified").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#basic_codebeautified").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

	$("#acception").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#acception").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

	$("#common").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

	$("#common").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#widely").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#widely").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

	$("#common_lg").keyup(function () {
	    $("#definition_seen").html(definitionAsSeen());
	}).keyup();

	$("#common_lg").change(function () {
	    $("#definition_seen").html(definitionAsSeen());
	});

    });
}; // if Js
