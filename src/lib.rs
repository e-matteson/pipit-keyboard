#![allow(unused_doc_comment)]
#![feature(entry_or_default)]
#![feature(conservative_impl_trait)]
#![feature(string_retain)]
#![feature(match_default_bindings)]

extern crate cursive;
extern crate itertools;
extern crate natord;
extern crate svg;
extern crate time;
extern crate toml;
extern crate unicode_segmentation;

#[macro_use]
extern crate serde_derive;

#[macro_use]
extern crate failure;

#[macro_use]
extern crate lazy_static;

pub use types::AllData;
pub use types::errors;

#[macro_use]
mod types;
#[macro_use]
mod load;
mod format;
mod util;
pub mod tutor;
pub mod cheatsheet;
