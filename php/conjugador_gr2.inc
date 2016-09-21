<?php

require_once('conjugador_lib.inc');

function conjugador_getTempsGroup2($model){
  $arr = array();

  if ($model == '230'){
    $arr['00_IndPres|Present']                 =  "i,es,,èm,sètz,on";
    $arr['01_IndImp|Imperfach']                =  "iái,iás,iá,iam,iatz,ián";
    $arr['02_IndPret|Preterit']                =  "iguèri,iguères,iguèt,iguèrem,iguèretz,iguèron";
    $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
    $arr['04_Infinitiu|Infinitiu']             =  "ir";
    $arr['05_Gerondiu|Gerondiu']               =  "issent";
    $arr['06_PartPassat|Participi passat']     =  "it,ida";
    $arr['07_Imperatiu|Imperatiu']             =  ",am,etz,iscas,iscam,iscatz";
    $arr['08_SubPres|Subjontiu present']       =  "a,as,a,am,atz,an";
    $arr['09_SubImp|Subjontiu imperfach']      =  "iguèsse,iguèsses,iguèsse,iguèssem,iguèssetz,iguèsson";
    $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";
  return $arr;
  }
  if ($model == '210' || $model == '211' || $model == '212' || $model == '213'){
    $arr['00_IndPres|Present']                 =  "ïssi,ïsses,ís,ïssèm,ïssètz,ïsson";
    $arr['01_IndImp|Imperfach']                =  "ïssiái,ïssiás,ïssiá,ïssiam,ïssiatz,ïssián";
    $arr['02_IndPret|Preterit']                =  "ïguèri,ïguères,ïguèt,ïguèrem,ïguèretz,ïguèron";
    $arr['03_IndFutur|Futur']                  =  "ïrai,ïràs,ïrà,ïrem,ïretz,ïràn";
    $arr['04_Infinitiu|Infinitiu']             =  "ïr";
    $arr['05_Gerondiu|Gerondiu']               =  "ïssent";
    $arr['06_PartPassat|Participi passat']     =  "ït,ida";
    $arr['07_Imperatiu|Imperatiu']             =  "ís,ïscam,ïssetz,ïscas,ïscam,ïscatz";
    $arr['08_SubPres|Subjontiu present']       =  "ïsca,ïscas,ïsca,ïscam,ïscatz,ïscan";
    $arr['09_SubImp|Subjontiu imperfach']      =  "ïguèsse,ïguèsses,ïguèsse,ïguèssem,ïguèssetz,ïguèsson";
    $arr['10_Conditional|Conditional']         =  "ïriái,ïriás,ïriá,ïriam,ïriatz,ïrián";
  return $arr;
  }

  $arr['00_IndPres|Present']                 =  "issi,isses,ís,issèm,issètz,isson";
  $arr['01_IndImp|Imperfach']                =  "issiái,issiás,issiá,issiam,issiatz,issián";
  $arr['02_IndPret|Preterit']                =  "iguèri,iguères,iguèt,iguèrem,iguèretz,iguèron";
  $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
  $arr['04_Infinitiu|Infinitiu']             =  "ir";
  $arr['05_Gerondiu|Gerondiu']               =  "issent";
  $arr['06_PartPassat|Participi passat']     =  "it,ida";
  $arr['07_Imperatiu|Imperatiu']             =  "ís,iscam,issetz,iscas,iscam,iscatz";
  $arr['08_SubPres|Subjontiu present']       =  "isca,iscas,isca,iscam,iscatz,iscan";
  $arr['09_SubImp|Subjontiu imperfach']      =  "iguèsse,iguèsses,iguèsse,iguèssem,iguèssetz,iguèsson";
  $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";
  return $arr;

} //conjugador_getTempsGroup2

function conjugador_conjugateGroup2($verb_infinitiu,$model){

  switch ($model){
    case '210':
    case '211':
    case '212':
    case '213':
      $pattern = '/ï/';
      $replacement = "i";
      $verb_infinitiu = preg_replace($pattern, $replacement, $verb_infinitiu); break;
  }

  $arr = conjugador_getTempsGroup2($model);

  $rootSaved = substr($verb_infinitiu,0,-2);

  $o="<div class=\"conjgroup1\" id=\"$verb_infinitiu.$model\">\n";

  $isModeDisplayed = FALSE;

  // for each temps
  foreach($arr as $lib=>$desinence){
    $arrLib = explode('|', $lib);
    switch($arrLib[0]){
      case "00_IndPres" :     $mode = 'Indicatiu'; $o .= "<div class=\"indicative\"><span class=\"label_mode\">Indicatiu</span><br><br>\n"; break;
      case "04_Infinitiu" :   $mode = 'Fòrmas impersonalas'; $o .= "\n</div>\n<div class=\"impersonal_forms\"><span class=\"label_mode\">Fòrmas impersonalas</span><br><br>\n"; break;
      case "07_Imperatiu" :   $mode = 'Imperatiu'; $o .= "\n</div>\n<div class=\"imperative\"><span class=\"label_mode\">Imperatiu</span><br><br>\n"; break;
      case "08_SubPres" :     $mode = 'Subjontiu'; $o .= "\n</div>\n<div class=\"subjunctive\"><span class=\"label_mode\">Subjontiu</span><br><br>\n"; break;
      case "10_Conditional" : $mode = 'Condicional'; $o .= "\n</div>\n<div class=\"conditional\"><span class=\"label_mode\">Condicional</span><br><br>\n"; break;
    }

    $o .= $arrLib[1] . '<br><br>';

    $isImperative=($arrLib[0] == "07_Imperatiu")?1:0;
    $gerundiveStuff=($arrLib[0] == "05_Gerondiu")?"en ":"";

    $desinences = explode(',', $desinence);
    $i=0;
    $arr = array();

    foreach ($desinences as $elmnt){
      $impStuff = '';
      if ($isImperative && $i < 3 ){
        $impStuff = " !";
      }
      if ($isImperative && $i >= 3 ){
        $impStuff = " pas !";
      }

      $root = conjugador_FixRadical($model,$rootSaved,$elmnt);
      $elmnt = conjugador_FixDesinence($model,$rootSaved,$elmnt);
      $arr[$i++] = $gerundiveStuff . $root . '-' . $elmnt . $impStuff ."</span><br>";

    } // for desinences
    
    // layout as a table

    $o .= "<table class=\"$lib\"><tbody>";
    
    // all cardinalites
    if (count($arr) == 6){
      for($i=0; $i < 3 ; $i++){
        $j = $i + 3;
        $o .= "<tr><td>$arr[$i]</td><td>$arr[$j]</td></tr>\n";
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

  //  $o = conjugador_PhonologicFixes($o);

  switch($model){
    case '220' :
      $pattern = '/br-it<\/span>/i';
      $replacement = '-bèrt</span>';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/br-ida<\/span>/i';
      $replacement = '-bèrta</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
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
} // conjugador_conjugateGroup2

function conjugador_JSONGroup2($verb_infinitiu,$model){

  switch ($model){
    case '210':
    case '211':
    case '212':
    case '213':
      $pattern = '/ï/';
      $replacement = "i";
      $verb_infinitiu = preg_replace($pattern, $replacement, $verb_infinitiu); break;
  }

  $arr = conjugador_getTempsGroup2($model);

  $rootSaved = substr($verb_infinitiu,0,-2);


  $isModeDisplayed = FALSE;
  $arrRet = array();

  // for each temps
  foreach($arr as $lib=>$desinence){
    $arrLib = explode('|', $lib);
    $tempsName = $arrLib[1];

    $isImperative=($arrLib[0] == "07_Imperatiu")?1:0;
    $gerundiveStuff=($arrLib[0] == "05_Gerondiu")?"en ":"";

    $desinences = explode(',', $desinence);
    $i=0;
    $s = "";

    foreach ($desinences as $elmnt){
      $impStuff = '';
      if ($isImperative && $i < 3 ){
        $impStuff = " !";
      }
      if ($isImperative && $i >= 3 ){
        $impStuff = " pas !";
      }

      $root = conjugador_FixRadical($model,$rootSaved,$elmnt);
      $elmnt = conjugador_FixDesinence($model,$rootSaved,$elmnt);
      $s .= $gerundiveStuff . $root . $elmnt . $impStuff ."|";

    } // for desinences

    switch($model){
      case '220' :
        $pattern = '/br-it<\/span>/i';
        $replacement = '-bèrt</span>';
        $s = preg_replace($pattern, $replacement, $s);
        $pattern = '/br-ida<\/span>/i';
        $replacement = '-bèrta</span>';
        $s = preg_replace($pattern, $replacement, $s);
        break;
    }
  
    
    $arrRet[$tempsName] = $s;
  } // foreach temps

  $o .= "</div>";

  //  $o = conjugador_PhonologicFixes($o);

  $a = '';

  foreach ($arrRet as &$a) {
    $a = ascii_to_entities( $a );
  }

  return $arrRet;
} // conjugador_JSONGroup2
