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
pub mod key_types;
pub mod words;
pub mod maps;
