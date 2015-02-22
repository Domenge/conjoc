<?php

class ConjugationDataProviderDrupal extends ConjugationDataProviderBase{

  public function getVerb($verb){
    $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_verbsmodel} WHERE verb =:verb",array(':verb'=>$verb));
    return $results->fetchObject();
  } // getVerb

  public function getVerbModel($numModel){
    $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_model} WHERE nummodel=:numModel",array(':numModel'=>$numModel));
    return $results->fetchObject();
  } // getVerbModel

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
      	$matches[$verbline->verb] = check_plain($verbline->verb) . " (n° model=$verbline->nummodel, $verbline->label_conjugation))";
      }
    } // if

    return $matches;
  } // getVerbAutoComplete

  function getRandomVerb(){
    $results = db_query("SELECT * FROM {" . $this->getBaseTableName() . "_verbsmodel} ORDER BY RAND() LIMIT 1");
    $line = $results->fetchObject();

    return($line->verb);

  } // getRandomVerb()

  function getSingleVerbs(){
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

} // class ConjugationDataProviderDrupal

?>