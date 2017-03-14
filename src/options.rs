
use toml::Value;

use std::collections::HashMap;
use std::io::prelude::*;
use std::fs::File;

#[derive(Debug)]
pub enum OpType{
    // TODO how to handle internal options? just with boolean flag, and abusing a
    //  similar variant?
    Mode {use_words: bool},
    DefineInt,
    DefineString,
    IfdefValue,
    IfdefKey, // should val store boolean or key?
    Array1D,
    Array2D,
    Array3D,
}

#[derive(Debug)]
pub enum OpVal{
    Str (String),
    Int (i64),
    Bool (bool),
    Vec (Vec<i64>),
}

#[derive(Debug)]
pub enum OpReq{
    Optional,
    Required,
    Dependent{key:String, val:Option<OpVal>}
}

#[derive(Debug)]
pub struct OpDef{
    op_type: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    internal: bool,
    auto: bool,
}

struct OpDefBuilder{
    op_type: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    internal: bool,
    auto: bool,
}

impl OpDefBuilder{
    fn new(op_type: OpType) -> OpDefBuilder{
        OpDefBuilder{op_type: op_type,
                     val: None,
                     default: None,
                     required: OpReq::Required,
                     internal: false,
                     auto: false,}
    }

    fn val(mut self, val: OpVal) -> OpDefBuilder{
        self.val = Some(val);
        self
    }
    fn default(mut self, default: OpVal) -> OpDefBuilder{
        self.default = Some(default);
        self
    }
    fn required(mut self, required: OpReq) -> OpDefBuilder{
        self.required = required;
        self
    }
    fn auto(mut self, auto: bool) -> OpDefBuilder{
        self.auto = auto;
        self
    }
    fn internal(mut self, internal: bool) -> OpDefBuilder{
        self.internal = internal;
        self
    }
    fn finalize(self) -> OpDef{
        OpDef{op_type: self.op_type,
              val: self.val,
              default: self.default,
              required: self.required,
              internal: self.internal,
              auto: self.auto,}
    }

}

pub fn define_options() -> HashMap<String, OpDef> {
    /// Define all available options here.
    let mut op_def_map: HashMap<String, OpDef> = HashMap::new();
    op_def_map.insert(
        "row_pins".to_string(),
        OpDefBuilder::new(OpType::Array1D)
            .finalize());
    op_def_map.insert(
        "num_rows".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .auto(true)
            .finalize());
    op_def_map.insert(
        "num_cols".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .auto(true)
            .finalize());
    op_def_map.insert(
        "chord_delay".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .finalize());
    op_def_map.insert(
        "has_battery".to_string(),
        OpDefBuilder::new(OpType::IfdefKey)
            .default(OpVal::Bool(false))
            .required(OpReq::Optional)
            .finalize());
    op_def_map.insert(
        "board_name".to_string(),
        OpDefBuilder::new(OpType::IfdefValue)
            .finalize());
    op_def_map.insert(
        "battery_level_pin".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .required(OpReq::Dependent{key: "has_battery".to_string(),
                                       val: Some(OpVal::Bool(true))})
            .finalize());
    op_def_map.insert(
        "normal_mode".to_string(),
        OpDefBuilder::new(OpType::Mode{use_words: true})
            .required(OpReq::Required)
            .finalize());
    op_def_map.insert(
        "onehand_mode".to_string(),
        OpDefBuilder::new(OpType::Mode{use_words: false})
            .required(OpReq::Required)
            .finalize());
    op_def_map
}

fn toml_to_vec(x: &Vec<Value>) -> Vec<i64> {
    /// Convert a parsed toml vector of Integer values into a a vector of i64s
    let mut out: Vec<i64> = Vec::new();
    for entry in x{
        match entry{
            &Value::Integer(i) => out.push(i),
            _ => panic!("Expected integer"),
        }
    }
    out
}

pub fn set_options(map: &mut HashMap<String, OpDef>, parsed_options: &Value) {
    match parsed_options{
        &Value::Table(ref t) =>
            for key in t.keys(){
                let op_def: &mut OpDef = map.get_mut(key)
                    .expect(&format!("Unknown option: {}", key));

                // TODO match on toml::Value variants instead?
                match op_def.op_type{
                    // match all integer value types
                    OpType::DefineInt => {
                        op_def.val = Some(match t[key]{
                            Value::Integer(x) => OpVal::Int(x),
                            _ => panic!("Expected integer"),
                        });
                    },
                    // match all string value types
                    OpType::Mode{..}
                    | OpType::DefineString
                        | OpType::IfdefValue => {
                            op_def.val = Some(match t[key]{
                                Value::String(ref x) => OpVal::Str(x.to_owned()),
                                _ => panic!("Expected string"),
                            });
                        },
                    // match all bool value types
                    OpType::IfdefKey => {
                        op_def.val = Some(match t[key]{
                            Value::Boolean(x) => OpVal::Bool(x),
                            _ => panic!("Expected boolean"),
                        });
                    },

                    // match 1d array value types
                    OpType::Array1D => {
                        op_def.val = Some(match t[key]{
                            Value::Array(ref x) => OpVal::Vec(toml_to_vec(&x)),
                            _ => panic!("Expected 1d array"),
                        });
                    },

                    // TODO how to handle >1D arrays neatly?

                    _ => println!("Unknown option type"),
                }
            },
        _ => panic!("Expected table"),
    }
    println!("{:?}", map);
}

pub fn get_parsed_settings() -> Value {
    let mut f: File = File::open("settings.toml").expect("failed to open settings file!");
    let mut buffer = String::new();
    f.read_to_string(&mut buffer).expect("failed to read settings file!");
    let parsed = buffer.parse::<Value>().expect("failed to parse settings file!");
    parsed
}
