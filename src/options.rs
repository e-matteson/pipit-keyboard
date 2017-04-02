use std::collections::HashMap;
use std::cmp::PartialOrd;
// use std::ops::{Index, IndexMut};

use toml::Value;
use key_types::SwitchPos;

use toml_convertor::*;

#[derive(Debug)]
pub struct OpDef {
    op_type: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    internal: bool,
}

impl OpDef{
    fn is_auto(&self) -> bool{
        self.required == OpReq::Auto
    }

    // fn set_val(&mut self){}
}

// impl PartiaLord for OpDef{
//     // Order on required, so ops with dependencies can be sorted to the end.
//     fn partial_cmp(&self, other: &OpDef) -> Option<Ordering> {
//         self.required.partial_cmp(&other.required)
//     }
// }

// impl PartialEq for OpDef {
//     fn eq(&self, other: &Person) -> bool {
//         self.height == other.height
//     }
// }

#[derive(Debug)]
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
#[derive(Eq)]
// TODO make OpVals unwrap()-able
pub enum OpVal {
    Str (String),
    Int (i64),
    Bool (bool),
    Vec (Vec<i64>),
    Vec2 (Vec<Vec<i64>>),
    VecKmap (Vec<Vec<SwitchPos>>),
}

impl OpVal{
    pub fn unwrap_int(&self) -> i64{
        match self{
            &OpVal::Int(x) => x,
            _ => panic!("Expected OpVal::Int"),
        }
    }
    pub fn unwrap_str(&self) -> &str{
        match self{
            &OpVal::Str(ref x) => x,
            _ => panic!("Expected OpVal::Str"),
        }
    }
    pub fn unwrap_bool(&self) -> bool{
        match self{
            &OpVal::Bool(x) => x,
            _ => panic!("Expected OpVal::Bool"),
        }
    }
    pub fn unwrap_vec(&self) -> &Vec<i64>{
        match self{
            &OpVal::Vec(ref x) => x,
            _ => panic!("Expected OpVal::Vec"),
        }
    }
    pub fn unwrap_vec2(&self) -> &Vec<Vec<i64>>{
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


#[derive(Debug)]
#[derive(PartialEq)]
pub enum OpReq {
    Required,
    Optional,

    // will be automatically generated, user should not supply it
    Auto,

    // Required only if key option has value val.
    // If val is None, required if option value is Some.
    Dependent {key:String, val:Option<OpVal>}
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

    fn val(mut self, val: OpVal) -> OpDefBuilder {
        self.val = Some(val);
        self
    }
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
pub struct Options (HashMap<String, OpDef>);

impl Options{
    pub fn get(&self, key: &str) -> &OpDef{
        match self.0.get(key){
            Some(opdef) => opdef,
            None => panic!(format!("option not found: {}", key)),
        }
    }

    pub fn get_mut(&mut self, key: &str) -> &mut OpDef{
        match self.0.get_mut(key){
            Some(opdef) => opdef,
            None => panic!(format!("option not found: {}", key)),
        }
    }

    fn set_val(&mut self, name: &str, val: OpVal){
        self.0.get_mut(name)
            .expect(&format!("option not found: {}", name))
            .val = Some(val);
    }

    pub fn get_val(&self, name: &str) -> &OpVal{
        let wrapped_val =  &self.0.get(name)
            .expect(&format!("option not found: {}", &name));

        match wrapped_val.val{
            Some(ref val) => val,
            _ => panic!(format!("value is None: {}", &name)),
        }
    }

    fn get_val_len(&self, name: &str) -> usize{
        // TODO implement for other vector-based variants?
        self.get_val(name).unwrap_vec().len()
    }

    pub fn new() -> Options{
        let mut options = Options(HashMap::new());
        options.initialize();
        options
    }

    pub fn load(&mut self, parsed_options: &Value) {
        self.from_parsed(parsed_options);
        self.check_requirements();
        self.set_immediate_auto_options();
    }

    fn initialize(&mut self) {
        /// Define all available options here.
        // let &mut Options(ref mut map) = self;

        self.0.insert(
            "row_pins".to_string(),
            OpDefBuilder::new(OpType::Array1D)
                .finalize());
        self.0.insert(
            "column_pins".to_string(),
            OpDefBuilder::new(OpType::Array1D)
                .finalize());
        self.0.insert(
            "rgb_led_pins".to_string(),
            OpDefBuilder::new(OpType::Array1D)
                .required(OpReq::Dependent {key: "enable_rgb_led".to_string(),
                                            val: Some(OpVal::Bool(true))})
                .finalize());
        self.0.insert(
            "kmap_format".to_string(),
            OpDefBuilder::new(OpType::ArrayKmap)
                .internal(true)
                .finalize());
        self.0.insert(
            "num_rows".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "num_cols".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "chord_delay".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .finalize());
        self.0.insert(
            "output_directory".to_string(),
            OpDefBuilder::new(OpType::DefineString)
                .internal(true)
                .finalize());
        self.0.insert(
            "stickymod_key".to_string(),
            OpDefBuilder::new(OpType::DefineString)
                .finalize());
        self.0.insert(
            "held_delay".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .finalize());
        self.0.insert(
            "debounce_delay".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .finalize());
        self.0.insert(
            "battery_level_pin".to_string(),
            OpDefBuilder::new(OpType::Uint8)
                .required(OpReq::Dependent {key: "has_battery".to_string(),
                                            val: Some(OpVal::Bool(true))})
                .finalize());
        self.0.insert(
            "has_battery".to_string(),
            OpDefBuilder::new(OpType::IfdefKey)
                .default(OpVal::Bool(false))
                .required(OpReq::Optional)
                .finalize());
        self.0.insert(
            "collapse_unknown_deletions".to_string(),
            OpDefBuilder::new(OpType::IfdefKey)
                .default(OpVal::Bool(false))
                .required(OpReq::Optional)
                .finalize());
        self.0.insert(
            "enable_unknown_deletion".to_string(),
            OpDefBuilder::new(OpType::IfdefKey)
                .default(OpVal::Bool(false))
                .required(OpReq::Optional)
                .finalize());
        self.0.insert(
            "enable_audio_feedback".to_string(),
            OpDefBuilder::new(OpType::IfdefKey)
                .default(OpVal::Bool(false))
                .required(OpReq::Optional)
                .finalize());
        self.0.insert(
            "enable_color_feedback".to_string(),
            OpDefBuilder::new(OpType::IfdefKey)
                .default(OpVal::Bool(false))
                .required(OpReq::Optional)
                .finalize());
        self.0.insert(
            "enable_rgb_led".to_string(),
            OpDefBuilder::new(OpType::IfdefKey)
                .default(OpVal::Bool(false))
                .required(OpReq::Optional)
                .finalize());
        self.0.insert(
            "board_name".to_string(),
            OpDefBuilder::new(OpType::IfdefValue)
                .finalize());
        self.0.insert(
            "debug_messages".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .finalize());
        self.0.insert(
            "normal_mode".to_string(),
            OpDefBuilder::new(OpType::Mode {use_words: true})
                .required(OpReq::Required)
                .finalize());
        self.0.insert(
            "onehand_mode".to_string(),
            OpDefBuilder::new(OpType::Mode {use_words: false})
                .required(OpReq::Required)
                .finalize());
        self.0.insert(
            "num_bytes_in_chord".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "num_matrix_positions".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "blank_mapping".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "shift_position".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "ctrl_position".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "alt_position".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
        self.0.insert(
            "gui_position".to_string(),
            OpDefBuilder::new(OpType::DefineInt)
                .required(OpReq::Auto)
                .finalize());
    }

    fn from_parsed( &mut self, parsed_options: &Value) {
        let parsed_map =
            if let &Value::Table(ref m) = parsed_options {m} else {
                panic!("Expected table");
            };

        for key in parsed_map.keys(){
            let op_def: &mut OpDef = self.0.get_mut(key)
                .expect(&format!("Unknown option: {}", key));

            match op_def.op_type {
                // match all integer value types
                OpType::DefineInt | OpType::Uint8 => {
                    op_def.val = Some(
                        match parsed_map[key]{
                            Value::Integer(x) => OpVal::Int(x),
                            _ => panic!("Expected integer"),
                        });
                },
                // match all string value types
                OpType::Mode {..}
                | OpType::DefineString
                    | OpType::IfdefValue => {
                        op_def.val = Some(
                            match parsed_map[key]{
                                Value::String(ref x) => OpVal::Str(x.to_owned()),
                                _ => panic!("Expected string"),
                            });
                    },
                // match all bool value types
                OpType::IfdefKey => {
                    op_def.val = Some(
                        match parsed_map[key]{
                            Value::Boolean(x) => OpVal::Bool(x),
                            _ => panic!("Expected boolean"),
                        });
                },
                // match 1d array value types
                OpType::Array1D => {
                    // println!("{:?}", parsed_map[key]);
                    op_def.val = Some(
                        match parsed_map[key]{
                            Value::Array(_) => {
                                OpVal::Vec(toml_to_vec1_int(&parsed_map[key]))
                            },
                            _ => panic!("Expected array value"),
                        });
                },
                // match 2d array value types
                OpType::Array2D => {
                    // println!("{:?}", parsed_map[key]);
                    op_def.val = Some(
                        match parsed_map[key]{
                            Value::Array(_) => OpVal::Vec2(
                                toml_to_vec2_int(&parsed_map[key])
                            ),
                            _ => panic!("Expected array value"),
                        });
                },
                // match kmap_format
                OpType::ArrayKmap => {
                    op_def.val = Some(
                        match parsed_map[key]{
                            Value::Array(_) => OpVal::VecKmap(
                                toml_to_kmap(&parsed_map[key])
                            ),
                            _ => panic!("Expected array value"),
                        });
                },
            }
        }
    }

    fn check_requirements(&self){
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
                    match (val, &self.0[key].val){
                        (&Some(ref expected), &Some(ref actual)) =>
                            if expected != actual {
                                continue
                            },
                        (&None, &None)
                            | (&Some(_), &None) =>
                            continue,
                        _ => (),
                    },
            }
            panic!("Missing required option: {}", name)
        }
    }

    fn set_immediate_auto_options(&mut self){
        /// Automatically generate the options that depend only on other options,
        ///  not outside information like layouts etc.

        // TODO write another function for chord-based autos
        self.set_val("blank_mapping" , OpVal::Int(0));

        let num_rows: i64 = self.get_val_len("row_pins") as i64;
        let num_cols: i64 = self.get_val_len("column_pins") as i64;
        let num_matrix_positions: i64 = num_rows * num_cols as i64;
        let num_bytes_in_chord: i64 = num_bits_to_bytes(num_matrix_positions);
        self.set_val("num_rows" , OpVal::Int(num_rows));
        self.set_val("num_cols" , OpVal::Int(num_cols));
        self.set_val("num_matrix_positions", OpVal::Int(num_matrix_positions));
        self.set_val("num_bytes_in_chord", OpVal::Int(num_bytes_in_chord));
    }

}

fn num_bits_to_bytes(num_bits: i64) -> i64{
    (num_bits as f64 / 8.0).ceil() as i64
}
