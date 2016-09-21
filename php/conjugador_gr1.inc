<?php

require_once('conjugador_lib.inc');

function conjugador_getTempsGroup1(){
  $arr = array();
  $arr['00_IndPres|Present']                 =  "i,as,a,am,atz,an";
  $arr['01_IndImp|Imperfach']                =  "avi,avas,ava,àvem,àvetz,avan";
  $arr['02_IndPret|Preterit']                =  "èri,ères,èt,èrem,èretz,èron";
  $arr['03_IndFutur|Futur']                  =  "arai,aràs,arà,arem,aretz,aràn";
  $arr['04_Infinitiu|Infinitiu']             =  "ar";
  $arr['05_Gerondiu|Gerondiu']               =  "ant";
  $arr['06_PartPassat|Participi passat']     =  "at,ada";
  $arr['07_Imperatiu|Imperatiu']             =  "a,em,atz,es,em,etz";
  $arr['08_SubPres|Subjontiu present']       =  "e,es,e,em,etz,en";
  $arr['09_SubImp|Subjontiu imperfach']      =  "èsse,èsses,èsse,èssem,èssetz,èsson";
  $arr['10_Conditional|Conditional']         =  "ariái,ariás,ariá,ariam,ariatz,arián";
  return $arr;
} //conjugador_getTempsGroup1

function conjugador_conjugateGroup1($verb_infinitiu,$model){
  $arr = conjugador_getTempsGroup1();

  // be careful of trailing number ex : trolhar 1 or trolhar 2
  $patterns = array();
  $patterns[0] = '/ \d+/';
  $replacements = array();
  $replacements[0] = '';
  $verb_infinitiu=  preg_replace($patterns, $replacements, $verb_infinitiu);

  // be careful of pronominal verbs ex : arrogar (s’)

  $patterns = array();
  $patterns[0] = '/ \(s\'\)/';
  $patterns[1] = '/ \(se\)/';
  $replacements = array();
  $replacements[1] = '';
  $replacements[0] = '';
  $verb_infinitiu=  preg_replace($patterns, $replacements, $verb_infinitiu);
  
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

  $o = conjugador_PhonologicFixes($o);

  switch($model){
    case '105 c' :
      $pattern = '/o-i<\/span>/i';
      $replacement = 'o-ï</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '105 d' :
      $pattern = '/i-i<\/span>/i';
      $replacement = 'i-ï</span>';
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
} // conjugador_conjugateGroup1

