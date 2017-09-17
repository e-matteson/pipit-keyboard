pub use self::key_press::KeyPress;
pub use self::c_code::{CCode, ToC};
pub use self::miscellaneous::{KmapInfo, KmapPath, KmapFormat, ModeInfo, ModeName,
                              Name, SeqType, Sequence, SwitchPos, OpNew};
pub use self::chord::Chord;
pub use self::words::{Word, WordBuilder, WordInfo};
pub use self::maps::Maps;
pub use self::checker::Checker;
// pub use self::errors::*;
// pub use self::other_error::*;


pub mod errors;
mod key_press;
mod c_code;
mod miscellaneous;
mod chord;
mod words;
mod maps;
mod checker;
