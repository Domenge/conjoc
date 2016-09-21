<?php
/**
 * \file      ConjugationBase.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     Base class for worker class Conjugation
 *
 * \details   implements everything possible and leave some abstract fonctions to be implemented by descendants.
*/
abstract class ConjugationBase implements iDisplayable, iConjugation{
/* TO BE REMOVED
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
  private $_row;
*/
/**
 * \brief    List of constants for the indexes  
 * \details  Indexes of an arrray returned by the conjugation processor
 *           Tempses and some geographical variances for gascon dialect
 */
  const LENGTH_CONJUGATION_ARRAY = 11;
  const IND_PRESENT = 0; /**< indicative present*/
  const IND_IMPERFECT = 1; /**< indicative imperfect*/
  const IND_PRETERIT = 2; /**< indicative preterit*/
  const IND_FUTURE = 3; /**< indicative future*/
  const INFINITIVE = 4; /**< mood infinitive*/ 
  const GERUND = 5; /**< mood gerundive*/
  const PAST_PARTICIPLE = 6; /**< past participle*/
  const IMPERATIVE = 7; /**<mood imperative*/
  const SUBJ_PRESENT = 8; /**<subjunctive present*/
  const SUBJ_IMPERFECT = 9;/**<subjunctive imperfect*/
  const CONDITIONAL = 10;/**<conditional*/
  const E_FIRST = 20; /**<EAST*/
  const E_IND_PRETERIT = 22; /**<EASTERN VARIANCE for PRETERIT*/
  const E_SUBJ_IMPERFECT = 29; /**<EASTERN VARIANCE for SUBJ IMPERFECT*/
  const E_CONDITIONAL = 30; /**<EASTERN VARIANCE for CONDITIONAL*/
  const N_FIRST = 40; /**<NORTH*/
  const N_IND_PRETERIT = 42; /**<NORTHERN VARIANCE for PRETERIT*/
  const N_SUBJ_IMPERFECT = 49; /**<NORTHERN  VARIANCE for SUBJ IMPERFECT*/ 
  const N_CONDITIONAL = 40; /**<NORTHERN VARIANCE for CONDITIONAL*/
  const SW_FIRST = 60; /**<SOUTH WEST*/
  const P_FIRST = 80; /**<to be documented*/

/**
*	VERBAL GROUPS
*
*/
  const AUXILLIARY = 0;/**<auxiliary*/
  const FIRST_GROUP = 1;/**<first group*/
  const SECOND_GROUP = 2;/**<second group*/
  const THIRD_GROUP = 3;/**<third group*/

  const LAST_NORMAL_TEMPS = ConjugationBase::CONDITIONAL; /**< the end binding*/
/**
 * \brief      Constructor
 * \details    points to the manager 
 *                  
 * \param      $manager the conjugation mananager.
 * \return     ConjugationBase object.
 */
  public function __construct(ConjugationManagerBase $manager){
    $this->_manager= $manager;
  } // __construct


/**
 * \brief      a vowel detector
 * \details    
 *                  
 * \param      $root  the radical of the verb
 * \return     the vowel detected
 */
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


/**
 * \brief     vowel accentuated as tonic
 * \details   in occitan language a tonic vowel is distinguised by the accentuation 
 *                  
 * \param      $root  the radical of the verb
 * \return     the tonic vowel detected
 */
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

/**
 * \brief      neutralize the accent
 * \details    takes an infinitive and remove the accent
 *                  
 * \param      $infinitive 
 * \param      $vowelGrave the vowel to neutralize
 * \return     the infinitive
 */
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

/**
 * \brief      neutralizes the tonic accent
 * \details    takes an infinitive and remove the accent
 *                  
 * \param      $infinitive 
 * \param      $vowelGrave the vowel to neutralize
 * \return     the infinitive
 */
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

/**
 * \brief      tells if the accent must be neutralized
 * \details    takes an infinitive and remove the accent
 *                  
 * \param      $infinitive 
 * \param      $vowelGrave the vowel to neutralize
 * \return     a boolean
 */
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

/**
 * \brief      fixes a string according to the occitan phonologic rules
 * \details    
 *                  
 * \param      $string
 * \return     the string altered
 */
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

/**
 * \brief      builds an associative array w/ all informations processed by the conjugation manager  
 * \details    gets all the information from the manager 
 *                  
 * \return     the associative array for the conjugation
 */
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
    $arr["row"]              = $this->getRow();

    return $arr;
  } // conjugate

/**
 * \brief      dummy function 
 * \details    does nothing
 *                  
 * \param      $radical
 * \param      $desinence
 * \return     the radical
 */
  protected function fixRadical($radical, $desinence){
    return $radical;
  } // fixRadical

/**
 * \brief      dummy function 
 * \details    does nothing
 *                  
 * \param      $desinence
 * \return     the desinence
 */
  protected function fixDesinence($desinence){
    return $desinence;
  } // fixDesinence


/**
 * \brief      dummy function 
 * \details    does nothing
 *                  
 * \return     the desinence lengths array
 */
  protected function getDesinenceLengthArray(){
      return array(); // empty by default
  } // fixDesinence


/**
 * \brief      dummy function 
 * \details    does nothing
 *                  
 * \return     the standard conjugation array
 */
  protected function getStandardConjugation(){
    return array();
  } // getStandardConjugation


  public function getGroup(){return $this->_manager->getGroup();}	/**< accessor to a manager method*/
  public function getVerb(){return $this->_manager->getVerb();}		/**< accessor to a manager method*/
  public function getVerbModel(){return $this->_manager->getVerbModel();}    /**< accessor to a manager method*/
  public function getVerbModelObject($nummodel){return $this->_manager->getVerbModelObject($nummodel);}	/**< accessor to a manager method*/

  public function getlibModel(){return $this->_manager->getLibModel();}	/**< accessor to a manager method*/
  public function getComments(){return $this->_manager->getComments();}	/**< accessor to a manager method*/
  public function getManager(){return $this->_manager;}			/**< accessor to a manager method*/
  public function getVerbId(){return $this->_manager->getVerbId();}	/**< accessor to a manager method*/
  public function getLocalization(){return $this->_manager->getLocalization();}	      /**< accessor to a manager method*/
  public function getAlias(){return $this->_manager->getAlias();}		      /**< accessor to a manager method*/
  public function getSeeAlso(){return $this->_manager->getSeeAlso();}		      /**< accessor to a manager method*/
  public function getDialect(){return $this->_manager->getDialect();}		      /**< accessor to a manager method*/
  public function getConjugations(){return $this->_manager->getConjugations();}	      /**< accessor to a manager method*/

/**
 * \brief      asks the manager the verb definition from a dictionary
 * \details    gets the infinitive and passes it to the manager method to seek the dictionary definition
 *                  
 * \return     the dictionary definition
 */
public function getDictionaryDefinition(){
      $conjugations = $this->getConjugationArray();
      $infinitive = $conjugations[ConjugationBase::INFINITIVE];
      return $this->_manager->getDictionaryDefinition($infinitive);
  }
  public function getRow(){return $this->_manager->getRow();}	/**< accessor to a manager method*/

  abstract public function display();				/**< differs the implementation to the descendants*/
  abstract protected function getConjugationArray();		/**< differs the implementation to the descendants*/
} // class ConjugationBase

?>
