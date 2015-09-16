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
  	 $o = '<?xml version="1.0" ?>';
	 $o .= '';
/*
<menubar>
   <menu name="File">
      <command value="New" action="CreateDoc" />
      <command value="Open" action="OpenDoc" />    
      <command value="Close" action="CloseDoc" />
   </menu>
</menubar>
*/
	return $o;
  }  // convertIndexedData
 
} // class ConverterXML

?>