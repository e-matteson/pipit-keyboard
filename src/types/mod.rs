pub use self::key_press::KeyPress;
pub use self::c_code::{CCode, ToC};
pub use self::miscellaneous::{COption, KmapFormat, KmapInfo, KmapPath,
                              ModeInfo, ModeName, Name, Pin, SeqType,
                              Sequence, SwitchPos};
pub use self::chord::Chord;
pub use self::words::{AnagramNum, Word, WordBuilder, WordConfig};
pub use self::all_data::AllData;
pub use self::checker::Checker;

pub use self::validate::Validate;
// pub use self::errors::*;
// pub use self::other_error::*;

#[macro_use]
mod validate;

pub mod errors;
mod key_press;
mod c_code;
mod miscellaneous;
mod chord;
mod words;
mod all_data;
mod checker;
