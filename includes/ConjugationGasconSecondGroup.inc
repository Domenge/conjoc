<?php


class ConjugationGasconSecondGroup extends ConjugationBase{

  protected function getStandardConjugation(){
    $arr = array();
    $arr['00_IndPres|Present']                 =  "issi,isses,ís,issem,issetz,issen";
    $arr['01_IndImp|Imperfach']                =  "ivi,ivas,iva,­ívam,ívatz,ivan";
    $arr['02_IndPret|Preterit']                =  "ii,ís,í,im,itz,ín";
    $arr['03_IndFutur|Futur']                  =  "irèi,iràs,irà,iram,iratz,iràn";
    $arr['04_Infinitiu|Infinitiu']             =  "ir";
    $arr['05_Gerondiu|Gerondiu']               =  "issent";
    $arr['06_PartPassat|Participi passat']     =  "it,ida";
    $arr['07_Imperatiu|Present positiu/present negatiu'] = "ís,im,itz,escas,escam,escatz";
    $arr['08_SubPres|Subjontiu present']       =  "esqui,escas,esca,escam,escatz,escan";
    $arr['09_SubImp|Subjontiu imperfach']      =  "issi,isses,isse,íssem,íssetz,issen";
    $arr['10_Conditional|Condicional']         =  "irí,irés,iré,irem,iretz,irén";    
    return $arr;
  } // setStandardConjugation

  protected function fixRadical($radical,$desinence){
    return $radical;
  } // fixRadical
  
  protected function fixDesinence($desinence){
    return $desinence;
  } // fixDesinence

  protected function getConjugationArray(){
    $infinitive = $this->getVerb();

    $pattern = '/ \d{1}$/';

    if (preg_match($pattern, $infinitive)){
      $rootSaved = preg_replace('/(.+)(ar \d{1}$)/', '$1', $infinitive);
    }else{
      $rootSaved = substr($infinitive,0,-2);
    }
        
    $conjugations = array();

    // for each temps
    foreach($this->getStandardConjugation() as $lib=>$desinence){
      $desinences = explode(',', $desinence);
      $i=0;
      $tempsConjugated = array();

      foreach ($desinences as $elmnt){
        $root = $this->fixRadical($rootSaved,$elmnt);
        $elmnt = $this->fixDesinence($elmnt);
        $tempsConjugated[] = $root.$elmnt; 
      } // for desinences
      $conjugations[] = $tempsConjugated;
    } // foreach temps

    return $conjugations;
  } // getConjugationArray

  protected function getDesinenceLengthArray(){
    $desinenceLengths = array();
    $desinenceLengths[]="1,2,1,2,3,2";
    $desinenceLengths[]="3,4,3,4,5,4";
    $desinenceLengths[]="3,4,2,4,5,4";
    $desinenceLengths[]="4,4,3,4,5,4";
    $desinenceLengths[]="2";
    $desinenceLengths[]="3";
    $desinenceLengths[]="1,2,3,2,2,3";
    $desinenceLengths[]="1,2,1,2,3,2";
    $desinenceLengths[]="4,5,4,4,6,5";
    $desinenceLengths[]="5,5,4,5,6,5";
    return $desinenceLengths;

  } // getDesinenceLengthArray

  public function display(){
    return array();
  } // display
} // class ConjugationGasconSecondGroup

?>