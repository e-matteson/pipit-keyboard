use std::collections::BTreeMap;
use std::fs;
use std::path::PathBuf;

use natord;

use cursive::{Cursive, Printer};
use cursive::align::HAlign;
use cursive::traits::*;
use cursive::views::{Dialog, SelectView, TextView};
use cursive::vec::Vec2;
use cursive::theme::ColorStyle;
use cursive::event::{Callback, Event, EventResult, Key};

use types::{Chord, Name};
use types::errors::*;
use tutor::graphic::Graphic;
use tutor::utils::{char_to_chord, char_to_label, grapheme_slice,
                   read_file_lines, TutorData};

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



impl TutorApp {
    pub fn run(data: TutorData) {
        TutorData::set(data);

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

    fn last_wrong_char(&self) -> Result<Option<char>> {
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
        self.graphic.next_chord = char_to_chord(character);
        self.graphic.next_label = Some(char_to_label(character));

        if let Some(character) = self.last_wrong_char()
            .expect("failed to check if char was wrong")
        {
            self.graphic.backspace_chord = backspace_chord();
            self.graphic.backspace_label = Some("bak".into());
            self.graphic.error_chord = char_to_chord(character);
            self.graphic.error_label = Some(char_to_label(character));
        } else {
            self.graphic.backspace_chord = None;
            self.graphic.backspace_label = None;
            self.graphic.error_chord = None;
            self.graphic.error_label = None;
        }
        self.graphic.update_switches();
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

fn get_style(actual_char: &str, expected_char: &str) -> ColorStyle {
    if actual_char == expected_char {
        ColorStyle::Primary
    } else {
        ColorStyle::Secondary
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


fn offset(width1: usize, width2: usize) -> usize {
    ((width2 - width1) as f32 / 2.).round() as usize
}

fn backspace_chord() -> Option<Chord> {
    TutorData::get_chord(Name("key_backspace".into()))
}
