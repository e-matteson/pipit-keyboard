// use std::time::Instant;

use cursive::Printer;
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::theme::ColorStyle;

use unicode_segmentation::UnicodeSegmentation;

use types::errors::*;
use tutor::utils::{grapheme_slice, offset};


pub struct Copier {
    expected: String,
    actual: String,
    num_chars: usize,
    point_marker: String,
    point_offset: usize,
    index: usize,
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
        }
    }

    pub fn type_char(&mut self, character: char) {
        self.actual.push(character);
        self.index += 1;
    }

    pub fn type_backspace(&mut self) {
        if self.index > 0 {
            self.actual.pop();
            self.index -= 1;
        }
    }

    pub fn start_line(&mut self, line: &str) {
        let pad = " ".repeat(self.extra_spaces());
        let expected = pad.clone() + line;
        let mut actual = String::from(pad);
        actual.reserve(expected.len());

        self.expected = expected;
        self.actual = actual;
        self.index = 0;
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
        let all =
            (self.actual.graphemes(true).count() - self.extra_spaces()) as f64;
        let errors: f64 = self.actual
            .graphemes(true)
            .zip(self.expected.graphemes(true))
            .map(|(actual, expected)| if actual == expected {
                0.
            } else {
                1.
            })
            .sum();
        // eprintln!("all: {}, errors: {}", all, errors);
        (all / CHARS_PER_WORD) - errors
    }

    pub fn last_wrong_char(&self) -> Result<Option<char>> {
        let offset = self.point_offset - 1;
        let actual = self.char_at_offset(&self.actual, offset)?;
        let expected = self.char_at_offset(&self.expected, offset)?;
        Ok(if actual != expected {
            Some(actual)
        } else {
            None
        })
    }

    fn char_at_offset(&self, string: &str, offset: usize) -> Result<char> {
        let mut chars = grapheme_slice(string, self.start(), self.end())
            .nth(offset)
            .ok_or_else(|| "no character offset".to_owned())?
            .chars();
        let first = chars
            .next()
            .ok_or_else(|| "invalid character at offset, no bytes".to_owned())?;
        if chars.count() > 0 {
            bail!("invalid character at offset, extra bytes");
        }
        Ok(first)
    }

    pub fn expected_char_at_point(&self) -> char {
        if self.at_end_of_line() {
            '\n'
        } else {
            self.char_at_offset(&self.expected, self.point_offset)
                .expect("failed to get character at point")
        }
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
