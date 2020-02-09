use natord;

use cursive::align::HAlign;
use cursive::direction::Orientation;
use cursive::views::{
    Checkbox, Dialog, ListView, SelectView, SliderView, TextView,
};
use cursive::Cursive;

use types::TutorData;

use tutor::{create_random_words, Lesson, LessonConfig, State};

pub struct TutorApp;

impl TutorApp {
    pub fn run(data: TutorData) {
        State::initialize(data).expect("failed to initialize global state");

        let mut siv = Cursive::default();

        siv.load_theme_file("settings/tutor/color_theme.toml")
            .expect("failed to load theme");

        Self::show_main_menu(&mut siv);
        siv.run();
    }

    fn show_main_menu(siv: &mut Cursive) {
        let items = vec!["Lessons", "Random Words", "Options", "Quit"];
        let select = SelectView::new()
            .h_align(HAlign::Left)
            .with_all_str(items)
            .on_submit(move |siv, item| match item {
                "Lessons" => Self::show_lesson_menu(siv),
                "Random Words" => Self::show_random_words(siv),
                "Options" => Self::show_option_menu(siv),
                "Quit" => siv.quit(),
                _ => panic!("unknown menu item"),
            });
        siv.add_layer(Dialog::around(select).title("Pipit Typing Tutor"));
    }

    fn show_option_menu(siv: &mut Cursive) {
        let initial = State::initial_learn_state() as usize;
        let max = initial.max(10);

        let mut mistakes_box = Checkbox::new();
        mistakes_box.set_checked(State::allow_mistakes());

        let mut persistence_box = Checkbox::new();
        persistence_box.set_checked(State::show_persistent_letters());

        let list = ListView::new()
            .child(
                "Mode:",
                SelectView::new()
                    .popup()
                    .with_all_str(State::mode_string_list())
                    .selected(State::current_mode_index())
                    .on_submit(|_siv, mode| State::set_mode(mode)),
            )
            .child(
                "Hint difficulty:",
                SliderView::new(Orientation::Horizontal, max)
                    .value(max - initial)
                    .on_change(move |_siv, value| {
                        State::set_initial_learn_state(max - value)
                    }),
            )
            .child(
                "Allow mistakes:",
                mistakes_box
                    .on_change(|_siv, value| State::set_allow_mistakes(value)),
            )
            .child(
                "Show persistent hints for the lesson's new letters:",
                persistence_box.on_change(|_siv, value| {
                    State::set_show_persistent_letters(value)
                }),
            );
        siv.add_layer(Dialog::new().title("Options").content(list).button(
            "Back",
            |siv| {
                siv.pop_layer().expect("No layer to pop!");
            },
        ));
    }

    fn show_lesson_menu(siv: &mut Cursive) {
        // TODO don't hardcode
        let lessons = LessonConfig::load_directory("settings/tutor/lessons/")
            .expect("failed to get lessons");

        let mut names: Vec<String> = lessons.keys().cloned().collect();
        names.sort_by(|a, b| natord::compare(a, b));

        let mut select = SelectView::new().h_align(HAlign::Left);

        select.add_all_str(names);
        select.set_on_submit(move |siv, name: &str| {
            let lesson = lessons.get(name).cloned().expect("lesson not found");
            Self::show_lesson(siv, lesson)
        });

        siv.add_layer(Dialog::around(select).title("Lessons").button(
            "Back",
            |siv| {
                siv.pop_layer().expect("No layer to pop!");
            },
        ));
    }

    fn show_random_words(siv: &mut Cursive) {
        let config = create_random_words().unwrap();
        Self::show_lesson(siv, config)
    }

    fn show_lesson(siv: &mut Cursive, lesson_config: LessonConfig) {
        // TODO will unwrap print nicely?
        let lesson = Lesson::new(lesson_config).unwrap();
        let popup = lesson.popup.clone();
        siv.add_layer(lesson);
        if !popup.is_empty() {
            siv.add_layer(Dialog::around(TextView::new(popup)).button(
                "Begin",
                |siv| {
                    siv.pop_layer();
                },
            ))
        }
    }
}
