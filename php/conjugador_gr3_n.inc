<?php

// F I X  M E
// 
// 
//
require_once('conjugador_lib.inc');

function conjugador_FixRadicalGr3_n($model,$root,$elmnt){
  switch ($model){
    case '314':
      $desinences = array('di','t','des','en','sca','scas', 'don'); break;
    case '333' :
    case '334' :
    case '335' :
      $desinences = array('si','ses','i','ga','gas', 'son', 'gan'); break;
    case '354' :
      $desinences = array('vi','ves','u','ga','gas', 'son', 'gan'); break;
    default : 
      $desinences = array('i','as','a','an','e','es','en','sca','scas', 'on','ga','gas');
  }
  
  // when è matches a radical we reverse the logic
  if(($model == '316' or $model == '311' or $model == '333' or $model == '364' or $model == '384') && ! in_array($elmnt,$desinences)) {

    $pattern = '/(.+?)è(.*?)/'; $replacement = '${1}e${2}';
    $root = preg_replace($pattern, $replacement, $root);

    if(! $elmnt){
      $pattern = '/(.+?)e(.+?)/'; $replacement = '${1}è${2}';
      $root = preg_replace($pattern, $replacement, $root);
    }
    return $root;
  }

  if(($model == '342' or $model == '343' or $model == '360' or $model == '361' or $model == '372') && ! in_array($elmnt,$desinences)) {

    $pattern = '/(.+?)é(.*?)/'; $replacement = '${1}e${2}';
    $root = preg_replace($pattern, $replacement, $root);

    if(! $elmnt){
      $pattern = '/(.+?)e(.+?)/'; $replacement = '${1}é${2}';
      $root = preg_replace($pattern, $replacement, $root);
    }
    return $root;
  }

  if(($model == '340' or $model == '341' or $model == '370' or $model == '371' or $model == '375') && ! in_array($elmnt,$desinences)) {

    $pattern = '/(.+?)à(.*?)/'; $replacement = '${1}a${2}';
    $root = preg_replace($pattern, $replacement, $root);

    if(! $elmnt){
      $pattern = '/(.+?)à(.+?)/'; $replacement = '${1}a${2}';
      $root = preg_replace($pattern, $replacement, $root);
    }
    return $root;
  }

  if(($model == '317' or $model == '334' or $model == '335' 
     or $model == '344'  or $model == '354' or $model == '355')  
     && ! in_array($elmnt,$desinences)) {

    $pattern = '/(.+?)ò(.*?)/'; $replacement = '${1}o${2}';
    $root = preg_replace($pattern, $replacement, $root);

    if(! $elmnt){
      $pattern = '/(.+?)o(.+?)/'; $replacement = '${1}ò${2}';
      $root = preg_replace($pattern, $replacement, $root);
    }
    return $root;
  }

  if(($model == '320')  && ! in_array($elmnt,$desinences)) {

    $pattern = '/(.+?)ó(.+?)/'; $replacement = '${1}o${2}';
    $root = preg_replace($pattern, $replacement, $root);

    if(! $elmnt){
      $pattern = '/(.+?)o(.+?)/'; $replacement = '${1}ó${2}';
      $root = preg_replace($pattern, $replacement, $root);
    }
    return $root;
  }

  if($model == '373' || $model == '374' || $model == '383') {  // ónher jònher bòlher

    $pattern = '/(.*?)ó(.+?)/'; $replacement = '${1}o${2}';
    $root = preg_replace($pattern, $replacement, $root);

    return $root;
  }

  if($model == '381' ) {  // mòlre 

    $pattern = '/(.*?)ò(.+?)/'; $replacement = '${1}o${2}';
    $root = preg_replace($pattern, $replacement, $root);
  }

  if($model == '345') {  // mólzer

    $pattern = '/(.*?)ó(.+?)/'; $replacement = '${1}o${2}';
    $root = preg_replace($pattern, $replacement, $root);
  }

  if($model == '386' && ! in_array($elmnt,$desinences)) {  // quèrre
    $pattern = '/(.*?)è(.+?)/'; $replacement = '${1}e${2}';
    $root = preg_replace($pattern, $replacement, $root);
  }

  if($model == '387' && ! in_array($elmnt,$desinences)) {  // córre
    $pattern = '/(.*?)ó(.+?)/'; $replacement = '${1}o${2}';
    $root = preg_replace($pattern, $replacement, $root);
  }

  if($model == '349' && ! in_array($elmnt,$desinences)) {

    $pattern = '/(.+?)é(.+?)/'; $replacement = '${1}e${2}';
    $root = preg_replace($pattern, $replacement, $root);
    return $root;
  }

  if(in_array($elmnt,$desinences)){
    switch ($model){
      case '314'   :
        $pattern = '/(.+?)o(.*?)$/'; $replacement = '${1}ò'; break;
      case '354'   :   // mòure
      case '355'   :   // sòlver
      case '381'   :   // mòlre
      case '382'   :   // voler
        $pattern = '/(.+?)o(.*?)$/'; $replacement = '${1}ò${2}'; break;
      case '322'   :
        $pattern = '/(.+?)i(.+?)$/'; $replacement = '${1}í${2}'; break;
      case '311'   :   // mèdre
      case '313'   :   // recebre
      case '333'   :   // seire
        $pattern = '/(.+?)e(.+?)$/'; $replacement = '${1}è${2}'; break;
      case '386'   :   // quèrre
        $pattern = '/(.+?)èr(.*?)$/'; $replacement = '${1}ièr${2}'; break;
      default :
        return $root;
    }
    return preg_replace($pattern, $replacement, $root);
  }
  if($model == '311'){ // mèdre
    $pattern = '/(.+?)è(.+?)/'; $replacement = '${1}e${2}';
    return preg_replace($pattern, $replacement, $root);
  }

  return $root;
} // conjugador_FixRadicalGr3

function conjugador_getTempsGroup3_n($model){

  $arr = array();

  switch($model){
    //***
    case '312' : // saber saupre
    case '313' :  
      $arr['00_IndPres|Present']                 =  "bi,bes,p,bèm,bètz,bon";
      $arr['01_IndImp|Imperfach']                =  "biái,biás,biá,biam,biatz,bián";
      $arr['02_IndPret|Preterit']                =  ($model=='312')? "upèri,upères,upèt,upèrem,upèretz,upèron":"bèri,bères,bèt,bèrem,bèretz,bèron";
      $arr['03_IndFutur|Futur']                  =  ($model=='312')?"uprai,upràs,uprà,uprem,upretz,upràn":"brai,bràs,brà,brem,bretz,bràn";
      $arr['04_Infinitiu|Infinitiu']             =  "ber";
      $arr['05_Gerondiu|Gerondiu']               =  "bent";
      $arr['06_PartPassat|Participi passat']     =  ($model=='312')?"uput,upuda":"but,buda";
      $arr['07_Imperatiu|Imperatiu']             =  "pia,piam,piatz,pias,piam,piatz";
      $arr['08_SubPres|Subjontiu present']       =  "pia,pias,pia,piam,piatz,pian";
      $arr['09_SubImp|Subjontiu imperfach']      =  ($model=='312')? "upèsse,upèsses,upèsse,upèssem,upèssetz,upèsson":"bèsse,bèsses,bèsse,bèssem,bèssetz,bèsson";
      $arr['10_Conditional|Conditional']         =  ($model=='312')?"upriái,upriás,upriá,upriam,upriatz,uprián":"briái,briás,briá,briam,briatz,brián";
      return $arr;
      //***
    case '321' : // aucire
    case '322' : // sufire
    case '323' : // rire
    case '324' : // traire
    case '330' : // taire
    case '331' : // creire
    case '333' : // sèire
    case '334' : // fòire
    case '335' : // còire
    case '336' : // veire
    case '332' :

      switch ($model){
        case '321' : 	
        case '322' : $arr['00_IndPres|Present'] = "si,ses,s,sèm,sètz,son"; break;
        case '323' :
        case '324' : $arr['00_IndPres|Present'] = "si,ses,tz,sèm,sètz,son"; break;
        case '330' :	
        case '331' :
        case '333' :
        case '334' :
        case '335' :
        case '336' :
        case '332' : $arr['00_IndPres|Present'] = "si,ses,i,sèm,sètz,son"; break;
      }

      $arr['01_IndImp|Imperfach']      =  "siái,siás,siá,siam,siatz,sián";

      switch ($model){
        case '330' :
          $arr['02_IndPret|Preterit']  =  "sèri,sères,sèt,sèrem,sèretz,sèron";break;
        case '336' :
          $arr['02_IndPret|Preterit']  =  "gèri,gères,gèt,gèrem,gèretz,gèron";break;
        default :
          $arr['02_IndPret|Preterit']  =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      }

      switch ($model){
        case '330' :
        case '335' :
        case '336' :
        case '332' : $arr['03_IndFutur|Futur'] = "irai,iràs,irà,irem,iretz,iràn"; break;
        default :
          $arr['03_IndFutur|Futur'] =  "rai,ràs,rà,rem,retz,ràn";
      }

      switch ($model){
        case '330' :
        case '332' : 
        case '333' : 
        case '334' :
        case '335' :
          $arr['04_Infinitiu|Infinitiu'] = "ire"; break;

       default :
          $arr['04_Infinitiu|Infinitiu'] = "re";
      }

      $arr['05_Gerondiu|Gerondiu'] = "sent";

      switch ($model){
        case '321' : $arr['06_PartPassat|Participi passat'] = "s,sa"; break;	
        case '322' : $arr['06_PartPassat|Participi passat'] = "t,da"; break;
        case '331' :
        case '333' :
        case '334' :
        case '323' : $arr['06_PartPassat|Participi passat'] = "gut,guda"; break;
        case '330' : $arr['06_PartPassat|Participi passat'] = "sut,suda"; break;
        case '324' :
        case '335' : 
        case '332' : 
          $arr['06_PartPassat|Participi passat'] = "ch,cha"; break;
        case '336' : $arr['06_PartPassat|Participi passat'] = "st,sta"; break;

     }

      switch ($model){
        case '321' : 	
        case '322' : $arr['07_Imperatiu|Imperatiu'] = "s,gam,sètz,gas,gam,gatz"; break;
        case '323' : 
        case '324' : $arr['07_Imperatiu|Imperatiu'] = "ga,gam,sètz,gas,gam,gatz"; break;
        case '330' : $arr['07_Imperatiu|Imperatiu'] = "i,sam,sètz,sas,sam,satz"; break;
        case '332' : 
        case '333' :
        case '334' : 
        case '335' :
          $arr['07_Imperatiu|Imperatiu'] = "i,gam,sètz,gas,gam,gatz"; break;
        case '336' :
          $arr['07_Imperatiu|Imperatiu'] = "ja,jam,jatz,jas,jam,jatz"; break;
      }

      switch ($model){
        case '330' :
          $arr['08_SubPres|Subjontiu present']  = "sa,sas,sa,sam,satz,san";
          $arr['09_SubImp|Subjontiu imperfach'] = "sèsse,sèsses,sèsse,sèssem,sèssetz,sèsson";
          break;
        case '336' :
          $arr['08_SubPres|Subjontiu present']  = "ja,jas,ja,jam,jatz,jan";
          $arr['09_SubImp|Subjontiu imperfach'] = "gèsse,gèsses,gèsse,gèssem,gèssetz,gèsson";
          break;
        default :
          $arr['08_SubPres|Subjontiu present']  =  "ga,gas,ga,gam,gatz,gan";
          $arr['09_SubImp|Subjontiu imperfach'] =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      }

      switch ($model){
        case '330' :
        case '332' :
        case '335' :
        case '336' :
          $arr['10_Conditional|Conditional']      =  "iriái,iriás,iriá,iriam,iriatz,irián"; break;
        default :
          $arr['10_Conditional|Conditional']      =  "riái,riás,riá,riam,riatz,rián";
      }

      return $arr;
      //***   
    case '325' : // aduire
    case '326' : // conclure

      $arr['00_IndPres|Present']                 =  "si,ses,tz,sèm,sètz,son";
      $arr['01_IndImp|Imperfach']                =  "siái,siás,siá,siam,siatz,sián";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";

      switch ($model){
        case '325' :
          $arr['03_IndFutur|Futur'] =  "irai,iràs,irà,irem,iretz,iràn"; break;
        case '326' : $arr['03_IndFutur|Futur'] =  "rai,ràs,rà,rem,retz,ràn"; break;
      }

      switch ($model){
        case '325' : $arr['04_Infinitiu|Infinitiu']              = "ire"; break;
        case '326' : $arr['04_Infinitiu|Infinitiu']              = "re"; break;
      }

      switch ($model){
        case '325' : $arr['05_Gerondiu|Gerondiu']               =  "isent"; break;
        case '326' : $arr['05_Gerondiu|Gerondiu']               =  "sent"; break;
      }
    
      switch ($model){
        case '325' : $arr['06_PartPassat|Participi passat']     =  "ch,cha"; break;
        case '326' : $arr['06_PartPassat|Participi passat']     =  "s,sa";break;
      }

      $arr['07_Imperatiu|Imperatiu'] = "tz,gam,sètz,gas,gam,gatz";

      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      switch ($model){
        case '325' : $arr['10_Conditional|Conditional'] = "iriái,iriás,iriá,iriam,iriatz,irián"; break;
        case '326' : $arr['10_Conditional|Conditional'] = "riái,riás,riá,riam,riatz,rián"; break;
      }
    
      return $arr;
      //***
    case '340' : // pàisser
    case '341' : // nàisser
    case '342' : // créisser
    case '343' : // conéisser
    case '344' : // ròisser

      $arr['00_IndPres|Present']                 =  "issi,isses,is,issèm,issètz,isson";
      $arr['01_IndImp|Imperfach']                =  "issiái,issiás,issiá,issiam,issiatz,issián";
      switch ($model){
        case '343' : $arr['02_IndPret|Preterit'] =  "guèri,guères,guèt,guèrem,guèretz,guèron";break;
        default :
          $arr['02_IndPret|Preterit']                =  "squèri,squères,squèt,squèrem,squèretz,squèron";
      }
      $arr['03_IndFutur|Futur']                  =  "isserai,isseràs,isserà,isserem,isseretz,isseràn";
      $arr['04_Infinitiu|Infinitiu']             =  "isser";
      $arr['05_Gerondiu|Gerondiu']               =  "issent";
      switch ($model){
        case '342' : $arr['06_PartPassat|Participi passat']     =  "scut,scuda"; break;
        case '343' : 
        case '344' :
          $arr['06_PartPassat|Participi passat']     =  "gut,guda"; break;
        default :
          $arr['06_PartPassat|Participi passat']     =  "iscut,iscuda";
      }
      switch ($model){
        //        case '343' : $arr['07_Imperatiu|Imperatiu']  =  "is,gam,issètz,scas,scam,scatz";break;
        default :
          $arr['07_Imperatiu|Imperatiu']             =  "is,iscam,issètz,scas,scam,scatz";

      }

      $arr['08_SubPres|Subjontiu present']       =  "sca,scas,sca,scam,scatz,scan";

      switch ($model){
        case '343' : $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";break;
        default :
          $arr['09_SubImp|Subjontiu imperfach']      =  "squèsse,squèsses,squèsse,squèssem,squèssetz,squèsson";
      }

      $arr['10_Conditional|Conditional']         =  "isseriái,isseriás,isseriá,isseriam,isseriatz,isserián";
      return $arr;
      //***     
    case '347' : // claure

      $arr['00_IndPres|Present']                 =  "si,ses,,sèm,sètz,son";
      $arr['01_IndImp|Imperfach']                =  "siái,siás,siá,siam,siatz,sián";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      $arr['03_IndFutur|Futur']                  =  "rai,ràs,rà,rem,retz,ràn";
      $arr['04_Infinitiu|Infinitiu']             =  "re";
      $arr['05_Gerondiu|Gerondiu']               =  "sent";
      $arr['06_PartPassat|Participi passat']     =  "s,sa";
      $arr['07_Imperatiu|Imperatiu']             =  ",gam,sètz,gas,gam,gatz";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      $arr['10_Conditional|Conditional']         =  "riái,riás,riá,riam,riatz,rián";
      return $arr;
      //***     
    case '348' : // torçer
      $arr['00_IndPres|Present']                 =  "ci,ces,ç,cèm,cètz,çon";
      $arr['01_IndImp|Imperfach']                =  "ciái,ciás,ciá,ciam,ciatz,cián";
      $arr['02_IndPret|Preterit']                =  "cèri,cères,cèt,cèrem,cèretz,cèron";
      $arr['03_IndFutur|Futur']                  =  "cerai,ceràs,cerà,cerem,ceretz,ceràn";
      $arr['04_Infinitiu|Infinitiu']             =  "cer";
      $arr['05_Gerondiu|Gerondiu']               =  "cent";
      $arr['06_PartPassat|Participi passat']     =  "çut,çuda";
      $arr['07_Imperatiu|Imperatiu']             =  "ç,çam,cètz,ças,çam,çatz";
      $arr['08_SubPres|Subjontiu present']       =  "ça,ças,ça,çam,çatz,çan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "cèsse,cèsses,cèsse,cèssem,cèssetz,cèsson";
      $arr['10_Conditional|Conditional']         =  "ceriái,ceriás,ceriá,ceriam,ceriatz,cerián";
      return $arr;
    case '349' : // vencer
      $arr['00_IndPres|Present']                 =  "ci,ces,ç,cèm,cètz,con";
      $arr['01_IndImp|Imperfach']                =  "ciái,ciás,ciá,ciam,ciatz,cián";
      $arr['02_IndPret|Preterit']                =  "quèri,quères,quèt,quèrem,quèretz,quèron";
      $arr['03_IndFutur|Futur']                  =  "cerai,ceràs,cerà,cerem,ceretz,ceràn";
      $arr['04_Infinitiu|Infinitiu']             =  "cer";
      $arr['05_Gerondiu|Gerondiu']               =  "cent";
      $arr['06_PartPassat|Participi passat']     =  "cut,cuda";
      $arr['07_Imperatiu|Imperatiu']             =  "ç,cam,cètz,cas,cam,catz";
      $arr['08_SubPres|Subjontiu present']       =  "ca,cas,ca,cam,catz,can";
      $arr['09_SubImp|Subjontiu imperfach']      =  "quèsse,quèsses,quèsse,quèssem,quèssetz,quèsson";
      $arr['10_Conditional|Conditional']         =  "ceriái,ceriás,ceriá,ceriam,ceriatz,cerián";
      return $arr;
      //***
    case '350' : // beure
    case '351' : // dever
    case '352' : // viure
    case '353' : // escriure
    case '354' : // moure
      $arr['00_IndPres|Present']      =  "vi,ves,u,vèm,vètz,von";
      $arr['01_IndImp|Imperfach']     =  "viái,viás,viá,viam,viatz,vián";
      switch ($model){
        case '352' :
          $arr['02_IndPret|Preterit'] =  "squèri,squères,squèt,squèrem,squèretz,squèron";break;
        default :
          $arr['02_IndPret|Preterit'] =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      }

      $arr['03_IndFutur|Futur']       =  "urai,uràs,urà,urem,uretz,uràn";
      $arr['04_Infinitiu|Infinitiu']  =  "ure";
      $arr['05_Gerondiu|Gerondiu']    =  "vent";
      switch ($model){
        case '352' :
          $arr['06_PartPassat|Participi passat']     =  "scut,scuda"; break;
        case '353' :
          $arr['06_PartPassat|Participi passat']     =  "ch,cha"; break;
        default :
          $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      }
      switch ($model){
        case '352' :
          $arr['07_Imperatiu|Imperatiu']             =  "u,scam,vètz,scas,scam,scatz";break;
        default :
          $arr['07_Imperatiu|Imperatiu']             =  "u,gam,vètz,gas,gam,gatz";
      }

      switch ($model){
        case '352' : 
          $arr['08_SubPres|Subjontiu present']       =  "sca,scas,sca,scam,scatz,scan";
          $arr['09_SubImp|Subjontiu imperfach']      =  "squèsse,squèsses,squèsse,squèssem,squèssetz,squèsson";break;
        default :
          $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
          $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      }
      $arr['10_Conditional|Conditional']         =  "uriái,uriás,uriá,uriam,uriatz,urián";
      return $arr;
      //***
    case '373' : // ónher 
    case '374' : // jónher

      $arr['00_IndPres|Present']                 =  "hi,hes,h,hèm,hètz,hon";
      $arr['01_IndImp|Imperfach']                =  "hiái,hiás,hiá,hiam,hiatz,hián";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      $arr['03_IndFutur|Futur']                  =  "herai,heràs,herà,herem,heretz,heràn";
      $arr['04_Infinitiu|Infinitiu']             =  "her";
      $arr['05_Gerondiu|Gerondiu']               =  "hent";
      $arr['06_PartPassat|Participi passat']     =  ($model == '373')?"ch,cha":"t,ta";
      $arr['07_Imperatiu|Imperatiu']             =  "h,gam,hètz,gas,gam,gatz";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      $arr['10_Conditional|Conditional']         =  "heriái,heriás,heriá,heriam,heriatz,herián";
      return $arr;
      //***
    case '314' : // perdre

      $arr['00_IndPres|Present']                 =  "di,des,t,dèm,dètz,don";
      $arr['01_IndImp|Imperfach']                =  "diái,diás,diá,diam,diatz,dián";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      $arr['03_IndFutur|Futur']                  =  "irai,iràs,irà,irem,iretz,iràn";
      $arr['04_Infinitiu|Infinitiu']             =  "der";
      $arr['05_Gerondiu|Gerondiu']               =  "dent";
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      $arr['07_Imperatiu|Imperatiu']             =  "sca,scam,scatz,scas,scam,scatz";
      $arr['08_SubPres|Subjontiu present']       =  "sca,scas,sca,scam,scatz,scan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      $arr['10_Conditional|Conditional']         =  "iriái,iriás,iriá,iriam,iriatz,irián";  
      return $arr;
      //***
    case '385'  :
    case '387'  :
      $arr['00_IndPres|Present']                 =  "ri,res,,rèm,rètz,ron";
      $arr['01_IndImp|Imperfach']                =  "riái,riás,riá,riam,riatz,rián";
      $arr['02_IndPret|Preterit']                =  "reguèri,reguères,reguèt,reguèrem,reguèretz,reguèron";
      $arr['03_IndFutur|Futur']                  =  "rerai,reràs,rerà,rerem,reretz,reràn";
      $arr['04_Infinitiu|Infinitiu']             =  "rer";
      $arr['05_Gerondiu|Gerondiu']               =  "rent";
      $arr['06_PartPassat|Participi passat']     =  "regut,reguda";
      $arr['07_Imperatiu|Imperatiu']             =  ",regam,rètz,regas,regam,regatz";
      $arr['08_SubPres|Subjontiu present']       =  "rega,regas,rega,regam,regatz,regan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "reguèsse,reguèsses,reguèsse,reguèssem,reguèssetz,reguèsson";
      $arr['10_Conditional|Conditional']         =  "reriái,reriás,reriá,reriam,reriatz,rerián";
      return $arr;

  }   

  //**************************************************
  //**************************************************
  // regular form                                    *
  //**************************************************
  //**************************************************
  $arr['00_IndPres|Present']                 =  "i,es,,èm,ètz,on";
  $arr['01_IndImp|Imperfach']                =  "iái,iás,iá,iam,iatz,ián";
  $arr['02_IndPret|Preterit']                =  "èri,ères,èt,èrem,èretz,èron";
  $arr['03_IndFutur|Futur']                  =  "rai,ràs,rà,rem,retz,ràn";
  $arr['04_Infinitiu|Infinitiu']             =  "re";
  $arr['05_Gerondiu|Gerondiu']               =  "ent";
  $arr['06_PartPassat|Participi passat']     =  "ut,uda";
  $arr['07_Imperatiu|Imperatiu']             =  ",am,ètz,as,am,atz";
  $arr['08_SubPres|Subjontiu present']       =  "a,as,a,am,atz,an";
  $arr['09_SubImp|Subjontiu imperfach']      =  "èsse,èsses,èsse,èssem,èssetz,èsson";
  $arr['10_Conditional|Conditional']         =  "riái,riás,riá,riam,riatz,rián";

  // 
  switch ($model){
    case '345' :
    case '360' :
      $arr['04_Infinitiu|Infinitiu']             =  "er";
      $arr['03_IndFutur|Futur']                  =  "erai,eràs,erà,erem,eretz,eràn";
      $arr['10_Conditional|Conditional']         =  "eriái,eriás,eriá,eriam,eriatz,erián";
      break;
    case '355' :
    case '361' :
      $arr['04_Infinitiu|Infinitiu']             =  "er";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      switch ($model){
        case '355' :
          $arr['03_IndFutur|Futur']                  =  "erai,eràs,erà,erem,eretz,eràn";
          $arr['10_Conditional|Conditional']         =  "eriái,eriás,eriá,eriam,eriatz,erián";
          break;
        default :
          $arr['03_IndFutur|Futur']                  =  "drai,dràs,drà,drem,dretz,dràn";
          $arr['10_Conditional|Conditional']         =  "driái,driás,driá,driam,driatz,drián";
      }
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      $arr['07_Imperatiu|Imperatiu']             =  ",gam,ètz,gas,gam,gatz";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      break;
    case '362' :
      $arr['04_Infinitiu|Infinitiu']             =  "ir";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      $arr['03_IndFutur|Futur']                  =  "drai,dràs,drà,drem,dretz,dràn";
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      $arr['07_Imperatiu|Imperatiu']             =  "i,gam,ètz,gas,gam,gatz";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      $arr['10_Conditional|Conditional']         =  "driái,driás,driá,driam,driatz,drián";
      break;
    case '363' :
      $arr['04_Infinitiu|Infinitiu']             =  "e";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      $arr['03_IndFutur|Futur']                  =  "drai,dràs,drà,drem,dretz,dràn";
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      $arr['10_Conditional|Conditional']         =  "driái,driás,driá,driam,driatz,drián";
      $arr['07_Imperatiu|Imperatiu']             =  ",gam,ètz,gas,gam,gatz";
      break;
    case '364' :
      $arr['04_Infinitiu|Infinitiu']             =  "er";
      $arr['03_IndFutur|Futur']                  =  "erai,eràs,erà,erem,eretz,eràn";
      $arr['10_Conditional|Conditional']         =  "eriái,eriás,eriá,eriam,eriatz,erián";
      break;
    case '370' :
    case '371' :
    case '372' :
    case '375' :
    case '383' :
    case '384' :
      $arr['00_IndPres|Present']                 =  "hi,hes,h,hèm,hètz,hon";
      $arr['01_IndImp|Imperfach']                =  "hiái,hiás,hiá,hiam,hiatz,hián";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";

      $arr['03_IndFutur|Futur']                  =  "herai,heràs,herà,herem,heretz,heràn";
      $arr['04_Infinitiu|Infinitiu']             =  "her";
      $arr['05_Gerondiu|Gerondiu']               =  "hent";
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      $arr['07_Imperatiu|Imperatiu']             =  "h,ham,hètz,as,am,atz";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
      $arr['10_Conditional|Conditional']         =  "heriái,heriás,heriá,heriam,heriatz,herián";
      break;
    case '380' :
    case '382' :
      $arr['04_Infinitiu|Infinitiu']             =  "er";
      $arr['02_IndPret|Preterit']                =  "guèri,guères,guèt,guèrem,guèretz,guèron";
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      $arr['07_Imperatiu|Imperatiu']             =  "ga,gam,gatz,gas,gam,gatz";
      $arr['08_SubPres|Subjontiu present']       =  "ga,gas,ga,gam,gatz,gan";
      $arr['09_SubImp|Subjontiu imperfach']      =  "guèsse,guèsses,guèsse,guèssem,guèssetz,guèsson";
    case '381' :
      $arr['04_Infinitiu|Infinitiu']             =  "re";
      $arr['06_PartPassat|Participi passat']     =  "gut,guda";
      break;
    case '386'  :
      $arr['04_Infinitiu|Infinitiu']             =  "re";
      $arr['02_IndPret|Preterit']                =  "eguèri,eguères,eguèt,eguèrem,eguèretz,eguèron";
      $arr['06_PartPassat|Participi passat']     =  "egut,eguda";
      $arr['09_SubImp|Subjontiu imperfach']      =  "eguèsse,eguèsses,eguèsse,eguèssem,eguèssetz,eguèsson";
      break;
  }
  return $arr;

} //conjugador_getTempsGroup3

/******************************
 ******************************/
function conjugador_conjugateGroup3_n($verb_infinitiu,$model){

  $arr = conjugador_getTempsGroup3_n($model);
  //  1,2,3,5 last letters of the infinitive
  $arr1lettersDropped = array('363');
  $arr3lettersDropped = array('312','313','314','325','330','332','333','334','335', '336','348','349','350','351','352','353','354','370','371','372','373','374','375','383','384','385','387');
  $arr5lettersDropped = array('340','341', '342', '343', '344');

  if (in_array($model, $arr3lettersDropped)){ 
    $rootSaved = substr($verb_infinitiu,0,-3);
  }else if (in_array($model, $arr5lettersDropped)){ 
    $rootSaved = substr($verb_infinitiu,0,-5);
  }else if (in_array($model, $arr1lettersDropped)){ 
    $rootSaved = substr($verb_infinitiu,0,-1);
  }else{
    $rootSaved = substr($verb_infinitiu,0,-2);
  } 

  $o="<div class=\"conjgroup3\" id=\"$verb_infinitiu.$model\">\n";

  $isModeDisplayed = FALSE;

  // for each temps
  foreach($arr as $lib=>$desinence){
    $arrLib = explode('|', $lib);
    switch($arrLib[0]){
      case "00_IndPres"   :   $mode = 'Indicatiu'; $o .= "<div class=\"indicative\"><span class=\"label_mode\">Indicatiu</span><br><br>\n"; break;
      case "04_Infinitiu" :   $mode = 'Fòrmas impersonalas'; $o .= "\n</div>\n<div class=\"impersonal_forms\"><span class=\"label_mode\">Fòrmas impersonalas</span><br><br>\n"; break;
      case "07_Imperatiu" :   $mode = 'Imperatiu'; $o .= "\n</div>\n<div class=\"imperative\"><span class=\"label_mode\">Imperatiu</span><br><br>\n"; break;
      case "08_SubPres"   :   $mode = 'Subjontiu'; $o .= "\n</div>\n<div class=\"subjunctive\"><span class=\"label_mode\">Subjontiu</span><br><br>\n"; break;
      case "10_Conditional" : $mode = 'Condicional'; $o .= "\n</div>\n<div class=\"conditional\"><span class=\"label_mode\">Condicional</span><br><br>\n"; break;
    } //switch

    $o .= $arrLib[1] . '<br><br>';

    $isImperative=($arrLib[0] == "07_Imperatiu")?1:0;
    $gerundiveStuff=($arrLib[0] == "05_Gerondiu")?"en ":"";

    $desinences = explode(',', $desinence);
    $i=0;
    $arr = array();

    foreach ($desinences as $elmnt){
      $impStuff = '';
      if ($isImperative && $i < 3 ){
        $impStuff = " !";
      }
      if ($isImperative && $i >= 3 ){
        $impStuff = " pas !";
      }

      $root = conjugador_FixRadicalGr3_n($model,$rootSaved,$elmnt);

      $arr[$i++] = $gerundiveStuff . $root . '-' . $elmnt . $impStuff ."</span><br>";

    } // for desinences
    
    // layout as a table

    $o .= "<table class=\"$lib\"><tbody>";
    
    // all cardinalites
    if (count($arr) == 6){
      for($i=0; $i < 3 ; $i++){
        $j = $i + 3;
        $o .= "<tr><td>$arr[$i]</td><td>$arr[$j]</td></tr>\n";
      }
    }

    if (count($arr) == 2){
      $o .= "<tr><td>$arr[0]</td><td>$arr[1]</td></tr>\n";
    }

    if (count($arr) == 1){
      $o .= "<tr><td>$arr[0]</td><td></td></tr>\n";
    }

    $o .= "</tbody></table>";
    $o .= "<br>";
  } // foreach temps

  $o .= "</div>";

  $o = conjugador_PhonologicFixes($o);
  //
  // Here the process is almost over the sting is full of conjugations
  // 
  switch($model){
    case '303' : // metre
      $pattern = '/et-ut/i';
      $replacement = 'es-';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/et-uda/i';
      $replacement = 'es-a';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '310' :  // escodre
      $pattern = '/od- /i';
      $replacement = 'ot- ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/od-<\/span>/i';
      $replacement = 'ot-</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '311' :  // mèdre
      $pattern = '/èd- /i';
      $replacement = 'èt- ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/èd-<\/span>/i';
      $replacement = 'èt-</span>';
      $o = preg_replace($pattern, $replacement, $o);
      // infinitive
      $pattern = '/ed-re<\/span>/i';
      $replacement = 'èd-re</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '312' :  // saber
      $pattern = '/a-pia /i';
      $replacement = 'à-pia ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/a-pias<\/span>/i';
      $replacement = 'à-pias</span>';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/a-pia<\/span>/i';
      $replacement = 'à-pia</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '313' :  // recebre
      $pattern = '/e-pia /i';
      $replacement = 'è-pia ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/e-pias /i';
      $replacement = 'è-pias ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/e-pias<\/span>/i';
      $replacement = 'è-pias</span>';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/e-pia<\/span>/i';
      $replacement = 'è-pia</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '315' :  // ardre
      $pattern = '/d-ut/i';
      $replacement = 's-';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/d-uda/i';
      $replacement = 's-a';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '316' :  // pèrdre
      $pattern = '/(.+?)erd-re/'; 
      $replacement = '${1}èrd-re';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '317' :  // mòrdre
      $pattern = '/(.+?)ord-re/'; 
      $replacement = '${1}òrd-re';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '320' :  // cóser
      $pattern = '/(.+?)os-re/'; 
      $replacement = '${1}ós-er';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '321' :  // aucire 
    case '322' :  // sufire
      $pattern = '/i-s /i';
      $replacement = 'í-s ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/i-s<\/span>/i';
      $replacement = 'í-s</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '326' :  // conclure
      $pattern = '/u-s<\/span>/i';
      $replacement = 'ú-s</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '331' :  // creire
      $pattern = '/i-g/i';
      $replacement = '-g';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '333' :  // sèire
      $pattern = '/e-ire<\/span>/i';
      $replacement = 'è-ire</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '334' :  // fòire
    case '335' :  // còire
      $pattern = '/o-ire<\/span>/i';
      $replacement = 'ò-ire</span>';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/o-ch/i';
      $replacement = 'uè-ch';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '336' :  // veire
      $pattern = '/e-st/i';
      $replacement = 'i-st';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '345' :  // mólzer
      $pattern = '/olz- /i';
      $replacement = 'ols- ';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/olz-<\/span>/i';
      $replacement = 'ols-</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '354' :  // mòure
      $pattern = '/o-ure/i';
      $replacement = 'ò-ure';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '355' :  // sòlver
      $pattern = '/olv-er/i';
      $replacement = 'òlv-er';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '360' :  // témer
      $pattern = '/em-er/i';
      $replacement = 'ém-er';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '362' :  // venir 
      $pattern = '/ven-i /i';
      $replacement = 'vèn-i ';
      $o = preg_replace($pattern, $replacement, $o); // vèni
    case '364' :  // cèrner 
      $pattern = '/ern-er/i';
      $replacement = 'èrn-er';
      $o = preg_replace($pattern, $replacement, $o); // cèrner
    case '371' :  // plànher
    case '375' :  // frànher
      $pattern = '/an-her<\/span>/i';
      $replacement = 'àn-her</span>';
      $o = preg_replace($pattern, $replacement, $o);
    case '372' :  // cénher
      $pattern = '/en-her<\/span>/i';
      $replacement = 'én-her</span>';
      $o = preg_replace($pattern, $replacement, $o);
    case '374' :  // jónher
      $pattern = '/jon-t(.*?)<\/span>/i';
      $replacement = 'jun-t${1}</span>';
      $o = preg_replace($pattern, $replacement, $o);
    case '373' :  // ónher
      $pattern = '/on-her<\/span>/i';
      $replacement = 'ón-her</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '381' :  // mòlre
    case '382' :  // voler
      $pattern = '/ol-<\/span>/i';
      $replacement = 'òl-</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '383' :  // bólher
      $pattern = '/ol-her<\/span>/i';
      $replacement = 'òl-her</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '386' :  // quèrre
      $pattern = '/er-<\/span>/i';
      $replacement = 'ièr-</span>';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/er-re<\/span>/i';
      $replacement = 'èr-re</span>';
      $o = preg_replace($pattern, $replacement, $o);
      $pattern = '/er- /i';
      $replacement = 'ièr- ';
      $o = preg_replace($pattern, $replacement, $o);
      break;
    case '387' :  // córrer
      $pattern = '/or-re<\/span>/i';
      $replacement = 'ór-re</span>';
      $o = preg_replace($pattern, $replacement, $o);
      break;

  }

  // add carriage return for cosmetic
  $pattern = '/<br>/';
  $replacement = "<br>\n";
  $o = preg_replace($pattern, $replacement, $o);

  // add class for desinence
  $pattern = '/-/';
  $replacement = "<span class=\"des\">";
  $o = preg_replace($pattern, $replacement, $o);
  
  return "$o</div>";
} // conjugador_conjugateGroup3
