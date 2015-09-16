<?php

class ConverterTEI implements IConverter{

/*
  print_r($conjugated);
  Array ( 
  [id] => 20 
  [name] => dar 
  [infinitive] => Array ( [0] => dar ) 
  [model] => 107 a 
  [comments] => not yet implemented 
  [libmodel] => conjugason 1 monosillabs 
  [dialect] => gascon 
  [localization] => C 
  [conjugations] => Array ( [0] => Array ( [0] => dau [1] => das [2] => da [3] => dam [4] => datz [5] => dan ) [1] => Array ( [0] => davi [1] => davas [2] => dava [3] => dàvam [4] => dàvatz [5] => davan ) [2] => Array ( [0] => dèi [1] => dès [2] => dè [3] => dèm [4] => dètz [5] => dèn ) [3] => Array ( [0] => darèi [1] => daràs [2] => darà [3] => daram [4] => daratz [5] => daràn ) [4] => Array ( [0] => dar ) [5] => Array ( [0] => dant ) [6] => Array ( [0] => dat [1] => dada ) [7] => Array ( [0] => da [1] => dem [2] => datz [3] => des [4] => dem [5] => detz ) [8] => Array ( [0] => dau [1] => des [2] => de [3] => dem [4] => detz [5] => den ) [9] => Array ( [0] => dèssi [1] => dèsses [2] => dèsse [3] => dèssem [4] => dèssetz [5] => dèssen ) [10] => Array ( [0] => darí [1] => darés [2] => daré [3] => darem [4] => daretz [5] => darén ) ) [desinenceLengths] => Array ( [0] => 1,2,1,2,3,2 [1] => 3,4,3,4,5,4 [2] => 3,4,2,4,5,4 [3] => 4,4,3,4,5,4 [4] => 2 [5] => 3 [6] => 1,2,3,2,2,3 [7] => 1,2,1,2,3,2 [8] => 4,5,4,4,6,5 [9] => 5,5,4,5,6,5 ) ) 
*/
  private $_converterIndexation;

  public function __construct(){
    $this->_converterIndexation = new ConverterIndexation();
  } // __construct

  
  public function getConverterIndexation() {return $this->_converterIndexation;}
   
  public function convertConjugation(array $conjugated){

    $conjugations = $conjugated['conjugations'];
    $dialect = $conjugated['dialect'];
    $out = "";
    $ModesArray = array();
    $verb = $conjugated['infinitive'][0];
    $verb = preg_replace('/\'/','',$verb);    
    $verb = preg_replace('/ /','_',$verb);
        
    // for each temps
    for ($i=ConjugationBase::IND_PRESENT;$i < ConjugationBase::CONDITIONAL +1 ;$i++){
      $conjugation = $conjugations[$i];

      switch($i){
        case ConjugationBase::IND_PRESENT : $ModesArray['Indicative']= array(); $mode ='Indicative' ;break;
        case ConjugationBase::INFINITIVE  : $ModesArray['Impersonal forms']= array(); $mode ='Impersonal forms' ; break;
        case ConjugationBase::IMPERATIVE  : $ModesArray['Imperative']= array(); $mode ='Imperative' ;break;
        case ConjugationBase::SUBJ_PRESENT: $ModesArray['Subjunctive']= array(); $mode ='Subjunctive'; break;
        case ConjugationBase::CONDITIONAL : $ModesArray['Conditional']= array(); $mode ='Conditional'; break;
      }

      
      // big dispatch
      // Each temps is dispatched in its own mode        
      switch($mode){
      	case "Indicative" :
      		$ModesArray['Indicative'][] = $conjugation; 
      		break; 
      	case "Impersonal forms" :
      		$ModesArray['Impersonal forms'][] = $conjugation; 
      		break; 
      	case "Imperative" :
      		$ModesArray['Imperative'][] = $conjugation; 
      		break; 
      	case "Subjunctive" :
      		$ModesArray['Subjunctive'][] = $conjugation; 
      		break; 
      	case "Conditional" :
      		$ModesArray['Conditional'][] = $conjugation; 
      		break; 
      } // switch
    } // for

    $o = $this->getHeader($dialect);
    if (count($conjugated) > 0){
    	$o .= "<entry>\n";
    	$o .= "\t<form>\n";
	$o .= "\t\t<orth>\n";
	$infinitive = $conjugated['infinitive'][0];
	$o .= "\t\t\t$infinitive\n";
	$o .= "\t\t</orth>\n";
	$o .= "\t\t<iType type=\"verbTable\">\n";
	$model = $conjugated['model'];
	$o .= "\t\t\t$model\n";
	$o .= "\t\t</iType>\n";
        $o .= $this->formatConjugation($model,$ModesArray);
	$o .= "\t</form>\n";
    	$o .= "</entry>\n";
    } // if

    $o .= $this->getFooter();
  $this->createDownloadFile($o,"$verb". '_' ."$dialect");	   
  } // convertConjugation

  
  private function formatConjugation($model, $ConjugationArray){
    $out = "";
      
    // Indicative
    $ary = $ConjugationArray['Indicative'];

    $tenses = array("present","imperfect","preterit","future");

    // put POS default values 
    $aryPOS = array();
    //$aryPOS['person'] = 1;
    // II Gender 1 Masculine 2 Feminine 3 Neuter
    $aryPOS['gender'] = 0;
    // III Number 1 Singular 2 Plural
    //$aryPOS['number'] = 1;
    // IV Finiteness 1 Finite 2 Non-finite
    $aryPOS['finiteness'] = 0;
    // V Mood 1 Indicative 2 Subjunctive 3 Imperative 4 Conditional 5 Infinitive 6 Participle 7 Gerund 8 Supine
    // $aryPOS['mood'] = 1;
    // VI Tense 1 Present 2 Imperfect 3 Future 4 Past
    // $aryPOS['tense'] = 1;
    // VII Voice 1 Active 2 Passive
    $aryPOS['voice'] = 0;
    // VIII Status 1 Main 2 Auxiliary 3 Semi-auxiliary
    $aryPOS['status'] = 1;
	
    if ($model == '001' || $model == '002'){
	$aryPOS['status'] = 2;
    }
    if ($model == '003' || $model == '003 b' || $model == '004'){
	$aryPOS['status'] = 3;
    }

    // IX Aspect 1 Perfective 2 Imperfective
    $aryPOS['aspect'] = 0;
    // X Separability 1 Non-separable 2 Separable
    $aryPOS['separability'] = 0;
    // XI Reflexivity 1 Reflexive 2 Non-reflexive
    $aryPOS['reflexivity'] = 0;
    // XII Auxiliary 1 Have 2 Be
    $aryPOS['auxiliary'] = 0;
    // iterating in the conjugations, a record is created for each flexion

/*
	I N D I C A T I V E
*/	
    $mood = 'indicative';
    $aryPOS['mood'] = 1;

    for ($j=0; $j < 4; $j++){

    	$tns  = $tenses[$j];
    	$conj = $ary[$j];
    	$aryPOS['tense'] = $this->getConverterIndexation()->encodeTense($j);
    	
	for($i=0;$i<6;$i++){
		$number = ($i<3)? 'singular':'plural';
		$numberPOS = ($i<3)? 1:2;
		$per = ($i<3)? $i+1:$i - 2;
		$orth = $conj[$i];
		$aryPOS['person'] = $per;
		$aryPOS['number'] = $numberPOS;
		$pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <per>
	        	      $per
	        	    </per>
	        	    <number>
	        	      $number
	        	    </number>
	        	    <mood>
	        	      $mood
	        	    </mood>
	        	    <tns>
	        	      $tns
	        	    </tns>
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>
	        	  </gramGrp>
	        	</form>
	        	       	
EOT;
	      	$out .= $str;

    	} //for

    } // for

/*
	C O N D I T I O N A L
*/	
    $ary = $ConjugationArray['Conditional'];

    $mood = 'conditional';
    $aryPOS['mood'] = 4;

    $tns  = 'present';
    $conj = $ary[0];
    	
     for($i=0;$i<6;$i++){
	$number = ($i<3)? 'singular':'plural';
	$per = ($i<3)? $i+1:$i - 2;
	$orth = $conj[$i];
	$pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <per>
	        	      $per
	        	    </per>
	        	    <number>
	        	      $number
	        	    </number>
	        	    <mood>
	        	      $mood
	        	    </mood>
	        	    <tns>
	        	      $tns
	        	    </tns>
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>	        	    
	        	  </gramGrp>
	        	</form>
	        	       	
EOT;
	$out .= $str;

    } // for

/*
	I N F I N I T I V E
*/	
    // INFINITIVE, GERUND & PARTICLE
    $ary = $ConjugationArray['Impersonal forms'];   

    $mood = 'infinitive';
    $aryPOS['mood'] = 5;
    $aryPOS['person'] = 0;
    $aryPOS['number'] = 1;
    
    $conj = $ary[0];   	
    $orth = $conj[0];
    $pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <mood>
	        	      $mood
	        	    </mood>
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>	        	    
	        	  </gramGrp>
	        	</form> 
	        	      	
EOT;
	$out .= $str;

/*
	G E R U N D I V E
*/	

    $mood = 'gerund';
    $conj = $ary[1];   	
    $orth = $conj[0];
    $aryPOS['mood'] = 7;
    $aryPOS['person'] = 0;
    $aryPOS['number'] = 1;
    $aryPOS['tense'] = 1;
    $pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <mood>
	        	      $mood
	        	    </mood>
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>
	        	  </gramGrp>
	        	</form>
	        	       	
EOT;
	$out .= $str;

/*
	P A S T  P A R T I C I P L E
*/
/*
M A S C U L I N E
*/	
    $mood = 'participle';
    $tns  = 'past';
    $conj = $ary[2];   	
    $orth = $conj[0];
    $gen  = 'masculin';
    $aryPOS['mood'] = 6;
    $aryPOS['gender'] = 1;
    $aryPOS['person'] = 0;
    $aryPOS['tense'] = 4;
    
    $pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <mood>
	        	      $mood
	        	    </mood>
    	  	            <tns>
	        	      $tns
	        	    </tns> 
    	  	            <gen>
	        	      $gen
	        	    </gen> 
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>
	        	  </gramGrp>
	        	</form>
	        	       	
EOT;

/*
F E M I N I N E
*/	
    $out .= $str;
    $orth = $conj[1];	
    $gen  = 'feminine';
    $aryPOS['mood'] = 6;
    $aryPOS['gender'] = 2;
    $pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <mood>
	        	      $mood
	        	    </mood>
    	  	            <tns>
	        	      $tns
	        	    </tns>
    	  	            <gen>
	        	      $gen
	        	    </gen> 
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>
      	             	  </gramGrp>
	        	</form>
	        	       	
EOT;
	$out .= $str;

 
    // IMPERATIVE
    $ary = $ConjugationArray['Imperative'];   
    $mood = 'imperative';
    $aryPOS['mood'] = 3;
    $aryPOS['tense']= 1;

    $tns  = 'present';
    $conj = $ary[0];
    	
	for($i=0;$i<6;$i++){
		$number = ($i==0 || $i==3)? 'singular':'plural';
		$usg = ($i<3)? 'positive':'negative';
		$per = ($i==2 || $i==5)? 2:1;
		$orth = $conj[$i];
		$pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <per>
	        	      $per
	        	    </per>
	        	    <number>
	        	      $number
	        	    </number>
	        	    <mood>
	        	      $mood
	        	    </mood>
	        	    <tns>
	        	      $tns
	        	    </tns>
      	           	    <usg>
	        	      $usg
        		    </usg>
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>	        	    
	        	  </gramGrp>
	        	</form>
	        	       	
EOT;
	      	$out .= $str;
    } // for

    
/*
	S U B J U N C T I V E
*/
    $ary = $ConjugationArray['Subjunctive'];   

    $tenses = array("present","imperfect");

    $mood = 'subjunctive';
    $aryPOS['mood'] = 2;

    for ($j=0; $j < 2; $j++){

    	$aryPOS['tense'] = $this->getConverterIndexation()->encodeTense($j);
    	$tns  = $tenses[$j];
    	$conj = $ary[$j];
    	
	for($i=0;$i<6;$i++){
		$number = ($i<3)? 'singular':'plural';
		$numberPOS = ($i<3)? 1:2;
		$per = ($i<3)? $i+1:$i - 2;
		$orth = $conj[$i];
		$aryPOS['person'] = $per;
		$aryPOS['number'] = $numberPOS;
		$pos = $this->getConverterIndexation()->encodePos($aryPOS);

$str = <<<EOT
<form type="inflected">
	        	  <orth>
	        	    $orth
	        	  </orth>
	        	  <gramGrp>
	        	    <per>
	        	      $per
	        	    </per>
	        	    <number>
	        	      $number
	        	    </number>
	        	    <mood>
	        	      $mood
	        	    </mood>
	        	    <tns>
	        	      $tns
	        	    </tns>
	        	    <pos>
	        	      verb
	        	    </pos>
	        	    <gram type="eaglescat">
	        	      $pos
	        	    </gram>
	        	  </gramGrp>
	        	</form>
	        	       	
EOT;
	      	$out .= $str;

    	} //for

    } // for

    return $out;  
  } // formatConjugation

  public function convertArray(array $list){
    $o = $this->getHeader();
    if (count($list) > 0){
      foreach($list as $key => $value){
    	$o .= "<entry>\n";
    	$o .= "\t<form>\n";
	$o .= "\t\t<orth>\n";
	$infinitive = $value['infinitive'][0];
	$o .= "\t\t\t$infinitive\n";
	$o .= "\t\t</orth>\n";
	$o .= "\t\t<iType type=\"verbTable\">\n";
	$model = $value['model'];
	$o .= "\t\t\t$model\n";
	$o .= "\t\t</iType>\n";
        $o .= $this->convertConjugation($value);
	$o .= "\t</form>\n";
    	$o .= "</entry>\n";
      } // for
    } // if

    $o .= $this->getFooter();
    $this->createDownloadFile($o, $verb);	   
  } // convertArray

  public function convertSelect(array $conjugation){
  
  }

private function getHeader($dialect='none'){

switch($dialect){
	case 'lengadocian': $libDialect = 'occitan languedocien'; $idDialect = 'oc-lnc'; $thanks = 'Patric Sauzet'; break;
	case 'gascon': $libDialect = 'occitan gascon'; $idDialect = 'oc-gsc'; $thanks = 'Maurici Romieu, Andrieu Bianchi, Florença Malcouyre'; break;
	case 'provençau': $libDialect = 'occitan provençal'; $idDialect = 'oc-prv'; $thanks = 'Bernat Moulin'; break;
} // switch

	$out = <<<EOT
<TEI>
  <teiHeader>
    <fileDesc>
      <titleStmt>
        <title>
          verb'Òc, conjugator occitan
        </title>
        <author>
          Lo Congrès Permanent de la Lenga Occitana
        </author>
      </titleStmt>
      <sourceDesc>
        <title>
          verb'Òc, conjugator occitan
        </title>
        <author>
          Lo Congrès Permanent de la Lenga Occitana
        </author>
        <editor>
          Lo Congrès Permanent de la Lenga Occitana
        </editor>
        <date>
          2015
        </date>
        <note>
          Version  xml réalisée par Domenge Château-Annaud
        </note>
      </sourceDesc>
      <publicationStmt>
        <availability>
          Creative commons (BY SA)
        </availability>
      </publicationStmt>
      <notesStmt>
        <note>
          Remerciements : $thanks
        </note>
      </notesStmt>
    </fileDesc>
    <profileDesc>
      <langUsage>
        <language ident="$idDialect">
          $libDialect
        </language>
      </langUsage>
    </profileDesc>
  </teiHeader>
  <text>
    <body>
    
EOT;
	return $out;	
} // getHeader

private function getFooter(){
	$out = <<<EOT
    </body>
  </text>
</TEI>
EOT;
	return $out;	
} // getFooter

private function createDownloadFile($strToWrite, $name='All'){
  $file_name = tempnam(variable_get('file_directory_temp', drupal_get_path('module', 'conjoc'). "/cache"), 'TEIexport'.$name);
  $name = "extraccion_TEI_$name";
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



} // class ConverterTEI

?>