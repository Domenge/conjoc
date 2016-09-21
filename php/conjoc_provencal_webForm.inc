<?php
//--*-PHP-*--
/**
 * @file
 * conjoc_provencal_verbForm.inc
 *
 */

/**
   P R O V E N C A L
   P R O V E N C A L
   P R O V E N C A L
 */

function ajax_provencal_verb_autocomplete($form, &$form_state) {

  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $lengadocianManager = new ConjugationProvencalManager();
  $drupalHTMLConverter = new ConverterHTML();
  $drupalLATEXConverter = new ConverterLATEX();

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
//    '#markup' => conjugador_displayUsuals(),
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
//    '#options' => conjugador_getTop20(),
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
//  '#markup' => $drupalHTMLConverter->convertArray($lengadocianManager->getSingleVerbs()),
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
//    '#markup' => '<div>'. conjugador_l($verb, $action) .'</div>',
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
