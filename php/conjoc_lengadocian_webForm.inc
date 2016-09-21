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
*/
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

 

/*
Indexation
*/

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


function indexation_searchform($form, &$form_state) {
  $form['#tree'] = TRUE;
  $conjugation = '';
  if (!empty($form_state['values'])){
     $values =  $form_state['values'];
     $search = $values['conjugation_search'];
     $conjugation = !empty($search['conjugation'])?$search['conjugation']:'';
  }

  /*
    C O N J U G A T I O N  S E A R C H
  */
  $form['conjugation_search'] = array(
  '#type' => 'fieldset',
  '#title' => t('Conjugation search'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['conjugation_search']['conjugation'] = array(
    '#weight' => 1,
    '#type' => 'textfield',
    '#default_value' => $conjugation,

    '#title' => t('Choose a conjugation'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'conjoc/verb_autocomplete_indexation_callback',
  );

  $form['conjugation_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('verb_autocomplete_indexation_submit'),
  );

  if (!empty($conjugation)){
     $form['conjugation_result'] = array(
     				 '#type' => 'fieldset',
     				 '#title' => t('Conjugation result'),
     				 '#weight' => 3,
     				 '#collapsible' => TRUE,
     				 '#collapsed' => FALSE,
     );
     $converter = new ConverterHTML();
     $manager = new ConjugationLengadocianManager();
     $form['conjugation_result']['info'] = array(
     					 '#weight' => 1,
  					 '#markup' => $converter->convertIndexedData($manager->getIndexationData($conjugation)),
					 );
  }

  return $form;
} // indexation_lengadocian_all


/*
  L E N G A D O C I A N
*/

function ajax_lengadocian_verb_autocomplete($form, &$form_state) {
//  drupal_set_message('ajax_lengadocian_verb_autocomplete');
  $form['#tree'] = TRUE;
  $action = (!empty($form_state['values']['action']))?$form_state['values']['action']:'';

  $lengadocianManager   = new ConjugationLengadocianManager();
  $converterHTML  = new ConverterHTML();
  $converterLATEX = new ConverterLATEX();
  
  $verb   = (!empty($form_state['values']['verb_search']['verb']))?
  	$form_state['values']['verb_search']['verb']:
  	$lengadocianManager->getRandomVerb();

  $lengadocianManager->setVerb($verb);

  $randomVerb = empty($form_state['values']['verb_search']['verb']);

  /*
    V E R B   S E A R C H
  */
  $form['verb_search'] = array(
  '#type' => 'fieldset',
  '#title' => t('Verb search'),
  '#weight' => 1,
  '#collapsible' => FALSE,
  );

  $form['verb_search']['verb'] = array(
    '#weight' => 1,
    '#type' => 'textfield',
    '#default_value' => $verb,

    '#title' => t('Choose a verb'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'conjoc/verb_autocomplete_lengadocian_callback',
  );

  $form['verb_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#executes_submit_callback' => FALSE,
    '#submit' => array('ajax_lengadocian_verb_autocomplete_submit'),
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
    '#markup' => $converterHTML->convertArray($lengadocianManager->getUsualVerbs()),
    '#weight' => 1,
  );

  /*
    T O P 2 0   V E R B S
  */

/*
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
    '#options' => $lengadocianManager->getTop20(),
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
*/

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
  '#markup' => $converterHTML->convertArray($lengadocianManager->getSingleVerbs()),
  );

  /*
    O T H E R S   I N   M O D E L
  */

  $countOthers = 0;

  if (isset($form_state['values']['verb_search']['verb']) 
  && ($countOthers = $lengadocianManager->getCountOthersInModel($form_state['values']['verb_search']['verb'])) 
  && $countOthers > 0 
  && $countOthers <= variable_get("MAX_OTHERVERBS")){

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
      '#options' => $lengadocianManager->getOthersInModel($verb),
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

  $conjugated = $lengadocianManager->conjugate();
  // If there's an error
  if (! empty($conjugated)){
      $fileNameToDownload = $converterLATEX->convertConjugation($conjugated);

     $form['verb_conjugated']['conjugation'] = array(
     '#markup' => '<div>'. $converterHTML->convertConjugation($conjugated) .'</div>',
     );
  
     $form['exportation'] = array(
  	'#type' => 'fieldset',
  	'#title' => t('Exportation of the verb conjugation'),
  	'#weight' => 4,
  	'#collapsible' => TRUE,
  	'#collapsed' => TRUE,
     );

     $form['exportation']['downloadPDF'] = array(
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
   }else{ // if
     $form['verb_conjugated']['conjugation'] = array(
        '#markup' => '<div>' . t("Error") . '</div>',
     );   	  
   }
/*
  $form['exportation']['submit_TEI'] = array(
	'#type' => 'image_button',
    	'#name' => 'TEI card',
    	'#value' => 'TEI card',
    	'#src' => '/sites/default/files/img/logoxml.png',    	 
        '#description' => t('The conjugation in Text Encoding Initiative (TEI).'),
        '#submit' => array('lengadocian_TEI_submit'),
  );
*/
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

function lengadocian_TEI_submit($form, &$form_state){

  $verb =  $form_state['values']['verb_search']['verb'];
  $manager = new ConjugationlengadocianManager();
  $manager->setVerb($verb);	
  $drupalTEIConverter = new ConverterTEI();
  $drupalTEIConverter->convertConjugation($manager->conjugate());  

} // lengadocian_TEI_submit

function conjoc_form_submit($form, &$form_state){
	drupal_set_message('conjoc_form_submit');
} // lengadocian_TEI_submit

/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function verb_autocomplete_indexation_callback($string = "") {
  $manager = new ConjugationlengadocianManager();
  $manager->getIndexationAutoComplete($string);
}

function verb_autocomplete_indexation_submit($form, &$form_state){
  $form_state['rebuild'] = TRUE;
}

function process_URL_arguments($content = NULL, $arg1 = NULL, $arg2 = NULL) {
  $o = "$content";
  
  if (!empty($arg1)) {
    $mode = strtolower($arg1);
    $content = strtolower($content);

    $manager = new ConjugationLengadocianManager();

    switch($mode){
	case 'json':
	     $converter = new ConverterJSON();
	     $o = $converter->convertIndexedData($manager->getIndexationData($content)); 
	     print $o;
	     exit();
	     break;
	case 'html':
	     $converter = new ConverterHTML();
	     $o = $converter->convertIndexedData($manager->getIndexationData($content)); 
	     break;
	case 'xml':
	     $converter = new ConverterXML();
	     $o = $converter->convertIndexedData($manager->getIndexationData($content)); 
	     print $o;
	     exit();
	     break;
	case 'csv':
	     $converter = new ConverterCSV();
	     $o = $converter->convertIndexedData($manager->getIndexationData($content));
	     print $o;
	     exit();
	     break;
	default :
	     $o = "unknown mode  $content";		     
    }
  } // if

  return $o;
}

/**
 * Page callback for use with most of the menu entries.
 *
 * The arguments it receives determine what it outputs.
 *
 * @param string $content
 *   The base content to output.
 * @param string $arg1
 *   First additional argument from the path used to access the menu
 * @param string $arg2
 *   Second additional argument.
 */
function _lengadocian_menu_page($content = NULL, $arg1 = NULL, $arg2 = NULL) {

  if (!empty($content)) {
    $form_state = array();

    $args = func_get_args();
    $form_state['build_info']['args'] = $args;
    $form_state['values']['verb_search']['verb'] = $content;
    $form_state['values']['action'] = 'force';
    return drupal_build_form('ajax_lengadocian_verb_autocomplete', $form_state);
  }

  return drupal_set_message(t('Conjoc content is void.'), 'error');
}
