<?php


class ConjugationGasconThirdGroup extends ConjugationBase{

  protected function getStandardConjugation(){
    $arr = array();
    $arr['00'] =  "i,es,,em,etz,en";
    $arr['01'] =  "èvi,èvas,èva,èvam,èvatz,èvan";
    $arr['02'] =  "oi,ós,ó,om,otz,ón";
    $arr['03'] =  "erèi,eràs,erà,eram,eratz,eràn";
    $arr['04'] =  "";
    $arr['05'] =  "ent";
    $arr['06'] =  "ut,uda";
    $arr['07'] =  ",em,etz,ias,iam,iatz";
    $arr['08'] =  "i,ias,ia,iam,iatz,ian";
    $arr['09'] =  "ossi,osses,osse,óssem,óssetz,ossen";
    $arr['10'] =  "erí,erés,eré,erem,eretz,erén";
    return $arr;
  } // getStandardConjugation

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

  public function display(){
    return "ConjugationGasconThirdGroup $this->_name " . $this->conjugate;
  } // display
} // class ConjugationGasconThirdGroup

?>