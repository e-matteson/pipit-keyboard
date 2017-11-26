use cursive::Printer;
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::theme::{Color, ColorStyle};

use types::{Chord, Name};
// use types::errors::*;

use tutor::utils::{char_to_chord, char_to_label, grapheme_slice, TutorData};

pub struct Graphic {
    pub next: Option<LabeledChord>,
    pub error: Option<LabeledChord>,
    pub backspace: Option<LabeledChord>,
    switches: Vec<Switch>,
}

#[derive(Clone)]
pub struct LabeledChord {
    pub chord: Option<Chord>,
    pub label: String,
}

#[derive(Clone, Copy)]
pub enum ChordType {
    Next,
    Error,
    Backspace,
}

struct Switch {
    position: (usize, usize),
    next: Option<String>,
    error: Option<String>,
    backspace: Option<String>,
}

////////////////////////////////////////////////////////////////////////////////

impl Graphic {
    pub fn new() -> Graphic {
        let switches: Vec<_> = get_switch_positions()
            .into_iter()
            .map(|pos| Switch::new(pos))
            .collect();
        Graphic {
            next: None,
            error: None,
            backspace: None,
            switches: switches,
        }
    }

    fn draw_question_mark(&self, printer: &Printer) {
        let center = printer.size.x / 2 as usize;
        printer.with_color(Switch::next_style(), |printer| {
            printer.print((center - 1, 1), "???");
        });
    }

    pub fn size(&self) -> Vec2 {
        Vec2::new(78, 12)
    }

    pub fn update(&mut self, next_char: char, last_wrong_char: Option<char>) {
        self.next = Some(LabeledChord {
            chord: char_to_chord(next_char),
            label: char_to_label(next_char),
        });

        if let Some(wrong_char) = last_wrong_char {
            self.backspace = Some(LabeledChord {
                chord: backspace_chord(),
                label: "bak".into(),
            });
            self.error = Some(LabeledChord {
                chord: char_to_chord(wrong_char),
                label: char_to_label(wrong_char),
            });
        } else {
            self.backspace = None;
            self.error = None;
        }
        self.update_switches();
    }

    pub fn update_switches(&mut self) {
        self.clear_switches();
        self.update_switches_with_type(ChordType::Next);
        self.update_switches_with_type(ChordType::Backspace);
        self.update_switches_with_type(ChordType::Error);
    }

    fn update_switches_with_type(&mut self, chord_type: ChordType) {
        if let Some(ref chord) = self.get_chord(chord_type) {
            let label = self.get_label(chord_type).clone();
            for (&bit, switch) in chord.iter().zip(self.switches.iter_mut()) {
                if bit {
                    switch.set(chord_type, label.clone());
                }
            }
        }
    }

    fn clear_switches(&mut self) {
        for switch in self.switches.iter_mut() {
            switch.clear()
        }
    }

    pub fn get_chord(&self, chord_type: ChordType) -> Option<Chord> {
        self.get(chord_type)?.chord
    }

    pub fn get_label(&self, chord_type: ChordType) -> Option<String> {
        Some(self.get(chord_type)?.label)
    }

    fn get(&self, chord_type: ChordType) -> Option<LabeledChord> {
        match chord_type {
            ChordType::Next => self.next.clone(),
            ChordType::Error => self.error.clone(),
            ChordType::Backspace => self.backspace.clone(),
        }
    }
}

impl View for Graphic {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        if self.get_chord(ChordType::Next).is_none() {
            self.draw_question_mark(printer);
        }
        for switch in &self.switches {
            switch.draw(printer);
        }
    }
}

impl Switch {
    fn new(position: (usize, usize)) -> Switch {
        Switch {
            next: None,
            error: None,
            backspace: None,
            position: position,
        }
    }

    fn draw(&self, printer: &Printer) {
        let (x, y) = self.position;
        let row2_left = format!("│{}", Switch::center_pad(&self.label(), 3));
        let (left, right) = self.styles();
        printer.with_color(left, |printer| {
            printer.print((x, y), "╭───");
            printer.print((x, y + 1), &row2_left);
            printer.print((x, y + 2), "╰");
        });
        printer.with_color(right, |printer| {
            printer.print((x + 4, y), "╮");
            printer.print((x + 4, y + 1), "│");
            printer.print((x + 1, y + 2), "───╯");
        });
    }


    fn clear(&mut self) {
        self.next = None;
        self.error = None;
        self.backspace = None;
    }

    fn label<'a>(&'a self) -> &'a str {
        if let Some(ref label) = self.next {
            label
        } else if let Some(ref label) = self.error {
            label
        } else if let Some(ref label) = self.backspace {
            label
        } else {
            ""
        }
    }

    fn styles(&self) -> (ColorStyle, ColorStyle) {
        match (&self.next, &self.error, &self.backspace) {
            (&Some(_), &None, &None) => {
                (Switch::next_style(), Switch::next_style())
            }
            (&None, &Some(_), &None) => {
                (Switch::error_style(), Switch::error_style())
            }
            (&None, &None, &Some(_)) => {
                (Switch::backspace_style(), Switch::backspace_style())
            }
            (&Some(_), &Some(_), &None) => {
                (Switch::next_style(), Switch::error_style())
            }
            (&Some(_), &None, &Some(_)) => {
                (Switch::next_style(), Switch::backspace_style())
            }
            _ => (Switch::default_style(), Switch::default_style()),
        }
    }

    pub fn set(&mut self, chord_type: ChordType, label: Option<String>) {
        match chord_type {
            ChordType::Next => self.next = label,
            ChordType::Error => self.error = label,
            ChordType::Backspace => self.backspace = label,
        }
    }

    fn center_pad(label: &str, width: usize) -> String {
        let len = grapheme_slice(label, 0, label.len()).count();
        let start = (width - len) / 2. as usize;
        " ".repeat(start) + label + &" ".repeat(width - start)
    }

    fn next_style() -> ColorStyle {
        ColorStyle::Tertiary
    }

    fn backspace_style() -> ColorStyle {
        // TODO the background color is hardcoded, instead of inheriting from
        // the theme!
        ColorStyle::Custom {
            front: Color::Rgb(100, 95, 0),
            back: Color::Rgb(0, 0, 0),
        }
    }

    fn error_style() -> ColorStyle {
        ColorStyle::Secondary
    }

    fn default_style() -> ColorStyle {
        ColorStyle::TitleSecondary
    }
}

fn get_switch_positions() -> Vec<(usize, usize)> {
    vec![
        (0, 2),
        (6, 1),
        (12, 1),
        (18, 1),
        (54, 1),
        (60, 1),
        (66, 1),
        (72, 2),
        (0, 5),
        (6, 4),
        (12, 4),
        (18, 4),
        (54, 4),
        (60, 4),
        (66, 4),
        (72, 5),
        (60, 7),
        (12, 7),
        (20, 8),
        (26, 8),
        (32, 9),
        (40, 9),
        (46, 8),
        (52, 8),
    ]
}


fn backspace_chord() -> Option<Chord> {
    TutorData::get_chord(Name("key_backspace".into()))
}
