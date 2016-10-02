<?php
/**
 * \file      ConjugationLengadocianFirstGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the first group of lengadacian verbs
*/
class ConjugationLengadocianFirstGroup extends ConjugationBase{

    /**
    * \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
    * \return an array w/ the desinences commonly used
    */
    protected function getStandardConjugation(){

        $arr = array();
        $arr['00_IndPres|Present']                 =  "i,as,a,am,atz,an";
        $arr['01_IndImp|Imperfach']                =  "avi,avas,ava,àvem,àvetz,avan";
        $arr['02_IndPret|Preterit']                =  "èri,ères,èt,èrem,èretz,èron";
        $arr['03_IndFutur|Futur']                  =  "arai,aràs,arà,arem,aretz,aràn";
        $arr['04_Infinitiu|Infinitiu']             =  "ar";
        $arr['05_Gerondiu|Gerondiu']               =  "ant";
        $arr['06_PartPassat|Participi passat']     =  "at,ada";
        $arr['07_Imperatiu|Imperatiu']             =  "a,em,atz,es,em,etz";
        $arr['08_SubPres|Subjontiu present']       =  "e,es,e,em,etz,en";
        $arr['09_SubImp|Subjontiu imperfach']      =  "èsse,èsses,èsse,èssem,èssetz,èsson";
        $arr['10_Conditional|Conditional']         =  "ariái,ariás,ariá,ariam,ariatz,arián";
        return $arr;
    } // setStandardConjugation

    /**
    * \brief does some changes inside the radical if needed for a some desinence and according to the verb model
    * \param $radical a string the radical to be altered
    * \param $desinence a string the current desinence
    * \return the radical
    */
    protected function fixRadical($radical,$desinence){
        $desinences = array('i','as','','a','an','e','es','en','ias','ia','ian');
  
        if(in_array($desinence,$desinences)){
            switch ($this->getVerbModel()){
            case '106 a' : $pattern = '/(.*)a(.+?)$/'; $replacement = '${1}à${2}'; break;
            case '106 b' : $pattern = '/(.*)e(.+?)$/'; $replacement = '${1}é${2}'; break;
            case '106 c' : $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ó${2}'; break;
            case '106 d' : $pattern = '/(.*)i(.+?)$/'; $replacement = '${1}í${2}'; break;
            case '106 e' : $pattern = '/(.*+)u(.+?)$/'; $replacement = '${1}ú${2}'; break;
            case '107 b' : 
                if (in_array($elmnt,array('e','es','en'))){
                    $pattern = '/(.*)e(.+?)$/'; $replacement = '${1}è${2}';}
                else{
                    $pattern = '//'; $replacement = '';}
                break;
            case '110'   :
            case '111'   :
            case '112'   :
            case '113'   :
            case '114'   :
            case '115'   :
            case '116 a' :
            case '116 b' :
                $pattern = '/(.*)e(.*?)$/'; $replacement = '${1}è${2}'; break;
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
                $pattern = '/(.*)o(.*?)$/'; $replacement = '${1}ò${2}'; break;
            case '156'   :
                $pattern = '/(.*)o(.*?)$/'; $replacement = '${1}ò${2}'; break;
            case '130'   :
            case '133'   :
                $pattern = '/(.*)e(.*)$/'; $replacement = '${1}iè${2}'; break;
            case '140'   :
            case '143'   :
                $pattern = '/(.*)o(.*?)$/'; $replacement = '${1}uè${2}'; break;
            case '160'   :
                $pattern = '/(.*)u(.*?)$/'; $replacement = '${1}uo${2}'; break;
            case '170'   :
            case '173'   :
                $pattern = '/(.*)u(.*?)$/'; $replacement = '${1}uè${2}'; break;
            default :
                return $radical;
            } // switch
            return preg_replace($pattern, $replacement, $radical);
        } // if
        return $radical;
    } // fixRadical
  
    /**
    * \brief sometimes a desinence can be altered this function does the change
    * \param $radical a string the radical to be altered
    * \return the desinence
    */
    protected function fixDesinence($desinence){
  
        $desinences = array('i','as','a','an','e','es','en');

        if(in_array($desinence,$desinences)){
            switch ($this->getVerbModel()){
            case '105 c' :
            case '105 d' :
            case '105 e' :
            case '115'   :
                $desinence = ($desinence=='i' ? 'ï':$desinence); break;
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

        $infinitive = $this->getVerb();

        // pronominal verbs take care to remove the pronoun
        $patterns = array();
        $patterns[0] = '/ \(s\'\)/';
        $patterns[1] = '/ \(se\)/';
        $replacements = array();
        $replacements[1] = '';
        $replacements[0] = '';
        $infinitive = preg_replace($patterns, $replacements, $infinitive);

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

        $desinenceLengths = array();
        $desinenceLengths[ConjugationBase::IND_PRESENT]="1,2,1,2,3,2";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="3,4,3,5,6,4";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="4,5,3,5,6,5";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="4,5,4,4,5,5";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="1,2,3,2,2,3";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="1,2,1,2,3,2";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="6,6,5,5,6,6";
        return $desinenceLengths;

    }

    /**
    * \brief a placeholder for the conjugate function
    */
    public function display(){
        return $this->conjugate();
    }

} // class ConjugationLengadocianFirstGroup

?>