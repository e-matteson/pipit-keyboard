#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

extern crate time;
extern crate toml;
extern crate itertools;

#[macro_use]
pub mod options;

// pub mod format;
// pub mod toml_convertor;

pub mod write;
pub mod parser;
pub mod switch_pos;
pub mod chord;
pub mod sequence;
pub mod words;
pub mod maps;
pub mod c_array;
pub mod compression;
