extern crate toml;

use std::collections::HashMap;
use toml::Value;

enum OptionType{
    Mode {useWords: bool},
    DefineInt,
    DefineString,
    IfdefValue,
    IfdefKey,
    Array1D,
    Array2D {dim2: u32},
    Internal,
}

enum OptionVal{
    Str (Option<String>),
    Int (Option<i64>),
    // Array {val: },
}


enum OptionReq{
    Optional,
    Required,
    Dependent{key:String, val:String}
}

struct OptionDef{
    optype: OptionType,
    auto: bool,
    required: OptionReq,
    // default:
}

fn makeOpDefMap() -> HashMap<String, OptionDef> {
    let mut opDefMap: HashMap<String, OptionDef> = HashMap::new();
    opDefMap.insert("num_rows".to_string(),
                    OptionDef{auto: true,
                              required: OptionReq::Required,
                              optype: OptionType::DefineInt});
    opDefMap.insert("num_cols".to_string(),
                    OptionDef{auto: true,
                              required: OptionReq::Required,
                              optype: OptionType::DefineInt});
    opDefMap.insert("false_ifdef".to_string(),
                    OptionDef{auto: true,
                              required: OptionReq::Required,
                              optype: OptionType::IfdefKey});
    opDefMap.insert("mode_name".to_string(),
                    OptionDef{auto: true,
                              required: OptionReq::Required,
                              optype: OptionType::Mode{useWords: true}});
    opDefMap
}

fn makeOpValMap() -> HashMap<String, OptionVal>{
    let mut opValMap: HashMap<String, OptionVal> = HashMap::new();
    opValMap.insert("num_rows".to_string(), OptionVal::Int(Some(42)));
    opValMap.insert("num_cols".to_string(), OptionVal::Int(None));
    opValMap.insert("mode_name".to_string(), OptionVal::Str(Some("normal".to_string())));
    opValMap.insert("false_ifdef".to_string(), OptionVal::Str(None));
    opValMap
}

fn main() {
    let value = "foo = 'bar'".parse::<Value>().unwrap();
    println!(value);

    // let op = OptionVal::Int(42);
    let opDefMap = makeOpDefMap();
    let opValMap = makeOpValMap();

    for (name, op) in opValMap.iter(){
        let def: &OptionDef = opDefMap.get(name).expect("Unknown type!");

        println!("{}", name);
        match op{
            &OptionVal::Str(Some(ref val)) => println!("str val: {}", val),
            &OptionVal::Str(None) => println!("str NONE"),
            &OptionVal::Int(ref foo) => {
                if foo.is_some(){
                    println!("{}", foo.unwrap());
                }
                else {
                    println!("int NONE");
                }
            },
            // _ => println!("failed")
        }
    }
}

// fn old() {
//     let mut opt: OptionType = OptionType::IfdefValue{val: "debug_messages".to_string()};
//     let mut opt2: OptionType = OptionType::DefineInt{val: 3};
//     let mut opt3: OptionType = OptionType::Mode{useWords: false, val: "normal".to_string()};
//     opt3.val = "insert";
//     match opt3{
//         OptionType::DefineInt{val: val} => println!("{}", val),
//         OptionType::IfdefValue{val: val} => println!("{}", val),
//         OptionType::Mode{val: val, ..} => println!("{}", val),
//         _ => println!("unknown"),
//     }

//     // let mut map: HashMap<&str, i32> = HashMap::new();
//     // map.insert("a", 1);
//     // map.insert("b", 2);
//     // for key in map.keys(){
//     //     println!("{}", key);
//     // }
//     // let val: i32 = map["a"];
//     // println!("{}", val );
// }
