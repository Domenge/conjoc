<?php
/**
 * \file      ConjugationGasconSecondGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the second group of gascon verbs
*/
class ConjugationGasconSecondGroup extends ConjugationBase{

      /**
      * \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
      * \return an array w/ the desinences commonly used
      */
   protected function getStandardConjugation(){
        $arr = array();
        $model = $this->getVerbModel();

        if ($model == '250' || $model == '252' || $model == '253'  || $model == '254'){
            $arr['00_IndPres|Present']                 =  ($model == '254')?"i,es,e,im,itz,en":"i,es,,im,itz,en";
            $arr['01_IndImp|Imperfach']                =  "ivi,ivas,iva,ívam,ívatz,ivan";
            $arr['02_IndPret|Preterit']                =  "ii,ís,í,im,itz,ín";
            $arr['03_IndFutur|Futur']                  =  "irèi,iràs,irà,iram,iratz,iràn";
            $arr['04_Infinitiu|Infinitiu']             =  "ir";
            $arr['05_Gerondiu|Gerondiu']               =  "int";
            $arr['06_PartPassat|Participi passat']     =  ($model == '254')?"èrt,èrta":"it,ida";
            $arr['07_Imperatiu|Imperatiu']             =  ($model == '254')?"e,im,itz,ias,iam,iatz":",im,itz,ias,iam,iatz";
            $arr['08_SubPres|Subjontiu present']       =  "i,ias,ia,iam,iatz,ian";
            $arr['09_SubImp|Subjontiu imperfach']      =  "issi,isses,isse,íssem,íssetz,issen";
            $arr['10_Conditional|Conditional']         =  "irí,irés,iré,irem,iretz,irén";
            return $arr;
        }

        if ( $model == '212' || $model == '213'){
            $arr['00_IndPres|Present']                 =  "eïshi,eïshes,eísh,eïshem,eïshetz,eïshen";
            $arr['01_IndImp|Imperfach']                =  "ïvi,ïvas,ïva,ívam,ívatz,ïvan";
            $arr['02_IndPret|Preterit']                =  "ii,ís,í,im,itz,ín";
            $arr['03_IndFutur|Futur']                  =  "ïrèi,ïràs,ïrà,ïram,ïratz,ïràn";
            $arr['04_Infinitiu|Infinitiu']             =  "ir";
            $arr['05_Gerondiu|Gerondiu']               =  "ïnt";
            $arr['06_PartPassat|Participi passat']     =  "ït,ïda";
            $arr['07_Imperatiu|Present positiu/present negatiu'] =  "eish,ïm,ïtz,escas,escam,escatz";
            $arr['08_SubPres|Subjontiu present']       =  "esqui,escas,esca,escam,escatz,escan";
            $arr['09_SubImp|Subjontiu imperfach']      =  "ïssi,ïsses,ïsse,íssem,íssetz,ïssen";
            $arr['10_Conditional|Conditional']         =  "ïrí,ïrés,ïré,ïrem,ïretz,ïrén";
            return $arr;
        }

        $arr['00_IndPres|Present']                 =  "eishi,eishes,eísh,eishem,eishetz,eishen";
        $arr['01_IndImp|Imperfach']                =  "ivi,ivas,iva,ívam,ívatz,ivan";
        $arr['02_IndPret|Preterit']                =  "ii,ís,í,im,itz,ín";
        $arr['03_IndFutur|Futur']                  =  "irèi,iràs,irà,iram,iratz,iràn";
        $arr['04_Infinitiu|Infinitiu']             =  "ir";
        $arr['05_Gerondiu|Gerondiu']               =  "int";
        $arr['06_PartPassat|Participi passat']     =  "it,ida";
        $arr['07_Imperatiu|Present positiu/present negatiu'] = "eish,im,itz,escas,escam,escatz";
        $arr['08_SubPres|Subjontiu present']       =  "esqui,escas,esca,escam,escatz,escan";
        $arr['09_SubImp|Subjontiu imperfach']      =  "issi,isses,isse,íssem,íssetz,issen";
        $arr['10_Conditional|Condicional']         =  "irí,irés,iré,irem,iretz,irén";

        if ($model == '220'){
            $arr['06_PartPassat|Participi passat']     =  "èrt,èrta";
        }
        if ($model == '230'){
            $arr['06_PartPassat|Participi passat']     =  "òrt,òrta";
        }
  
        return $arr;
    } // getStandardConjugation

    /**
    * \brief does some changes inside the radical if needed for a some desinence and according to the verb model
    * \param $radical a string the radical to be altered
    * \param $desinence a string the current desinence
    * \return the radical
    */
    protected function fixRadical($radical,$desinence){

        $desinences = array('i','as','','a','an','e','es','en','ias','ia','ian');

        $model = $this->getVerbModel();
  
        if(in_array($desinence,$desinences)){
            switch ($model){
            case '250' : 
                $pattern = '/(.*)e(.+?)$/'; 
                if(preg_match($pattern,$radical)){
                    $replacement = '${1}é${2}';
                    $radical = preg_replace($pattern, $replacement, $radical);
                    return $radical;
                }
                $pattern = '/(.*)a(.+?)$/'; 
                if(preg_match($pattern,$radical)){
                    $replacement = '${1}à${2}';
                    $radical = preg_replace($pattern, $replacement, $radical);
                    return $radical;
                }
                $pattern = '/(.*)u(.+?)$/'; 
                if(preg_match($pattern,$radical)){
                    $replacement = '${1}ú${2}';
                    $radical = preg_replace($pattern, $replacement, $radical);
                    return $radical;
                }
                $pattern = '/(.*)o(.+?)$/'; 
                if(preg_match($pattern,$radical)){
                    $replacement = $replacement = '${1}ó${2}';
                    $radical = preg_replace($pattern, $replacement, $radical);
                    return $radical;
                }

            case '252' : $pattern = '/(.*)e(.+?)$/'; $replacement = '${1}è${2}'; break;
            case '253' : $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
            case '254' : $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
            default :
                return $radical;
            } // switch

        } // if

        if (($model == '220' || $model == '254')&& ($desinence == 'èrt' || $desinence == 'èrta') ){
            $radical = preg_replace('/r$/', '', $radical);      
        }
        if ($model == '230'&& ($desinence == 'òrt' || $desinence == 'òrta') ){
            $radical = preg_replace('/or$/', '', $radical);      
        }
        return $radical;
    } // fixRadical
  
    /**
    * \brief sometimes a desinence can be altered this function does the change
    * \param $desinence a string the desinence to be altered
    * \return the desinence
    */
    protected function fixDesinence($desinence){
        $model = $this->getVerbModel();
        if ($model == '213'){
            $desinence = preg_replace('/iss/', 'ïss', $desinence);      
        }
        return $desinence;
    } // fixDesinence

    /**
    * \brief the most important function, returns the data for conjugating the current verb
    * \return an array
    */
    protected function getConjugationArray(){
        $infinitive = $this->getVerb();

        $rootSaved =  $infinitive;

        if (preg_match('/.+ \d{1}$/', $infinitive)){
            $rootSaved = preg_replace('/(.+) \d{1}$/', '$1', $infinitive);
        }

        if (preg_match('/.*ir$/', $rootSaved)){
            $rootSaved = preg_replace('/(.+)ir$/', '$1', $rootSaved);
        }

        if (preg_match('/.*ïr$/', $rootSaved)){
            $rootSaved = preg_replace('/(.+)ïr$/', '$1', $rootSaved);
        }
        // clean up radical

        $conjugations = array();

        $i=0;
        
        // for each temps
        foreach($this->getStandardConjugation() as $lib=>$desinence){
            $desinences = explode(',', $desinence);
            $tempsConjugated = array();

            $model = $this->getVerbModel();
            foreach ($desinences as $elmnt){
                if (! ($model == '250' && $i == ConjugationBase::IND_PRESENT)){
                    $root = $this->fixRadical($rootSaved,$elmnt);
                }else{
                    $root = $rootSaved;
                }
                $elmnt = $this->fixDesinence($elmnt);
                $tempsConjugated[] = $root.$elmnt;
            } // for desinences
            $conjugations[] = $tempsConjugated;
            $i++;
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
        $desinenceLengths[ConjugationBase::IND_PRESENT]="4,5,2,5,6,5";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="3,4,3,5,6,4";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="1,3,2,2,3,3";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="5,5,4,4,5,5";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="3";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="3,2,3,5,5,6";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="5,5,4,5,6,5";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="4,5,4,6,7,5";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="4,5,4,4,5,5";

        switch($model){
        case '212':
        case '213':
            $desinenceLengths[ConjugationBase::IND_PRESENT]   ="4,5,2,5,6,5";
            $desinenceLengths[ConjugationBase::IND_IMPERFECT] ="4,5,4,5,6,5";
            $desinenceLengths[ConjugationBase::IMPERATIVE]    ="3,3,4,5,5,6";
            $desinenceLengths[ConjugationBase::IND_FUTURE]    ="6,6,5,5,6,6";
            $desinenceLengths[ConjugationBase::IND_PRETERIT]  ="2,3,2,2,3,3";
            $desinenceLengths[ConjugationBase::INFINITIVE]    ="2";
            $desinenceLengths[ConjugationBase::GERUND]        ="4";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,4";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="5,5,4,5,6,5";
            $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,6,5,6,7,6";
            $desinenceLengths[ConjugationBase::CONDITIONAL]="5,6,5,5,6,6";
            break;
        case '220' :
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="4,5";
            break;
        case '230':
            $desinenceLengths[ConjugationBase::IND_PRETERIT]="2,3,2,2,3,3";
            $desinenceLengths[ConjugationBase::IND_FUTURE]="5,5,4,4,5,5";
            break;
        case '250':
        case '252':
        case '253':
            $desinenceLengths[ConjugationBase::IND_PRESENT]   ="1,2,0,2,3,2";
            $desinenceLengths[ConjugationBase::IND_IMPERFECT] ="3,4,3,5,6,4";
            $desinenceLengths[ConjugationBase::IND_PRETERIT]  ="2,3,2,2,3,3";
            $desinenceLengths[ConjugationBase::IND_FUTURE]    ="5,5,4,4,5,5";
            $desinenceLengths[ConjugationBase::IMPERATIVE]    ="0,2,3,3,3,4";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]  ="1,3,2,3,4,3";
            break;
        case '254':
            $desinenceLengths[ConjugationBase::IND_IMPERFECT] ="3,4,3,5,6,4";
            $desinenceLengths[ConjugationBase::IND_PRETERIT]  ="2,3,2,2,3,3";
            $desinenceLengths[ConjugationBase::IND_FUTURE]    ="5,5,4,4,5,5";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]  ="1,3,2,3,4,3";
            $desinenceLengths[ConjugationBase::IND_PRESENT]   ="1,2,1,2,3,2";
            $desinenceLengths[ConjugationBase::IMPERATIVE]    ="1,2,3,3,3,4";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="4,5";
            break;
        } // switch
        return $desinenceLengths;

    } // getDesinenceLengthArray

    /**
    * \brief a placeholder for the conjugate function
    */
    public function display(){
        return array();
    } // display
} // class ConjugationGasconSecondGroup

?>