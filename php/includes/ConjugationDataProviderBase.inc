<?php
/**
 * \file      ConjugationDataProviderBase.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     Base class for worker classes ConjugationDataProviderXXXX
 *
 * \details   this hierarchy of classes implements the data access layer in order to isolate the data persistance.
 */
       
abstract class ConjugationDataProviderBase implements iConjugationDataProvider{
  
  const INDEXATION_STEP = 1000;

  protected $_baseTableName; /**< the only attribute*/

/**
 * \brief      the Ctor
 * \details    
 *                  
 * \param      $baseTableName string the name of the table is known at higther level. 
 * \return     the object
 */
  public function __construct($baseTableName){
  	 $this->_baseTableName = $baseTableName;
  } // __construct

  /**
  * \brief getter for the baseTableName which is specific for the dialect.
  */
  protected function getBaseTableName(){
  	    return $this->_baseTableName;
  }

  abstract public function getVerb($verb); /**< simple getter */
  abstract public function getVerbById($id); /**< simple getter */
  abstract public function getVerbModelObject($numModel);  /**< simple getter */
  abstract public function getTop20(); /**< simple getter */
  abstract public function getOthersInModel($verb);  /**< simple getter */
  abstract public function getCountOthersInModel($verb);  /**< simple getter */
  abstract public function getVerbAutoComplete($string);  /**< simple getter */
  abstract public function getRandomVerb();  /**< simple getter */
  abstract public function getSingleVerbs();  /**< simple getter */
  abstract public function getAllVerbs();  /**< simple getter */
  abstract public function getAllDuplicatedVerbs();  /**< simple getter */
  abstract public function insertIndexedVerb(array $arr);  /**< a function to update the table for indexing conjugation every time necessary */
  abstract public function getVerbsModels();  /**< simple getter */
  abstract public function getVerbsModelsMixed();  /**< simple getter */
	
} // class ConjugationDataProviderBase

?>