<?php
/**
 * \file      ConjugationGasconManager.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     concrete class that specific code for setting up the Gascon conjugation
 *
 */
class ConjugationGasconManager extends ConjugationManagerBase{

    /**
     * \brief the Ctor
     * \return the object
     */
    public function __construct(){
        $this->setDialect(ConjugationManagerBase::GASCON);
    } // __construct

    /**
     * \brief detects the verbal group of the current verb and intanciates the conjugator object
     * \return the conjugator object
     */
    public function generateConjugation(){
        switch ($this->getGroup()){
        case ConjugationBase::AUXILLIARY :
            $obj = new ConjugationGasconAuxilliary($this);
            break;
        case ConjugationBase::FIRST_GROUP:
            $obj = new ConjugationGasconFirstGroup($this);
            break;
        case ConjugationBase::SECOND_GROUP:
            $obj = new ConjugationGasconSecondGroup($this);
            break;
        case ConjugationBase::THIRD_GROUP:
            $obj = new ConjugationGasconThirdGroup($this);
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
        $arrRet['èsser'] = 'gascon/verb_autocomplete/usuals/èsser';
        $arrRet['aver'] = 'gascon/verb_autocomplete/usuals/aver';
        $arrRet['anar'] = 'gascon/verb_autocomplete/usuals/anar';
        $arrRet['far'] = 'gascon/verb_autocomplete/usuals/har'; /**< be careful of the lengadocian entry FAR instead of HAR \todo please investigate*/
        $arrRet['venir'] = 'gascon/verb_autocomplete/usuals/venir';
        $arrRet['cantar'] = 'gascon/verb_autocomplete/usuals/cantar';
        $arrRet['poder'] = 'gascon/verb_autocomplete/usuals/poder';
        $arrRet['saber'] = 'gascon/verb_autocomplete/usuals/saber';
        $arrRet['valer'] = 'gascon/verb_autocomplete/usuals/valer';
        $arrRet['aduire'] = 'gascon/verb_autocomplete/usuals/aduire';

        return $arrRet;
    } // getUsualVerbs 

    /**
     * returns the dialect code
     */
    public function getShortLabel(){
        return "gsc";
    }

    /**
     * returns the dialect long label
     */
    public function getLongLabel(){
        return "gascon";
    }

    /**
     * returns a verb from the HAR family
     */
    public function getVerbHAR($verb){
        return $this->getProvider()->getVerbHAR($verb);
    }
	
} // class ConjugationGasconManager

?>