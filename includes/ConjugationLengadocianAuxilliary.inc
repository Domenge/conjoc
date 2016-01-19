<?php


class ConjugationLengadocianAuxilliary extends ConjugationBase{

    public function display(){
        return array();
    } // display

    public function getConjugationArray(){
        $infinitive = $this->getVerb();
        $model = $this->getVerbModel();
        // treatment of verb «FAR»
        // the prefix to the verb FAR for exemple 'des' in desfar
        // is added to all the conjugations
        $rootVerb = '';

        if ($model == '004'){
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
                // correction for the verb "far" monosyllabic
                if($model == '004' && $rootVerb == ''){
                    switch($elmnt){
                    case 'fàs' : $elmnt = 'fas'; break;
                    case 'fàn' : $elmnt = 'fan'; break;
                    case 'fà' : $elmnt = 'fa'; break;       
                    }
                }
                $tempsConjugated[] = $rootVerb.$elmnt; 
            } // for desinences
            $retconjugations[] = $tempsConjugated;
        } // foreach temps

        return $retconjugations;
    } // getConjugationArray

    protected function getDesinenceLengthArray(){

        $model = $this->getVerbModel();

        $desinenceLengths = array();
        $desinenceLengths[ConjugationBase::IND_PRESENT]="1,2,0,2,3,2";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="4,4,3,3,4,4";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="4,5,3,5,6,5";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="3,4,3,3,4,4";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="0,2,4,2,2,3";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="1,2,1,2,3,2";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="5,5,4,4,5,5";

        if ($model == '001'){

            $desinenceLengths[ConjugationBase::IND_IMPERFECT]="2,3,2,3,4,3";
            $desinenceLengths[ConjugationBase::IMPERATIVE]="2,2,3,3,2,3";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,3,2,2,3,3";
            $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
            $desinenceLengths[ConjugationBase::CONDITIONAL]="5,5,4,4,5,5";
	
        }
        return $desinenceLengths;

    } // getDesinenceLengthArray

} // class ConjugationLengadocianAuxilliary
?>