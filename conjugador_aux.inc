<?php

require_once('conjugador_lib.inc');

function conjugador_getTempsLabels(){
  $arr = array();
  $arr[]  =  "Present";
  $arr[]  =  "Imperfach";
  $arr[]  =  "Preterit";
  $arr[]  =  "Futur";
  $arr[]  =  "Infinitiu";
  $arr[]  =  "Gerondiu";
  $arr[]  =  "Participi passat";
  $arr[]  =  "Imperatiu";
  $arr[]  =  "Subjonctiu present";
  $arr[]  =  "Subjonctiu imperfach";
  $arr[]  =  "Conditional";
  return $arr;
} //conjugador_getTempsLabels

function conjugador_conjugateAuxillars($verb,$model){

  $arrTempsLabels  = conjugador_getTempsLabels();
  $o="\n<div class=\"conjAuxillars\" id=\"$verb.$model\">\n";

  $results = db_query("SELECT * FROM {sauzet_model} where nummodel='$model'");
  $line = $results->fetchObject();
  $label = $line->label_conjugation;
  $conjugations= $line->conjugations;

  // treatment of verb «FAR»
  if ($model == '004'){
    //SELECT verb, substr( verb, 1, position( 'far' IN verb ) -1 ) FROM `sauzet_verbsmodel` WHERE nummodel = '004'
    $resultsFAR = db_query("SELECT substr( verb, 1, position( 'far' IN verb ) -1 ) as verbtrimmed FROM {sauzet_verbmodel} where verb='$verb'");
    $lineFAR = db_fetch_object($resultsFAR);
    $rootVerb = $lineFAR->verbtrimmed;
  } //far

  $tempses = explode('|', $conjugations);

  // for each conjugation
  $arrTemps = array();

  foreach($tempses as $temps){
    $arrConjugations = explode(':', $temps);
    $index = (int)$arrConjugations[0];
    //    drupal_set_message("[" . $arrTempsLabels[$index] ."]");

    switch($index){
      case 0 : $o .= "<div class=\"indicative\">\n"; break;
      case 4 : $o .= "\n</div>\n<div class=\"impersonal_forms\">\n"; break;
      case 7 : $o .= "\n</div>\n<div class=\"imperative\">\n"; break;
      case 8 : $o .= "\n</div>\n<div class=\"subjunctive\">\n"; break;
      case 10 : $o .= "\n</div>\n<div class=\"conditional\">\n"; break;
    }

    $isImperative=($index == 7)?1:0;
    $gerundiveStuff=($index == 5)?"en ":"";

    $conjugations = explode(',',$arrConjugations[1]);

    $arr = array();
    $i=0;

    foreach($conjugations as $elmnt){
      $impStuff = '';
      if ($isImperative && $i < 3 ){
        $impStuff = " !";
      }
      if ($isImperative && $i >= 3 ){
        $impStuff = " pas !";
      }

      $arr[$i++] = '<span class="des">'. $gerundiveStuff . $elmnt . $impStuff ."</span><br>";
      
    }
    $o .= $arrTempsLabels[$index] . '<br><br>';

    // layout as a table
    $lib ="auxillars";
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

  return "$o</div>";
} // conjugador_conjugateAuxillars

