use std::cmp::Ordering;

use types::{CLiteral, CTree, CType, Chord, FirmwareOrder};

impl Ord for Chord<FirmwareOrder> {
    fn cmp(&self, other: &Self) -> Ordering {
        self.switches().blocks().cmp(other.switches().blocks())
    }
}

impl Chord<FirmwareOrder> {
    /// Convert the chord into strings containing the byte representation
    /// used in the firmware.
    fn to_c_bytes(&self) -> Vec<CTree> {
        self.switches()
            .blocks()
            .map(|x| CTree::Literal(CLiteral(x.to_string())))
            .collect()
    }

    pub fn to_struct_initializer(&self) -> CTree {
        CTree::StructInit {
            struct_type: Self::c_type_name(),
            values: vec![CTree::ArrayInit {
                values: self.to_c_bytes(),
            }],
        }
    }

    pub fn c_type_name() -> CType {
        CType::custom("ChordData")
    }
}
