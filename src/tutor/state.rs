use std::sync::Mutex;
use std::collections::HashMap;
use std::path::PathBuf;
use std::fs::File;
use std::io::Write;
use std::fs::OpenOptions;
use serde_yaml;

use types::{Chord, ModeName, Name, Spelling, TutorData};
use failure::{Error, ResultExt};

lazy_static! {
    static ref STATE: Mutex<State> = Mutex::new(State::new());
}

#[derive(Debug, Clone)]
pub struct State {
    tutor_data: Option<TutorData>,
    learning_map: HashMap<String, LearnState>,
    save_path: PathBuf,
    saveable: Saveable,
}

#[derive(Debug, Clone, Deserialize, Serialize)]
#[serde(deny_unknown_fields)]
pub struct Saveable {
    initial_learn_state: usize,
    mode: ModeName,
    freeze_on_error: bool,
}

#[derive(Debug, Clone)]
pub struct LearnState(pub usize);

impl State {
    fn new() -> State {
        State {
            tutor_data: None,
            learning_map: HashMap::new(),
            save_path: PathBuf::from("settings/tutor/saved_options.yaml"),
            saveable: Saveable {
                initial_learn_state: 10,
                mode: ModeName::default(),
                freeze_on_error: true,
            },
        }
    }

    pub fn load() -> Result<(), Error> {
        eprintln!("load");
        let path = State::save_path();
        let saveable = read_state_file(&path)?;
        saveable.validate()?;
        STATE.lock().unwrap().saveable = saveable;
        Ok(())
    }

    pub fn save(&self) -> Result<(), Error> {
        let s = serde_yaml::to_string(&self.saveable)?;
        eprintln!("{:?}", s);
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

    fn save_path() -> PathBuf {
        STATE.lock().unwrap().save_path.clone()
    }

    pub fn set_tutor_data(data: TutorData) {
        let mut state = STATE.lock().unwrap();
        match state.tutor_data {
            Some(_) => panic!("tutor data can only be set once"),
            None => state.tutor_data = Some(data),
        }
    }

    pub fn chord(name: &Name) -> Option<Chord> {
        if name == &Name(String::new()) {
            // Used for skipping colors in the cheatsheet config
            return Some(Chord::default());
        }

        let state = STATE.lock().unwrap();
        if let Some(ref data) = state.tutor_data {
            data.chords.get(&state.saveable.mode)?.get(name).cloned()
        } else {
            panic!("tutor data was not set")
        }
    }

    pub fn chord_from_spelling(spelling: &Spelling) -> Option<Chord> {
        let name = State::name(&spelling)?;
        let mut chord = State::chord(&name)?;
        if spelling.is_uppercase() {
            chord.intersect(&State::chord(&Name("mod_shift".into()))?)
        }
        Some(chord)
    }

    fn name(spelling: &Spelling) -> Option<Name> {
        let state = STATE.lock().unwrap();
        if let Some(ref data) = state.tutor_data {
            data.spellings.get(spelling).map(|name| name.clone())
        } else {
            panic!("tutor data was not set")
        }
    }

    pub fn is_learned(name: &str) -> Option<bool> {
        STATE
            .lock()
            .unwrap()
            .learning_map
            .get(name)
            .map(|state| state.is_learned())
    }

    pub fn update_learn_state(name: String, was_correct: bool) {
        let mut state = STATE.lock().unwrap();
        let initial_learn_state = state.saveable.initial_learn_state;
        state
            .learning_map
            .entry(name)
            .or_insert_with(|| LearnState(initial_learn_state))
            .update(was_correct);
    }

    pub fn initial_learn_state() -> usize {
        STATE.lock().unwrap().saveable.initial_learn_state
    }

    pub fn freeze_on_error() -> bool {
        STATE.lock().unwrap().saveable.freeze_on_error
    }

    pub fn set_freeze_on_error(value: bool) {
        let mut state = STATE.lock().unwrap();
        state.saveable.freeze_on_error = value;

        // ignore any errors while saving
        state.save().ok();
    }

    pub fn set_initial_learn_state(initial: usize) {
        let mut state = STATE.lock().unwrap();
        for (_, learn_state) in state.learning_map.iter_mut() {
            learn_state.reset(initial);
        }
        state.saveable.initial_learn_state = initial;

        // ignore any errors while saving
        state.save().ok();
    }

    fn mode_list() -> Vec<ModeName> {
        let state = STATE.lock().unwrap();
        if let Some(ref data) = state.tutor_data {
            data.chords.keys().cloned().collect()
        } else {
            panic!("tutor data was not set")
        }
    }

    pub fn mode_string_list() -> Vec<String> {
        State::mode_list()
            .into_iter()
            .map(|mode| mode.0.clone())
            .collect()
    }

    fn mode_index(mode: &ModeName) -> Option<usize> {
        State::mode_list().into_iter().position(|m| &m == mode)
    }

    pub fn current_mode_index() -> usize {
        let mode = STATE.lock().unwrap().saveable.mode.clone();
        State::mode_index(&mode).expect("current mode not found in list")
    }

    pub fn set_mode(mode_str: &str) {
        let mode = ModeName::from(mode_str);
        let mut state = STATE.lock().unwrap();
        if let Some(ref data) = state.tutor_data {
            if !data.chords.contains_key(&mode) {
                panic!("tried to switch unknown ModeName: {}", mode);
            }
        } else {
            panic!("tutor data was not set")
        }

        state.saveable.mode = mode;

        // Reset the learning state for each letter, since the chords could be
        // totally different now.
        let initial = state.saveable.initial_learn_state;
        for (_, learn_state) in state.learning_map.iter_mut() {
            learn_state.reset(initial);
        }
        // ignore any errors while saving
        state.save().ok();
    }
}
impl Saveable {
    pub fn validate(&self) -> Result<(), Error> {
        State::mode_index(&self.mode)
            .ok_or(format_err!("Unknown ModeName: {}", &self.mode))?;
        Ok(())
    }
}

impl TutorData {
    pub fn chord(&self, name: &Name, mode: &ModeName) -> Option<Chord> {
        if name == &Name(String::new()) {
            // Used for skipping colors in the cheatsheet config
            return Some(Chord::default());
        }
        self.chords.get(mode)?.get(name).cloned()
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

pub fn read_state_file(path: &PathBuf) -> Result<Saveable, Error> {
    let file = File::open(path)
        .context(format!("failed to open file: {}", path.display()))?;
    let saveable: Saveable = serde_yaml::from_reader(file)
        .context(format!("failed to read RON file: {}", path.display()))?;
    saveable.validate()?;
    Ok(saveable)
}
