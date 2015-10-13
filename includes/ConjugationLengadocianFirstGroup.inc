<?php


class ConjugationLengadocianFirstGroup extends ConjugationBase{

  protected function getStandardConjugation(){

  $arr = array();
  $arr['00_IndPres|Present']                 =  "i,as,a,am,atz,an";
  $arr['01_IndImp|Imperfach']                =  "avi,avas,ava,àvem,àvetz,avan";
  $arr['02_IndPret|Preterit']                =  "èri,ères,èt,èrem,èretz,èron";
  $arr['03_IndFutur|Futur']                  =  "arai,aràs,arà,arem,aretz,aràn";
  $arr['04_Infinitiu|Infinitiu']             =  "ar";
  $arr['05_Gerondiu|Gerondiu']               =  "ant";
  $arr['06_PartPassat|Participi passat']     =  "at,ada";
  $arr['07_Imperatiu|Imperatiu']             =  "a,em,atz,es,em,etz";
  $arr['08_SubPres|Subjontiu present']       =  "e,es,e,em,etz,en";
  $arr['09_SubImp|Subjontiu imperfach']      =  "èsse,èsses,èsse,èssem,èssetz,èsson";
  $arr['10_Conditional|Conditional']         =  "ariái,ariás,ariá,ariam,ariatz,arián";
  return $arr;
  } // setStandardConjugation

  protected function fixRadical($radical,$desinence){
    //$radical = $this->phonologicFixes($radical);
    // present indicative and present subjunctive
    $desinences = array('i','as','','a','an','e','es','en','ias','ia','ian');
  
    if(in_array($desinence,$desinences)){
      switch ($this->getVerbModel()){
        case '106 a' : $pattern = '/(.+?)a(.+?)$/'; $replacement = '${1}à${2}'; break;
          //      case '106 b' : $pattern = '/(.+?)e(.+?)$/'; $replacement = '${1}é${2}'; break;
        //      case '106 c' :
        case '106 d' : $pattern = '/(.+?)i(.+?)$/'; $replacement = '${1}í${2}'; break;
        case '106 e' : $pattern = '/(.+?)u(.+?)$/'; $replacement = '${1}ú${2}'; break;
        case '107 b' : 
          if (in_array($desinence,array('e','es','en'))){
            //drupal_set_message("$desinence"); 
            $pattern = '/(.*?)e(.+?)$/'; $replacement = '${1}è${2}';}
          else{
            $pattern = '//'; $replacement = '';}
          break;
        case '110'   :
        case '111'   :
        case '112'   :
        case '113'   :
        case '114'   :
        case '115'   :
          $pattern = '/(.+)e(.+?)$/'; $replacement = '${1}è${2}'; break;
        case '120'   :
        case '121'   :
        case '122'   :
        case '123'   :
        case '124'   :
        case '125'   :
        case '126 a' :
        case '126 b' :
        case '150'   :
        case '154'   :
          $pattern = '/(.+)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
        case '156'   :
          $pattern = '/(.*)o(.+?)$/'; $replacement = '${1}ò${2}'; break;
        case '130'   :
          $pattern = '/(.+)e(.+?)$/'; $replacement = '${1}iè${2}'; break;
        case '140'   :
        case '143'   :
          $pattern = '/(.+)o(.+?)$/'; $replacement = '${1}uè${2}'; break;
        case '160'   :
          $pattern = '/(.+)u(.+?)$/'; $replacement = '${1}uo${2}'; break;
        case '170'   :
        case '173'   :
          $pattern = '/(.+)u(.+?)$/'; $replacement = '${1}uè${2}'; break;
        default :
          return $radical;
    }
      return preg_replace($pattern, $replacement, $radical);
  }

    return $radical;
  } // fixRadical
  
  protected function fixDesinence($desinence){
  
    $desinences = array('i','as','a','an','e','es','en');

    if(in_array($desinence,$desinences)){
      switch ($this->getVerbModel()){
        case '107 a' :   // Attention dar,  di becomes dau
          $desinence = ($desinence=='i' ? 'au':$desinence); break;
        case '107 b' :   // Attention estar,  estid becomes estau
          $desinence = ($desinence=='i' ? 'au':$desinence);
          $desinence = ($desinence=='as' ? 'às':$desinence);
          $desinence = ($desinence=='a' ? 'à':$desinence);
          $desinence = ($desinence=='an' ? 'àn':$desinence);
      }
    }        
    return $desinence;
  } // fixDesinence

  protected function getConjugationArray(){

    $infinitive = $this->getVerb();

    $pattern = '/ \d{1}$/';

    if (preg_match($pattern, $infinitive)){
      $rootSaved = preg_replace('/(.+)(ar \d{1}$)/', '$1', $infinitive);
    }else{
      $rootSaved = preg_replace('/(.+)(ar)/', '$1', $infinitive);
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
        $conj = $this->phonologicFixes($root.'-'.$elmnt);
        $conj = preg_replace('/-/', '', $conj);
        $tempsConjugated[] = $conj; 
      } // for desinences
      $conjugations[] = $tempsConjugated;
    } // foreach temps

    return $conjugations;

  } // getConjugationArray

  protected function getDesinenceLengthArray(){

    $desinenceLengths = array();
    $desinenceLengths[ConjugationBase::IND_PRESENT]="1,2,1,2,3,2";
    $desinenceLengths[ConjugationBase::IND_IMPERFECT]="3,4,3,4,5,4";
    $desinenceLengths[ConjugationBase::IND_PRETERIT]="3,4,2,4,5,4";
    $desinenceLengths[ConjugationBase::IND_FUTURE]="4,4,3,4,5,4";
    $desinenceLengths[ConjugationBase::INFINITIVE]="2";
    $desinenceLengths[ConjugationBase::GERUND]="3";
    $desinenceLengths[ConjugationBase::PAST_PARTICIPLE]="2,3";
    $desinenceLengths[ConjugationBase::IMPERATIVE]="1,2,1,2,3,2";
    $desinenceLengths[ConjugationBase::SUBJ_PRESENT]="4,5,4,4,6,5";
    $desinenceLengths[ConjugationBase::SUBJ_IMPERFECT]="5,5,4,5,6,5";
    $desinenceLengths[ConjugationBase::CONDITIONAL]="4,4,3,4,5,4";
    return $desinenceLengths;

  }

  public function display(){
    return $this->conjugate();
  }

} // class ConjugationLengadocianFirstGroup

?>