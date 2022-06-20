use std::collections::BTreeMap;

use time::*;

use error::Error;
use types::{
    AllData, CEnumVariant, CIdent, CLiteral, CTree, CType, Command, LayerName,
    ModeName, Modifier, Name, SeqType,
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
        let early_name_base = format!("{}_early", file_name_base);

        let use_cpp = true;
        let main_file;
        let early_file;
        let extension;
        if use_cpp {
            main_file = self.render_main(with_message)?.format_to_cpp()?;
            early_file =
                self.render_early_config(with_message)?.format_to_cpp()?;
            extension = "h";
        } else {
            main_file = self.render_main(with_message)?.format_to_rust()?;
            early_file =
                self.render_early_config(with_message)?.format_to_rust()?;
            extension = "rs";
        }

        let mut file_names = Vec::new();
        file_names.push(main_file.save(
            &self.output_directory,
            file_name_base,
            extension,
        )?);

        file_names.push(early_file.save(
            &self.output_directory,
            &early_name_base,
            extension,
        )?);

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
            group.push(CTree::Comment(autogen_message()));
        }
        group.push(CTree::Quote("#pragma once\n".to_string()));

        let mut namespace = Vec::new();
        namespace.extend(self.user_options.render_early());
        namespace.push(KmapBuilder::render_limits());
        namespace.push(self.huffman_table.render_early());
        namespace.push(ModeName::render_c_enum(self.modes.keys()));

        let default_mode_name = ModeName::from("default_mode");
        if !self.modes.contains_key(&default_mode_name) {
            return Err(Error::Missing {
                missing: default_mode_name.into(),
                container: "mode list".into(),
            });
        }
        namespace.push(CTree::ConstDef {
            name: "DEFAULT_MODE".into(),
            value: Box::new(
                CIdent(format!("Mode::{}", default_mode_name)).into(),
            ),
            c_type: CType::custom("Mode"),
        });

        let all_mods: Vec<_> = self
            .modifier_names()
            .into_iter()
            .map(|name| Modifier::new(name))
            .collect();

        namespace.push(Modifier::render_c_enum(all_mods.iter()));
        namespace.push(CTree::ConstDef {
            name: "NUM_MODIFIERS".into(),
            value: Box::new(CTree::Literal(CLiteral(
                all_mods.len().to_string(),
            ))),
            c_type: CType::U8,
        });
        namespace.push(SeqType::render_c_enum(self.sequences.seq_types()));

        group.push(CTree::Namespace {
            name: "conf".into(),
            contents: Box::new(CTree::Group(namespace)),
        });

        Ok(CTree::Group(group))
    }

    fn render_main(&self, with_message: bool) -> Result<CTree, Error> {
        Ok(CTree::Group(vec![
            intro(with_message)?,
            CTree::Namespace {
                name: "conf".into(),
                contents: Box::new(CTree::Group(vec![
                    self.user_options.render(),
                    Command::render_c_enum(self.commands.iter()),
                    self.huffman_table.render()?,
                    self.render_modifiers()?,
                    self.render_modes()?,
                ])),
            },
            make_debug_macros(),
        ]))
    }

    fn render_modes(&self) -> Result<CTree, Error> {
        let mut g = Vec::new();

        g.push(CTree::ConstDef {
            name: "MAX_KEYS_IN_SEQUENCE".into(),
            value: Box::new(
                usize_to_u8(self.sequences.max_seq_length())?.into(),
            ),
            c_type: CType::U8,
        });

        let (tree, layer_struct_names) = self.render_layers()?;
        g.push(tree);

        let mut mode_struct_names = Vec::new();
        for (mode, info) in &self.modes {
            let m = ModeBuilder {
                mode_name: mode,
                info,
                layer_struct_names: &layer_struct_names,
                mod_chords: self.modifier_chords(mode),
                anagram_mask: self.get_anagram_mask(mode),
                chord_spec: self.chord_spec.clone(),
            };
            let (tree, name) = m.render()?;
            g.push(tree);
            mode_struct_names.push(name);
        }

        let num_mode_struct_names = mode_struct_names.len();
        g.push(CTree::ConstDef {
            name: "mode_structs".into(),
            c_type: CType::std_array(
                CType::pointer(CType::custom("ModeStruct")),
                num_mode_struct_names,
            ),
            value: Box::new(CTree::ArrayInit {
                values: mode_struct_names
                    .into_iter()
                    .map(|ident| CTree::Address(ident))
                    .collect(),
            }),
        });
        Ok(CTree::Group(g))
    }

    fn render_layers(
        &self,
    ) -> Result<(CTree, BTreeMap<LayerName, CIdent>), Error> {
        // Render all layer structs as CTrees, and return their names
        let mut layer_struct_names = BTreeMap::new();
        let mut g = Vec::new();
        for (i, (layer_name, chords)) in self.chords.iter().enumerate() {
            let builder = KmapBuilder {
                kmap_nickname: format!("kmap{}", i),
                chord_map: chords,
                seq_maps: &self.sequences,
                huffman_table: &self.huffman_table,
                chord_spec: self.chord_spec.clone(),
            };
            let (tree, layer_struct_name) = builder.render()?;
            g.push(tree);
            layer_struct_names.insert(layer_name.to_owned(), layer_struct_name);
        }
        Ok((CTree::Group(g), layer_struct_names))
    }

    fn render_modifiers(&self) -> Result<CTree, Error> {
        fn to_variants(mod_names: &[Name]) -> Vec<CTree> {
            mod_names
                .iter()
                .map(|name| {
                    CTree::Ident(Modifier::new(name).qualified_enum_variant())
                })
                .collect()
        }

        let mut group = Vec::new();

        group.push(CTree::ConstDef {
            name: "MAX_ANAGRAM_NUM".into(),
            value: Box::new(self.chords.max_anagram_num().into()),
            c_type: CType::U8,
        });

        group.push(CTree::ConstDef {
            name: "word_mods".into(),
            c_type: CType::std_array(
                CType::custom(Modifier::enum_type().to_string()),
                self.word_mods.len(),
            ),
            value: Box::new(CTree::ArrayInit {
                values: to_variants(&self.word_mods),
            }),
        });

        group.push(CTree::ConstDef {
            name: "plain_mods".into(),
            c_type: CType::std_array(
                CType::custom(Modifier::enum_type().to_string()),
                self.plain_mods.len(),
            ),
            value: Box::new(CTree::ArrayInit {
                values: to_variants(&self.plain_mods),
            }),
        });

        group.push(CTree::ConstDef {
            name: "anagram_mods".into(),
            c_type: CType::std_array(
                CType::custom(Modifier::enum_type().to_string()),
                self.anagram_mods.len(),
            ),
            value: Box::new(CTree::ArrayInit {
                values: to_variants(&self.anagram_mods),
            }),
        });

        let anagram_mod_numbers: Vec<CTree> = self
            .get_anagram_mod_numbers()?
            .iter()
            .map(|num| (*num).into())
            .collect();

        group.push(CTree::ConstDef {
            name: "anagram_mod_numbers".into(),
            c_type: CType::std_array(CType::U8, anagram_mod_numbers.len()),
            value: Box::new(CTree::ArrayInit {
                values: anagram_mod_numbers,
            }),
        });

        let plain_mod_codes = self.get_plain_mod_codes()?;
        group.push(CTree::ConstDef {
            name: "plain_mod_keys".into(),
            c_type: CType::std_array(CType::U8, plain_mod_codes.len()),
            value: Box::new(CTree::ArrayInit {
                values: plain_mod_codes,
            }),
        });

        Ok(CTree::Group(group))
    }

    fn get_plain_mod_codes(&self) -> Result<Vec<CTree>, Error> {
        self.plain_mods
            .iter()
            .map(|name| {
                let ident = self
                    .sequences
                    .get_seq_of_any_type(name)?
                    .lone_keypress()?
                    .lone_mod()?;
                Ok(CTree::Cast {
                    value: Box::new(ident.into()),
                    new_type: CType::U8,
                })
            })
            .collect()
    }
}

/// Generate the top of the main auto_config files. If `with_message` is true,
/// add a commented message about when the file was autogenerated.
fn intro(with_message: bool) -> Result<CTree, Error> {
    let mut group = Vec::new();
    if with_message {
        group.push(CTree::Comment(autogen_message()));
    }
    group.push(CTree::Quote("#pragma once\n".to_string()));

    group.push(CTree::Include {
        path: "<Arduino.h>".to_string(),
    });
    group.push(CTree::Include {
        path: "<stdint.h>".to_string(),
    });
    group.push(CTree::Include {
        path: "\"config_types.h\"".to_string(),
    });

    group.push(CTree::Comment(
    "Hacky way to be able to write the type of C-style arrays as `c_array_t<int,\
    42>`, in which the type is entirely before the variable name. Otherwise it's\
    harder to auto-generate the code because the type information is split\
    across either side of the variable name.".to_string()
    ));
    group.push(CTree::Quote(
        "\n#include <type_traits>
template<class T, size_t N>
using c_array_t = T[N];\n\n"
            .to_string(),
    ));

    group.push(CTree::Quote(
        "typedef void (*voidFuncPtr)(void);\n".to_string(),
    ));

    Ok(CTree::Group(group))
}

fn autogen_message() -> String {
    const AUTHOR: &str = "pipit-keyboard";

    let mut s = format!(
        "Automatically generated by {} on:  {}\n",
        AUTHOR,
        now().strftime("%c").unwrap()
    );
    s += "Do not make changes here, they will be overwritten.";
    s
}

fn make_debug_macros() -> CTree {
    // TODO clean up debug macros
    // TODO use Define variant instead
    let mut s = String::new();
    s += "\n#ifdef DEBUG_MESSAGES\n";
    s += "   #define ENABLE_SERIAL_DEBUG\n";
    s += "   #include <Arduino.h>\n";
    s += "   #define DEBUG1(msg) Serial.print(msg)\n";
    s += "   #define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#else\n";
    s += "    #define DEBUG1(msg)\n";
    s += "    #define DEBUG1_LN(msg)\n";
    s += "#endif\n\n";
    CTree::Quote(s)
}
