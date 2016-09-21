<?php
$con = new mysqli("localhost","root","","autopin");

$result = $con->query("SELECT id,imageurl FROM pinterest LIMIT 0,10");
    while ($row = $result->fetch_object()){
         $user_arr[] = $row->id;
         $user_arr2[] = $row->imageurl;
     }
     $result->close();
     echo json_encode($user_arr2);
?>