<?php
   if (isset($_GET['dialect'])){
   $dialect=$_GET['dialect'];
   function __autoload($class_name) {
   include "./includes/". $class_name . '.inc';
   }
   switch(strtoupper($dialect)){
   case 'LNG' :
     $manager = new ConjugationLengadocianManager();
     break;
   case 'GSC' :
     $manager = new ConjugationGasconManager();
     break;
   default :
     print "Dialect unknown";
     return;
   } // switch
   
   $verb = isset($_GET['verb'])?$_GET['verb']:$manager->getRandomVerb();
   $manager->setVerb($verb);
   $conjugated = $manager->conjugate();
   // a TEI format
   $converter = new ConverterTEI();
   $tei = $converter->convertConjugation($conjugated); 
   print ($tei);
} // isset Dialect
?>
