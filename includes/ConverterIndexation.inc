<?php

class ConverterIndexation implements IConverter{

  public function __construct(){
  } // __construct

  // EAGLES Morphosyntactic Annotation # 4.2.2 
  public function encodePOS($ary){
/*
$person,$gender,$number,
  	$finiteness,$mood,$tense,
  	$voice,$status,$aspect,
  	$separability,$reflexivity,$auxiliary
*/
    $strret = 'V';
    // I Person 1 First 2 Second 3 Third
    $strret .= $ary['person'];
    // II Gender 1 Masculine 2 Feminine 3 Neuter
    $strret .= $ary['gender'];
    // III Number 1 Singular 2 Plural
    $strret .= $ary['number'];
    // IV Finiteness 1 Finite 2 Non-finite
    $strret .= $ary['finiteness'];
    // V Mood 1 Indicative 2 Subjunctive 3 Imperative 4 Conditional 5 Infinitive 6 Participle 7 Gerund 8 Supine
    $strret .= $ary['mood'];
    // VI Tense 1 Present 2 Imperfect 3 Future 4 Past
    $strret .= $ary['tense'];
    // VII Voice 1 Active 2 Passive
    $strret .= $ary['voice'];
    // VIII Status 1 Main 2 Auxiliary 3 Semi-auxiliary
    $strret .= $ary['status'];
    // IX Aspect 1 Perfective 2 Imperfective
    $strret .= $ary['aspect'];
    // X Separability 1 Non-separable 2 Separable
    $strret .= $ary['separability'];
    // XI Reflexivity 1 Reflexive 2 Non-reflexive
    $strret .= $ary['reflexivity'];
    // XII Auxiliary 1 Have 2 Be
    $strret .= $ary['auxiliary'];

    return $strret;
  } // encodePOS

  public function decodePOS($pos){
    // split the pos string into characters
    $chars = preg_split('//', $pos, -1, PREG_SPLIT_NO_EMPTY);
    $arret = array();
    $arret['type'] = (strtolower($chars[0]) == 'v')?'Verb':'error'; 
    $arret['person'] = ($chars[1] == 0)?'N/A':$chars[1];
    // II Gender 1 Masculine 2 Feminine 3 Neuter
    $arret['gender'] = ($chars[2] == 1)?'Masculine':'N/A';
    $arret['gender'] = ($chars[2] == 2)?'Feminine':$arret['gender'];
    $arret['gender'] = ($chars[2] == 3)?'Neuter':$arret['gender'];
     
    // III Number 1 Singular 2 Plural
    $arret['number'] = ($chars[3] == 1)?'Singular':'N/A';
    $arret['number'] = ($chars[3] == 2)?'Plural':$arret['number'];

    // IV Finiteness 1 Finite 2 Non-finite
    $arret['finiteness'] = ($chars[4] == 1)?'Finite':'N/A';
    $arret['finiteness'] = ($chars[4] == 2)?'Non-finite':$arret['finiteness'];

    // V Mood 1 Indicative 2 Subjunctive 3 Imperative 4 Conditional 5 Infinitive 6 Participle 7 Gerund 8 Supine
    $arret['mood'] = ($chars[5] == 1)?'Indicative':'N/A';
    $arret['mood'] = ($chars[5] == 2)?'Subjunctive':$arret['mood'];
    $arret['mood'] = ($chars[5] == 3)?'Imperative':$arret['mood'];
    $arret['mood'] = ($chars[5] == 4)?'Conditional':$arret['mood'];
    $arret['mood'] = ($chars[5] == 5)?'Infinitive':$arret['mood'];
    $arret['mood'] = ($chars[5] == 6)?'Participle':$arret['mood'];
    $arret['mood'] = ($chars[5] == 7)?'Gerund':$arret['mood'];
    $arret['mood'] = ($chars[5] == 8)?'Supine':$arret['mood'];

    // VI Tense 1 Present 2 Imperfect 3 Future 4 Past
    $arret['tense'] = ($chars[6] == 1)?'Present':'N/A';
    $arret['tense'] = ($chars[6] == 2)?'Imperfect':$arret['tense'];
    $arret['tense'] = ($chars[6] == 3)?'Future':$arret['tense'];
    $arret['tense'] = ($chars[6] == 4)?'Past':$arret['tense'];
    // VII Voice 1 Active 2 Passive
    $arret['voice'] = ($chars[7] == 1)?'Active':'N/A';
    $arret['voice'] = ($chars[7] == 2)?'Passive':$arret['voice'];
    // VIII Status 1 Main 2 Auxiliary 3 Semi-auxiliary
    $arret['status'] = ($chars[8] == 1)?'Main':'N/A';
    $arret['status'] = ($chars[8] == 2)?'Auxiliary':$arret['status'];
    $arret['status'] = ($chars[8] == 3)?'Semi-auxiliary':$arret['status'];
    // IX Aspect 1 Perfective 2 Imperfective
    $arret['aspect'] = ($chars[9] == 1)?'Perfective':'N/A';
    $arret['aspect'] = ($chars[9] == 2)?'Imperfective':$arret['aspect'];
    // X Separability 1 Non-separable 2 Separable
    $arret['separability'] = ($chars[10] == 1)?'Non-separable':'N/A';
    $arret['separability'] = ($chars[10] == 2)?'Separable':$arret['separability'];
    // XI Reflexivity 1 Reflexive 2 Non-reflexive
    $arret['reflexivity'] = ($chars[11] == 1)?'Reflexive':'N/A';
    $arret['reflexivity'] = ($chars[11] == 2)?'Non-reflexive':$arret['reflexivity'];
    // XII Auxiliary 1 Have 2 Be
    $arret['auxiliary'] = ($chars[12] == 1)?'Have':'N/A';
    $arret['auxiliary'] = ($chars[12] == 2)?'Be':$arret['auxiliary'];

    return $arret;
  } // encodePOS

  public function encodeDialect($str){
    $strRet = ($str == 'lengadocian')?'LNG':'ERROR';
    $strRet = ($str == 'gascon')?'GSC':$strRet;
    $strRet = ($str == 'provencal')?'PRV':$strRet;
  	
    return $strRet;
  } // encodeDialect

  public function decodeDialect($str){
    $str = strtoupper($str);
    $strRet = ($str == 'LNG')?'lengadocian':'ERROR';
    $strRet = ($str == 'GSC')?'gascon':$strRet;
    $strRet = ($str == 'PRV')?'provencal':$strRet;
  	
    return $strRet;
  } // decodeDialect

  public function encodeTense($code){
    $codeRet = 0;
    $codeRet = ($code == ConjugationBase::IND_PRESENT)?1:$codeRet;
    $codeRet = ($code == ConjugationBase::IND_IMPERFECT)?2:$codeRet;
    $codeRet = ($code == ConjugationBase::IND_PRETERIT)?4:$codeRet;
    $codeRet = ($code == ConjugationBase::IND_FUTURE)?3:$codeRet;
    $codeRet = ($code == ConjugationBase::PAST_PARTICIPLE)?4:$codeRet;
    $codeRet = ($code == ConjugationBase::IMPERATIVE)?1:$codeRet;
    $codeRet = ($code == ConjugationBase::SUBJ_PRESENT)?1:$codeRet;
    $codeRet = ($code == ConjugationBase::SUBJ_IMPERFECT)?2:$codeRet;
    $codeRet = ($code == ConjugationBase::CONDITIONAL)?3:$codeRet; 	
    return $codeRet;
  } // encodeTense
  
  public function convertConjugation(array $conjugated){

    $conjugations = $conjugated["conjugations"];
    $model        = $conjugated["model"];
    
    $ModesArray = array();
    
    // for each tens
    for ($i=ConjugationBase::IND_PRESENT;$i < ConjugationBase::CONDITIONAL +1 ;$i++){
      $conjugation = $conjugations[$i];

      switch($i){
        case ConjugationBase::IND_PRESENT : $mode = 'Indicative'; $ModesArray['Indicative']= array();break;
        case ConjugationBase::INFINITIVE  : $mode = 'Impersonal forms'; $ModesArray['Impersonal forms']= array(); break;
        case ConjugationBase::IMPERATIVE  : $mode = 'Imperative'; $ModesArray['Imperative']= array(); break;
        case ConjugationBase::SUBJ_PRESENT: $mode = 'Subjunctive'; $ModesArray['Subjunctive']= array(); break;
        case ConjugationBase::CONDITIONAL : $mode = 'Conditional'; $ModesArray['Conditional']= array(); break;
      }

      
      // big dispatch
      // Each temps is dispatched in its own mode        
      switch($mode){
      	case "Indicative" :
      		$ModesArray['Indicative'][] = $conjugation; 
      		break; 
      	case "Impersonal forms" :
      		$ModesArray['Impersonal forms'][] = $conjugation;
      		break; 
      	case "Imperative" :
      		$ModesArray['Imperative'][] = $conjugation; 
      		break; 
      	case "Subjunctive" :
      		$ModesArray['Subjunctive'][] = $conjugation; 
      		break; 
      	case "Conditional" :
      		$ModesArray['Conditional'][] = $conjugation; 
      		break; 
      } // switch
    } // for
    return $this->formatConjugation($model,$ModesArray);
  } // convertConjugation

  
  private function formatConjugation($model,$ConjugationArray){
    $out = "";
    
    // 0 is a value for void or not availability
     
    // I	Person	1 First 2 Second 3 Third
    // II	Gender	1 Masculine 2 Feminine 3 Neuter
    // III	Number	1 Singular 2 Plural
    // IV	Finiteness	1 Finite 2 Non-finite
    // V	Mood	1 Indicative 2 Subjunctive 3 Imperative 4 Conditional 5 Infinitive 6 Participle 7 Gerund 8 Supine
    // VI	Tense	1 Present 2 Imperfect 3 Future 4 Past
    // VII	Voice	1 Active 2 Passive
    // VIII	Status	1 Main 2 Auxiliary 3 Semi-auxiliary
    // IX	Aspect	1 Perfective 2 Imperfective
    // X	Separability	1 Non-separable 2 Separable
    // XI	Reflexivity	1 Reflexive 2 Non-reflexive
    // XII	Auxiliary	1 Have 2 Be

    // Default values
    $voice = 0;
    $finiteness = 0;
    $status = 1;
    
    // Indicative
    $ary = $ConjugationArray['Indicative'];

//    $tenses = array("present","imperfect","preterit","future");
    $tenses = array(1,2,4,3);
    $gen = 0; // neuter	
    $mood = 1;

    for ($j=0; $j < 4; $j++){

    	$tns  = $tenses[$j];
    	$conj = $ary[$j];
    	
	for($i=0;$i<6;$i++){
		$number = ($i<3)? 'singular':'plural';
		$per = ($i<3)? $i+1:$i - 2;
		$orth = $conj[$i];
    	} //for

    } // for

    // CONDITIONAL
    $ary = $ConjugationArray['Conditional'];

    $mood = 4;

    $tns  = 'present';
    $conj = $ary[0];
    	
    for($i=0;$i<6;$i++){
	$number = ($i<3)? 'singular':'plural';
	$per = ($i<3)? $i+1:$i - 2;
	$orth = $conj[$i];
    } // for

    // INFINITIVE, GERUND & PARTICLE
    $ary = $ConjugationArray['Impersonal forms'];   

    $mood = 5; // 'infinitive';
    $conj = $ary[0];   	
    $orth = $conj[0];

    $mood = 6; // 'gerund';
    $conj = $ary[1];   	
    $orth = $conj[0];

    $mood = 7; // 'participle';
    $tns  = 'past';
    $conj = $ary[2];   	
    $orth = $conj[0];
    $gen  = 1; // 'masculin';

    $orth = $conj[1];	
    $gen  = 2; //'feminine';
  
    // IMPERATIVE
    $ary = $ConjugationArray['Imperative'];   
    $mood = 'imperative';

    $tns  = 'present';
    $conj = $ary[0];
    	
	for($i=0;$i<6;$i++){
		$number = ($i==0 || $i==3)? 'singular':'plural';
		$usg = ($i<3)? 'positive':'negative';
		$per = ($i==2 || $i==5)? 2:1;
		$orth = $conj[$i];
    } // for

    
    // SUBJUNCTIVE
    $ary = $ConjugationArray['Subjunctive'];   

    $tenses = array("present","imperfect");

    $mood = 'subjunctive';

    for ($j=0; $j < 2; $j++){

    	$tns  = $tenses[$j];
    	$conj = $ary[$j];
    	
	for($i=0;$i<6;$i++){
		$number = ($i<3)? 'singular':'plural';
		$per = ($i<3)? $i+1:$i - 2;
		$orth = $conj[$i];
    	} //for

    } // for

    return $out;  
  } // formatConjugation

/*
Array ( 
[id] => 11821 
[name] => abajanir 
[infinitive] => Array ( [0] => abajanir ) 
[model] => 200 
[comments] => not yet implemented 
[libmodel] => conjugason 2 radical consonantic 
[dialect] => lengadocian 
[localization] => C 
[conjugations] => Array ( [0] => Array ( [0] => abajanissi [1] => abajanisses [2] => abajanís [3] => abajanissem [4] => abajanissetz [5] => abajanissen ) [1] => Array ( [0] => abajanivi [1] => abajanivas [2] => abajaniva [3] => abajan­ívam [4] => abajanívatz [5] => abajanivan ) [2] => Array ( [0] => abajanii [1] => abajanís [2] => abajaní [3] => abajanim [4] => abajanitz [5] => abajanín ) [3] => Array ( [0] => abajanirèi [1] => abajaniràs [2] => abajanirà [3] => abajaniram [4] => abajaniratz [5] => abajaniràn ) [4] => Array ( [0] => abajanir ) [5] => Array ( [0] => abajanissent ) [6] => Array ( [0] => abajanit [1] => abajanida ) [7] => Array ( [0] => abajanís [1] => abajanim [2] => abajanitz [3] => abajanescas [4] => abajanescam [5] => abajanescatz ) [8] => Array ( [0] => abajanesqui [1] => abajanescas [2] => abajanesca [3] => abajanescam [4] => abajanescatz [5] => abajanescan ) [9] => Array ( [0] => abajanissi [1] => abajanisses [2] => abajanisse [3] => abajaníssem [4] => abajaníssetz [5] => abajanissen ) [10] => Array ( [0] => abajanirí [1] => abajanirés [2] => abajaniré [3] => abajanirem [4] => abajaniretz [5] => abajanirén ) ) 
[desinenceLengths] => Array ( [0] => 1,2,1,2,3,2 [1] => 3,4,3,4,5,4 [2] => 3,4,2,4,5,4 [3] => 4,4,3,4,5,4 [4] => 2 [5] => 3 [6] => 1,2,3,2,2,3 [7] => 1,2,1,2,3,2 [8] => 4,5,4,4,6,5 [9] => 5,5,4,5,6,5 ) ) 
*/
  public function convertArray(array $ary){
    $row = 0;
    return array(
    'verb'=>$ary['name'],
    'row'=>$row,
    'dialect'=>$this->encodeDialect($ary['dialect']),
    'nummodel'=>$ary['model'],
    'conjugation'=>$ary['conjugations'],
    'pos'=>$ary['pos']);

  } // convertArray

  public function convertSelect(array $conjugation){
  
  }


} // class ConverterIndexation

?>