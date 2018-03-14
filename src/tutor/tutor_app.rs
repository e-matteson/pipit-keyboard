use std::time::Instant;

use natord;

use cursive::{Cursive, Printer};
use cursive::align::HAlign;
use cursive::traits::*;
use cursive::views::{Dialog, SelectView, TextView};
use cursive::vec::Vec2;
use cursive::event::{Callback, Event, EventResult, Key};
use cursive::utils::lines::simple::make_lines;
use cursive::theme::ColorStyle;

use types::TutorData;
use types::errors::{print_and_panic, BadValueErr};
use failure::{Error, ResultExt};

use tutor::graphic::Graphic;
use tutor::utils::{load_lessons, offset, set_tutor_data, Slide};
use tutor::copier::Copier;

pub struct TutorApp;

struct Lesson {
    slides: Vec<Slide>,
    graphic: Graphic,
    graphic_spacing: usize,
    instruction_spacing: usize,
    copier: Copier,
    start_time: Option<Instant>,
    net_words: f64,
    instruction: String,
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
            instruction_spacing: 3,
            copier: copier,
            start_time: None,
            net_words: 0.,
            instruction: String::new(),
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
        self.instruction = slide.instruction;
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
        if self.copier.at_end_of_line() {
            LessonState::EndOfLine
        } else {
            LessonState::Typing
        }
    }

    fn instruction_size(&self) -> Vec2 {
        let max_width = 80;
        let rows = make_lines(&self.instruction, max_width);
        if rows.len() > 1 {
            panic!("instruction is too long!")
        }
        if rows.len() == 0 {
            Vec2::new(0, 1)
        } else {
            let row = rows[0];
            Vec2::new(row.width, 1)
            // Vec2::new(max_width, 1)
        }
    }

    fn instruction_padding(&self) -> Vec2 {
        eprintln!("size: {:?}", self.instruction_size());
        let x = offset(self.instruction_size().x, self.size().x);
        Vec2::new(x, 0)
        // Vec2::new(5, 0)
    }

    fn copy_padding(&self) -> Vec2 {
        eprintln!("padding: {:?}", self.instruction_padding());
        let x = offset(self.copier.size().x, self.size().x);
        let y = self.instruction_padding().y + self.instruction_spacing;
        Vec2::new(x, y)
    }

    fn graphic_padding(&self) -> Vec2 {
        let x = offset(self.graphic.size().x, self.size().x);
        let y =
            self.copy_padding().y + self.copier.size().y + self.graphic_spacing;
        Vec2::new(x, y)
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
        let instruction_size = self.instruction_size();
        let x = graphic_size.x.max(copy_size.x).max(instruction_size.x);

        let y = graphic_size.y + copy_size.y + self.graphic_spacing
            + instruction_size.y + self.instruction_spacing;
        // let y = graphic_size.y + self.graphic_padding().y;
        Vec2::new(x, y)
    }

    fn draw_instruction(&self, printer: &Printer) {
        printer.with_color(ColorStyle::title_primary(), |printer| {
            printer.print((self.instruction_padding().x, 0), &self.instruction);
        });
    }
}

impl View for Lesson {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        // TODO draw nothing if copier is not in use?
        eprintln!(
            "copy pad: {:?}, size: {:?}",
            self.copy_padding(),
            self.copier.size()
        );
        let fake_padding =
            self.copy_padding() - Vec2::new(0, self.instruction_spacing);
        eprintln!("fake pad: {:?} ", fake_padding);
        self.draw_instruction(&printer.sub_printer(
            // self.instruction_padding(),
            // self.instruction_size() + self.instruction_padding(),
            fake_padding,
            self.copier.size(),
            false,
        ));
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
                Event::Char(letter) => {
                    // Let them keep typing past the end of the line (important
                    // for cycling to shorter words)
                    self.copier.type_char(letter);
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
