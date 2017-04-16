use load::toml_conversion::*;
use load::load::load_settings;
use toml::Value;

use types::{Maps, Options, OpDef, OpType, OpVal};

// Implement loading options

impl Maps {

    pub fn load(path: &str) -> Maps {
        // TODO load all layouts
        let mut maps = Maps::new();

        // loads stuff into both options and maps
        let mut options = load_settings(path, &mut maps);

        options.update_after_loading_chords(&maps);
        maps.options = options;

        maps
    }

}


impl Options {

    pub fn load(parsed_options: &Value) -> Options{
        let mut options = Options::new();
        options.from_toml(parsed_options);
        options.verify_requirements();
        options.update_after_loading_toml();
        options
    }

    fn from_toml( &mut self, parsed_options: &Value) {
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

}
