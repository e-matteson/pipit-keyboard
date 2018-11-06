use std::collections::BTreeMap;
use std::fs::{self, File};
use std::path::PathBuf;

use serde_yaml;
use unicode_segmentation::UnicodeSegmentation;

use error::{Error, ResultExt};
use tutor::Slide;

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct LessonConfig {
    pub slides: Vec<Slide>,
    #[serde(default)]
    pub popup: String,
}

pub fn offset(width1: usize, width2: usize) -> usize {
    ((width2 - width1) as f32 / 2.).round() as usize
}

pub fn load_lessons(
    lesson_dir: &str,
) -> Result<BTreeMap<String, LessonConfig>, Error> {
    let entries = fs::read_dir(lesson_dir)?;
    let mut map = BTreeMap::new();
    for entry in entries {
        let path: PathBuf = entry?.path();
        if path.extension().map(|ext| ext != "yaml").unwrap_or(true) {
            continue;
        }
        let name = lesson_path_to_name(&path);
        map.insert(name, read_lesson_file(&path)?);
    }
    Ok(map)
}

fn lesson_path_to_name(path: &PathBuf) -> String {
    let s = path
        .file_stem()
        .expect("invalid lesson file name")
        .to_str()
        .expect("lesson path is not valid unicode");
    let mut sections = s.split('_');
    let number = sections.next().expect("invalid lesson file name");
    let words: Vec<_> = sections.collect();
    format!("{}) {}", number, words.join(" "))
}

pub fn read_lesson_file(path: &PathBuf) -> Result<LessonConfig, Error> {
    let file = open_file(path)
        .with_context(|| format!("Failed to open file: {}", path.display()))?;
    let lesson: LessonConfig =
        serde_yaml::from_reader(file).with_context(|| {
            format!("Failed to read lesson file: {}", path.display())
        })?;
    Ok(lesson)
}

fn open_file(path: &PathBuf) -> Result<File, Error> {
    Ok(File::open(path)?)
}

pub fn grapheme_slice<'a>(
    s: &'a str,
    start: usize,
    end: usize,
) -> impl Iterator<Item = &'a str> {
    s.graphemes(true).skip(start).take(end)
}
