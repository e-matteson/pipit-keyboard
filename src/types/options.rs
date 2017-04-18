use std::collections::BTreeMap;

use types::{Chord, SwitchPos, Maps};

fn  get_option_definitions<'a>() -> Vec<(&'a str, OpDef)> {
    /// Define new options here!

    vec![
        ("default_mode",
         OpDefBuilder::new(OpType::Mode {use_words: true})
         .required(OpReq::Required)
         .internal(true)
         .finalize()),

        // ("onehand_mode",
        //  OpDefBuilder::new(OpType::Mode {use_words: false})
        //  .required(OpReq::Required)
        //  .internal(true)
        //  .finalize()),

        ("krita_mode",
         OpDefBuilder::new(OpType::Mode {use_words: false})
         .required(OpReq::Required)
         .internal(true)
         .finalize()),

        ("row_pins",
         OpDefBuilder::new(OpType::Array1D) .finalize()),

        ("column_pins",
         OpDefBuilder::new(OpType::Array1D).finalize()),

        ("rgb_led_pins",
         OpDefBuilder::new(OpType::Array1D)
         .required(OpReq::Dependent
                   {key: "enable_rgb_led".to_owned(),
                    val: Some(OpVal::Bool(true))})
         .finalize()),

        ("num_rgb_led_pins",
         OpDefBuilder::new(OpType::DefineInt)
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
         .internal(true)
         .finalize()),

        ("stickymod_key",
         OpDefBuilder::new(OpType::DefineString)
         .finalize()),

        ("held_delay",
         OpDefBuilder::new(OpType::DefineInt)
         .finalize()),

        ("debounce_delay",
         OpDefBuilder::new(OpType::DefineInt)
         .finalize()),

        ("battery_level_pin",
         OpDefBuilder::new(OpType::Uint8)
         .required(OpReq::Dependent
                   {key: "has_battery".to_string(),
                    val: Some(OpVal::Bool(true))})
         .finalize()),

        ("has_battery",
         OpDefBuilder::new(OpType::IfdefKey)
         .default(OpVal::Bool(false))
         .required(OpReq::Optional)
         .finalize()),

        ("collapse_unknown_deletions",
         OpDefBuilder::new(OpType::IfdefKey)
         .default(OpVal::Bool(false))
         .required(OpReq::Optional)
         .finalize()),

        ("enable_unknown_deletion",
         OpDefBuilder::new(OpType::IfdefKey)
         .default(OpVal::Bool(false))
         .required(OpReq::Optional)
         .finalize()),

        ("enable_audio_feedback",
         OpDefBuilder::new(OpType::IfdefKey)
         .default(OpVal::Bool(false))
         .required(OpReq::Optional)
         .finalize()),

        ("enable_color_feedback",
         OpDefBuilder::new(OpType::IfdefKey)
         .default(OpVal::Bool(false))
         .required(OpReq::Optional)
         .finalize()),

        ("enable_rgb_led",
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

        ("shift_position",
         OpDefBuilder::new(OpType::Array1D)
         .required(OpReq::Auto)
         .finalize()),

        ("ctrl_position",
         OpDefBuilder::new(OpType::Array1D)
         .required(OpReq::Auto)
         .finalize()),

        ("alt_position",
         OpDefBuilder::new(OpType::Array1D)
         .required(OpReq::Auto)
         .finalize()),

        ("gui_position",
         OpDefBuilder::new(OpType::Array1D)
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

    #[allow(unused_variables)]
    pub fn is_mode(&self) -> bool {
        match self.op_type {
            OpType::Mode{use_words} => true,
            _ => false,
        }
    }

    #[allow(unused_variables)]
    pub fn is_mode_with_words(&self) -> bool {
        match self.op_type {
            OpType::Mode{use_words} => use_words,
            _ => false,
        }
    }

    pub fn get_val(&self) -> &OpVal{
        match self.val{
            Some(ref val) => val,
            _ => panic!(format!("value is None")),
        }
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
        match self.0.get(key) {
            Some(opdef) => opdef,
            None => panic!(format!("option not found: {}", key)),
        }
    }

    pub fn get_mut(&mut self, key: &str) -> &mut OpDef {
        match self.0.get_mut(key) {
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
        let op_def =  &self.0.get(name)
            .expect(&format!("option not found: {}", &name));
        op_def.get_val()
    }

    fn get_val_len(&self, name: &str) -> usize{
        // TODO implement for other vector-based variants?
        self.get_val(name).unwrap_vec().len()
    }

    pub fn get_modes(&self) -> Vec<String> {
        self.0.iter()
            .filter(|&(_, val)| val.is_mode())
            .map(|(key, _)| key.to_string())
            .collect()
    }

    pub fn get_modes_with_words(&self) -> Vec<String> {
        self.0.iter()
            .filter(|&(_, val)| val.is_mode_with_words())
            .map(|(key, _)| key.to_string())
            .collect()
    }

    pub fn verify_requirements(&self){
        /// Verify that whether option dependencies are satisfied.
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

    pub fn update_after_loading_chords(&mut self, maps: &Maps){
        /// Automatically generate the options that depend on chords

        let mods = vec![("modifierkey_shift", "shift_position"),
                        ("modifierkey_ctrl",  "ctrl_position"),
                        ("modifierkey_alt",   "alt_position"),
                        ("modifierkey_gui",   "gui_position")];

        for (op_name, mod_name) in mods {
            let mut positions: Vec<i64> = Vec::new();
            for mode in &maps.options.get_modes() {
                positions.push(maps.get_modifier_position(op_name, mode) as i64);
            }
            self.set_val(mod_name, OpVal::Vec(positions))
        }
    }

    pub fn update_after_loading_toml(&mut self) {
        /// Automatically generate the options that depend only on other options,
        ///  not outside information like layouts etc.

        self.set_val("blank_mapping" , OpVal::Int(0));

        let num_rows: i64 = self.get_val_len("row_pins") as i64;
        let num_columns: i64 = self.get_val_len("column_pins") as i64;
        let num_matrix_positions: i64 = num_rows * num_columns as i64;
        let num_bytes_in_chord: i64 = round_up_to_num_bytes(num_matrix_positions);

        let mut num_rgb_led_pins: i64 = 0;
        if self.get_val("enable_rgb_led").unwrap_bool() {
            num_rgb_led_pins = self.get_val_len("rgb_led_pins") as i64;
        }

        self.set_val("num_rows" , OpVal::Int(num_rows));
        self.set_val("num_columns" , OpVal::Int(num_columns));
        self.set_val("num_matrix_positions", OpVal::Int(num_matrix_positions));
        self.set_val("num_bytes_in_chord", OpVal::Int(num_bytes_in_chord));
        self.set_val("num_rgb_led_pins" , OpVal::Int(num_rgb_led_pins));

        Chord::set_num_bytes(self.get_val("num_bytes_in_chord").unwrap_int());
    }

    pub fn get_non_internal(&self) -> BTreeMap<String, OpDef> {
        let map: BTreeMap<_,_> = self.0.clone().into_iter()
            .filter(|&(_, ref val)| !val.is_internal())
            .collect();
        map
    }

}

fn round_up_to_num_bytes(num_bits: i64) -> i64{
    (num_bits as f64 / 8.0).ceil() as i64
}
