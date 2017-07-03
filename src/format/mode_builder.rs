use std::collections::BTreeMap;

use types::{SeqType, KmapPath, CCode, Chord, KmapInfo, ModeName, ToC};

use format::{Format, CArray};


pub struct  ModeBuilder <'a> {
    pub infos: &'a Vec<KmapInfo>,
    pub kmap_struct_names: &'a BTreeMap<SeqType, BTreeMap<KmapPath, CCode>>,
    pub seq_types: Vec<SeqType>,
    pub mode_name: &'a ModeName,
    pub mod_chords: Vec<Chord>,
    pub anagram_chords: Vec<Chord>,
}

impl <'a> ModeBuilder <'a> {
    pub fn format (&self, mode_struct_name: &mut CCode ) -> Format {
        let mut kmap_array_name = CCode::new();
        let mut f = self.format_struct_array(&mut kmap_array_name);

        let mut anagram_array_name = CCode::new();
        f.append(&self.format_anagram_array(&mut anagram_array_name));

        let mut anagram_mask_name = CCode::new();
        f.append(&self.format_anagram_mask(&mut anagram_mask_name));

        let mut mod_array_name = CCode::new();
        f.append(&self.format_modifier_array(&mut mod_array_name));

        // TODO why does the explicit casting seem to be necessary?!
        //  And why don't KmapStructs need it too?!
        let m = ModeStruct {
            num_kmaps: self.infos.len() as u8, // TODO warn if too long?
            kmaps: CCode(format!("(const KmapStruct***) {}", kmap_array_name)),
            mod_chords: CCode(format!("(const uint8_t**) {}", mod_array_name)),
            anagram_chords: CCode(format!("(const uint8_t**) {}", anagram_array_name)),
            anagram_mask: CCode(format!("(const uint8_t*) {}", anagram_mask_name)),
        };
        *mode_struct_name = format!("{}_struct", self.mode_name).to_c();
        f.append(&m.format(&mode_struct_name));
        f
    }

    fn format_struct_array (&self, kmap_array_name: &mut CCode) -> Format
    {
        let mut v = Vec::new();
        for seq_type in self.seq_types.iter() {
            let mut v_row = Vec::new();
            let struct_names = self.kmap_struct_names.get(seq_type)
                .expect("struct name not found");

            for info in self.infos {
                v_row.push(
                    if *seq_type == SeqType::Word && !info.use_words {
                        "NULL".to_c()
                    } else {
                        CCode(
                            format!("&{}",
                                    struct_names.get(&info.path)
                                    .expect("kmap struct name not found")))
                    }
                );
            }
            v.push(v_row);
        }

        *kmap_array_name = CCode(format!("{}_kmap_structs", self.mode_name));
        CArray::new()
            .name(kmap_array_name)
            .is_extern(false)
            .c_type(&"KmapStruct*".to_c())
            .fill_2d(&v)
            .format()
    }

    fn format_anagram_mask (&self, array_name: &mut CCode) -> Format {
        let mut anagram_mask = Chord::new();
        for c in self.anagram_chords.iter() {
            anagram_mask.intersect(c);
        }
        *array_name = CCode(format!("{}_anagram_mask", self.mode_name));
        CArray::new()
            .name(array_name)
            .is_extern(false)
            .fill_1d(&anagram_mask.to_ints())
            .format()
    }

    fn format_anagram_array (&self, new_array_name: &mut CCode) -> Format {
        *new_array_name = CCode(format!("{}_anagram_chords", self.mode_name));
        CArray::new()
            .name(new_array_name)
            .is_extern(false)
            .fill_2d(&self.anagram_chords.iter()
                     .map(|c| c.to_ints())
                     .collect())
            .format()
    }

    fn format_modifier_array (&self, new_array_name: &mut CCode) -> Format {
        *new_array_name = CCode(format!("{}_modifier_chords", self.mode_name));
        CArray::new()
            .name(new_array_name)
            .is_extern(false)
            .fill_2d(&self.mod_chords.iter()
                     .map(|c| c.to_ints())
                     .collect())
            .format()
    }
}

c_struct!(
    struct ModeStruct {
        num_kmaps: u8,
        kmaps: CCode,
        mod_chords: CCode,
        anagram_chords: CCode,
        anagram_mask: CCode
    }
);
