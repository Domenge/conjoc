<?php
/**
 * \file      IConjugationDataProvider.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     interface
 *
 * \details   declares a contract that every ConjugationDataProvider
 */
interface IConjugationDataProvider{
    public function getVerb($verb); /**< returns the conjugation data of the verb infinitive  */
    public function getVerbById($id); /**< returns the conjugation data of the verb id  */

    /**
       \brief returns the conjugaton data of the verb id  
       \param $numModel the model code
    */
    public function getVerbModelObject($numModel);  
    public function getTop20(); /**< returns a list of the 20 most wanted verbs (infinitive)  */

    /**
       \brief returns  a list of the other verbs in the verb model
       \param $verb the current verb to be conjugated
    */
    public function getOthersInModel($verb);
    /**
       \brief returns the count of the other verbs in the verb model
       \param $verb the current verb to be conjugated
    */
    
    public function getCountOthersInModel($verb);

    /**
       \brief a helper function to return a list of infinitive beginning by the string
       \param $string a string beginning the infinitive of a verb
    */
    public function getVerbAutoComplete($string); /**< an autocomplete routine for the CMS needs */
    public function getRandomVerb(); /**< returns a verb at random */
    public function getSingleVerbs(); /**< returns the verbs single respectively in their model  */
    public function getAllVerbs(); /**< returns all the verbs, there is a lot */
    public function getAllDuplicatedVerbs(); /**< returns the verb with the same infinitive but a different meaning */
    public function insertIndexedVerb(array $arr); /**< inserts a verb data into the indexation database once in a row  */
    public function getVerbsModels(); /**< returns all the verb models for a dialect  */
    public function getVerbsModelsMixed(); /**< returns all the verb models from all the dialects */ 
} // interface IConjugationDataProvider

?>