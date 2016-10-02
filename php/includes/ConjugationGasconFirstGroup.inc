<?php
/**
 * \file      ConjugationGasconFirstGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the first group of gascon verbs
*/
class ConjugationGasconFirstGroup extends ConjugationBase{

/**
* \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
* \return an array w/ the desinences commonly used
*/
protected function getStandardConjugation(){

        $model = $this->getVerbModel();

        $arr = array();
        // present indicative
        switch($model){
        case '107 a': $arr[ConjugationBase::IND_PRESENT] = "au,as,a,am,atz,an"; break;
        case '107 b': $arr[ConjugationBase::IND_PRESENT] = "au,às,à,am,atz,àn"; break;
        default: $arr[ConjugationBase::IND_PRESENT] = "i,as,a,am,atz,an";
        }

        // imperfect indicative
        $arr[ConjugationBase::IND_IMPERFECT] = "avi,avas,ava,àvam,àvatz,avan";
        // preterit indicative
        $arr[ConjugationBase::IND_PRETERIT] = "èi,ès,è,èm,ètz,èn";
        // future indicative
        $arr[ConjugationBase::IND_FUTURE] = "arèi,aràs,arà,aram,aratz,aràn";
        $arr[ConjugationBase::INFINITIVE] = "ar";
        $arr[ConjugationBase::GERUND] = "ant";
        $arr[ConjugationBase::PAST_PARTICIPLE] = "at,ada";
        // imperative
        if ($model == '107 b'){
            $arr[ConjugationBase::IMPERATIVE] = "à,am,atz,és,em,etz";
        }else{
        $arr[ConjugationBase::IMPERATIVE] = "a,em,atz,es,em,etz";
        }
        // present subjonctive 
        switch($model){
        case '107 a': $arr[ConjugationBase::SUBJ_PRESENT] = "ei,es,é,em,etz,en"; break;
        case '107 b': $arr[ConjugationBase::SUBJ_PRESENT] = "ei,és,é,em,etz,én";; break;
        default: $arr[ConjugationBase::SUBJ_PRESENT] = "i,es,e,em,etz,en";
        }
        $arr[ConjugationBase::SUBJ_IMPERFECT] = "èssi,èsses,èsse,èssem,èssetz,èssen";
        $arr[ConjugationBase::CONDITIONAL] = "arí,arés,aré,arem,aretz,arén";
    
        return $arr;

    } // getStandardConjugation

    /**
    * \brief does some changes inside the radical if needed for a some desinence and according to the verb model
    * \param $radical a string the radical to be altered
    * \param $desinence a string the current desinence
    * \return the radical
    */
    protected function fixRadical($radical,$desinence){
        //$radical = $this->phonologicFixes($radical);
        // present indicative and present subjunctive
        $desinences = array('i','as','','a','an','e','es','en','ias','ia','ian');
  
        if(in_array($desinence,$desinences)){
            switch ($this->getVerbModel()){
            case '106 a' : $pattern = '/(.+)a(.+?)$/'; $replacement = '${1}à${2}'; break;
            case '106 b' : $pattern = '/(.+)e(.+?)$/'; $replacement = '${1}é${2}'; break;
            case '106 c' : $pattern = '/(.+)o(.+?)$/'; $replacement = '${1}ó${2}'; break;
            case '106 d' : $pattern = '/(.+)i(.+?)$/'; $replacement = '${1}í${2}'; break;
            case '106 e' : $pattern = '/(.+)u(.+?)$/'; $replacement = '${1}ú${2}'; break;
            case '107 b' : 
                if (in_array($desinence,array('e','es','en'))){
                    $pattern = '/(.*?)e(.+?)$/'; $replacement = '${1}è${2}';}
                else{
                    $pattern = '//'; $replacement = '';}
                break;
            case '110'   :
            case '111'   :
            case '112'   :
            case '113'   :
            case '114'   :
            case '115'   :
            case '116'   :
            case '116 a'   :
                $pattern = '/(.+)e(.+?)$/'; $replacement = '${1}è${2}'; break;
            case '120'   :
            case '121'   :
            case '122'   :
            case '123'   :
            case '124'   :
            case '125'   :
            case '126'   :
            case '126 a' :
            case '126 b' :
            case '150'   :
            case '154'   :
                $pattern = '/(.+)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
            case '156'   :
                $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
            case '130'   :
                $pattern = '/(.+)e(.+?)$/'; $replacement = '${1}iè${2}'; break;
            case '140'   :
            case '143'   :
                $pattern = '/(.+)o(.+?)$/'; $replacement = '${1}uè${2}'; break;
            case '160'   :
                $pattern = '/(.+)u(.+?)$/'; $replacement = '${1}uo${2}'; break;
            case '170'   :
            case '173'   :
                $pattern = '/(.+)u(.+?)$/'; $replacement = '${1}uè${2}'; break;
            default :
                return $radical;
            }
            return preg_replace($pattern, $replacement, $radical);
        } // if in array
        return $radical;
    } // fixRadical
  
    /**
    * \brief sometimes a desinence can be altered this function does the change
    * \param $desinence a string the radical to be altered
    * \return the desinence
    */
    protected function fixDesinence($desinence){
  
        $desinences = array('i','as','a','an','e','es','en');

        if(in_array($desinence,$desinences)){
            switch ($this->getVerbModel()){
            case '105 a' :   // Attention crear,  crei becomes creï
            case '105 b' :   // Attention tuar,  tui becomes tuï
            case '105 c' :   // Attention entinoar,  entinoi becomes entinoï
            case '105 e' :   // Attention tuar,  tui becomes tuï
                $desinence = ($desinence=='i' ? 'ï':$desinence); break;
            case '107 b' :   // Attention estar,  estid becomes estau
                $desinence = ($desinence=='i' ? 'au':$desinence);
                $desinence = ($desinence=='as' ? 'às':$desinence);
                $desinence = ($desinence=='a' ? 'à':$desinence);
                $desinence = ($desinence=='an' ? 'àn':$desinence);
            }
        }        
        return $desinence;
    } // fixDesinence

    /**
    * \brief the most important function, returns the data for conjugating the current verb
    * \return an array
    */
    protected function getConjugationArray(){

        $infinitive = $this->getVerb();

        $pattern = '/ \d{1}$/';

        if (preg_match($pattern, $infinitive)){
            $rootSaved = preg_replace('/(.+)(ar \d{1}$)/', '$1', $infinitive);
        }else{
            $rootSaved = preg_replace('/(.+)(ar)/', '$1', $infinitive);
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
                $conj = $this->phonologicFixes($root.'-'.$elmnt);
                $conj = preg_replace('/-/', '', $conj);
                $tempsConjugated[] = $conj; 
            } // for desinences
            $conjugations[] = $tempsConjugated;
        } // foreach temps

        return $conjugations;

    } // getConjugationArray

    /**
    * \brief returns an array w/ the length of each size of the desinence  for each tense for each person
    * \return an associative array of integers
    */
    protected function getDesinenceLengthArray(){

        $model = $this->getVerbModel();

        $desinenceLengths = array();
        $desinenceLengths[ConjugationBase::IND_PRESENT]="1,2,1,2,3,2";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="3,4,3,5,6,4";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="3,3,2,3,4,3";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="5,5,4,4,5,5";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="1,2,3,2,2,3";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="1,2,1,2,3,2";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="4,5,4,4,5,5";

        if ($model == '101'){
            $desinenceLengths[ConjugationBase::CONDITIONAL]="6,7,6,6,7,7";
        }
        if ($model == '105 a' ||$model == '105 b' || $model == '105 c' || $model == '105 c'  || $model == '105 e'){
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,2,1,2,3,2";
        }
        if ($model == '107 a'){
            $desinenceLengths[ConjugationBase::IND_PRESENT]="2,2,1,2,3,2";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,2,1,2,3,2";
         }
        if ($model == '110'){
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,2,1,2,3,2";
         }
        if ($model == '107 a'){
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,2,3,2,3,2";
         }
        if ($model == '107 b'){
            $desinenceLengths[ConjugationBase::IND_PRESENT]="2,2,1,2,3,2";
            $desinenceLengths[ConjugationBase::IMPERATIVE]="2,2,3,3,2,3";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,3,2,2,3,3";
            $desinenceLengths[ConjugationBase::CONDITIONAL]="4,5,4,4,5,5";
         }

        return $desinenceLengths;

    }

    /**
    * \brief a placeholder for the conjugate function
    */
    public function display(){
        return $this->conjugate();
    }

} // class ConjugationGasconFirstGroup

?>