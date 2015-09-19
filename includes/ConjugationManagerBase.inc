<?php

abstract class ConjugationManagerBase{
  protected $_baseTablename;
  private $_dialect;
  private $_dialectCode;
  private $_localization;
  private $_comments;
  private $_libModel;
  private $_verbPrime;
  private $_verb;
  private $_model;
  private $_conjugations;
  private $_group;
  private $_seeAlso;
  private $_alias;
  private $_idVerb;

  private $_dataProvider;

  const LENGADOCIAN  = "lengadocian";
  const GASCON       = "gascon";
  const PROVENCAL    = "provencal";
  const VIVAROALPENC = "vivaro-alpenc";
  const AUVERNHAT    = "auvernhat";
  const LEMOSIN      = "lemosin";

  const LENGADOCIAN_CODE  = "lng";
  const GASCON_CODE       = "gsc";
  const PROVENCAL_CODE    = "prv";
  const VIVAROALPENC_CODE = "alp";
  const AUVERNHAT_CODE    = "auv";
  const LEMOSIN_CODE      = "lem";

  public function __construct(){
  } // __construct

  public function getDialect(){
    return $this->_dialect;
  }

  public function getDialectCode(){
    return $this->_dialectCode;
  }

  public function setDialect($dialect){
    $dialect = strtolower($dialect);
    $this->_dialect = $dialect;

    switch($dialect){
      case ConjugationManagerBase::LENGADOCIAN:
        $this->_dialectCode = ConjugationManagerBase::LENGADOCIAN_CODE;
        $this->_baseTablename = "sauzet";
      	break;
      case ConjugationManagerBase::GASCON:
        $this->_dialectCode = ConjugationManagerBase::GASCON_CODE;
        $this->_baseTablename = "gascon";
      	break;
      case ConjugationManagerBase::PROVENCAL:
        $this->_dialectCode = ConjugationManagerBase::PROVENCAL_CODE;
        $this->_baseTablename = "provencal";
      	break;
    }
    if (! empty($this->_baseTablename)){
       $this->_dataProvider = new ConjugationDataProviderDrupal($this->_baseTablename);
    }else{ 
    // should never be here
      $text = t(":@dialect: is not a supported dialect", array('@dialect' => $dialect));
      drupal_set_message($text, 'error');
//      die($text);
    }
  }

  public function setDialectCode($dialectCode){
    $this->_dialectCode = $dialectCode;
  } // setDialectCode
  
  public function getVerb(){
    return $this->_verb;
  } // getVerb

  public function setVerb($verb){
    $this->_verb = $verb;
    $line  = $this->_dataProvider->getVerb($verb); 

    $this->setVerbModel($line->nummodel);

    $this->_seeAlso = $line->see;
    $this->_alias = $line->alias;
    $this->_idVerb = $line->id;

    $modelObj  = $this->_dataProvider->getVerbModel($line->nummodel); 

    $this->_localization = 'c';
    $this->_comments  = 'not yet implemented';
    $this->_libModel  = empty($modelObj->label_conjugation)?"":$modelObj->label_conjugation;
    $this->_verbPrime = empty($modelObj->verb_prime)?"":$modelObj->verb_prime;
    $this->_conjugations = $modelObj->conjugations;
  } // setVerb

  private function setVerbModel($model){
    $group = substr($model,0,1);

    $this->_group = $group;
    $this->_model = $model;
  }

  public function getVerbModel(){
    return $this->_model;
  }

  public function getGroup(){
    return $this->_group;
  }

  public function getSeeAlso(){
    return $this->_seeAlso;
  }

  public function getAlias(){
    return $this->_alias;
  }

  public function getVerbId(){
    return $this->_idVerb;
  }

  public function getComments(){
    return $this->_comments;
  }

  public function getLibModel(){
    return $this->_libModel;
  }

  public function getLocalization(){
    return 'C';
  }

  public function getConjugations(){
    return $this->_conjugations;
  }

  public function getProvider(){
    return $this->_dataProvider;
  }

  public function getTop20(){
       return $this->_dataProvider->getTop20();
  } // getTop20

  public function getOthersInModel($verb){
       return $this->_dataProvider->getOthersInModel($verb);
  } // getOthersInModel

  public function getCountOthersInModel($verb){
       return $this->_dataProvider->getCountOthersInModel($verb);
  } // getCountOthersInModel

  public function getSingleVerbs(){
    $arrRet = array();
    $singleVerbs = $this->_dataProvider->getSingleVerbs();

    foreach ($singleVerbs as $verb){
      $arrRet[$verb] = "gascon/verb_autocomplete/usuals/$verb";
    }
    return $arrRet;
  } // getSingleVerbs

  public function getVerbAutoComplete($string){
       return drupal_json_output($this->_dataProvider->getVerbAutoComplete($string));
  } // getVerbAutoComplete

  public function getIndexationAutoComplete($string){
       return drupal_json_output($this->_dataProvider->getIndexationAutoComplete($string));
  } // getIndexationAutoComplete

  public function getIndexationData($conjugation){
       return $this->_dataProvider->getIndexationData($conjugation);
  } // getIndexatioData

  public function getRandomVerb(){
    return $this->_dataProvider->getRandomVerb();
  } // getRandomVerb()

  abstract public function getUsualVerbs();
  abstract public function generateConjugation();
  
  public function conjugate(){
     return $this->generateConjugation()->conjugate();
  }

  public function processIndexation(){
    $indexationConverter = new ConverterIndexation();
    $allVerbs = $this->_dataProvider->getAllVerbsByIncrement();

    foreach($allVerbs as $aVerb){
        $infinitive = $aVerb['infinitive'];
        $row = $aVerb['row'];
        
	$this->setVerb($aVerb['verb']);
	
    	$ary = $this->conjugate();
	$name = $ary['name'];

	$conjugations = $ary['conjugations'];
	$model = $ary['model'];
	$dialect = $indexationConverter->encodeDialect($ary['dialect']);
	// put POS default values 
	$aryPOS = array();
	
	//$aryPOS['person'] = 1;
	// II Gender 1 Masculine 2 Feminine 3 Neuter
	$aryPOS['gender'] = 0;
	// III Number 1 Singular 2 Plural
	//$aryPOS['number'] = 1;
	// IV Finiteness 1 Finite 2 Non-finite
	$aryPOS['finiteness'] = 0;
	// V Mood 1 Indicative 2 Subjunctive 3 Imperative 4 Conditional 5 Infinitive 6 Participle 7 Gerund 8 Supine
	// $aryPOS['mood'] = 1;
	// VI Tense 1 Present 2 Imperfect 3 Future 4 Past
	// $aryPOS['tense'] = 1;
	// VII Voice 1 Active 2 Passive
	$aryPOS['voice'] = 0;
	// VIII Status 1 Main 2 Auxiliary 3 Semi-auxiliary
	$aryPOS['status'] = 1;
	
	if ($model == '001' || $model == '002'){
		$aryPOS['status'] = 2;
	}
	if ($model == '003' || $model == '003 b' || $model == '004'){
		$aryPOS['status'] = 3;
	}

	// IX Aspect 1 Perfective 2 Imperfective
	$aryPOS['aspect'] = 0;
	// X Separability 1 Non-separable 2 Separable
	$aryPOS['separability'] = 0;
	// XI Reflexivity 1 Reflexive 2 Non-reflexive
	$aryPOS['reflexivity'] = 0;
	// XII Auxiliary 1 Have 2 Be
	$aryPOS['auxiliary'] = 0;
	// iterating in the conjugations, a record is created for each flexion

	for($i=ConjugationBase::IND_PRESENT; $i < ConjugationBase::LAST_NORMAL_TEMPS + 1; $i++){

      	   $conjugation = $conjugations[$i];
	   switch($i){
	     case ConjugationBase::IND_PRESENT : 
	     case ConjugationBase::IND_IMPERFECT : 
	     case ConjugationBase::IND_PRETERIT : 
	     case ConjugationBase::IND_FUTUR :
	     	$mood = '1'; 
	     	break;
             case ConjugationBase::INFINITIVE  : $mood = '5'; break;
             case ConjugationBase::GERUND      : $mood = '7'; break;
             case ConjugationBase::PAST_PARTICIPLE  : $mood = '6'; break;
             case ConjugationBase::IMPERATIVE  : $mood = '3'; break;
             case ConjugationBase::SUBJ_PRESENT: 
             case ConjugationBase::SUBJ_IMPERFECT: 
             	$mood = '2'; break;
             case ConjugationBase::CONDITIONAL : $mood = '4'; break;
      	   }
      	   
      	   $aryPOS['mood'] = $mood;
      	   $aryPOS['tense'] = $indexationConverter->encodeTense($i);
      	   
      	   if ($i == ConjugationBase::INFINITIVE || $i == ConjugationBase::GERUND){
      	   	  $conj = $conjugation[0];
		  $aryPOS['person'] = 0;
		  $aryPOS['number'] = 1;
	    	  $pos = $indexationConverter->encodePOS($aryPOS);
    		  $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                  $this->_dataProvider->insertIndexedVerb($fields);
      	   }else if ($i == ConjugationBase::PAST_PARTICIPLE){
      	   	  $conj = $conjugation[0];
		  $aryPOS['person'] = 0;
		  $aryPOS['number'] = 1;
		  $aryPOS['gender'] = 1;
		  $aryPOS['tense'] = 4;

	    	  $pos = $indexationConverter->encodePOS($aryPOS);
    		  $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                  $this->_dataProvider->insertIndexedVerb($fields);

      	   	  $conj = $conjugation[1];
		  $aryPOS['person'] = 0;
		  $aryPOS['number'] = 1;
	  	  $aryPOS['gender'] = 2;

	    	  $pos = $indexationConverter->encodePOS($aryPOS);
    		  $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                  $this->_dataProvider->insertIndexedVerb($fields);

      	   }else if ($i == ConjugationBase::IMPERATIVE){
      	   	for($j=0;$j < 6;$j++){
	     	  $conj = $conjugation[$j];
	     	  $person = ($j < 3)? $j+1:$j-2;
		  $aryPOS['person'] = $person;
	     	  $number = ($j < 3)? 1:2;
		  $aryPOS['number'] = $number;
	    	  $pos = $indexationConverter->encodePOS($aryPOS);
    		  $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                  $this->_dataProvider->insertIndexedVerb($fields);
	     	} // for	     
      	   }else{   // OTHERS
      	   	for($j=0;$j < 6;$j++){
	     	  $conj = $conjugation[$j];
	     	  $person = ($j < 3)? $j+1:$j-2;
		  $aryPOS['person'] = $person;
	     	  $number = ($j < 3)? 1:2;
		  $aryPOS['number'] = $number;
	    	  $pos = $indexationConverter->encodePOS($aryPOS);
    		  $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                  $this->_dataProvider->insertIndexedVerb($fields);
	     	} // for	     
      	   }      	   
	} // for

    }
    return "<strong>done</strong>";
	
  } // processIndexation
	
} // class ConjugationManagerBase

?>