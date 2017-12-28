use std::collections::BTreeMap;

// use format::CFiles;
use types::{CCode, CTree, Chord, Field, KmapPath, ModeInfo, ModeName, SeqType,
            ToC};
use types::errors::*;


pub struct ModeBuilder<'a> {
    pub info: &'a ModeInfo,
    pub kmap_struct_names: &'a BTreeMap<SeqType, BTreeMap<KmapPath, CCode>>,
    pub seq_types: Vec<SeqType>,
    pub mode_name: &'a ModeName,
    pub mod_chords: Vec<Chord>,
    pub anagram_chords: Vec<Chord>,
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

////////////////////////////////////////////////////////////////////////////////

impl<'a> ModeBuilder<'a> {
    pub fn format(&self, mode_struct_name: &mut CCode) -> Result<CTree> {
        let mut kmap_array_name = CCode::new();
        let mut g = Vec::new();
        g.push(self.format_kmap_array(&mut kmap_array_name)?);

        let mut anagram_array_name = CCode::new();
        g.push(self.format_anagram_array(&mut anagram_array_name));

        let mut anagram_mask_name = CCode::new();
        g.push(self.format_anagram_mask(&mut anagram_mask_name));

        let mut mod_array_name = CCode::new();
        g.push(self.format_modifier_array(&mut mod_array_name));

        let m = ModeStruct {
            num_kmaps: self.info.keymaps.len() as u8, // TODO warn if too long!
            kmaps: kmap_array_name.to_c(),
            mod_chords: mod_array_name.to_c(),
            anagram_chords: anagram_array_name.to_c(),
            anagram_mask: anagram_mask_name.to_c(),
            is_gaming: self.info.gaming,
        };
        *mode_struct_name = format!("{}_struct", self.mode_name).to_c();
        g.push(m.to_c_tree(mode_struct_name.to_owned()));
        Ok(CTree::Group(g))
    }

    fn format_kmap_array(&self, kmap_array_name: &mut CCode) -> Result<CTree> {
        let mut g = Vec::new();
        let mut subarray_names = Vec::new();
        for seq_type in &self.seq_types {
            let mut contents = Vec::new();
            let struct_names = self.kmap_struct_names
                .get(seq_type)
                .ok_or("struct name not found")?;

            for kmap_info in &self.info.keymaps {
                contents.push(
                    if *seq_type == SeqType::Word && !kmap_info.use_words {
                        "NULL".to_c()
                    } else {
                        format!(
                            "&{}",
                            struct_names
                                .get(&kmap_info.file)
                                .ok_or("kmap struct name not found")?
                        ).to_c()
                    },
                );
            }
            let name =
                format!("{}_{}_kmap_array", self.mode_name, seq_type).to_c();
            subarray_names.push(name.clone());
            g.push(CTree::Array {
                name: name,
                values: contents,
                c_type: "KmapStruct*".to_c(),
                is_extern: false,
            });

            // f += CArray::new(&name, &contents)
            //     .c_extern(false)
            //     .c_type("KmapStruct*")
            //     .format();
        }

        *kmap_array_name = format!("{}_kmap_arrays", self.mode_name).to_c();
        g.push(CTree::Array {
            name: kmap_array_name.to_owned(),
            values: subarray_names,
            c_type: "KmapStruct**".to_c(),
            is_extern: false,
        });
        // f += CArray::new(kmap_array_name, &subarray_names)
        //     .c_extern(false)
        //     .c_type("KmapStruct**")
        //     .format();
        Ok(CTree::Group(g))
    }

    fn format_anagram_mask(&self, array_name: &mut CCode) -> CTree {
        let mut anagram_mask = Chord::new();
        for c in &self.anagram_chords {
            anagram_mask.intersect(c);
        }
        *array_name = format!("{}_anagram_mask", self.mode_name).to_c();
        CTree::Array {
            name: array_name.to_owned(),
            values: anagram_mask.to_c_bytes(),
            c_type: "uint8_t".to_c(),
            is_extern: false,
        }
    }

    fn format_anagram_array(&self, new_array_name: &mut CCode) -> CTree {
        self.format_chord_array_helper(
            new_array_name,
            &self.anagram_chords,
            &"anagram_chord".to_c(),
        )
    }


    fn format_modifier_array(&self, new_array_name: &mut CCode) -> CTree {
        self.format_chord_array_helper(
            new_array_name,
            &self.mod_chords,
            &"mod_chord".to_c(),
        )
    }

    fn format_chord_array_helper(
        &self,
        new_array_name: &mut CCode,
        chords: &[Chord],
        label: &CCode,
    ) -> CTree {
        *new_array_name = format!("{}_{}", self.mode_name, label).to_c();
        CTree::CompoundArray {
            name: new_array_name.to_owned(),
            values: chords.iter().map(|c| c.to_c_bytes()).collect(),
            subarray_type: "uint8_t".to_c(),
            is_extern: false,
        }
    }

    // fn format_chord_array_helper(
    //     &self,
    //     new_array_name: &mut CCode,
    //     chords: &[Chord],
    //     label: &CCode,
    // ) -> CTree {
    //     let mut f = CFiles::new();
    //     let mut subarray_names = Vec::new();
    //     for (i, c) in chords.iter().enumerate() {
    //         let name = CCode(format!("{}_{}{}", self.mode_name, label, i));
    //         f += CArray::new(&name, &c.to_bytes()).c_extern(false).format();
    //         subarray_names.push(name);
    //     }
    //     *new_array_name = CCode(format!("{}_{}s", self.mode_name, label));
    //     f += CArray::new(new_array_name, &subarray_names)
    //         .c_type(&"uint8_t*".to_c())
    //         .c_extern(false)
    //         .format();
    //     f
    // }
}
