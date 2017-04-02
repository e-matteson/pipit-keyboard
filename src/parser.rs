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


type Section<'a> = Vec<(usize, Vec<&'a str>)>;

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
        let items_per_line: Vec<_> = format.iter().map(|v| v.len()).collect();
        Parser {
            items_per_line: items_per_line,
            lines_in_block: 1+format.len(), // 1 extra for the top name line
            lines_parsed: 0,
            permutation: make_permutation(ops),
            bytes_in_chord: ops.get_val("num_bytes_in_chord")
                .unwrap_int() as usize,
        }
    }

    // pub fn parse(&mut self, path: &str, chords: &mut HashMap<String, Chord>) {
    //     let all_lines = load_lines(path);
    //     let lines_iter =
    //         &all_lines.iter()
    //         .map(|l| l.trim())
    //         .filter(|l| !l.is_empty() && !l.starts_with(COMMENT_START))
    //         .map(|l| split(l))
    //         .chunks(self.lines_in_block);

    //     let mut pairs: Vec<(String, Chord)> = Vec::new();
    //     for chunk in lines_iter{
    //         let section: Vec<_> = chunk.collect();
    //         pairs.extend(self.parse_section(section));
    //     }
    //     for (key, val) in pairs{
    //         chords.insert(key, val);
    //     }
    // }

    pub fn parse(&mut self, path: &str, chords: &mut HashMap<String, Chord>) {
        let all_lines = load_lines(path);
        let lines_iter =
            &all_lines.iter()
            .enumerate()                     // track line numbers
            .map(|(i, l)| (i, l.trim()))     // trim whitespace
            .filter(|&(i, l)|                // remove comments and empty lines
                    !l.is_empty() && !l.starts_with(COMMENT_START))
            .map(|(i, l)|                    // split on whitespace
                 (i, split(l)))
            .chunks(self.lines_in_block);    // chunk into sections

        let mut pairs: Vec<(String, Chord)> = Vec::new();
        for chunk in lines_iter{
            let section: Vec<_> = chunk.collect();
            pairs.extend(self.parse_section(section));
        }
        for (key, val) in pairs{
            chords.insert(key, val);
        }
    }

    fn parse_section(&mut self, section: Section) -> Vec<(String, Chord)>{
        let (names, blocks) = self.get_block_strings(section);
        let mut pairs: Vec<(String, Chord)> = Vec::new();
        for (block, name) in blocks.iter().zip(names.iter()){
            let chord = self.to_firmware_order(block.chars()
                                               .map(|c| c != UNPRESSED_CHAR)
                                               .collect());
            pairs.push(((*name).to_owned(), chord));
        }
        pairs
    }

    fn get_block_strings(&mut self, section: Section) -> (Vec<String>, Vec<String>) {

        let (line_nums, lines): (Vec<_>, Vec<_>) = section.into_iter().unzip();
        if lines.len() != self.lines_in_block {
            self.panic_syntax_error(*line_nums.last().unwrap());
        }

        let names: Vec<String> = lines[0].iter().cloned().map(|s| s.to_owned()).collect();
        let body: Vec<_> = lines[1..].iter().map(|l| l.join("")).collect();
        let num_blocks = names.len();

        // accumulate one string for each block
        let mut strings: Vec<String> = vec![String::new() ; num_blocks];

        // store index into each line
        let mut indices: Vec<usize> = vec![0 ; body.len()];

        for l in 0..body.len(){
            let num_items = self.items_per_line[l];
            if body[l].len() != num_items * num_blocks {
                self.panic_syntax_error(line_nums[l]);
            }
            for b in 0..num_blocks {
                let end = indices[l]+num_items;
                strings[b] += &body[l][indices[l]..end];
                indices[l] = end;
            }
        }
        (names, strings)
    }

    fn panic_syntax_error(&self, line_num: usize){
        panic!(format!("syntax error in kmap file near line {}", line_num));
    }

    fn to_firmware_order(&self, vector: Vec<bool>) -> Chord {
        // Convert a vector with switches given in kmap order to a vector in
        //  firmware order.
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
    let mut lines: Vec<String> =
        buf.lines()
        .map(|w| w.unwrap())
        .collect();
    lines.insert(0, "".to_owned()); // to make 0-indexed line numbering work
    if lines.is_empty(){
        panic!("File is empty: {}", path);
    }
    lines
}

fn split(line: &str) -> Vec<&str>{
    let words: Vec<_> = line.split_whitespace().collect();
    words
}
