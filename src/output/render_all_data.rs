use std::collections::BTreeMap;

use time::*;

use error::Error;
use types::{
    AllData, CCode, CEnumVariant, CTree, Command, KeyDefs, KmapPath, ModeName,
    Modifier, Name, SeqType, ToC,
};

use output::{KmapBuilder, ModeBuilder};
use util::usize_to_u8;

impl AllData {
    /// Generate and save the c code containing the keyboard firmware
    /// configuration. `file_name_base` should have no extension. `.h` and
    /// `.cpp` will be added to it as needed.
    pub fn save_as(&self, file_name_base: &str) -> Result<(), Error> {
        self.save_helper(file_name_base, true)
    }

    /// Used for testing. The message contains a timestamp that would make the
    /// same output files look different if they're only generated at different
    /// times.
    #[cfg(test)]
    pub fn save_without_message_as(
        &self,
        file_name_base: &str,
    ) -> Result<(), Error> {
        self.save_helper(file_name_base, false)
    }

    fn save_helper(
        &self,
        file_name_base: &str,
        with_message: bool,
    ) -> Result<(), Error> {
        let main_files =
            self.render_main(with_message)?.format(file_name_base)?;

        let early_name_base = format!("{}_early", file_name_base);
        let early_files = self
            .render_early_config(with_message)?
            .format(&early_name_base)?;

        let mut file_names =
            main_files.save(&self.output_directory, file_name_base)?;

        file_names.extend(
            early_files.save(&self.output_directory, &early_name_base)?,
        );

        let file_name_list = file_names
            .into_iter()
            .map(|path| format!("{:?}", path))
            .collect::<Vec<_>>()
            .join(", ");

        println!("Saved keyboard configuration to: {}", file_name_list);
        Ok(())
    }

    /// Render c code defining any constants etc. that need to be included
    /// before / separately from the main auto_config.h file.
    fn render_early_config(&self, with_message: bool) -> Result<CTree, Error> {
        let mut group = Vec::new();
        if with_message {
            group.push(CTree::LiteralH(autogen_message()));
        }
        group.push(CTree::LiteralH("#pragma once\n".to_c()));

        let mut namespace = Vec::new();
        namespace.extend(self.user_options.render_early());
        namespace.push(KmapBuilder::render_limits());
        namespace.push(self.huffman_table.render_early());
        namespace.push(ModeName::render_c_enum(self.modes.keys()));

        // Use the first mode enum variant as the default mode
        // TODO what happens if there are no modes, so no variant with value 0,
        // and this cast is invalid?
        namespace.push(CTree::LiteralH(
            "constexpr Mode defaultMode() { return static_cast<Mode>(0); }\n\n"
                .to_c(),
        ));

        let all_mods: Vec<_> = self
            .modifier_names()
            .into_iter()
            .map(|name| Modifier::new(name))
            .collect();

        namespace.push(Modifier::render_c_enum(all_mods.iter()));
        namespace.push(CTree::Define {
            name: "NUM_MODIFIERS".to_c(),
            value: all_mods.len().to_c(),
        });
        namespace.push(SeqType::render_c_enum(self.sequences.seq_types()));

        group.push(CTree::Namespace {
            name: "conf".to_c(),
            contents: Box::new(CTree::Group(namespace)),
        });

        Ok(CTree::Group(group))
    }

    fn render_main(&self, with_message: bool) -> Result<CTree, Error> {
        Ok(CTree::Group(vec![
            intro(with_message)?,
            CTree::Namespace {
                name: "conf".to_c(),
                contents: Box::new(CTree::Group(vec![
                    self.user_options.render(),
                    self.huffman_table.render()?,
                    self.render_modifiers()?,
                    Command::render_c_enum(self.commands.iter()),
                    self.render_modes()?,
                ])),
            },
            make_debug_macros(),
        ]))
    }

    fn render_modes(&self) -> Result<CTree, Error> {
        let mut g = Vec::new();

        g.push(CTree::ConstVar {
            name: "MAX_KEYS_IN_SEQUENCE".to_c(),
            value: usize_to_u8(self.sequences.max_seq_length())?.to_c(),
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        let (tree, kmap_struct_names) = self.render_kmaps()?;
        g.push(tree);

        let mut mode_struct_names = Vec::new();
        for (mode, info) in &self.modes {
            let m = ModeBuilder {
                mode_name: mode,
                info,
                kmap_struct_names: &kmap_struct_names,
                mod_chords: self.modifier_chords(mode),
                anagram_mask: self.get_anagram_mask(mode),
                chord_spec: self.chord_spec.clone(),
            };
            let (tree, name) = m.render()?;
            g.push(tree);
            mode_struct_names.push(name);
        }

        g.push(CTree::StdArray {
            name: "mode_structs".to_c(),
            values: CCode::map_prepend("&", &mode_struct_names),
            c_type: "const ModeStruct*".to_c(),
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
                huffman_table: &self.huffman_table,
                chord_spec: self.chord_spec.clone(),
            };
            let (tree, kmap_struct_name) = builder.render()?;
            g.push(tree);
            kmap_struct_names.insert(kmap_name.to_owned(), kmap_struct_name);
        }
        Ok((CTree::Group(g), kmap_struct_names))
    }

    fn render_modifiers(&self) -> Result<CTree, Error> {
        fn to_variants(mod_names: &[Name]) -> Vec<CCode> {
            mod_names
                .iter()
                .map(|name| Modifier::new(name).qualified_enum_variant())
                .collect()
        }

        let mut group = Vec::new();

        group.push(CTree::ConstVar {
            name: "MAX_ANAGRAM_NUM".to_c(),
            value: self.chords.max_anagram_num().to_c(),
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        group.push(CTree::StdArray {
            name: "word_mods".to_c(),
            values: to_variants(&self.word_mods),
            c_type: Modifier::enum_type(),
            is_extern: true,
        });

        group.push(CTree::StdArray {
            name: "plain_mods".to_c(),
            values: to_variants(&self.plain_mods),
            c_type: Modifier::enum_type(),
            is_extern: true,
        });

        group.push(CTree::StdArray {
            name: "anagram_mods".to_c(),
            values: to_variants(&self.anagram_mods),
            c_type: Modifier::enum_type(),
            is_extern: true,
        });

        group.push(CTree::StdArray {
            name: "anagram_mod_numbers".to_c(),
            values: self
                .get_anagram_mod_numbers()?
                .iter()
                .map(|num| num.to_c())
                .collect(),
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        group.push(CTree::StdArray {
            name: "plain_mod_keys".to_c(),
            values: self.get_plain_mod_codes()?,
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        Ok(CTree::Group(group))
    }

    fn get_plain_mod_codes(&self) -> Result<Vec<CCode>, Error> {
        // TODO this should be easier...
        self.plain_mods
            .iter()
            .map(|name| {
                Ok(self
                    .sequences
                    .get_seq_of_any_type(name)?
                    .lone_keypress()?
                    .format_mods())
            })
            .collect()
    }
}

/// Generate the top of the main auto_config files. If `with_message` is true,
/// add a commented message about when the file was autogenerated.
fn intro(with_message: bool) -> Result<CTree, Error> {
    let mut group = Vec::new();
    if with_message {
        let msg = autogen_message();
        group.push(CTree::LiteralC(msg.clone()));
        group.push(CTree::LiteralH(msg));
    }
    group.push(CTree::LiteralH("#pragma once\n".to_c()));
    group.push(CTree::IncludeSelf);

    group.push(CTree::IncludeH {
        path: "<Arduino.h>".to_c(),
    });
    group.push(CTree::IncludeH {
        path: "<stdint.h>".to_c(),
    });
    group.push(CTree::IncludeH {
        path: "\"config_types.h\"".to_c(),
    });

    group.push(CTree::LiteralH(
        "typedef void (*voidFuncPtr)(void);\n".to_c(),
    ));

    group.push(render_keycode_definitions());

    Ok(CTree::Group(group))
}

fn autogen_message() -> CCode {
    const AUTHOR: &str = "pipit-keyboard";

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
    s += "    #define DEBUG1(msg)\n";
    s += "    #define DEBUG1_LN(msg)\n";
    s += "    #define DEBUG2(msg)\n";
    s += "    #define DEBUG2_LN(msg)\n";
    s += "#else\n";
    s += "   #define ENABLE_SERIAL_DEBUG\n";
    s += "   #include <Arduino.h>\n";
    s += "   #define DEBUG1(msg) Serial.print(msg)\n";
    s += "   #define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "   #if DEBUG_MESSAGES == 1\n";
    s += "       #define DEBUG2(msg)\n";
    s += "       #define DEBUG2_LN(msg)\n";
    s += "   #else\n";
    s += "       #define DEBUG2(msg) Serial.print(msg)\n";
    s += "       #define DEBUG2_LN(msg) Serial.println(msg)\n";
    s += "   #endif\n\n";
    s += "#endif\n\n";
    CTree::LiteralH(CCode(s))
}

fn render_keycode_definitions() -> CTree {
    let keycodes = KeyDefs::scancode_table();
    let example = keycodes
        .keys()
        .nth(0)
        .expect("KeyDefs::scancode_table() is empty!")
        .to_owned();

    let keycode_definitions = CTree::Group(
        keycodes
            .iter()
            .map(|(&name, &value)| CTree::Define {
                name: name.to_owned(),
                value: value.to_c(),
            })
            .collect(),
    );

    CTree::Ifndef {
        conditional: example.to_owned(),
        contents: Box::new(keycode_definitions),
    }
}
