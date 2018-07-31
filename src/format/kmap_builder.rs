use itertools::Itertools;
use std::collections::{BTreeMap, BTreeSet};
use std::ops::BitOr;

use types::errors::OutOfRangeErr;
use types::{
    AllSeqMaps, AnagramNum, CCode, CTree, ChordMap, ChordSpec, Field,
    HuffmanTable, Name, SeqType, Sequence, ToC,
};
use util::usize_to_u16;

use failure::{Error, ResultExt};

// type SeqMap = BTreeMap<SeqType, BTreeMap<Name, Sequence>>;
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
    pub chord_map: &'a ChordMap,
    pub seq_maps: &'a AllSeqMaps,
    pub huffman_table: &'a HuffmanTable,
    pub chord_spec: ChordSpec,
}

c_struct!(struct KmapStruct {
    lookups_for_kmap: CCode,
});

c_struct!(struct LookupKmapType {
    num_lookups: usize,
    lookups: CCode,
});

c_struct!(struct LookupKmapTypeLenAnagram {
    seq_bit_len_and_anagram: u16,
    num_chords: u16,
    chords: CCode,
    sequences: CCode,
});

////////////////////////////////////////////////////////////////////////////////

impl<'a> KmapBuilder<'a> {
    pub fn render(&self) -> Result<(CTree, CCode), Error> {
        let mut g = Vec::new();
        let mut seq_type_names = Vec::new();

        for &seq_type in self.seq_maps.seq_types() {
            let grouped_names = self
                .group_names(seq_type)
                .context("failed to group names")?;

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
            c_type: "LookupKmapType*".to_c(),
            is_extern: false,
        });
        g.push(
            KmapStruct {
                lookups_for_kmap: array_name,
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
            c_type: "LookupKmapTypeLenAnagram*".to_c(),
            is_extern: false,
        });

        g.push(
            LookupKmapType {
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
                self.kmap_nickname,
                seq_type,
                info.length,
                info.anagram.unwrap()
            ).to_c();

            let seqs_name = format!("{}_seqs", struct_name).to_c();
            let chords_name = format!("{}_chords", struct_name).to_c();

            let chord_bytes = Itertools::flatten(
                names
                    .iter()
                    .map(|name| {
                        Ok(self
                            .chord_spec
                            .to_c_bytes(self.chord_map.get_result(name)?)?)
                    }).collect::<Result<Vec<_>, Error>>()?
                    .into_iter(),
            ).collect();

            let seqs = names
                .iter()
                .map(|name| self.seq_maps.get(name, seq_type))
                .collect::<Result<Vec<_>, Error>>()?;

            let seq_bytes =
                Sequence::flatten(&seqs).as_bytes(&self.huffman_table)?;

            let lookup_struct = LookupKmapTypeLenAnagram::new(
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

    // Group names by the lengths of their sequences and their anagram
    // numbers.
    fn group_names(&self, seq_type: SeqType) -> Result<LenMap, Error> {
        let mut grouped_names = BTreeMap::new();

        let names_in_kmap: BTreeSet<_> = self.chord_map.names().collect();
        let names_of_type: BTreeSet<_> =
            self.seq_maps.get_seq_map(seq_type)?.names().collect();

        for &name in names_in_kmap.intersection(&names_of_type) {
            let info = LenAndAnagram {
                length: self
                    .seq_maps
                    .get(name, seq_type)?
                    .formatted_length_in_bits(&self.huffman_table)?,
                anagram: self.chord_map.get(name).unwrap().anagram_num,
            };

            grouped_names
                .entry(info)
                .or_insert_with(Vec::new)
                .push(name.to_owned());
        }

        Ok(grouped_names)
    }
}

impl LookupKmapTypeLenAnagram {
    // TODO use a builder pattern instead of taking so many unnamed arguments?
    fn new(
        chords: CCode,
        sequences: CCode,
        num_chords: usize,
        anagram: AnagramNum,
        seq_bit_len: usize,
    ) -> Result<LookupKmapTypeLenAnagram, Error> {
        Ok(LookupKmapTypeLenAnagram {
            num_chords: usize_to_u16(num_chords)
                .context("Too many chords in lookup struct")?,
            chords: chords,
            sequences: sequences,
            seq_bit_len_and_anagram: LookupKmapTypeLenAnagram::pack(
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

        let packed = (anagram.unwrap() as u16).bitor(
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
