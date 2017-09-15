use self::from_toml::{get_key, toml_to_vec, FromToml};
// use self::decode::{Settings};
use self::kmap_parser::KmapParser;

mod kmap_parser;
mod impl_load;
mod from_toml;
mod decode;
