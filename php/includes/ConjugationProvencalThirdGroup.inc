<?php
/**
 * \file      ConjugationProvencalThirdGroup.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker class for conjugating the third group of provencal verbs
 */
class ConjugationProvencalThirdGroup extends ConjugationBase{

    /**
     * \brief returns an array w/ the conjugations of the current verb, acts as a helper for getConjugationArray()
     * \return an array w/ the desinences commonly used
     */
    protected getStandardConjugation(){
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
     * \brief a placeholder for the conjugate function
     */
    public function display(){
        return "ConjugationProvencalThirdGroup $this->_name " . $this->conjugate;
    } // display
} // class ConjugationProvencalThirdGroup

?>