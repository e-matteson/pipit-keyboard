use std::cmp::Ordering;

use types::{CCode, Chord, FirmwareOrder, ToC};

impl Ord for Chord<FirmwareOrder> {
    fn cmp(&self, other: &Self) -> Ordering {
        self.switches().blocks().cmp(other.switches().blocks())
    }
}

impl Chord<FirmwareOrder> {
    /// Convert the chord into CCode strings containing the byte representation
    /// used in the firmware.
    fn to_c_bytes(&self) -> Vec<CCode> {
        self.switches().blocks().map(|x| x.to_c()).collect()
    }

    fn to_c_initializer(&self) -> CCode {
        format!("{{{}}}", self.to_c_bytes().join(", ")).to_c()
    }

    pub fn to_c_constructor(&self) -> CCode {
        // TODO there are a bunch of extra allocations here...
        format!("{}({})", Self::c_type_name(), self.to_c_initializer()).to_c()
    }

    pub fn c_type_name() -> CCode {
        "ChordData".to_c()
    }
}
