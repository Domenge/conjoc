<?php


class ConjugationProvencalSecondGroup extends ConjugationBase{

  protected function getStandardConjugation(){
    $arr = array();
    $arr['00_IndPres|Present']                 =  "issi,isses,ís,issem,issetz,issen";
    $arr['01_IndImp|Imperfach']                =  "ivi,ivas,iva,­ívam,ívatz,ivan";
    $arr['02_IndPret|Preterit']                =  "ii,ís,í,im,itz,ín";
    $arr['03_IndFutur|Futur']                  =  "irèi,iràs,irà,iram,iratz,iràn";
    $arr['04_Infinitiu|Infinitiu']             =  "ir";
    $arr['05_Gerondiu|Gerondiu']               =  "issent";
    $arr['06_PartPassat|Participi passat']     =  "it,ida";
    $arr['07_Imperatiu|Present positiu/present negatiu'] = "ís,im,itz,escas,escam,escatz";
    $arr['08_SubPres|Subjontiu present']       =  "esqui,escas,esca,escam,escatz,escan";
    $arr['09_SubImp|Subjontiu imperfach']      =  "issi,isses,isse,íssem,íssetz,issen";
    $arr['10_Conditional|Condicional']         =  "irí,irés,iré,irem,iretz,irén";    
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