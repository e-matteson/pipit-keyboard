use std::collections::{BTreeMap, BTreeSet};

use error::{Error, ResultExt};
use types::{
    AllSeqMaps, AnagramNum, CCode, CTree, Chord, ChordMap, ChordSpec, Field,
    HuffmanTable, Name, SeqType, Sequence, ToC,
};
use util::usize_to_u16;

type LenMap = BTreeMap<LengthAndAnagram, Vec<Name>>;

// TODO refactor this whole file
// At least be more consistent about terminology

#[derive(Eq, PartialEq, PartialOrd, Ord, Clone, Copy, Debug)]
struct LengthAndAnagram {
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

c_struct!(
    struct KmapStruct {
        lookups_for_kmap: CCode,
    }
);

c_struct!(
    struct LookupKmapType {
        num_lookups: usize,
        lookups: CCode,
    }
);

c_struct!(
    struct LookupKmapTypeLenAnagram {
        seq_bit_len_and_anagram: CCode,
        num_chords: u16,
        chords: CCode,
        sequences: CCode,
    }
);

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
                self.make_lookups_of_seq_type(seq_type, &struct_names);

            g.push(tree);
            seq_type_names.push(struct_name);
        }

        let (tree, kmap_struct_name) = self.make_kmap(&seq_type_names);
        g.push(tree);
        Ok((CTree::Group(g), kmap_struct_name))
    }

    fn make_kmap(&self, seq_type_names: &[CCode]) -> (CTree, CCode) {
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
            }
            .render(kmap_struct_name.clone()),
        );
        (CTree::Group(g), kmap_struct_name)
    }

    fn make_lookups_of_seq_type(
        &self,
        seq_type: SeqType,
        lookups_of_length: &[CCode],
    ) -> (CTree, CCode) {
        let mut g = Vec::new();

        let num_lookups = lookups_of_length.len();
        let struct_name =
            format!("{}_{}_lookups", self.kmap_nickname, seq_type).to_c();
        let array_name = format!("{}_array", struct_name).to_c();

        g.push(CTree::Array {
            name: array_name.clone(),
            values: CCode::map_prepend("&", &lookups_of_length),
            // TODO no literal type name
            c_type: "LookupKmapTypeLenAnagram*".to_c(),
            is_extern: false,
        });

        g.push(
            LookupKmapType {
                num_lookups,
                lookups: array_name,
            }
            .render(struct_name.clone()),
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

        for (&info, names) in grouped_names {
            let struct_name = format!(
                "{}_{}_len{}_anagram{}",
                self.kmap_nickname,
                seq_type,
                info.length,
                info.anagram.get()
            )
            .to_c();

            let chords = names
                .iter()
                .map(|name| {
                    Ok(self
                        .chord_spec
                        .to_firmware(self.chord_map.get_result(name)?)?)
                })
                .collect::<Result<Vec<_>, Error>>()?;

            let seqs = names
                .iter()
                .map(|name| self.seq_maps.get(name, seq_type))
                .collect::<Result<Vec<_>, Error>>()?;

            let mut chords_and_seqs: Vec<_> =
                chords.into_iter().zip(seqs.into_iter()).collect();

            chords_and_seqs.sort_unstable_by(|(a, _), (b, _)| a.cmp(b));

            // TODO lots of allocations!
            let (chord_bytes, seqs): (Vec<_>, Vec<_>) = chords_and_seqs
                .into_iter()
                .map(|(c, s)| (c.to_c_constructor(), s))
                .unzip();

            let seq_bytes =
                Sequence::flatten(&seqs).as_bytes(&self.huffman_table)?;

            let chords_name = format!("{}_chords", struct_name).to_c();
            let seqs_name = format!("{}_seqs", struct_name).to_c();

            g.push(CTree::Array {
                name: chords_name.clone(),
                values: chord_bytes,
                c_type: Chord::c_type_name(),
                is_extern: false,
            });

            g.push(CTree::Array {
                name: seqs_name.clone(),
                values: seq_bytes,
                c_type: "uint8_t".to_c(),
                is_extern: false,
            });

            let lookup_struct = LookupKmapTypeLenAnagram::new(
                chords_name,
                seqs_name,
                names.len(),
                info,
            )
            .with_context(|| {
                format!("Failed to make lookup: '{}'", struct_name)
            })?;

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
            let info = LengthAndAnagram::new(
                self.seq_maps
                    .get(name, seq_type)?
                    .formatted_length_in_bits(&self.huffman_table)?,
                self.chord_map.get(name).unwrap().anagram_num,
            )?;

            grouped_names
                .entry(info)
                .or_insert_with(Vec::new)
                .push(name.to_owned());
        }

        Ok(grouped_names)
    }

    /// This depends on the representation in the firmware lookup tables.
    fn max_allowed_bit_length() -> usize {
        // We currently use 12 bits to store length
        2_usize.pow(12) - 1
    }

    /// State the limits we used when enforcing max lengths / anagrams, so the
    /// firmware can produce a compile time error if it disagree about what the
    /// limits should have been.
    pub fn render_limits() -> CTree {
        CTree::Group(vec![
            CTree::PublicConst {
                name: "MAX_ALLOWED_ANAGRAM".to_c(),
                value: AnagramNum::max_allowed().to_c(),
                c_type: "uint8_t".to_c(),
            },
            CTree::PublicConst {
                name: "MAX_ALLOWED_SEQUENCE_BIT_LENGTH".to_c(),
                value: Self::max_allowed_bit_length().to_c(),
                c_type: "uint16_t".to_c(),
            },
        ])
    }
}

impl LookupKmapTypeLenAnagram {
    // TODO use a builder pattern instead of taking so many unnamed arguments?
    fn new(
        chords: CCode,
        sequences: CCode,
        num_chords: usize,
        info: LengthAndAnagram,
    ) -> Result<Self, Error> {
        Ok(Self {
            num_chords: usize_to_u16(num_chords)
                .context("Too many chords in lookup struct")?,
            chords,
            sequences,
            seq_bit_len_and_anagram: info.initializer(),
        })
    }
}

impl LengthAndAnagram {
    fn new(length: usize, anagram: AnagramNum) -> Result<Self, Error> {
        if length > KmapBuilder::max_allowed_bit_length() {
            return Err(Error::OutOfRangeErr {
                name: "length of compressed sequence".to_owned(),
                value: length,
                min: 0,
                max: KmapBuilder::max_allowed_bit_length(),
            });
        }
        Ok(LengthAndAnagram { length, anagram })
    }

    fn initializer(&self) -> CCode {
        format!("{}({}, {})", Self::c_type(), self.length, self.anagram).to_c()
    }

    fn c_type() -> CCode {
        "LengthAndAnagram".to_c()
    }
}
