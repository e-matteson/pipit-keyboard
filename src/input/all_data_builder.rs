use std::collections::{BTreeMap, BTreeSet};
use std::path::PathBuf;

use serde_yaml;

use input::Settings;

use error::{Error, ResultExt};
use types::{
    AllChordMaps, AllData, AllSeqMaps, CCode, CEnumVariant, Chord, Command,
    HuffmanTable, KeyDefs, KeyPress, KmapOrder, LayerInfo, LayerName, Name,
    SeqMap, SeqType, Sequence, SpellingTable, Validate, Wordlike,
};
use util::read_file;

/// This handles all the details of building an AllData struct from
/// configuration files. It loads sequences and chords, generates word chords,
/// generates huffman encodings, and so on.
pub fn load_all_data(settings_path: &PathBuf) -> Result<AllData, Error> {
    let settings: Settings = serde_yaml::from_str(&read_file(settings_path)?)?;
    settings.validate()?;
    settings.validate_layer_list()?;

    let mut chords = load_chords(&settings).context("Failed to load chords")?;

    let mut sequences = AllSeqMaps::default();
    sequences
        .insert_map(SeqMap::from(settings.macros.clone()), SeqType::Macro)?;
    let mut plain_seqs = SeqMap::from(settings.plain_keys.clone());
    plain_seqs.append(
        load_plain_mods(&settings).context("Failed to load plain mods")?,
    )?;
    sequences.insert_map(plain_seqs, SeqType::Plain)?;

    let spellings = make_spelling_table(&settings)
        .context("Failed to make spelling table")?;

    load_words_and_snippets(&settings, &spellings, &mut chords, &mut sequences)
        .context("Failed to load words and snippets")?;

    let commands = load_commands(&settings, &mut sequences)
        .context("Failed to load commands")?;

    let huffman_table = HuffmanTable::new(sequences.all_keypresses())
        .context("Failed to make table of huffman encodings")?;

    Ok(AllData {
        huffman_table,
        commands,
        chords,
        sequences,
        word_mods: settings.word_modifiers.clone(),
        anagram_mods: settings.anagram_modifiers.clone(),
        plain_mods: settings.plain_modifiers.keys().cloned().collect(),
        layers: settings.layers.clone(),
        modes: settings.modes.clone(),
        spellings,
        chord_spec: settings.options.chord_spec()?,
        output_directory: settings.options.output_directory.clone(),
        board: settings.options.board_name.clone(),
        user_options: settings.options,
    })
}

fn load_chords(settings: &Settings) -> Result<AllChordMaps, Error> {
    let mut chords = AllChordMaps::default();
    for (layer_name, layer_info) in &settings.layers {
        if let LayerInfo::KmapLayer { kmap_file } = layer_info {
            let named_chords =
                kmap_file.read(&settings.options.kmap_format).with_context(
                    || format!("Failed to load kmap file: '{}'", kmap_file),
                )?;

            chords.insert_map(named_chords, layer_name.to_owned())?;
        }
    }
    Ok(chords)
}

fn load_plain_mods(settings: &Settings) -> Result<SeqMap, Error> {
    settings
        .plain_modifiers
        .iter()
        .map(|(name, keypress)| {
            KeyDefs::ensure_plain_mod(&keypress).with_context(|| {
                format!("Invalid plain modifier keypress for {}", name)
            })
        })
        .collect::<Result<Vec<_>, Error>>()?;

    Ok(SeqMap::from(settings.plain_modifiers.clone()))
}

// Requires all the SeqType::Plain sequences to have been loaded already.
// TODO how to enforce that invariant?
// fn make_spelling_table(plain_seqs: &SeqMap) -> Result<SpellingTable, Error> {
fn make_spelling_table(settings: &Settings) -> Result<SpellingTable, Error> {
    let mut table = BTreeMap::new();
    for (name, keypress) in settings
        .plain_keys
        .iter()
        .chain(settings.plain_modifiers.iter())
    {
        if let Some(spelling) = KeyDefs::spelling_from_keypress(keypress)? {
            table.insert(spelling, name.to_owned());
        }
    }
    Ok(SpellingTable(table))
}

fn load_words_and_snippets(
    settings: &Settings,
    spellings: &SpellingTable,
    destination_chords: &mut AllChordMaps,
    sequences: &mut AllSeqMaps,
) -> Result<(), Error> {
    for (layer_name, layer_info) in &settings.layers {
        match layer_info {
            LayerInfo::KmapLayer { .. } => continue,
            LayerInfo::WordLayer {
                word_list_name,
                kmap_file_for_chord_generation: kmap_file,
            } => {
                let word_list = settings
                    .word_lists
                    .get(word_list_name)
                    .ok_or_else(|| Error::LookupErr {
                        key: word_list_name.to_string(),
                        container: "word lists".into(),
                    })?;
                let source_chords = kmap_file
                    .read(&settings.options.kmap_format)
                    .with_context(|| {
                        format!("Failed to load kmap file: '{}'", kmap_file)
                    })?;
                for word_info in word_list {
                    add_wordlike(
                        word_info,
                        layer_name,
                        word_list_name,
                        spellings,
                        &source_chords,
                        destination_chords,
                        sequences,
                    )
                    .with_context(|| {
                        format!("Failed to add word: {}", word_info.word)
                    })?;
                }
            }

            LayerInfo::SnippetLayer {
                snippet_list_name,
                kmap_file_for_chord_generation: kmap_file,
            } => {
                let snippets = settings
                    .snippets
                    .get(snippet_list_name)
                    .ok_or_else(|| Error::LookupErr {
                        key: snippet_list_name.to_string(),
                        container: "snippet lists".into(),
                    })?;

                let source_chords = kmap_file
                    .read(&settings.options.kmap_format)
                    .with_context(|| {
                        format!("Failed to load kmap file: '{}'", kmap_file)
                    })?;

                for snippet_info in snippets {
                    add_wordlike(
                        snippet_info,
                        layer_name,
                        snippet_list_name,
                        spellings,
                        &source_chords,
                        destination_chords,
                        sequences,
                    )
                    .with_context(|| {
                        format!(
                            "Failed to add snippet: {}",
                            snippet_info.snippet
                        )
                    })?;
                }
            }
        }
    }
    Ok(())
}

fn add_wordlike<T>(
    wordlike: &T,
    layer_name: &LayerName,
    wordlike_list_name: &T::WordlikeListName,
    spellings: &SpellingTable,
    source_chords: &BTreeMap<Name, Chord<KmapOrder>>,
    destination_chords: &mut AllChordMaps,
    sequences: &mut AllSeqMaps,
) -> Result<(), Error>
where
    T: Wordlike,
{
    let name = wordlike.name(wordlike_list_name);
    sequences.insert(name.clone(), wordlike.sequence()?, T::seq_type())?;

    let chord = make_wordlike_chord(wordlike, spellings, source_chords)
        .with_context(|| format!("Failed to make chord for '{}'", name))?;
    destination_chords.insert(name, chord, layer_name.clone())
}

fn make_wordlike_chord<T>(
    wordlike: &T,
    spelling_table: &SpellingTable,
    chords: &BTreeMap<Name, Chord<KmapOrder>>,
) -> Result<Chord<KmapOrder>, Error>
where
    T: Wordlike,
{
    let mut names = Vec::new();
    for spelling in wordlike.chord_spellings()? {
        names.extend(spelling_table.get_checked(spelling)?)
    }

    let mut letter_chords = names.iter().map(|name| {
        chords.get(name).ok_or_else(|| Error::LookupErr {
            key: name.into(),
            container: "chord map".into(),
        })
    });

    // TODO better static union method?
    let mut word_chord: Chord<KmapOrder> = letter_chords
        .next()
        .ok_or_else(|| {
            Error::Empty(
                "set of letter chords for constructing relative chord".into(),
            )
        })??
        .to_owned();
    for c in letter_chords {
        word_chord.union_mut(c?)?;
    }
    word_chord.anagram_num = wordlike.anagram_num();
    Ok(word_chord)
}

/// In addition to loading commands from the settings file, automatically
/// create command bindings for switching to every mode (eg.
/// "command_switch_to_default_mode"). This means you don't need to manually
/// list mode-switching commands in the settings file, or more importantly,
/// in the firmware's `Command` enum or `Pipit::doCommand()`. Otherwise,
/// deleting modes in the settings file would cause a firmware compilation
/// error, because `doCommand()` would reference an unknown `Command`
/// variant. Instead, we store mode-switching commands in the lookup using a
/// single `Command::command_switch_to` variant, followed by a mode
/// argument.
fn load_commands(
    settings: &Settings,
    sequences: &mut AllSeqMaps,
) -> Result<Vec<Command>, Error> {
    // TODO cleanup
    let mut variants = BTreeSet::new();
    for normal_command in settings.commands.clone() {
        variants.insert(normal_command.clone());
        add_command(
            normal_command.name().to_owned(),
            normal_command,
            &[],
            sequences,
        )
        .context("Failed to add command")?;
    }

    let base_name = "command_switch_to";
    let variant = Command(base_name.into());
    variants.insert(variant.clone());
    for mode in settings.mode_names() {
        let name = Name::from(format!("{}_{}", base_name, mode));
        add_command(
            name,
            variant.clone(),
            &[mode.qualified_enum_variant()],
            sequences,
        )
        .context("Failed to add mode-switching command")?;
    }

    Ok(variants.into_iter().collect())
}

/// Create a sequence for this command. The command variants will be
/// collected separately.
// TODO don't take sequences? just return stuff
fn add_command(
    name: Name,
    variant: Command,
    args: &[CCode],
    sequences: &mut AllSeqMaps,
) -> Result<(), Error> {
    // Commands don't have actual key sequences, just a byte containing an
    // enum value, and maybe some extra bytes as argument. But we'll
    // store them as Sequences for convenience.
    let mut fake_seq: Sequence =
        KeyPress::new_fake(variant.qualified_enum_variant()).into();
    for arg in args {
        fake_seq.push(KeyPress::new_fake(arg.to_owned()))
    }

    sequences.insert(name, fake_seq, SeqType::Command)
}
