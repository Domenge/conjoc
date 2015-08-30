<?php

class ConjugationLengadocianManager extends ConjugationManagerBase{
  public function __construct(){
    $this->setDialect(ConjugationManagerBase::LENGADOCIAN);
  } // __construct

  public function generateConjugation(){
    switch ($this->getGroup()){
      case ConjugationBase::AUXILLIARY :
        $obj = new ConjugationLengadocianAuxilliary($this);
        break;
      case ConjugationBase::FIRST_GROUP:
        $obj = new ConjugationLengadocianFirstGroup($this);
        break;
      case ConjugationBase::SECOND_GROUP:
        $obj = new ConjugationLengadocianSecondGroup($this);
        break;
      case ConjugationBase::THIRD_GROUP:
        $obj = new ConjugationLengadocianThirdGroup($this);
        break;
    }
    return $obj;

  } // generateConjugation

  public function getUsualVerbs(){
     $arrRet = array();
     $arrRet['èsser'] = 'lengadocian/verb_autocomplete/usuals/èsser';
     $arrRet['aver'] = 'lengadocian/verb_autocomplete/usuals/aver';
     $arrRet['anar'] = 'lengadocian/verb_autocomplete/usuals/anar';
     $arrRet['far'] = 'lengadocian/verb_autocomplete/usuals/far';
     $arrRet['venir'] = 'lengadocian/verb_autocomplete/usuals/venir';
     $arrRet['cantar'] = 'lengadocian/verb_autocomplete/usuals/cantar';
     $arrRet['poder'] = 'lengadocian/verb_autocomplete/usuals/poder';
     $arrRet['saber'] = 'lengadocian/verb_autocomplete/usuals/saber';
     $arrRet['valer'] = 'lengadocian/verb_autocomplete/usuals/valer';
     $arrRet['aduire'] = 'lengadocian/verb_autocomplete/usuals/aduire';

     return $arrRet;
  } // getUsuals 

  public function getVerbFAR($verb){
  	return $this->getProvider()->getVerbFAR($verb);
  }	
} // class ConjugationLengadocianManager

?>