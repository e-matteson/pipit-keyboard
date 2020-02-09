//! This module handles the details of loading the configuration data from from
//! files. Any structs that are only ever needed during loading are defined
//! within this module. Other structs that are defined elsewhere may have extra
//! impl's in this module, adding methods that are only needed during the
//! loading phase (eg. `KmapPath`).
//!
//! One exception to these conventions is that some structs defined outside this
//! module derive `Deserialize`. Although the `Deserialize` functionality feels
//! like it should be contained in this module, we need to add the derive
//! attributes to the struct definition itself.

pub use self::all_data_builder::load_all_data;
use self::settings::Settings;

mod all_data_builder;
mod parse_kmap;
mod settings;
