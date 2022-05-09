use bit_vec::BitVec;

use error::Error;
use types::{CLiteral, CTree, HuffmanTable, KeyPress, Sequence};

impl KeyPress {
    fn huffman(&self, table: &HuffmanTable) -> Result<BitVec<u8>, Error> {
        self.ensure_non_empty()?;

        let mut bits: BitVec<u8> = BitVec::default();
        for modifier in &self.mods {
            bits.extend(table.bits(modifier)?);
        }

        // There must be a key following the mod(s), so that we know when the
        // entry ends. If a keypress has a mod but no key,
        // use a blank dummy value for the key.
        bits.extend(table.bits(&self.key_or_blank())?);
        Ok(bits)
    }
}

impl Sequence {
    pub fn as_bytes(&self, table: &HuffmanTable) -> Result<Vec<CTree>, Error> {
        // TODO different name for "bytes"?
        Ok(self
            .as_bits(table)?
            .blocks()
            .map(|x: u8| CTree::Literal(CLiteral(x.to_string())))
            .collect())
    }

    pub fn formatted_length_in_bits(
        &self,
        table: &HuffmanTable,
    ) -> Result<usize, Error> {
        // TODO don't compute twice!
        Ok(self.as_bits(table)?.len())
    }

    pub fn as_bits(&self, table: &HuffmanTable) -> Result<BitVec<u8>, Error> {
        let mut bits = BitVec::default();
        for keypress in self.keypresses() {
            bits.extend(keypress.huffman(table)?)
        }
        Ok(bits)
    }
}
