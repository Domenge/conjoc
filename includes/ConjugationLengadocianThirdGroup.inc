<?php


class ConjugationLengadocianThirdGroup extends ConjugationBase{

  protected function getStandardConjugation(){
  $arr = array();
  $arr['00'] =  "i,es,,èm,ètz,on";
  $arr['01'] =  "iái,iás,iá,iam,iatz,ián";
  $arr['02'] =  "èri,ères,èt,èrem,èretz,èron";
  $arr['03'] =  "rai,ràs,rà,rem,retz,ràn";
  $arr['04'] =  "";
  $arr['05'] =  "ent";
  $arr['06'] =  "ut,uda";
  $arr['07'] =  ",am,ètz,as,am,atz";
  $arr['08'] =  "a,as,a,am,atz,an";
  $arr['09'] =  "èsse,èsses,èsse,èssem,èssetz,èsson";
  $arr['10'] =  "riái,riás,riá,riam,riatz,rián";

  return $arr;
  } // getStandardConjugation

  public function display(){
    return "ConjugationLengadocianThirdGroup $this->_name " . $this->conjugate;
  } // display
  
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
  
  protected function fixRadical($radical,$desinence){
    return $radical;
  } // fixRadical
  
  protected function fixDesinence($desinence){
    return $desinence;
  } // fixDesinence

  public function getDesinenceLengthArray(){
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
  
} // class ConjugationLengadocianThirdGroup

?>