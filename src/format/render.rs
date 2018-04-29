use time::*;
use std::collections::BTreeMap;

use util::{bools_to_bytes, usize_to_u8};
use types::{AllData, CCode, CTree, Field, HuffmanTable, KeyPress, KmapPath,
            Name, SeqType, Sequence, ToC};

use format::{KmapBuilder, ModeBuilder};
// use format::KmapBuilder;

use types::errors::{BadValueErr, MissingErr};
use failure::{Error, ResultExt};

c_struct!(
    struct HuffmanChar {
        bits: CCode,
        num_bits: usize,
        key_code: CCode,
        is_mod: bool
    }
);

impl AllData {
    pub fn save_as(&self, file_name_base: &str) -> Result<(), Error> {
        let c_tree = self.render(file_name_base)?;
        let f = c_tree.format()?;
        // TODO as_ref?
        let dir = self.output_directory.as_ref().ok_or_else(|| MissingErr {
            missing: "output directory".into(),
            container: "settings".into(),
        })?;
        f.save(dir, file_name_base)
    }

    pub fn render(&self, file_name_base: &str) -> Result<CTree, Error> {
        let h_file_name = format!("{}.h", file_name_base);

        let mut group = Vec::new();
        group.push(self.render_options());
        group.push(self.huffman_table().render()?);
        group.push(self.render_modifiers()?);
        group.push(self.render_command_enum());
        group.push(self.render_seq_type_enum());
        group.push(self.render_mode_enum());
        group.push(self.render_modes()?);
        wrap_intro(&h_file_name, CTree::Group(group))
    }

    fn render_modes(&self) -> Result<CTree, Error> {
        let mut g = Vec::new();
        let (tree, kmap_struct_names) = self.render_kmaps()?;
        g.push(tree);

        let mut mode_struct_names = Vec::new();
        for (mode, info) in &self.modes {
            let m = ModeBuilder {
                mode_name: mode,
                info: info,
                kmap_struct_names: &kmap_struct_names,
                mod_chords: self.get_mod_chords(mode),
                anagram_chords: self.get_anagram_chords(mode),
            };
            let (tree, name) = m.render()?;
            g.push(tree);
            mode_struct_names.push(name);
        }

        g.push(CTree::Array {
            name: "mode_structs".to_c(),
            values: CCode::map_prepend("&", &mode_struct_names),
            c_type: "ModeStruct*".to_c(),
            is_extern: true,
        });
        Ok(CTree::Group(g))
    }

    fn render_kmaps(
        &self,
    ) -> Result<(CTree, BTreeMap<KmapPath, CCode>), Error> {
        // Render all keymap structs as CTrees, and return their names
        let mut kmap_struct_names = BTreeMap::new();
        let mut g = Vec::new();
        for (i, (kmap_name, chords)) in self.chords.iter().enumerate() {
            let builder = KmapBuilder {
                kmap_nickname: format!("kmap{}", i),
                chord_map: chords,
                seq_maps: &self.sequences,
                huffman_table: self.huffman_table(),
            };
            let (tree, kmap_struct_name) = builder.render()?;
            g.push(tree);
            kmap_struct_names.insert(kmap_name.to_owned(), kmap_struct_name);
        }
        Ok((CTree::Group(g), kmap_struct_names))
    }

    fn render_options(&self) -> CTree {
        CTree::Group(self.options.clone())
    }

    fn render_mode_enum(&self) -> CTree {
        let modes_list: Vec<_> =
            self.modes.keys().map(|x| x.to_c().to_uppercase()).collect();
        CTree::EnumDecl {
            name: "mode_enum".to_c(),
            variants: modes_list,
            size: Some("uint8_t".to_c()),
        }
    }

    fn make_mod_index_variants(&self) -> BTreeMap<Name, CCode> {
        // TODO rename?
        let mut all_index_variants = BTreeMap::new();
        for name in &self.get_mod_names() {
            all_index_variants.insert(
                name.to_owned(),
                format!("{}_ENUM", name).to_c().to_uppercase(),
            );
        }
        all_index_variants
    }

    fn get_variants(
        &self,
        mod_names: &[Name],
        all_mod_indices: &BTreeMap<Name, CCode>,
    ) -> Vec<CCode> {
        mod_names
            .iter()
            .map(|x| all_mod_indices[x].clone())
            .collect()
    }

    fn render_modifiers(&self) -> Result<CTree, Error> {
        let all_index_variants = self.make_mod_index_variants();
        let mut group = Vec::new();
        group.push(CTree::EnumDecl {
            name: "mod_enum".to_c(),
            variants: all_index_variants.values().cloned().collect(),
            size: Some("uint8_t".to_c()),
        });

        group.push(CTree::Define {
            name: "NUM_MODIFIERS".to_c(),
            value: all_index_variants.len().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_WORD_MODS".to_c(),
            value: self.word_mods.len().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_ANAGRAM_MODS".to_c(),
            value: self.anagram_mods.len().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_ANAGRAMS".to_c(),
            value: self.get_num_anagrams().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_PLAIN_MODS".to_c(),
            value: self.plain_mods.len().to_c(),
        });

        group.push(CTree::Array {
            name: "word_mod_indices".to_c(),
            values: self.get_variants(&self.word_mods, &all_index_variants),
            c_type: "mod_enum".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "plain_mod_indices".to_c(),
            values: self.get_variants(&self.plain_mods, &all_index_variants),
            c_type: "mod_enum".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "anagram_mod_indices".to_c(),
            values: self.get_variants(&self.anagram_mods, &all_index_variants),
            c_type: "mod_enum".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "plain_mod_keys".to_c(),
            values: self.get_plain_mod_codes()?,
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        Ok(CTree::Group(group))
    }

    fn get_plain_mod_codes(&self) -> Result<Vec<CCode>, Error> {
        self.plain_mods
            .iter()
            .map(|name| Ok(self.get_single_keypress(name)?.format_mods()))
            .collect()
    }

    fn render_command_enum(&self) -> CTree {
        let command_list: Vec<_> = self.sequences[&SeqType::Command]
            .keys()
            .map(|x: &Name| x.to_owned().to_c().to_uppercase())
            .collect();
        CTree::EnumDecl {
            name: "command_enum".to_c(),
            variants: command_list,
            size: Some("uint8_t".to_c()),
        }
    }

    fn render_seq_type_enum(&self) -> CTree {
        let v: Vec<_> = self.get_seq_types()
            .into_iter()
            .map(|s| s.to_c().to_uppercase())
            .collect();
        CTree::EnumDecl {
            name: "seq_type_enum".to_c(),
            variants: v,
            size: Some("uint8_t".to_c()),
        }
    }
}

impl HuffmanTable {
    fn render(&self) -> Result<CTree, Error> {
        let mut group = Vec::new();

        group.push(CTree::Define {
            name: KeyPress::blank(),
            value: 0.to_c(),
        });
        group.push(CTree::Define {
            name: "NUM_HUFFMAN_CODES".to_c(),
            value: self.0.len().to_c(),
        });

        let mut initializers = Vec::new();
        for key in self.0.keys() {
            // TODO Don't repeatedly look up key
            let name = format!("_huffman_bits_{}", key).to_c();
            let init = HuffmanChar {
                bits: name.clone(),
                num_bits: self.num_bits(key)?,
                key_code: KeyPress::truncate(key),
                is_mod: self.is_mod(key)?,
            }.render(CCode::new())
                .initializer();

            initializers.push(init);
            group.push(CTree::Array {
                name: name,
                values: self.as_c_bits(key)?,
                c_type: "bool".to_c(),
                is_extern: false,
            });
        }

        group.push(CTree::Array {
            name: "huffman_lookup".to_c(),
            values: initializers,
            c_type: "HuffmanChar".to_c(),
            is_extern: true,
        });

        Ok(CTree::Group(group))
    }
}

impl KeyPress {
    fn truncate(contents: &CCode) -> CCode {
        CCode(format!("({})&0xff", contents))
    }

    fn format_mods(&self) -> CCode {
        // TODO think about this
        match self.mods {
            Some(ref codes) => KeyPress::truncate(&CCode::join(codes, "|")),
            None => KeyPress::empty_code(),
        }
    }

    pub fn check_non_empty(&self) -> Result<(), Error> {
        let error = || {
            Err(BadValueErr {
                value: "(empty)".into(),
                thing: "KeyPress".into(),
            }).context("KeyPress must contain at least one key or modifier")
        };

        match (&self.key, &self.mods) {
            (None, None) => error()?,
            (None, Some(ref v)) if v.is_empty() => error()?,
            _ => Ok(()),
        }
    }

    pub fn huffman(&self, table: &HuffmanTable) -> Result<Vec<bool>, Error> {
        // TODO ensure codes are never longer than 255 bits! Firmware uses
        // uint8_t
        self.check_non_empty()?;

        let mut bits = Vec::new();
        if let Some(modifiers) = &self.mods {
            for modifier in modifiers {
                bits.extend(table.bits(modifier)?);
            }
        }

        // There must be a key following the mod(s), so that we know when the
        // entry ends. If a keypress has a mod but no key,
        // use a blank dummy value for the key.

        bits.extend(table.bits(&self.key_or_blank())?);

        Ok(bits)
    }
}

impl Sequence {
    pub fn as_bytes(&self, table: &HuffmanTable) -> Result<Vec<CCode>, Error> {
        // TODO different name for "bytes"?
        Ok(bools_to_bytes(&self.as_bits(table)?)
            .into_iter()
            .map(|x: u8| x.to_c())
            .collect())
    }

    pub fn formatted_length_in_bits(
        &self,
        table: &HuffmanTable,
    ) -> Result<usize, Error> {
        // TODO don't compute twice! switch to bitvec
        Ok(self.as_bits(table)?.len())
    }

    pub fn as_bits(&self, table: &HuffmanTable) -> Result<Vec<bool>, Error> {
        let mut bits = Vec::new();
        for keypress in self.keypresses() {
            bits.extend(keypress.huffman(table)?)
        }
        Ok(bits)
    }
}

pub fn wrap_intro(
    h_file_name: &str,
    namespace_tree: CTree,
) -> Result<CTree, Error> {
    // format!("#ifndef {}\n#define {}\n\n", guard_name, guard_name);
    let mut guard_group = Vec::new();
    guard_group.push(CTree::Include {
        path: "<Arduino.h>".to_c(),
    });
    guard_group.push(CTree::Include {
        path: "\"structs.h\"".to_c(),
    });
    guard_group.push(CTree::LiteralH(
        "typedef void (*voidFuncPtr)(void);\n".to_c(),
    ));

    guard_group.push(render_keycode_definitions());

    guard_group.push(CTree::Namespace {
        name: "conf".to_c(),
        contents: Box::new(namespace_tree),
    });

    guard_group.push(make_debug_macros());

    let guard = CTree::IncludeGuard {
        header_name: h_file_name.to_owned(),
        contents: Box::new(CTree::Group(guard_group)),
    };

    let mut outer_group = Vec::new();
    let msg = autogen_message();
    outer_group.push(CTree::LiteralC(msg.clone()));
    outer_group.push(CTree::LiteralH(msg));
    outer_group.push(guard);

    Ok(CTree::Group(outer_group))
}

fn autogen_message() -> CCode {
    const AUTHOR: &str = "pipit-config";

    let mut s = format!(
        "/**\n * Automatically generated by {} on:  {}\n",
        AUTHOR,
        now().strftime("%c").unwrap()
    );
    s += " * Do not make changes here, they will be overwritten.\n */\n\n";
    s.to_c()
}

fn make_debug_macros() -> CTree {
    // TODO clean up debug macros
    // TODO use Define variant instead
    let mut s = String::new();
    s += "\n#if DEBUG_MESSAGES == 0\n";
    s += "#define DEBUG1(msg)\n";
    s += "#define DEBUG1_LN(msg)\n";
    s += "#define DEBUG2(msg)\n";
    s += "#define DEBUG2_LN(msg)\n";
    s += "#endif\n\n";
    s += "#if DEBUG_MESSAGES == 1\n";
    s += "#define ENABLE_SERIAL_DEBUG\n";
    s += "#define DEBUG1(msg) Serial.print(msg)\n";
    s += "#define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#define DEBUG2(msg)\n";
    s += "#define DEBUG2_LN(msg)\n";
    s += "#endif\n\n";
    s += "#if DEBUG_MESSAGES == 2\n";
    s += "#define ENABLE_SERIAL_DEBUG\n";
    s += "#define DEBUG1(msg) Serial.print(msg)\n";
    s += "#define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#define DEBUG2(msg) Serial.print(msg)\n";
    s += "#define DEBUG2_LN(msg) Serial.println(msg)\n";
    s += "#endif\n\n";
    CTree::LiteralH(CCode(s))
}

fn render_keycode_definitions() -> CTree {
    let keycodes = KeyPress::defined_keycodes();
    let example = keycodes
        .keys()
        .nth(0)
        .expect("KeyPress::defined_keycodes() is empty!")
        .to_owned();

    let keycode_definitions = CTree::Group(
        keycodes
            .iter()
            .map(|(name, value)| CTree::Define {
                name: name.to_owned(),
                value: value.to_owned(),
            })
            .collect(),
    );

    CTree::Ifndef {
        conditional: example,
        contents: Box::new(keycode_definitions),
    }
}
