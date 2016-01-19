<?php

class ConjugationDataProviderDrupal extends ConjugationDataProviderBase{

    public function getVerb($verb){
        $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_verbsmodel} WHERE verb =:verb",array(':verb'=>$verb));
        return $results->fetchObject();
    } // getVerb

    public function getVerbById($id){
        $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_verbsmodel} WHERE id =:id",array(':id'=>$id));
        return $results->fetchObject();
    } // getVerbById

    public function getVerbModelObject($numModel){
        $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_model} WHERE nummodel=:numModel",array(':numModel'=>$numModel));
        return $results->fetchObject();
    } // getVerbModelObject

    public function getTop20(){
        $results = db_query("SELECT COUNT(*) as cpter, group_concat(cast(idverb as char)) as concat FROM {" . $this->getBaseTableName() . "_access} GROUP BY idverb ORDER BY cpter DESC LIMIT 20");
        $arrRet = array();
/*
  T O  B E  D O N E
  T O  B E  D O N E
  T O  B E  D O N E

  while($line = $results->fetchObject()){
  $arr = explode(',', $line->concat);
  $id = $arr[0];
  $id = isset($id)?$id:0;
  $resInner  = db_query("SELECT verb FROM {". $this->getBaseTableName() . "_verbsmodel} WHERE id =:id LIMIT 1",array(':id'=>$id));
  $lineInner = $resInner->fetchObject();
  $arrRet[0] = $lineInner->verb;
  } // while
*/
        return $arrRet;
    } // getTop20

    public function getOthersInModel($verb){

        $count = $this->getCountOthersInModel($verb);
        $arrRet = array();

        if ($count <= variable_get("MAX_OTHERVERBS") && $count){
            $results = db_query("SELECT sv2.verb as verb, sv2.nummodel FROM " . 
            $this->getBaseTableName() . 
            "_verbsmodel as sv1, ". 
            $this->getBaseTableName().
            "_verbsmodel as sv2 where sv1.verb=:verb and sv1.nummodel = sv2.nummodel and sv2.verb <> :verb", array(':verb'=>$verb));

            while($line = $results->fetchObject()){
                $arrRet = $line->verb;
            } // while
        }
        return $arrRet;
    } // getOthersInModel

    public function getCountOthersInModel($verb){
        $resultsCount = db_query("SELECT count(*) as cptr FROM " .
        $this->getBaseTableName() . 
        "_verbsmodel` as sv1, " .
        $this->getBaseTableName() . 
        "_verbsmodel as sv2 where sv1.verb=:verb and sv1.nummodel = sv2.nummodel and sv2.verb <> :verb", array(':verb'=>$verb));

        $line = $resultsCount->fetchObject();
        return $line->cptr;
    } // getCountOthersInModel

    public function getVerbAutoComplete($string){
        $matches = array();

        if ($string) {
            $tableName = $this->getBaseTableName() . "_verbsmodel"; 
       
            $query = db_select("$tableName",'vm');

            $tableName = $this->getBaseTableName() . "_model"; 
            $query->join("$tableName", 'm', 'vm.nummodel=m.nummodel');
            $query->groupby('vm.verb');
            $query->fields('vm', array('id','verb', 'nummodel'));
            $query->fields('m', array('verb_prime','label_conjugation'));
            $result = $query->condition('vm.verb', db_like($string) . '%', 'LIKE')->range(0, 100)->execute();

            foreach ($result as $verbline) {
                // In the simplest case (see user_autocomplete), the key and the value are
                // the same. Here we'll display the uid along with the username in the
                // dropdown.
//                $matches[$verbline->verb] = check_plain($verbline->verb) . " (n° model=$verbline->nummodel, $verbline->label_conjugation))";
                $matches[$verbline->verb] = check_plain($verbline->verb) . " (n° model=$verbline->nummodel)";
            }
        } // if

        return $matches;
    } // getVerbAutoComplete

    public function getRandomVerb(){
        $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_verbsmodel} ORDER BY RAND() LIMIT 1");
        $line = $results->fetchObject();

        return($line->verb);

    } // getRandomVerb()

    public function getSingleVerbs(){
        $results = db_query("SELECT COUNT(*) as cpter, group_concat(verb) as concat FROM {". 
        $this->getBaseTableName() 
        . "_verbsmodel} GROUP BY nummodel ORDER BY cpter ASC LIMIT 25");

        $arrRet = array();  

        while($line = $results->fetchObject()){

            if ($line->cpter == 1){
                $verb = $line->concat;
                if (strlen($verb) > 0){
                    $arrRet[] = $verb;
                } 
            }
        } // while
  
        return $arrRet;
    } // getSingleVerbs()

    public function getVerbFAR($verb){
        // returns the prefix of the verb build on semiauxiliary FAR
        $results = db_query("SELECT SUBSTR( verb, 1, position( 'far' IN verb ) -1 ) as verbtrimmed FROM {".
        $this->getBaseTableName() 
        . "_verbsmodel} where verb = :verb", array(':verb'=>$verb));
        $line = $results->fetchObject();
        return $line->verbtrimmed;  
    }

    public function getVerbHAR($verb){
        // returns the prefix of the verb build on semiauxiliary HAR gascon
        $results = db_query("SELECT SUBSTR( verb, 1, position( 'har' IN verb ) -1 ) as verbtrimmed FROM {".
        $this->getBaseTableName() 
        . "_verbsmodel} where verb = :verb", array(':verb'=>$verb));
        $line = $results->fetchObject();
        return $line->verbtrimmed;  
    } // getVerbHAR
  
    public function getIndexationAutoComplete($conjugation){
        $matches = array();
        if ($conjugation) {
            $results = db_query("SELECT distinct conjugation, verb FROM {conjoc_index} where conjugation like '$conjugation%'");

            foreach ($results as $line) {
                $matches[$line->conjugation] = check_plain($line->conjugation) . " ($line->verb)";
            }
        } // if
        return $matches;     
    } // getIndexationAutoComplete

    public function getIndexationData($conjugation){
        if ($conjugation) {
            $results = db_query("SELECT * FROM {conjoc_index} where conjugation = :conjugation", array(':conjugation'=> $conjugation));
            $line = $results->fetchObject();
            return $line;
        } // if

        return array();     
    } // getIndexationData

    public function getAllDuplicatedVerbs(){

        $results = db_query("SELECT DISTINCT left(verb,locate(' ', verb)) as element FROM  {". 
        $this->getBaseTableName() 
        . "_verbsmodel} where verb regexp '[[:digit:]]' order by binary verb");

        $arrRet = array();  

        while($line = $results->fetchObject()){
            $arrRet[] = $line->element;
        } // while
  
        return $arrRet;
    } // getAllDuplicatedVerbs()

/*
 */

    public function getAllVerbs(){
        $results = db_query("SELECT * FROM {". 
        $this->getBaseTableName() 
        . "_verbsmodel} where substr(nummodel,1,1) = '3' ORDER BY BINARY verb");
//    . "_verbsmodel} where substr(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT 0, 2500");
//    . "_verbsmodel} where substr(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT 2500, 2500");
//    . "_verbsmodel} where substr(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT 5000, 2500");
//    . "_verbsmodel} where substr(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT 7500, 2500");
//    . "_verbsmodel} where substr(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT 10000, 2500");

        $arrRet = array();  

        while($line = $results->fetchObject()){
            $arr = array();
            $arr['verb']= $line->verb;
            $arr['row']= $line->row;
            $arr['infinitive']= $line->infinitive;
            $arrRet[] = $arr;
        } // while
  
        return $arrRet;
    } // getAllVerbs()

    public function getAllVerbsByIncrement(){

        /*L E N G A D O C I A N*/
        if(variable_get('conjoc_indexation_Lengadocian_enabled', FALSE)){
            $increment =  variable_get('conjoc_indexation_Lengadocian_increment', 0);

            $results = db_query("SELECT  count(*) div :indexationstep as increments, count(*) as totalVerbs FROM {".
            $this->getBaseTableName() 
            . "_verbsmodel} WHERE SUBSTR(nummodel,1,1) = '1'", array('indexationstep'=> ConjugationDataProviderBase::INDEXATION_STEP));
            $line = $results->fetchObject();
            $increments = $line->increments;
            $totalVerbs = $line->totalVerbs;

            if ($increment > ($increments + 1)){
                // we are done
                drupal_set_message("Indexation completed");
                variable_set('conjoc_indexation_Lengadocian_increment', '0');
                variable_set('conjoc_indexation_Lengadocian_enabled', FALSE);
                variable_set('conjoc_indexation_Lengadocian_verbsindexed', '0');
            }

            if ($increment == 0){
                // TODO truncate the conjoc_index table
                db_truncate('conjoc_index')->execute();
                $clause = " SUBSTR(nummodel,1,1) = '0' OR SUBSTR(nummodel,1,1) = '2' OR SUBSTR(nummodel,1,1) = '3' ORDER BY BINARY verb";
            }else{
                $limit = ($increment -1) * (int)ConjugationDataProviderBase::INDEXATION_STEP; 
                $clause = " SUBSTR(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT $limit, " . ConjugationDataProviderBase::INDEXATION_STEP;
            }

            $increment++;

            variable_set('conjoc_indexation_Lengadocian_increment', $increment);

            $results = db_query("SELECT * FROM {". $this->getBaseTableName() . "_verbsmodel} WHERE $clause");

            $arrRet = array();  

            while($line = $results->fetchObject()){
                $arr = array();
                $arr['verb']= $line->verb;
                $arr['row']= $line->row;
                $arr['infinitive']= $line->infinitive;
                $arrRet[] = $arr;
            } // while

            $verbsIndexed = $increment * (int)ConjugationDataProviderBase::INDEXATION_STEP;
            $verbsLeft = $totalVerbs - $verbsIndexed;
            $verbsLeft = $verbsLeft > 0 ? $verbsLeft:0; 
            variable_set('conjoc_indexation_Lengadocian_verbstoindex', $verbsLeft);
            variable_set('conjoc_indexation_Lengadocian_verbsindexed', $verbsIndexed);
            variable_set('conjoc_indexation_Lengadocian_totalIncrements', $increments + 1);
  
            return $arrRet;
        }

        /* G A S C O N */
        if(variable_get('conjoc_indexation_Gascon_enabled', FALSE)){
            $increment =  variable_get('conjoc_indexation_Gascon_increment', 0);

            $results = db_query("SELECT  count(*) div :indexationstep as increments, count(*) as totalVerbs FROM {".
            $this->getBaseTableName() 
            . "_verbsmodel} WHERE SUBSTR(nummodel,1,1) = '1'", array('indexationstep'=> ConjugationDataProviderBase::INDEXATION_STEP));
            $line = $results->fetchObject();
            $increments = $line->increments;
            $totalVerbs = $line->totalVerbs;

            if ($increment > ($increments + 1)){
                // we are done
                drupal_set_message("Indexation completed");
                variable_set('conjoc_indexation_Gascon_increment', '0');
                variable_set('conjoc_indexation_Gascon_enabled', FALSE);
                variable_set('conjoc_indexation_Gascon_verbsindexed', '0');
            }

            if ($increment == 0){
                // TODO truncate the conjoc_index table
                db_truncate('conjoc_index')->execute();
                $clause = " SUBSTR(nummodel,1,1) = '0' OR SUBSTR(nummodel,1,1) = '2' OR SUBSTR(nummodel,1,1) = '3' ORDER BY BINARY verb";
            }else{
                $limit = ($increment -1) * (int)ConjugationDataProviderBase::INDEXATION_STEP; 
                $clause = " SUBSTR(nummodel,1,1) = '1' ORDER BY BINARY verb LIMIT $limit, " . ConjugationDataProviderBase::INDEXATION_STEP;
            }

            $increment++;

            variable_set('conjoc_indexation_Gascon_increment', $increment);

            $results = db_query("SELECT * FROM {". $this->getBaseTableName() . "_verbsmodel} WHERE $clause");

            $arrRet = array();  

            while($line = $results->fetchObject()){
                $arr = array();
                $arr['verb']= $line->verb;
                $arr['row']= $line->row;
                $arr['infinitive']= $line->infinitive;
                $arrRet[] = $arr;
            } // while

            $verbsIndexed = $increment * (int)ConjugationDataProviderBase::INDEXATION_STEP;
            $verbsLeft = $totalVerbs - $verbsIndexed;
            $verbsLeft = $verbsLeft > 0 ? $verbsLeft:0; 
            variable_set('conjoc_indexation_Gascon_verbstoindex', $verbsLeft);
            variable_set('conjoc_indexation_Gascon_verbsindexed', $verbsIndexed);
            variable_set('conjoc_indexation_Gascon_totalIncrements', $increments + 1);
  
            return $arrRet;
        }
    } // getAllVerbsByIncrement()
  
    public function insertIndexedVerb(array $fields){
        db_insert('conjoc_index')->fields($fields)->execute();
    } // insertIndexedVerb

    public function getDictionaryDefinition($infinitive){
        $results = db_query("SELECT * FROM totenun_OF_index as tofi INNER JOIN totenun_OF as tof WHERE id = idtotenunOF and tofi.term = :infinitive", array(':infinitive'=> $infinitive));

        $arrRet = array();

        while($line = $results->fetchObject()){
            $definition = $line->definition;
            $catgram    = $line->catgram;
            $arrRet[] =  array('definition'=>$line->definition,'catgram'=>$line->catgram);
        }
        return $arrRet;
    } // getDictionaryDefinition
} // class ConjugationDataProviderDrupal
