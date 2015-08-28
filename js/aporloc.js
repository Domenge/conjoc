/*
function checksyntax(text){

//	regexp = new RegExp(/<glossentry><glossterm>.*?<\/glossterm>(<genregram>.*?<\/genregram>)?<glossdef>((\(.*\))?.*?(<genregram>.*<\/genregram>)?(;)?)+<\/glossdef><\/glossentry>/);

	var regexp0 = /<glossentry><glossterm>.*?<\/glossterm>(<genregram>.*?<\/genregram>)?<glossdef>(.*)<\/glossdef><\/glossentry>/;
//	var regexp1 = /(\(.*\))(?.*)+(<genregram>.*<\/genregram>)?/;
	var coderet = 0;
//	var tab = regexp0.exec(text);

//	var glossdef = tab[2];
	var tabinner:
	var str;

	if (glossdef != ''){

		alert(glossdef);

		var terms = glossdef.split( ";" );
		var term;
		var ret;
		
		for ( var i = 0; i < terms.length; i++ )
		{
			term = terms[ i ];
//			tabinner = regexp1.exec(term);
//			str = tabinner[2];
			alert(term);
		}

	} 

	return coderet;
}
*/
if (Drupal.jsEnabled){
    $(document).ready(function(){
		//event
		$("#copiarbtn").click(
			function(){
					var x=document.getElementById("codebeautified").value;
					// nettoyage par regex
					x = x.replace(/\n+/g,"");
					x = x.replace(/>\s+/g,">");
					x = x.replace(/\s+</g,"<");
					document.getElementById("codetarget").value = x;
					// vérification de la syntaxe
/*					
					var regexp0 = /<glossentry><glossterm>.*?<\/glossterm>(<genregram>.*?<\/genregram>)?<glossdef>(.*)<\/glossdef><\/glossentry>/;
					//	var regexp1 = /(\(.*\))(?.*)+(<genregram>.*<\/genregram>)?/;
					var coderet = 0;
					
					var tab = regexp0.exec(text);

					var glossdef = tab[2];
					var tabinner:
					var str;

					if (glossdef != ''){

						alert(glossdef);

						var terms = glossdef.split( ";" );
						var term;
						var ret;
		
						for ( var i = 0; i < terms.length; i++ )
						{
							term = terms[ i ];
			//				tabinner = regexp1.exec(term);
			//				str = tabinner[2];
							alert(term);
						}

					} // if
*/
					/*
					if (checksyntax(x) == 0){
					    $(".redtrafficlight").hide('slow');
					//    $(".redtrafficlight").value='Ok';
					    $(".corregit").show('slow');
					}
					*/
//						alert("fin1");
					} // function
					 
		); // event
		$("#applybtn").click(
			function(){
			    var x=document.getElementById("basiccodebeautified").value;
			    alert(x);
			    //x = x.replace(/1/g,"X");
			    //document.getElementById("definition_seen").innerHTML = x;
			} // function
					 
		); // event
		
	});
}; // if Js
