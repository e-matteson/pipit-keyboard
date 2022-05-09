use std::collections::{BTreeMap, BTreeSet};

use error::{Error, ResultExt};
use types::{
    AllSeqMaps, AnagramNum, CIdent, CTree, CType, Chord, ChordMap, ChordSpec,
    HuffmanTable, Name, SeqType, Sequence,
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
        lookups_for_kmap: CIdent,
    }
);

c_struct!(
    struct LookupKmapType {
        num_lookups: usize,
        lookups: CIdent,
    }
);

c_struct!(
    struct LookupKmapTypeLenAnagram {
        seq_bit_len_and_anagram: CTree,
        num_chords: u16,
        chords: CIdent,
        sequences: CIdent,
    }
);

////////////////////////////////////////////////////////////////////////////////

impl<'a> KmapBuilder<'a> {
    pub fn render(&self) -> Result<(CTree, CIdent), Error> {
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

    fn make_kmap(&self, seq_type_names: &[CIdent]) -> (CTree, CIdent) {
        let kmap_struct_name =
            CIdent(format!("{}_lookups", self.kmap_nickname));
        let array_name = CIdent(format!("{}_array", kmap_struct_name));

        let mut g = Vec::new();
        g.push(CTree::array_def(
            array_name.clone(),
            CType::pointer(CType::custom("LookupKmapType")),
            seq_type_names
                .iter()
                .map(|ident| CTree::Address(ident.to_owned()))
                .collect(),
        ));
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
        lookups_of_length: &[CIdent],
    ) -> (CTree, CIdent) {
        let mut g = Vec::new();

        let num_lookups = lookups_of_length.len();
        let struct_name =
            CIdent(format!("{}_{}_lookups", self.kmap_nickname, seq_type));
        let array_name = CIdent(format!("{}_array", struct_name));

        g.push(CTree::array_def(
            array_name.clone(),
            CType::pointer(CType::custom("LookupKmapTypeLenAnagram")),
            lookups_of_length
                .into_iter()
                .map(|ident| CTree::Address(ident.to_owned()))
                .collect(),
        ));

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
    ) -> Result<(CTree, Vec<CIdent>), Error> {
        // TODO split into smaller functions?
        let mut g = Vec::new();
        let mut struct_names = Vec::new();

        for (&info, names) in grouped_names {
            let struct_name = CIdent(format!(
                "{}_{}_len{}_anagram{}",
                self.kmap_nickname,
                seq_type,
                info.length,
                info.anagram.get()
            ));

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
                .map(|(c, s)| (c.to_struct_initializer(), s))
                .unzip();

            let seq_bytes =
                Sequence::flatten(&seqs).as_bytes(&self.huffman_table)?;

            let chords_name = CIdent(format!("{}_chords", struct_name.0));
            let seqs_name = CIdent(format!("{}_seqs", struct_name.0));

            g.push(CTree::array_def(
                chords_name.clone(),
                Chord::c_type_name(),
                chord_bytes,
            ));

            g.push(CTree::array_def(seqs_name.clone(), CType::U8, seq_bytes));

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
            CTree::ConstDef {
                name: "MAX_ALLOWED_ANAGRAM".into(),
                value: Box::new(AnagramNum::max_allowed().into()),
                c_type: CType::U8,
            },
            CTree::ConstDef {
                name: "MAX_ALLOWED_SEQUENCE_BIT_LENGTH".into(),
                value: Box::new(Self::max_allowed_bit_length().into()),
                c_type: CType::U16,
            },
        ])
    }
}

impl LookupKmapTypeLenAnagram {
    // TODO use a builder pattern instead of taking so many unnamed arguments?
    fn new(
        chords: CIdent,
        sequences: CIdent,
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

    fn initializer(&self) -> CTree {
        CTree::StructInit {
            struct_type: Self::c_type(),
            values: vec![self.length.into(), self.anagram.into()],
        }
    }

    fn c_type() -> CType {
        CType::custom("LengthAndAnagram")
    }
}
