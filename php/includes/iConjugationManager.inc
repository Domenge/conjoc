<?php
/**
 * \file      iConjugationManager.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     interface
 *
 * \details   declares a contract that every ConjugationManager 
 */
interface iConjugationManager{
  /**
  * \return a string, a verb at random in its infinitive mood. 
  */
  public function getRandomVerb();
  /**
    \return an short array of verbs usually asked for.
  */
  public function getUsualVerbs();
  /**
    \brief immediatly called after setting a verb.
    \sa setVerb($verb) 
    \return a Conjugation object of an already set verb.
  */
  public function conjugate();
  /**
    \param string, the verb to conjugate in its indicative mood.
    \return nothing
  */
  public function setVerb($verb);
  /**
    \return an array of 20 of the most asked verbs
  */
  public function getTop20();  
} // interface IConjugationManager

?>