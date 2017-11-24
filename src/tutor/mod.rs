use std::collections::BTreeMap;
use std::fs::File;
use std::io::{BufReader, Read};

use serde_json;
use unicode_segmentation::UnicodeSegmentation;

use cursive::{Cursive, Printer};
use cursive::align::HAlign;
use cursive::traits::*;
use cursive::views::{Dialog, SelectView, TextView};
use cursive::vec::Vec2;
use cursive::theme::ColorStyle;
use cursive::event::{Callback, Event, EventResult, Key};

use types::{Chord, ModeName, Name};
use types::errors::*;

struct LessonMenu;
struct LessonWrapper;

type TutorData = BTreeMap<ModeName, BTreeMap<Name, Chord>>;

enum LessonState {
    Typing,
    EndOfLine,
}

struct Graphic {
    positions: Vec<(usize, usize)>,
    chord: Option<Chord>,
    alternate_chord: Chord,
}

struct Switch {
    left_style: ColorStyle,
    right_style: ColorStyle,
}

struct Lesson {
    lines: Vec<String>,
    expected: String,
    actual: String,
    width: usize,
    point_marker: String,
    point_offset: usize,
    index: usize,
    graphic: Graphic,
    graphic_spacing: usize,
}

////////////////////////////////////////////////////////////////////////////////

pub fn run() {
    let mut siv = Cursive::new();

    // TODO move theme file to an assets folder?
    siv.load_theme_file("src/tutor/theme.toml")
        .expect("failed to load theme");
    LessonMenu::show(&mut siv);
    siv.run();
}

fn read_file(path: &str) -> Result<String> {
    let file = File::open(path)
        .chain_err(|| format!("failed to open file: {}", path))?;
    let mut s = String::new();
    BufReader::new(file).read_to_string(&mut s)?;
    Ok(s)
}

pub fn load_tutor_data() -> Result<TutorData> {
    let path = "tutor/tutor_data.json";
    let json = read_file(path)?;
    let data = serde_json::from_str(&json)?;
    Ok(data)
}

impl LessonMenu {
    fn show(siv: &mut Cursive) {
        let names = vec![
            "home row letters",
            "top row letters",
            "double-switch letters",
        ];

        let mut select = SelectView::new().h_align(HAlign::Center);

        select.add_all_str(names);

        select.set_on_submit(|siv, name| {
            LessonMenu::cleanup(siv);
            LessonWrapper::show(siv, name)
        });

        siv.add_layer(
            Dialog::around(select.fixed_size((20, 10)))
                .title("Please select a lesson"),
        );
    }

    fn cleanup(siv: &mut Cursive) {
        siv.pop_layer();
    }
}

impl LessonWrapper {
    fn show(siv: &mut Cursive, _name: &str) {
        let lines = vec![
            "hello world and fox".into(),
            "this is the second line".into(),
            "and the last one!".into(),
        ];
        siv.add_layer(Lesson::new(lines).with_id("text"));
    }

    fn cleanup(siv: &mut Cursive) {
        siv.pop_layer();
    }

    fn show_confirm_back(siv: &mut Cursive) {
        siv.add_layer(
            Dialog::around(TextView::new("Return to lesson menu?"))
                .dismiss_button("Cancel")
                .button("Yes", |siv| {
                    siv.pop_layer();
                    LessonWrapper::cleanup(siv);
                    LessonMenu::show(siv);
                }),
        )
    }

    fn end_lesson_callback(siv: &mut Cursive) {
        siv.add_layer(Dialog::around(TextView::new("Lesson complete")).button(
            "back",
            |siv| {
                siv.pop_layer();
                LessonWrapper::cleanup(siv);
                LessonMenu::show(siv)
            },
        ));
    }
}

impl Lesson {
    fn new(lines: Vec<String>) -> Lesson {
        let width = 31;
        let point_offset = 15;

        let mut lesson = Lesson {
            lines: lines.into_iter().rev().collect(),
            expected: String::new(),
            actual: String::new(),
            width: width,
            point_marker: "▼".into(),
            point_offset: point_offset,
            index: 0,
            graphic: Graphic::new(),
            graphic_spacing: 1,
        };
        lesson.next_line();
        lesson.update_chord();
        lesson
    }


    fn type_char(&mut self, character: char) {
        self.actual.push(character);
        self.index += 1;
    }

    fn backspace(&mut self) {
        if self.index > 0 {
            self.actual.pop();
            self.index -= 1;
        }
    }

    fn start(&self) -> usize {
        self.index
    }

    fn end(&self) -> usize {
        self.index + self.width
    }

    fn next_line(&mut self) {
        let pad = " ".repeat(self.point_offset);
        let expected =
            pad.clone() + &self.lines.pop().expect("lesson was empty");
        let mut actual = String::from(pad);
        actual.reserve(expected.len());

        self.expected = expected;
        self.actual = actual;
        self.index = 0;
    }

    fn at_end_of_line(&self) -> bool {
        self.actual.len() == self.expected.len()
    }

    fn state(&self) -> LessonState {
        if self.at_end_of_line() {
            LessonState::EndOfLine
        } else {
            LessonState::Typing
        }
    }

    fn graphic_padding(&self) -> Vec2 {
        let x = offset(self.graphic.size().x, self.size().x);
        let y = 3 + self.graphic_spacing;
        Vec2::new(x, y)
    }

    fn text_padding(&self) -> Vec2 {
        let x = offset(self.width, self.size().x);
        Vec2::new(x, 0)
    }

    fn size(&self) -> Vec2 {
        let graphic_size = self.graphic.size();
        let x = self.width.max(graphic_size.x);
        let y = 3 + self.graphic_spacing + graphic_size.y;
        Vec2::new(x, y)
    }

    fn was_last_char_wrong(&self) -> Result<bool> {
        let offset = self.point_offset - 1;
        Ok(
            self.char_at_offset(&self.expected, offset)?
                != self.char_at_offset(&self.actual, offset)?,
        )
    }

    fn expected_char_at_point(&self) -> Result<char> {
        self.char_at_offset(&self.expected, self.point_offset)
    }

    fn char_at_offset(&self, string: &str, offset: usize) -> Result<char> {
        // eprintln!("{}",self.start(), self.end(), self.point());
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

    fn expected_chord_at_point(&self) -> Result<Chord> {
        let name = if self.at_end_of_line() {
            Name("key_enter".into())
        } else {
            get_char_name(self.expected_char_at_point()?)?
        };

        get_chord(name)
    }

    fn update_chord(&mut self) {
        // TODO handle error better
        self.graphic.chord =
            Some(self.expected_chord_at_point().expect("chord not found"));

        self.graphic.alternate_chord = if self.was_last_char_wrong()
            .expect("failed to check if char was wrong")
        {
            backspace_chord().expect("backspace chord not found")
        } else {
            Chord::new()
        };
    }
}

impl View for Lesson {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        let pad = self.text_padding().x;
        printer.print((self.point_offset + pad, 0), &self.point_marker);

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

        self.graphic.draw(&printer.sub_printer(
            self.graphic_padding(),
            self.graphic.size(),
            false,
        ))
    }

    fn on_event(&mut self, event: Event) -> EventResult {
        if let Event::Key(Key::Esc) = event {
            return EventResult::Consumed(
                Some(Callback::from_fn(LessonWrapper::show_confirm_back)),
            );
        }
        match self.state() {
            LessonState::Typing => match event {
                Event::Key(Key::Backspace) => self.backspace(),
                Event::Char(letter) => self.type_char(letter),
                _ => return EventResult::Ignored,
            },
            LessonState::EndOfLine => match event {
                Event::Key(Key::Backspace) => self.backspace(),
                Event::CtrlChar('j') | Event::Key(Key::Enter) => {
                    if self.lines.is_empty() {
                        // Lesson is done
                        return EventResult::Consumed(Some(Callback::from_fn(
                            LessonWrapper::end_lesson_callback,
                        )));
                    }
                    self.next_line()
                }
                _ => return EventResult::Ignored,
            },
        }
        self.update_chord();
        EventResult::Consumed(None)
    }
}

impl Graphic {
    fn new() -> Graphic {
        Graphic {
            positions: get_switch_positions(),
            chord: None,
            alternate_chord: Chord::default(),
        }
    }

    fn size(&self) -> Vec2 {
        Vec2::new(45, 6)
    }

    fn draw_switches(&self, printer: &Printer) {
        // TODO don't clone?
        if let Some(bits) = self.chord.clone() {
            eprintln!("DRAWSWITCHES: {:?}, {:?}", bits, self.alternate_chord);

            for ((&pos, &bit), &alt_bit) in self.positions
                .iter()
                .zip(bits.to_bools().iter())
                .zip(self.alternate_chord.clone().to_bools().iter())
            {
                eprintln!("{}, {}", bit, alt_bit);
                Switch::new(bit, alt_bit).draw(pos, printer)
            }
        }
    }

    fn draw_frame(&self, printer: &Printer) {
        printer.with_color(ColorStyle::TitleSecondary, |printer| {
            printer.print((0, 0),
                          "╭─────────────╮               ╭─────────────╮"
            );
            printer.print(
                (0, 1),
                "│             │               │             │",
            );
            printer.print(
                (0, 2),
                "│             │               │             │",
            );
            printer.print((0, 3),
                          "╰─────╮       ╰──────╮ ╭──────╯       ╭─────╯"
            );
            printer.print((0, 4),
                          "      ╰───╮          │ │          ╭───╯",
            );
            printer.print((0, 5),
                          "          ╰──────────╯ ╰──────────╯"
            )
        });
    }
}

impl Switch {
    const LEFT_ICON: &'static str = "▆";
    const RIGHT_ICON: &'static str = "▆";

    fn new(bit: bool, alt_bit: bool) -> Switch {
        let (left, right) = match (bit, alt_bit) {
            (false, false) => (Switch::blank(), Switch::blank()),
            (true, false) => (Switch::next(), Switch::next()),
            (false, true) => (Switch::wrong(), Switch::wrong()),
            (true, true) => (Switch::next(), Switch::wrong()),
        };
        Switch {
            left_style: left,
            right_style: right,
        }
    }

    fn draw(&self, pos: (usize, usize), printer: &Printer) {
        eprintln!("draw switch");
        let (x, y) = pos;
        printer.with_color(self.left_style, |printer| {
            printer.print((x, y), &Switch::LEFT_ICON)
        });
        printer.with_color(self.right_style, |printer| {
            printer.print((x + 1, y), &Switch::RIGHT_ICON)
        });
    }

    fn wrong() -> ColorStyle {
        ColorStyle::Secondary
    }

    fn next() -> ColorStyle {
        ColorStyle::Tertiary
    }

    fn blank() -> ColorStyle {
        ColorStyle::TitleSecondary
    }
}

impl View for Graphic {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        self.draw_frame(printer);
        self.draw_switches(printer);
    }
}

fn get_switch_positions() -> Vec<(usize, usize)> {
    let p = vec![
        (2, 1),
        (5, 1),
        (8, 1),
        (11, 1),
        (32, 1),
        (35, 1),
        (38, 1),
        (41, 1),
        (2, 2),
        (5, 2),
        (8, 2),
        (11, 2),
        (32, 2),
        (35, 2),
        (38, 2),
        (41, 2),
        (8, 3),
        (35, 3),
        (12, 4),
        (15, 4),
        (18, 4),
        (25, 4),
        (28, 4),
        (31, 4),
    ];
    p
}

fn grapheme_slice<'a>(
    s: &'a str,
    start: usize,
    end: usize,
) -> Box<Iterator<Item = &'a str> + 'a> {
    Box::new(s.graphemes(true).skip(start).take(end))
}


fn offset(width1: usize, width2: usize) -> usize {
    ((width2 - width1) as f32 / 2.).round() as usize
}


fn get_style(actual_char: &str, expected_char: &str) -> ColorStyle {
    if actual_char == expected_char {
        ColorStyle::Primary
    } else {
        ColorStyle::Secondary
    }
}


fn get_pipit_data() -> Result<&'static TutorData> {
    // TODO don't hardcode path - redesign!
    lazy_static!{
        static ref DATA: TutorData = {
            eprintln!("Loading pipit data from tutor file");
            load_tutor_data().expect("failed to load tutor data")
        };
    }
    Ok(&DATA)
}

// fn get_key_name(key: Key) -> Result<Name> {
//     match key {
//         Key::Backspace => Some("key_backspace"),
//         Key::Enter => Some("key_enter"),
//         _ => return None,
//     }
// }

fn get_char_name(character: char) -> Result<Name> {
    if character.is_alphanumeric() {
        return Ok(Name(format!("key_{}", character.to_lowercase())));
    }
    let name = match character {
        ' ' => "key_space".into(),
        '.' => "key_period".into(),
        ',' => "key_comma".into(),
        '\'' => "key_quote".into(),
        _ => bail!("tutor: unknown character"),
    };
    Ok(Name(name))
}

fn get_chord(chord_name: Name) -> Result<Chord> {
    let mode_name = ModeName::default();
    // TODO handle missing chords better?
    let chord: Chord = get_pipit_data()?
        .get(&mode_name)
        .ok_or_else(|| "mode not found in tutor data".to_owned())?
        .get(&chord_name)
        .cloned()
        .ok_or_else(|| "chord not found in mode".to_owned())?;
    Ok(chord)
}
fn backspace_chord() -> Result<Chord> {
    get_chord(Name("key_backspace".into()))
}
