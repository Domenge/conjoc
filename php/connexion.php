<?php
$con = new mysqli("localhost","drupal","ch0c0l\@t","labo.macarel.net");
$result = $con->query("SELECT term,id FROM totenun_OF' LIMIT 0,10");
    while ($row = $result->fetch_object()){
         $user_arr[] = $row->id;
         $user_arr2[] = $row->term;
     }
     $result->close();
     echo json_encode($user_arr2);
?>