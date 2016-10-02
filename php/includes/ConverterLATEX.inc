<?php
/**
 * \file      ConverterLATEX.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     builds a pdf file with a conjugation and returns the name of the file. 
 * \details   takes a template file for LaTeX and stuffs it with the real conjugation filling, builds a pdf file and returns the name of the file. A lot of unix commands and pdflatex are called outside of the php process.     
 */
class ConverterLATEX implements iConverter{

  private $verbName = "";
  private $workPath = "";
  private $fullFileName = '';
  private $templateTEX = '';
  const FILECACHING = FALSE;
  /**
  * \brief a Ctor
  * \return the object
  */
  public function __construct(){
  } // __construct

  /**
  * \return an array with the tokens to be replaced into the template file
  */
  protected function getTokensArray(){

  $arr = array();
  $arr[]='prsS1';
  $arr[]='prsS2';
  $arr[]='prsS3';
  $arr[]='prsP1';
  $arr[]='prsP2';
  $arr[]='prsP3';
  $arr[]='imfS1';
  $arr[]='imfS2';
  $arr[]='imfS3';
  $arr[]='imfP1';
  $arr[]='imfP2';
  $arr[]='imfP3';
  $arr[]='prtS1';
  $arr[]='prtS2';
  $arr[]='prtS3';
  $arr[]='prtP1';
  $arr[]='prtP2';
  $arr[]='prtP3';
  $arr[]='ftrS1';
  $arr[]='ftrS2';
  $arr[]='ftrS3';
  $arr[]='ftrP1';
  $arr[]='ftrP2';
  $arr[]='ftrP3';
  $arr[]='infFI';
  $arr[]='gerFI';
  $arr[]='pamFI';
  $arr[]='pafFI';
  $arr[]='impS2';
  $arr[]='impP1';
  $arr[]='impP2';
  $arr[]='imnS2';
  $arr[]='imnP1';
  $arr[]='imnP2';
  $arr[]='supS1';
  $arr[]='supS2';
  $arr[]='supS3';
  $arr[]='supP1';
  $arr[]='supP2';
  $arr[]='supP3';
  $arr[]='suiS1';
  $arr[]='suiS2';
  $arr[]='suiS3';
  $arr[]='suiP1';
  $arr[]='suiP2';
  $arr[]='suiP3';
  $arr[]='cndS1';
  $arr[]='cndS2';
  $arr[]='cndS3';
  $arr[]='cndP1';
  $arr[]='cndP2';
  $arr[]='cndP3';
  return $arr;
  } // getTokensArray 

  /**
  * \brief merger for two arrays
  * \param $index
  * \param $tokens
  * \param $conjugationArr
  */
  protected function mergeTokensArray(&$index,&$tokens,$conjugationArr){

    // we are forging a sed command based on the substitution of a token and the real conjugation
    // the element could look like «s/prsS1/canti/»

    for($i=0; $i < count($conjugationArr); $i++){
      $tokens[$index] = "s/" . $tokens[$index] ."/". $conjugationArr[$i]."/";
      $index++; 
    }
    
  } // mergeTokensArray

  /**
  * \details this function is highly dependant of the environment, its gets a template file, creates a TEX file, does some processing and compiles the TEX file to produce a LaTeX/PDF file of the current conjugation
  * \param $conjugated an array
  * \return the full name of the PDF file
  */
  public function convertConjugation(array $conjugated){

    $pwd = dirname(__FILE__);
    $pwd = preg_replace('/(.*)includes/', '${1}cache', $pwd);
    $dialect      = $conjugated["dialect"];
    $dialectCode  = ConjugationManagerBase::getThisDialectCode($dialect);

    $this->verbName = preg_replace('/ /', '_', $conjugated["name"]);
    $this->workPath = getcwd() . "/php/cache";
    $this->templateTEX = getcwd(). "/php/templates/conjugation.tex";
    $this->fullFileName = "/php/latex_pdf/$dialectCode/$this->verbName.pdf";

    // do some caching 
    // if the file already exists, returns its name
    if (ConverterLATEX::FILECACHING && file_exists("$this->fullFileName")){
      return "$this->fullFileName";
    }

    $conjugations = $conjugated["conjugations"];
    $model        = $conjugated["model"];
    $defModel     = $conjugated["libmodel"];

    switch($dialect){
	case 'lengadocian':
	    $creditsDialect = 'Crédits -- auteur et linguiste : Patric Sauzet ; conception et réalisation : Domenge Château-Annaud ; correction : Florença Malcouyre';
	    break;
	case 'gascon':
	    $creditsDialect = 'Crédits -- auteurs et linguistes : Andrieu Bianchi, Maurici Romieu ; conception et réalisation : Domenge Château-Annaud ; lexicographe : Florença Malcouyre';
	    break;
	case 'provencau':
	    $creditsDialect = 'Crédits -- auteur et linguiste : Bernat Moulin ; conception et réalisation : Domenge Château-Annaud';
	    break;
    }	

    $tokensArray = $this->getTokensArray();

    $index=0;
    // for each temps
    for ($i=ConjugationBase::IND_PRESENT;$i < ConjugationBase::CONDITIONAL +1 ;$i++){
      $conjugation = $conjugations[$i];
      $this->mergeTokensArray($index,$tokensArray,$conjugation);        
    } // for
    
    $tokensArray[]="s/Dialect/$dialect/";
    $tokensArray[]="s/Vèrb/$this->verbName/";
    $tokensArray[]="s/Modèl/Modèl \«$model\»/";
    $tokensArray[]="s/CREDITS/$creditsDialect/";

    $pattern = '/\//';
    $replacement = '\/';
    $defModel = preg_replace($pattern, $replacement, $defModel);
    $pwd      = preg_replace($pattern, $replacement, $pwd);
    $pattern = '/\n/';
    $replacement = '';
    $defModel = preg_replace($pattern, $replacement, $defModel);

    $tokensArray[]="s/DefMdl/$defModel/";
    $tokensArray[]="s/PWD/$pwd/g";
    
    $out = "";
    
    // the array of array is flatten in one string
    foreach($tokensArray as $elemnt){
	 $out .= $elemnt . "\n";
	} // foreach
	
    $handle = fopen("$this->workPath/$this->verbName.sed", "w");
    fwrite($handle, $out);
    fclose($handle);
 
    $this->createPDF($dialectCode);
    
   return $this->fullFileName;
        
  } // convertConjugation

  /**
  * \brief calls the unix commands in order to create a LaTeX/PDF file 
  * \param $dialectCode a string
  */
  private function createPDF($dialectCode){

    if (!isset($this->verbName)){
       return "";
    }

    $output = "";
    $return_var = 0;

    $commandSED = "sed -f $this->workPath/$this->verbName.sed $this->templateTEX > $this->workPath/$this->verbName.tex";
//echo $commandSED ."<br>";
    $commandLATEX = "/usr/local/bin/pdflatex -synctex=1 -output-directory=$this->workPath -interaction=nonstopmode $this->workPath/$this->verbName.tex";
//echo $commandLATEX ."<br>";

    $commandMOVE = "mv $this->workPath/$this->verbName.pdf $this->workPath/../latex_pdf/$dialectCode/.";
//echo $commandMOVE ."<br>";

    $commandREMOVE = "rm $this->workPath/$this->verbName.*";
//echo $commandREMOVE ."<br>";

    // executes the command
    $str = exec($commandSED,$output,$return_var);


    $str = shell_exec($commandLATEX);

    $str = exec($commandMOVE,$output,$return_var);

    // do some housekeeping
    $str = exec($commandREMOVE,$output,$return_var);
//echo $commandMOVE ."<br>";
  } // createPDF

  /**
  * \brief not implemented
  * \param $list
  * \return an empty string
  */
  public function convertArray(array $list){
    return "";
  } // convertArray

  /**
  * \brief does nothing
  * \param $conjugation
  * \return an empty string
  */
  public function convertSelect(array $conjugation){
    return "";	 
  }
 
} // class ConverterLATEX

?>