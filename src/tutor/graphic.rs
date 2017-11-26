

use cursive::Printer;
use cursive::traits::*;
use cursive::vec::Vec2;
use cursive::theme::{Color, ColorStyle};

use types::Chord;
// use types::errors::*;
use tutor::utils::grapheme_slice;

pub struct Graphic {
    pub next_chord: Option<Chord>,
    pub error_chord: Option<Chord>,
    pub backspace_chord: Option<Chord>,
    pub next_label: Option<String>,
    pub error_label: Option<String>,
    pub backspace_label: Option<String>,
    switches: Vec<Switch>,
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
            next_chord: None,
            error_chord: None,
            backspace_chord: None,
            next_label: Some(String::new()),
            error_label: Some(String::new()),
            backspace_label: Some(String::new()),
            switches: switches,
        }
    }

    pub fn size(&self) -> Vec2 {
        Vec2::new(78, 12)
    }

    fn draw_question_mark(&self, printer: &Printer) {
        let center = printer.size.x / 2 as usize;
        printer.with_color(Switch::next_style(), |printer| {
            printer.print((center - 1, 1), "???");
        });
    }

    fn clear_switches(&mut self) {
        for switch in self.switches.iter_mut() {
            switch.clear()
        }
    }

    pub fn update_switches(&mut self) {
        self.clear_switches();
        if let Some(ref bits) = self.next_chord {
            for (&bit, switch) in bits.iter().zip(self.switches.iter_mut()) {
                if bit {
                    switch.set_next(self.next_label.clone());
                }
            }
        }
        if let Some(ref bits) = self.error_chord {
            for (&bit, switch) in bits.iter().zip(self.switches.iter_mut()) {
                if bit {
                    switch.set_error(self.error_label.clone());
                }
            }
        }
        if let Some(ref bits) = self.backspace_chord {
            for (&bit, switch) in bits.iter().zip(self.switches.iter_mut()) {
                if bit {
                    switch.set_backspace(self.backspace_label.clone());
                }
            }
        }
    }
}

impl View for Graphic {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        if self.next_chord.is_none() {
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
    // bit: bool, alt_bit: bool, label: &str, alt_label: &str
    // let (left, right, foo) = match (bit, alt_bit) {
    // (false, false) => (Switch::default_style(), Switch::default_style(),
    // String::new()),
    // (true, false) => (Switch::next_style(), Switch::next_style(),
    // label.into()),
    //     (false, true) => {
    // (Switch::backspace_style(), Switch::backspace_style(),
    // alt_label.into())
    //     }
    // (true, true) => (Switch::next_style(), Switch::backspace_style(),
    // label.into()),
    // };
    // Switch {
    //     left_style: left,
    //     right_style: right,
    //     label: foo,
    // }

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

    fn set_next(&mut self, label: Option<String>) {
        self.next = label;
    }

    fn set_error(&mut self, label: Option<String>) {
        self.error = label;
    }

    fn set_backspace(&mut self, label: Option<String>) {
        self.backspace = label;
    }

    fn center_pad(label: &str, width: usize) -> String {
        let len = grapheme_slice(label, 0, label.len()).count();
        let start = (width - len) / 2. as usize;
        " ".repeat(start) + label + &" ".repeat(width - start)
    }

    fn draw(&self, printer: &Printer) {
        let (x, y) = self.position;
        let row1_left = "╭───";
        let row2_left = format!("│{}", Switch::center_pad(&self.label(), 3));
        let row3_left = "╰";
        let row1_right = "╮";
        let row2_right = "│";
        let row3_right = "───╯";
        let (left, right) = self.styles();
        printer.with_color(left, |printer| {
            printer.print((x, y), row1_left);
            printer.print((x, y + 1), &row2_left);
            printer.print((x, y + 2), row3_left);
        });
        printer.with_color(right, |printer| {
            printer.print((x + 4, y), row1_right);
            printer.print((x + 4, y + 1), &row2_right);
            printer.print((x + 1, y + 2), row3_right);
        });
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
