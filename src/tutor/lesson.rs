use std::time::Instant;

use cursive::event::{Callback, Event, EventResult, Key};
use cursive::theme::ColorStyle;
use cursive::traits::*;
use cursive::utils::lines::simple::make_lines;
use cursive::vec::Vec2;
use cursive::views::{Dialog, TextView};
use cursive::{Cursive, Printer};

use failure::{Error, ResultExt};
use types::errors::{print_and_panic, BadValueErr};

use tutor::{offset, Copier, Graphic, LessonConfig, PrevCharStatus, Slide};

pub struct Lesson {
    pub popup: String,
    slides: Vec<Slide>,
    graphic: Graphic,
    graphic_spacing: usize,
    instruction_spacing: usize,
    copier: Copier,
    start_time: Option<Instant>,
    net_words: f64,
    instruction: String,
    info_bar: String,
    info_bar_spacing: usize,
    total_slides: usize,
}

impl Lesson {
    pub fn new(config: LessonConfig) -> Result<Lesson, Error> {
        let copier = Copier::new(79);
        let slides: Vec<_> = config.slides.into_iter().rev().collect();
        let mut lesson = Lesson {
            // reverse slide order so we can pop them off the end of a vec
            total_slides: slides.len(),
            slides: slides,
            popup: config.popup,
            graphic: Graphic::new(),
            graphic_spacing: 1,
            instruction_spacing: 3,
            copier: copier,
            start_time: None,
            net_words: 0.,
            instruction: String::new(),
            info_bar: String::new(),
            info_bar_spacing: 1,
        };
        let status = lesson.next_slide().unwrap();
        lesson.update_chord(status)?;
        Ok(lesson)
    }

    fn next_slide(&mut self) -> Result<PrevCharStatus, Error> {
        // TODO check for empty lessons when loading from file, instead.
        // We should panic here instead if we failed to end the lesson after
        // going through all the slides.
        let slide = self.slides.pop().ok_or_else(|| BadValueErr {
            thing: "lesson contents".into(),
            value: "(empty)".into(),
        })?;
        self.copier.start_line(&slide.line)?;
        self.instruction = slide.instruction;
        self.info_bar =
            format!("Line {}.  Press `esc` to exit.", self.slide_counter());
        // TODO otherwise... other transition?
        Ok(PrevCharStatus::Correct)
    }

    fn slide_counter(&self) -> String {
        let current_num = self.total_slides - self.slides.len();
        format!("{}/{}", current_num, self.total_slides)
    }

    fn update_chord(&mut self, status: PrevCharStatus) -> Result<(), Error> {
        let next_char =
            self.copier.next_hint().context("failed to get hint")?;
        self.graphic.update(next_char, status);
        Ok(())
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
        // eprintln!("size: {:?}", self.instruction_size());
        let x = offset(self.instruction_size().x, self.size().x);
        Vec2::new(x, 0)
        // Vec2::new(5, 0)
    }

    fn copy_padding(&self) -> Vec2 {
        // eprintln!("padding: {:?}", self.instruction_padding());
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

    fn info_bar_size(&self) -> Vec2 {
        // This is making assumptions about size based on the length of the
        // string. Not sure why I can't just ask a TextView for its
        // size... And this panics if the string is longer than 1 line.
        let x = self.info_bar.len();
        // I would compare it to the total size, but that checks info_bar_size,
        // so we'd get infinite recursion. Comparing to the graphic
        // size is close enough.
        assert!(x < self.graphic.size().x);
        let y = 1;
        Vec2::new(x, y)
    }

    fn info_bar_padding(&self) -> Vec2 {
        let x = 1;
        let y = self.graphic_padding().y
            + self.graphic.size().y
            + self.info_bar_spacing;
        Vec2::new(x, y)
    }

    fn start_if_not_started(&mut self) {
        if self.start_time.is_none() {
            self.start_time = Some(Instant::now());
        }
    }

    fn minutes(&self) -> f64 {
        let mins = (self
            .start_time
            .expect("timer was not started")
            .elapsed()
            .as_secs() as f64)
            / 60.;
        mins
    }

    fn words_per_minute(&self) -> usize {
        (self.net_words / self.minutes()) as usize
    }

    fn size(&self) -> Vec2 {
        let graphic_size = self.graphic.size();
        let copy_size = self.copier.size();
        let instruction_size = self.instruction_size();
        let info_bar_size = self.info_bar_size();
        let x = graphic_size
            .x
            .max(copy_size.x)
            .max(instruction_size.x)
            .max(info_bar_size.x);

        let y = info_bar_size.y
            + graphic_size.y
            + copy_size.y
            + instruction_size.y
            + self.info_bar_spacing
            + self.graphic_spacing
            + self.instruction_spacing;
        Vec2::new(x, y)
    }

    fn draw_instruction(&self, printer: &Printer) {
        printer.with_color(ColorStyle::primary(), |printer| {
            printer.print((self.instruction_padding().x, 0), &self.instruction);
        });
    }

    fn draw_info_bar(&self, printer: &Printer) {
        printer.with_color(ColorStyle::title_primary(), |printer| {
            printer.print(self.info_bar_padding(), &self.info_bar);
        });
    }
}

impl View for Lesson {
    fn required_size(&mut self, _constraint: Vec2) -> Vec2 {
        self.size()
    }

    fn draw(&self, printer: &Printer) {
        // eprintln!(
        //     "copy pad: {:?}, size: {:?}",
        //     self.copy_padding(),
        //     self.copier.size()
        // );
        let fake_padding =
            self.copy_padding() - Vec2::new(0, self.instruction_spacing);
        // eprintln!("fake pad: {:?} ", fake_padding);
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
        ));

        self.draw_info_bar(printer)
    }

    fn on_event(&mut self, event: Event) -> EventResult {
        if let Event::Key(Key::Esc) = event {
            return EventResult::Consumed(Some(Callback::from_fn(
                show_confirm_back,
            )));
        }
        let status = match event {
            Event::Key(Key::Backspace) => self.copier.type_backspace(),
            Event::Char(letter) => {
                self.start_if_not_started();
                self.copier.type_char(letter)
            }
            Event::CtrlChar('j') | Event::Key(Key::Enter)
                if self.copier.at_end_of_line() =>
            {
                // End the line, and maybe the whole lesson.
                self.net_words += self.copier.net_words();
                if self.slides.is_empty() {
                    // Lesson is done
                    let wpm = self.words_per_minute();
                    return EventResult::Consumed(Some(Callback::from_fn(
                        move |siv| end_lesson_callback(siv, wpm),
                    )));
                }
                self.next_slide().expect("failed to get next slide")
            }
            _ => return EventResult::Ignored,
        };

        if let Err(error) = self.update_chord(status) {
            print_and_panic(error);
        }

        EventResult::Consumed(None)
    }
}

fn end_lesson_callback(siv: &mut Cursive, wpm: usize) {
    let message = format!("Lesson complete.\nNet WPM: {}", wpm);
    siv.add_layer(Dialog::around(TextView::new(message)).button(
        "Back",
        |siv| {
            siv.pop_layer(); // pop dialog
            siv.pop_layer(); // pop lesson
        },
    ));
}

fn show_confirm_back(siv: &mut Cursive) {
    siv.add_layer(
        Dialog::around(TextView::new("Return to lesson menu?"))
            .dismiss_button("Cancel")
            .button("Yes", |siv| {
                siv.pop_layer(); // pop dialog
                siv.pop_layer(); // pop lesson
            }),
    )
}
