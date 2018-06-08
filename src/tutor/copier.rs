use std::collections::HashMap;

use cursive::Printer;
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::theme::ColorStyle;

use unicode_segmentation::UnicodeSegmentation;

use types::errors::BadValueErr;
use failure::Error;
use tutor::{grapheme_slice, offset, LabeledChord, PrevCharStatus, SlideEntry,
            SlideLine, State};

#[derive(Debug, Clone)]
pub struct Copier {
    num_chars: usize,
    point_marker: String,
    point_offset: usize,
    line: CopierLine,
}

#[derive(Debug, Clone)]
struct CopierLine {
    expected: String,
    actual: String,
    index: usize,
    show_errors: bool,
    hint_map: HashMap<usize, LabeledChord>,
    show_hints_within_words: bool,
}

impl Copier {
    pub fn new(num_chars: usize) -> Copier {
        let point_offset = (num_chars + 1) / 2. as usize;
        Copier {
            num_chars: num_chars,
            point_offset: point_offset,
            point_marker: "▼".into(),
            line: CopierLine::default(),
        }
    }

    pub fn needs_hint(&self, letter: &str) -> bool {
        !State::is_learned(letter).unwrap_or(false)
    }

    pub fn next_hint(&mut self) -> Result<Option<LabeledChord>, Error> {
        let word_edge_hint = self.line.hint_map.get(&self.line.index);
        if word_edge_hint.is_some() {
            return Ok(word_edge_hint.cloned());
        }

        if self.at_end_of_line() {
            return Ok(LabeledChord::from_letter("\n"));
        }

        if !self.line.show_hints_within_words {
            return Ok(None);
        }

        let next_letter = self.expected_next()
            .expect("failed to get next char, did we check for end of line?");

        let letter_hint = if self.needs_hint(&next_letter) {
            LabeledChord::from_letter(&next_letter)
        } else {
            None
        };

        Ok(letter_hint)
    }

    /// Offset of the most recently typed character
    fn prev_offset(&self) -> usize {
        self.point_offset - 1
    }

    fn next_offset(&self) -> usize {
        self.point_offset
    }

    fn expected_next(&self) -> Option<String> {
        self.expected_at_offset(self.next_offset())
        // .expect("failed to get next expected char")
    }

    fn expected_prev(&self) -> Option<String> {
        self.expected_at_offset(self.prev_offset())
        // .expect("failed to get prev expected char")
    }

    fn actual_prev(&self) -> String {
        self.actual_at_offset(self.prev_offset())
            .expect("failed to get prev actual char")
    }

    pub fn type_char(&mut self, character: char) -> PrevCharStatus {
        let expected = self.expected_next();
        let actual = character.to_string();
        let status = self.prev_char_status(&actual, &expected);

        if status.is_correct() || !State::freeze_on_error() {
            // make the typed char appear
            self.line.actual += &actual;
            self.line.index += 1;
        }
        if let Some(e) = &expected {
            State::update_learn_state(e.clone(), status.is_correct());
        }
        status
    }

    fn prev_char_status(
        &self,
        actual: &str,
        expected: &Option<String>,
    ) -> PrevCharStatus {
        let correct = expected.as_ref().map(|e| e == &actual).unwrap_or(false);
        if correct || !self.line.show_errors {
            PrevCharStatus::Correct
        } else {
            PrevCharStatus::Incorrect(LabeledChord::from_letter(&actual))
        }
    }

    pub fn type_backspace(&mut self) -> PrevCharStatus {
        if self.line.index > 0 {
            self.line.actual.pop();
            self.line.index -= 1;
            self.prev_char_status(&self.actual_prev(), &self.expected_prev())
        } else {
            PrevCharStatus::Correct
        }
    }

    pub fn start_line(&mut self, line: &SlideLine) -> Result<(), Error> {
        self.line = CopierLine::from(line, self.extra_spaces())?;
        Ok(())
    }

    pub fn at_end_of_line(&self) -> bool {
        self.line.actual.graphemes(true).count()
            >= self.line.expected.graphemes(true).count()
    }

    fn extra_spaces(&self) -> usize {
        self.point_offset
    }

    fn text_padding(&self) -> Vec2 {
        let x = offset(self.num_chars, self.size().x);
        Vec2::new(x, 0)
    }

    pub fn size(&self) -> Vec2 {
        Vec2::new(self.num_chars, 3)
    }

    pub fn net_words(&self) -> f64 {
        const CHARS_PER_WORD: f64 = 5.;
        let total_chars = (self.line.expected.graphemes(true).count()
            - self.extra_spaces()) as f64;

        // this will ignore anything typed past the end of the line
        let wrong_chars: f64 = self.line
            .actual
            .graphemes(true)
            .zip(self.line.expected.graphemes(true))
            .map(|(actual, expected)| if actual == expected { 0. } else { 1. })
            .sum();

        // ensure the corrected wpm won't be negative
        f64::max(0., (total_chars / CHARS_PER_WORD) - wrong_chars)
    }

    fn actual_at_offset(&self, offset: usize) -> Result<String, Error> {
        Ok(self.char_at_offset(&self.line.actual, offset)
            .ok_or_else(|| BadValueErr {
                thing: "character offset".into(),
                value: offset.to_string(),
            })?)
    }

    fn expected_at_offset(&self, offset: usize) -> Option<String> {
        self.char_at_offset(&self.line.expected, offset)
    }

    fn char_at_offset(&self, string: &str, offset: usize) -> Option<String> {
        grapheme_slice(string, self.start(), self.end())
            .nth(offset)
            .map(|s| s.to_owned())
    }

    fn start(&self) -> usize {
        self.line.index
    }

    fn end(&self) -> usize {
        self.line.index + self.num_chars
    }
}

impl View for Copier {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        let pad = self.text_padding().x;

        printer.with_color(ColorStyle::title_secondary(), |printer| {
            printer.print((self.point_offset + pad, 0), &self.point_marker);
        });

        let expected: Vec<_> =
            grapheme_slice(&self.line.expected, self.start(), self.end())
                .collect();

        for (i, letter) in expected.iter().enumerate() {
            printer.with_color(ColorStyle::primary(), |printer| {
                printer.print((i + pad, 1), letter);
            })
        }

        let actual =
            grapheme_slice(&self.line.actual, self.start(), self.end());

        for (i, letter) in actual.enumerate() {
            printer.with_color(
                get_style(letter, expected.get(i).cloned()),
                |printer| printer.print((i + pad, 2), letter),
            );
        }
    }
}

impl CopierLine {
    fn from(
        line: &SlideLine,
        extra_spaces: usize,
    ) -> Result<CopierLine, Error> {
        let (entries, text) = line.to_entries()?;

        let pad = " ".repeat(extra_spaces);
        let expected = pad.clone() + &text;
        let mut actual = String::from(pad);
        actual.reserve(expected.len());
        Ok(CopierLine {
            expected: expected,
            actual: actual,
            index: 0,
            show_errors: line.show_errors(),
            hint_map: make_hint_map(&entries),
            show_hints_within_words: !line.has_length_overrides(),
        })
    }
}

impl Default for CopierLine {
    fn default() -> CopierLine {
        CopierLine {
            expected: String::new(),
            actual: String::new(),
            index: 0,
            show_errors: true,
            hint_map: HashMap::new(),
            show_hints_within_words: true,
        }
    }
}

fn get_style(actual_char: &str, expected_char: Option<&str>) -> ColorStyle {
    if let Some(expected_char) = expected_char {
        if actual_char == expected_char {
            // correct
            ColorStyle::tertiary()
        } else {
            // incorrect
            ColorStyle::secondary()
        }
    } else {
        // incorrect
        ColorStyle::secondary()
    }
}

fn make_hint_map(entries: &[SlideEntry]) -> HashMap<usize, LabeledChord> {
    let mut position = 0;
    let mut map = HashMap::new();
    for entry in entries {
        map.insert(position, entry.to_labeled_chord());
        position += entry.len();
    }
    map
}
