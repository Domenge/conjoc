<?php

abstract class ConjugationManagerBase{
  protected $_baseTablename;
  private $_dialect;
  private $_localization;
  private $_comments;
  private $_libModel;
  private $_verbPrime;
  private $_verb;
  private $_model;
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

  public function __construct(){
  } // __construct

  public function getDialect(){
    return $this->_dialect;
  }

  public function setDialect($dialect){
    $dialect = strtolower($dialect);
    $this->_dialect = $dialect;

    switch($dialect){
      case ConjugationManagerBase::LENGADOCIAN:
        $this->_baseTablename = "sauzet";
      	break;
      case ConjugationManagerBase::GASCON:
        $this->_baseTablename = "gascon";
      	break;
      case ConjugationManagerBase::PROVENCAU:
        $this->_baseTablename = "provencau";
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
  
  public function getVerb(){
    return $this->_verb;
  }

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
  }

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

  public function getRandomVerb(){
    return $this->_dataProvider->getRandomVerb();
  } // getRandomVerb()

  abstract public function getUsualVerbs();
  abstract public function generateConjugation();
  
  public function conjugate(){
     return $this->generateConjugation()->conjugate();
  }
	
} // class ConjugationManagerBase

?>