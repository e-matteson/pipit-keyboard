use std::collections::BTreeMap;

use types::{SeqType, KmapPath, CCode, Chord, ModeName, ModeInfo, ToC};
use format::{CFiles, CArray};


pub struct  ModeBuilder <'a> {
    pub info: &'a ModeInfo,
    pub kmap_struct_names: &'a BTreeMap<SeqType, BTreeMap<KmapPath, CCode>>,
    pub seq_types: Vec<SeqType>,
    pub mode_name: &'a ModeName,
    pub mod_chords: Vec<Chord>,
    pub anagram_chords: Vec<Chord>,
}

impl <'a> ModeBuilder <'a> {
    pub fn format (&self, mode_struct_name: &mut CCode ) -> CFiles {
        let mut kmap_array_name = CCode::new();
        let mut f = self.format_kmap_array(&mut kmap_array_name);

        let mut anagram_array_name = CCode::new();
        f.append(&self.format_anagram_array(&mut anagram_array_name));

        let mut anagram_mask_name = CCode::new();
        f.append(&self.format_anagram_mask(&mut anagram_mask_name));

        let mut mod_array_name = CCode::new();
        f.append(&self.format_modifier_array(&mut mod_array_name));

        let m = ModeStruct {
            num_kmaps: self.info.keymaps.len() as u8, // TODO warn if too long!
            kmaps: CCode(format!("{}", kmap_array_name)),
            mod_chords: CCode(format!("{}", mod_array_name)),
            anagram_chords: CCode(format!("{}", anagram_array_name)),
            anagram_mask: CCode(format!("{}", anagram_mask_name)),
            is_gaming: self.info.is_gaming,
        };
        *mode_struct_name = format!("{}_struct", self.mode_name).to_c();
        f.append(&m.format(mode_struct_name));
        f
    }

    fn format_kmap_array (&self, kmap_array_name: &mut CCode) -> CFiles
    {
        let mut f = CFiles::new();
        let mut subarray_names = Vec::new();
        for seq_type in &self.seq_types {
            let mut v = Vec::new();
            let struct_names = self.kmap_struct_names.get(seq_type)
                .expect("struct name not found");

            for kmap_info in &self.info.keymaps {
                v.push(
                    if *seq_type == SeqType::Word && !kmap_info.use_words {
                        "NULL".to_c()
                    } else {
                        CCode(
                            format!("&{}",
                                    struct_names.get(&kmap_info.path)
                                    .expect("kmap struct name not found")))
                    }
                );
            }
            let name = CCode(format!("{}_{}_kmap_array",
                                     self.mode_name,
                                     seq_type));
            f.append(&CArray::new()
                     .name(&name)
                     .c_extern(false)
                     .c_type(&"KmapStruct*".to_c())
                     .fill_1d(&v)
                     .format());
            subarray_names.push(name);
        }

        *kmap_array_name = CCode(format!("{}_kmap_arrays", self.mode_name));
        f.append(&CArray::new()
                 .name(kmap_array_name)
                 .c_extern(false)
                 .c_type(&"KmapStruct**".to_c())
                 .fill_1d(&subarray_names)
                 .format());
        f
    }

    fn format_anagram_mask (&self, array_name: &mut CCode) -> CFiles {
        let mut anagram_mask = Chord::new();
        for c in &self.anagram_chords {
            anagram_mask.intersect(c);
        }
        *array_name = CCode(format!("{}_anagram_mask", self.mode_name));
        CArray::new()
            .name(array_name)
            .c_extern(false)
            .fill_1d(&anagram_mask.to_ints())
            .format()
    }

    fn format_anagram_array (&self, new_array_name: &mut CCode) -> CFiles {
        self.format_chord_array_helper(new_array_name,
                             &self.anagram_chords,
                             &"anagram_chord".to_c())
    }


    fn format_modifier_array (&self, new_array_name: &mut CCode) -> CFiles {
        self.format_chord_array_helper(new_array_name,
                                       &self.mod_chords,
                                       &"mod_chord".to_c())
    }

    fn format_chord_array_helper (&self,
                                  new_array_name: &mut CCode,
                                  chords: &[Chord],
                                  label: &CCode) -> CFiles {
        let mut f = CFiles::new();
        let mut subarray_names = Vec::new();
        for (i,c) in chords.iter().enumerate() {
            let name = CCode(format!("{}_{}{}", self.mode_name, label, i));
            f.append(&CArray::new()
                     .name(&name)
                     .c_extern(false)
                     .fill_1d(&c.to_ints())
                     .format());
            subarray_names.push(name);
        }
        *new_array_name = CCode(format!("{}_{}s", self.mode_name, label));
        f.append(&CArray::new()
                 .name(new_array_name)
                 .c_type(&"uint8_t*".to_c())
                 .c_extern(false)
                 .fill_1d(&subarray_names)
                 .format());
        f
    }
}

c_struct!(
    struct ModeStruct {
        num_kmaps: u8,
        kmaps: CCode,
        mod_chords: CCode,
        anagram_chords: CCode,
        anagram_mask: CCode,
        is_gaming: bool
    }
);
