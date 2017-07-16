use std::collections::BTreeMap;

use types::{Chord, SwitchPos};
use types::errors::*;

const DEFAULT_OUTPUT_DIRECTORY: &str = "pipit-firmware/";

fn  get_option_definitions<'a>() -> Vec<(&'a str, OpDef)> {
    /// Define new options here!

    vec![
        ("row_pins",
         OpDefBuilder::new(OpType::Array1D) .finalize()),

        ("column_pins",
         OpDefBuilder::new(OpType::Array1D).finalize()),

        ("rgb_led_pins",
         OpDefBuilder::new(OpType::Array1D)
         .required(OpReq::Optional)
         .finalize()),

        ("num_rgb_led_pins",
         OpDefBuilder::new(OpType::DefineInt)
         .required(OpReq::Auto)
         .finalize()),

        ("enable_rgb_led",
         OpDefBuilder::new(OpType::IfdefKey)
         .required(OpReq::Auto)
         .finalize()),

        ("kmap_format",
         OpDefBuilder::new(OpType::ArrayKmap)
         .internal(true)
         .finalize()),

        ("num_rows",
         OpDefBuilder::new(OpType::DefineInt)
         .required(OpReq::Auto)
         .finalize()),

        ("num_columns",
         OpDefBuilder::new(OpType::DefineInt)
         .required(OpReq::Auto)
         .finalize()),

        ("chord_delay",
         OpDefBuilder::new(OpType::DefineInt)
         .finalize()),

        ("output_directory",
         OpDefBuilder::new(OpType::DefineString)
         .required(OpReq::Optional)
         .default(OpVal::Str(DEFAULT_OUTPUT_DIRECTORY.to_owned()))
         .internal(true)
         .finalize()),

        ("held_delay",
         OpDefBuilder::new(OpType::DefineInt)
         .finalize()),

        ("debounce_delay",
         OpDefBuilder::new(OpType::DefineInt)
         .finalize()),

        ("battery_level_pin",
         OpDefBuilder::new(OpType::Uint8)
         .required(OpReq::Optional)
         .finalize()),

        ("has_battery",
         OpDefBuilder::new(OpType::IfdefKey)
         .required(OpReq::Auto)
         .finalize()),

        // ("enable_audio_typing_feedback",
        //  OpDefBuilder::new(OpType::IfdefKey)
        //  .default(OpVal::Bool(false))
        //  .required(OpReq::Optional)
        //  .finalize()),

        ("enable_led_typing_feedback",
         OpDefBuilder::new(OpType::IfdefKey)
         .default(OpVal::Bool(false))
         .required(OpReq::Optional)
         .finalize()),

        ("board_name",
         OpDefBuilder::new(OpType::IfdefValue)
         .finalize()),

        ("debug_messages",
         OpDefBuilder::new(OpType::DefineInt)
         .finalize()),

        ("num_bytes_in_chord",
         OpDefBuilder::new(OpType::DefineInt)
         .required(OpReq::Auto)
         .finalize()),

        ("num_matrix_positions",
         OpDefBuilder::new(OpType::DefineInt)
         .required(OpReq::Auto)
         .finalize()),

        ("blank_mapping",
         OpDefBuilder::new(OpType::DefineInt)
         .required(OpReq::Auto)
         .finalize()),
    ]
}



#[derive(Debug)]
#[derive(Clone)]
pub struct OpDef {
    pub op_type: OpType,
    pub val: Option<OpVal>,
    pub default: Option<OpVal>,
    pub required: OpReq,
    pub internal: bool,
}

impl OpDef{
    // fn is_auto(&self) -> bool{
    //     self.required == OpReq::Auto
    // }

    pub fn is_mode(&self) -> bool {
        match self.op_type {
            OpType::Mode{..} => true,
            _ => false,
        }
    }

    pub fn is_mode_with_words(&self) -> bool {
        match self.op_type {
            OpType::Mode{use_words} => use_words,
            _ => false,
        }
    }

    pub fn get_val(&self) -> &OpVal{
        self.val.as_ref().expect(&format!("value is None"))
    }

    pub fn is_set(&self) -> bool {
        self.val.is_some()
    }

    fn is_internal(&self) -> bool {
        self.internal
    }

}


#[derive(Debug)]
#[derive(Clone)]
pub enum OpType {
    // TODO how to handle internal options? just with boolean flag, and abusing a
    //  similar variant?
    Mode {use_words: bool},
    DefineInt,
    DefineString,
    IfdefValue,
    IfdefKey, // should val store boolean or key?
    Uint8,
    Array1D,
    Array2D,
    ArrayKmap,
}

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Clone)]
pub enum OpReq {
    Required,
    Optional,

    // will be automatically generated, user should not supply it
    Auto,

    // Required only if key option has value val.
    // If val is None, required if option value is Some.
    Dependent {key:String, val:Option<OpVal>}
}


#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Clone)]
// TODO let Vecs hold any OpVal recursively?
pub enum OpVal {
    Str (String),
    StrVec (Vec<String>),
    Int32 (i32),
    Uint8 (u8),
    Bool (bool),
    Vec (Vec<u8>),
    Vec2 (Vec<Vec<u8>>),
    VecKmap (Vec<Vec<SwitchPos>>),
}

impl OpVal{
    pub fn unwrap_int32(&self) -> i32{
        match self{
            &OpVal::Int32(x) => x,
            _ => panic!("Expected OpVal::Int32"),
        }
    }
    pub fn unwrap_uint8(&self) -> u8{
        match self{
            &OpVal::Uint8(x) => x,
            _ => panic!("Expected OpVal::Uint8"),
        }
    }
    pub fn unwrap_str(&self) -> &str{
        match self{
            &OpVal::Str(ref x) => x,
            _ => panic!("Expected OpVal::Str"),
        }
    }
    pub fn unwrap_strvec(&self) -> &Vec<String>{
        match self{
            &OpVal::StrVec(ref x) => x,
            _ => panic!("Expected OpVal::StrVec"),
        }
    }
    pub fn unwrap_bool(&self) -> bool{
        match self{
            &OpVal::Bool(x) => x,
            _ => panic!("Expected OpVal::Bool"),
        }
    }
    pub fn unwrap_vec(&self) -> &Vec<u8>{
        match self{
            &OpVal::Vec(ref x) => x,
            _ => panic!("Expected OpVal::Vec"),
        }
    }
    pub fn unwrap_vec2(&self) -> &Vec<Vec<u8>>{
        match self{
            &OpVal::Vec2(ref x) => x,
            _ => panic!("Expected OpVal::Vec2"),
        }
    }
    pub fn unwrap_vec_kmap(&self) -> &Vec<Vec<SwitchPos>>{
        match self{
            &OpVal::VecKmap(ref x) => x,
            _ => panic!("Expected OpVal::VecKmap"),
        }
    }
}


struct OpDefBuilder {
    op_type: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    internal: bool,
}

impl OpDefBuilder {
    fn new(op_type: OpType) -> OpDefBuilder {
        OpDefBuilder {op_type: op_type,
                      val: None,
                      default: None,
                      required: OpReq::Required,
                      internal: false,
        }
    }

    // fn val(mut self, val: OpVal) -> OpDefBuilder {
    //     self.val = Some(val);
    //     self
    // }
    fn default(mut self, default: OpVal) -> OpDefBuilder {
        self.default = Some(default);
        self
    }
    fn required(mut self, required: OpReq) -> OpDefBuilder {
        self.required = required;
        self
    }
    fn internal(mut self, internal: bool) -> OpDefBuilder {
        self.internal = internal;
        self
    }
    fn finalize(self) -> OpDef {
        OpDef {op_type: self.op_type,
               val: self.val,
               default: self.default,
               required: self.required,
               internal: self.internal,
        }
    }
}

#[derive(Debug)]
pub struct Options (pub BTreeMap<String, OpDef>);

impl Options {

    pub fn new() -> Options {
        let mut options = Options(BTreeMap::new());
        for (key, val) in get_option_definitions() {
            options.0.insert(key.to_owned(), val);
        }
        options
    }

    pub fn get(&self, key: &str) -> &OpDef {
        self.0.get(key).expect(&format!("option not found: {}", key))
    }

    pub fn get_mut(&mut self, key: &str) -> Result<&mut OpDef> {
        self.0
            .get_mut(key)
            .ok_or(ErrorKind::UnexpectedKey(key.into()).into())
        // {
        //     Some(opdef) => Ok(opdef),
        //     None => Err(),
        // }
    }

    fn set_val(&mut self, name: &str, val: OpVal){
        self.0.get_mut(name)
            .expect(&format!("option not found: {}", name))
            .val = Some(val);
    }

    pub fn get_val(&self, name: &str) -> &OpVal{
        let op_def =  &self.0.get(name)
            .expect(&format!("option not found: {}", &name));
        op_def.get_val()
    }

    fn get_val_len(&self, name: &str) -> usize{
        // TODO implement for other vector-based variants?
        self.get_val(name).unwrap_vec().len() as usize
    }

    pub fn verify_requirements(&self) -> Result<()>{
        /// Verify that option dependencies are satisfied.
        for (name, op) in self.0.iter(){
            if let Some(_) = op.val{
                // The option was provided in the settings file.
                continue
            }

            match &op.required {
                &OpReq::Auto => continue,
                &OpReq::Optional => continue,
                &OpReq::Required => (),
                &OpReq::Dependent{ref key, ref val} =>
                // TODO clean this up?
                    match (val, &self.0[key].val){
                        (&Some(ref expected), &Some(ref actual)) =>
                            if expected != actual {
                                continue
                            },
                        (&None, &None) | (&Some(_), &None) =>
                            continue,
                        _ => (),
                    },
            }
            bail!(
                ErrorKind::MissingValue(
                    "required option key".into(),
                    Some(name.to_string())
                )
            );
        }
        Ok(())
    }

    pub fn set_auto(&mut self)  {
        /// Generate the OpReq::Auto options that depend only on other options

        let num_rows = self.get_val_len("row_pins");
        let num_columns = self.get_val_len("column_pins");
        let num_matrix_positions = num_rows * num_columns;
        let num_bytes_in_chord = round_up_to_num_bytes(num_matrix_positions);
        let has_battery = self.get("battery_level_pin").is_set();

        let mut num_rgb_led_pins = 0;
        let mut enable_rgb_led = false;
        if self.get("rgb_led_pins").is_set() {
            num_rgb_led_pins = self.get_val_len("rgb_led_pins");
            enable_rgb_led = true;
        }


        self.set_val("num_rows" , OpVal::Int32(num_rows as i32));
        self.set_val("num_columns" , OpVal::Int32(num_columns as i32));
        self.set_val("num_matrix_positions", OpVal::Int32(num_matrix_positions as i32));
        self.set_val("num_bytes_in_chord", OpVal::Int32(num_bytes_in_chord as i32));
        self.set_val("num_rgb_led_pins", OpVal::Int32(num_rgb_led_pins as i32));
        self.set_val("enable_rgb_led", OpVal::Bool(enable_rgb_led));
        self.set_val("has_battery", OpVal::Bool(has_battery));
        self.set_val("blank_mapping", OpVal::Int32(0));

        Chord::set_num_bytes(self.get_val("num_bytes_in_chord").unwrap_int32());
        // Ok(())
    }

    pub fn get_formattable_options(&self) -> BTreeMap<String, OpDef> {
        let map: BTreeMap<_,_> = self.0.clone().into_iter()
            .filter(|&(_, ref val)| !val.is_internal() && val.is_set())
            .collect();
        map
    }

}

fn round_up_to_num_bytes(num_bits: usize) -> usize{
    (num_bits as f64 / 8.0).ceil() as usize
}
