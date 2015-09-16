<?php

class ConjugationGasconAuxilliary extends ConjugationBase{

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

  public function conjugate(){
    $conjugations = $this->getConjugationArray();

    $arr = array();
    $arr["id"]               = $this->getVerbId();
    $arr["name"]             = $this->getVerb();
    $arr["infinitive"]       = $conjugations[ConjugationBase::INFINITIVE];
    $arr["model"]            = $this->getVerbModel();
    $arr["comments"]         = $this->getComments();
    $arr["libmodel"]         = $this->getLibModel();
    $arr["dialect"]          = $this->getDialect();
    $arr["localization"]     = $this->getLocalization();
    $arr["comments"]         = $this->getComments();
    $arr["conjugations"]     = $conjugations;
    $arr["desinenceLengths"] = $this->getDesinenceLengthArray();
  
    return $arr;
  } // conjugate

  public function display(){
    return array();
  } // display

  public function getConjugationArray(){
    $infinitive = $this->getVerb();

    $pattern = '/ \d{1}$/';

    if (preg_match($pattern, $infinitive)){
      $rootSaved = preg_replace('/(.+)(ar \d{1}$)/', '$1', $infinitive);
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
        $tempsConjugated[] = $root.$elmnt; 
      } // for desinences
      $conjugations[] = $tempsConjugated;
    } // foreach temps

    return $conjugations;
  } // getConjugationArray

  public function fixRadical($radical, $desinence){
    return $radical;
  } // fixRadical

  public function fixDesinence($desinence){
    return $desinence;
  } // fixDesinence

  public function getDesinenceLengthArray(){
    return array();
  } // fixDesinence

} // class ConjugationGasconAuxilliary

?>