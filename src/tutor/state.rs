use rand::seq::IteratorRandom;
use serde_yaml;
use std::collections::HashMap;
use std::fs::File;
use std::fs::OpenOptions;
use std::io::Write;
use std::path::PathBuf;
use std::sync::Mutex;

use error::{Error, ResultExt};
use types::{
    Chord, KeyDefs, KmapOrder, ModeName, Name, Spelling, TutorData,
    WordSpacePosition,
};

lazy_static! {
    static ref STATE: Mutex<Option<InnerState>> = Mutex::new(None);
}

#[derive(Debug, Clone)]
pub struct InnerState {
    tutor_data: TutorData,
    learning_map: HashMap<String, LearnState>,
    save_path: PathBuf,
    saveable: SaveableSettings,
}

// TODO module instead?
#[derive(Debug, Clone)]
pub struct State;

#[derive(Debug, Clone, Deserialize, Serialize)]
#[serde(deny_unknown_fields)]
pub struct SaveableSettings {
    initial_learn_state: usize,
    mode: ModeName,
    allow_mistakes: bool,
    show_persistent_letters: bool,
}

#[derive(Debug, Clone)]
pub struct LearnState(pub usize);

impl InnerState {
    fn save_settings(&self) -> Result<(), Error> {
        let s = serde_yaml::to_string(&self.saveable)?;
        let mut file = OpenOptions::new()
            .create(true)
            .write(true)
            .open(&self.save_path)
            .context("Failed to open output file")?;

        file.set_len(0).context("Failed to clear output file")?;

        file.write_all(s.as_bytes())
            .context("Failed to write to output file")?;
        Ok(())
    }

    fn chord(&self, name: &Name) -> Result<Chord<KmapOrder>, Error> {
        self.tutor_data.chord(name, &self.saveable.mode)
    }

    fn chord_from_spelling(
        &self,
        spelling: Spelling,
    ) -> Option<Chord<KmapOrder>> {
        let mut names = self.names(spelling).into_iter();

        // TODO fold?
        let mut chord = self.chord(&names.next()?).ok()?;
        for name in names {
            chord.union_mut(&self.chord(&name).ok()?).ok()?;
        }
        Some(chord)
    }

    fn names(&self, spelling: Spelling) -> Vec<Name> {
        self.tutor_data.spellings.get(spelling)
    }

    fn is_learned(&self, name: &str) -> Option<bool> {
        self.learning_map.get(name).map(|state| state.is_learned())
    }

    fn update_learn_state(&mut self, name: String, was_correct: bool) {
        let initial_learn_state = self.saveable.initial_learn_state;
        self.learning_map
            .entry(name)
            .or_insert_with(|| LearnState(initial_learn_state))
            .update(was_correct);
    }

    fn set_initial_learn_state(&mut self, initial: usize) {
        for learn_state in self.learning_map.values_mut() {
            learn_state.reset(initial);
        }
        self.saveable.initial_learn_state = initial;

        // ignore any errors while saving
        self.save_settings().ok();
    }

    fn set_allow_mistakes(&mut self, value: bool) {
        self.saveable.allow_mistakes = value;

        // ignore any errors while saving
        self.save_settings().ok();
    }

    fn set_show_persistent_letters(&mut self, value: bool) {
        self.saveable.show_persistent_letters = value;
        // ignore any errors while saving
        self.save_settings().ok();
    }

    fn mode_list(&self) -> Vec<ModeName> {
        self.tutor_data.chords.keys().cloned().collect()
    }

    fn mode_index(&self, mode: &ModeName) -> Option<usize> {
        self.mode_list().into_iter().position(|m| &m == mode)
    }

    fn current_mode_index(&self) -> usize {
        self.mode_index(&self.saveable.mode)
            .expect("current mode not found in list")
    }

    fn set_mode(&mut self, mode_str: &str) {
        let mode = ModeName::from(mode_str);
        if !self.tutor_data.chords.contains_key(&mode) {
            panic!("tried to switch to unknown ModeName: {}", mode);
        }
        self.saveable.mode = mode;

        // Reset the learning state for each letter, since the chords could be
        // totally different now.
        let initial = self.saveable.initial_learn_state;
        for learn_state in self.learning_map.values_mut() {
            learn_state.reset(initial);
        }
        // ignore any errors while saving
        self.save_settings().ok();
    }

    fn random_word_names(&self, count: usize) -> Vec<Name> {
        self.tutor_data
            .word_sequences
            .names()
            .choose_multiple(&mut rand::thread_rng(), count)
            .into_iter()
            .cloned()
            .collect()
    }

    fn word_spelling(&self, word_name: &Name) -> Result<String, Error> {
        let seq =
            self.tutor_data
                .word_sequences
                .get(word_name)
                .ok_or_else(|| Error::LookupErr {
                    key: word_name.into(),
                    container: "words".into(),
                })?;
        seq.keypresses()
            .map(|keypress| {
                let spelling =
                    KeyDefs::spelling_from_keypress_any_case(keypress)?;
                Ok(spelling.0)
            })
            .collect()
    }
}

impl State {
    pub fn initialize(tutor_data: TutorData) -> Result<(), Error> {
        let mut state = STATE.lock().unwrap();
        assert!(state.is_none(), "State was already initialized");

        // TODO don't hardcode path
        let save_path = PathBuf::from("settings/tutor/saved_options.yaml");
        let saveable = SaveableSettings::from_file(&save_path, &tutor_data)?
            .unwrap_or_default();
        let inner = InnerState {
            tutor_data,
            learning_map: HashMap::new(),
            save_path,
            saveable,
        };

        *state = Some(inner);
        Ok(())
    }

    pub fn chord(name: &Name) -> Result<Chord<KmapOrder>, Error> {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .chord(name)
    }

    pub fn chord_from_spelling(spelling: Spelling) -> Option<Chord<KmapOrder>> {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .chord_from_spelling(spelling)
    }

    pub fn is_learned(name: &str) -> Option<bool> {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .is_learned(name)
    }

    pub fn update_learn_state(name: String, was_correct: bool) {
        STATE
            .lock()
            .unwrap()
            .as_mut()
            .expect("state not set")
            .update_learn_state(name, was_correct);
    }

    pub fn initial_learn_state() -> usize {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .saveable
            .initial_learn_state
    }

    pub fn set_initial_learn_state(initial: usize) {
        STATE
            .lock()
            .unwrap()
            .as_mut()
            .expect("state not set")
            .set_initial_learn_state(initial)
    }

    pub fn allow_mistakes() -> bool {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .saveable
            .allow_mistakes
    }

    pub fn set_allow_mistakes(value: bool) {
        STATE
            .lock()
            .unwrap()
            .as_mut()
            .expect("state not set")
            .set_allow_mistakes(value)
    }

    pub fn show_persistent_letters() -> bool {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .saveable
            .show_persistent_letters
    }

    pub fn set_show_persistent_letters(value: bool) {
        STATE
            .lock()
            .unwrap()
            .as_mut()
            .expect("state not set")
            .set_show_persistent_letters(value)
    }

    pub fn mode_string_list() -> Vec<String> {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .mode_list()
            .into_iter()
            .map(|mode| mode.0.clone())
            .collect()
    }

    pub fn current_mode_index() -> usize {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .current_mode_index()
    }

    pub fn set_mode(mode_str: &str) {
        STATE
            .lock()
            .unwrap()
            .as_mut()
            .expect("state not set")
            .set_mode(mode_str)
    }

    pub fn word_space_position() -> WordSpacePosition {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .tutor_data
            .word_space_position
    }

    pub fn word_spelling(word_name: &Name) -> Result<String, Error> {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .word_spelling(word_name)
    }

    pub fn random_word_names(count: usize) -> Vec<Name> {
        STATE
            .lock()
            .unwrap()
            .as_ref()
            .expect("state not set")
            .random_word_names(count)
    }
}

impl Default for SaveableSettings {
    fn default() -> SaveableSettings {
        SaveableSettings {
            initial_learn_state: 2,
            mode: ModeName::default(),
            allow_mistakes: false,
            show_persistent_letters: false,
        }
    }
}

impl SaveableSettings {
    pub fn from_file(
        path: &PathBuf,
        tutor_data: &TutorData,
    ) -> Result<Option<Self>, Error> {
        if let Ok(file) = File::open(path) {
            let settings: SaveableSettings = serde_yaml::from_reader(file)
                .with_context(|| {
                    format!("failed to read file: {}", path.display())
                })?;
            settings.validate(tutor_data)?;
            Ok(Some(settings))
        } else {
            Ok(None)
        }
    }

    pub fn validate(&self, tutor_data: &TutorData) -> Result<(), Error> {
        if !tutor_data.chords.contains_key(&self.mode) {
            Err(Error::LookupErr {
                key: self.mode.to_string(),
                container: "known mode names".to_owned(),
            })
        } else {
            Ok(())
        }
    }
}

impl TutorData {
    pub fn chord(
        &self,
        name: &Name,
        mode: &ModeName,
    ) -> Result<Chord<KmapOrder>, Error> {
        if name.is_empty() {
            // Used for skipping colors in the cheatsheet config
            return Ok(self.chord_spec.new_chord());
        }
        self.chords
            .get(mode)
            .ok_or_else(|| Error::LookupErr {
                key: mode.to_string(),
                container: "tutor data modes".to_owned(),
            })?
            .get(name)
            .cloned()
            .ok_or_else(|| Error::LookupErr {
                key: name.into(),
                container: "tutor data chords".to_owned(),
            })
    }
}

impl LearnState {
    pub fn update(&mut self, was_correct: bool) {
        if was_correct {
            if self.0 > 0 {
                self.0 -= 1;
            }
        } else {
            self.0 += 1;
        }
    }

    pub fn reset(&mut self, initial: usize) {
        self.0 = initial;
    }

    pub fn is_learned(&self) -> bool {
        self.0 == 0
    }
}
