use error::{Error, ResultExt};
use tutor::{LessonConfig, SlideLine, SlideWord, State};
use types::{Name, WordSpacePosition};

fn word_spelling(word_name: &Name) -> Result<String, Error> {
    let word = State::word_spelling(word_name)?;
    Ok(match State::word_space_position() {
        WordSpacePosition::Before => format!(" {}", word),
        WordSpacePosition::After => format!("{} ", word),
        WordSpacePosition::None => word,
    })
}

pub fn create_random_words() -> Result<LessonConfig, Error> {
    let word_names = State::random_word_names(50);

    let words = word_names
        .into_iter()
        .map(|name| {
            Ok(SlideWord {
                text: word_spelling(&name)?,
                names: vec![name.clone()],
                length_override: None,
            })
        })
        .collect::<Result<Vec<_>, Error>>()
        .context("failed to generate random words")?;

    let slides = vec![SlideLine::Words {
        words,
        show_errors: true,
    }
    .into()];

    let persistent = Vec::new();
    Ok(LessonConfig {
        slides,
        popup: "Practice chording these random words from the dictionary"
            .to_owned(),
        persistent,
    })
}
