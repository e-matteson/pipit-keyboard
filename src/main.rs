extern crate toml;
use toml::Value;

use std::collections::HashMap;
use std::fmt;

#[derive(Debug)]
enum OpType{
    Mode {useWords: bool},
    DefineInt,
    DefineString,
    IfdefValue,
    IfdefKey,
    Array1D,
    Array2D,
    Internal,
}

#[derive(Debug)]
enum OpVal{
    Str (String),
    Int (i64),
    Bool (bool),
    // Array {val: },
}

#[derive(Debug)]
enum OpReq{
    Optional,
    Required,
    Dependent{key:String, val:Option<OpVal>}
}

#[derive(Debug)]
struct OpDef{
    opType: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    auto: bool,
}

struct OpDefBuilder{
    opType: OpType,
    val: Option<OpVal>,
    default: Option<OpVal>,
    required: OpReq,
    auto: bool,
}

impl OpDefBuilder{
    fn new(opType: OpType) -> OpDefBuilder{
        OpDefBuilder{opType: opType,
                     val: None,
                     default: None,
                     required: OpReq::Required,
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
    fn finalize(self) -> OpDef{
        OpDef{opType: self.opType,
              val: self.val,
              default: self.default,
              required: self.required,
              auto: self.auto,}
    }

}

fn defineOptions() -> HashMap<String, OpDef> {
    /// Define all options here.
    let mut opDefMap: HashMap<String, OpDef> = HashMap::new();
    opDefMap.insert(
        "num_rows".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .auto(true)
            .finalize());
    opDefMap.insert(
        "num_cols".to_string(),
        OpDefBuilder::new(OpType::DefineInt)
            .default(OpVal::Int(3))
            .auto(false)
            .finalize());
    opDefMap.insert(
        "false_ifdef".to_string(),
        OpDefBuilder::new(OpType::IfdefKey)
            .default(OpVal::Bool(false))
            .required(OpReq::Optional)
            .finalize());
    opDefMap.insert(
        "mode_name".to_string(),
        OpDefBuilder::new(OpType::Mode{useWords: false})
            .required(OpReq::Required)
            .finalize());
    opDefMap
}

fn setOptions(map: &mut HashMap<String, OpDef>) {
    // TODO implement
    // also needs to take the data containing option values...
    for (name, op) in map.iter(){
        println!("{}", name);
        println!("{:?}", op);
    }
}

fn main() {
    // let value = "foo = 'bar'".parse::<Value>().unwrap();
    // println!(value);
    let value: OpVal = OpVal::Int(42);
    let t: OpType = OpType::Mode{useWords: true };
    println!("{:?}", value);
    println!("{:?}", t);
    let opDefMap = defineOptions();
    println!("{:#?}", opDefMap);
}
