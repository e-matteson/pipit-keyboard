/// For parsing kmap files

use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::HashMap;
use std::iter::Peekable;
use itertools::{Itertools, multizip};
use key_types::*;

use options::*;

const COMMENT_START: &str = "#";
const UNPRESSED_CHAR: char = '.';

pub struct Parser {
    items_per_line: Vec<usize>,
    lines_in_block: usize,
    lines_parsed: usize,
    permutation: Vec<usize>,
    bytes_in_chord: usize,
}

impl Parser {
    pub fn new(ops: &Options) -> Parser {
        let format = ops.get_val("kmap_format").unwrap_vec_kmap();
        let bytes_in_chord = ops.get_val("num_bytes_in_chord").unwrap_int();

        let lines_in_block = 1+format.len(); // 1 extra for the top name line
        let items_per_line: Vec<_> = format.iter().map(|v| v.len()).collect();
        Parser {
            items_per_line: items_per_line,
            lines_in_block: lines_in_block,
            lines_parsed: 0,
            permutation: make_permutation(ops),
            bytes_in_chord: bytes_in_chord,
        }
    }

    pub fn parse(&mut self, path: &str, chords: &mut HashMap<String, Chord>) {
        let all_lines = load_lines(path);
        let lines_iter =
            &all_lines.iter()
            .map(|l| l.trim())
            .filter(|l| !l.is_empty() && !l.starts_with(COMMENT_START))
            .map(|l| split(l))
            .chunks(self.lines_in_block);

        let mut pairs: Vec<(String, Chord)> = Vec::new();
        for chunk in lines_iter{
            let section: Vec<_> = chunk.collect();
            pairs.extend(self.parse_section(section));
        }
        for (key, val) in pairs{
            chords.insert(key, val);
        }
    }

    fn parse_section(&mut self, section: Vec<Vec<&str>>) -> Vec<(String, Chord)>{
        let blocks = self.get_block_strings(&section);
        let mut pairs: Vec<(String, Chord)> = Vec::new();
        for (block, name) in blocks.iter().zip(section[0].iter()){
            let chord = self.to_firmware_order(block.chars()
                                               .map(|c| c != UNPRESSED_CHAR)
                                               .collect());
            pairs.push(((*name).to_owned(), chord));
        }
        pairs
    }

    fn get_block_strings(&mut self, section: &Vec<Vec<&str>>) -> Vec<String>{
        self.lines_parsed += section.len();
        if section.len() != self.lines_in_block {
            self.panic_syntax_error();
        }

        let num_blocks = section[0].len();
        let lines: Vec<_> = section[1..].iter().map(|l| l.join("")).collect();
        let mut strings: Vec<String> = vec!["".to_owned() ; num_blocks];
        let mut indices: Vec<usize> = vec![0 ; lines.len()];
        for l in 0..lines.len(){
            let num_items = self.items_per_line[l];
            if lines[l].len() % num_items != 0 {
                self.panic_syntax_error();
            }
            for b in 0..num_blocks{
                let end = indices[l]+num_items;
                strings[b] += &lines[l][indices[l]..end];
                indices[l] = end;
            }
        }
        strings
    }

    fn panic_syntax_error(&self){
        // TODO the line number isn't accurate because we filter comments & blanks
        panic!(format!("syntax error in kmap file"));
        // panic!(format!("syntax error in kmap file near line {}",
        //                self.lines_parsed));
    }

    fn to_firmware_order(&self, vector: Vec<bool>) -> Chord {
        let mut chord: Chord = vec![false; 8*self.bytes_in_chord];
        assert_eq!(vector.len(), self.permutation.len());
        for i in 0..vector.len(){
            chord[self.permutation[i]] = vector[i];
        }
        chord
    }
}

fn make_permutation(ops: &Options) -> Vec<usize> {
    let kmap_order = make_kmap_order(ops);
    let firmware_order = make_firmware_order(ops);
    let mut permutation: Vec<usize> = Vec::new();
    for pos in kmap_order{
        permutation.push(
            firmware_order.iter()
                .position(|p| *p == pos)
                .expect(&format!("Not found in firmware_order: {:?}", pos))
        )
    }
    // println!("{:?}, {}", permutation, permutation.len());
    permutation
}

fn make_kmap_order(ops: &Options) -> Vec<SwitchPos> {
    let format = ops.get_val("kmap_format").unwrap_vec_kmap();
    // let format = match ops.get_val("kmap_format") {
    //     &OpVal::VecKmap(ref v) => v,
    //     _ => panic!("expected VecKmap"),
    // };
    let mut order: Vec<SwitchPos> = Vec::new();
    for line in format.iter(){
        order.extend_from_slice(line);
    }
    order
}

fn make_firmware_order(ops: &Options) -> Vec<(SwitchPos)> {
    // must match the algorithm used in the firmware"s scanMatrix()!
    let mut order: Vec<SwitchPos> = Vec::new();
    let row_pins = ops.get_val("row_pins").unwrap_vec();
    let column_pins = ops.get_val("column_pins").unwrap_vec();
    for c in column_pins {
        for r in row_pins {
            order.push(SwitchPos::new(*r, *c));
        }
    }
    order
}


fn load_lines(path: &str) -> Vec<String> {
    let file = File::open(path).expect("failed to open words file");
    let buf = BufReader::new(file);
    let lines: Vec<String> =
        buf.lines()
        .map(|w| w.unwrap())
        .collect();

    if lines.is_empty(){
        panic!("File is empty: {}", path);
    }
    lines
}

fn split(line: &str) -> Vec<&str>{
    let words: Vec<_> = line.split_whitespace().collect();
    words
}
