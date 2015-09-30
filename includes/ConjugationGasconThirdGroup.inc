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

  private function getMixedConjugation($model){
  	  $arr = $this->getStandardConjugation($model);

	  $line = $this->getVerbModelObject($model);
  	  $label = $line->label_conjugation;
  	  $conjugations= $line->conjugations;

  	  $tempses = explode('|', $conjugations);

  	  // for each conjugation
  	  $arrTemps = array();

  	  foreach($tempses as $temps){
    	    $arrConjugations = explode(':', $temps);
    	    $index = $arrConjugations[0];
    	    $conjugationStr = (isset($arrConjugations[1]))?$arrConjugations[1]:"";
 
	    if ($conjugationStr){
      	      $arr[$index]= $conjugationStr; 
    	    } // if
          } // foreach 

     return $arr;
  } // getMixedConjugation($model)

  protected function getConjugationArray(){

    $infinitive = $this->getVerb();
    $vowelGrave = $this->isVowelDetected($infinitive);
    $tonic = $this->isTonicDetected($infinitive);
    $model = $this->getVerbModel();
    $arr = $this->getMixedConjugation($model);

    $patterns = array();
    $patterns[1] = '/er$/';
    $patterns[0] = '/re$/';
    $replacements = array();
    $replacements[1] = '';
    $replacements[0] = '';
    $rootTruncated = preg_replace($patterns, $replacements, $infinitive);
    $conjugations = array();

    $rootTruncated = $this->neutralizeTonic($rootTruncated,$tonic);

    // for each temps
    foreach($arr as $lib=>$desinence){
      $desinences = explode(',', $desinence);
      $i=0;
      $tempsConjugated = array();

      foreach ($desinences as $elmnt){
         $rootDotLess = $rootTruncated;
	 // if there are dots in the desinence they are interpreted as backspaces
      	 if (substr_count($elmnt, '.')){
       	    $rootDotLess = substr($rootTruncated, 0, -1*(int)substr_count($elmnt, '.'));
	 }
      	 $elmnt = str_replace ( '.' , '', $elmnt );
      
	 if ($this->mustNeutralizeVowel($lib,$i)){
           $rootSaved = $this->neutralizeVowel($rootDotLess,$vowelGrave);
      	 }else{
	   $rootSaved = $rootDotLess;
      	 }

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