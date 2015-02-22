<?php

require_once('conjugador_lib.inc');

define("CALER","caler");

function conjugador_isVowelDetected($root){
  $pattern = '/.+?è.*?/';
  if (preg_match($pattern, $root)){
    return 'è';
  }
  $pattern = '/.+?ò.*?/';
  if (preg_match($pattern, $root)){
    return 'ò';
  }
  $pattern = '/.+?à.*?/';
  if (preg_match($pattern, $root)){
    return 'à';
  }
} // conjugador_isVowelDetected

function conjugador_isTonicDetected($root){
  $pattern = '/.+?é.*?/';
  if (preg_match($pattern, $root)){
    return "é";
  }

  $pattern = '/.+?ó.*?/';
  if (preg_match($pattern, $root)){
    return 'ó';
  }
  $pattern = '/.+?á.*?/';
  if (preg_match($pattern, $root)){
    return 'á';
  }
  $pattern = '/.+?ú.*?/';
  if (preg_match($pattern, $root)){
    return 'ú';
  }

} // conjugador_isTonicDetected

function conjugador_getMixedConjugation($model){
  $arr = conjugador_getStandardConjugation($model);

  $results = db_query("SELECT * FROM {sauzet_model} where nummodel='$model' limit 1");
  $line = $results->fetchObject();
  $label = $line->label_conjugation;
  $conjugations= $line->conjugations;

  $tempses = explode('|', $conjugations);

  // for each conjugation
  $arrTemps = array();

  foreach($tempses as $temps){
    $arrConjugations = explode(':', $temps);
    $index = $arrConjugations[0];
    $conjugationStr = (isset($arrConjugations[1]))?$arrConjugations[1]:"";
 
    if ($conjugationStr){
      $arr[$index]= $conjugationStr; 
    } // if
  } // foreach 

  return $arr;
} // conjugador_getMixedConjugation($model)

function conjugador_getStandardConjugation(){

  $arr = array();
  $arr['00'] =  "i,es,,èm,ètz,on";
  $arr['01'] =  "iái,iás,iá,iam,iatz,ián";
  $arr['02'] =  "èri,ères,èt,èrem,èretz,èron";
  $arr['03'] =  "rai,ràs,rà,rem,retz,ràn";
  $arr['04'] =  "";
  $arr['05'] =  "ent";
  $arr['06'] =  "ut,uda";
  $arr['07'] =  ",am,ètz,as,am,atz";
  $arr['08'] =  "a,as,a,am,atz,an";
  $arr['09'] =  "èsse,èsses,èsse,èssem,èssetz,èsson";
  $arr['10'] =  "riái,riás,riá,riam,riatz,rián";

  return $arr;

} // conjugador_getStandardConjugation


function conjugador_neutralizeVowel($verb_infinitiu,$vowelGrave){
  switch($vowelGrave){
    case 'è' : 
      $pattern = '/(.*?)è(.*?)/'; $replacement = '${1}e${2}';
      return preg_replace($pattern, $replacement, $verb_infinitiu);
    case 'à' :	
      $pattern = '/(.*?)à(.*?)/'; $replacement = '${1}a${2}';
      return preg_replace($pattern, $replacement, $verb_infinitiu);
    case 'ò' :	
      $pattern = '/(.*?)ò(.*?)/'; $replacement = '${1}o${2}';
      return preg_replace($pattern, $replacement, $verb_infinitiu);
  }
  return $verb_infinitiu;
} // neutralizeVowel

function conjugador_neutralizeTonic($verb_infinitiu,$tonic){
  
  switch($tonic){
    case 'é' : 
      $pattern = '/(.*?)é(.*?)/'; $replacement = '${1}e${2}';
      return preg_replace($pattern, $replacement, $verb_infinitiu);
    case 'í' :	
      $pattern = '/(.*?)í(.*?)/'; $replacement = '${1}i${2}';
      return preg_replace($pattern, $replacement, $verb_infinitiu);
    case 'ó' :	
      $pattern = '/(.*?)ó(.*?)/'; $replacement = '${1}o${2}';
      return preg_replace($pattern, $replacement, $verb_infinitiu);
  }
  return $verb_infinitiu;

} // neutralizeTonic

function conjugador_mustNeutralizeVowel($temps,$person){
  $arrtemps = array('00','08');
  $arrperson = array(0,1,2,5);
  $arrpersonImp = array(0,3);
  if ($temps == '07' and in_array($person,$arrpersonImp)){
    return false;
  }
  if (in_array($temps,$arrtemps) and in_array($person,$arrperson)){
    return false;
  }
  return true;
} // mustNeutralizeVowel

/******************************
 ******************************/
function conjugador_conjugateGroup3($verb_infinitiu,$model){


  $vowelGrave = conjugador_isVowelDetected($verb_infinitiu);
  $tonic = conjugador_isTonicDetected($verb_infinitiu);

	
  $arrLabel = array();
  $arrLabel['00']     =  "Present";
  $arrLabel['01']     =  "Imperfach";
  $arrLabel['02']     =  "Preterit";
  $arrLabel['03']     =  "Futur";
  $arrLabel['04']     =  "Infinitiu";
  $arrLabel['05']     =  "Gerondiu";
  $arrLabel['06']     =  "Participi passat";
  $arrLabel['07']     =  "Imperatiu";
  $arrLabel['08']     =  "Subjontiu present";
  $arrLabel['09']     =  "Subjontiu imperfach";
  $arrLabel['10']     =  "Conditional";

  $arr = conjugador_getMixedConjugation($model);

  $patterns = array();
  $patterns[1] = '/er$/';
  $patterns[0] = '/re$/';
  $replacements = array();
  $replacements[1] = '';
  $replacements[0] = '';
  $rootTruncated = preg_replace($patterns, $replacements, $verb_infinitiu);
  
//  $rootTruncated = substr($verb_infinitiu,0,-2);
 
  $rootTruncated = conjugador_neutralizeTonic($rootTruncated,$tonic);


  $o="<div class=\"conjgroup3\" id=\"$verb_infinitiu.$model\">\n";

  $isModeDisplayed = FALSE;

  $isDefective = ($verb_infinitiu === CALER);

  // for each temps
  foreach($arr as $arrLib=>$desinence){
    $i = 0;

    switch($arrLib){
      case '00' :   $mode = 'Indicatiu'; $o .= "<div class=\"indicative\"><span class=\"label_mode\">Indicatiu</span><br><br>\n"; break;
      case '04' :   $mode = 'Fòrmas impersonalas'; $o .= "\n</div>\n<div class=\"impersonal_forms\"><span class=\"label_mode\">Fòrmas impersonalas</span><br><br>\n"; break;
      case '07' :   $mode = 'Imperatiu'; $o .= "\n</div>\n<div class=\"imperative\"><span class=\"label_mode\">Imperatiu</span><br><br>\n"; break;
      case '08' :   $mode = 'Subjontiu'; $o .= "\n</div>\n<div class=\"subjunctive\"><span class=\"label_mode\">Subjontiu</span><br><br>\n"; break;
      case '10' :   $mode = 'Condicional'; $o .= "\n</div>\n<div class=\"conditional\"><span class=\"label_mode\">Condicional</span><br><br>\n"; break;
    } //switch

    $o .= (isset($arrLabel[$arrLib]))?$arrLabel[$arrLib]:"" . '<br><br>';

    $isImperative=($arrLib == "07")?1:0;
    $gerundiveStuff=($arrLib == "05")?"en ":"";

    $isInfinitiu=($arrLib == "04")?1:0;

    $desinences = explode(',', $desinence);

    $arr = array();

    foreach ($desinences as $elmnt){
      $impStuff = '';
      if ($isImperative && $i < 3 ){
        $impStuff = " !";
      }
      if ($isImperative && $i >= 3 ){
        $impStuff = " pas !";
      }

      // if there are commas in the desinence they are interpreted as backspaces
      $rootCommaLess = $rootTruncated;

      if (substr_count($elmnt, '.')){
        $rootCommaLess = substr($rootTruncated, 0, -1*(int)substr_count($elmnt, '.'));
      }
      $elmnt = str_replace ( '.' , '', $elmnt );
      
      if (conjugador_mustNeutralizeVowel($arrLib,$i)){
        $root = conjugador_neutralizeVowel($rootCommaLess,$vowelGrave);
      }else{
        $root = $rootCommaLess;
      }

      if ($isInfinitiu){
        $arr[$i++] = '-' . $verb_infinitiu . "</span><br>";
      }else{
        $arr[$i++] = $gerundiveStuff . $root . '-' . $elmnt . $impStuff ."</span><br>";
      }
    } // for desinences
    
    // layout as a table
    $lib = (isset($arrLabel[$arrLib]))?$arrLabel[$arrLib]:"";
    $o .= "<table class=\"$lib\"><tbody>";
    
    // all cardinalites
    if (count($arr) == 6){
      for($i=0; $i < 3 ; $i++){
        $j = $i + 3;

        if (! $isDefective){
          $o .= "<tr><td>$arr[$i]</td><td>$arr[$j]</td></tr>\n";
        }elseif ($i == 2){
          $o .= "<tr><td>$arr[$i]</td><td></td></tr>\n";
        }else{
            $o .= "<tr><td></td><td></td></tr>\n";
        }
      }
    }

    if (count($arr) == 2){
      $o .= "<tr><td>$arr[0]</td><td>$arr[1]</td></tr>\n";
    }

    if (count($arr) == 1){
      $o .= "<tr><td colspan=2>$arr[0]</td></tr>\n";
    }

    $o .= "</tbody></table>";
    $o .= "<br>";

  } // foreach temps

  $o .= "</div>";

  if ($model != '337'){
    $o = conjugador_PhonologicFixes($o);
  }

  // add carriage return for cosmetic
  $pattern = '/<br>/';
  $replacement = "<br>\n";
  $o = preg_replace($pattern, $replacement, $o);

  // add class for desinence
  $pattern = '/-/';
  $replacement = "<span class=\"des\">";
  $o = preg_replace($pattern, $replacement, $o);
  
  return "$o</div>";
} // conjugador_conjugateGroup3


