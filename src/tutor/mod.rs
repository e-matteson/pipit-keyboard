use std::collections::BTreeMap;
use std::fs::{self, File};
use std::path::PathBuf;
use std::io::{BufRead, BufReader, Read};
use std::sync::Mutex;

use serde_json;
use unicode_segmentation::UnicodeSegmentation;
use natord;

use cursive::{Cursive, Printer};
use cursive::align::HAlign;
use cursive::traits::*;
use cursive::views::{Dialog, SelectView, TextView};
use cursive::vec::Vec2;
use cursive::theme::ColorStyle;
use cursive::event::{Callback, Event, EventResult, Key};

use types::{Chord, ModeName, Name};
use types::errors::*;


type TutorData = BTreeMap<ModeName, BTreeMap<Name, Chord>>;

pub struct TutorApp;

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

enum LessonState {
    Typing,
    EndOfLine,
}

struct Graphic {
    positions: Vec<(usize, usize)>,
    chord: Option<Chord>,
    alt_chord: Option<Chord>,
    label: String,
    alt_label: String,
}

struct Switch {
    left_style: ColorStyle,
    right_style: ColorStyle,
    label: String,
}

////////////////////////////////////////////////////////////////////////////////

lazy_static! {
    static ref TUTOR_DATA: Mutex<Option<TutorData>> = Mutex::new(None);
}

fn set_tutor_data(data: TutorData) {
    let mut tutor_data = TUTOR_DATA.lock().unwrap();
    match *tutor_data {
        Some(_) => panic!("tutor data can only be set once"),
        None => *tutor_data = Some(data),
    }
}

fn char_to_chord(character: char) -> Option<Chord> {
    let (name, is_uppercase) = get_char_name(character)?;
    let mut chord = get_chord(name)?;
    if is_uppercase {
        chord.intersect(&get_chord(Name("mod_shift".into()))?)
    }
    Some(chord)
}

fn get_chord(chord_name: Name) -> Option<Chord> {
    let mode_name = ModeName::default();

    if let Some(ref data) = *TUTOR_DATA.lock().unwrap() {
        data.get(&mode_name)?.get(&chord_name).cloned()
    } else {
        panic!("tutor data was not set")
    }
}

fn load_lessons(lesson_dir: &str) -> Result<BTreeMap<String, Vec<String>>> {
    let entries = fs::read_dir(lesson_dir)?;
    let mut map = BTreeMap::new();
    for entry in entries {
        let path = entry?.path();
        let name = lesson_path_to_name(&path);
        map.insert(name, read_file_lines(&path)?);
    }
    Ok(map)
}

fn lesson_path_to_name(path: &PathBuf) -> String {
    let s = path.file_stem()
        .expect("invalid lesson file name")
        .to_str()
        .expect("lesson path is not valid unicode");
    let mut sections = s.split("_");
    let number = sections.next().expect("invalid lesson file name");
    let words: Vec<_> = sections.collect();
    format!("{}) {}", number, words.join(" "))
}

impl TutorApp {
    pub fn run(data: TutorData) {
        set_tutor_data(data);

        let mut siv = Cursive::new();

        // TODO move theme file to an assets folder?
        siv.load_theme_file("src/tutor/theme.toml")
            .expect("failed to load theme");
        TutorApp::show_menu(&mut siv);
        siv.run();
    }

    fn show_menu(siv: &mut Cursive) {
        let lessons =
            load_lessons("tutor/lessons/").expect("failed to get lessons");
        let mut names: Vec<String> = lessons.keys().cloned().collect();
        names.sort_by(|a, b| natord::compare(a, b));

        let mut select = SelectView::new().h_align(HAlign::Left);

        select.add_all_str(names);
        select.set_on_submit(move |siv, name| {
            TutorApp::cleanup_menu(siv);
            let lines = lessons.get(name).cloned().expect("lesson not found");
            TutorApp::show_lesson(siv, name, lines)
        });

        siv.add_layer(
            // Dialog::around(select.fixed_size((20, 10)))
            // Dialog::around(select).title("Please select a lesson"),
            Dialog::around(select).title("Lessons"),
        );
    }

    fn cleanup_menu(siv: &mut Cursive) {
        siv.pop_layer();
    }

    fn show_lesson(siv: &mut Cursive, _name: &str, lines: Vec<String>) {
        siv.add_layer(Lesson::new(lines).with_id("text"));
    }

    fn cleanup_lesson(siv: &mut Cursive) {
        siv.pop_layer();
    }

    fn show_confirm_back(siv: &mut Cursive) {
        siv.add_layer(
            Dialog::around(TextView::new("Return to lesson menu?"))
                .dismiss_button("Cancel")
                .button("Yes", |siv| {
                    siv.pop_layer();
                    TutorApp::cleanup_lesson(siv);
                    TutorApp::show_menu(siv);
                }),
        )
    }

    fn end_lesson_callback(siv: &mut Cursive) {
        siv.add_layer(Dialog::around(TextView::new("Lesson complete")).button(
            "back",
            |siv| {
                siv.pop_layer();
                TutorApp::cleanup_lesson(siv);
                TutorApp::show_menu(siv)
            },
        ));
    }
}

impl Lesson {
    fn new(lines: Vec<String>) -> Lesson {
        let width = 79;
        let point_offset = 39;

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

    fn expected_char_at_point(&self) -> char {
        if self.at_end_of_line() {
            '\n'
        } else {
            self.char_at_offset(&self.expected, self.point_offset)
                .expect("failed to get character at point")
        }
    }

    fn update_chord(&mut self) {
        let character = self.expected_char_at_point();
        self.graphic.chord = char_to_chord(character);
        self.graphic.label = char_to_label(character);

        let (alt_chord, alt_label) = if self.was_last_char_wrong()
            .expect("failed to check if char was wrong")
        {
            (backspace_chord(), "bak".into())
        } else {
            (None, String::new())
        };
        self.graphic.alt_chord = alt_chord;
        self.graphic.alt_label = alt_label;
    }
}

impl View for Lesson {
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

        self.graphic.draw(&printer.sub_printer(
            self.graphic_padding(),
            self.graphic.size(),
            false,
        ))
    }

    fn on_event(&mut self, event: Event) -> EventResult {
        if let Event::Key(Key::Esc) = event {
            return EventResult::Consumed(
                Some(Callback::from_fn(TutorApp::show_confirm_back)),
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
                        return EventResult::Consumed(Some(
                            Callback::from_fn(TutorApp::end_lesson_callback),
                        ));
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
            alt_chord: None,
            label: String::new(),
            alt_label: String::new(),
        }
    }

    fn size(&self) -> Vec2 {
        Vec2::new(80, 26)
    }

    fn draw_question_mark(&self, printer: &Printer) {
        let center = printer.size.x / 2 as usize;
        // printer.with_color(Switch::blank(), |printer| {
        //     printer.print((center - 2, 0), "╭───╮");
        //     printer.print((center - 2, 1), "│   │");
        //     printer.print((center - 2, 2), "╰───╯");
        // });
        printer.with_color(Switch::next(), |printer| {
            printer.print((center - 1, 1), "???");
        });
    }
}

impl Switch {
    fn new(bit: bool, alt_bit: bool, label: &str, alt_label: &str) -> Switch {
        let (left, right, foo) = match (bit, alt_bit) {
            (false, false) => (Switch::blank(), Switch::blank(), String::new()),
            (true, false) => (Switch::next(), Switch::next(), label.into()),
            (false, true) => {
                (Switch::wrong(), Switch::wrong(), alt_label.into())
            }
            (true, true) => (Switch::next(), Switch::wrong(), label.into()),
        };
        Switch {
            left_style: left,
            right_style: right,
            label: foo,
        }
    }

    fn center_pad(label: &str, width: usize) -> String {
        let len = grapheme_slice(label, 0, label.len()).count();
        let start = (width - len) / 2. as usize;
        " ".repeat(start) + label + &" ".repeat(width - start)
    }

    fn draw(&self, pos: (usize, usize), printer: &Printer) {
        let (x, y) = pos;
        let row1_left = "╭───";
        let row2_left = format!("│{}", Switch::center_pad(&self.label, 3));
        let row3_left = "╰";
        let row1_right = "╮";
        let row2_right = "│";
        let row3_right = "───╯";
        printer.with_color(self.left_style, |printer| {
            printer.print((x, y), row1_left);
            printer.print((x, y + 1), &row2_left);
            printer.print((x, y + 2), row3_left);
        });
        printer.with_color(self.right_style, |printer| {
            printer.print((x + 4, y), row1_right);
            printer.print((x + 4, y + 1), &row2_right);
            printer.print((x + 1, y + 2), row3_right);
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
        let bits = match self.chord {
            Some(ref chord) => chord.to_bools(),
            None => {
                self.draw_question_mark(printer);
                Chord::default().to_bools()
            }
        };

        let alt_bits = self.alt_chord.clone().unwrap_or_default().to_bools();

        for ((&pos, &bit), &alt_bit) in
            self.positions.iter().zip(bits.iter()).zip(alt_bits.iter())
        {
            Switch::new(bit, alt_bit, &self.label, &self.alt_label)
                .draw(pos, printer)
        }
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

fn char_to_label(character: char) -> String {
    match character {
        '\n' => "ret".into(), // "⏎"
        '\t' => "tab".into(),
        ' ' => "spc".into(),
        c => c.to_string(),
    }
}

fn get_char_name(character: char) -> Option<(Name, bool)> {
    if character.is_alphanumeric() {
        return Some((
            Name(format!("key_{}", character.to_lowercase())),
            character.is_uppercase(),
        ));
    }
    let name = match character {
        '&' => "key_ampersand".into(),
        '*' => "key_asterisk".into(),
        '@' => "key_at".into(),
        '\\' => "key_backslash".into(),
        '!' => "key_bang".into(),
        '^' => "key_caret".into(),
        ':' => "key_colon".into(),
        ',' => "key_comma".into(),
        '$' => "key_dollar".into(),
        '"' => "key_doublequote".into(),
        '\n' => "key_enter".into(),
        '=' => "key_equal".into(),
        '`' => "key_grave".into(),
        '#' => "key_hash".into(),
        '<' => "key_left_angle".into(),
        '[' => "key_left_brace".into(),
        '{' => "key_left_curly".into(),
        '(' => "key_left_paren".into(),
        '-' => "key_minus".into(),
        '%' => "key_percent".into(),
        '.' => "key_period".into(),
        '|' => "key_pipe".into(),
        '+' => "key_plus".into(),
        '?' => "key_question".into(),
        '\'' => "key_quote".into(),
        '>' => "key_right_angle".into(),
        ']' => "key_right_brace".into(),
        '}' => "key_right_curly".into(),
        ')' => "key_right_paren".into(),
        ';' => "key_semicolon".into(),
        '/' => "key_slash".into(),
        ' ' => "key_space".into(),
        '\t' => "key_tab".into(),
        '~' => "key_tilde".into(),
        '_' => "key_underscore".into(),
        _ => return None,
    };
    Some((Name(name), false))
}

fn backspace_chord() -> Option<Chord> {
    get_chord(Name("key_backspace".into()))
}

fn read_file_lines(path: &PathBuf) -> Result<Vec<String>> {
    let file = File::open(path)
        .chain_err(|| format!("failed to open file: {}", path.display()))?;
    let buf = BufReader::new(file);
    let lines: Vec<String> = buf.lines()
        .map(|w| w.unwrap())
        .filter(|s| !s.is_empty())
        .collect();
    Ok(lines)
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
