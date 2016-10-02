<?php
/**
 * \file      ConjugationDataProviderBootstrap.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     worker classe for Bootstrap environment
 *
 * \details   
 */      
class ConjugationDataProviderBootstrap extends ConjugationDataProviderBase{
  private $cnx; /**< a database connection */

  /**
  * \return the connection
  */
  protected function getConnection(){
      return $this->cnx;
  }

/**
* \brief the Ctor
* \return the object
*/
  public function __construct($baseTableName){
      parent::__construct($baseTableName);
      $this->cnx = new mysqli("localhost","conjocuser","ADLcWBDV4zkdmnf0","conjoc");
      if (!$this->cnx->set_charset("utf8")) {
        printf("Error loading character set utf8: %s\n", $this->cnx->error);
        exit();
       } else {
  //	    printf("Current character set: %s\n", $cnx->character_set_name());
       }     
  } // __construct


/**
 * \brief      go get the verb from the verb w/ its model table
 * \details     
 *                  
 * \param      $verb infinitive of the verb
 * \return     an object on containing a verb.
 */
  public function getVerb($verb){
      $results = $this->getConnection()->query("SELECT * FROM " . $this->getBaseTableName() . "_verbsmodel WHERE verb ='$verb'");
      $objRet =  $results->fetch_object();
      $results->close();
      return $objRet;
    } // getVerb

/**
 * \brief      go get the verb from the verb w/ its model table
 * \details     
 *                  
 * \param      $id id of the verb
 * \return     an object on containing the verb.
 */
    public function getVerbById($id){
        $results = $this->getConnection()->query("SELECT * FROM " . $this->getBaseTableName() . "_verbsmodel WHERE id =$id");
        return $results->fetch_object();
    } // getVerbById

/**
 * \brief      go get the verb model by its number 
 * \details     
 *                  
 * \param      $numModel
 * \return     an object on containing the model of a verb.
 */
    public function getVerbModelObject($numModel){
        $results = $this->getConnection()->query("SELECT * FROM " . $this->getBaseTableName() . "_model WHERE nummodel='$numModel'");
        return $results->fetch_object();
    } // getVerbModelObject

/**
 * \brief      go get the list of verb models
 * \details     
 * \todo	  
 * \return     an empty array
 */
    public function getVerbsModels(){
    	    $queryCount = "SELECT count(*) AS cptr FROM `sauzet_verbsmodel`";	
            $results = $this->getConnection()->query($queryCount);
	    $cptrTotal = $results->fetch_object()->cptr;

	    $query = "select  nummodel, label_conjugation, verb_prime, (select count(*) FROM " . $this->getBaseTableName() . "_verbsmodel WHERE nummodel = mdl.nummodel) as cardModel FROM " . $this->getBaseTableName() . "_model mdl order by mdl.nummodel";
    $results = $this->getConnection()->query($query);
        $arrRet = array();

        while($line = $results->fetch_object()){
            $percent = sprintf("%.3f", (float)$line->cardModel/(float)$cptrTotal*100);
            $arrRet[] = "$line->nummodel\t$line->label_conjugation\t$line->verb_prime\t$percent";
        } // while

        return $arrRet;
    } // getVerbsModels
    
/**
 * \brief      
 * \details     
 * \todo	document this function                 
 * \return     an array of infinitives
 */
    public function getVerbsModelsMixed(){
    	$query = "SELECT  gm.nummodel AS numgm, gm.verb_prime as gverb, gm.label_conjugation as glabel, lm.nummodel as numlm, lm.verb_prime as lverb, lm.label_conjugation AS llabel FROM gascon_model as gm LEFT JOIN sauzet_model as lm  ON gm.nummodel = lm.nummodel " .
	"UNION ALL SELECT  gm0.nummodel AS numgm, gm0.verb_prime as gverb, gm0.label_conjugation as glabel, lm0.nummodel as numlm, lm0.verb_prime as lverb, lm0.label_conjugation AS llabel FROM gascon_model as gm0 RIGHT JOIN sauzet_model as lm0 ON gm0.nummodel = lm0.nummodel ".
	"WHERE   gm0.nummodel IS NULL ORDER BY COALESCE(numgm, numlm)";   
        $results = $this->getConnection()->query($query);
        $arrRet = array();

        while($line = $results->fetch_object()){
// print("$line->numlm,$line->llabel,$line->lverb,$line->numgm,$line->glabel,$line->gverb<br>");
	    $nummodel = $line->numlm;
	    $queryCount = "SELECT count(*) AS cptr FROM `sauzet_verbsmodel` where nummodel = '$nummodel' ";	
            $resultsInner = $this->getConnection()->query($queryCount);
	    $cptrLengadocian = $resultsInner->fetch_object()->cptr;
	    $cptrLengadocian = ($cptrLengadocian > 0)?$cptrLengadocian:'';
	    $nummodel = $line->numgm;
	    $queryCount = "SELECT count(*) AS cptr FROM `gascon_verbsmodel` where nummodel = '$nummodel' ";	
            $resultsInner = $this->getConnection()->query($queryCount);
	    $cptrGascon = $resultsInner->fetch_object()->cptr;
	    $cptrGascon = ($cptrGascon > 0)?$cptrGascon:'';
	    $arrInner = array($line->numlm,$line->llabel,$line->lverb,$cptrLengadocian,$line->numgm,$line->glabel,$line->gverb,$cptrGascon);
            $arrRet[] = $arrInner;
        } // while

        return $arrRet;
    } // getVerbsModelsMixed

/**
 * \brief      go get the 20 verbs most wanted
 * \details     
 *                  
 * \return     an array of infinitives
 */
    public function getTop20(){
        $results = $this->getConnection()->query("SELECT COUNT(*) as cpter, group_concat(cast(idverb as char)) as concat FROM " . $this->getBaseTableName() . "_access GROUP BY idverb ORDER BY cpter DESC LIMIT 20");
        $arrRet = array();
/*
  T O  B E  D O N E
  T O  B E  D O N E
  T O  B E  D O N E

  while($line = $results->fetch_object()){
  $arr = explode(',', $line->concat);
  $id = $arr[0];
  $id = isset($id)?$id:0;
  $resInner  = db_query("SELECT verb FROM ". $this->getBaseTableName() . "_verbsmodel WHERE id ='$id' LIMIT 1");
  $lineInner = $resInner->fetch_object();
  $arrRet[0] = $lineInner->verb;
  } // while
*/
        return $arrRet;
    } // getTop20

/**
 * \brief get the ids of the verbs w/ the same model except the current one 
 * \details     
 * \param  $verb the infinitive of the current verb 
 * \return     an array containing the ids of the verbs w/ the same models except the current verb 
 */
    public function getOthersInModel($verb){

        $count = $this->getCountOthersInModel($verb);

        if ($count <= ConjugationManagerBase::MAX_OTHERVERBS && $count){
            $arrRet = array();
        
            $query = 'SELECT * FROM '.
                $this->getBaseTableName() . '_verbsmodel as sv1,' .
                $this->getBaseTableName() . "_verbsmodel as sv2 where sv1.verb='$verb' and sv1.nummodel = sv2.nummodel and sv2.verb <> '$verb'";

            $results = $this->getConnection()->query($query);

            while($line = $results->fetch_object()){
                $arrRet[] = $line->verb;
            } // while
            return $arrRet;
        } // if
    } // getOthersInModel
    
/**
 * \brief  returns how many other verbs with the same model  
 * \details 
 * \param  $verb the infinitive of the current verb 
 * \return  a counter
 */
    public function getCountOthersInModel($verb){

        $query = 'SELECT count(*) as cptr FROM '.
            $this->getBaseTableName() . '_verbsmodel as sv1,' .
            $this->getBaseTableName() . "_verbsmodel as sv2 where sv1.verb='$verb' and sv1.nummodel = sv2.nummodel and sv2.verb <> '$verb'";
      
        $resultsCount = $this->getConnection()->query($query);

        $line = $resultsCount->fetch_object();
        return $line->cptr;
    } // getCountOthersInModel

/**
 * \brief  for each string go get the list of infinitive verbs beginning with the string
 * \details 
 * \param  $verb the infinitive of the current verb 
 * \return  an array of matches
 */
    public function getVerbAutoComplete($string){
        $matches = array();
        throw new Exception("getVerbAutoComplete not implemented.");
        return $matches;
    } // getVerbAutoComplete

/**
 * \brief  gets an infinitive at random
 * \details 
 * \return  an infinitive at random
 */
    public function getRandomVerb(){
        $results = $this->getConnection()->query("SELECT * FROM " . $this->getBaseTableName() . "_verbsmodel ORDER BY RAND() LIMIT 1");
        if (empty($results)){
            echo "results est vide";
        }
        $line = $results->fetch_object();
        $results->close();
        return($line->verb);
    } // getRandomVerb()

/**
 * \brief  gets an list of single infinitive in their model
 * \details 
 * \return  an array of infinitives
 */
    public function getSingleVerbs(){
        $results = $this->getConnection()->query("SELECT COUNT(*) as cpter, group_concat(verb) as concat FROM ". 
        $this->getBaseTableName() 
        . "_verbsmodel GROUP BY nummodel ORDER BY cpter ASC LIMIT 25");

        $arrRet = array();  

        while($line = $results->fetch_object()){

            if ($line->cpter == 1){
                $verb = $line->concat;
                if (strlen($verb) > 0){
                    $arrRet[] = $verb;
                } 
            }
        } // while
  
        return $arrRet;
    } // getSingleVerbs()

/**
 * \brief  returns the prefix of the verb build on semiauxiliary FAR
 * \details
 * \param  $verb the infinitive
 * \return  a string
 */
    public function getVerbFAR($verb){
        // returns the prefix of the verb build on semiauxiliary FAR
        $results = $this->getConnection()->query("SELECT SUBSTR( verb, 1, position( 'far' IN verb ) -1 ) as verbtrimmed FROM ".
        $this->getBaseTableName() 
        . "_verbsmodel where verb = '$verb'");
        $line = $results->fetch_object();
        return $line->verbtrimmed;  
    }

/**
 * \brief  returns the prefix of the verb build on semiauxiliary HAR
 * \details
 * \param  $verb the infinitive
 * \return  a string
 */
    public function getVerbHAR($verb){
        // returns the prefix of the verb build on semiauxiliary HAR gascon
        $results = $this->getConnection()->query("SELECT SUBSTR( verb, 1, position( 'har' IN verb ) -1 ) as verbtrimmed FROM ".
        $this->getBaseTableName() 
        . "_verbsmodel where verb = '$verb'");
        $line = $results->fetch_object();
        return $line->verbtrimmed;  
    } // getVerbHAR
  
/**
 * \brief returns a list of indexed conjugations beginning w/ the string
 * \details 
 * \param  $conjugation a sting
 * \return  an array of matches
 */
    public function getIndexationAutoComplete($conjugation){
        $matches = array();
        if ($conjugation) {
            $results = $this->getConnection()->query("SELECT distinct conjugation, verb FROM {conjoc_index} where conjugation like '$conjugation%'");

            foreach ($results as $line) {
                $matches[$line->conjugation] = check_plain($line->conjugation) . " ($line->verb)";
            }
        } // if
        return $matches;     
    } // getIndexationAutoComplete

/**
 * \brief returns the data of an indexed conjugation
 * \details 
 * \param  $conjugation a sting
 * \return  an array of matches
 */
    public function getIndexationData($conjugation){
        if (!empty($conjugation)) {
            $results = $this->getConnection()->query("SELECT * FROM conjoc_index where conjugation = '$conjugation'");
            $line = $results->fetch_object();
            return $line;
        } // if

        return array();     
    } // getIndexationData

/**
 * \brief returns a list of infinitives that are prefixed with an index ex : "acochar 1" and "acochar 2" 
 * \details 
 * \return  an array of matches
 */
    public function getAllDuplicatedVerbs(){

        $results = $this->getConnection()->query("SELECT DISTINCT left(verb,locate(' ', verb)) as element FROM  ". 
        $this->getBaseTableName() 
        . "_verbsmodel where verb regexp '[[:digit:]]' order by binary verb");

        $arrRet = array();  

        while($line = $results->fetch_object()){
            $arrRet[] = $line->element;
        } // while
  
        return $arrRet;
    } // getAllDuplicatedVerbs()

/*
 */

/**
 * \brief returns a list of all infinitives. This is used for doing a massive indexation
 * \details not to be used in production
 * \return  an array of matches
 */
    public function getAllVerbs(){
        $results = $this->getConnection()->query("SELECT * FROM ". 
        $this->getBaseTableName() 
        . "_verbsmodel where substr(nummodel,1,1) = '3' ORDER BY BINARY verb");

        $arrRet = array();  

        while($line = $results->fetch_object()){
            $arr = array();
            $arr['verb']= $line->verb;
            $arr['row']= $line->row;
            $arr['infinitive']= $line->infinitive;
            $arrRet[] = $arr;
        } // while
  
        return $arrRet;
    } // getAllVerbs()

/**
* \details returns a list of infinitives by increments or steps and manages a counter to
* save the progression 
* \return an array of infinitives
*/
    public function getAllVerbsByIncrement(){
        throw new Exception("getAllVerbsByIncrement not implemented.");

        return $array();
    } // getAllVerbsByIncrement()
  
    /**
    * \brief inserts data for the indexation of a conjugation
    * \todo see the acces protected or not for this function
    */
    public function insertIndexedVerb(array $fields){
        $verbArr = $fields['verb'];
        $verb = $verbArr[0];
        $row = $fields['row'];
        $dialect = $fields['dialect'];
        $nummodel = $fields['nummodel'];
        $conjugation = $fields['conjugation'];
        $pos = $fields['pos'];
        $this->getConnection()->query("INSERT INTO conjoc_index (verb,row,dialect,nummodel,conjugation,pos) VALUES ('$verb', '$row','$dialect','$nummodel','$conjugation','$pos')");

    } // insertIndexedVerb

    /**
    * \details returns the definition/french translation of a verb at the infinitive 
    * \param $infinitive a string
    * \return a string with the definition from a dictionary
    */
    public function getDictionaryDefinition($infinitive){
        $results = $this->getConnection()->query("SELECT * FROM totenun_OF_index as tofi INNER JOIN totenun_OF as tof WHERE id = idtotenunOF and tofi.term = '$infinitive[0]'");

        $arrRet = array();

        while($line = $results->fetch_object()){
            $definition = $line->definition;
            $catgram    = $line->catgram;
            $arrRet[] =  array('definition'=>$line->definition,'catgram'=>$line->catgram);
        }
        return $arrRet;
    } // getDictionaryDefinition
} // class ConjugationDataProviderBootstrap
