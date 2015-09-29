# conjoc
Class library for conjugating some occitan dialects (lengadocian, provençal, gascon). Expandable, ready for leveraging, this class library is used in a Drupal module but can be ported to any environment.

As of this writing the production version is not completely ported in object style, as you can see in the Drupal module especially « conjoc_webform.inc ».

The Drupal module uses the two styles, for exemple the lengadocian implementation is in the old style, the gascon one uses the object.
In the conjoc_webform.inc file, the ajax_gascon_verb_autocomplete function instanciates the ConjugationGasconManager and uses its methods.
ex :   
  $gasconManager = new ConjugationGasconManager();
  $drupalHTMLConverter = new ConverterHTML();
...
  // to inject the HTML code produced by the conjugation
  // line 748
    '#markup' => $drupalHTMLConverter->convertArray($gasconManager->getUsualVerbs()),
...
An instance of ConjugationGasconManager is created so a HTMLConverter specially designed for Drupal. The converter acts as a filter giving a HTML code ready for a drupal website.
