<?php
/**
 * \file      ConjugationProvencalManager.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     concrete class for setting up the provencal conjugation
 *
 */
class ConjugationProvencalManager extends ConjugationManagerBase{
    /**
     * \brief a Ctor
     * \return the manager object
     */
    public function __construct(){
        $this->setDialect(ConjugationManagerBase::PROVENCAL);
    } // __construct

    /**
     * \brief detects the verbal group of the current verb and intanciates the conjugator object
     * \return the conjugator object
     */
    public function generateConjugation(){
        switch ($this->getGroup()){
        case ConjugationBase::AUXILLIARY :
            $obj = new ConjugationProvencalAuxilliary($this,$verb,$id,$model,$comments,$localization);
            break;
        case ConjugationBase::FIRST_GROUP:
            $obj = new ConjugationProvencalFirstGroup($this,$verb,$model,$comments,$localization);
            break;
        case ConjugationBase::SECOND_GROUP:
            $obj = new ConjugationProvencalSecondGroup($this,$verb,$model,$comments,$localization);
            break;
        case ConjugationBase::THIRD_GROUP:
            $obj = new ConjugationProvencalThirdGroup($this,$verb,$alias,$model,$comments,$localization);
            break;
        }
        return $obj;

    } // generateConjugation

    /**
     * \brief returns a list of usual verbs in gascon dialect
     * \return an associative array of usual verbs
     */
    public function getUsualVerbs(){
        $arrRet = array();
        $arrRet['èsser'] = 'conjoc/verb_autocomplete/usuals/èsser';
        $arrRet['aver'] = 'conjoc/verb_autocomplete/usuals/aver';
        $arrRet['anar'] = 'conjoc/verb_autocomplete/usuals/anar';
        $arrRet['far'] = 'conjoc/verb_autocomplete/usuals/far';
        $arrRet['venir'] = 'conjoc/verb_autocomplete/usuals/venir';
        $arrRet['cantar'] = 'conjoc/verb_autocomplete/usuals/cantar';
        $arrRet['poder'] = 'conjoc/verb_autocomplete/usuals/poder';
        $arrRet['saber'] = 'conjoc/verb_autocomplete/usuals/saber';
        $arrRet['valer'] = 'conjoc/verb_autocomplete/usuals/valer';
        $arrRet['aduire'] = 'conjoc/verb_autocomplete/usuals/aduire';

        return $arrRet;
    } // getUsuals 

    /**
     * returns the dialect code
     */
    public function getShortLabel(){
        return "prv";
    }

    /**
     * returns the dialect long label
     */
    public function getLongLabel(){
        return "provencal";
    }

} // class ConjugationProvencalManager

?>