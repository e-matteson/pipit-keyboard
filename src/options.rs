
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
    ArrayKmap,
}

#[derive(Debug)]
pub struct SwitchPos{
    row: i64,
    col: i64,
}

#[derive(Debug)]
pub enum OpVal{
    Str (String),
    Int (i64),
    Bool (bool),
    Vec (Vec<i64>),
    Vec2 (Vec<Vec<i64>>),
    VecKmap (Vec<Vec<SwitchPos>>),
}

#[derive(Debug)]
pub enum OpReq{
    Required,
    Optional,
    // will be automatically generated, user should not supply it
    Auto,
    // Required only if key option has value val.
    // If val is None, required if option value is Some.
    Dependent{key:String, val:Option<OpVal>}
}

#[derive(Debug)]
pub struct OpDef{
    op_type: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    internal: bool,
}

struct OpDefBuilder{
    op_type: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    internal: bool,
}

impl OpDefBuilder{
    fn new(op_type: OpType) -> OpDefBuilder{
        OpDefBuilder{op_type: op_type,
                     val: None,
                     default: None,
                     required: OpReq::Required,
                     internal: false,
        }
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
        }
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
        "test_2d".to_string(),
        OpDefBuilder::new(OpType::Array2D)
            .finalize());
    op_def_map.insert(
        "kmap_format".to_string(),
        OpDefBuilder::new(OpType::ArrayKmap)
            .internal(true)
            .finalize());
    op_def_map.insert(
        "num_rows".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .required(OpReq::Auto)
            .finalize());
    op_def_map.insert(
        "num_cols".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .required(OpReq::Auto)
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

fn toml_to_vec<T, F>(toml_array: &Value, f: F) -> Vec<T> where F: Fn(&Value)->T{
    match toml_array{
        &Value::Array(ref vector) => {
            vector.iter()
                .map(f)
                .collect()
        },
        _ => panic!("Expected array value"),
    }
}

fn toml_to_int(toml_value: &Value) -> i64 {
    match toml_value{
        &Value::Integer(i) => i,
        _ => panic!("Expected integer value"),
    }
}

fn toml_to_keypos(toml_array: &Value) -> SwitchPos {
    let int_vec = toml_to_vec(toml_array, toml_to_int);
    if int_vec.len() != 2{
        panic!("Expected vector of length 2");
    }
    SwitchPos{row: int_vec[0], col: int_vec[1]}
}


fn toml_to_kmap(toml_array: &Value) -> Vec<Vec<SwitchPos>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1, |d2| toml_to_keypos(d2))
    )
}


fn toml_to_vec2(toml_array: &Value) -> Vec<Vec<i64>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1, toml_to_int)
    )
}

fn toml_to_vec3(toml_array: &Value) -> Vec<Vec<Vec<i64>>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1,
                                 |d2| toml_to_vec(d2, toml_to_int))
    )
}

pub fn set_options(def_map: &mut HashMap<String, OpDef>, parsed_options: &Value) {
    let parsed_map =
        if let &Value::Table(ref m) = parsed_options{m} else{
            panic!("Expected table");
        };

    for key in parsed_map.keys(){
        let op_def: &mut OpDef = def_map.get_mut(key)
            .expect(&format!("Unknown option: {}", key));

        match op_def.op_type{
            // match all integer value types
            OpType::DefineInt => {
                op_def.val = Some(
                    match parsed_map[key]{
                        Value::Integer(x) => OpVal::Int(x),
                        _ => panic!("Expected integer"),
                    });
            },
            // match all string value types
            OpType::Mode{..}
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
                println!("{:?}", parsed_map[key]);
                op_def.val = Some(
                    match parsed_map[key]{
                        Value::Array(_) => {
                            OpVal::Vec(toml_to_vec(&parsed_map[key], toml_to_int))
                        },
                        _ => panic!("Expected array value"),
                    });
            },
            // match 2d array value types
            OpType::Array2D => {
                println!("{:?}", parsed_map[key]);
                op_def.val = Some(
                    match parsed_map[key]{
                        Value::Array(_) => OpVal::Vec2(
                            toml_to_vec2(&parsed_map[key])
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

pub fn get_parsed_settings() -> Value {
    let mut f: File = File::open("settings.toml").expect("failed to open settings file!");
    let mut buffer = String::new();
    f.read_to_string(&mut buffer).expect("failed to read settings file!");
    let parsed = buffer.parse::<Value>().expect("failed to parse settings file!");
    parsed
}
