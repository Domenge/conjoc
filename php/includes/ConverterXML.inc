<?php
/**
 * \file      ConverterXMLinc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     converts a conjugation in XML the POS string must be decoded
 *
 * \details   
 */
class ConverterXML implements iConverter{

  /**
  *
  * \brief Ctor   
  */
  public function __construct(){
  } // __construct

  /**
  *
  * \param $conjugated
  * \return a string empty
  */
  public function convertConjugation(array $conjugated){
   return "";        
  } // convertConjugation


  /**
  *
  * \param $list a conjugation in array format
  * \return an empty string
  */
  public function convertArray(array $list){
    return "";
  } // convertArray

  /**
  *
  * \return an empty string
  */
  public function convertSelect(array $conjugation){
    return "";	 
  }

  /**
  * \param $data an conjugation object
  * \return an XML string fully formatted
  */
  public function convertIndexedData($data){
    $converter = new ConverterIndexation();
    $arrPos = $converter->decodePOS($data->pos);

    $type = $arrPos['type'];
    $person = $arrPos['person'];
    $gender = $arrPos['gender'];
    $number = $arrPos['number'];
    $finiteness = $arrPos['finiteness'];
    $mood = $arrPos['mood'];
    $tense = $arrPos['tense'];
    $voice = $arrPos['voice'];
    $status = $arrPos['status'];
    $aspect = $arrPos['aspect'];
    $separability = $arrPos['separability'];
    $reflexivity = $arrPos['reflexivity'];
    $auxiliary = $arrPos['auxiliary'];

$o = <<<EOT
<?xml version="1.0" encoding="UTF-8" ?>
<document>
<id>$data->id</id>
<verb>$data->verb</verb>
<row>$data->row</row>
<dialect>$data->dialect</dialect>
<nummodel>$data->nummodel</nummodel>
<conjugation>$data->conjugation</conjugation>
<pos>$data->pos</pos>
	<decodedPOS>
		<type>$type</type>
		<person>$person</person>
		<gender>$gender</gender>
		<number>$number</number>
		<finiteness>$finiteness</finiteness>
		<mood>$mood</mood>
		<tense>$tense</tense>
		<voice>$voice</voice>
		<status>$status</status>
		<aspect>$aspect</aspect>
		<separability>$separability</separability>
		<reflexivity>$reflexivity</reflexivity>
		<auxiliary>$auxiliary</auxiliary>
	</decodedPOS>	        	       	
</document>
EOT;
	$this->createDownloadFile($o,$data->conjugation . '_' . $data->pos); /**< this function call exits to let the navigator download the newly created file*/	   
  }  // convertIndexedData


  /**
  * \param $strToWrite an XML string
  * \param $name string a suffix for the filename
  * \return this function exits the call
  */
private function createDownloadFile($strToWrite, $name='All'){
  $file_name = tempnam(getcwd(). '/cache/', "Indexationexport.$name");

  $name = "extraccion_XML_$name";
  $handle = @fopen($file_name, 'w'); // The @ supresses errors.

  // Write data
  @fwrite($handle, $strToWrite);

  // Close the file.
  @fclose($handle);

  header("Content-type: application/xml");
  header("Content-Disposition: attachment; filename=". preg_replace('/\.$/', '', str_replace(' ', '_', htmlspecialchars($name))) .".xml");

  @readfile($file_name); // The @ makes it silent.
  @unlink($file_name); // Clean up, the @ makes it silent.
  exit(0);
} // createDownloadFile
 
} // class ConverterXML

?>