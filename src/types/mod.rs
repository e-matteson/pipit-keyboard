pub use self::key_press::{KeyPress};
pub use self::c_code::{CCode, ToC};
pub use self::miscellaneous::{SwitchPos, SeqType, KmapPath, KmapInfo, ModeName,
                              ModeInfo, Name, Sequence};
pub use self::chord::Chord;
pub use self::words::{Word, WordInfo, WordBuilder};
pub use self::options::{Options, OpDef, OpType, OpVal};
pub use self::maps::Maps;
pub use self::checker::Checker;
// pub use self::errors::*;
// pub use self::other_error::*;


pub mod errors;
mod options;
mod key_press;
mod c_code;
mod miscellaneous;
mod chord;
mod words;
mod maps;
mod checker;
