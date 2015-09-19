<?php

require_once(drupal_get_path('module', 'conjoc').'/conjugador_lib.inc');

class ConverterHTML implements IConverter{

  public function __construct(){
  } // __construct

  protected function getTempses(){
    $arr = array();
    $arr[] = "Present";
    $arr[] = "Imperfach";
    $arr[] = "Preterit";
    $arr[] = "Futur";
    $arr[] = "Infinitiu";
    $arr[] = "Gerondiu";
    $arr[] = "Participi passat";
    $arr[] = "Present positiu/present negatiu";
    $arr[] = "Subjontiu present";
    $arr[] = "Subjontiu imperfach";
    $arr[] = "Condicional";

    return $arr;
  }

  public function convertConjugation(array $conjugated){

    $tempses = $this->getTempses();
    $conjugations = $conjugated["conjugations"];
    $out = "";
    $ModesArray = array();
    
    // for each temps
    for ($i=ConjugationBase::IND_PRESENT;$i < ConjugationBase::CONDITIONAL +1 ;$i++){
      $conjugation = $conjugations[$i];

      switch($i){
        case ConjugationBase::IND_PRESENT : $mode = 'Indicatiu'; $ModesArray['Indicatiu']= array(); $o = "<div class=\"indicative\"><span class=\"label_mode\">Indicatiu</span><br>\n"; break;
        case ConjugationBase::INFINITIVE  : $mode = 'Formas impersonalas'; $ModesArray['Formas impersonalas']= array(); $o = "\n</div><br>\n<div class=\"impersonal_forms\"><span class=\"label_mode\">Formas impersonalas</span><br>\n"; break;
        case ConjugationBase::IMPERATIVE  : $mode = 'Imperatiu'; $ModesArray['Imperatiu']= array(); $o = "\n</div><br>\n<div class=\"imperative\"><span class=\"label_mode\">Imperatiu</span><br>\n"; break;
        case ConjugationBase::SUBJ_PRESENT: $mode = 'Subjontiu'; $ModesArray['Subjontiu']= array(); $o = "\n</div><br>\n<div class=\"subjunctive\"><span class=\"label_mode\">Subjontiu</span><br>\n"; break;
        case ConjugationBase::CONDITIONAL : $mode = 'Conditional'; $ModesArray['Conditional']= array(); $o = "\n</div><br>\n<div class=\"conditional\"><span class=\"label_mode\">Condicional</span><br>\n"; break;
      }

      
      // big dispatch
      // Each temps is dispatched in its own mode        
      switch($mode){
      	case "Indicatiu" :
      		$ModesArray['Indicatiu'][] = $conjugation; 
      		break; 
      	case "Formas impersonalas" :
      		$ModesArray['Formas impersonalas'][] = $conjugation; 
      		break; 
      	case "Imperatiu" :
      		$ModesArray['Imperatiu'][] = $conjugation; 
      		break; 
      	case "Subjontiu" :
      		$ModesArray['Subjontiu'][] = $conjugation; 
      		break; 
      	case "Conditional" :
      		$ModesArray['Conditional'][] = $conjugation; 
      		break; 
      } // switch
    } // for

    $o = "";
    
    drupal_add_css(drupal_get_path('module', 'conjoc') . '/css/conjugador.css');
    
    // SEE ALSO
    $see = $conjugated["see_also"];
    $libmodel = $conjugated["libmodel"];
    $model = $conjugated["model"];
    $dialect = $conjugated["dialect"];
    
    $o .= '<div class="verb">';
    if ($see){
      $o .= t("remandament") . ' <span class="see_also">' . l("$see", "$dialect/verb_autocomplete/better_see/$see") . "</span><br><br>";
    }else{
      $o .= "<span class=\"label_verb\">$model</span> <span class=\"label_verb\">$libmodel</span>";
    }

    $o .= '</div>';
    
    $o .= $this->formatConjugation($ModesArray);
    return $o; 
  } // convertConjugation
  
  private function formatConjugation($ConjugationArray){
  /*
    HTML and CSS code
  */ 
    $out = '';
    
    // INDICATIVE
    $ary = $ConjugationArray['Indicatiu'];
    $persons = $this->getPersonsArray();
    $tempses = array("present","imperfach","preterit","futur");
    $out .= '<div class="indicative"><table><tbody>';
    $out .= "<tr><th colspan='5'>Indicatiu</th></tr>";
    $j = 0;
    $present   = $ary[0];
    $imperfect = $ary[1];
    $preterit  = $ary[2];
    $future    = $ary[3];
      
    $out .= "<tr><th></th><th>Present</th><th>Imperfach</th><th>Preterit</th><th>Futur</th></tr>";
	
    for($i=0;$i<6;$i++){
      $out .= "<tr><td><i>$persons[$i]</i></td><td>$present[$i]</td><td>$imperfect[$i]</td><td>$preterit[$i]</td><td>$future[$i]</td></tr>";
    }

    $out .= "</tbody></table></div>";
   
    // IMPERSONAL FORMS
    $ary = $ConjugationArray['Formas impersonalas'];   
    $out .= '<div class="impersonal_forms"><table><tbody>';
    $out .= "<tr><th>Formas impersonalas</th></tr><tr>";
    
    $out .= "<table><tbody>";
    $out .= '<tr><th>Infinitiu</th></tr>';
    $infinitive = $ary[0];
    $out .= "<tr><td>$infinitive[0]</td></tr>";
    $out .= "</tbody></table>";

    $out .= "<table><tbody>";
    $out .= '<tr><th>Participi passat</th></tr>';
    $past_particle = $ary[2];
    $out .= "<tr><td>$past_particle[0]</td></tr>";
    $out .= "</tbody></table>";

    $out .= "<table><tbody>";
    $out .= '<tr><th>Gerondiu</th></tr>';
    $gerund = $ary[1];
    $out .= "<tr><td>en $gerund[0]</td></tr>";
    $out .= "</tbody></table>";

    $out .= "</tbody></table></div>";
  
    // IMPERATIVE
    $ary = $ConjugationArray['Imperatiu'];   
    $out .= '<div class="imperative"><table><tbody>';
    $out .= "<tr><th colspan='2'>Imperatiu</th></tr><tr>";
    
    $out .= '<tr><th>forma positiva</th><th>forma negativa</th></tr>';
    $imperative = $ary[0];
    
    for($j=0;$j<3;$j++){
      $p = $j + 3;
      $out .= "<tr><td>$imperative[$j] !</td><td>$imperative[$p] pas !</td></tr>";
    }
    
    $out .= "</tbody></table></div>";
    
    // SUBJUNCTIVE
    $ary = $ConjugationArray['Subjontiu'];   
    $out .= '<div class="subjunctive"><table><tbody>';
    $out .= "<tr><th colspan='3'>Subjontiu</th></tr><tr>";    
    $out .= '<tr><th></th><th>Present</th><th>Passat</th></tr>';
    $subjunctive_present = $ary[0];
    $subjunctive_past    = $ary[1];
    
    for($j=0;$j<6;$j++){
      $out .= "<tr><td><i>$persons[$j]</i></td><td>$subjunctive_present[$j]</td><td>$subjunctive_past[$j]</td></tr>";
    }
    
    $out .= "</tbody></table></div>";


    // CONDITIONAL
    $ary = $ConjugationArray['Conditional'];   
    $out .= '<div class="conditional"><table><tbody>';
    $out .= "<tr><th  colspan='23'>Conditional</th></tr><tr>";    
    $out .= '<tr><th></th><th>Present</th></tr>';
    $conditional = $ary[0];
    
    for($j=0;$j<6;$j++){
      $out .= "<tr><td><i>$persons[$j]</i></td><td>$conditional[$j]</td></tr>";
    }
    
    $out .= "</tbody></table></div>";
    
    return $out;  
  } // formatConjugation

  private function getPersonsArray(){
    $ary = array();
    $ary[] = 's1'; 
    $ary[] = 's2'; 
    $ary[] = 's3'; 
    $ary[] = 'p1'; 
    $ary[] = 'p2'; 
    $ary[] = 'p3';
     
    return $ary;
  }
  
  public function convertArray(array $list){
    $o = "";
    if (count($list) > 0){
      $o = "<table style=\"width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">";
      $o .= "<tbody>";

      $cptr = 0;

      foreach($list as $key => $value){

        if (!$cptr % 5){
      	   $o .= '<tr align=\"center\">' . l("$key", "$value");
      	}
      	$o .= "<td>" . l("$key","$value");

      	if ($cptr % 5 == 4){
           $o .= _nl("</tr>");
      	}
      	$cptr++;
      } // for
  
      $o .= _nl("</tbody>");
      $o .= _nl("</table>");
    } // if
    return $o;
  } // convertArray

  public function convertSelect(array $conjugation){
  
  }

  public function convertIndexedData($data){
    if(empty($data)){
      drupal_set_message(t("Conjugation not found"), 'error');
      return "";
    }
    $converter = new ConverterIndexation();
    $arrPos = $converter->decodePOS($data->pos);
	
    // apply the style
    drupal_add_css(drupal_get_path('module', 'conjoc') . '/css/conjugador.css');
    $o = '<div class="indexedData">';
    $o .='<table><tbody>';
    $o .='<tr><td>conjugation</td><td><span class="indexed_conjugation">' . $data->conjugation . '</span></td></tr>';
    $o .='<tr><td>infinitive</td><td><span class="indexed_verb">' . $data->verb . '</span></td></tr>';
    $o .='<tr><td>index</td><td><span class="indexed_row">' . $data->row . '</span></td></tr>';
    $dialect = $converter->decodeDialect($data->dialect);
    $o .='<tr><td>dialect</td><td><span class="indexed_dialect">' . $dialect . '</span></td></tr>';
    $o .='<tr><td>model</td><td><span class="indexed_nummodel">' . $data->nummodel . '</span></td></tr>';
    $o .='<tr rowspan="2"><td>EAGLES POS</td><td><span class="indexed_POS">' . $data->pos . '</span></td></tr>';
    $o .= '<tr><td>EAGLES POS decoded</td><td>' . $this->convertPOS($arrPos). '</td></tr>'; 
    $o .= '</tbody></table>';
    $o .= '</div>';
    return $o;
  }  // convertIndexedData

  private function convertPOS(array $aPos){
   $type = $aPos['type'];   	  
   $person = $aPos['person'];
   $gender = $aPos['gender'];
   $number = $aPos['number'];
   $finiteness = $aPos['finiteness'];
   $tense = $aPos['tense'];
   $voice = $aPos['voice'];
   $aspect = $aPos['aspect'];
   $separability = $aPos['separability'];
   $reflexivity = $aPos['reflexivity'];
   $auxiliary = $aPos['auxiliary'];
   $mood = $aPos['mood'];

    $o = '<div class="decoded_POS">';
    $o .= '<table border="0"><tbody>';
    $o .= '<tr><td><strong>type</strong></td><td><span class="POS_type">' . $type . '</span></td></tr>';
    $o .= '<tr><td><strong>person</strong></td><td><span class="POS_person">' . $person . '</span></td></tr>';
    $o .= '<tr><td><strong>gender</strong></td><td><span class="POS_gender">' . $gender . '</span></td></tr>';
    $o .= '<tr><td><strong>number</strong></td><td><span class="POS_number">' . $number . '</span></td></tr>';
    $o .= '<tr><td><strong>finiteness</strong></td><td><span class="POS_finiteness">' . $finiteness . '</span></td></tr>';
    $o .= '<tr><td><strong>mood</strong></td><td><span class="POS_mood">' . $mood . '</span></td></tr>';
    $o .= '<tr><td><strong>tense</strong></td><td><span class="POS_tense">' . $tense . '</span></td></tr>';
    $o .= '<tr><td><strong>voice</strong></td><td><span class="POS_voice">' . $voice . '</span></td></tr>';
    $o .= '<tr><td><strong>aspect</strong></td><td><span class="POS_aspect">' . $aspect . '</span></td></tr>';
    $o .= '<tr><td><strong>separability</strong></td><td><span class="POS_separability">' . $separability . '</span></td></tr>';
    $o .= '<tr><td><strong>reflexivity</strong></td><td><span class="POS_reflexivity">' . $reflexivity . '</span></td></tr>';
    $o .= '<tr><td><strong>auxiliary</strong></td><td><span class="POS_auxiliary">' . $auxiliary . '</span></td></tr>';
    return $o . "</tbody></table></div>";
  } // convertPOS
} // class ConverterHTML

?>