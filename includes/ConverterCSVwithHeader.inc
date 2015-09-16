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
/*
{"id":"25","verb":"abajanir","row":"0","dialect":"LNG","nummodel":"200","conjugation":"abajanir","pos":"V001050010000","decodedPOS":{"type":"Verb","person":"0","gender":"N\/A","number":"Singular","finiteness":"N\/A","mood":"Infinitive","tense":"N\/A","voice":"N\/A","status":"Main","aspect":"N\/A","separability":"N\/A","reflexivity":"N\/A","auxiliary":"N\/A"}}
*/
    $converter = new ConverterIndexation();
    $o = '"id";"verb";"row";"dialect";"nummodel";"conjugation";"pos";"decodedPOS";"type";"person";"gender";"number";"finiteness";"mood";"tense";"voice";"status";"aspect";"separability";"reflexivity";"auxiliary"';
    $o .= "<br>\n";
    $arrPos = $converter->decodePOS($data->pos);
    $o .= "\"$data->id\";\"$data->verb\";\"$data->row\";\"$data->dialect\";\"$data->nummodel\";\"$data->conjugation\";\"$data->pos\";\"decodedPOS\";\"";

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

    return $o;
  }  // convertIndexedData
 
} // class ConverterCSVwithHeader

?>
