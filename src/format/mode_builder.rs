use std::collections::BTreeMap;

use types::{SeqType, KmapPath, CCode, Chord, KmapInfo, ModeName, ToC};

use format::{Format, CArray};


pub struct  ModeBuilder <'a> {
    pub infos: &'a Vec<KmapInfo>,
    pub kmap_struct_names: &'a BTreeMap<SeqType, BTreeMap<KmapPath, CCode>>,
    pub seq_types: Vec<SeqType>,
    pub mode_name: &'a ModeName,
    pub mod_ctrl_chord: Chord,
    pub mod_shift_chord: Chord,
    pub mod_alt_chord: Chord,
    pub mod_gui_chord: Chord,
    pub wordmod_capital_chord: Chord,
    pub wordmod_nospace_chord: Chord,
    pub anagram_chords: Vec<Chord>,
}

impl <'a> ModeBuilder <'a> {
    pub fn format (&self, mode_struct_name: &mut CCode ) -> Format {
        let mut new_struct_name = CCode::new();
        let mut f = self.format_struct_list(&mut new_struct_name);

        let anagrams = CArray::new()
            .fill_2d(&self.anagram_chords.iter()
                     .map(|c| c.to_ints())
                     .collect())
            .format_contents();

        let m = ModeStruct {
            num_kmaps: self.infos.len() as u8, // TODO warn if too long?
            kmaps: new_struct_name,
            mod_ctrl_chord: self.mod_ctrl_chord.to_c(),
            mod_shift_chord: self.mod_shift_chord.to_c(),
            mod_alt_chord: self.mod_alt_chord.to_c(),
            mod_gui_chord: self.mod_gui_chord.to_c(),
            wordmod_capital_chord: self.wordmod_capital_chord.to_c(),
            wordmod_nospace_chord: self.wordmod_nospace_chord.to_c(),
            anagram_chords: anagrams,
            anagram_mask: self.make_anagram_mask().to_c(),
        };
        *mode_struct_name = format!("{}_struct", self.mode_name).to_c();
        f.append(&m.format(&mode_struct_name));
        f
    }

    fn format_struct_list (&self, new_struct_name: &mut CCode) -> Format
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
                        struct_names.get(&info.path)
                            .expect("kmap struct name not found")
                            .to_owned()
                    }
                );
            }
            v.push(v_row);
        }

        *new_struct_name = CCode(format!("{}_kmap_structs", self.mode_name));
        CArray::new()
            .name(new_struct_name)
            .c_type(&"KmapStruct".to_c())
            .fill_2d(&v)
            .format()
    }

    fn make_anagram_mask (&self) -> Chord {
        let mut anagram_mask = Chord::new();
        for c in self.anagram_chords.iter() {
            anagram_mask.intersect(c);
        }
        anagram_mask
    }
}

c_struct!(
    struct ModeStruct {
        num_kmaps: u8,
        kmaps: CCode,
        mod_ctrl_chord: CCode,
        mod_shift_chord: CCode,
        mod_alt_chord: CCode,
        mod_gui_chord: CCode,
        wordmod_capital_chord: CCode,
        wordmod_nospace_chord: CCode,
        anagram_chords: CCode,
        anagram_mask: CCode
    }
);
