use std::collections::BTreeMap;

use error::{Error, ResultExt};
use types::{
    CCode, CTree, Chord, ChordSpec, Field, KmapOrder, LayerName, ModeInfo,
    ModeName, ToC,
};

use util::usize_to_u8;

pub struct ModeBuilder<'a> {
    pub mode_name: &'a ModeName,
    pub info: &'a ModeInfo,
    pub layer_struct_names: &'a BTreeMap<LayerName, CCode>,
    pub mod_chords: Vec<Chord<KmapOrder>>,
    pub anagram_mask: Chord<KmapOrder>,
    pub chord_spec: ChordSpec,
}

c_struct!(
    struct ModeStruct {
        is_gaming: bool,
        num_kmaps: u8,
        kmaps: CCode,
        mod_chords: CCode,
        anagram_mask: CCode,
    }
);

////////////////////////////////////////////////////////////////////////////////

impl<'a> ModeBuilder<'a> {
    pub fn render(&self) -> Result<(CTree, CCode), Error> {
        let mut g = Vec::new();
        let (tree, kmap_array_name, num_kmaps) = self.render_layer_array()?;
        g.push(tree);

        let (tree, mod_array_name) = self.render_modifier_array()?;
        g.push(tree);

        let (tree, anagram_mask_name) = self.render_anagram_mask()?;
        g.push(tree);

        let mode_struct = ModeStruct {
            num_kmaps: usize_to_u8(num_kmaps)
                .context("too many kmaps in mode")?,
            kmaps: kmap_array_name,
            mod_chords: mod_array_name,
            anagram_mask: anagram_mask_name,
            is_gaming: self.info.gaming,
        };
        let mode_struct_name = format!("{}_struct", self.mode_name).to_c();
        g.push(mode_struct.render(mode_struct_name.clone()));
        Ok((CTree::Group(g), mode_struct_name))
    }

    fn render_layer_array(&self) -> Result<(CTree, CCode, usize), Error> {
        let mut g = Vec::new();

        let array_name = format!("{}_kmaps_array", self.mode_name).to_c();

        let contents: Vec<_> = self
            .info
            .layers
            .iter()
            .map(|layer_name| {
                self.layer_struct_names
                    .get(&layer_name)
                    .expect("no struct name was found for layer")
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

    fn render_anagram_mask(&self) -> Result<(CTree, CCode), Error> {
        let array_name_out = format!("{}_anagram_mask", self.mode_name).to_c();
        let tree = CTree::PrivateConst {
            name: array_name_out.clone(),
            value: self
                .chord_spec
                .to_firmware(&self.anagram_mask)?
                .to_c_constructor(),
            c_type: Chord::c_type_name(),
        };
        Ok((tree, array_name_out))
    }

    fn render_modifier_array(&self) -> Result<(CTree, CCode), Error> {
        self.render_chord_array_helper(&self.mod_chords, &"mod_chord".to_c())
    }

    fn render_chord_array_helper(
        &self,
        chords: &[Chord<KmapOrder>],
        label: &CCode,
    ) -> Result<(CTree, CCode), Error> {
        // TODO share code with stuff in kmap_builder? get rid of this helper?
        let array_name_out = format!("{}_{}", self.mode_name, label).to_c();
        let tree = CTree::Array {
            name: array_name_out.clone(),
            values: chords
                .iter()
                .map(|c| Ok(self.chord_spec.to_firmware(c)?.to_c_constructor()))
                .collect::<Result<Vec<CCode>, Error>>()?,
            c_type: Chord::c_type_name(),
            is_extern: false,
        };
        Ok((tree, array_name_out))
    }
}
