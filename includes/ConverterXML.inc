<?php

class ConverterXML implements IConverter{

  public function __construct(){
  } // __construct

  public function convertConjugation(array $conjugated){
   return "";        
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
	$this->createDownloadFile($o,$data->conjugation . '_' . $data->pos);	   
  }  // convertIndexedData

private function createDownloadFile($strToWrite, $name='All'){
  $file_name = tempnam(variable_get('file_directory_temp', drupal_get_path('module', 'conjoc'). "/cache"), 'Indexationexport'.$name);
  $name = "$name";
  $handle = @fopen($file_name, 'w'); // The @ supresses errors.

  // Write data
  @fwrite($handle, $strToWrite);

  // Close the file.
  @fclose($handle);

  header("Content-type: application/xml");
  header("Content-Disposition: attachment; filename=". preg_replace('/\.$/', '', str_replace(' ', '_', check_plain($name))) .".xml");

  @readfile($file_name); // The @ makes it silent.
  @unlink($file_name); // Clean up, the @ makes it silent.
  exit(0);
} // createDownloadFile

 
} // class ConverterXML

?>