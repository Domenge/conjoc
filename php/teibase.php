<?php
/*
  noun TYPE,GENDER,NUMBER,CASE
  verb PERSON,GENDER,NUMBER,FINITUDE,MOOD,TENSE,VOICE,STATUS,ASPECT,SEPARABILITY,REFLEXIVITY,AUXILLIARY
  adjective DEGREE,GENDER,NUMBER,CASE
  pronoun PERSON,GENDER,NUMBER,CASE,CATEGORY,PRONOUN TYPE,DETERMINER TYPE, PERSONNAL/REFLEXIVE TYPE,INTERROGATIVE/RELATIVE TYPE, POLITENESS, STRENGTH
  adverb DEGREE,TYPE,POLARITY,WH-TYPE
  adposition TYPE
  article TYPE,GENDER,NUMBER,CASE
  conjunction TYPE
  numerals TYPE,GENDER,NUMBER,CASE,FUNCTION
  residual TYPE,GENDER,NUMBER
  unique TYPE
*/

function noun($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"Commun"},{"value":2,"label":"Propre"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    case 'CASE' :
        echo '[{"value":1,"label":"Nominatif"},{"value":2,"label":"Génitif"},{"value":3,"label":"Datif"},{"value":4,"label":"Accusatif"},{"value":5,"label":"Vocatif"}]';
        break;
    } // switch
} // noun

function verb($verb){
    switch(strtoupper($attribute)){
    case 'PERSON' :
        echo '[{"value":1,"label":"Première"},{"value":2,"label":"Deuxième"},{"value":3,"label":"Troisième"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    case 'FINITUDE' :
        echo '[{"value":1,"label":"Fini"},{"value":2,"label":"Non fini"}]';
        break;
    case 'MOOD' :
        echo '[{"value":1,"label":"Indicatif"},{"value":2,"label":"Subjonctif"},{"value":3,"label":"Impératif"},{"value":4,"label":"Conditionnel"},{"value":5,"label":"Infinitif"},{"value":6,"label":"Participe"},{"value":7,"label":"Gérondif"}]';
        break;
    case 'TENSE' :
        echo '[{"value":1,"label":"Présent"},{"value":2,"label":"Imparfait"},{"value":3,"label":"Futur"},{"value":4,"label":"Passé"}]';
        break;
    case 'VOICE' :
        echo '[{"value":1,"label":"Active"},{"value":2,"label":"Passive"}]';
        break;
    case 'STATUS' :
        echo '[{"value":1,"label":"Principal"},{"value":2,"label":"Auxilliaire"}]';
        break;
    case 'ASPECT' :
        echo '[{"value":1,"label":"Perfectif"},{"value":2,"label":"Imperfectif"}]';
        break;
    case 'SEPARABILITY' :
        echo '[{"value":1,"label":"Non séparable"},{"value":2,"label":"Séparable"}]';
        break;
    case 'REFLEXIVITY' :
        echo '[{"value":1,"label":"Réfléchi"},{"value":2,"label":"Non réfléchi"}]';
        break;
    case 'AUXILLIARY' :
        echo '[{"value":1,"label":"Avoir"},{"value":2,"label":"Être"}]';
        break;
    } // switch
} // verb

function adjective($attribute){
    // adjective
    switch(strtoupper($attribute)){
    case 'DEGREE' :
        echo '[{"value":1,"label":"Positif"},{"value":2,"label":"Comparatif"},{"value":3,"label":"Superlatif"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    case 'CASE' :
        echo '[{"value":1,"label":"Nominatif"},{"value":2,"label":"Génitif"},{"value":3,"label":"Datif"},{"value":4,"label":"Accusatif"},{"value":5,"label":"Vocatif"}]';
        break;
    }
} // adjective

function pronoun($attribute){
    switch(strtoupper($attribute)){
    case 'PERSON' :
        echo '[{"value":1,"label":"Positif"},{"value":2,"label":"Comparatif"},{"value":3,"label":"Superlatif"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    case 'CASE' :
        echo '[{"value":1,"label":"Nominatif"},{"value":2,"label":"Génitif"},{"value":3,"label":"Datif"},{"value":4,"label":"Accusatif"},{"value":5,"label":"Vocatif"}]';
        break;
    case 'CATEGORY' :
        echo '[{"value":1,"label":"Pronom"},{"value":2,"label":"Déterminant"},{"value":3,"label":"Les deux"}]';
        break;
    case 'PRONOUN TYPE' :
        echo '[{"value":1,"label":"Démonstratif"},{"value":2,"label":"Indéfini"},{"value":3,"label":"Possessif"},{"value":4,"label":"Interrogatif/Relatif"},{"value":5,"label":"Personnel/Réfléchi"}]';
        break;
    case 'DETERMINER TYPE' :
        echo '[{"value":1,"label":"Démonstratif"},{"value":2,"label":"Indéfini"},{"value":3,"label":"Possessif"},{"value":4,"label":"Interrogatif/Relatif"},{"value":5,"label":"Partitif"}]';
        break;
    case 'PERSONNAL/REFLEXIVE TYPE' :
        echo '[{"value":1,"label":"Personnel"},{"value":2,"label":"Réfléchi"},{"value":3,"label":"Réciproque"}]';
        break;
    case 'INTERROGATIVE/RELATIVE TYPE' :
        echo '[{"value":1,"label":"Interrogatif"},{"value":2,"label":"Relatif"},{"value":3,"label":"Exclamatif"}]';
        break;
    case 'POLITENESS' :
        echo '[{"value":1,"label":"Poli"},{"value":2,"label":"Familier"}]';
        break;
    case 'STRENGTH' :
        echo '[{"value":1,"label":"Faible"},{"value":2,"label":"Fort"}]';
        break;
    } // switch
} // pronoun

function adverb($attribute){
    switch(strtoupper($attribute)){
    case 'DEGREE' :
        echo '[{"value":1,"label":"Positif"},{"value":2,"label":"Comparatif"},{"value":3,"label":"Superlatif"}]';
        break;
    case 'TYPE' :
        echo '[{"value":1,"label":"Général"},{"value":2,"label":"Degré"}]';
        break;
    case 'POLARITY' :
        echo '[{"value":1,"label":"Wh-Type"},{"value":2,"label":"Non wh-type"}]';
        break;
    case 'WH-TYPE' :
        echo '[{"value":1,"label":"Interrogatif"},{"value":2,"label":"Relatif"},{"value":3,"label":"Exclamatif"}]';
        break;
    } // switch
} // adverb

function adposition($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"Préposition"}]';
        break;
    } // switch
} // adposition

function article($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"Général"},{"value":2,"label":"Degré"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    case 'CASE' :
        echo '[{"value":1,"label":"Nominatif"},{"value":2,"label":"Génitif"},{"value":3,"label":"Datif"},{"value":4,"label":"Accusatif"}]';
        break;
    }
} // article

function conjunction($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"De coordination"},{"value":2,"label":"De subordination"}]';
        break;
    }
} // conjunction

function numerals($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"Cardinal"},{"value":2,"label":"Ordinal"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    case 'CASE' :
        echo '[{"value":1,"label":"Nominatif"},{"value":2,"label":"Génitif"},{"value":3,"label":"Datif"},{"value":4,"label":"Accusatif"}]';
        break;     
    case 'FUNCTION' :
        echo '[{"value":1,"label":"Pronom"},{"value":2,"label":"Déterminant"},{"value":3,"label":"Adjectif"}]';
        break;
    } // switch
} // numerals

function residual($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"Mot étranger"},{"value":2,"label":"Formule"},{"value":3,"label":"Symbôle"},{"value":4,"label":"Acronyme"},{"value":5,"label":"Abréviation"},{"value":6,"label":"Non classifié"}]';
        break;
    case 'GENDER' :
        echo '[{"value":1,"label":"Masculin"},{"value":2,"label":"Féminin"},{"value":3,"label":"Neutre"}]';
        break;
    case 'NUMBER' :
        echo '[{"value":1,"label":"Singulier"},{"value":2,"label":"Pluriel"}]';
        break;
    }  // switch
} // residual

function unique($attribute){
    switch(strtoupper($attribute)){
    case 'TYPE' :
        echo '[{"value":1,"label":"Particule négative"},{"value":2,"label":"Seconde particule négative"}]';
        break;
    } // switch
} // unique


/*
  M A I N
*/
if (isset($_GET['catgram']) && isset($_GET['attribute'])){
    $catgram=$_GET['catgram'];
    $attribute=$_GET['attribute'];

    switch(strtoupper($catgram)){
    case 'N' :
        // noun
        noun($attribute);
        break;
    case 'V' :
        //verb
        verb($attribute);
        break;
    case 'AJ' :
        // adjective
        adjective($attribute);
        break;
    case 'PD' :
        // pronoun determinant
        pronoun($attribute);
        break;
    case 'AV' :
        // ADVERB
        adverb($attribute);
        break;
    case 'AP' :
        // ADPOSITION
        adposition($attribute);
        break;
    case 'AT' :
        // ARTICLE
        article($attribute);
        break;
    case 'C' :
        // CONJUNCTION
        conjunction($attribute);
        break;
    case 'NU' :
        // NUMERALS
        numerals($attribute);
        break;
    case 'U' :
        //UNIQUE
        unique($attribute);
        break;
    case 'R' :
        // RESIDUAL
        residual($attribute);
        break;
    default :
        print "CATGRAM unknown";
        return;
    } // switch
} // isset 
?>

