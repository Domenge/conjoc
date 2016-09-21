<?php
/**
 * \file      ConverterCSV.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     converts a conjugation in CVS format
 *
 * \details   
 */
class ConverterCSV implements iConverter{

  /**
  does nothing
  */
  public function __construct(){
  } // __construct

  /**
  * \return empty string
  */
  public function convertConjugation(array $conjugated){
   return '';
        
  } // convertConjugation

  /**
  * \return empty string
  */
  public function convertArray(array $list){
    return "";
  } // convertArray

  public function convertSelect(array $conjugation){
    return "";	 
  }

  /**
  * \param $data a Conjugation object
  * \return a string in CSV format (data separated by semi-colon) 
  */
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

    return $o;
  }  // convertIndexedData
 
} // class ConverterCSV

?>
