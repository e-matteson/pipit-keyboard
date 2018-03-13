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

use types::TutorData;
use types::errors::{print_and_panic, BadValueErr};
use failure::{Error, ResultExt};

use tutor::graphic::Graphic;
use tutor::utils::{offset, read_file_lines, set_tutor_data, Slide, SlideLine,
                   SlideWord};
use tutor::copier::Copier;

pub struct TutorApp;

struct Lesson {
    slides: Vec<Slide>,
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
        load_lessons("tutor/lessons/").expect("failed to get lessons");

        let lessons = fake_lessons();
        let mut names: Vec<String> = lessons.keys().cloned().collect();
        names.sort_by(|a, b| natord::compare(a, b));

        let mut select = SelectView::new().h_align(HAlign::Left);

        select.add_all_str(names);
        select.set_on_submit(move |siv, name| {
            TutorApp::cleanup_menu(siv);
            let slides = lessons.get(name).cloned().expect("lesson not found");
            TutorApp::show_lesson(siv, name, slides)
        });

        siv.add_layer(
            // Dialog::around(select.fixed_size((20, 10)))
            Dialog::around(select).title("Lessons"),
        );
    }

    fn cleanup_menu(siv: &mut Cursive) {
        siv.pop_layer();
    }

    fn show_lesson(siv: &mut Cursive, _name: &str, slides: Vec<Slide>) {
        let lesson = match Lesson::new(slides) {
            Ok(lesson) => lesson,
            Err(error) => print_and_panic(error),
        };
        siv.add_layer(lesson.with_id("text"));
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
    fn new(slides: Vec<Slide>) -> Result<Lesson, Error> {
        let copier = Copier::new(79);

        let mut lesson = Lesson {
            // TODO why reverse?
            slides: slides.into_iter().rev().collect(),
            graphic: Graphic::new(),
            graphic_spacing: 1,
            copier: copier,
            start_time: None,
            net_words: 0.,
        };
        lesson.next_slide().unwrap();
        lesson.update_chord()?;
        Ok(lesson)
    }

    fn next_slide(&mut self) -> Result<(), Error> {
        // TODO check for empty lessons when loading from file, instead
        // We should panic here instead if we failed to end the lesson after
        // going through all the slides.
        let slide = self.slides.pop().ok_or_else(|| BadValueErr {
            thing: "lesson contents".into(),
            value: "(empty)".into(),
        })?;
        self.copier.start_line(&slide.line)?;
        // TODO otherwise... other transition?
        Ok(())
    }

    fn update_chord(&mut self) -> Result<(), Error> {
        let next_char = self.copier.next_hint().context("failed to get hint")?;
        let last_wrong_char = self.copier
            .last_wrong_char()
            .expect("failed to check if char was wrong");
        self.graphic.update(next_char, last_wrong_char);
        Ok(())
    }

    fn state(&self) -> LessonState {
        // TODO what if no copier...
        // Should always exist, and start and stop timer as needed?
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

    fn size(&self) -> Vec2 {
        let graphic_size = self.graphic.size();
        let copy_size = self.copier.size();
        // self.copier.map(|c| c.size()).unwrap_or(Vec2::new(0, 0));
        let x = graphic_size.x.max(copy_size.x);
        let y = graphic_size.y + copy_size.y + self.graphic_spacing;
        Vec2::new(x, y)
    }
}

impl View for Lesson {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        // TODO draw nothing if copier is not in use?
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
            return EventResult::Consumed(Some(Callback::from_fn(
                TutorApp::show_confirm_back,
            )));
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
                    if self.slides.is_empty() {
                        // Lesson is done
                        let wpm = self.words_per_minute();
                        return EventResult::Consumed(Some(Callback::from_fn(
                            move |siv| TutorApp::end_lesson_callback(siv, wpm),
                        )));
                    }
                    // TODO don't unwrap
                    self.next_slide().unwrap();
                }
                _ => return EventResult::Ignored,
            },
        }

        if let Err(error) = self.update_chord() {
            print_and_panic(error);
        }

        EventResult::Consumed(None)
    }
}

fn load_lessons(
    lesson_dir: &str,
) -> Result<BTreeMap<String, Vec<String>>, Error> {
    let entries = fs::read_dir(lesson_dir)?;
    let mut map = BTreeMap::new();
    for entry in entries {
        let path = entry?.path();
        let name = lesson_path_to_name(&path);
        map.insert(name, read_file_lines(&path)?);
    }
    Ok(map)
}

fn fake_lessons() -> BTreeMap<String, Vec<Slide>> {
    vec![
        (
            "fake lesson".into(),
            vec![
                Slide {
                    line: SlideLine::Words {
                        check_errors: true,
                        words: vec![
                            SlideWord {
                                names: vec![
                                    "word_tap".into(),
                                    "mod_nospace".into(),
                                    "mod_capital".into(),
                                ],
                                text: "Tap".into(),
                            },
                            SlideWord {
                                names: vec![
                                    "word_ing".into(),
                                    "mod_double".into(),
                                ],
                                text: "ping".into(),
                            },
                        ],
                    },
                },
                Slide {
                    line: SlideLine::Letters("goodbye".into()),
                },
            ],
        ),
    ].into_iter()
        .collect()
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
