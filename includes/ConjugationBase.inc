<?php

abstract class ConjugationBase implements iDisplayable{
  private $_group;
  private $_standardconjugation;
  private $_name;
  private $_model;
  private $_libModel;
  private $_comments;
  private $_standardConjugation;
  private $_manager;
  private $_id;
  private $_localization;

  const LENGTH_CONJUGATION_ARRAY = 11;
  const IND_PRESENT = 0;
  const IND_IMPERFECT = 1;
  const IND_PRETERIT = 2;
  const IND_FUTURE = 3;
  const INFINITIVE = 4;
  const GERUND = 5;
  const PAST_PARTICIPLE = 6;
  const IMPERATIVE = 7;
  const SUBJ_PRESENT = 8;
  const SUBJ_IMPERFECT = 9;
  const CONDITIONAL = 10;
  const E_FIRST = 20;
  const E_IND_PRETERIT = 22;
  const E_SUBJ_IMPERFECT = 29;
  const E_CONDITIONAL = 30;
  const N_FIRST = 40;
  const N_IND_PRETERIT = 42;
  const N_SUBJ_IMPERFECT = 49;
  const N_CONDITIONAL = 40;
  const SW_FIRST = 60;
  const P_FIRST = 80;
	
  const AUXILLIARY = 0;
  const FIRST_GROUP = 1;
  const SECOND_GROUP = 2;
  const THIRD_GROUP = 3;

  const LAST_NORMAL_TEMPS = ConjugationBase::CONDITIONAL;

  public function __construct(ConjugationManagerBase $manager){
    $this->_manager= $manager;
  } // __construct


  protected function isVowelDetected($root){
    $pattern = '/.*?è.*?/';
    if (preg_match($pattern, $root)){
      return 'è';
    }
    $pattern = '/.*?ò.*?/';
    if (preg_match($pattern, $root)){
      return 'ò';
    }
    $pattern = '/.*?à.*?/';
    if (preg_match($pattern, $root)){
      return 'à';
    }
  } // isVowelDetected

  protected function isTonicDetected($root){
    $pattern = '/.*?é.*?/';
    if (preg_match($pattern, $root)){
      return "é";
    }

    $pattern = '/.*?ó.*?/';
    if (preg_match($pattern, $root)){
      return 'ó';
    }
    $pattern = '/.*?á.*?/';
    if (preg_match($pattern, $root)){
      return 'á';
    }
    $pattern = '/.*?ú.*?/';
    if (preg_match($pattern, $root)){
      return 'ú';
    }
    $pattern = '/.*?í.*?/';
    if (preg_match($pattern, $root)){
      return 'í';
    }
  } // isTonicDetected

  protected function neutralizeVowel($infinitive,$vowelGrave){
    switch($vowelGrave){
      case 'è' : 
        $pattern = '/(.*?)è(.*?)/'; $replacement = '${1}e${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'à' :	
        $pattern = '/(.*?)à(.*?)/'; $replacement = '${1}a${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'ò' :	
        $pattern = '/(.*?)ò(.*?)/'; $replacement = '${1}o${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'ò' :	
        $pattern = '/(.*?)ò(.*?)/'; $replacement = '${1}o${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'ò' :	
        $pattern = '/(.*?)ò(.*?)/'; $replacement = '${1}o${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'ò' :	
        $pattern = '/(.*?)ò(.*?)/'; $replacement = '${1}o${2}';
        return preg_replace($pattern, $replacement, $infinitive);
    }
    return $infinitive;
  } // neutralizeVowel

  protected function neutralizeTonic($infinitive,$tonic){
  
    switch($tonic){
      case 'á' : 
        $pattern = '/(.*?)á(.*?)/'; $replacement = '${1}a${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'é' : 
        $pattern = '/(.*?)é(.*?)/'; $replacement = '${1}e${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'í' :	
        $pattern = '/(.*?)í(.*?)/'; $replacement = '${1}i${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'ó' :	
        $pattern = '/(.*?)ó(.*?)/'; $replacement = '${1}o${2}';
        return preg_replace($pattern, $replacement, $infinitive);
      case 'ú' :	
        $pattern = '/(.*?)ú(.*?)/'; $replacement = '${1}u${2}';
        return preg_replace($pattern, $replacement, $infinitive);
    }
    return $infinitive;

  } // neutralizeTonic

  protected function mustNeutralizeVowel($temps,$person){
    $arrtemps = array(ConjugationBase::IND_PRESENT,ConjugationBase::SUBJ_PRESENT);
    $arrperson = array(0,1,2,5);
    $arrpersonImp = array(0,3);
    if ((int)$temps == ConjugationBase::IMPERATIVE and in_array($person,$arrpersonImp)){
      return false;
    }
    if (in_array((int)$temps,$arrtemps) and in_array($person,$arrperson)){
      return false;
    }
    return true;
  } // mustNeutralizeVowel

  protected function phonologicFixes($string){
    // Corrections
    if (preg_match("/j-[ieè]/", $string )) {
      // j to g
      $patterns = array();
      $patterns[0] = '/j-i/';
      $patterns[1] = '/j-e/';
      $patterns[2] = '/j-è/';
      $replacements = array();
      $replacements[2] = 'g-i';
      $replacements[1] = 'g-e';
      $replacements[0] = 'g-è';
      //echo "correction j-[ieé]";
      return preg_replace($patterns, $replacements, $string);
    }

    if (preg_match("/c-[ieè]/", $string )) {
      // c to qu
      $patterns = array();
      $patterns[0] = '/c-i/';
      $patterns[1] = '/c-e/';
      $patterns[2] = '/c-è/';
      $replacements = array();
      $replacements[2] = 'qu-i';
      $replacements[1] = 'qu-e';
      $replacements[0] = 'qu-è';
      return preg_replace($patterns, $replacements, $string);
    }

    // ç to c
    if (preg_match("/ç-[ieè]/", $string )) {
      $patterns = array();
      $patterns[0] = '/ç-i/';
      $patterns[1] = '/ç-e/';
      $patterns[2] = '/ç-è/';
      $replacements = array();
      $replacements[2] = 'c-i';
      $replacements[1] = 'c-e';
      $replacements[0] = 'c-è';
      return preg_replace($patterns, $replacements, $string);
    }
    // Corrections


    if (preg_match("/g-[ieèo]/", $string ) && $this->getVerbModel() == '104') {
      // g to gu
      $patterns = array();
      $patterns[0] = '/g-i/';
      $patterns[1] = '/g-e/';
      $patterns[2] = '/g-è/';
      $replacements = array();
      $replacements[2] = 'gu-i';
      $replacements[1] = 'gu-e';
      $replacements[0] = 'gu-è';
      return preg_replace($patterns, $replacements, $string);
    }

    if (preg_match("/gu-[ieè]/", $string )) {
      // gu[ieè] to g[ieè]
      $patterns = array();
      $patterns[0] = '/gu-i/';
      $patterns[1] = '/gu-e/';
      $patterns[2] = '/gu-è/';
      $replacements = array();
      $replacements[2] = 'g-i';
      $replacements[1] = 'g-e';
      $replacements[0] = 'g-è';
      return preg_replace($patterns, $replacements, $string);
    }
    return $string;
  } // phonologicFixes

  public function conjugate(){
    $arr = array();

    if ($this->getVerbId() == 0){
       return $arr;
    }

    $conjugations = $this->getConjugationArray();


    $arr["id"]               = $this->getVerbId();
    $arr["name"]             = $this->getVerb();
    $arr["infinitive"]       = $conjugations[ConjugationBase::INFINITIVE];
    $arr["model"]            = $this->getVerbModel();
    $arr["see_also"]         = $this->getSeeAlso();
    $arr["comments"]         = $this->getComments();
    $arr["libmodel"]         = $this->getLibModel();
    $arr["dialect"]          = $this->getDialect();
    $arr["localization"]     = $this->getLocalization();
    $arr["comments"]         = $this->getComments();
    $arr["conjugations"]     = $conjugations;
    $arr["desinenceLengths"] = $this->getDesinenceLengthArray();
    $arr["dictionaryDefinition"] = $this->getDictionaryDefinition();
  
    return $arr;
  }

  protected function fixRadical($radical, $desinence){
    return $radical;
  } // fixRadical

  protected function fixDesinence($desinence){
    return $desinence;
  } // fixDesinence

  protected function getDesinenceLengthArray(){
      return array(); // empty by default
  } // fixDesinence

  protected function getStandardConjugation(){
    return array();
  } // getStandardConjugation


  public function getGroup(){return $this->_manager->getGroup();}
  public function getVerb(){return $this->_manager->getVerb();}
  public function getVerbModel(){return $this->_manager->getVerbModel();}
  public function getVerbModelObject($nummodel){return $this->_manager->getVerbModelObject($nummodel);}

  public function getlibModel(){return $this->_manager->getLibModel();}
  public function getComments(){return $this->_manager->getComments();}
  public function getManager(){return $this->_manager;}
  public function getVerbId(){return $this->_manager->getVerbId();}
  public function getLocalization(){return $this->_manager->getLocalization();}
  public function getAlias(){return $this->_manager->getAlias();}
  public function getSeeAlso(){return $this->_manager->getSeeAlso();}
  public function getDialect(){return $this->_manager->getDialect();}
  public function getConjugations(){return $this->_manager->getConjugations();}
  public function getDictionaryDefinition(){
      $conjugations = $this->getConjugationArray();
      $infinitive = $conjugations[ConjugationBase::INFINITIVE];
      return $this->_manager->getDictionaryDefinition($infinitive);
  }

  abstract public function display();
  abstract protected function getConjugationArray();
} // class ConjugationBase

?>
