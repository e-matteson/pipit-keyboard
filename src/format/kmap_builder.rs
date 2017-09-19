use std::fmt::Display;
use std::collections::BTreeMap;

use format::{CArray, CFiles};
use types::{CCode, Chord, KmapPath, Name, SeqType, Sequence, ToC};
use types::errors::*;

type SeqMap = BTreeMap<Name, Sequence>;
type ChordMap = BTreeMap<Name, Chord>;
type LenMap = BTreeMap<usize, Vec<Name>>;

// TODO refactor this whole file
// At least be more consistent about terminology


struct ChordEntry {
    chord: Chord,
    offset: u8,
}

impl ChordEntry {
    pub fn new() -> ChordEntry {
        ChordEntry {
            chord: Chord::new(),
            offset: 0,
        }
    }

    pub fn to_ints(&self) -> Vec<u8> {
        // let mut v = vec![self.offset as i64];
        let mut v = self.make_prefix_byte();
        v.extend(self.chord.to_ints());
        v
    }

    pub fn make_prefix_byte(&self) -> Vec<u8> {
        // This format must match Lookup::readOffset() and
        // Lookup::readAnagramNum()!
        // Offset and anagram bits fit into 1 byte, so must add up to 8.
        const NUM_OFFSET_BITS: u32 = 5; // (least significant)
        const NUM_ANAGRAM_BITS: u32 = 3; // (most significant)

        let max_offset = 2u32.pow(NUM_OFFSET_BITS) as u8;
        let max_anagram = 2u32.pow(NUM_ANAGRAM_BITS) as u8;

        if self.offset > max_offset {
            panic!("offset is too large - too many layouts?");
        }

        if self.chord.anagram_num.0 > max_anagram {
            panic!("anagram num is too large");
        }

        let msb = self.chord.anagram_num.0.checked_shl(NUM_OFFSET_BITS).unwrap();
        let lsb = self.offset;
        vec![msb + lsb]
    }
}

//////////////////////

pub struct KmapBuilder<'a> {
    seq_type: SeqType, // word, plain, macro, or command
    seq_map: &'a SeqMap,
    chord_maps: &'a BTreeMap<KmapPath, ChordMap>,
    kmap_ids: &'a BTreeMap<KmapPath, String>,
    use_compression: bool,
    use_mods: bool,
}


impl<'a> KmapBuilder<'a> {
    pub fn new(
        seq_type: SeqType,
        seq_map: &'a SeqMap,
        chord_maps: &'a BTreeMap<KmapPath, ChordMap>,
        kmap_ids: &'a BTreeMap<KmapPath, String>,
    ) -> KmapBuilder<'a> {
        KmapBuilder {
            seq_type: seq_type,
            seq_map: seq_map,
            chord_maps: chord_maps,
            kmap_ids: kmap_ids,
            use_compression: get_compression_config(seq_type),
            use_mods: get_mods_config(seq_type),
        }
    }

    pub fn format(
        &self,
        struct_names_out: &mut BTreeMap<KmapPath, CCode>,
    ) -> Result<CFiles> {
        // Store the struct names in struct_names_out, for later use
        // TODO don't make chord and seq array names in more than one place?
        // TODO skip words for kmap if never used? gcc seems to optimize them
        // away...
        let names_by_len = self.make_length_map();

        let seq_arrays = self.make_seq_arrays(&names_by_len);
        let chord_arrays = self.make_chord_arrays(&names_by_len)?;

        let mut f = CFiles::new();
        f += self.format_seq_arrays(&seq_arrays);
        f += self.format_chord_arrays(&chord_arrays)?;

        let seq_array_name = self.make_seq_array_name();
        for kmap in chord_arrays.keys() {
            let chord_array_name = self.make_chord_array_name(kmap)?;
            let s = KmapStruct {
                chords: chord_array_name.clone(),
                sequences: seq_array_name.clone(),
                use_compression: self.use_compression,
                use_mods: self.use_mods,
            };
            let struct_name = self.make_lookup_struct_name(kmap);
            f += s.format(&struct_name);
            struct_names_out.insert(kmap.clone(), struct_name);
        }
        Ok(f)
    }

    fn format_chord_arrays(
        &self,
        chord_arrays: &BTreeMap<KmapPath, Vec<Vec<ChordEntry>>>,
    ) -> Result<CFiles> {
        // TODO be consistent about "array" / "subarray" terminology
        let mut f = CFiles::new();
        let mut array_names: Vec<CCode> = Vec::new();
        for (kmap, length_entries) in chord_arrays {
            let length_ints: Vec<Vec<u8>> = length_entries
                .iter()
                .map(|v| flatten_chord_entries(v))
                .collect();

            let array_name = self.make_chord_array_name(kmap)?;
            f += self.format_length_arrays(length_ints, &array_name, false);
            array_names.push(array_name.clone());
        }
        Ok(f)
    }

    fn format_seq_arrays(&self, seq_arrays: &[Sequence]) -> CFiles {
        let byte_arrays: Vec<_> = seq_arrays
            .iter()
            .map(|keypress| {
                keypress.to_bytes(self.use_compression, self.use_mods)
            })
            .collect();
        self.format_length_arrays(
            byte_arrays,
            &self.make_seq_array_name(),
            false,
        )
    }

    fn make_seq_arrays(&self, names_by_len: &LenMap) -> Vec<Sequence> {
        let mut seq_arrays = Vec::new();
        for length in 0..max_len(names_by_len) + 1 {
            let subarray =
                // match names_by_len.get(&length) {
                //     Some(names) =>
                //         make_flat_sequence(self.seq_map, names),
                //     None => Sequence::new(),
                // };
                names_by_len.get(&length).map_or_else(
                    Sequence::new,
                    |names| make_flat_sequence(self.seq_map, names)
                );
            seq_arrays.push(subarray);
        }
        seq_arrays
    }

    fn make_chord_arrays(
        &self,
        names_by_len: &LenMap,
    ) -> Result<BTreeMap<KmapPath, Vec<Vec<ChordEntry>>>> {
        let mut chord_arrays = BTreeMap::new();
        for kmap in self.chord_maps.keys() {
            let mut kmap_array = Vec::new();

            for length in 0..max_len(names_by_len) + 1 {
                kmap_array
                    .push(self.make_chord_subarray(names_by_len, length, kmap)?);
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
    ) -> Result<Vec<ChordEntry>> {
        let chords = &self.chord_maps[kmap];
        let mut entries = Vec::new();
        if let Some(names) = names_by_len.get(&length) {
            let mut last_index: usize = 0;
            for (index, name) in names.iter().enumerate() {
                if !chords.contains_key(name) {
                    continue;
                }
                entries.push(ChordEntry {
                    offset: (index - last_index) as u8,
                    chord: chords
                        .get(name)
                        .ok_or("failed to get chord")?
                        .clone(),
                });
                last_index = index;
            }
        }
        // blank entry marks the end of the array
        entries.push(ChordEntry::new());
        Ok(entries)
    }


    fn format_length_arrays<T>(
        &self,
        arrays: Vec<Vec<T>>,
        name: &CCode,
        is_extern: bool,
    ) -> CFiles
    where
        T: Display + Clone,
    {
        let mut subarray_names: Vec<_> = (0..arrays.len())
            .map(|x| CCode(format!("{}_{}", name, x)))
            .collect();
        let mut f = CFiles::new();
        for i in 0..subarray_names.len() {
            f += CArray::new(&subarray_names[i], &arrays[i])
                .c_extern(false)
                .format();
        }
        subarray_names.push("NULL".to_c());
        f += CArray::new(name, &subarray_names)
            .c_extern(is_extern)
            .c_type(&"uint8_t*".to_c())
            .format();
        f
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

    fn make_chord_array_name(&self, kmap: &KmapPath) -> Result<CCode> {
        Ok(CCode(format!(
            "{}_{}_chord_lookup",
            self.seq_type.to_string(),
            self.kmap_ids.get(kmap).ok_or("kmap name not found")?
        )))
    }

    fn make_seq_array_name(&self) -> CCode {
        CCode(format!("{}_seq_lookup", self.seq_type.to_string()))
    }

    fn make_lookup_struct_name(&self, kmap: &KmapPath) -> CCode {
        CCode(format!(
            "{}_{}_struct",
            self.seq_type.to_string(),
            self.kmap_ids.get(kmap).expect("kmap name not found")
        ))
    }
}

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

fn flatten_chord_entries(entries: &[ChordEntry]) -> Vec<u8> {
    let mut v = Vec::new();
    for entry in entries {
        v.extend(entry.to_ints());
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


c_struct!(
    struct KmapStruct {
        chords: CCode,
        sequences: CCode,
        use_compression: bool,
        use_mods: bool
    }
);
