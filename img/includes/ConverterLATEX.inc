<?php

class ConverterLATEX implements IConverter{

  private $verbName = "";
  private $workPath = "";
  private $fullFileName = '';
  private $templateTEX = '';
  const FILECACHING = FALSE;

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
	
  protected function mergeTokensArray(&$index,&$tokens,$conjugationArr){

    // we are forging a sed command based on the substitution of a token and the real conjugation
    // the element could look like «s/prsS1/canti/»

    for($i=0; $i < count($conjugationArr); $i++){
      $tokens[$index] = "s/" . $tokens[$index] ."/". $conjugationArr[$i]."/";
      $index++; 
    }
    
  } // mergeTokensArray

  public function convertConjugation(array $conjugated){

    $pwd = dirname(__FILE__);
    $pwd = preg_replace('/(.*)includes/', '${1}cache', $pwd); // replace « includes » directory name by « cache » 

    $this->verbName = preg_replace('/ /', '_', $conjugated["name"]);
    $this->workPath = drupal_get_path('module', 'conjoc'). "/cache";
    $this->templateTEX = drupal_get_path('module', 'conjoc'). "/templates/conjugation.tex";

    $conjugations = $conjugated["conjugations"];
    $model        = $conjugated["model"];
    $dialect      = $conjugated["dialect"];
    $defModel     = $conjugated["libmodel"];

    switch($dialect){
	case 'lengadocian':
	    $dialectCode = 'lng';
	    $creditsDialect = 'Crédits -- auteur et linguiste : Patric Sauzet ; conception et réalisation : Domenge Château-Annaud ; correction : Florença Malcouyre';
	    break;
	case 'gascon':
	    $dialectCode = 'gsc';
	    $creditsDialect = 'Crédits -- auteurs et linguistes : Andrieu Bianchi, Maurici Romieu ; conception et réalisation : Domenge Château-Annaud ; lexicographe : Florença Malcouyre';
	    break;
	case 'provencau':
	    $dialectCode = 'prv';	
	    $creditsDialect = 'Crédits -- auteur et linguiste : Bernat Moulin ; conception et réalisation : Domenge Château-Annaud';
	    break;
    }
    	
    $this->fullFileName = "sites/default/files/latex_pdf/$dialectCode/$this->verbName.pdf";

    // do some caching 
    // if the file already exists, returns its name
    if (ConverterLATEX::FILECACHING && file_exists("$this->fullFileName")){
      return "$this->fullFileName";
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


  private function createPDF($dialectCode){

    if (!isset($this->verbName)){
       return "";
    }

    $output = "";
    $return_var = 0;

    $commandSED = "sed -f $this->workPath/$this->verbName.sed $this->templateTEX > $this->workPath/$this->verbName.tex";

    $commandLATEX = "/usr/local/bin/pdflatex -synctex=1 -output-directory=$this->workPath -interaction=nonstopmode $this->workPath/$this->verbName.tex";

    $commandMOVE = "mv $this->workPath/$this->verbName.pdf sites/default/files/latex_pdf/$dialectCode/.";

    $commandREMOVE = "rm $this->workPath/$this->verbName.*";

    // executes the command
    $str = exec($commandSED,$output,$return_var);
//    drupal_set_message("createPDF SED passed $commandSED");

    $str = shell_exec($commandLATEX);
//    drupal_set_message("createPDF LATEX passed $commandLATEX .$str.");

    $str = exec($commandMOVE,$output,$return_var);

    // do some housekeeping
    $str = exec($commandREMOVE,$output,$return_var);

  } // createPDF

  public function convertArray(array $list){
    return "";
  } // convertArray

  public function convertSelect(array $conjugation){
    return "";	 
  }
 
} // class ConverterLATEX

?>