
use std::collections::HashMap;


use options::*;
use maps::*;
// use words::*;
use self::toml_convertor::*;
use self::options::*;
use key_types::*;

use self::settings_struct::*;
use settings::SETTINGS;

pub struct Loader{
    // For temporarily holding the loaded values
    pub options: Options,
    pub macros: HashMap<String, Sequence>,
    pub plain_keys: HashMap<String, Sequence>,
    pub special_list: Vec<String>,
    pub word_list: Vec<Vec<String>>,
}

impl Loader{
    pub fn load() -> Loader{
        let mut loader = Loader{
            options: Options::new(),
            macros: HashMap::new(),
            plain_keys: HashMap::new(),
            special_list: Vec::new(),
            word_list: Vec::new(),
        };

        SETTINGS.with(|x| loader.load_helper(&x));
        loader
    }

    fn load_helper(&mut self, settings: &Settings){
        println!("{:?}", settings);
    }
}
