<?php

function _nl($msg){
	 return "$msg\n";
}

function conjugador_PhonologicFixes($string){
  // Corrections

  // g to gu
  $patterns = array();
  $patterns[0] = '/g-i/';
  $patterns[1] = '/g-e/';
  $patterns[2] = '/g-è/';
  if (preg_match($patterns[0], $string) || 
     preg_match($patterns[1], $string) ||
     preg_match($patterns[2], $string)
  ){
     $replacements = array();
     $replacements[2] = 'gu-i';
     $replacements[1] = 'gu-e';
     $replacements[0] = 'gu-è';
     return preg_replace($patterns, $replacements, $string);
  }
  // j to g
  $patterns = array();
  $patterns[0] = '/j-i/';
  $patterns[1] = '/j-e/';
  $patterns[2] = '/j-è/';
  if (preg_match($patterns[0], $string) || 
     preg_match($patterns[1], $string) ||
     preg_match($patterns[2], $string)
  ){
     $replacements = array();
     $replacements[2] = 'g-i';
     $replacements[1] = 'g-e';
     $replacements[0] = 'g-è';
     return preg_replace($patterns, $replacements, $string);
  }

  // c to qu
  $patterns = array();
  $patterns[0] = '/c-i/';
  $patterns[1] = '/c-e/';
  $patterns[2] = '/c-è/';

  if (preg_match($patterns[0], $string) || 
     preg_match($patterns[1], $string) ||
     preg_match($patterns[2], $string)
  ){

     $replacements = array();
     $replacements[2] = 'qu-i';
     $replacements[1] = 'qu-e';
     $replacements[0] = 'qu-è';
     return preg_replace($patterns, $replacements, $string);
  }

  // ç to c
  $patterns = array();
  $patterns[0] = '/ç\-i/';
  $patterns[1] = '/ç\-e/';
  $patterns[2] = '/ç\-è/';

  if (preg_match($patterns[0], $string) || 
     preg_match($patterns[1], $string) ||
     preg_match($patterns[2], $string)
  ){
     $replacements = array();
     $replacements[2] = 'c-i';
     $replacements[1] = 'c-e';
     $replacements[0] = 'c-è';
     return preg_replace($patterns, $replacements, $string);
  }
  return $string;
}

function conjugador_FixDesinence($model,$root,$elmnt){

  $desinences = array('i','as','a','an','e','es','en');

  if(in_array($elmnt,$desinences)){
    switch ($model){
      case '107 a' :   // Attention dar,  di becomes dau
        $elmnt = ($elmnt=='i' ? 'au':$elmnt); break;
      case '107 b' :   // Attention estar,  estid becomes estau
        $elmnt = ($elmnt=='i' ? 'au':$elmnt);
        $elmnt = ($elmnt=='as' ? 'às':$elmnt);
        $elmnt = ($elmnt=='a' ? 'à':$elmnt);
        $elmnt = ($elmnt=='an' ? 'àn':$elmnt);
    }
  }        

  return $elmnt;
} // conjugador_FixDesinence

function conjugador_FixRadical($model,$root,$elmnt){
  $desinences = array('i','as','a','an','e','es','en');
  if(in_array($elmnt,$desinences)){
    switch ($model){
      case '106 a' : $pattern = '/(.*)a(.+?)$/'; $replacement = '${1}à${2}'; break;
      case '106 b' : $pattern = '/(.*)e(.+?)$/'; $replacement = '${1}é${2}'; break;
      case '106 c' : $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ó${2}'; break;
      case '106 d' : $pattern = '/(.*)i(.+?)$/'; $replacement = '${1}í${2}'; break;
      case '106 e' : $pattern = '/(.*+)u(.+?)$/'; $replacement = '${1}ú${2}'; break;
      case '107 b' : 
        if (in_array($elmnt,array('e','es','en'))){
          $pattern = '/(.*)e(.+?)$/'; $replacement = '${1}è${2}';}
        else{
          $pattern = '//'; $replacement = '';}
        break;
      case '110'   :
      case '111'   :
      case '112'   :
      case '113'   :
      case '114'   :
      case '115'   :
      case '116 a' :
        $pattern = '/(.*)e(.+?)$/'; $replacement = '${1}è${2}'; break;
      case '120'   :
      case '121'   :
      case '122'   :
      case '123'   :
      case '124'   :
      case '125'   :
      case '126 a' :
      case '126 b' :
      case '150'   :
      case '154'   :
        $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
      case '156'   :
        $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
      case '130'   :
      case '133'   :
        $pattern = '/(.*)e(.+)$/'; $replacement = '${1}iè${2}'; break;
      case '140'   :
      case '143'   :
        $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}uè${2}'; break;
      case '160'   :
        $pattern = '/(.*)u(.+?)$/'; $replacement = '${1}uo${2}'; break;
      case '170'   :
      case '173'   :
        $pattern = '/(.*)u(.+?)$/'; $replacement = '${1}uè${2}'; break;
      default :
        return $root;
    }
    return preg_replace($pattern, $replacement, $root);
  }
  return $root;
} // conjugador_FixRadical
