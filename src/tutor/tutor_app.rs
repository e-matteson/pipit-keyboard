use natord;

use cursive::align::HAlign;
use cursive::direction::Orientation;
use cursive::views::{
    Checkbox, Dialog, ListView, SelectView, SliderView, TextView,
};
use cursive::Cursive;

use types::errors::print_and_panic;
use types::TutorData;

use tutor::{load_lessons, Lesson, LessonConfig, State};

pub struct TutorApp;

impl TutorApp {
    pub fn run(data: TutorData) {
        State::set_tutor_data(data);
        State::load().ok(); // ignore errors

        let mut siv = Cursive::new();

        siv.load_theme_file("settings/tutor/color_theme.toml")
            .expect("failed to load theme");

        TutorApp::show_main_menu(&mut siv);
        siv.run();
    }

    fn show_main_menu(siv: &mut Cursive) {
        let items = vec!["Lessons", "Options", "Quit"];
        let select = SelectView::new()
            .h_align(HAlign::Left)
            .with_all_str(items)
            .on_submit(move |siv, item| match item {
                "Lessons" => TutorApp::show_lesson_menu(siv),
                "Options" => TutorApp::show_option_menu(siv),
                "Quit" => siv.quit(),
                _ => panic!("unknown menu item"),
            });
        siv.add_layer(Dialog::around(select).title("Pipit Typing Tutor"));
    }

    fn show_option_menu(siv: &mut Cursive) {
        let initial = State::initial_learn_state() as usize;
        let max = initial.max(10);

        let mut check_box = Checkbox::new();
        check_box.set_checked(State::allow_mistakes());

        let list = ListView::new()
            .child(
                "Mode:",
                SelectView::new()
                    .popup()
                    .with_all_str(State::mode_string_list())
                    .selected(State::current_mode_index())
                    .on_submit(|_siv, mode| State::set_mode(mode)),
            ).child(
                "Hint difficulty:",
                SliderView::new(Orientation::Horizontal, max)
                    .value(max - initial)
                    .on_change(move |_siv, value| {
                        State::set_initial_learn_state(max - value)
                    }),
            ).child(
                "Allow mistakes:",
                check_box
                    .on_change(|_siv, value| State::set_allow_mistakes(value)),
            );
        siv.add_layer(Dialog::new().title("Options").content(list).button(
            "Back",
            |siv| siv.pop_layer(), // TODO how to go back?
        ));
    }

    fn show_lesson_menu(siv: &mut Cursive) {
        let lessons = load_lessons("settings/tutor/lessons/")
            .expect("failed to get lessons");
        let mut names: Vec<String> = lessons.keys().cloned().collect();
        names.sort_by(|a, b| natord::compare(a, b));

        let mut select = SelectView::new().h_align(HAlign::Left);

        select.add_all_str(names);
        select.set_on_submit(move |siv, name| {
            let lesson = lessons.get(name).cloned().expect("lesson not found");
            TutorApp::show_lesson(siv, name, lesson)
        });

        siv.add_layer(
            Dialog::around(select)
                .title("Lessons")
                .button("Back", |siv| siv.pop_layer()),
        );
    }

    fn show_lesson(
        siv: &mut Cursive,
        _name: &str,
        lesson_config: LessonConfig,
    ) {
        let lesson = match Lesson::new(lesson_config) {
            Ok(lesson) => lesson,
            Err(error) => print_and_panic(error),
        };
        let popup = lesson.popup.clone();
        siv.add_layer(lesson);
        if !popup.is_empty() {
            siv.add_layer(Dialog::around(TextView::new(popup)).button(
                "Begin",
                |siv| {
                    siv.pop_layer(); // pop dialog
                },
            ))
        }
    }
}
