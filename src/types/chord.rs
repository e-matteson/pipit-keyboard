use std::fmt;
use std::sync::Mutex;

use types::errors::BadValueErr;
use types::{AnagramNum, CCode, Permutation, ToC};
use util::bools_to_bytes;

use failure::{Error, ResultExt};

/// This info (chord length etc.) should be set once after the settings file is
/// read, and then be the same for all chords.
lazy_static! {
    static ref INFO: Mutex<Option<StaticChordInfo>> = Mutex::new(None);
}

#[derive(Clone, Debug)]
pub struct StaticChordInfo {
    pub num_switches: usize,
    pub to_firmware_order: Permutation,
}

/// A chord is a set of switches pressed simultaneously. In the case of words'
/// chords, the anagram number will be stored separately, instead of literally
/// including the anagram modifier's switches in the word chord.
#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Serialize, Deserialize)]
pub struct Chord {
    /// Invariant: the length of this vec must always equal
    /// StaticChordInfo::num_switches.
    switches: Vec<bool>,
    pub anagram_num: AnagramNum,
}

////////////////////////////////////////////////////////////////////////////////

impl Chord {
    /// Construct a new empty chord with the default AnagramNum.
    pub fn new() -> Chord {
        Chord {
            switches: vec![false; Chord::static_length()],
            anagram_num: AnagramNum::default(),
        }
    }

    /// Construct a new empty chord with the given AnagramNum.
    pub fn with_anagram(num: AnagramNum) -> Chord {
        let mut chord = Chord::default();
        chord.anagram_num = num;
        chord
    }

    /// Construct a chord from bools representing each switch, in kmap order,
    /// where true means pressed.
    pub fn from_vec(v: Vec<bool>) -> Result<Chord, Error> {
        if v.len() != Chord::static_length() {
            Err(BadValueErr {
                thing: "chord length".into(),
                value: v.len().to_string(),
            }).context("Failed to create chord")?;
        }

        Ok(Chord {
            switches: v,
            anagram_num: AnagramNum::default(),
        })
    }

    /// The number of pressed switches in this chord.
    pub fn count_pressed(&self) -> usize {
        self.switches.iter().filter(|x| **x).count()
    }

    /// Make all the switches pressed in the other chord pressed in this chord,
    /// too. The AnagramNum of the other chord must be zero/default, or it
    /// will return an error. That's because otherwise we're probably doing
    /// something wrong, and might lose information by discarding the
    /// anagram number. Usually we'll just be intersecting plain_keys
    /// and/or plain_mods.
    pub fn intersect(&mut self, other: &Chord) {
        self.assert_correct_length();
        other.assert_correct_length();

        if other.anagram_num != AnagramNum::default() {
            // TODO return Result instead of unwrapping
            Err(BadValueErr {
                thing: "anagram number of other chord".into(),
                value: format!("{}", other.anagram_num),
            }).expect("Failed to intersect chords")
        }

        for i in 0..self.switches.len() {
            self.switches[i] |= other.switches[i];
        }
    }

    /// An iterator over the switch booleans (in kmap order)
    pub fn iter(&self) -> ::std::slice::Iter<bool> {
        self.switches.iter()
    }

    /// Convert the chord into CCode strings containing the byte representation
    /// used in the firmware.
    pub fn to_c_bytes(&self) -> Result<Vec<CCode>, Error> {
        // TODO  share code - replace with Into<Vec<CCode>> for Vec<T: ToC>?
        Ok(self.to_bytes()?.into_iter().map(|x| x.to_c()).collect())
    }

    /// Convert the chord into the byte representation used in the firmware.
    /// Treat each switch as a bit (1 means pressed). Permute them from kmap
    /// order to firmware order and pack them into bytes, padding the
    /// most-significant bits with zeros as needed.
    fn to_bytes(&self) -> Result<Vec<u8>, Error> {
        let ordered_bools =
            static_info().to_firmware_order.permute(&self.switches)?;
        Ok(bools_to_bytes(&ordered_bools))
    }

    /// The number of bytes required to represent a chord in the firmware.
    pub fn num_bytes_in_chord() -> Result<usize, Error> {
        // The best way to be sure we're calculating num_bytes_in_chord
        // correctly is to just create a chord, turn it to bytes like we will
        // during rendering, and check how many bytes are in it.
        Ok(Chord::new().to_bytes()?.len())
    }

    /// Set info about chord length etc. determined at runtime from the settings
    /// file (even though we wish we knew it at compile time). This info can
    /// never be modified after it is set, and it will apply to every chord
    /// that is created.
    pub fn set_info(info: StaticChordInfo) {
        set_static_info(info);
    }

    /// Get the number of switches in every chord (determined at runtime from
    /// the settings file). `Chord::set_info()` must have been
    pub fn static_length() -> usize {
        static_info().num_switches
    }

    /// Panic if the length of this particular chord doesn't match the expected
    /// length of every chord. Something has gone horribly wrong.
    fn assert_correct_length(&self) {
        assert_eq!(self.switches.len(), Chord::static_length())
    }

    /// Meant only for human-friendly debug printing
    fn bit_string(&self) -> String {
        let tmp: Vec<_> = self.switches
            .iter()
            .map(|&b| if b { "1" } else { "0" })
            .collect();
        tmp.join("")
    }
}

impl Default for Chord {
    fn default() -> Chord {
        Chord::new()
    }
}

impl fmt::Debug for Chord {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "Chord {{ {} : {}}}",
            self.bit_string(),
            self.anagram_num.unwrap()
        )
    }
}

fn set_static_info(info: StaticChordInfo) {
    let mut static_info = INFO.lock().unwrap();
    match *static_info {
        Some(_) => panic!("static chord info can only be set once"),
        None => *static_info = Some(info),
    }
}

fn static_info() -> StaticChordInfo {
    INFO.lock()
        .unwrap()
        .clone()
        .expect("static chord info was not set")
}
