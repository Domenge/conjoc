<?php


class ConjugationLengadocianThirdGroup extends ConjugationBase{

  public function __construct(ConjugationManager $manager, $name, $id, $alias, $model, $comments, $localization){
    $this->setId($id);
    $this->setManager($manager);
    $this->setName($name);
    $this->setModel($model);
    $this->setComments($comments);
    $this->setLocalization($localization);
    $this->setStandardConjugation();
  } // __construct

  protected getStandardConjugation(){
    $arr = array();
    $arr['00'] =  "i,es,,em,etz,en";
    $arr['01'] =  "�vi,�vas,�va,�vam,�vatz,�van";
    $arr['02'] =  "oi,�s,�,om,otz,�n";
    $arr['03'] =  "er�i,er�s,er�,eram,eratz,er�n";
    $arr['04'] =  "";
    $arr['05'] =  "ent";
    $arr['06'] =  "ut,uda";
    $arr['07'] =  ",em,etz,ias,iam,iatz";
    $arr['08'] =  "i,ias,ia,iam,iatz,ian";
    $arr['09'] =  "ossi,osses,osse,�ssem,�ssetz,ossen";
    $arr['10'] =  "er�,er�s,er�,erem,eretz,er�n";
    return $arr;
  } // getStandardConjugation

  protected function conjugate(){
    return "conjugate";
  }
  public function display(){
    return "ConjugationLengadocianThirdGroup $this->_name " . $this->conjugate;
  } // display
} // class ConjugationLengadocianThirdGroup

?>