<?php
/**
 * \file      ConjugationProvencalFirstGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the first group of provencal verbs
 *
 */
class ConjugationProvencalFirstGroup extends ConjugationBase{

    /**
     * \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
     * \return an array w/ the desinences commonly used
     */
    protected function getStandardConjugation(){

        $arr = array();
        $arr[] = "i,as,a,am,atz,an";
        $arr[] = "avi,avas,ava,àvam,àvatz,avan";
        $arr[] = "èi,ès,è,èm,ètz,èn";
        $arr[] = "arèi,aràs,arà,aram,aratz,aràn";
        $arr[] = "ar";
        $arr[] = "ant";
        $arr[] = "at,ada";
        $arr[] = "a,em,atz,es,em,etz";
        $arr[] = "i,es,e,em,etz,en";
        $arr[] = "èssi,èsses,èsse,èssem,èssetz,èssen";
        $arr[] = "arí,arés,aré,arem,aretz,arén";
    
        return $arr;

    } // setStandardConjugation

    /**
     * \brief does some changes inside the radical if needed for a some desinence and according to the verb model
     * \param $radical a string the radical to be altered
     * \param $desinence a string the current desinence
     * \return the radical
     */
    protected function fixRadical($radical,$desinence){
        //    $radical = $this->phonologicFixes($radical);
        // present indicative and present subjunctive
        $desinences = array('i','as','','a','an','e','es','en','ias','ia','ian');
  
        if(in_array($desinence,$desinences)){
            switch ($this->getModel()){
            case '106 a' : $pattern = '/(.+?)a(.+?)$/'; $replacement = '${1}à${2}'; break;
                //      case '106 b' : $pattern = '/(.+?)e(.+?)$/'; $replacement = '${1}é${2}'; break;
                //      case '106 c' :
            case '106 d' : $pattern = '/(.+?)i(.+?)$/'; $replacement = '${1}í${2}'; break;
            case '106 e' : $pattern = '/(.+?)u(.+?)$/'; $replacement = '${1}ú${2}'; break;
            case '107 b' : 
                if (in_array($desinence,array('e','es','en'))){
                    //drupal_set_message("$desinence"); 
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
                $pattern = '/(.+)e(.+?)$/'; $replacement = '${1}è${2}'; break;
            case '120'   :
            case '121'   :
            case '122'   :
            case '123'   :
            case '124'   :
            case '125'   :
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
        }

        return $radical;
    } // fixRadical
  
    /**
     * \brief sometimes a desinence can be altered this function does the change
     * \param $desinence a string the desinence to be altered
     * \return the desinence
     */
    protected function fixDesinence($desinence){
  
        $desinences = array('i','as','a','an','e','es','en');

        if(in_array($desinence,$desinences)){
            switch ($this->getModel()){
            case '107 a' :   // Attention dar,  di becomes dau
                $desinence = ($desinence=='i' ? 'au':$desinence); break;
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

        $infinitive = $this->getName();

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

    }

    /**
     * \brief a placeholder for the conjugate function
     */
    public function display(){
        return $this->conjugate();
    }

} // class ConjugationProvencalFirstGroup

?>