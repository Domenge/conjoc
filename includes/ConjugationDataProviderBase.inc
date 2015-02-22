<?php

abstract class ConjugationDataProviderBase{

  protected $_baseTableName;

  public function __construct($baseTableName){
  	 $this->_baseTableName = $baseTableName;
  } // __construct

  
  protected function getBaseTableName(){
    return $this->_baseTableName;
  }

  abstract public function getVerb($verb);
  abstract public function getVerbModel($numModel);
  abstract public function getTop20();
  abstract public function getOthersInModel($verb);
  abstract public function getCountOthersInModel($verb);
  abstract public function getVerbAutoComplete($string);
  abstract public function getRandomVerb();
  abstract public function getSingleVerbs();
	
} // class ConjugationManagerBase

?>