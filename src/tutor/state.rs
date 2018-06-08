use std::sync::Mutex;
use std::collections::HashMap;

use types::{Chord, ModeName, Name, Spelling, TutorData};

lazy_static! {
    static ref STATE: Mutex<State> = Mutex::new(State::new());
}

#[derive(Debug, Clone)]
pub struct State {
    tutor_data: Option<TutorData>,
    learning_map: HashMap<String, LearnState>,
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
            initial_learn_state: 10,
            mode: ModeName::default(),
            freeze_on_error: true,
        }
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
            data.chords.get(&state.mode)?.get(name).cloned()
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
        let initial_learn_state = state.initial_learn_state;
        state
            .learning_map
            .entry(name)
            .or_insert_with(|| LearnState(initial_learn_state))
            .update(was_correct);
    }

    pub fn initial_learn_state() -> usize {
        STATE.lock().unwrap().initial_learn_state
    }

    pub fn freeze_on_error() -> bool {
        STATE.lock().unwrap().freeze_on_error
    }
    pub fn set_freeze_on_error(value: bool) {
        STATE.lock().unwrap().freeze_on_error = value;
    }

    pub fn set_initial_learn_state(initial: usize) {
        let mut state = STATE.lock().unwrap();
        for (_, learn_state) in state.learning_map.iter_mut() {
            learn_state.reset(initial);
        }
        state.initial_learn_state = initial;
    }

    pub fn mode_list() -> Vec<String> {
        let state = STATE.lock().unwrap();
        if let Some(ref data) = state.tutor_data {
            data.chords.keys().map(|mode| mode.0.clone()).collect()
        } else {
            panic!("tutor data was not set")
        }
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

        state.mode = mode;

        // Reset the learning state for each letter, since the chords could be
        // totally different now.
        let initial = state.initial_learn_state;
        for (_, learn_state) in state.learning_map.iter_mut() {
            learn_state.reset(initial);
        }
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
