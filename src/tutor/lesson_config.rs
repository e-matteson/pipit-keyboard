use std::collections::BTreeMap;
use std::fmt;
use std::fs::{self, File};
use std::path::PathBuf;

use serde_yaml;

use error::{Error, ResultExt};
use types::Name;

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct LessonConfig {
    pub slides: Vec<Slide>,
    #[serde(default)]
    pub popup: String,
    #[serde(default)]
    pub persistent: Vec<String>,
}

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Slide {
    #[serde(default)]
    pub instruction: String,
    pub line: SlideLine,
}

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub enum SlideLine {
    Letters(String),
    Words {
        words: Vec<SlideWord>,
        #[serde(default = "return_true")]
        show_errors: bool,
    },
}

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct SlideWord {
    pub names: Vec<Name>,
    #[serde(default)]
    pub text: String,
    #[serde(default)]
    pub length_override: Option<usize>,
}

impl LessonConfig {
    pub fn from_file(path: &PathBuf) -> Result<LessonConfig, Error> {
        let file = File::open(path).with_context(|| {
            format!("Failed to open file: {}", path.display())
        })?;
        let lesson: LessonConfig =
            serde_yaml::from_reader(file).with_context(|| {
                format!("Failed to read lesson file: {}", path.display())
            })?;
        Ok(lesson)
    }

    pub fn load_directory(
        lesson_dir: &str,
    ) -> Result<BTreeMap<String, LessonConfig>, Error> {
        // TODO cleanup
        let paths: Result<Vec<PathBuf>, Error> =
            fs::read_dir(lesson_dir)?.map(|f| Ok(f?.path())).collect();
        let paths = paths?;
        let mut map = BTreeMap::new();
        for path in paths {
            if let Some(ext) = path.extension() {
                if ext == "yaml" {
                    map.insert(
                        LessonConfig::name_from_path(&path),
                        LessonConfig::from_file(&path)?,
                    );
                }
            }
        }
        Ok(map)
    }

    fn name_from_path(path: &PathBuf) -> String {
        // TODO return result
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
}

impl SlideLine {
    pub fn show_errors(&self) -> bool {
        match self {
            SlideLine::Letters(_) => true,
            SlideLine::Words { show_errors, .. } => *show_errors,
        }
    }

    pub fn has_length_overrides(&self) -> bool {
        match self {
            SlideLine::Letters(_) => false,
            SlideLine::Words { words, .. } => {
                words.iter().any(|w| w.length_override.is_some())
            }
        }
    }
}

impl fmt::Display for SlideWord {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.text.fmt(f)
    }
}

fn return_true() -> bool {
    true
}
