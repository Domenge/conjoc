<?php
/**
 * \file      ConjugationGasconThirdGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the third group of gascon verbs
*/
class ConjugationGasconThirdGroup extends ConjugationBase{
    /**
    * \brief this is a try to implement a special behaviour of monosyllabic verbs in gascon
    * \return an array of infinitives
    */
    protected function getVerbsMonoSyllabics(){
        $arr = array();
        $arr[] =  "bater";
        return $arr;
    } // getVerbsMonoSylabics

    /**
    * \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
    * \return an array w/ the desinences commonly used
    */
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

    /**
    * \brief does some changes inside the radical if needed for a some desinence and according to the verb model
    * \param $radical a string the radical to be altered
    * \param $desinence a string the current desinence
    * \return the radical
    */
   protected function fixRadical($radical,$desinence){
        return $radical;
    } // fixRadical
  
    /**
    * \brief sometimes a desinence can be altered this function does the change
    * \param $desinence a string the desinence to be altered
    * \return the desinence
    */
    protected function fixDesinence($desinence){
        return $desinence;
    } // fixDesinence

    /**
    * \param $temps the tense
    * \param $person
    * \return a boolean
    */ 
    protected function mustNeutralizeVowel($temps,$person){
        return true;
    } // mustNeutralizeVowel

    /**
    * \brief this function mixes the standard conjugation and the processed one
    * \param $model the model
    * \return an array
    */
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

   /**
   * \brief the most important function, returns the data for conjugating the current verb
   * \return an array
   */
   protected function getConjugationArray(){

        $infinitive = $this->getVerb();
        $vowelGrave = $this->isVowelDetected($infinitive);
        $tonic = $this->isTonicDetected($infinitive);
        $model = $this->getVerbModel();
        $arr = $this->getMixedConjugation($model);

        // clean the index
        $rootTruncated = preg_replace('/(.+) \d{1}$/', '$1', $infinitive);
        $infinitiveSaved = $rootTruncated;
        $patterns = array();
        $patterns[1] = '/er$/';
        $patterns[0] = '/re$/';
        $replacements = array();
        $replacements[1] = '';
        $replacements[0] = '';
        $rootTruncated = preg_replace($patterns, $replacements, $rootTruncated);
        $conjugations = array();

        $rootTruncated = $this->neutralizeTonic($rootTruncated,$tonic);

        $model = $this->getVerbModel();

        // for each temps
        $j = 0;
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

                if (! ($model == '305' && $j == ConjugationBase::IND_PRESENT)){
                    $root = $this->fixRadical($rootSaved,$elmnt);
                }else{
                    $root = $rootSaved;
                }

                $elmnt = $this->fixDesinence($elmnt);
                $conj = $root.$elmnt;

                // impersonal verbs

                if($model=='390' && ($rootSaved == 'cal' || $rootSaved == 'fal')){
                    $conjSaved = $conj;
                    $conj=($i==2)?$conj:"";
                    $conj=($j == ConjugationBase::GERUND || $j == ConjugationBase::PAST_PARTICIPLE)?$conjSaved:$conj;
                    $conj=($j == ConjugationBase::IMPERATIVE)?"":$conj;
                }

                $tempsConjugated[] = $conj;
                $i++;
            } // for desinences
            if ($j == ConjugationBase::INFINITIVE){ //
                $conjugations[] = array($infinitiveSaved);
            }else{ // if
                $conjugations[] = $tempsConjugated;
            }
            $j++;
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
        $desinenceLengths[ConjugationBase::IND_PRESENT]="1,2,0,2,3,2";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]   ="4,5,4,5,6,5";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]    ="2,3,2,2,3,3";
        $desinenceLengths[ConjugationBase::IND_FUTURE]      ="5,5,4,4,5,5";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]      ="0,2,3,3,3,4";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]    ="1,3,2,3,4,3";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]  ="4,5,4,6,7,5";
        $desinenceLengths[ConjugationBase::CONDITIONAL]     ="4,5,4,4,5,5";


        switch($model){
        case '303' :
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
            break;
        case '307' :
            $desinenceLengths[ConjugationBase::IMPERATIVE]      ="0,2,3,2,2,3";
            break;
        case '311' :
            $desinenceLengths[ConjugationBase::IMPERATIVE]      ="3,3,4,3,3,4";
            break;
        case '371 a' :
            $desinenceLengths[ConjugationBase::IND_IMPERFECT]   ="4,0,0,3,4,0";
            break;
        case '373':
            $desinenceLengths[ConjugationBase::IND_PRETERIT]="6,7,5,7,8,7";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="1,2";
            $desinenceLengths[ConjugationBase::IMPERATIVE]="0,3,4,3,3,4";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,3,2,3,4,3";
            $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="7,8,7,8,9,8";
            $desinenceLengths[ConjugationBase::CONDITIONAL]="6,6,5,5,6,6";
            break;
        } // switch

        return $desinenceLengths;

    } // getDesinenceLengthArray


    /**
    * \brief a placeholder for the conjugate function
    */
    public function display(){
        return "ConjugationGasconThirdGroup $this->_name " . $this->conjugate;
    } // display
} // class ConjugationGasconThirdGroup

?>