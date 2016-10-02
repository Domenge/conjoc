<?php
/**
 * \file      ConjugationGasconThirdGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the third group of lengadocian verbs
*/
class ConjugationLengadocianThirdGroup extends ConjugationBase{

    /**
    * \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
    * \return an array w/ the desinences commonly used
    */
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

/**
* \brief this is a function that mixes a standard conjugation and the processed one
* \param $model a string of the model code
* \return an array of conjugations
/*
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
    * \brief a placeholder for the conjugate function
    */
    public function display(){
        return "ConjugationLengadocianThirdGroup $this->_name " . $this->conjugate;
    } // display
  
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

        $pattern = '/ \d{1}$/';

        if (preg_match($pattern, $infinitive)){
            $rootSaved = preg_replace('/(.+)(er \d{1}$)/', '$1', $infinitive);
            $rootSaved = preg_replace('/(.+)(re \d{1}$)/', '$1', $infinitive);
            $rootSaved = preg_replace('/(.+)(ir \d{1}$)/', '$1', $infinitive);
            $rootSaved = preg_replace('/(.+)(ne \d{1}$)/', '$1', $infinitive);
        }else{
            $rootSaved = preg_replace('/(.+)(er)/', '$1', $infinitive);
            $rootSaved = preg_replace('/(.+)(re \d{1}$)/', '$1', $infinitive);
            $rootSaved = preg_replace('/(.+)(ir \d{1}$)/', '$1', $infinitive);
            $rootSaved = preg_replace('/(.+)(ne \d{1}$)/', '$1', $infinitive);
        }

        $patterns = array();
        $patterns[2] = '/ir$/';
        $patterns[1] = '/er$/';
        $patterns[0] = '/re$/';
        $replacements = array();
        $replacements[0] = '';
        $replacements[1] = '';
        $replacements[2] = '';
        $rootTruncated = preg_replace($patterns, $replacements, $rootSaved);
        $conjugations = array();

        $rootTruncated = $this->neutralizeTonic($rootTruncated,$tonic);

        if ($model == '373'){
            // prendre
            $pattern = '/nd$/';
            $replacement = '';
            $rootTruncated = preg_replace($pattern, $replacement, $rootTruncated);
        }

        // for each temps
        $j=0;
        foreach($arr as $lib=>$desinence){
            $desinences = explode(',', $desinence);
            $i=0;
            $tempsConjugated = array();

            foreach ($desinences as $elmnt){
                $rootDotLess = $rootTruncated;
                // if there are dots in the desinence they are interpreted as backspaces
                $count = substr_count($elmnt, '.');
                if ($count){
                    $rootDotLess = substr($rootTruncated, 0, -1*(int)$count);
                }
                $elmnt = str_replace ( '.' , '', $elmnt );
      
                if ($this->mustNeutralizeVowel($lib,$i)){
                    $rootSaved = $this->neutralizeVowel($rootDotLess,$vowelGrave);
                }else{
                    $rootSaved = $rootDotLess;
                }

                $root = $this->fixRadical($rootSaved,$elmnt);
                $elmnt = $this->fixDesinence($elmnt);
                $conj = $this->phonologicFixes($root.'-'.$elmnt);
                $conj = preg_replace('/-/', '', $conj);
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
                $conjugations[] = array($infinitive);
            }else{ // if
                $conjugations[] = $tempsConjugated;
            }
            $j++;
        } // foreach temps

        return $conjugations;
    } // getConjugationArray

    /**
    * \brief does some changes inside the radical if needed for a some desinence and according to the verb model
    * \param $radical a string the radical to be altered
    * \param $desinence a string the current desinence
    * \return the radical
    */
    protected function fixRadical($radical,$desinence){
        $model = $this->getVerbModel();

//        $desinences = array('i','as','','a','on','an','e','es','en','ias','ia','ian');
  
        switch ($model){
        case '373'   :
            $pattern = '/(.*)ne$/'; $replacement = '${1}'; 
            $radical =  preg_replace($pattern, $replacement, $radical);
            break;
        // radical w/à : replacement of the a acute heritated from radical
        case '350'   :
        case '351'   :
        case '380'   :
        case '381'   :
        case '385'   :
            $pattern = '/(.*)à(.*?)$/'; $replacement = '${1}a${2}'; 
            $radical =  preg_replace($pattern, $replacement, $radical);
            break;
        } // switch

        return $radical;
        
    } // fixRadical
  
    /**
    * \brief sometimes a desinence can be altered this function does the change
    * \param $radical a string the radical to be altered
    * \return the desinence
    */
    protected function fixDesinence($desinence){
        return $desinence;
    } // fixDesinence

    /**
    * \brief returns an array w/ the length of each size of the desinence  for each tense for each person
    * \return an associative array of integers
    */
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

        if ($model == '373'){
            // prendre
            $desinenceLengths[ConjugationBase::IND_PRETERIT]="6,7,5,7,8,7";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="1,2";
            $desinenceLengths[ConjugationBase::IMPERATIVE]="0,3,4,3,3,4";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="2,3,2,3,4,3";
            $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="7,8,7,8,9,8";
            $desinenceLengths[ConjugationBase::CONDITIONAL]="6,6,5,5,6,6";

        }

        if ($model == '303'){
            // mettre
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,2";
        }
        if ($model == '313'){
            // escodre
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,3";
        }
        if ($model == '325'){
            // encendre
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,3";
        }
        if ($model == '336'){
            // conclure
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,3";
        }
        if ($model == '345'){
            // coire
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="4,5";
        }
        if ($model == '355'){
            // sorzer
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="1,2";
        }
        if ($model == '373'){
            // prene
            $desinenceLengths[ConjugationBase::INFINITIVE]="1";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,3";
            $desinenceLengths[ConjugationBase::IND_FUTURE]="4,5,4,4,5,5";
        }

        return $desinenceLengths;

    } // getDesinenceLengthArray
  
} // class ConjugationLengadocianThirdGroup

?>