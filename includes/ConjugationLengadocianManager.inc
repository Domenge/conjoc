<?php

class ConjugationLengadocianManager extends ConjugationManagerBase{
  public function __construct(){
    $this->setDialect(GASCON);
  } // __construct

  public function generateConjugation(){
    switch ($this->getGroup()){
      case ConjugationBase::AUXILLIARY :
        $obj = new ConjugationLengadocianAuxilliary($this,$verb,$id,$model,$comments,$localization);
        break;
      case ConjugationBase::FIRST_GROUP:
        $obj = new ConjugationLengadocianFirstGroup($this,$verb,$model,$comments,$localization);
        break;
      case ConjugationBase::SECOND_GROUP:
        $obj = new ConjugationLengadocianSecondGroup($this,$verb,$model,$comments,$localization);
        break;
      case ConjugationBase::THIRD_GROUP:
        $obj = new ConjugationLengadocianThirdGroup($this,$verb,$alias,$model,$comments,$localization);
        break;
    }
    return $obj;

  } // generateConjugation

  public function getUsualVerbs(){
     $arrRet = array();
     $arrRet['èsser'] = 'conjoc/verb_autocomplete/usuals/èsser';
     $arrRet['aver'] = 'conjoc/verb_autocomplete/usuals/aver';
     $arrRet['anar'] = 'conjoc/verb_autocomplete/usuals/anar';
     $arrRet['far'] = 'conjoc/verb_autocomplete/usuals/far';
     $arrRet['venir'] = 'conjoc/verb_autocomplete/usuals/venir';
     $arrRet['cantar'] = 'conjoc/verb_autocomplete/usuals/cantar';
     $arrRet['poder'] = 'conjoc/verb_autocomplete/usuals/poder';
     $arrRet['saber'] = 'conjoc/verb_autocomplete/usuals/saber';
     $arrRet['valer'] = 'conjoc/verb_autocomplete/usuals/valer';
     $arrRet['aduire'] = 'conjoc/verb_autocomplete/usuals/aduire';

     return $arrRet;
  } // getUsuals 

	
} // class ConjugationLengadocianManager

?>