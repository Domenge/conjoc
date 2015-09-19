<?php

class ConverterCSV implements IConverter{

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

     if(empty($data)){
	$arrPos = array();
	$arrPos['type'] = 'error';
	$arrPos['person'] = 'N/A';
	$arrPos['gender'] = 'N/A';
	$arrPos['number'] = 'N/A';
	$arrPos['finiteness'] = 'N/A';
	$arrPos['mood'] = 'N/A';
	$arrPos['tense'] = 'N/A';
	$arrPos['voice'] = 'N/A';
	$arrPos['status'] = 'N/A';
	$arrPos['aspect'] = 'N/A';
	$arrPos['separability'] = 'N/A';
	$arrPos['reflexivity'] = 'N/A';
	$arrPos['auxiliary'] = 'N/A';

    	$arrData = array();
	$arrData['id'] = 'error';
	$arrData['verb'] = 'error';
	$arrData['row'] = 'error';
	$arrData['dialect'] = 'error';
	$arrData['nummodel'] = 'error';
	$arrData['conjugation'] = 'error';
	$arrData['pos'] = 'error';
	$arrData['decodePOS'] = 'error';
     }else{
	$arrPos = $converter->decodePOS($data->pos);
    	$arrData = (array)$data;
 	}
    $arrData['decodedPOS'] = $arrPos;  
    return json_encode($arrData);
  }  // convertIndexedData
 
} // class ConverterCSV

?>