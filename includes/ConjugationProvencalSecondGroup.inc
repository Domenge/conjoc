<?php


class ConjugationProvencalSecondGroup extends ConjugationBase{

  protected function getStandardConjugation(){
    $arr = array();
    $arr['00_IndPres|Present']                 =  "issi,isses,�s,issem,issetz,issen";
    $arr['01_IndImp|Imperfach']                =  "ivi,ivas,iva,��vam,�vatz,ivan";
    $arr['02_IndPret|Preterit']                =  "ii,�s,�,im,itz,�n";
    $arr['03_IndFutur|Futur']                  =  "ir�i,ir�s,ir�,iram,iratz,ir�n";
    $arr['04_Infinitiu|Infinitiu']             =  "ir";
    $arr['05_Gerondiu|Gerondiu']               =  "issent";
    $arr['06_PartPassat|Participi passat']     =  "it,ida";
    $arr['07_Imperatiu|Present positiu/present negatiu'] = "�s,im,itz,escas,escam,escatz";
    $arr['08_SubPres|Subjontiu present']       =  "esqui,escas,esca,escam,escatz,escan";
    $arr['09_SubImp|Subjontiu imperfach']      =  "issi,isses,isse,�ssem,�ssetz,issen";
    $arr['10_Conditional|Condicional']         =  "ir�,ir�s,ir�,irem,iretz,ir�n";    
    return $arr;
  } // setStandardConjugation

  protected function conjugate(){
    return "conjugate";
  }

  public function display(){
    return array();
  } // display
} // class ConjugationProvencalSecondGroup

?>