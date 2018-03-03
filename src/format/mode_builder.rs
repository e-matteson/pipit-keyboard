use std::collections::BTreeMap;

use types::{CCode, CTree, Chord, Field, KmapPath, ModeInfo, ModeName, ToC};
// use types::errors::LookupErr;
use failure::Error;

pub struct ModeBuilder<'a> {
    pub mode_name: &'a ModeName,
    pub info: &'a ModeInfo,
    pub kmap_struct_names: &'a BTreeMap<KmapPath, CCode>,
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
    pub fn render(&self) -> Result<(CTree, CCode), Error> {
        let mut g = Vec::new();
        let (tree, kmap_array_name, num_kmaps) = self.render_kmap_array()?;
        g.push(tree);

        let (tree, mod_array_name) = self.render_modifier_array();
        g.push(tree);

        let (tree, anagram_array_name) = self.render_anagram_array();
        g.push(tree);

        let (tree, anagram_mask_name) = self.render_anagram_mask();
        g.push(tree);

        let mode_struct = ModeStruct {
            num_kmaps: num_kmaps as u8, // TODO warn if too long!
            kmaps: kmap_array_name,
            mod_chords: mod_array_name,
            anagram_chords: anagram_array_name,
            anagram_mask: anagram_mask_name,
            is_gaming: self.info.gaming,
        };
        let mode_struct_name = format!("{}_struct", self.mode_name).to_c();
        g.push(mode_struct.render(mode_struct_name.clone()));
        Ok((CTree::Group(g), mode_struct_name))
    }

    fn render_kmap_array(&self) -> Result<(CTree, CCode, usize), Error> {
        let mut g = Vec::new();

        let array_name = format!("{}_kmaps_array", self.mode_name).to_c();

        let contents: Vec<_> = self.info
            .keymaps
            .iter()
            .map(|info| {
                self.kmap_struct_names
                    .get(&info.file)
                    .expect("no struct name was found for kmap")
                    .to_owned()
            })
            .collect();

        g.push(CTree::Array {
            name: array_name.clone(),
            values: CCode::map_prepend("&", &contents),
            c_type: "KmapStruct*".to_c(),
            is_extern: false,
        });

        Ok((CTree::Group(g), array_name, contents.len()))
    }

    fn render_anagram_mask(&self) -> (CTree, CCode) {
        let mut anagram_mask = Chord::new();
        for c in &self.anagram_chords {
            anagram_mask.intersect(c);
        }
        let array_name_out = format!("{}_anagram_mask", self.mode_name).to_c();
        let tree = CTree::Array {
            name: array_name_out.clone(),
            values: anagram_mask.to_c_bytes(),
            c_type: "uint8_t".to_c(),
            is_extern: false,
        };
        (tree, array_name_out)
    }

    fn render_anagram_array(&self) -> (CTree, CCode) {
        self.render_chord_array_helper(
            &self.anagram_chords,
            &"anagram_chord".to_c(),
        )
    }

    fn render_modifier_array(&self) -> (CTree, CCode) {
        self.render_chord_array_helper(&self.mod_chords, &"mod_chord".to_c())
    }

    fn render_chord_array_helper(
        &self,
        chords: &[Chord],
        label: &CCode,
    ) -> (CTree, CCode) {
        let array_name_out = format!("{}_{}", self.mode_name, label).to_c();
        let tree = CTree::CompoundArray {
            name: array_name_out.clone(),
            values: chords.iter().map(|c| c.to_c_bytes()).collect(),
            subarray_type: "uint8_t".to_c(),
            is_extern: false,
        };
        (tree, array_name_out)
    }
}
