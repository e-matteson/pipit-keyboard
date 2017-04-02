use std::collections::HashMap;

use key_types::*;

// macro from https://stackoverflow.com/questions/28392008/more-concise-hashmap-initialization/28392068#28392068

#[macro_export]
macro_rules! hashmap {
    ($( $key: expr => $val: expr ),*) => {{
        let mut map = ::std::collections::HashMap::new();
        $( map.insert($key, $val); )*
            map
    }}
}

#[macro_export]
// like vec!, but for initializing 2d vectors.
macro_rules! vec2 {
    ( $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x.to_vec());
            )*
                temp_vec
        }
    };
}

// #[derive(Debug)]
// pub struct Settings{
//     pub a: i64,
//     // pub h: HashMap<String, i64>,
//     pub h: HashMap<i64, i64>,
//     pub u: Vec<Vec<i64>>,
//     pub v: Vec<Vec<i64>>,
//     pub s: Vec<i64>,
// }

#[derive(Debug)]
pub struct  Settings<'a>{
    pub output_directory           : &'a str,
    pub normal_mode                : &'a str,
    pub onehand_mode               : &'a str,
    pub chord_delay                : i64,
    pub held_delay                 : i64,
    pub debounce_delay             : i64,
    pub stickymod_key              : &'a str,
    pub enable_audio_feedback      : bool,
    pub debug_messages             : i64,
    pub enable_unknown_deletion    : bool,
    pub collapse_unknown_deletions : bool,
    pub board_name                 : &'a str,
    pub has_battery                : bool,
    pub battery_level_pin          : i64,
    pub enable_rgb_led             : bool,
    pub enable_color_feedback      : bool,
    pub rgb_led_pins               : Vec<i64>,
    pub row_pins                   : Vec<i64>,
    pub column_pins                : Vec<i64>,
    pub kmap_format                : Vec<Vec<(i64, i64)>>,
    pub plains : HashMap<&'a str, (&'a str, &'a str)>,
    pub macros : HashMap<&'a str, Vec<(&'a str, &'a str)>>,
    pub special_functions : Vec<&'a str>,
    pub words : Vec<Vec<&'a str>>,
}
