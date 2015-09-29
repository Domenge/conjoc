<?php

class ConjugationGasconManager extends ConjugationManagerBase{

  public function __construct(){
    $this->setDialect(ConjugationManagerBase::GASCON);
  } // __construct

  public function generateConjugation(){
    switch ($this->getGroup()){
      case ConjugationBase::AUXILLIARY :
        $obj = new ConjugationGasconAuxilliary($this);
        break;
      case ConjugationBase::FIRST_GROUP:
        $obj = new ConjugationGasconFirstGroup($this);
        break;
      case ConjugationBase::SECOND_GROUP:
        $obj = new ConjugationGasconSecondGroup($this);
        break;
      case ConjugationBase::THIRD_GROUP:
        $obj = new ConjugationGasconThirdGroup($this);
        break;
    }
    return $obj;

  } // generateConjugation

  public function getUsualVerbs(){
     $arrRet = array();
     $arrRet['èsser'] = 'gascon/verb_autocomplete/usuals/èsser';
     $arrRet['aver'] = 'gascon/verb_autocomplete/usuals/aver';
     $arrRet['anar'] = 'gascon/verb_autocomplete/usuals/anar';
     $arrRet['far'] = 'gascon/verb_autocomplete/usuals/far';
     $arrRet['venir'] = 'gascon/verb_autocomplete/usuals/venir';
     $arrRet['cantar'] = 'gascon/verb_autocomplete/usuals/cantar';
     $arrRet['poder'] = 'gascon/verb_autocomplete/usuals/poder';
     $arrRet['saber'] = 'gascon/verb_autocomplete/usuals/saber';
     $arrRet['valer'] = 'gascon/verb_autocomplete/usuals/valer';
     $arrRet['aduire'] = 'gascon/verb_autocomplete/usuals/aduire';

     return $arrRet;
  } // getUsualVerbs 

  public function getShortLabel(){
  	return "gsc";
  }

  public function getLongLabel(){
  	return "gascon";
  }
	
} // class ConjugationGasconManager

?>