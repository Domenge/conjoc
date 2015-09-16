<?php


class ConjugationLengadocianAuxilliary extends ConjugationBase{

  public function display(){
    return array();
  } // display

  public function getConjugationArray(){
    $infinitive = $this->getVerb();
    	
    // treatment of verb «FAR»
    // the prefix to the verb FAR for exemple 'des' in desfar
    // is added to all the conjugations
    $rootVerb = '';
    if ($this->getVerbModel() == '004'){
      $rootVerb = $this->getManager()->getVerbFar($infinitive);
    } //far
                
    $conjugations = explode('|', $this->getConjugations());

    // for each temps    
    foreach($conjugations as $desinence){
      // we get rid of the first part of the desinence 
      $ary = explode(':', $desinence);
      $desinences = explode(',', $ary[1]);
      $tempsConjugated = array();
      foreach ($desinences as $elmnt){
        $tempsConjugated[] = $rootVerb.$elmnt; 
      } // for desinences
      $retconjugations[] = $tempsConjugated;
    } // foreach temps

    return $retconjugations;
  } // getConjugationArray

} // class ConjugationLengadocianAuxilliary
?>