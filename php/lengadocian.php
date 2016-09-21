<?php
  $o = "";
  $cnx = new mysqli("localhost","conjocuser","ADLcWBDV4zkdmnf0","conjoc");
  if (!$cnx->set_charset("utf8")) {
    printf("Error loading character set utf8: %s\n", $cnx->error);
    exit();
  } else {
  //	    printf("Current character set: %s\n", $cnx->character_set_name());
  }

  if(isset($_GET['action']) && $_GET['action'] == 'verbs_siblings'){
    $query = isset($_GET['verb'])?$_GET['verb']:'';
    $query .= '%';	
    $result = $cnx->query("SELECT s2.verb FROM `sauzet_verbsmodel` as s1,`sauzet_verbsmodel` as s2 WHERE s1.verb = '$query' and s1.nummodel = s2.nummodel and s2.verb <> '$query'");
  }else{
    $query = isset($_GET['verb'])?$_GET['verb']:'';
    $query .= '%';	
    $result = $cnx->query("SELECT verb FROM sauzet_verbsmodel where verb like '$query'");
  }
  
  $ary = array();
  $o = '[';
  while ($row = $result->fetch_object()){
    $ary[] = '{"value":"' . $row->verb .'"}';
    $o .= '{"value":"' . $row->verb .'"},';
  }
  $result->close();

  $o = substr($o,0,-1); // chop the last comma
  echo $o . ']';

?>