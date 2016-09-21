<?php
class ConjugationGasconAuxilliary extends ConjugationBase{

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
      $rootVerb = $this->getManager()->getVerbHar($infinitive);
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

  protected function getDesinenceLengthArray(){

        $model = $this->getVerbModel();

        $desinenceLengths = array();
        $desinenceLengths[ConjugationBase::IND_PRESENT]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::INFINITIVE]="0";
        $desinenceLengths[ConjugationBase::GERUND]="0";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="0,0";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="0,0,0,0,0,0";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="0,0,0,0,0,0";
       
        if ($model == '001'){
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="2,3,2,2,3,3";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="4,5,4,6,7,5";
        }
        if ($model == '002'){
        $desinenceLengths[ConjugationBase::IND_PRESENT]="0,0,0,2,3,0";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="4,5,4,5,6,5";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="2,3,2,2,3,3";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="4,5,4,6,7,5";
        }
        if ($model == '003'){
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="3,4,3,5,6,4";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="3,3,2,3,4,3";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="5,5,4,4,5,5";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="0,2,3,0,2,3";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="1,2,1,2,3,2";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="4,5,4,4,5,5";
        }
        if ($model == '004'){
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="5,6,5,6,7,6";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="3,4,3,3,4,4";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="3,3,2,2,3,3";
        $desinenceLengths[ConjugationBase::GERUND]="2";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="0,0,0,4,4,5";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,4,3,4,5,4";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="3,4,3,3,4,4";
        }
        return $desinenceLengths;

    } // getDesinenceLengthArray

} // class ConjugationGasconAuxilliary
?>