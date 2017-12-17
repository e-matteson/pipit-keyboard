use std::collections::BTreeMap;
use std::fs;
use std::path::PathBuf;
use std::time::Instant;

use natord;

use cursive::{Cursive, Printer};
use cursive::align::HAlign;
use cursive::traits::*;
use cursive::views::{Dialog, SelectView, TextView};
use cursive::vec::Vec2;
use cursive::event::{Callback, Event, EventResult, Key};

use types::errors::*;
use tutor::graphic::Graphic;
use tutor::utils::{offset, read_file_lines, set_tutor_data, TutorData};
use tutor::copier::Copier;

pub struct TutorApp;

struct Lesson {
    lines: Vec<String>,
    graphic: Graphic,
    graphic_spacing: usize,
    copier: Copier,
    start_time: Option<Instant>,
    net_words: f64,
}

enum LessonState {
    Typing,
    EndOfLine,
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

    fn end_lesson_callback(siv: &mut Cursive, wpm: usize) {
        let message = format!("Lesson complete.\nNet WPM: {}", wpm);
        siv.add_layer(Dialog::around(TextView::new(message)).button(
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
        let copier = Copier::new(79);

        let mut lesson = Lesson {
            lines: lines.into_iter().rev().collect(),
            graphic: Graphic::new(),
            graphic_spacing: 1,
            copier: copier,
            start_time: None,
            net_words: 0.,
        };
        lesson.next_line();
        lesson.update_chord();
        lesson
    }

    fn size(&self) -> Vec2 {
        let graphic_size = self.graphic.size();
        let copy_size = self.copier.size();
        let x = graphic_size.x.max(copy_size.x);
        let y = graphic_size.y + copy_size.y + self.graphic_spacing;
        Vec2::new(x, y)
    }

    fn next_line(&mut self) {
        self.copier
            .start_line(&self.lines.pop().expect("lesson was empty"))
    }

    fn state(&self) -> LessonState {
        if self.copier.at_end_of_line() {
            LessonState::EndOfLine
        } else {
            LessonState::Typing
        }
    }

    fn graphic_padding(&self) -> Vec2 {
        let x = offset(self.graphic.size().x, self.size().x);
        let y = self.copier.size().y + self.graphic_spacing;
        Vec2::new(x, y)
    }

    fn copy_padding(&self) -> Vec2 {
        let x = offset(self.copier.size().x, self.size().x);
        Vec2::new(x, 0)
    }

    fn update_chord(&mut self) {
        let next_char = self.copier.next_hint();
        let last_wrong_char = self.copier
            .last_wrong_char()
            .expect("failed to check if char was wrong");
        self.graphic.update(next_char, last_wrong_char);
    }

    fn start_if_not_started(&mut self) {
        if self.start_time.is_none() {
            self.start_time = Some(Instant::now());
        }
    }

    fn minutes(&self) -> f64 {
        let mins = (self.start_time
            .expect("timer was not started")
            .elapsed()
            .as_secs() as f64) / 60.;
        mins
    }

    fn words_per_minute(&self) -> usize {
        (self.net_words / self.minutes()) as usize
    }
}

impl View for Lesson {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        self.copier.draw(&printer.sub_printer(
            self.copy_padding(),
            self.copier.size(),
            false,
        ));
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
                Event::Key(Key::Backspace) => self.copier.type_backspace(),
                Event::Char(letter) => {
                    self.copier.type_char(letter);
                    self.start_if_not_started()
                }
                _ => return EventResult::Ignored,
            },
            LessonState::EndOfLine => match event {
                Event::Key(Key::Backspace) => self.copier.type_backspace(),
                Event::CtrlChar('j') | Event::Key(Key::Enter) => {
                    self.net_words += self.copier.net_words();
                    eprintln!(
                        "net_words: {}, minutes: {}",
                        self.net_words,
                        self.minutes()
                    );
                    if self.lines.is_empty() {
                        // Lesson is done
                        let wpm = self.words_per_minute();
                        return EventResult::Consumed(Some(Callback::from_fn(
                            move |siv| TutorApp::end_lesson_callback(siv, wpm),
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
