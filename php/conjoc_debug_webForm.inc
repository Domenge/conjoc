<?php
//--*-PHP-*--
/**
 * @file
 * conjoc_debug_verbForm.inc
 *
*/
 

/**
	D E B U G
	D E B U G
	D E B U G
 */

function ajax_debug_verb_autocomplete($form, &$form_state) {

  $form['#tree'] = TRUE;

  $lengadocianManager   = new ConjugationLengadocianManager();
  $drupalHTMLConverter  = new ConverterHTML();
  $drupalLATEXConverter = new ConverterLATEX();

  $randomVerb = empty($form_state['values']['verb_search']['verb']);
  
  $verb   = (!empty($form_state['values']['verb_search']['verb']))?
  	$form_state['values']['verb_search']['verb']:
  	$lengadocianManager->getRandomVerb();
  
  /*
    V E R B   S E A R C H
  */

  $form['verb_search'] = array(
  	'#type' => 'fieldset',
  	'#title' => t('Verb search'),
  	'#weight' => 2,
  	'#collapsible' => FALSE,
  );

  $form['verb_search']['verb'] = array(
  	'#weight' => 1,
  	'#type' => 'textfield',
  	'#default_value' => $verb,

  	'#title' => t('Choose a verb'),
  	// The autocomplete path is provided in hook_menu in ajax_example.module.
  	'#autocomplete_path' => 'conjoc/verb_autocomplete_debug_callback',
  );

  $form['verb_search']['submit'] = array(
    '#weight' => 2,
    '#type' => 'submit',
    '#value' => t('Debug submit'),
    '#submit' => array('search_submit'),    
  );


  /*
    V E R B   C O N J U G A T E D
  */

  $lengadocianManager->setVerb($verb);

  $conjugated = $lengadocianManager->conjugate();
  $fileNameToDownload = $drupalLATEXConverter->convertConjugation($conjugated);


  $form['debug_verb_conjugated'] = array(
  	'#type' => 'fieldset',
  	'#title' => ($randomVerb)?t('Random verb conjugated '):t('Verb conjugated'),
  	'#weight' => 7,
  	'#collapsible' => TRUE,
  	'#collapsed' => FALSE,
  );

  $form['debug_verb_conjugated']['conjugation'] = array(
  	'#markup' => '<div>'. $drupalHTMLConverter->convertConjugation($conjugated) .'</div>',
  );

  /*
    E X P O R T A T I O N
  */
   
  $form['exportation'] = array(
	'#type' => 'fieldset',
  	'#title' => t('Exportation of the verb conjugation'),
  	'#weight' => 2,
  	'#collapsible' => TRUE,
  	'#collapsed' => TRUE,
  );

  $form['exportation']['submit_TEI'] = array(
	'#type' => 'image_button',
    	'#name' => 'TEI card',
    	'#value' => 'TEI card',
    	'#executes_submit_callback' => FALSE,
    	'#src' => '/sites/default/files/img/logoxml.png',    	 
        '#description' => t('The conjugation in Text Encoding Initiative (TEI).'),
        '#submit' => array('debug_TEI_submit'),
  );
 
  return $form;
} // ajax_debug_verb_autocomplete 

/**
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_debug_verb_autocomplete_callback($string = "") {
  $manager = new ConjugationlengadocianManager();
  $manager->getVerbAutoComplete($string);
}


function debug_TEI_submit($form, &$form_state){
//  dpm($form_state);

  $verb =  $form_state['values']['verb_search']['verb'];
  drupal_set_message("debug_TEI_submit [$verb]");

  $manager = new ConjugationlengadocianManager();
  $manager->setVerb($verb);	
  $drupalTEIConverter = new ConverterTEI();
  $drupalTEIConverter->convertConjugation($manager->conjugate());  
} // debug_TEI_submit

function search_submit($form, &$form_state){
  dpm($form_state);
  $verb =  $form_state['values']['verb_search']['verb'];
  $op = $form_state['values']['op'];
  drupal_set_message("debug_search_submit [$op]");
//  $form_state['rebuild'] = TRUE;  

} // debug_search_submit

