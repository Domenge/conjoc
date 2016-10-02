<?php
/**
 * \file      ConjugationLengadocianManager.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     concrete class for setting up the Lengadocian conjugation
 *
 */
class ConjugationLengadocianManager extends ConjugationManagerBase{

    /**
     * \brief a Ctor
     * \return the manager object
     */
    public function __construct(){
        $this->setDialect(ConjugationManagerBase::LENGADOCIAN);
    } // __construct

    /**
     * \brief detects the verbal group of the current verb and intanciates the conjugator object
     * \return the conjugator object
     */
    public function generateConjugation(){
        switch ($this->getGroup()){
        case ConjugationBase::AUXILLIARY :
            $obj = new ConjugationLengadocianAuxilliary($this);
            break;
        case ConjugationBase::FIRST_GROUP:
            $obj = new ConjugationLengadocianFirstGroup($this);
            break;
        case ConjugationBase::SECOND_GROUP:
            $obj = new ConjugationLengadocianSecondGroup($this);
            break;
        case ConjugationBase::THIRD_GROUP:
            $obj = new ConjugationLengadocianThirdGroup($this);
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
        $arrRet['èsser'] = 'lengadocian/verb_autocomplete/usuals/èsser';
        $arrRet['aver'] = 'lengadocian/verb_autocomplete/usuals/aver';
        $arrRet['anar'] = 'lengadocian/verb_autocomplete/usuals/anar';
        $arrRet['far'] = 'lengadocian/verb_autocomplete/usuals/far';
        $arrRet['venir'] = 'lengadocian/verb_autocomplete/usuals/venir';
        $arrRet['cantar'] = 'lengadocian/verb_autocomplete/usuals/cantar';
        $arrRet['poder'] = 'lengadocian/verb_autocomplete/usuals/poder';
        $arrRet['saber'] = 'lengadocian/verb_autocomplete/usuals/saber';
        $arrRet['valer'] = 'lengadocian/verb_autocomplete/usuals/valer';
        $arrRet['aduire'] = 'lengadocian/verb_autocomplete/usuals/aduire';

        return $arrRet;
    } // getUsuals 

    /**
     * returns a verb from the FAR family
     */
    public function getVerbFAR($verb){
        return $this->getProvider()->getVerbFAR($verb);
    }

    /**
     * returns the dialect code
     */
    public function getShortLabel(){
        return "lng";
    }

    /**
     * returns the dialect long label
     */
    public function getLongLabel(){
        return "lengadocian";
    }

} // class ConjugationLengadocianManager

?>