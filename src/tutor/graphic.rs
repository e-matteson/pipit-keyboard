use cursive::theme::{Color, ColorStyle};
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::Printer;

use tutor::{Label, LabeledChord, PrevCharStatus};

pub struct Graphic {
    switches: Vec<Switch>,
}

#[derive(Clone, Copy)]
pub enum ChordType {
    Next,
    Error,
    Backspace,
    Shown,
}

struct Switch {
    position: (usize, usize),
    next: Option<Label>,
    error: Option<Label>,
    shown: Option<Label>,
    backspace: Option<Label>,
}

////////////////////////////////////////////////////////////////////////////////

impl Graphic {
    pub fn new(shown: Vec<LabeledChord>) -> Self {
        let switches: Vec<_> = get_switch_positions()
            .into_iter()
            .map(Switch::new)
            .collect();
        let mut graphic = Self { switches };
        for labeled_chord in shown {
            graphic.apply_chord(labeled_chord, ChordType::Shown);
        }
        graphic
    }

    pub fn update(
        &mut self,
        next: Option<LabeledChord>,
        prev: &PrevCharStatus,
    ) {
        for switch in &mut self.switches {
            switch.clear()
        }
        if let Some(c) = next {
            self.apply_chord(c, ChordType::Next)
        }
        if let Some(c) = prev.backspace() {
            self.apply_chord(c, ChordType::Backspace)
        }
        if let Some(c) = prev.error() {
            self.apply_chord(c, ChordType::Error)
        }
    }

    fn apply_chord(&mut self, lc: LabeledChord, chord_type: ChordType) {
        let (label, chord) = (lc.label, lc.chord);
        for (bit, switch) in chord.iter().zip(self.switches.iter_mut()) {
            if bit {
                switch.set_label(chord_type, label.clone());
            }
        }
    }

    pub fn size(&self) -> Vec2 {
        Vec2::new(78, 12)
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
            shown: None,
            position,
        }
    }

    fn set_label(&mut self, chord_type: ChordType, label: Label) {
        match chord_type {
            ChordType::Next => self.next = Some(label),
            ChordType::Error => self.error = Some(label),
            ChordType::Backspace => self.backspace = Some(label),
            ChordType::Shown => self.shown = Some(label),
        }
    }

    /// Clear all labels except the `shown` label, since that one stays for the
    /// whole lesson
    fn clear(&mut self) {
        self.next = None;
        self.error = None;
        self.backspace = None;
    }

    /// Pick 1 label to show, according to their priority order
    fn label(&self) -> Label {
        self.next
            .as_ref()
            .or(self.error.as_ref())
            .or(self.backspace.as_ref())
            .or(self.shown.as_ref())
            .cloned()
            .unwrap_or_else(Label::default)
    }

    /// Pick a style for the switch, based on which labeled chords include it
    fn styles(&self) -> (ColorStyle, ColorStyle) {
        let next = Self::next_style();
        let error = Self::error_style();
        let backspace = Self::backspace_style();
        let default = Self::default_style();
        match (
            self.next.is_some(),
            self.error.is_some(),
            self.backspace.is_some(),
        ) {
            (true, false, false) => (next, next),
            (false, true, false) => (error, error),
            (false, false, true) => (backspace, backspace),
            (true, true, false) => (next, error),
            (true, false, true) => (next, backspace),
            _ => (default, default),
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
