<?php
/**
 * \file      ConjugationManagerBase.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     abstract class that contains most of the code for all the managers of spectific dialects
 *
 * \details   the manager is the central class of the framework  
 */
abstract class ConjugationManagerBase implements iConjugationManager{
    protected $_baseTablename; /**< the prefix of the table name, there is one per dialect*/
    private $_dialect;
    private $_dialectCode;
    private $_localization;
    private $_comments;
    private $_libModel;
    private $_verbPrime;
    private $_verb;
    private $_model;
    private $_conjugations;
    private $_group;
    private $_seeAlso;
    private $_alias;
    private $_idVerb;
    private $_row;

    private $_dataProvider; /**< aggregates a data provider */

    /**
     * a some important constants lie here 
     */
    const LENGADOCIAN  = "lengadocian"; /**< occitan dialect*/
    const GASCON       = "gascon";  /**< occitan dialect*/
    const PROVENCAL    = "provencal";  /**< occitan dialect*/
    const VIVAROALPENC = "vivaro-alpenc";  /**< occitan dialect*/
    const AUVERNHAT    = "auvernhat";  /**< occitan dialect*/
    const LEMOSIN      = "lemosin";  /**< occitan dialect*/

    const LENGADOCIAN_CODE  = "lng";  /**< occitan dialect code*/
    const GASCON_CODE       = "gsc";  /**< occitan dialect code*/
    const PROVENCAL_CODE    = "prv";  /**< occitan dialect code*/
    const VIVAROALPENC_CODE = "alp";  /**< occitan dialect code*/
    const AUVERNHAT_CODE    = "auv";  /**< occitan dialect code*/
    const LEMOSIN_CODE      = "lem";  /**< occitan dialect code*/

    const MAX_OTHERVERBS = 50;   /**< don't load other verbs if there are more than 50*/

    /**
     * \brief a Ctor
     * \return the object
     */
    public function __construct(){
    } // __construct

    public function getDialect(){ /**< simple accessor */
        return $this->_dialect;
    }

    /**
     * \return a string the dialect code
     */
    public function getDialectCode(){
        return $this->_dialectCode;
    }

    /**
     * \brief gets a dialect code
     * \param $dialect a string to set the name of the tables in the database for this very dialect.
     * \sa iConjugationDataProvider
     */
    static public function getThisDialectCode($dialect){
        switch($dialect){
        case ConjugationManagerBase::LENGADOCIAN:
            return ConjugationManagerBase::LENGADOCIAN_CODE;
        case ConjugationManagerBase::GASCON:
            return ConjugationManagerBase::GASCON_CODE;
        case ConjugationManagerBase::PROVENCAL:
            return ConjugationManagerBase::PROVENCAL_CODE;
        case ConjugationManagerBase::VIVAROALPENC:
            return ConjugationManagerBase::VIVAROALPENC_CODE;
        case ConjugationManagerBase::AUVERNHAT:
            return ConjugationManagerBase::AUVERNHAT_CODE;
        case ConjugationManagerBase::LEMOSIN:
            return ConjugationManagerBase::LEMOSIN_CODE;
        }
    } // getThisDialectCode

    /**
       \param $dialect a string to set the name of the tables in the database for this very dialect.
       \sa iConjugationDataProvider
    */
    public function setDialect($dialect){
        $dialect = strtolower($dialect);
        $this->_dialect = $dialect;

        switch($dialect){
        case ConjugationManagerBase::LENGADOCIAN:
            $this->_dialectCode = ConjugationManagerBase::LENGADOCIAN_CODE;
            $this->_baseTablename = "sauzet";
            break;
        case ConjugationManagerBase::GASCON:
            $this->_dialectCode = ConjugationManagerBase::GASCON_CODE;
            $this->_baseTablename = "gascon";
            break;
        case ConjugationManagerBase::PROVENCAL:
            $this->_dialectCode = ConjugationManagerBase::PROVENCAL_CODE;
            $this->_baseTablename = "provencal";
            break;
        }
        if (! empty($this->_baseTablename)){
            $this->_dataProvider = new ConjugationDataProviderBootstrap($this->_baseTablename);
        }else{ 
            // should never be here
            $text = t(":@dialect: is not a supported dialect", array('@dialect' => $dialect));
            die($text);
        }
    }

    /**
       \brief a setter 
       \param $dialectCode a string to set the name of the tables in the database for this very dialect.
    */
    public function setDialectCode($dialectCode){
        $this->_dialectCode = $dialectCode;
    } // setDialectCode
  
    /**
       \brief a getter 
       \return the infinitve mood of the verb
    */
    public function getVerb(){
        return $this->_verb;
    } // getVerb

    /**
       \brief more than a setter the dataprovider gets all the information for the verb if the verb is not found the object is filled w/ null values  
       \param $verb at its infinitive mood
    */
    public function setVerb($verb){
        $this->_verb = $verb;
        $line  = $this->_dataProvider->getVerb($verb);

        if (empty($line)){
            $this->setVerbModel('');
            $this->_seeAlso = '';
            $this->_alias = '';
            $this->_idVerb = 0;
            $this->_row    = 0;

            $this->_localization = '';
            $this->_comments  = 'not yet implemented';
            $this->_libModel  = '';
            $this->_verbPrime = '';
            $this->_conjugations = '';

            return;
        } 

        $this->setVerbModel($line->nummodel);

        $this->_seeAlso = $line->see;
        $this->_alias   = $line->alias;
        $this->_idVerb  = $line->id;
        $this->_row     = $line->row;

        $modelObj  = $this->_dataProvider->getVerbModelObject($line->nummodel); 

        $this->_localization = 'c';
        $this->_comments  = 'not yet implemented';
        $this->_libModel  = empty($modelObj->label_conjugation)?"":$modelObj->label_conjugation;
        $this->_verbPrime = empty($modelObj->verb_prime)?"":$modelObj->verb_prime;
        $this->_conjugations = $modelObj->conjugations;
    } // setVerb
  
    /**
     * \param $model a string the model code
     */
    private function setVerbModel($model){
        $group = substr($model,0,1);

        $this->_group = $group;
        $this->_model = $model;
    }

    /**
     * \return a string the model code
     */
    public function getVerbModel(){
        return $this->_model;
    }

    /**
     * \brief a simple setter
     * \param $nummodel a string the mode code
     */
    public function getVerbModelObject($nummodel){
        return $this->_dataProvider->getVerbModelObject($nummodel);
    }

    public function getGroup(){ /**< a simple accessor */
        return $this->_group;
    }

    public function getSeeAlso(){ /**< a simple accessor */
        return $this->_seeAlso;
    }

    public function getAlias(){ /**< a simple accessor */
        return $this->_alias;
    }

    public function getVerbId(){ /**< a simple accessor */
        return $this->_idVerb;
    }

    public function getComments(){ /**< a simple accessor */
        return $this->_comments;
    }

    public function getLibModel(){ /**< a simple accessor */
        return $this->_libModel;
    }

    public function getLocalization(){ /**< a simple accessor */
        return 'C';
    }

    public function getConjugations(){ /**< a simple accessor */
        return $this->_conjugations;
    }
    /**
     * \brief returns a dictionary definition (maybe french) matching this infinitive
     * \param $infinitive  a string of the verb at the mood infinitive
     * \return a HTML string the dictionary definition 
     */
    public function getDictionaryDefinition($infinitive){
        return $this->_dataProvider->getDictionaryDefinition($infinitive);
    }

    public function getRow(){ /**< a simple accessor */
        return $this->_row;
    }
 
    public function getProvider(){ /**< \return the dataprovider aggregated */
        return $this->_dataProvider;
    }

    public function getTop20(){ /**< a simple accessor */
        return $this->_dataProvider->getTop20();
    } // getTop20

    /**
     * \param $verb a string the verb at the infinitive
     * \return a list of verbs in the same model
     */
    public function getOthersInModel($verb){ 
        return $this->_dataProvider->getOthersInModel($verb);
    } // getOthersInModel

    /**
     * \param $verb a string the verb at the infinitive
     * \return a counter
     */
    public function getCountOthersInModel($verb){
        return $this->_dataProvider->getCountOthersInModel($verb);
    } // getCountOthersInModel

    /**
     * \todo clean the drupal stuff
     * \return a list of verb single in their model
     */
    public function getSingleVerbs(){
        $arrRet = array();
        $singleVerbs = $this->_dataProvider->getSingleVerbs();
        $dialect = $this->getDialect();
        foreach ($singleVerbs as $verb){
            $arrRet[$verb] = "$dialect/verb_autocomplete/usuals/$verb";
        }
        return $arrRet;
    } // getSingleVerbs

    /**
     * \param $string a string some characters beginning an infinitive
     * \return a list of infinitives beginning w/ the string
     */
    public function getVerbAutoComplete($string){
        return drupal_json_output($this->_dataProvider->getVerbAutoComplete($string));
    } // getVerbAutoComplete

    /**
     * \param $string a string some characters beginning an infinitive
     * \return a list of infinitives beginning w/ the string
     */
    public function getIndexationAutoComplete($string){
        return drupal_json_output($this->_dataProvider->getIndexationAutoComplete($string));
    } // getIndexationAutoComplete

    /**
     * \param $conjugation a conjugation object
     * \return only the information needed for indexing the conjugation
     */
    public function getIndexationData($conjugation){
        return $this->_dataProvider->getIndexationData($conjugation);
    } // getIndexatioData

    
    /**
     * \return an infinitve at random
     */
    public function getRandomVerb(){
        return $this->_dataProvider->getRandomVerb();
    } // getRandomVerb()

    abstract public function getUsualVerbs(); /**< a simple accessor */
    abstract public function generateConjugation();  /**< a simple accessor */

    /**
     * \brief a placeholder function
     * \return the conjugation object
     */
    public function conjugate(){
        return $this->generateConjugation()->conjugate();
    }
  
    /**
     * \brief inserts an indexation data once for a conjugation
     * \details everytimes a verb is conjugated its data are inserted in the database. The POS data is encoded.
     */
    public function processIndexationOnce($arrVerb){
        $indexationConverter = new ConverterIndexation();
 
        $infinitive = $arrVerb['infinitive'];
        $this->setVerb($arrVerb['verb']);
        $row = $arrVerb['row'];
	
        $ary = $this->conjugate();
        $name = $ary['name'];

        $conjugations = $ary['conjugations'];
        $model = $ary['model'];
        $dialect = $indexationConverter->encodeDialect($ary['dialect']);
        // put POS default values 
        $aryPOS = array();
	
        //$aryPOS['person'] = 1;
        // II Gender 1 Masculine 2 Feminine 3 Neuter
        $aryPOS['gender'] = 0;
        // III Number 1 Singular 2 Plural
        //$aryPOS['number'] = 1;
        // IV Finiteness 1 Finite 2 Non-finite
        $aryPOS['finiteness'] = 0;
        // V Mood 1 Indicative 2 Subjunctive 3 Imperative 4 Conditional 5 Infinitive 6 Participle 7 Gerund 8 Supine
        // $aryPOS['mood'] = 1;
        // VI Tense 1 Present 2 Imperfect 3 Future 4 Past
        // $aryPOS['tense'] = 1;
        // VII Voice 1 Active 2 Passive
        $aryPOS['voice'] = 0;
        // VIII Status 1 Main 2 Auxiliary 3 Semi-auxiliary
        $aryPOS['status'] = 1;
	
        if ($model == '001' || $model == '002'){
            $aryPOS['status'] = 2;
        }
        if ($model == '003' || $model == '003 b' || $model == '004'){
            $aryPOS['status'] = 3;
        }

        // IX Aspect 1 Perfective 2 Imperfective
        $aryPOS['aspect'] = 0;
        // X Separability 1 Non-separable 2 Separable
        $aryPOS['separability'] = 0;
        // XI Reflexivity 1 Reflexive 2 Non-reflexive
        $aryPOS['reflexivity'] = 0;
        // XII Auxiliary 1 Have 2 Be
        $aryPOS['auxiliary'] = 0;
        // iterating in the conjugations, a record is created for each flexion

        for($i=ConjugationBase::IND_PRESENT; $i < ConjugationBase::LAST_NORMAL_TEMPS + 1; $i++){

            $conjugation = $conjugations[$i];
            switch($i){
            case ConjugationBase::IND_PRESENT : 
            case ConjugationBase::IND_IMPERFECT : 
            case ConjugationBase::IND_PRETERIT : 
            case ConjugationBase::IND_FUTURE :
                $mood = '1'; 
                break;
            case ConjugationBase::INFINITIVE  : $mood = '5'; break;
            case ConjugationBase::GERUND      : $mood = '7'; break;
            case ConjugationBase::PAST_PARTICIPLE  : $mood = '6'; break;
            case ConjugationBase::IMPERATIVE  : $mood = '3'; break;
            case ConjugationBase::SUBJ_PRESENT: 
            case ConjugationBase::SUBJ_IMPERFECT: 
                $mood = '2'; break;
            case ConjugationBase::CONDITIONAL : $mood = '4'; break;
            }
      	   
            $aryPOS['mood'] = $mood;
            $aryPOS['tense'] = $indexationConverter->encodeTense($i);
      	   
            if ($i == ConjugationBase::INFINITIVE || $i == ConjugationBase::GERUND){
                $conj = $conjugation[0];
                $aryPOS['person'] = 0;
                $aryPOS['number'] = 1;
                $pos = $indexationConverter->encodePOS($aryPOS);
                $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                $this->_dataProvider->insertIndexedVerb($fields);
            }else if ($i == ConjugationBase::PAST_PARTICIPLE){
                $conj = $conjugation[0];
                $aryPOS['person'] = 0;
                $aryPOS['number'] = 1;
                $aryPOS['gender'] = 1;
                $aryPOS['tense'] = 4;

                $pos = $indexationConverter->encodePOS($aryPOS);
                $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                $this->_dataProvider->insertIndexedVerb($fields);

                $conj = $conjugation[1];
                $aryPOS['person'] = 0;
                $aryPOS['number'] = 1;
                $aryPOS['gender'] = 2;

                $pos = $indexationConverter->encodePOS($aryPOS);
                $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                $this->_dataProvider->insertIndexedVerb($fields);

            }else if ($i == ConjugationBase::IMPERATIVE){
                for($j=0;$j < 6;$j++){
                    $conj = $conjugation[$j];
                    $person = ($j < 3)? $j+1:$j-2;
                    $aryPOS['person'] = $person;
                    $number = ($j < 3)? 1:2;
                    $aryPOS['number'] = $number;
                    $pos = $indexationConverter->encodePOS($aryPOS);
                    $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                    $this->_dataProvider->insertIndexedVerb($fields);
                } // for	     
            }else{   // OTHERS
                for($j=0;$j < 6;$j++){
                    $conj = $conjugation[$j];
                    $person = ($j < 3)? $j+1:$j-2;
                    $aryPOS['person'] = $person;
                    $number = ($j < 3)? 1:2;
                    $aryPOS['number'] = $number;
                    $pos = $indexationConverter->encodePOS($aryPOS);
                    $fields = array('verb' => $infinitive, 'row' => $row, 'dialect' => $dialect, 'nummodel' => $model, 'conjugation' => $conj, 'pos' => $pos);
                    $this->_dataProvider->insertIndexedVerb($fields);
                } // for	     
            }      	   
        } 
    } // processIndexationOnce
  
    /**
     * \brief launches the big indexation by increments DO NOT USE
     * \return a HTML string
     */
    public function processIndexation(){
        $allVerbs = $this->_dataProvider->getAllVerbsByIncrement();

        foreach($allVerbs as $arrVerb){
            processIndexationOnce($arrVerb);
        } // for
 
        return "<strong>done</strong>";
	
    } // processIndexation

    abstract public function getShortLabel(); /**< an abstract accessor */
    abstract public function getLongLabel(); /**< an abstract accessor */

    /**
     * a simple accessor
     */
    public function getVerbsModels(){ 
        return $this->_dataProvider->getVerbsModels();
    }

    /**
     * a simple accessor
     */
    public function getVerbsModelsMixed(){
        return $this->_dataProvider->getVerbsModelsMixed();
    }

} // class ConjugationManagerBase

?>