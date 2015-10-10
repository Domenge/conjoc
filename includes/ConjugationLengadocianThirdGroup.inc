<?php


class ConjugationLengadocianThirdGroup extends ConjugationBase{

    protected function getStandardConjugation(){
  	    $arr = array();
  	    $arr['00'] =  "i,es,,èm,ètz,on";
  	    $arr['01'] =  "iái,iás,iá,iam,iatz,ián";
  	    $arr['02'] =  "èri,ères,èt,èrem,èretz,èron";
  	    $arr['03'] =  "rai,ràs,rà,rem,retz,ràn";
  	    $arr['04'] =  "";
  	    $arr['05'] =  "ent";
  	    $arr['06'] =  "ut,uda";
  	    $arr['07'] =  ",am,ètz,as,am,atz";
  	    $arr['08'] =  "a,as,a,am,atz,an";
  	    $arr['09'] =  "èsse,èsses,èsse,èssem,èssetz,èsson";
  	    $arr['10'] =  "riái,riás,riá,riam,riatz,rián";

  	    return $arr;
    } // getStandardConjugation

    private function getMixedConjugation($model){
        $arr = $this->getStandardConjugation($model);
        $line = $this->getVerbModelObject($model);
	  
        $label = $line->label_conjugation;
        $conjugations= $line->conjugations;

        $tempses = explode('|', $conjugations);

        // for each conjugation
        $arrTemps = array();

        foreach($tempses as $temps){
    	    $arrConjugations = explode(':', $temps);
    	    $index = $arrConjugations[0];
    	    $conjugationStr = (isset($arrConjugations[1]))?$arrConjugations[1]:"";
 
            if ($conjugationStr){
                $arr[$index]= $conjugationStr; 
    	    } // if
        } // foreach 

        return $arr;
    } // getMixedConjugation($model)

    public function display(){
        return "ConjugationLengadocianThirdGroup $this->_name " . $this->conjugate;
    } // display
  
    protected function getConjugationArray(){

        $infinitive = $this->getVerb();
        $vowelGrave = $this->isVowelDetected($infinitive);
        $tonic = $this->isTonicDetected($infinitive);
        $model = $this->getVerbModel();
        $arr = $this->getMixedConjugation($model);

        $patterns = array();
        $patterns[1] = '/er$/';
        $patterns[0] = '/re$/';
        $replacements = array();
        $replacements[1] = '';
        $replacements[0] = '';
        $rootTruncated = preg_replace($patterns, $replacements, $infinitive);
        $conjugations = array();

        $rootTruncated = $this->neutralizeTonic($rootTruncated,$tonic);

        if ($model == '373'){
            // prendre
            $pattern = '/nd$/';
            $replacement = '';
            $rootTruncated = preg_replace($pattern, $replacement, $rootTruncated);
        }

        // for each temps
        $j=0;
        foreach($arr as $lib=>$desinence){
            $desinences = explode(',', $desinence);
            $i=0;
            $tempsConjugated = array();

            foreach ($desinences as $elmnt){
                $rootDotLess = $rootTruncated;
                // if there are dots in the desinence they are interpreted as backspaces
                $count = substr_count($elmnt, '.');
                if ($count){
                    $rootDotLess = substr($rootTruncated, 0, -1*(int)$count);
                }
                $elmnt = str_replace ( '.' , '', $elmnt );
      
                if ($this->mustNeutralizeVowel($lib,$i)){
                    $rootSaved = $this->neutralizeVowel($rootDotLess,$vowelGrave);
                }else{
                    $rootSaved = $rootDotLess;
                }

                $root = $this->fixRadical($rootSaved,$elmnt);
                $elmnt = $this->fixDesinence($elmnt);
                $tempsConjugated[] = $root.$elmnt; 
                $i++;
            } // for desinences
            if ($j == ConjugationBase::INFINITIVE){ //
                $conjugations[] = array($infinitive);
            }else{ // if
                $conjugations[] = $tempsConjugated;
            }
            $j++;
        } // foreach temps

        return $conjugations;
    } // getConjugationArray
  
    protected function fixRadical($radical,$desinence){
        return $radical;
    } // fixRadical
  
    protected function fixDesinence($desinence){
        return $desinence;
    } // fixDesinence

    public function getDesinenceLengthArray(){
        $desinenceLengths = array();
        $desinenceLengths[]="1,2,1,2,3,2";
        $desinenceLengths[]="3,4,3,4,5,4";
        $desinenceLengths[]="3,4,2,4,5,4";
        $desinenceLengths[]="4,4,3,4,5,4";
        $desinenceLengths[]="2";
        $desinenceLengths[]="3";
        $desinenceLengths[]="1,2,3,2,2,3";
        $desinenceLengths[]="1,2,1,2,3,2";
        $desinenceLengths[]="4,5,4,4,6,5";
        $desinenceLengths[]="5,5,4,5,6,5";
        return $desinenceLengths;
    } // getDesinenceLengthArray
  
} // class ConjugationLengadocianThirdGroup

?>