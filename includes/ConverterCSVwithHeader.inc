<?php

class ConverterCSVwithHeader implements IConverter{

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
    $o = '"id";"verb";"row";"dialect";"nummodel";"conjugation";"pos";"decodedPOS";"type";"person";"gender";"number";"finiteness";"mood";"tense";"voice";"status";"aspect";"separability";"reflexivity";"auxiliary"';
    $o .= "<br>\n";
    $arrPos = $converter->decodePOS($data->pos);
    if(empty($data->id)){
        $o .= '"error";"error";"error";"error";"error";"error";"error";"error";"';
    }else{
        $o .= "\"$data->id\";\"$data->verb\";\"$data->row\";\"$data->dialect\";\"$data->nummodel\";\"$data->conjugation\";\"$data->pos\";\"decodedPOS\";\"";
}
    $o .= $arrPos['type'] . '";"'; 
    $o .= $arrPos['person'] . '";"'; 
    $o .= $arrPos['gender'] . '";"'; 
    $o .= $arrPos['number'] . '";"'; 
    $o .= $arrPos['finiteness'] . '";"'; 
    $o .= $arrPos['mood'] . '";"';
    $o .= $arrPos['tense'] . '";"'; 
    $o .= $arrPos['voice'] . '";"';
    $o .= $arrPos['status'] . '";"'; 
    $o .= $arrPos['aspect'] . '";"';
    $o .= $arrPos['separability'] . '";"';
    $o .= $arrPos['reflexivity'] . '";"';
    $o .= $arrPos['auxiliary'] . '";"';

    return utf8_decode($o);
  }  // convertIndexedData
 
} // class ConverterCSVwithHeader

?>
