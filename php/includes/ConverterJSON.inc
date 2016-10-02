<?php
/**
 * \file      ConverterJSON.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     converts a conjugation in JSON format
 *
 * \details   
 */
class ConverterJSON implements iConverter{
  /**
  * \brief ctor
  * \return the object
  */
  public function __construct(){
  } // __construct

  /**
  * \brief converts a conjugation
  * \param $conjugated an array
  * \return an empty string
  */
  public function convertConjugation(array $conjugated){
   return '';        
  } // convertConjugation
  
  /**
  * \brief does nothing
  * \param $list an array
  * \return an empty string
  */
  public function convertArray(array $list){
    return "";
  } // convertArray

  /**
  * \param $conjugation an array
  * \brief does nothing
  * \return an empty string
  */
  public function convertSelect(array $conjugation){
    return "";	 
  }

  /**
  * \brief calls the indexation converter and converts the POS into JSON format
  * \param $data a conjugation object
  * \return the decoded POS in JSON format
  */
  public function convertIndexedData($data){
    $converter = new ConverterIndexation();
 
    $arrPos = $converter->decodePOS($data->pos);
    $count = 0;
    $arrData = (array)$data;

    $arrData['decodedPOS'] = $arrPos;  
    return json_encode($arrData);
  }  // convertIndexedData
 
} // class ConverterJSON

?>