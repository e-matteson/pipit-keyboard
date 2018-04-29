use std::collections::{BTreeMap, BTreeSet};
use std::ops::BitOr;

use util::usize_to_u16;
use types::{AnagramNum, CCode, CTree, Chord, Field, HuffmanTable, Name,
            SeqType, Sequence, ToC};
use types::errors::OutOfRangeErr;

use failure::{Error, ResultExt};

type SeqMap = BTreeMap<SeqType, BTreeMap<Name, Sequence>>;
// type ChordMap = BTreeMap<Name, Chord>;
type LenMap = BTreeMap<LenAndAnagram, Vec<Name>>;

// TODO refactor this whole file
// At least be more consistent about terminology

#[derive(Eq, PartialEq, PartialOrd, Ord, Clone, Copy, Debug)]
struct LenAndAnagram {
    pub length: usize,
    pub anagram: AnagramNum,
}

pub struct KmapBuilder<'a> {
    pub kmap_nickname: String,
    pub chord_map: &'a BTreeMap<Name, Chord>,
    pub seq_maps: &'a SeqMap,
    pub huffman_table: &'a HuffmanTable,
}

c_struct!(
    struct KmapStruct {
        lookups_by_seq_type: CCode
    }
);

c_struct!(
    struct LookupsOfSeqType {
        num_lookups: usize,
        lookups: CCode
    }
);

c_struct!(
    struct LookupOfLength {
        seq_bit_len_and_anagram: u16,
        // sequence_bit_length: u8,
        // anagram_number: AnagramNum,
        num_chords: u16,
        chords: CCode,
        sequences: CCode
    }
);

////////////////////////////////////////////////////////////////////////////////

impl<'a> KmapBuilder<'a> {
    pub fn render(&self) -> Result<(CTree, CCode), Error> {
        let mut g = Vec::new();
        let mut seq_type_names = Vec::new();

        for &seq_type in self.seq_maps.keys() {
            let grouped_names = self.group_names(seq_type)?;
            let (tree, struct_names) =
                self.make_lookups_of_length(seq_type, &grouped_names)?;
            g.push(tree);

            let (tree, struct_name) =
                self.make_lookups_of_seq_type(seq_type, struct_names);
            g.push(tree);
            seq_type_names.push(struct_name);
        }
        let (tree, kmap_struct_name) = self.make_kmap(seq_type_names);
        g.push(tree);
        Ok((CTree::Group(g), kmap_struct_name))
    }

    fn make_kmap(&self, seq_type_names: Vec<CCode>) -> (CTree, CCode) {
        let kmap_struct_name = format!("{}_lookups", self.kmap_nickname).to_c();
        let array_name = format!("{}_array", kmap_struct_name).to_c();

        let mut g = Vec::new();
        g.push(CTree::Array {
            name: array_name.clone(),
            values: CCode::map_prepend("&", &seq_type_names),
            // TODO wrong type?
            c_type: "LookupsOfSeqType*".to_c(),
            is_extern: false,
        });
        g.push(
            KmapStruct {
                lookups_by_seq_type: array_name,
            }.render(kmap_struct_name.clone()),
        );
        (CTree::Group(g), kmap_struct_name)
    }

    fn make_lookups_of_seq_type(
        &self,
        seq_type: SeqType,
        lookups_of_length: Vec<CCode>,
    ) -> (CTree, CCode) {
        let mut g = Vec::new();

        let num_lookups = lookups_of_length.len();
        let struct_name =
            format!("{}_{}_lookups", self.kmap_nickname, seq_type).to_c();
        let array_name = format!("{}_array", struct_name).to_c();

        g.push(CTree::Array {
            name: array_name.clone(),
            values: CCode::map_prepend("&", &lookups_of_length),
            c_type: "LookupOfLength*".to_c(),
            is_extern: false,
        });

        g.push(
            LookupsOfSeqType {
                num_lookups: num_lookups,
                lookups: array_name,
            }.render(struct_name.clone()),
        );

        (CTree::Group(g), struct_name)
    }

    fn make_lookups_of_length(
        &self,
        seq_type: SeqType,
        grouped_names: &LenMap,
    ) -> Result<(CTree, Vec<CCode>), Error> {
        // TODO split into smaller functions?
        let mut g = Vec::new();
        let mut struct_names = Vec::new();

        for (info, names) in grouped_names {
            let struct_name = format!(
                "{}_{}_len{}_anagram{}",
                self.kmap_nickname, seq_type, info.length, info.anagram.0
            ).to_c();

            let seqs_name = format!("{}_seqs", struct_name).to_c();
            let chords_name = format!("{}_chords", struct_name).to_c();

            let chord_bytes: Vec<_> = names
                .iter()
                .flat_map(|name| self.chord_map[name].to_c_bytes())
                .collect();

            let seqs: Vec<_> = names
                .iter()
                .map(|name| &self.seq_maps[&seq_type][name])
                .collect();

            let seq_bytes =
                Sequence::flatten(&seqs).as_bytes(&self.huffman_table)?;

            let lookup_struct = LookupOfLength::new(
                chords_name.clone(),
                seqs_name.clone(),
                names.len(),
                info.anagram,
                info.length,
            ).with_context(|_| {
                format!("Failed to render lookup: '{}'", struct_name)
            })?;

            g.push(CTree::Array {
                name: chords_name,
                values: chord_bytes,
                c_type: "uint8_t".to_c(),
                is_extern: false,
            });

            g.push(CTree::Array {
                name: seqs_name,
                values: seq_bytes,
                c_type: "uint8_t".to_c(),
                is_extern: false,
            });

            g.push(lookup_struct.render(struct_name.clone()));
            struct_names.push(struct_name);
        }
        Ok((CTree::Group(g), struct_names))
    }

    fn group_names(&self, seq_type: SeqType) -> Result<LenMap, Error> {
        // Group names by the lengths of their sequences and their anagram
        // numbers.
        let mut grouped_names = BTreeMap::new();

        let names_in_kmap: BTreeSet<_> = self.chord_map.keys().collect();
        let names_of_type: BTreeSet<_> =
            self.seq_maps[&seq_type].keys().collect();

        for &name in names_in_kmap.intersection(&names_of_type) {
            let info = LenAndAnagram {
                length: self.seq_maps[&seq_type][name]
                    .formatted_length_in_bits(&self.huffman_table)?,
                anagram: self.chord_map[name].anagram_num,
            };

            grouped_names
                .entry(info)
                .or_insert_with(Vec::new)
                .push(name.to_owned());
        }
        Ok(grouped_names)
    }
}

impl LookupOfLength {
    // TODO use a builder pattern instead of taking so many unnamed arguments?
    fn new(
        chords: CCode,
        sequences: CCode,
        num_chords: usize,
        anagram: AnagramNum,
        seq_bit_len: usize,
    ) -> Result<LookupOfLength, Error> {
        Ok(LookupOfLength {
            num_chords: usize_to_u16(num_chords)
                .context("Too many chords in lookup struct")?,
            chords: chords,
            sequences: sequences,
            seq_bit_len_and_anagram: LookupOfLength::pack(
                seq_bit_len,
                anagram,
            )?,
        })
    }

    fn pack(seq_bit_len: usize, anagram: AnagramNum) -> Result<u16, Error> {
        let bits_for_len = 12;
        let bits_for_anagram = 4;

        assert!(16 == bits_for_anagram + bits_for_len);
        assert!(
            AnagramNum::max_allowable() as u32 == max_val(bits_for_anagram)
        );

        let max_len = max_val(bits_for_len) as usize;
        if seq_bit_len > max_len {
            Err(OutOfRangeErr {
                name: "length of compressed sequence".into(),
                value: seq_bit_len,
                min: 0,
                max: max_len,
            })?;
        }

        let packed = (anagram.0 as u16).bitor(
            usize_to_u16(seq_bit_len)
                .unwrap()
                .checked_shl(bits_for_anagram)
                .expect("failed to pack seq len and anagram"),
        );
        Ok(packed)
    }
}
fn max_val(num_bits: u32) -> u32 {
    2u32.pow(num_bits) - 1
}
