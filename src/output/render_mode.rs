use std::collections::BTreeMap;

use error::{Error, ResultExt};
use types::{
    CIdent, CTree, CType, Chord, ChordSpec, KmapOrder, LayerName, ModeInfo,
    ModeName,
};

use util::usize_to_u8;

pub struct ModeBuilder<'a> {
    pub mode_name: &'a ModeName,
    pub info: &'a ModeInfo,
    pub layer_struct_names: &'a BTreeMap<LayerName, CIdent>,
    pub mod_chords: Vec<Chord<KmapOrder>>,
    pub anagram_mask: Chord<KmapOrder>,
    pub chord_spec: ChordSpec,
}

c_struct!(
    struct ModeStruct {
        is_gaming: bool,
        num_kmaps: u8,
        kmaps: CIdent,
        mod_chords: CIdent,
        anagram_mask: CIdent,
    }
);

////////////////////////////////////////////////////////////////////////////////

impl<'a> ModeBuilder<'a> {
    pub fn render(&self) -> Result<(CTree, CIdent), Error> {
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
        let mode_struct_name = CIdent(format!("{}_struct", self.mode_name));
        g.push(mode_struct.render(mode_struct_name.clone()));
        Ok((CTree::Group(g), mode_struct_name))
    }

    fn render_layer_array(&self) -> Result<(CTree, CIdent, usize), Error> {
        let mut g = Vec::new();

        let array_name = CIdent(format!("{}_kmaps_array", self.mode_name));

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
        let length = contents.len();
        g.push(CTree::array_def(
            array_name.clone(),
            CType::pointer(CType::custom("KmapStruct")),
            contents
                .into_iter()
                .map(|ident| CTree::Address(ident))
                .collect(),
        ));

        Ok((CTree::Group(g), array_name, length))
    }

    fn render_anagram_mask(&self) -> Result<(CTree, CIdent), Error> {
        let array_name_out = CIdent(format!("{}_anagram_mask", self.mode_name));
        let tree = CTree::ConstDef {
            name: array_name_out.clone(),
            value: Box::new(
                self.chord_spec
                    .to_firmware(&self.anagram_mask)?
                    .to_struct_initializer(),
            ),
            c_type: Chord::c_type_name(),
        };
        Ok((tree, array_name_out))
    }

    fn render_modifier_array(&self) -> Result<(CTree, CIdent), Error> {
        self.render_chord_array_helper(&self.mod_chords, "mod_chord")
    }

    fn render_chord_array_helper(
        &self,
        chords: &[Chord<KmapOrder>],
        label: &str,
    ) -> Result<(CTree, CIdent), Error> {
        // TODO share code with stuff in kmap_builder? get rid of this helper?
        let array_name_out = CIdent(format!("{}_{}", self.mode_name, label));
        let tree = CTree::array_def(
            array_name_out.clone(),
            Chord::c_type_name(),
            chords
                .iter()
                .map(|c| {
                    Ok(self.chord_spec.to_firmware(c)?.to_struct_initializer())
                })
                .collect::<Result<Vec<CTree>, Error>>()?,
        );
        Ok((tree, array_name_out))
    }
}
