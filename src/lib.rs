#![allow(unused_doc_comment)]

extern crate itertools;
extern crate time;
extern crate toml;

#[macro_use]
extern crate serde_derive;

#[macro_use]
extern crate error_chain;

pub use types::Maps;
pub use types::errors;

#[macro_use]
pub mod load;
mod format;
mod types;
