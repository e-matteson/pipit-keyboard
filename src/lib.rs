#![allow(unused_doc_comment)]
#![feature(entry_or_default)]
#![feature(conservative_impl_trait)]
#![feature(string_retain)]
#![feature(match_default_bindings)]
#![feature(iterator_try_fold)]
#![feature(inclusive_range_syntax)]

extern crate cursive;
extern crate itertools;
extern crate natord;
extern crate ron;
extern crate serde;
extern crate serde_yaml;
extern crate svg;
extern crate time;
extern crate unicode_segmentation;

#[macro_use]
extern crate serde_derive;

#[macro_use]
extern crate failure;

#[macro_use]
extern crate lazy_static;

pub use types::{AllData, TutorData};
pub use types::errors;

#[macro_use]
mod types;
#[macro_use]
mod load;
mod format;
mod util;
pub mod tutor;
pub mod cheatsheet;
