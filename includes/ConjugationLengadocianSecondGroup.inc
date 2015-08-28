<?php

class ConjugationLengadocianSecondGroup extends ConjugationBase{

  protected function getStandardConjugation(){

  $arr = array();
  $model = $this->getVerbModel();
   
  if ($model == '230'){
    $arr['00_IndPres|Present']                 =  "i,es,,èm,sètz,on";
    $arr['01_IndImp|Imperfach']                =  "iái,iás,iá,iam,iatz,ián";
    $arr['02_IndPret|Preterit']                =  "iguèri,iguères,iguèt,iguèrem,iguèretz,iguèron";
    $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
    $arr['04_Infinitiu|Infinitiu']             =  "ir";
    $arr['05_Gerondiu|Gerondiu']               =  "issent";
    $arr['06_PartPassat|Participi passat']     =  "it,ida";
    $arr['07_Imperatiu|Imperatiu']             =  ",am,etz,iscas,iscam,iscatz";
    $arr['08_SubPres|Subjontiu present']       =  "a,as,a,am,atz,an";
    $arr['09_SubImp|Subjontiu imperfach']      =  "iguèsse,iguèsses,iguèsse,iguèssem,iguèssetz,iguèsson";
    $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";
  return $arr;
  }
  if ($model == '210' || $model == '211' || $model == '212' || $model == '213'){
    $arr['00_IndPres|Present']                 =  "ïssi,ïsses,ís,ïssèm,ïssètz,ïsson";
    $arr['01_IndImp|Imperfach']                =  "ïssiái,ïssiás,ïssiá,ïssiam,ïssiatz,ïssián";
    $arr['02_IndPret|Preterit']                =  "ïguèri,ïguères,ïguèt,ïguèrem,ïguèretz,ïguèron";
    $arr['03_IndFutur|Futur']                  =  "ïrai,ïràs,ïrà,ïrem,ïretz,ïràn";
    $arr['04_Infinitiu|Infinitiu']             =  "ïr";
    $arr['05_Gerondiu|Gerondiu']               =  "ïssent";
    $arr['06_PartPassat|Participi passat']     =  "ït,ida";
    $arr['07_Imperatiu|Imperatiu']             =  "ís,ïscam,ïssetz,ïscas,ïscam,ïscatz";
    $arr['08_SubPres|Subjontiu present']       =  "ïsca,ïscas,ïsca,ïscam,ïscatz,ïscan";
    $arr['09_SubImp|Subjontiu imperfach']      =  "ïguèsse,ïguèsses,ïguèsse,ïguèssem,ïguèssetz,ïguèsson";
    $arr['10_Conditional|Conditional']         =  "ïriái,ïriás,ïriá,ïriam,ïriatz,ïrián";
  return $arr;
  }

  $arr['00_IndPres|Present']                 =  "issi,isses,ís,issèm,issètz,isson";
  $arr['01_IndImp|Imperfach']                =  "issiái,issiás,issiá,issiam,issiatz,issián";
  $arr['02_IndPret|Preterit']                =  "iguèri,iguères,iguèt,iguèrem,iguèretz,iguèron";
  $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
  $arr['04_Infinitiu|Infinitiu']             =  "ir";
  $arr['05_Gerondiu|Gerondiu']               =  "issent";
  $arr['06_PartPassat|Participi passat']     =  "it,ida";
  $arr['07_Imperatiu|Imperatiu']             =  "ís,iscam,issetz,iscas,iscam,iscatz";
  $arr['08_SubPres|Subjontiu present']       =  "isca,iscas,isca,iscam,iscatz,iscan";
  $arr['09_SubImp|Subjontiu imperfach']      =  "iguèsse,iguèsses,iguèsse,iguèssem,iguèssetz,iguèsson";
  $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";
  return $arr;
  } // setStandardConjugation

  protected function getDesinenceLengthArray(){

    $desinenceLengths = array();
    $desinenceLengths[]="1,2,1,2,3,2";
    $desinenceLengths[]="3,4,3,4,5,4";
    $desinenceLengths[]="3,4,2,4,5,4";
    $desinenceLengths[]="4,4,3,4,5,4";
    $desinenceLengths[]="2";
    $desinenceLengths[]="3";
    $desinenceLengths[]="1,2,3,2,2,3";
    $desinenceLengths[]="1,2,1,2,3,2";
    $desinenceLengths[]="4,5,4,4,6,5";
    $desinenceLengths[]="5,5,4,5,6,5";
    return $desinenceLengths;

  }

  protected function fixRadical($radical,$desinence){
    return $radical;
  } // fixRadical
  
  protected function fixDesinence($desinence){       
    return $desinence;
  } // fixDesinence

  protected function getConjugationArray(){

    $infinitive = $this->getVerb();

    $pattern = '/ \d{1}$/';

    if (preg_match($pattern, $infinitive)){
      $rootSaved = preg_replace('/(.+) (\d{1}$)/', '$1', $infinitive);
    }else{
      $rootSaved = substr($infinitive,0,-2);
    }
        
    $conjugations = array();

    // for each temps
    foreach($this->getStandardConjugation() as $lib=>$desinence){
      $desinences = explode(',', $desinence);
      $i=0;
      $tempsConjugated = array();

      foreach ($desinences as $elmnt){
        $root = $this->fixRadical($rootSaved,$elmnt);
        $elmnt = $this->fixDesinence($elmnt);
        $tempsConjugated[] = utf8_encode($root.$elmnt); 
      } // for desinences
      $conjugations[] = $tempsConjugated;
    } // foreach temps

    return $conjugations;

  } // getConjugationArray

  public function display(){
    return array();
  } // display
} // class ConjugationLengadocianSecondGroup

?>