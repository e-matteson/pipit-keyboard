///! For parsing kmap files to get chords
use std::collections::BTreeMap;
use std::fs::File;
use std::io::{BufRead, BufReader};

use error::{Error, ResultExt};
use types::{Chord, KmapFormat, KmapOrder, KmapPath, Name};

const COMMENT_START: char = '#';
const UNPRESSED_CHAR: char = '.';
const PRESSED_CHAR: char = '*';
const BLANK_MAPPING: &str = "blank_mapping";

struct Section {
    line_num: usize,
    lines: Vec<String>,
    names: Vec<Name>,
    items_per_line: Vec<usize>,
}

////////////////////////////////////////////////////////////////////////////////

impl KmapPath {
    pub fn read(
        &self,
        format: &KmapFormat,
    ) -> Result<BTreeMap<Name, Chord<KmapOrder>>, Error> {
        let lines = self
            .load_lines()?
            .into_iter()
            .enumerate() // track line numbers
            .map(|(i, l)|                   // trim whitespace
                 (i, l.trim().to_owned()))
            .filter(|&(_, ref l)|           // remove comments and empty lines
                    !is_ignored(l))
            .map(|(i, l)| check_ascii(i, l))
            .collect::<Result<Vec<_>, Error>>()?;

        let mut mappings = Vec::new();
        for chunk in lines.chunks(format.block_length()) {
            let section = Section::new(chunk, format)?;
            mappings.extend(section.mappings()?);
        }
        to_chord_map(mappings)
    }

    fn load_lines(&self) -> Result<Vec<String>, Error> {
        let buf = BufReader::new(File::open(&self.0)?);
        let mut lines: Vec<_> = buf.lines().map(|w| w.unwrap()).collect();
        if lines.is_empty() {
            return Err(Error::Empty("kmap file".to_owned()));
        }
        lines.insert(0, String::new()); // to make 0-indexed line numbering work
        Ok(lines)
    }
}

impl Section {
    fn new(
        input: &[(usize, String)],
        format: &KmapFormat,
    ) -> Result<Self, Error> {
        let (line_nums, all_lines): (Vec<_>, Vec<_>) =
            input.iter().cloned().unzip();

        if all_lines.len() != format.block_length() {
            return Err(Error::KmapSyntaxErr {
                line: *line_nums.last().unwrap(),
            })
            .with_context(|| {
                format!(
                    "According to the kmap_format setting, there should be {} \
                     lines per block. {} lines were found.",
                    format.block_length(),
                    all_lines.len()
                )
            });
        }

        Ok(Self {
            names: all_lines[0].split_whitespace().map(|s| s.into()).collect(),
            lines: all_lines.into_iter().skip(1).collect(),
            line_num: line_nums[0],
            items_per_line: format.switches_per_line(),
        })
    }

    /// Get all Name -> Chord mappings from the section.
    fn mappings(self) -> Result<Vec<(Name, Chord<KmapOrder>)>, Error> {
        let chords = self.chords()?;
        Ok(self.names.into_iter().zip(chords.into_iter()).collect())
    }

    /// Extract the Chords from the section, in the same order as their
    /// names.
    fn chords(&self) -> Result<Vec<Chord<KmapOrder>>, Error> {
        let mut chords = Vec::new();
        let mut switch_chunks = self.switch_chunks()?;

        for _ in 0..self.num_blocks() {
            let mut chord = Vec::new();
            for line in &mut switch_chunks {
                chord.extend(
                    line.pop().expect("wrong line length, check failed"),
                );
            }
            chords.push(Chord::from_vec(chord).unwrap());
        }
        Ok(chords)
    }

    /// Convert each line of switch-characters to bools, and chunk them by
    /// block. Reverse the order of chunks within the line, so that we can use
    /// pop() to get them back in the same order as the names.
    fn switch_chunks(&self) -> Result<Vec<Vec<Vec<bool>>>, Error> {
        let mut switch_chunks = Vec::new();
        for i in 0..self.lines.len() {
            let mut line = self.lines[i].to_owned();

            // Remove meaningless whitespace between switch characters
            line.retain(|c| !char::is_whitespace(c));

            // Convert from characters to bools, meaning pressed or unpressed.
            let switch_line = line
                .chars()
                .map(|c| self.char_to_switch(c, i + 1))
                .collect::<Result<Vec<_>, Error>>()?;

            self.check_line_length(&switch_line, i)?;

            // Put each block's switches in a different chunk, and reverse
            // chunk order for later popping.
            let chunks: Vec<Vec<_>> = switch_line
                .chunks(self.items_per_line[i])
                .map(|v| v.to_owned())
                .rev()
                .collect();

            switch_chunks.push(chunks);
        }
        Ok(switch_chunks)
    }

    /// If the line length is wrong, produce a syntax error.
    fn check_line_length(
        &self,
        line: &[bool],
        index: usize,
    ) -> Result<(), Error> {
        if line.len() != self.items_per_line[index] * self.num_blocks() {
            return Err(self.error_at(index + 1).with_context(|| {
                format!(
                "Wrong number of switches on line. Expected {} chords in this \
                 block, each with {} switches on this line. Is kmap_format \
                 correct for this file?",
                self.num_blocks(),
                self.items_per_line[index]
            )
            }));
        }
        Ok(())
    }

    /// Produce a syntax error at a line with the given offset from the
    /// first line of the section.
    fn error_at(&self, line_offset: usize) -> Error {
        Error::KmapSyntaxErr {
            line: self.line_num + line_offset,
        }
    }

    fn num_blocks(&self) -> usize {
        self.names.len()
    }

    fn char_to_switch(
        &self,
        c: char,
        line_index: usize,
    ) -> Result<bool, Error> {
        if c == PRESSED_CHAR {
            Ok(true)
        } else if c == UNPRESSED_CHAR {
            Ok(false)
        } else {
            Err(self.error_at(line_index).with_context(|| {
                format!(
                    "Expected '{}', '{}', or whitespace. Found '{}'",
                    UNPRESSED_CHAR, PRESSED_CHAR, c
                )
            }))
        }
    }
}

fn to_chord_map(
    mappings: Vec<(Name, Chord<KmapOrder>)>,
) -> Result<BTreeMap<Name, Chord<KmapOrder>>, Error> {
    // let blank_mapping = Name::from(BLANK_MAPPING);
    let mut map = BTreeMap::new();
    for (name, chord) in mappings {
        if name.0 == BLANK_MAPPING {
            continue;
        }
        if map.insert(name.clone(), chord).is_some() {
            return Err(Error::ConflictErr {
                key: name.to_string(),
                container: "chord names".into(),
            })
            .context("Duplicate chord names in kmap file");
        }
    }
    Ok(map)
}

fn is_ignored(line: &str) -> bool {
    line.is_empty() || line.starts_with(COMMENT_START)
}

fn check_ascii(
    line_number: usize,
    line: String,
) -> Result<(usize, String), Error> {
    if line.is_ascii() {
        Ok((line_number, line))
    } else {
        Err(Error::KmapSyntaxErr { line: line_number })
            .context("Non-ascii characters are not allowed outside of comments")
    }
}
