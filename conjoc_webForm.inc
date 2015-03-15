<?php
//--*-PHP-*--
/**
 * @file
 * conjoc_verbForm.inc
 *
 * Demonstrates usage of the Form API's autocomplete features.
 *
 * This file provides three examples in increasing complexity:
 * - A simple username autocomplete (usernames are unique, so little effort is
 *   required)
 * - A node title autocomplete (titles are not unique, so we have to find the
 *   nid and stash it in the field)
 * - A username autocomplete that updates a node title autocomplete with a
 *   changed #autocomplete_path so that the #autocomplete_path can have
 *   context (the username to use in the search).
 */
require_once('conjugador_lib.inc');
require_once('conjugador_aux.inc');
require_once('conjugador_gr1.inc');
require_once('conjugador_gr2.inc');
require_once('conjugador_gr3.inc');

/**
   LENGADOCIAN
 */
function ajax_conjoc_verb_autocomplete($form, &$form_state) {

  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $verb   = (!empty($form_state['values']['leng_verb_search']['verb']))?$form_state['values']['leng_verb_search']['verb']: conjoc_getRandomLengadocianVerb();

  $randomVerb = empty($form_state['values']['leng_verb_search']['verb']);
  /*
    V E R B   S E A R C H
  */
  $form['leng_verb_search'] = array(
  '#type' => 'fieldset',
  '#title' => t('Verb search'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['leng_verb_search']['verb'] = array(
    '#weight' => 1,
    '#type' => 'textfield',
    '#default_value' => $verb,

    '#title' => t('Choose a verb'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'conjoc/verb_autocomplete_callback',
  );

  $form['leng_verb_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  /*
    U S U A L S   V E R B S
  */

  $form['verbs_usuals'] = array(
  '#type' => 'fieldset',
  '#title' => t('Usual verbs'),
  '#weight' => 2,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['verbs_usuals']['info'] = array(
    '#markup' => conjugador_displayUsuals(),
    '#weight' => 1,
  );

  /*
    T O P 2 0   V E R B S
  */


  $form['TOP20_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Top 20 verbs'),
  '#weight' => 3,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );
   
  $form['TOP20_verbs']['selected'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => conjugador_getTop20(),
    //    '#default_value' => $category['TOP20_verbs']['selected'],
    '#description' => t('To be done.'),
  );  

  $form['TOP20_verbs']['info'] = array(
    //    '#markup' => '<div>'. conjugador_displayTop20($verb) .'</div>',
  );

  $form['TOP20_verbs']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit to be translated'),
  );

  /*
    S I N G L E   V E R B S
  */

  $form['single_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Single verbs'),
  '#weight' => 4,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['single_verbs']['info'] = array(
  '#markup' => conjugador_displaySingles(),
  );

  /*
    O T H E R S   I N   M O D E L
  */
  $countOthers = 0;
  if (isset($form_state['values']['leng_verb_search']['verb']) && ($countOthers = conjugador_countOthersInModel($form_state['values']['leng_verb_search']['verb'])) && $countOthers > 0 && $countOthers <= variable_get("MAX_OTHERVERBS")){

    $form['other_verbs_in_model'] = array(
      '#type' => 'fieldset',
      '#title' => t('Other verbs in model'),
      '#weight' => 5,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['other_verbs_in_model']['selected'] = array(
      '#type' => 'select',
      '#title' => t('Selected'),
      '#options' => conjugador_getOthersInModel($verb),
      //    '#default_value' => $category['other_verbs_in_model']['selected'],
      '#description' => t('To be done.'),
    );  

    $form['other_verbs_in_model']['info'] = array(
      //      '#markup' => '<div>'. conjugador_displayOthersInModel($verb) .'</div>',
    );

    $form['other_verbs_in_model']['submit'] = array(
      '#weight' => 2,
      '#type' => 'submit',
      '#value' => t('Submit, to be changed'),
    );

  }

  /*
    V E R B   C O N J U G A T E D
  */

  $form['verb_conjugated'] = array(
  '#type' => 'fieldset',
  '#title' => ($randomVerb)?t('Random verb conjugated '):t('Verb conjugated'),
  '#weight' => 7,
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $action = "as to be done.";

  $form['verb_conjugated']['conjugation'] = array(
    '#markup' => '<div>'. conjugador_l($verb, $action) .'</div>',
  );

  return $form;
}

/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_conjoc_verb_autocomplete_callback($string = "") {

  $matches = array();

  if ($string) {
    $query = db_select('sauzet_verbsmodel','vm');
    $query->join('sauzet_model', 'm', 'vm.nummodel=m.nummodel');
    $query->groupby('vm.verb');
    $query->fields('vm', array('id','verb', 'nummodel'));
    $query->fields('m', array('verb_prime','label_conjugation'));
    $result = $query->condition('vm.verb', db_like($string) . '%', 'LIKE')->range(0, 100)->execute();

    foreach ($result as $verbline) {
      // In the simplest case (see user_autocomplete), the key and the value are
      // the same. Here we'll display the uid along with the username in the
      // dropdown.
      $matches[$verbline->verb] = check_plain($verbline->verb) . " (n° model=$verbline->nummodel, $verbline->label_conjugation))";
    }
  } // if

  drupal_json_output($matches);
}

/**
 * Submit handler for node lookup unique autocomplete example.
 *
 * Here the nid has already been placed in $form_state['values']['node'] by the
 * validation handler.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 *
 * @return array
 *   Form API array.
 */
function ajax_conjoc_verb_autocomplete_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 */
function ajax_conjoc_verb_autocomplete_validate($form, &$form_state) {
  drupal_set_message('ajax_conjoc_verb_autocomplete_validate');
  $verb = $form_state['values']['leng_verb_search']['verb'];

  if (!empty($form_state['values']['other_verbs_in_model']['selected'])){
//    drupal_set_message("selected has value " . $form_state['values']['other_verbs_in_model']['selected']);
  }

  if (!empty($form_state['values']['TOP20_verbs']['selected'])){
//    drupal_set_message("selected has value " . $form_state['values']['TOP20_verbs']['selected']);
  }

  // Now, if we somehow found a nid, assign it to the node. If we failed, emit
  // an error.
  if (empty($verb)) {
    form_error($form['leng_verb_search']['verb'], t('Sorry, you must ask for a verb'));
  }

}

function conjoc_getRandomLengadocianVerb(){
    $results = db_query("SELECT * FROM `sauzet_verbsmodel` ORDER BY RAND() LIMIT 1");
    $line = $results->fetchObject();

    return($line->verb);

} // conjoc_getRandomLengadocianVerb()


/**************
* D I S P L A Y
***************/

function conjugador_l($verb = NULL, $action = NULL){
  variable_set("DISPLAYNOTES", false);
  variable_set("MAX_OTHERVERBS",30);


  drupal_add_js (drupal_get_path('module', 'conjoc') . '/js/cplo.js');
  drupal_add_css(drupal_get_path('module', 'conjoc') . '/css/conjugador.css');

  $results = db_query("SELECT * FROM `sauzet_verbsmodel` WHERE verb =:verb", array(':verb'=>$verb));
  $line  = $results->fetchObject();
  $model = $line->nummodel;
  $see   = $line->see;

  $o = "";
  $o .= _nl("<div class=\"conjugador\">\n");


  $o .= "<div class=\"verb\" id=\"$verb\">\n";

  if ($see){
    $o .= t("remandament") . " <span class=\"label_verb\">" . l("$see", "conjoc/verb_autocomplete/better_see/$see") . "</span><br><br>";
  }else{
    $o .= "<span class=\"label_verb\">$verb</span><br><br>\n";
  }
  $results = db_query("SELECT * FROM {sauzet_model} where nummodel=:model",array(':model'=>$model));
  $line = $results->fetchObject();
  $label = $line->label_conjugation;
  $o .= "<span class=\"label_conjugation\">Modèl $model : $label</span><br><br>\n";
  // caution the star symbol is legitimate as it marks an incorrect form
  // but this symbol must be removed
  $pattern = '/\*/';
  $replacement = '';
  $verb = preg_replace($pattern, $replacement, $verb);

  $o .= conjugador_conjugate($verb,$model). "<br>\n</div>\n";

  if (variable_get("DISPLAYNOTES")){
    $o .= "<div class=\"notes\"><span class=\"label_notes\">Nòtas</span>";
    $o .= conjugador_displaynotes($model);
    $o .= "</div>";
  }

  $o .= "</div>\n";

  return $o;

} // conjugador_display

function conjugador_conjugate($verb,$model){

  $group = substr($model,0,1);

  switch ($group){
    case '0':
      $o = conjugador_conjugateAuxillars($verb,$model);
      break;
    case '1':
      $o = conjugador_conjugateGroup1($verb,$model);
      break;
    case "2":
      $o = conjugador_conjugateGroup2($verb,$model);
      break;
    case "3":
      $o = conjugador_conjugateGroup3($verb,$model);
      break;
    }
  return $o;
} // conjugador_conjugate

function conjugador_displaynotes($nummodel){
  $model = $nummodel . '_';

  $results = db_query("SELECT * FROM {sauzet_notes} where code=:model", array(':model'=>$model));
  $line = $results->fetchObject();

  return $line->content;
} // conjugador_displaynotes

function conjugador_displaySingles(){

  $results = db_query("SELECT COUNT(*) as cpter, group_concat(verb) as concat FROM {sauzet_verbsmodel} GROUP BY nummodel ORDER BY cpter ASC LIMIT 20");

  $o = "<table style=\"width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">";
  $o .= "<tbody>";

  $cptr = 0;

  while($line = $results->fetchObject()){
    if ($line->cpter == 1){
      $verb = $line->concat;

      if (!$cptr % 5){
        $o .= '<tr align=\"center\">' . l("$verb", "conjoc/verb_autocomplete/singles/$verb");
      }

      $o .= "<td>" . l("$verb","conjoc/verb_autocomplete/singles/$verb");

      if ($cptr % 5 == 4){
        $o .= _nl("</tr>");
      }
      $cptr++;
    }
  } // while
  
  $o .= _nl("</tbody>");
  $o .= _nl("</table>");

  return $o;
} // conjugador_displaySingles

function conjugador_displayTop20($verbCurrent){

 $results = db_query("SELECT COUNT(*) as cpter, group_concat(cast(idverb as char)) as concat FROM {sauzet_access} GROUP BY idverb ORDER BY cpter DESC LIMIT 20");

  $o = "<table style=\"width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">";
  $o .= "<tbody>";

  $o .= "<tr>";
  $o .= '<select name="top20_verb" onchange="this.form.submit()">';
  
  while($line = $results->fetchObject()){
    $arr = explode(',', $line->concat);
    $id = $arr[0];
    $resInner = db_query("SELECT verb FROM {sauzet_verbsmodel} WHERE id =:id LIMIT 1",array(':id'=>$id));
    $lineInner = $resInner->fetchObject();
    $verb = $lineInner->verb;
    $selected = ($verbCurrent == $verb)?'selected="selected"':"";
    $o .= "<option value=\"$lineInner->verb\" $selected>$verb</option>";
 } // while
  $o .= "</select>";
  $o .= "</tr>";

  $o .= "</tbody>";
  $o .= "</table>";

  return $o;
} // conjugador_displayTop20

function conjugador_displayOthersInModel($verb){

  $count = conjugador_countOthersInModel($verb);

  if ($count <= variable_get("MAX_OTHERVERBS") && $count){
    // SELECT sv2.verb as verb, sv2.nummodel, sv2.id as id FROM sauzet_verbsmodel as sv1, sauzet_verbsmodel as sv2 where sv1.verb='aduire' and sv1.nummodel = sv2.nummodel and sv2.verb <> 'aduire' 
    $results = db_query("SELECT sv2.verb as verb, sv2.nummodel FROM sauzet_verbsmodel as sv1, sauzet_verbsmodel as sv2 where sv1.verb=:verb and sv1.nummodel = sv2.nummodel and sv2.verb <> :verb", array(':verb'=>$verb));

    $o = "<table style=\"width: 50%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">";
    $o .= "<tbody>";

    $o .= "<tr>";
    $cptr = 0;
    $o .= '<select name="othersInModel_verb" onchange="this.form.submit()">';
    $o .= "<option>...</option>";
  
    while($line = $results->fetchObject()){
      $selected = ($line->verb == $verb)?'selected="selected"':"";
      $o .= "<option value=\"$line->verb\" $selected>$line->verb</option>";
      $cptr++;
    } // while

    $o .= "</select>";
    $o .= "</tr>";

    $o .= "</tbody>";
    $o .= "</table>";

  }else{
    $o = "";
  }

  return $o;
} // conjugador_displayOthersInModel

function conjugador_countOthersInModel($verb){
  $resultsCount = db_query("SELECT count(*) as cptr FROM `sauzet_verbsmodel` as sv1, sauzet_verbsmodel as sv2 where sv1.verb=:verb and sv1.nummodel = sv2.nummodel and sv2.verb <> :verb", array(':verb'=>$verb));

  $line = $resultsCount->fetchObject();
  return $line->cptr;
} // conjugador_countOthersInModel

function conjugador_displayUsuals(){

  $o = "<table style=\"width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\">";
  $o .= "<tbody>";
  $o .= "<tr align=\"center\">";
  $o .= "<td>". l('èsser','conjoc/verb_autocomplete/usuals/èsser') . "</td>";
  $o .= "<td>". l('aver','conjoc/verb_autocomplete/usuals/aver') . "</td>";
  $o .= "<td>". l('anar','conjoc/verb_autocomplete/usuals/anar') . "</td>";
  $o .= "<td>". l('far','conjoc/verb_autocomplete/usuals/far') . "</td>";
  $o .= "<td>". l('venir','conjoc/verb_autocomplete/usuals/venir') . "</td>";
  $o .=  "</tr>";
  $o .=  "<tr align=\"center\">";
  $o .= "<td>". l('cantar','conjoc/verb_autocomplete/usuals/cantar')."</td>";
  $o .= "<td>". l('poder','conjoc/verb_autocomplete/usuals/poder'). "</td>";
  $o .= "<td>". l('saber','conjoc/verb_autocomplete/usuals/saber'). "</td>";
  $o .= "<td>". l('valer','conjoc/verb_autocomplete/usuals/valer') ."</td>";
  $o .= "<td>". l('aduire','conjoc/verb_autocomplete/usuals/aduire')."</td>";
  $o .= "</tr>";
  $o .= "</tbody>";
  $o .= "</table>";

  return $o;
} // conjugador_displayUsuals 

function conjugador_getTop20(){
  $arret = array();
  $results = db_query("SELECT COUNT(*) as cpter, group_concat(cast(idverb as char)) as concat FROM {sauzet_access} GROUP BY idverb ORDER BY cpter DESC LIMIT 20");

  while($line = $results->fetchObject()){
    $arr = explode(',', $line->concat);
    $id = $arr[0];
    $resInner = db_query("SELECT verb FROM {sauzet_verbsmodel} WHERE id =:id LIMIT 1",array(':id'=>$id));
    $lineInner = $resInner->fetchObject();
    $verb = $lineInner->verb;
    $arret[$verb]=$verb;
  } // while

  return $arret;
}

function conjugador_getOthersInModel($verb){
  $arret = array();
  $results = db_query("SELECT sv2.verb as verb, sv2.nummodel FROM sauzet_verbsmodel as sv1, sauzet_verbsmodel as sv2 where sv1.verb=:verb and sv1.nummodel = sv2.nummodel and sv2.verb <> :verb", array(':verb'=>$verb));
  while($line = $results->fetchObject()){
    //      $selected = ($line->verb == $verb)?'selected="selected"':"";
    $verbCurrent = $line->verb;
    $arret[$verbCurrent]=$verbCurrent; 
  } // while

  return $arret;
}

/**
   PROVENCAL
 */

function ajax_provencal_verb_autocomplete($form, &$form_state) {

  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $verb   = (!empty($form_state['values']['prov_verb_search']['verb']))?$form_state['values']['prov_verb_search']['verb']: conjoc_getRandomProvencalVerb();

  $randomVerb = empty($form_state['values']['prov_verb_search']['verb']);
  /*
    V E R B   S E A R C H
  */
  $form['prov_verb_search'] = array(
  '#type' => 'fieldset',
  '#title' => t('Verb search'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['prov_verb_search']['verb'] = array(
    '#weight' => 1,
    '#type' => 'textfield',
    '#default_value' => $verb,

    '#title' => t('Choose a verb'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'conjoc/verb_autocomplete_prov_callback',
  );

  $form['prov_verb_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  /*
    U S U A L S   V E R B S
  */

  $form['prov_verbs_usuals'] = array(
  '#type' => 'fieldset',
  '#title' => t('Usual verbs'),
  '#weight' => 2,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['prov_verbs_usuals']['info'] = array(
    '#markup' => conjugador_displayUsuals(),
    '#weight' => 1,
  );

  /*
    T O P 2 0   V E R B S
  */


  $form['prov_TOP20_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Top 20 verbs'),
  '#weight' => 3,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );
   
  $form['prov_TOP20_verbs']['selected'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => conjugador_getTop20(),
    //    '#default_value' => $category['prov_TOP20_verbs']['selected'],
    '#description' => t('To be done.'),
  );  

  $form['prov_TOP20_verbs']['info'] = array(
    //    '#markup' => '<div>'. conjugador_displayTop20($verb) .'</div>',
  );

  $form['prov_TOP20_verbs']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit to be translated'),
  );

  /*
    S I N G L E   V E R B S
  */

  $form['prov_single_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Single verbs'),
  '#weight' => 4,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['prov_single_verbs']['info'] = array(
  '#markup' => conjugador_displaySingles(),
  );

  /*
    O T H E R S   I N   M O D E L
  */
  $countOthers = 0;
  if (isset($form_state['values']['prov_verb_search']['verb']) 
  && ($countOthers = conjugador_countOthersInModel($form_state['values']['prov_verb_search']['verb'])) 
  && $countOthers > 0 && $countOthers <= variable_get("MAX_OTHERVERBS")){

    $form['prov_other_verbs_in_model'] = array(
      '#type' => 'fieldset',
      '#title' => t('Other verbs in model'),
      '#weight' => 5,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['prov_other_verbs_in_model']['selected'] = array(
      '#type' => 'select',
      '#title' => t('Selected'),
      '#options' => conjugador_getOthersInModel($verb),
      //    '#default_value' => $category['other_verbs_in_model']['selected'],
      '#description' => t('To be done.'),
    );  

    $form['prov_other_verbs_in_model']['info'] = array(
      //      '#markup' => '<div>'. conjugador_displayOthersInModel($verb) .'</div>',
    );

    $form['prov_other_verbs_in_model']['submit'] = array(
      '#weight' => 2,
      '#type' => 'submit',
      '#value' => t('Submit, to be changed'),
    );

  }

  /*
    V E R B   C O N J U G A T E D
  */

  $form['prov_verb_conjugated'] = array(
  '#type' => 'fieldset',
  '#title' => ($randomVerb)?t('Random verb conjugated '):t('Verb conjugated'),
  '#weight' => 7,
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $action = "as to be done.";

  $form['prov_verb_conjugated']['conjugation'] = array(
    '#markup' => '<div>'. conjugador_l($verb, $action) .'</div>',
  );

  return $form;
}

/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_provencal_verb_autocomplete_callback($string = "") {

  $matches = array();

  if ($string) {
    $query = db_select('provencal_verbsmodel','vm');
    $query->join('provencal_model', 'm', 'vm.nummodel=m.nummodel');
    $query->groupby('vm.verb');
    $query->fields('vm', array('id','verb', 'nummodel'));
    $query->fields('m', array('verb_prime','label_conjugation'));
    $result = $query->condition('vm.verb', db_like($string) . '%', 'LIKE')->range(0, 100)->execute();

    foreach ($result as $verbline) {
      // In the simplest case (see user_autocomplete), the key and the value are
      // the same. Here we'll display the uid along with the username in the
      // dropdown.
      $matches[$verbline->verb] = check_plain($verbline->verb) . " (n° model=$verbline->nummodel, $verbline->label_conjugation))";
    }
  } // if

  drupal_json_output($matches);
}

function conjoc_getRandomProvencalVerb(){
    $results = db_query("SELECT * FROM `provencal_verbsmodel` ORDER BY RAND() LIMIT 1");
    $line = $results->fetchObject();

    return($line->verb);

} // conjoc_getRandomProvencalVerb()


/*
  G A S C O N
*/

function ajax_gascon_verb_autocomplete($form, &$form_state) {
//  drupal_set_message('ajax_gascon_verb_autocomplete');
  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $gasconManager = new ConjugationGasconManager();
  $drupalHTMLConverter = new ConverterHTML();
  $drupalLATEXConverter = new ConverterLATEX();
//  print_r($form_state);
  
  $verb   = (!empty($form_state['values']['gasc_verb_search']['verb']))?$form_state['values']['gasc_verb_search']['verb']: $gasconManager->getRandomVerb();

  $gasconManager->setVerb($verb);

  $randomVerb = empty($form_state['values']['gasc_verb_search']['verb']);
  /*
    V E R B   S E A R C H
  */
  $form['gasc_verb_search'] = array(
  '#type' => 'fieldset',
  '#title' => t('Verb search'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['gasc_verb_search']['verb'] = array(
    '#weight' => 1,
    '#type' => 'textfield',
    '#default_value' => $verb,

    '#title' => t('Choose a verb'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'conjoc/verb_autocomplete_gasc_callback',
  );

  $form['gasc_verb_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  /*
    U S U A L S   V E R B S
  */

  $form['gasc_verbs_usuals'] = array(
  '#type' => 'fieldset',
  '#title' => t('Usual verbs'),
  '#weight' => 2,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['gasc_verbs_usuals']['info'] = array(
    '#markup' => $drupalHTMLConverter->convertArray($gasconManager->getUsualVerbs()),
    '#weight' => 1,
  );

  /*
    T O P 2 0   V E R B S
  */


  $form['gasc_TOP20_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Top 20 verbs'),
  '#weight' => 3,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );
   
  $form['gasc_TOP20_verbs']['selected'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => $gasconManager->getTop20(),
    //    '#default_value' => $category['TOP20_verbs']['selected'],
    '#description' => t('To be done.'),
  );  

  $form['gasc_TOP20_verbs']['info'] = array(
    //    '#markup' => '<div>'. conjugador_displayTop20($verb) .'</div>',
  );

  $form['gasc_TOP20_verbs']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit to be translated'),
  );

  /*
    S I N G L E   V E R B S
  */

  $form['gasc_single_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Single verbs'),
  '#weight' => 4,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['gasc_single_verbs']['info'] = array(
  '#markup' => $drupalHTMLConverter->convertArray($gasconManager->getSingleVerbs()),
  );

  /*
    O T H E R S   I N   M O D E L
  */

  $countOthers = 0;

  if (isset($form_state['values']['gasc_verb_search']['verb']) 
  && ($countOthers = $gasconManager->getCountOthersInModel($form_state['values']['gasc_verb_search']['verb'])) 
  && $countOthers > 0 
  && $countOthers <= variable_get("MAX_OTHERVERBS")){

    $form['gasc_other_verbs_in_model'] = array(
      '#type' => 'fieldset',
      '#title' => t('Other verbs in model'),
      '#weight' => 5,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['gasc_other_verbs_in_model']['selected'] = array(
      '#type' => 'select',
      '#title' => t('Selected'),
      '#options' => $gasconManager->getOthersInModel($verb),
      //    '#default_value' => $category['other_verbs_in_model']['selected'],
      '#description' => t('To be done.'),
    );  

    $form['gasc_other_verbs_in_model']['info'] = array(
      //      '#markup' => '<div>'. conjugador_displayOthersInModel($verb) .'</div>',
    );

    $form['gasc_other_verbs_in_model']['submit'] = array(
      '#weight' => 2,
      '#type' => 'submit',
      '#value' => t('Submit, to be changed'),
    );

  }

  /*
    V E R B   C O N J U G A T E D
  */

  $form['gasc_verb_conjugated'] = array(
  '#type' => 'fieldset',
  '#title' => ($randomVerb)?t('Random verb conjugated '):t('Verb conjugated'),
  '#weight' => 7,
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $conjugated = $gasconManager->conjugate();
  $fileNameToDownload = $drupalLATEXConverter->convertConjugation($conjugated);

  $form['gasc_verb_conjugated']['downloadPDF'] = array(
    '#markup' => l(t("ficha en format PDF «" . $verb . "»" ) ,$fileNameToDownload) . '<img width="32px" src="/sites/default/files/img/logopdf.png"></img>',
  );

  $form['gasc_verb_conjugated']['conjugation'] = array(
    '#markup' => '<div>'. $drupalHTMLConverter->convertConjugation($conjugated) .'</div>',
  );
  

  return $form;
} // ajax_gascon_verb_autocomplete 

function ajax_gascon_verb_autocomplete_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_gascon_verb_autocomplete_callback($string = "") {
  $gasconManager = new ConjugationGasconManager();
  $gasconManager->getVerbAutoComplete($string);
}
