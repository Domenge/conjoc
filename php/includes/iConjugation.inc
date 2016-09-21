<?php
/**
 * \file      IConjugation.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     interface
 *
 * \details   declares a contract that every Conjugation object must implement.
 */
interface iConjugation{
  /**
    \return a string, the definition of the verb infinitive 
  */
  public function getDictionaryDefinition();
  /**
    \return a string, the verbal group
  */
  public function getGroup();
  public  function getVerb();
  /**
    \return a string, the verb model (a standardized form i.e "105 d")
  */
  public function getVerbModel();
  public function getVerbModelObject($nummodel);

  /**
    \return a string, the label of the model (i.e "conjugason 1 non alternanta, iat Espii, espia, espiam, espièi, espiat")
  */
  public function getlibModel();
  public function getComments();
  /**
    \return the manager \todo (not supposed to be public)
  */
  public function getManager();
  /**
    \return a string the id of the verb
  */
  public function getVerbId();
  /**
    \return a string the localization of this conjugation (to be developped)
  */
  public function getLocalization();
  /**
    \return an id of the verb to be conjugated instead of this infinitive, in this case the infinitive is only a placeholder
  */
  public function getAlias();
  /**
    \return a string, an infinitive of the verb recommended instead of this one
  */
  public function getSeeAlso();
  /**
    \return a string of the dialect in its short form
  */ 
  public function getDialect();
  /**
    \return an associative array of the object content
  */   
  public function getConjugations();

} // interface iConjugation

?>