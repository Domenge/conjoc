<?php
/**
 * \file      ConverterHTML.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     converts a conjugation in HTML format
 *
 * \details   
 */
class ConverterHTML implements iConverter{

    /**
    * \brief the ctor
    * \return the object
    */
    public function __construct(){
    } // __construct

    /**
    * \brief return a list of Tenses
    * \return an array
    */
    protected function getTempses(){
        $arr = array();
        $arr[] = "Present";
        $arr[] = "Imperfach";
        $arr[] = "Preterit";
        $arr[] = "Futur";
        $arr[] = "Infinitiu";
        $arr[] = "Gerondiu";
        $arr[] = "Participi passat";
        $arr[] = "Present positiu/present negatiu";
        $arr[] = "Subjontiu present";
        $arr[] = "Subjontiu imperfach";
        $arr[] = "Condicional";

        return $arr;
    }

/*
  $arr["id"]               
  $arr["name"]             
  $arr["infinitive"]       
  $arr["model"]            
  $arr["see_also"]         
  $arr["comments"]         
  $arr["libmodel"]         
  $arr["dialect"]          
  $arr["localization"]     
  $arr["comments"]         
  $arr["conjugations"]     
  $arr["desinenceLengths"] 
  $arr["dictionaryDefinition"]

*/
    /**
    * \brief return a list of Tenses
    * \param $conjugated an array of the conjugation data
    * \return a string in HTML
    */
    public function convertConjugation(array $conjugated){

        $tempses = $this->getTempses();
        if (empty($conjugated["conjugations"])){
            print ("Pas de conjugasons per aqueste vèrb.");
            exit;
        }else{
            $conjugations = $conjugated["conjugations"];
        }

        $infinitive = $conjugated["infinitive"][0];

        $out = "";
    
        // SEE ALSO
        $see = $conjugated["see_also"];
        $libmodel = $conjugated["libmodel"];
        $model = $conjugated["model"];
        $dialect = $conjugated["dialect"];
        $dictionaryDefinitions = $conjugated["dictionaryDefinition"];

        /**
	* I N F I N I T I V E
	*/
        $out .= "<h2>$infinitive</h2>\n";

        $out .= '<div class="verb">' . "\n";
        if ($see){
            $out .= "remandament" . ' <span class="see_also"><a href='. $_SERVER['PHP_SELF'].'?verb_selected=' . urlencode($see) . ">$see</a></span><br>";
        }
        $out .= "<span class=\"label_verb\">$model</span> <span class=\"label_verb\">$libmodel</span>" . "\n";

        $creditDefinition = 'sorça : <a href="http://ideco-dif.com/ieo_edicions/pedagogia/tot_en_un_novela_edicion/" target="_blank">Tot En Un, lexic Occitan-Francés, Joan-Claudi SÈRRAS. IEO Edicions</a>' . "\n";
        if (!empty($dictionaryDefinitions)){
            $out .= '<div class="panel panel-default">'."\n";
            foreach($dictionaryDefinitions as $elmnt){
                $out .= '<div class="panel-body">'."\n".'<span class="infinitive">' . 
                    $infinitive . 
                    '</span> : <span class="catgram">' . 
                    $elmnt['catgram'] . 
                    '</span>, <span class="definition">' . 
                    $elmnt['definition'] . 
                    '</span></div><div class="panel-footer">' .
                    $creditDefinition . 
                    '</div>'."\n";
            } // foreach

            $out .= '</div>'."\n".'</div>' . "\n";
     
        } // if !empty

    
        $out .= $this->formatConjugation($conjugated);
        return $out; 
    } // convertConjugation

    /**
    * \brief a heavy loaded function used as helper for convertConjugation() where a the HTML writing takes place
    * \param $conjugated an associative array of the conjugation data
    * \return a HTML string
    */
    private function formatConjugation($conjugated){
        $dialect = $conjugated["dialect"];
        $conjugations = $conjugated["conjugations"];
        $desinenceLengths = $conjugated["desinenceLengths"];

        $ModesArray = array();
    
        // for each temps
        for ($i=ConjugationBase::IND_PRESENT;$i < ConjugationBase::CONDITIONAL +1 ;$i++){
            $conjugation = $conjugations[$i];

            switch($i){
            case ConjugationBase::IND_PRESENT : $mode = 'Indicatiu'; $ModesArray['Indicatiu']= array(); $o = "<div class=\"indicative\"><span class=\"label_mode\">Indicatiu</span><br>\n"; break;
            case ConjugationBase::INFINITIVE  : $mode = 'Formas impersonalas'; $ModesArray['Formas impersonalas']= array(); $o = "\n</div><br>\n<div class=\"impersonal_forms\"><span class=\"label_mode\">Formas impersonalas</span><br>\n"; break;
            case ConjugationBase::IMPERATIVE  : $mode = 'Imperatiu'; $ModesArray['Imperatiu']= array(); $o = "\n</div><br>\n<div class=\"imperative\"><span class=\"label_mode\">Imperatiu</span><br>\n"; break;
            case ConjugationBase::SUBJ_PRESENT: $mode = 'Subjontiu'; $ModesArray['Subjontiu']= array(); $o = "\n</div><br>\n<div class=\"subjunctive\"><span class=\"label_mode\">Subjontiu</span><br>\n"; break;
            case ConjugationBase::CONDITIONAL : $mode = 'Condicional'; $ModesArray['Condicional']= array(); $o = "\n</div><br>\n<div class=\"conditional\"><span class=\"label_mode\">Condicional</span><br>\n"; break;
            }
      
            // big dispatch
            // Each temps is dispatched in its own mode        
            switch($mode){
            case "Indicatiu" :
                $ModesArray['Indicatiu'][] = $conjugation; 
                break; 
            case "Formas impersonalas" :
                $ModesArray['Formas impersonalas'][] = $conjugation; 
                break; 
            case "Imperatiu" :
                $ModesArray['Imperatiu'][] = $conjugation; 
                break; 
            case "Subjontiu" :
                $ModesArray['Subjontiu'][] = $conjugation; 
                break; 
            case "Condicional" :
                $ModesArray['Condicional'][] = $conjugation; 
                break; 
            } // switch
        } // for
    
        /**
        *  HTML and CSS code
        */ 
        $out = '';

        $out .= '<div class="row">' . "\n"; // ROW 

        /**
	* INDICATIVE
	*/
        $ary = $ModesArray['Indicatiu'];
        $persons = $this->getPersonsArray();
        $tempses = array("present","imperfach","preterit","futur");
        $out .= '<div class="indicative col-sm-6">' . "\n" . '<table>'."\n".'<tbody>' . "\n";
        $out .= '<tr><th colspan="5" class="mode">Indicatiu</th></tr>' . "\n";
        $j = 0;
        $dLengthsPresent = explode(',', $desinenceLengths[ConjugationBase::IND_PRESENT]); 
        $dLengthsImperfect = explode(',', $desinenceLengths[ConjugationBase::IND_IMPERFECT]); 
        $dLengthsPreterit = explode(',', $desinenceLengths[ConjugationBase::IND_PRETERIT]); 
        $dLengthsFuture = explode(',', $desinenceLengths[ConjugationBase::IND_FUTURE]); 
        $present   = $ary[0];
        $imperfect = $ary[1];
        $preterit  = $ary[2];
        $future    = $ary[3];
      
        $replace = '<span class="radical">${1}</span><span class="desinence">${2}</span>';

        $out .= '<tr><th></th><th class="tempses">Present</th><th class="tempses">Imperfach</th><th class="tempses">Preterit</th><th class="tempses">Futur</th></tr>' . "\n";
	
        for($i=0;$i<6;$i++){
            $pattern = '/^(.*?)(.{'.$dLengthsPresent[$i].'})$/';
            $pres = utf8_encode(preg_replace($pattern,$replace,utf8_decode($present[$i])));
            $pattern = '/^(.*?)(.{'.$dLengthsImperfect[$i].'})$/';
            $imp = preg_replace($pattern,$replace,$imperfect[$i]);
            $pattern = '/^(.*?)(.{'.$dLengthsPreterit[$i].'})$/';
            $pret = preg_replace($pattern,$replace,$preterit[$i]);
            $pattern = '/^(.*?)(.{'.$dLengthsFuture[$i].'})$/';
            $fut = preg_replace($pattern,$replace,$future[$i]);

            $out .= "<tr><td><span class=\"persons\">$persons[$i]</span></td><td>$pres</td><td>$imp</td><td>$pret</td><td>$fut</td></tr>"  . "\n";
        }

        $out .= '</tbody>'."\n".'</table>'."\n".'</div>'."\n";
   
        /**
	* IMPERSONAL FORMS
	*/
	$ary = $ModesArray['Formas impersonalas'];   
        $out .= '<div class="impersonal_forms col-sm-3"><table>'. "\n". '<tbody>' . "\n";
        $out .= '<tr><th class="mode">Formas impersonalas</th></tr><tr>' . "\n";  
        $out .= '<tr><th class="tempses">Infinitiu</th></tr>';
        $infinitive = $ary[0];

        $dLengthsInfinitive = explode(',', $desinenceLengths[ConjugationBase::INFINITIVE]); 
        $pattern = '/^(.*?)(.{'.$dLengthsInfinitive[0].'})$/';
        $inf = preg_replace($pattern,$replace,$infinitive[0]);
        $out .= "<tr><td>$inf</td></tr>" . "\n";
        $out .= '</tbody>'."\n".'</table>'."\n";

        $out .= '<table>' . "\n".'<tbody>' . "\n";
        $out .= '<tr><th class="tempses">Participi passat</th></tr>' . "\n";
        $past_particle = $ary[2];
        $dLengthsPastParticiple = explode(',', $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]); 
        $pattern = '/^(.*?)(.{'.$dLengthsPastParticiple[0].'})$/';
        $pastM = preg_replace($pattern,$replace,$past_particle[0]);
        $pattern = '/^(.*?)(.{'.$dLengthsPastParticiple[1].'})$/';
        $pastF = preg_replace($pattern,$replace,$past_particle[1]);

        $out .= "<tr><td>$pastM, $pastF</td></tr>" . "\n";
        $out .= '</tbody>' . "\n".'</table>'."\n";

        $out .= '<table>'."\n".'<tbody>' . "\n";
        $out .= '<tr><th class="tempses">Gerondiu</th></tr>' . "\n";
        $gerund = $ary[1];
        $dLengthsGerund = explode(',', $desinenceLengths[ConjugationBase::GERUND]); 
        $pattern = '/^(.*?)(.{'.$dLengthsGerund[0].'})$/';
        $ger = preg_replace($pattern,$replace,$gerund[0]);
        $out .= "<tr><td>en $ger</td></tr>" . "\n";
        $out .= '</tbody>'."\n".'</table>'."\n".'</div>'."\n";

        /**
	* IMPERATIVE
	*/
        $ary = $ModesArray['Imperatiu'];   
        $out .= '<div class="imperative col-sm-3">'."\n".'<table>'."\n".'<tbody>'."\n";
        $out .= '<tr><th colspan="2" class="mode">Imperatiu</th></tr><tr>';
    
        $out .= '<tr><th class="tempses">forma positiva</th><th class="tempses">forma negativa</th></tr>';
        $imperative = $ary[0];
    
        for($j=0;$j<3;$j++){
            $p = $j + 3;
            $dLengthsImperative = explode(',', $desinenceLengths[ConjugationBase::IMPERATIVE]); 
            $pattern = '/^(.*?)(.{'.$dLengthsImperative[$j].'})$/';
            $impPos = preg_replace($pattern,$replace,$imperative[$j]);
            $pattern = '/^(.*?)(.{'.$dLengthsImperative[$p].'})$/';
            $impNeg = preg_replace($pattern,$replace,$imperative[$p]);
            // special case for impersonal verbs imperative
            if((empty($impPos)||$impPos =='<span class="radical"></span><span class="desinence"></span>') && empty($impNeg)){
                $out .= "<tr><td></td><td></td></tr>";
            }else{
                $neg = $dialect=='lengadocian'?'':'ne '; // in Gascon the completed negative form is NE imperative PAS
                $out .= "<tr><td>$impPos !</td><td>$neg$impNeg pas !</td></tr>";
            } // if
        }
    
        $out .= '</tbody>'."\n".'</table>'."\n".'</div>'."\n";

        $out .= '</div> <!--end of row-->' . "\n"; // END OF ROW

        $out .= '<div>' . "\n"; // ROW
    
        /**
	* SUBJUNCTIVE
	*/
        $ary = $ModesArray['Subjontiu'];   
        $out .= '<div class="subjunctive col-sm-6">'."\n".'<table>'."\n".'<tbody>'."\n";
        $out .= '<tr><th colspan="3" class="mode">Subjontiu</th></tr>'."\n";    
        $out .= '<tr><th></th><th class="tempses">Present</th><th class="tempses">Passat</th></tr>'."\n";
        $subjunctive_present = $ary[0];
        $subjunctive_past    = $ary[1];
    
        for($j=0;$j<6;$j++){
            $dLengthsSubjPres = explode(',', $desinenceLengths[ConjugationBase::SUBJ_PRESENT]); 
            $pattern = '/^(.*?)(.{'.$dLengthsSubjPres[$j].'})$/';
            $subjPres = preg_replace($pattern,$replace,$subjunctive_present[$j]);
            $dLengthsSubjImp = explode(',', $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]); 
            $pattern = '/^(.*?)(.{'.$dLengthsSubjImp[$j].'})$/';
            $subjPast = preg_replace($pattern,$replace,$subjunctive_past[$j]);

            $out .= "<tr><td><span class=\"persons\">$persons[$j]</span></td><td>$subjPres</td><td>$subjPast</td></tr>"."\n";
        }
    
        $out .= '</tbody>'."\n".'</table>'."\n".'</div>'."\n";


        /**
	* CONDITIONAL
	*/
        $ary = $ModesArray['Condicional'];   
        $out .= '<div class="conditional col-sm-6">'."\n".'<table>'."\n".'<tbody>'."\n";
        $out .= '<tr><th  colspan="2" class="mode">Condicional</th></tr><tr>'."\n";    
        $out .= '<tr><th></th><th class="tempses">Present</th></tr>'."\n";
        $conditional = $ary[0];
    
        for($j=0;$j<6;$j++){
            $dLengthsConditional = explode(',', $desinenceLengths[ConjugationBase::CONDITIONAL]); 
            $pattern = '/^(.*?)(.{'.$dLengthsConditional[$j].'})$/';
            $cond = preg_replace($pattern,$replace,$conditional[$j]);

            $out .= "<tr><td><span class=\"persons\">$persons[$j]</span></td><td>$cond</td></tr>"."\n";
        }
    
        $out .= '</tbody>'."\n".'</table>'."\n".'</div>'."\n";
        $out .= '</div> <!--end of row-->' . "\n"; // END OF ROW
    
        return $out;  
    } // formatConjugation

    /**
    * \return an array of the code for persons
    */
    private function getPersonsArray(){
        $ary = array();
        $ary[] = 's1'; 
        $ary[] = 's2'; 
        $ary[] = 's3'; 
        $ary[] = 'p1'; 
        $ary[] = 'p2'; 
        $ary[] = 'p3';
     
        return $ary;
    }
    /**
    * \brief a placeholder function to convert an array into HTML
    * \param $list
    * \return a HTML string
    */
    public function convertArray(array $list){
        $o = "";
        if (count($list) > 0){
            $o = "<table style=\"width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">";
            $o .= "<tbody>";

            $cptr = 0;

            foreach($list as $key => $value){

                if (!$cptr % 5){
                    $o .= '<tr align=\"center\">' . l("$key", "$value");
                }
                $o .= "<td>" . l("$key","$value");

                if ($cptr % 5 == 4){
                    $o .= _nl("</tr>");
                }
                $cptr++;
            } // for
  
            $o .= _nl("</tbody>");
            $o .= _nl("</table>");
        } // if
        return $o;
    } // convertArray

    /**
    * \brief does nothing
    */
    public function convertSelect(array $conjugation){
  
    }

    /**
    * \brief converts a word coming from a verb conjugated,  
    * \param $data an objet w/ all the info from an indexed conjugation
    * \return a string
    */
    public function convertIndexedData($data){
        if(empty($data)){
            echo("Conjugation not found");
            return "";
        }
        $converter = new ConverterIndexation();
        $arrPos = $converter->decodePOS($data->pos);
	
        $o = '<div class="indexedData">';
        $o .='<table><tbody>';
        $o .='<tr><td>conjugation</td><td><span class="indexed_conjugation">' . $data->conjugation . '</span></td></tr>';
        $o .='<tr><td>infinitive</td><td><span class="indexed_verb">' . $data->verb . '</span></td></tr>';
        $o .='<tr><td>index</td><td><span class="indexed_row">' . $data->row . '</span></td></tr>';
        $dialect = $converter->decodeDialect($data->dialect);
        $o .='<tr><td>dialect</td><td><span class="indexed_dialect">' . $dialect . '</span></td></tr>';
        $o .='<tr><td>model</td><td><span class="indexed_nummodel">' . $data->nummodel . '</span></td></tr>';
        $o .='<tr rowspan="2"><td>EAGLES POS</td><td><span class="indexed_POS">' . $data->pos . '</span></td></tr>';
        $o .= '<tr><td>EAGLES POS decoded</td><td>' . $this->convertPOS($arrPos). '</td></tr>'; 
        $o .= '</tbody></table>';
        $o .= '</div>';
        return $o;
    }  // convertIndexedData

    /**
    * \brief a POS part of speech array is converted in HTML array
    * \param $aPos an array containing POS data
    * \return a HTML string
    */
    private function convertPOS(array $aPos){
        $type = $aPos['type'];   	  
        $person = $aPos['person'];
        $gender = $aPos['gender'];
        $number = $aPos['number'];
        $finiteness = $aPos['finiteness'];
        $tense = $aPos['tense'];
        $voice = $aPos['voice'];
        $aspect = $aPos['aspect'];
        $separability = $aPos['separability'];
        $reflexivity = $aPos['reflexivity'];
        $auxiliary = $aPos['auxiliary'];
        $mood = $aPos['mood'];

        $o = '<div class="decoded_POS">';
        $o .= '<table border="0"><tbody>';
        $o .= '<tr><td><strong>type</strong></td><td><span class="POS_type">' . $type . '</span></td></tr>';
        $o .= '<tr><td><strong>person</strong></td><td><span class="POS_person">' . $person . '</span></td></tr>';
        $o .= '<tr><td><strong>gender</strong></td><td><span class="POS_gender">' . $gender . '</span></td></tr>';
        $o .= '<tr><td><strong>number</strong></td><td><span class="POS_number">' . $number . '</span></td></tr>';
        $o .= '<tr><td><strong>finiteness</strong></td><td><span class="POS_finiteness">' . $finiteness . '</span></td></tr>';
        $o .= '<tr><td><strong>mood</strong></td><td><span class="POS_mood">' . $mood . '</span></td></tr>';
        $o .= '<tr><td><strong>tense</strong></td><td><span class="POS_tense">' . $tense . '</span></td></tr>';
        $o .= '<tr><td><strong>voice</strong></td><td><span class="POS_voice">' . $voice . '</span></td></tr>';
        $o .= '<tr><td><strong>aspect</strong></td><td><span class="POS_aspect">' . $aspect . '</span></td></tr>';
        $o .= '<tr><td><strong>separability</strong></td><td><span class="POS_separability">' . $separability . '</span></td></tr>';
        $o .= '<tr><td><strong>reflexivity</strong></td><td><span class="POS_reflexivity">' . $reflexivity . '</span></td></tr>';
        $o .= '<tr><td><strong>auxiliary</strong></td><td><span class="POS_auxiliary">' . $auxiliary . '</span></td></tr>';
        return $o . "</tbody></table></div>";
    } // convertPOS
} // class ConverterHTML

?>