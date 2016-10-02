<?php
  $o = "";
  $cnx = new mysqli("localhost","conjocuser","mypasswd","conjoc");
  if (!$cnx->set_charset("utf8")) {
    printf("Error loading character set utf8: %s\n", $cnx->error);
    exit();
  } else {
  //	    printf("Current character set: %s\n", $cnx->character_set_name());
  }

  $query = isset($_GET['verb'])?$_GET['verb']:'';
  $query .= '%';	
  $result = $cnx->query("SELECT verb FROM gascon_verbsmodel where verb like '$query'");
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
