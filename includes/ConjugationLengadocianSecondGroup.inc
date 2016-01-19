<?php

class ConjugationLengadocianSecondGroup extends ConjugationBase{

    protected function getStandardConjugation(){

        $arr = array();
        $model = $this->getVerbModel();
   
        if ($model == '230' || $model == '250' || $model == '251'){
            $arr['00_IndPres|Present']                 =  "i,es,,èm,ètz,on";
            $arr['01_IndImp|Imperfach']                =  "iái,iás,iá,iam,iatz,ián";
            $arr['02_IndPret|Preterit']                =  "iguèri,iguères,iguèt,iguèrem,iguèretz,iguèron";
            $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
            $arr['04_Infinitiu|Infinitiu']             =  "ir";
            $arr['05_Gerondiu|Gerondiu']               =  "issent";
            $arr['06_PartPassat|Participi passat']     =  "it,ida";
            if ($model == '230' || $model == '251'){
                $arr['06_PartPassat|Participi passat']     =  "òrt,òrta";
            }

            $arr['07_Imperatiu|Imperatiu']             =  ",am,ètz,iscas,iscam,iscatz";

            if ($model == '230' || $model == '251'){
                $arr['07_Imperatiu|Imperatiu']             =  ",am,ètz,a,am,atz";
            }

            $arr['08_SubPres|Subjontiu present']       =  "a,as,a,am,atz,an";
            $arr['09_SubImp|Subjontiu imperfach']      =  "iguèsse,iguèsses,iguèsse,iguèssem,iguèssetz,iguèsson";
            $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";
            return $arr;
        }
        if ($model == '210' || $model == '211' || $model == '212' || $model == '213'){
            $arr['00_IndPres|Present']                 =  "ïssi,ïsses,ís,ïssèm,ïssètz,ïsson";
            $arr['01_IndImp|Imperfach']                =  "ïssiái,ïssiás,ïssiá,ïssiam,ïssiatz,ïssián";
            $arr['02_IndPret|Preterit']                =  "ïguèri,ïguères,ïguèt,ïguèrem,ïguèretz,ïguèron";
            $arr['03_IndFutur|Futur']                  =  "ïrai,ïràs,ïrà,ïrem,ïretz,ïràn";
            $arr['04_Infinitiu|Infinitiu']             =  "ïr";
            $arr['05_Gerondiu|Gerondiu']               =  "ïssent";
            $arr['06_PartPassat|Participi passat']     =  "ït,ida";
            $arr['07_Imperatiu|Imperatiu']             =  "ís,ïscam,ïssètz,ïscas,ïscam,ïscatz";
            $arr['08_SubPres|Subjontiu present']       =  "ïsca,ïscas,ïsca,ïscam,ïscatz,ïscan";
            $arr['09_SubImp|Subjontiu imperfach']      =  "ïguèsse,ïguèsses,ïguèsse,ïguèssem,ïguèssetz,ïguèsson";
            $arr['10_Conditional|Conditional']         =  "ïriái,ïriás,ïriá,ïriam,ïriatz,ïrián";
            return $arr;
        }

        $arr['00_IndPres|Present']                 =  "issi,isses,ís,issèm,issètz,isson";
        $arr['01_IndImp|Imperfach']                =  "issiái,issiás,issiá,issiam,issiatz,issián";
        $arr['02_IndPret|Preterit']                =  "iguèri,iguères,iguèt,iguèrem,iguèretz,iguèron";
        $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
        $arr['04_Infinitiu|Infinitiu']             =  "ir";
        $arr['05_Gerondiu|Gerondiu']               =  "issent";
        $arr['06_PartPassat|Participi passat']     =  "it,ida";
        $arr['07_Imperatiu|Imperatiu']             =  "ís,iscam,issètz,iscas,iscam,iscatz";
        $arr['08_SubPres|Subjontiu present']       =  "isca,iscas,isca,iscam,iscatz,iscan";
        $arr['09_SubImp|Subjontiu imperfach']      =  "iguèsse,iguèsses,iguèsse,iguèssem,iguèssetz,iguèsson";
        $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";

        if ($model == '220'){
            $arr['06_PartPassat|Participi passat']     =  "èrt,èrta";
        }

        if ($model == '230'){
            $arr['06_PartPassat|Participi passat']     =  "òrt,òrta";
        }

        return $arr;
    } // getStandardConjugation

    protected function getConjugationArray(){

        $infinitive = $this->getVerb();

        $pattern = '/ \d{1}$/';

        if (preg_match($pattern, $infinitive)){
            $rootSaved = preg_replace('/^(.+?)(ir \d{1}$)/', '$1', $infinitive);
        }else{
            $rootSaved = preg_replace('/^(.+)(ir)$/', '$1', $infinitive);
        }

        $pattern = '/^(.+)(ïr)$/';

        if (preg_match($pattern, $rootSaved)){
            $rootSaved = preg_replace($pattern, '$1', $rootSaved);
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

    public function display(){
        return array();
    } // display

    protected function getDesinenceLengthArray(){

        $model = $this->getVerbModel();

        $desinenceLengths = array();
        $desinenceLengths[ConjugationBase::IND_PRESENT]="4,5,3,6,7,5";
        $desinenceLengths[ConjugationBase::IND_IMPERFECT]="7,4,7,6,7,7";
        $desinenceLengths[ConjugationBase::IND_PRETERIT]="7,8,6,8,9,8";
        $desinenceLengths[ConjugationBase::IND_FUTURE]="4,5,4,4,5,5";
        $desinenceLengths[ConjugationBase::INFINITIVE]="2";
        $desinenceLengths[ConjugationBase::GERUND]="6";
        $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
        $desinenceLengths[ConjugationBase::IMPERATIVE]="3,5,6,5,5,6";
        $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="4,5,4,5,6,5";
        $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="8,9,8,9,10,9";
        $desinenceLengths[ConjugationBase::CONDITIONAL]="6,6,5,5,6,6";
    
        if ($model == '250' || $model == '251'){
            $desinenceLengths[ConjugationBase::IND_PRESENT]   ="1,2,0,2,3,2";
            $desinenceLengths[ConjugationBase::IND_IMPERFECT] ="4,4,3,3,4,4";
            $desinenceLengths[ConjugationBase::IMPERATIVE]    = "0,2,4,5,5,6";
            if ($model == '251'){
                $desinenceLengths[ConjugationBase::IMPERATIVE]    = "0,2,4,1,2,3";
            }
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="1,2";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]  ="1,2,1,2,3,2";
            return $desinenceLengths;
        }

        if ($model == '230'){
            $desinenceLengths[ConjugationBase::IND_PRESENT]   ="4,5,2,5,6,5";
            $desinenceLengths[ConjugationBase::IND_IMPERFECT] ="7,7,6,6,7,7";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="1,2";
            $desinenceLengths[ConjugationBase::IMPERATIVE]    ="3,5,7,5,5,6";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]  ="4,5,4,5,6,5";
            return $desinenceLengths;
        }

        if ($model == '213' and $this->getVerb() == 'circuïr'){
            $desinenceLengths[ConjugationBase::IND_PRESENT]="4,5,3,6,7,5";
            $desinenceLengths[ConjugationBase::IND_IMPERFECT]="8,4,7,7,8,8";
            $desinenceLengths[ConjugationBase::IND_PRETERIT]="8,9,7,9,10,9";
            $desinenceLengths[ConjugationBase::IND_FUTURE]="5,6,5,5,6,6";
            $desinenceLengths[ConjugationBase::INFINITIVE]="3";
            $desinenceLengths[ConjugationBase::GERUND]="7";
            $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="3,4";
            $desinenceLengths[ConjugationBase::IMPERATIVE]="3,6,6,6,6,7";
            $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="5,6,5,6,7,6";
            $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="9,10,9,10,11,10";
            $desinenceLengths[ConjugationBase::CONDITIONAL]="7,7,6,6,7,7";
            return $desinenceLengths;
        }

        return $desinenceLengths;

    } // getDesinenceLengthArray

    protected function fixRadical($radical, $desinence){
        $model = $this->getVerbModel();

        $desinences = array('i','as','','a','on','an','e','es','en','ias','ia','ian');
  
        if(in_array($desinence,$desinences)){
            switch ($model){
            case '251'   :
                $pattern = '/(.*)o(.*?)$/'; $replacement = '${1}ò${2}'; 
                $radical =  preg_replace($pattern, $replacement, $radical);
                break;
            } // switch
        } // if

        if ($model == '220' and ($desinence == 'èrt' or $desinence == 'èrta')){
            $pattern = '/^(.+)(r)$/';
            $radical = preg_replace($pattern, '$1', $radical);
        } 

        if (($model == '230' or $model == '251') and ($desinence == 'òrt' or $desinence == 'òrta')){
            $pattern = '/^(.+)(or)$/';
            $radical = preg_replace($pattern, '$1', $radical);
        } 
        return $radical;
    } // fixRadical

} // class ConjugationLengadocianSecondGroup

?>