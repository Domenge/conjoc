<?php

class ConverterJSON implements iConverter{

  public function __construct(){
  } // __construct

  public function convertConjugation(array $conjugated){
   return '';
        
  } // convertConjugation

  public function convertArray(array $list){
    return "";
  } // convertArray

  public function convertSelect(array $conjugation){
    return "";	 
  }

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