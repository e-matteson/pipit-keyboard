/// For parsing kmap files to get chords

use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::BTreeMap;
use itertools::Itertools;

use types::{Chord, KmapFormat, KmapPath, Name};

use types::errors::*;


const COMMENT_START: char = '#';
const UNPRESSED_CHAR: char = '.';
const BLANK_MAPPING: &str = "blank_mapping";

type Section<'a> = Vec<(usize, Vec<&'a str>)>;

pub struct KmapParser {
    items_per_line: Vec<usize>,
    lines_in_block: usize,
}

////////////////////////////////////////////////////////////////////////////////

impl KmapParser {
    pub fn new(format: &KmapFormat) -> Result<KmapParser> {
        let items_per_line: Vec<_> = format.0.iter().map(|v| v.len()).collect();
        Ok(KmapParser {
            items_per_line: items_per_line,
            lines_in_block: 1 + format.0.len(), // 1 extra for the top name line
        })
    }

    pub fn parse(&mut self, path: &KmapPath) -> Result<BTreeMap<Name, Chord>> {
        let all_lines = load_lines(path)?;
        let lines_iter = &all_lines.iter()
            .enumerate()                     // track line numbers
            .map(|(i, l)| (i, l.trim()))     // trim whitespace
            .filter(|&(_, l)|                // remove comments and empty lines
                    !l.is_empty()
                    && !l.starts_with(COMMENT_START))
            .map(|(i, l)|                    // split on whitespace
                 (i, split(l)))
            .chunks(self.lines_in_block); // chunk into sections

        let mut pairs: Vec<(Name, Chord)> = Vec::new();
        for chunk in lines_iter {
            let section: Vec<_> = chunk.collect();
            pairs.extend(self.parse_section(section)?);
        }
        to_chord_map(pairs)
    }

    fn parse_section(
        &mut self,
        section: Section,
    ) -> Result<Vec<(Name, Chord)>> {
        let (names, blocks) = self.get_block_strings(section)?;
        let mut pairs: Vec<(Name, Chord)> = Vec::new();
        for (block, name) in blocks.iter().zip(names.iter()) {
            let chord = Chord::from_vec(
                block.chars().map(|c| c != UNPRESSED_CHAR).collect(),
            );
            pairs.push(((*name).clone(), chord));
        }
        Ok(pairs)
    }

    fn get_block_strings(
        &mut self,
        section: Section,
    ) -> Result<(Vec<Name>, Vec<String>)> {
        let (line_nums, lines): (Vec<_>, Vec<_>) = section.into_iter().unzip();
        if lines.len() != self.lines_in_block {
            bail!(ErrorKind::KmapSyntax(last(&line_nums)));
        }

        let names: Vec<_> =
            lines[0].iter().cloned().map(|s| Name(s.into())).collect();
        let body: Vec<_> = lines[1..].iter().map(|l| l.join("")).collect();

        let num_blocks = names.len();

        // accumulate one string for each block
        let mut strings = vec![String::new(); num_blocks];

        // store index into each line
        let mut indices: Vec<usize> = vec![0; body.len()];

        for l in 0..body.len() {
            let num_items = self.items_per_line[l];
            if body[l].len() != num_items * num_blocks {
                bail!(ErrorKind::KmapSyntax(line_nums[l]));
            }
            for s in strings.iter_mut().take(num_blocks) {
                let end = indices[l] + num_items;
                *s += &body[l][indices[l]..end];
                indices[l] = end;
            }
        }
        Ok((names, strings))
    }
}


fn load_lines(path: &KmapPath) -> Result<Vec<String>> {
    // TODO share file reading code?
    let file = File::open(path.0.clone())?;
    let buf = BufReader::new(file);
    let mut lines: Vec<String> = buf.lines().map(|w| w.unwrap()).collect();
    lines.insert(0, "".into()); // to make 0-indexed line numbering work
    if lines.is_empty() {
        bail!("file is empty");
    }
    Ok(lines)
}

fn split(line: &str) -> Vec<&str> {
    let words: Vec<_> = line.split_whitespace().collect();
    words
}

fn last(line_nums: &[usize]) -> usize {
    *line_nums.last().unwrap()
}

fn to_chord_map(pairs: Vec<(Name, Chord)>) -> Result<BTreeMap<Name, Chord>> {
    let blank_mapping = Name::from(BLANK_MAPPING);
    let mut map = BTreeMap::new();
    for (name, chord) in pairs {
        if name == blank_mapping {
            continue;
        }
        if map.insert(name.clone(), chord).is_some() {
            bail!("duplicate chords for: '{}'", name);
        }
    }
    Ok(map)
}
