use std::collections::HashMap;

use cursive::Printer;
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::theme::ColorStyle;

use unicode_segmentation::UnicodeSegmentation;

use types::errors::BadValueErr;
use failure::{Error, ResultExt};

use tutor::utils::{grapheme_slice, offset, LabeledChord, LastChar, SlideEntry,
                   SlideLine};

pub struct Copier {
    was_backspace_typed_last: bool,
    expected: String,
    actual: String,
    num_chars: usize,
    point_marker: String,
    point_offset: usize,
    index: usize,
    learned_keys: HashMap<String, LearnState>,
    entries: Vec<SlideEntry>,
    check_errors: bool,
    hint_map: HashMap<usize, LabeledChord>,
}

struct LearnState(i64);

impl LearnState {
    fn update(&mut self, was_correct: bool) {
        if was_correct {
            self.0 -= 1;
        } else {
            self.0 += 1;
        }
    }

    fn needs_hint(&self) -> bool {
        self.0 >= 0
    }
}

impl Default for LearnState {
    fn default() -> LearnState {
        // Set the number of times you must type this character correctly
        // before the hint goes away
        LearnState(5)
    }
}

impl Copier {
    pub fn new(num_chars: usize) -> Copier {
        let point_offset = (num_chars + 1) / 2. as usize;
        Copier {
            num_chars: num_chars,
            point_offset: point_offset,
            point_marker: "▼".into(),
            expected: String::new(),
            actual: String::new(),
            index: 0,
            was_backspace_typed_last: false,
            learned_keys: HashMap::new(),
            entries: Vec::new(),
            check_errors: true,
            hint_map: HashMap::new(),
        }
    }

    pub fn next_hint(&mut self) -> Result<Option<LabeledChord>, Error> {
        let special_hint = self.hint_map.get(&self.index);
        if special_hint.is_some() {
            return Ok(special_hint.cloned());
        }

        let next_letter = self.expected_char_at_point()?;
        let entry = self.learned_keys.entry(next_letter.clone()).or_default();
        let letter_hint = if entry.needs_hint() || self.was_backspace_typed_last
        {
            LabeledChord::from_letter(&next_letter)
        } else {
            None
        };

        Ok(letter_hint)
    }

    pub fn last_wrong_char(&self) -> Result<LastChar, Error> {
        if !self.check_errors {
            return Ok(LastChar::Correct);
        }

        let offset = self.point_offset - 1;
        let actual = self.char_at_offset(&self.actual, offset)?;
        let expected = self.char_at_offset(&self.expected, offset)?;

        // TODO don't include actual if not at word boundary!
        Ok(if actual != expected {
            LastChar::Incorrect(LabeledChord::from_letter(&actual))
        } else {
            LastChar::Correct
        })
    }

    pub fn type_char(&mut self, character: char) {
        let s = character.to_string();
        self.actual += &s;
        self.index += 1;
        self.was_backspace_typed_last = false;
    }

    pub fn type_backspace(&mut self) {
        if self.index > 0 {
            self.actual.pop();
            self.index -= 1;
            self.was_backspace_typed_last = true;
        }
    }

    pub fn start_line(&mut self, line: &SlideLine) -> Result<(), Error> {
        let (entries, text) = line.to_entries()?;

        // TODO why String::from?
        let pad = " ".repeat(self.extra_spaces());
        let expected = pad.clone() + &text;
        let mut actual = String::from(pad);
        actual.reserve(expected.len());

        self.expected = expected;
        self.actual = actual;
        self.index = 0;
        self.check_errors = line.check_errors();
        self.hint_map = make_hint_map(&entries);
        self.entries = entries;
        Ok(())
    }

    pub fn at_end_of_line(&self) -> bool {
        self.actual.len() == self.expected.len()
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

    // pub fn actual_graphemes<'a>(&self) -> Box<Iterator<Item = &'a str> + 'a>
    // {x
    //     grapheme_slice(&self.actual, 0, self.actual.len())
    // }

    // pub fn expected_graphemes<'a>(&self) -> Box<Iterator<Item = &'a str> +
    // 'a> {
    //     grapheme_slice(&self.expected, 0, self.expected.len())
    // }

    pub fn net_words(&self) -> f64 {
        const CHARS_PER_WORD: f64 = 5.;
        let total_chars =
            (self.actual.graphemes(true).count() - self.extra_spaces()) as f64;
        let wrong_chars: f64 = self.actual
            .graphemes(true)
            .zip(self.expected.graphemes(true))
            .map(|(actual, expected)| if actual == expected { 0. } else { 1. })
            .sum();
        // ensure the corrected wpm won't be negative
        f64::max(0., (total_chars / CHARS_PER_WORD) - wrong_chars)
    }

    fn was_last_char_correct(&self) -> Result<bool, Error> {
        Ok(self.last_wrong_char()
            .context("failed to check if last char was correct")?
            .is_correct())
    }

    fn char_at_offset(
        &self,
        string: &str,
        offset: usize,
    ) -> Result<String, Error> {
        grapheme_slice(string, self.start(), self.end())
            .nth(offset)
            .ok_or_else(|| {
                BadValueErr {
                    thing: "character offset".into(),
                    value: offset.to_string(),
                }.into()
            })
            .map(|s| s.to_owned())
    }

    pub fn expected_char_at_point(&self) -> Result<String, Error> {
        let char = if self.at_end_of_line() {
            "\n".to_owned()
        } else {
            self.char_at_offset(&self.expected, self.point_offset)
                .context("failed to get character at point")?
        };
        Ok(char)
    }

    fn start(&self) -> usize {
        self.index
    }

    fn end(&self) -> usize {
        self.index + self.num_chars
    }
}

impl View for Copier {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        let pad = self.text_padding().x;

        printer.with_color(ColorStyle::TitleSecondary, |printer| {
            printer.print((self.point_offset + pad, 0), &self.point_marker);
        });

        let expected = grapheme_slice(&self.expected, self.start(), self.end());
        let mut actual = grapheme_slice(&self.actual, self.start(), self.end());

        for (i, m_char) in expected.enumerate() {
            printer.print((i + pad, 1), m_char);
            if let Some(t_char) = actual.next() {
                printer.with_color(get_style(m_char, t_char), |printer| {
                    printer.print((i + pad, 2), t_char)
                });
            }
        }
    }
}

fn get_style(actual_char: &str, expected_char: &str) -> ColorStyle {
    if actual_char == expected_char {
        ColorStyle::Primary
    } else {
        ColorStyle::Secondary
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
