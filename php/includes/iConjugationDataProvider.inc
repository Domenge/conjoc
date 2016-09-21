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
  public function getVerb($verb);
  public function getVerbById($id);
  public function getVerbModelObject($numModel);
  public function getTop20();
  public function getOthersInModel($verb);
  public function getCountOthersInModel($verb);
  public function getVerbAutoComplete($string);
  public function getRandomVerb();
  public function getSingleVerbs();
  public function getAllVerbs();
  public function getAllDuplicatedVerbs();
  public function insertIndexedVerb(array $arr);
  public function getVerbsModels();
  public function getVerbsModelsMixed();

} // interface IConjugationDataProvider

?>