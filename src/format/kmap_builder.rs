use std::collections::BTreeMap;

use types::{AnagramNum, CCode, CTree, Chord, Field, KmapPath, Name, SeqType,
            Sequence, ToC};
use failure::Error;

use types::errors::LookupErr;

type SeqMap = BTreeMap<Name, Sequence>;
type ChordMap = BTreeMap<Name, Chord>;
type LenMap = BTreeMap<usize, Vec<Name>>;

// TODO refactor this whole file
// At least be more consistent about terminology

pub struct KmapBuilder<'a> {
    seq_type: SeqType, // word, plain, macro, or command
    seq_map: &'a SeqMap,
    chord_maps: &'a BTreeMap<KmapPath, ChordMap>,
    kmap_nicknames: BTreeMap<KmapPath, String>,
    use_compression: bool,
    use_mods: bool,
}

struct ChordEntry {
    chord: Chord,
    offset: u8,
}

c_struct!(
    struct KmapStruct {
        chords: CCode,
        sequences: CCode,
        use_compression: bool,
        use_mods: bool
    }
);

////////////////////////////////////////////////////////////////////////////////

fn make_kmap_nicknames(
    kmap_paths: Vec<&KmapPath>,
) -> BTreeMap<KmapPath, String> {
    kmap_paths
        .into_iter()
        .enumerate()
        .map(|(i, kmap)| (kmap.to_owned(), format!("kmap{}", i)))
        .collect()
}

impl<'a> KmapBuilder<'a> {
    pub fn new(
        seq_type: SeqType,
        seq_map: &'a SeqMap,
        chord_maps: &'a BTreeMap<KmapPath, ChordMap>,
    ) -> KmapBuilder<'a> {
        KmapBuilder {
            seq_type: seq_type,
            seq_map: seq_map,
            chord_maps: chord_maps,
            kmap_nicknames: make_kmap_nicknames(chord_maps.keys().collect()),
            use_compression: get_compression_config(seq_type),
            use_mods: get_mods_config(seq_type),
        }
    }

    pub fn render(&self) -> Result<(CTree, BTreeMap<KmapPath, CCode>), Error> {
        // TODO don't make chord and seq array names in more than one place?
        // TODO skip words for kmap if never used? gcc seems to optimize them
        // away...
        let names_by_len = self.make_length_map();

        let seq_arrays = self.make_seq_arrays(&names_by_len);
        let chord_arrays = self.make_chord_arrays(&names_by_len)?;

        let seq_array_name = self.make_seq_array_name();

        let mut g = Vec::new();
        g.push(self.render_seq_arrays(&seq_arrays, seq_array_name.clone()));
        g.push(self.render_chord_arrays(&chord_arrays)?);

        let mut struct_names_out = BTreeMap::new();
        for kmap in chord_arrays.keys() {
            let chord_array_name = self.make_chord_array_name(kmap)?;
            let kmap_struct = KmapStruct {
                chords: chord_array_name.clone(),
                sequences: seq_array_name.clone(),
                use_compression: self.use_compression,
                use_mods: self.use_mods,
            };
            let struct_name = self.make_lookup_struct_name(kmap);
            g.push(kmap_struct.render(struct_name.clone()));
            struct_names_out.insert(kmap.clone(), struct_name);
        }
        Ok((CTree::Group(g), struct_names_out))
    }

    fn render_chord_arrays(
        &self,
        chord_arrays: &BTreeMap<KmapPath, Vec<Vec<ChordEntry>>>,
    ) -> Result<CTree, Error> {
        // TODO be consistent about "array" / "subarray" terminology
        let mut g = Vec::new();
        let mut array_names: Vec<CCode> = Vec::new();
        for (kmap, length_entries) in chord_arrays {
            let length_ints: Vec<Vec<CCode>> = length_entries
                .iter()
                .map(|subarray| flatten_chord_entries(subarray))
                .collect();

            let array_name = self.make_chord_array_name(kmap)?;
            g.push(CTree::CompoundArray {
                name: array_name.clone(),
                values: length_ints,
                subarray_type: "uint8_t".to_c(),
                is_extern: false,
            });
            array_names.push(array_name);
        }
        Ok(CTree::Group(g))
    }

    fn render_seq_arrays(&self, seq_arrays: &[Sequence], name: CCode) -> CTree {
        let byte_arrays: Vec<_> = seq_arrays
            .iter()
            .map(|keypress| {
                keypress.as_bytes(self.use_compression, self.use_mods)
            })
            .collect();

        CTree::CompoundArray {
            name: name,
            values: byte_arrays,
            subarray_type: "uint8_t".to_c(),
            is_extern: false,
        }
    }

    fn make_seq_arrays(&self, names_by_len: &LenMap) -> Vec<Sequence> {
        let mut seq_arrays = Vec::new();
        for length in 0..max_len(names_by_len) + 1 {
            let subarray = names_by_len
                .get(&length)
                .map_or_else(Sequence::new, |names| {
                    make_flat_sequence(self.seq_map, names)
                });
            seq_arrays.push(subarray);
        }
        seq_arrays
    }

    fn make_chord_arrays(
        &self,
        names_by_len: &LenMap,
    ) -> Result<BTreeMap<KmapPath, Vec<Vec<ChordEntry>>>, Error> {
        let mut chord_arrays = BTreeMap::new();
        for kmap in self.chord_maps.keys() {
            let mut kmap_array = Vec::new();
            // TODO inclusive range
            for length in 0..max_len(names_by_len) + 1 {
                kmap_array.push(self.make_chord_subarray(
                    names_by_len,
                    length,
                    kmap,
                )?);
            }
            chord_arrays.insert(kmap.to_owned(), kmap_array);
        }
        Ok(chord_arrays)
    }

    fn make_chord_subarray(
        &self,
        names_by_len: &LenMap,
        length: usize,
        kmap: &KmapPath,
    ) -> Result<Vec<ChordEntry>, Error> {
        let chords = &self.chord_maps[kmap];
        let mut entries = Vec::new();
        if let Some(names) = names_by_len.get(&length) {
            let mut last_index: usize = 0;
            for (index, name) in names.iter().enumerate() {
                if !chords.contains_key(name) {
                    continue;
                }
                // TODO use helper for lookup and error
                // TODO remove annotations
                let chord: Result<&Chord, Error> =
                    chords.get(name).ok_or_else(|| {
                        LookupErr {
                            key: name.to_string(),
                            container: "chord".into(),
                        }.into()
                    });
                // ?
                // .to_owned();
                entries.push(ChordEntry {
                    offset: (index - last_index) as u8,
                    chord: chord?.to_owned(),
                });
                last_index = index;
            }
        }
        // blank entry marks the end of the array
        entries.push(ChordEntry::new());
        Ok(entries)
    }

    fn make_length_map(&self) -> LenMap {
        // collect names by the lengths of their sequences
        let mut names_by_len = BTreeMap::new();
        let mut names: Vec<_> = self.seq_map.keys().collect();
        names.sort();
        for name in names {
            let length = self.seq_map[name].len();
            names_by_len
                .entry(length)
                .or_insert_with(Vec::new)
                .push(name.to_owned());
        }
        self.reorder_length_map(names_by_len)
    }

    fn reorder_length_map(&self, names_by_len: LenMap) -> LenMap {
        /// Alternately pick one name from each kmap, so no 2
        /// successive chords
        /// for a kmap will be too far apart.
        // Find the first name that's used in the given kmap.
        let find_name = |names: &Vec<Name>, kmap: &KmapPath| {
            names
                .iter()
                .position(|name| self.chord_maps[kmap].contains_key(name))
        };

        let mut new_map: LenMap = BTreeMap::new();
        for (length, mut names) in names_by_len {
            let mut v: Vec<Name> = Vec::new();
            let mut remaining_kmaps: Vec<_> = self.chord_maps.keys().collect();
            while !names.is_empty() {
                // For each entry/sequence:
                if remaining_kmaps.len() <= 1 {
                    // Just dump in all the remaining entries.
                    v.extend(names.clone());
                    // Done with this length!
                    break;
                }
                for kmap in remaining_kmaps.clone() {
                    match find_name(&names, kmap) {
                        Some(position) => {
                            // Move the entry to the new map
                            v.push(names[position].clone());
                            names.swap_remove(position);
                        }
                        None => {
                            // All of this kmap's entries have already been
                            // moved.
                            // Skip it from now on.
                            let kmap_index = remaining_kmaps
                                .iter()
                                .position(|&x| x == kmap)
                                .unwrap();
                            remaining_kmaps.remove(kmap_index);
                        }
                    }
                }
            }
            new_map.insert(length, v);
        }
        new_map
    }

    fn get_kmap_nickname(&self, kmap: &KmapPath) -> Result<String, Error> {
        self.kmap_nicknames
            .get(kmap)
            .ok_or_else(|| {
                LookupErr {
                    key: kmap.to_string(),
                    container: "kmap nicknames".into(),
                }.into()
            })
            .map(|s| s.to_owned())
    }

    fn make_chord_array_name(&self, kmap: &KmapPath) -> Result<CCode, Error> {
        Ok(CCode(format!(
            "{}_{}_chord_lookup",
            self.seq_type.to_string(),
            self.get_kmap_nickname(kmap)?
        )))
    }

    fn make_seq_array_name(&self) -> CCode {
        CCode(format!("{}_seq_lookup", self.seq_type.to_string()))
    }

    fn make_lookup_struct_name(&self, kmap: &KmapPath) -> CCode {
        CCode(format!(
            "{}_{}_struct",
            self.seq_type.to_string(),
            self.kmap_nicknames.get(kmap).expect("kmap name not found")
        ))
    }
}

////////////////////////////////////////////////////////////////////////////////

impl ChordEntry {
    fn new() -> ChordEntry {
        ChordEntry {
            chord: Chord::new(),
            offset: 0,
        }
    }

    fn to_bytes(&self) -> Vec<u8> {
        let mut v = self.make_prefix_byte();
        v.extend(self.chord.to_bytes());
        v
    }

    pub fn to_c_bytes(&self) -> Vec<CCode> {
        self.to_bytes().into_iter().map(|x| x.to_c()).collect()
    }

    fn make_prefix_byte(&self) -> Vec<u8> {
        // This format must match Lookup::readOffset() and
        // Lookup::readAnagramNum()!
        // Offset and anagram bits fit into 1 byte, so must add up to 8.
        const NUM_OFFSET_BITS: u32 = 5; // (least significant)
        const NUM_ANAGRAM_BITS: u32 = 3; // (most significant)

        let max_offset = (2u32.pow(NUM_OFFSET_BITS) - 1) as u8;
        let max_anagram = (2u32.pow(NUM_ANAGRAM_BITS) - 1) as u8;

        if self.offset > max_offset {
            panic!("offset is too large - too many layouts?");
        }

        if self.chord.anagram_num.0 > max_anagram {
            panic!("anagram num is too large");
        }
        assert_eq!(max_anagram, AnagramNum::max_allowable());

        let msb = self.chord
            .anagram_num
            .0
            .checked_shl(NUM_OFFSET_BITS)
            .expect("failed to shift when making prefix byte");
        let lsb = self.offset;
        vec![msb + lsb]
    }
}

////////////////////////////////////////////////////////////////////////////////

fn make_flat_sequence(seq_map: &SeqMap, names: &[Name]) -> Sequence {
    let mut flat_seq = Sequence::new();
    for name in names {
        flat_seq.extend(seq_map[name].clone());
    }
    flat_seq
}

fn max_len(names_by_len: &LenMap) -> usize {
    *names_by_len.keys().max().unwrap_or(&0)
}

fn flatten_chord_entries(entries: &[ChordEntry]) -> Vec<CCode> {
    let mut v = Vec::new();
    for entry in entries {
        v.extend(entry.to_c_bytes());
    }
    v
}

fn get_compression_config(seq_type: SeqType) -> bool {
    match seq_type {
        SeqType::Plain | SeqType::Macro | SeqType::Command => false,
        SeqType::Word => true,
    }
}

fn get_mods_config(seq_type: SeqType) -> bool {
    match seq_type {
        SeqType::Plain | SeqType::Macro => true,
        SeqType::Command | SeqType::Word => false,
    }
}
