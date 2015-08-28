<?php
//--*-PHP-*--
/**
 * @file
 * conjoc_lengadocian_verbForm.inc
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
 

/**
   LENGADOCIAN
 */

/*
TEI

function tei_export_lengadocian_all($form, &$form_state) {
  $form['#tree'] = TRUE;

  $lengadocianManager = new ConjugationLengadocianManager();
  $teiConverter = new ConverterTEI();

  $form['export_TEI'] = array(
  '#type' => 'fieldset',
  '#title' => t('Export Lengadocian all'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['export_TEI']['all'] = array(
    '#markup' => $teiConverter->convertArray($lengadocianManager->getAllVerbs()),
    '#weight' => 1,
  );

  return $form;
} // tei_export_lengadocian_all

*/ 

/*
Indexation

function indexation_lengadocian_all($form, &$form_state) {
  $form['#tree'] = TRUE;

  $lengadocianManager = new ConjugationLengadocianManager();

  $form['indexation_Lengadocian'] = array(
  '#type' => 'fieldset',
  '#title' => t('Index Lengadocian all'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['indexation_Lengadocian']['all'] = array(
    '#markup' => $lengadocianManager->processIndexation(),
    '#weight' => 1,
  );

  return $form;
} // indexation_lengadocian_all

*/ 

/*
  L E N G A D O C I A N
*/

function ajax_lengadocian_verb_autocomplete($form, &$form_state) {
//  drupal_set_message('ajax_lengadocian_verb_autocomplete');
  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $lengadocianManager = new ConjugationLengadocianManager();
  $drupalHTMLConverter = new ConverterHTML();
  $drupalLATEXConverter = new ConverterLATEX();
//  print_r($form_state);
  
  $verb   = (!empty($form_state['values']['leng_verb_search']['verb']))?$form_state['values']['leng_verb_search']['verb']: $lengadocianManager->getRandomVerb();

  $lengadocianManager->setVerb($verb);

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
    '#autocomplete_path' => 'conjoc/verb_autocomplete_lengadocian_callback',
  );

  $form['leng_verb_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  /*
    U S U A L S   V E R B S
  */

  $form['leng_verbs_usuals'] = array(
  '#type' => 'fieldset',
  '#title' => t('Usual verbs'),
  '#weight' => 2,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['leng_verbs_usuals']['info'] = array(
    '#markup' => $drupalHTMLConverter->convertArray($lengadocianManager->getUsualVerbs()),
    '#weight' => 1,
  );

  /*
    T O P 2 0   V E R B S
  */


  $form['leng_TOP20_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Top 20 verbs'),
  '#weight' => 3,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );
   
  $form['leng_TOP20_verbs']['selected'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => $lengadocianManager->getTop20(),
    //    '#default_value' => $category['TOP20_verbs']['selected'],
    '#description' => t('To be done.'),
  );  

  $form['leng_TOP20_verbs']['info'] = array(
    //    '#markup' => '<div>'. conjugador_displayTop20($verb) .'</div>',
  );

  $form['leng_TOP20_verbs']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit to be translated'),
  );

  /*
    S I N G L E   V E R B S
  */

  $form['leng_single_verbs'] = array(
  '#type' => 'fieldset',
  '#title' => t('Single verbs'),
  '#weight' => 4,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $form['leng_single_verbs']['info'] = array(
  '#markup' => $drupalHTMLConverter->convertArray($lengadocianManager->getSingleVerbs()),
  );

  /*
    O T H E R S   I N   M O D E L
  */

  $countOthers = 0;

  if (isset($form_state['values']['leng_verb_search']['verb']) 
  && ($countOthers = $lengadocianManager->getCountOthersInModel($form_state['values']['leng_verb_search']['verb'])) 
  && $countOthers > 0 
  && $countOthers <= variable_get("MAX_OTHERVERBS")){

    $form['leng_other_verbs_in_model'] = array(
      '#type' => 'fieldset',
      '#title' => t('Other verbs in model'),
      '#weight' => 5,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['leng_other_verbs_in_model']['selected'] = array(
      '#type' => 'select',
      '#title' => t('Selected'),
      '#options' => $lengadocianManager->getOthersInModel($verb),
      //    '#default_value' => $category['other_verbs_in_model']['selected'],
      '#description' => t('To be done.'),
    );  

    $form['leng_other_verbs_in_model']['info'] = array(
      //      '#markup' => '<div>'. conjugador_displayOthersInModel($verb) .'</div>',
    );

    $form['leng_other_verbs_in_model']['submit'] = array(
      '#weight' => 2,
      '#type' => 'submit',
      '#value' => t('Submit, to be changed'),
    );

  }

  /*
    V E R B   C O N J U G A T E D
  */

  $form['leng_verb_conjugated'] = array(
  '#type' => 'fieldset',
  '#title' => ($randomVerb)?t('Random verb conjugated '):t('Verb conjugated'),
  '#weight' => 7,
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );

  $conjugated = $lengadocianManager->conjugate();
  $fileNameToDownload = $drupalLATEXConverter->convertConjugation($conjugated);

  $form['leng_verb_conjugated']['downloadPDF'] = array(
    '#markup' => l( 
    t("ficha en format PDF «" . $verb . "»" . '<img width="32px" src="/sites/default/files/img/logopdf.png"></img>'), 
    $fileNameToDownload, 
    array(
    	'html' => TRUE,
    	'attributes' => array('target'=>'_blank'
    	)
    )
    ),
  );

  $form['leng_verb_conjugated']['conjugation'] = array(
    '#markup' => '<div>'. $drupalHTMLConverter->convertConjugation($conjugated) .'</div>',
  );
  

  return $form;
} // ajax_lengadocian_verb_autocomplete 

function ajax_lengadocian_verb_autocomplete_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_lengadocian_verb_autocomplete_callback($string = "") {
  $lengadocianManager = new ConjugationlengadocianManager();
  $lengadocianManager->getVerbAutoComplete($string);
}
