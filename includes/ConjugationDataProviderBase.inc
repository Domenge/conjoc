<?php

abstract class ConjugationDataProviderBase{
  
  const INDEXATION_STEP = 1000;

  protected $_baseTableName;

  public function __construct($baseTableName){
  	 $this->_baseTableName = $baseTableName;
  } // __construct

  
  protected function getBaseTableName(){
    return $this->_baseTableName;
  }

  abstract public function getVerb($verb);
  abstract public function getVerbById($id);
  abstract public function getVerbModelObject($numModel);
  abstract public function getTop20();
  abstract public function getOthersInModel($verb);
  abstract public function getCountOthersInModel($verb);
  abstract public function getVerbAutoComplete($string);
  abstract public function getRandomVerb();
  abstract public function getSingleVerbs();
  abstract public function getAllVerbs();
  abstract public function getAllDuplicatedVerbs();
  abstract public function insertIndexedVerb(array $arr);
	
} // class ConjugationDataProviderBase

?>