<?php
//--*-PHP-*--
/**
 * @file
 * conjoc_gascon_verbForm.inc
 *
*/
 

/**
   G A S C O N
   G A S C O N
   G A S C O N
 */

function ajax_gascon_verb_autocomplete($form, &$form_state) {
//  drupal_set_message('ajax_gascon_verb_autocomplete');
  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $gasconManager = new ConjugationGasconManager();
  $drupalHTMLConverter = new ConverterHTML();
  $drupalLATEXConverter = new ConverterLATEX();
 
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
    '#value' => t('Vai querre'),
    '#submit' => array('ajax_gascon_verb_autocomplete_submit'),    
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

  $form['gasc_verb_conjugated']['conjugation'] = array(  
    '#markup' => '<div>'. $drupalHTMLConverter->convertConjugation($conjugated) .'</div>',
  );
  
  $form['exportation'] = array(
  '#type' => 'fieldset',
  '#title' => t('Exportation'),
  '#weight' => 6,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  );

  $fileNamePDFToDownload = $drupalLATEXConverter->convertConjugation($conjugated);

  $form['exportation']['downloadPDF'] = array(
    '#markup' => l( 
    t("ficha en format PDF «" . $verb . "»" . '<img width="32px" src="/sites/default/files/img/logopdf.png"></img>'), 
    $fileNamePDFToDownload, 
    array(
    	'html' => TRUE,
    	'attributes' => array('target'=>'_blank'
    	)
    )
    ),
  );


/*
  $form['exportation']['downloadTEI'] = array(
	'#type' => 'image_button',
    	'#name' => 'TEI card',
    	'#value' => 'TEI card',
    	'#src' => '/sites/default/files/img/logoxml.png',    	 
        '#description' => t('The conjugation in Text Encoding Initiative (TEI).'),
        '#submit' => array('gascon_TEI_submit'),
  );
*/

  return $form;
} // ajax_gascon_verb_autocomplete 



function ajax_gascon_verb_autocomplete_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

function gascon_TEI_submit($form, &$form_state){

  $drupalTEIConverter = new ConverterTEI();
  $conjugated = $form_state['values']['exportation']['downloadTEI']['conjugation']; 
  $drupalTEIConverter->convertConjugation($conjugated);  

} // gascon_TEI_submit
/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_gascon_verb_autocomplete_callback($string = "") {
  $gasconManager = new ConjugationGasconManager();
  $gasconManager->getVerbAutoComplete($string);
}
