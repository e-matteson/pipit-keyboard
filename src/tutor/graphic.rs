use cursive::theme::{Color, ColorStyle};
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::Printer;

// use types::Chord;
// use types::errors::*;

use tutor::{Label, LabeledChord, PrevCharStatus};

pub struct Graphic {
    pub next: Option<LabeledChord>,
    pub error: Option<LabeledChord>,
    pub backspace: Option<LabeledChord>,
    switches: Vec<Switch>,
}

#[derive(Clone, Copy)]
pub enum ChordType {
    Next,
    Error,
    Backspace,
}

struct Switch {
    position: (usize, usize),
    next: Option<Label>,
    error: Option<Label>,
    backspace: Option<Label>,
}

////////////////////////////////////////////////////////////////////////////////

impl Graphic {
    pub fn new() -> Self {
        let switches: Vec<_> = get_switch_positions()
            .into_iter()
            .map(Switch::new)
            .collect();
        Self {
            next: None,
            error: None,
            backspace: None,
            switches,
        }
    }

    // fn draw_question_mark(&self, printer: &Printer) {
    //     let center = printer.size.x / 2 as usize;
    //     printer.with_color(Switch::next_style(), |printer| {
    //         printer.print((center - 1, 1), "???");
    //     });
    // }

    pub fn size(&self) -> Vec2 {
        Vec2::new(78, 12)
    }

    pub fn update(
        &mut self,
        next: Option<LabeledChord>,
        prev: &PrevCharStatus,
    ) {
        self.next = next;
        self.error = prev.error();
        self.backspace = prev.backspace();
        self.update_switches();
    }

    pub fn update_switches(&mut self) {
        self.clear_switches();
        self.update_switches_with_type(ChordType::Next);
        self.update_switches_with_type(ChordType::Backspace);
        self.update_switches_with_type(ChordType::Error);
    }

    fn update_switches_with_type(&mut self, chord_type: ChordType) {
        if let Some(labeled_chord) = self.get(chord_type) {
            let chord = labeled_chord.chord;
            for (&bit, switch) in chord.iter().zip(self.switches.iter_mut()) {
                if bit {
                    switch.set(chord_type, labeled_chord.label.clone());
                }
            }
        }
    }

    fn clear_switches(&mut self) {
        for switch in &mut self.switches {
            switch.clear()
        }
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
        for switch in &self.switches {
            switch.draw(printer);
        }
    }
}

impl Switch {
    fn new(position: (usize, usize)) -> Self {
        Self {
            next: None,
            error: None,
            backspace: None,
            position,
        }
    }

    fn draw(&self, printer: &Printer) {
        let (x, y) = self.position;
        let row2_left = format!("│{}", self.label().pad(3));
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

    fn label(&self) -> Label {
        if let Some(ref label) = self.next {
            label.to_owned()
        } else if let Some(ref label) = self.error {
            label.to_owned()
        } else if let Some(ref label) = self.backspace {
            label.to_owned()
        } else {
            Label::default()
        }
    }

    fn styles(&self) -> (ColorStyle, ColorStyle) {
        match (&self.next, &self.error, &self.backspace) {
            (&Some(_), &None, &None) => {
                (Self::next_style(), Self::next_style())
            }
            (&None, &Some(_), &None) => {
                (Self::error_style(), Self::error_style())
            }
            (&None, &None, &Some(_)) => {
                (Self::backspace_style(), Self::backspace_style())
            }
            (&Some(_), &Some(_), &None) => {
                (Self::next_style(), Self::error_style())
            }
            (&Some(_), &None, &Some(_)) => {
                (Self::next_style(), Self::backspace_style())
            }
            _ => (Self::default_style(), Self::default_style()),
        }
    }

    pub fn set(&mut self, chord_type: ChordType, label: Label) {
        match chord_type {
            ChordType::Next => self.next = Some(label),
            ChordType::Error => self.error = Some(label),
            ChordType::Backspace => self.backspace = Some(label),
        }
    }

    fn next_style() -> ColorStyle {
        ColorStyle::tertiary()
    }

    fn backspace_style() -> ColorStyle {
        // TODO the background color is hardcoded, instead of inheriting from
        // the theme!
        ColorStyle::new(Color::Rgb(100, 95, 0), Color::Rgb(0, 0, 0))
    }

    fn error_style() -> ColorStyle {
        ColorStyle::secondary()
    }

    fn default_style() -> ColorStyle {
        ColorStyle::title_secondary()
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
