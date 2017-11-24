use std::collections::BTreeMap;
use std::path::PathBuf;

use serde_json;
use types::{AllData, CCode, Chord, ModeName, Name, SeqType};
use types::errors::*;
use format::c_files::write_to_file;


impl AllData {
    pub fn save_tutor_data(&self) -> Result<()> {
        let file_name = "tutor_data.json";
        let mut path: PathBuf = self.tutor_directory.clone().unwrap();
        // .ok_or_else(|| "No path given for tutor data file".into())?;
        path.push(file_name);
        let json = serde_json::to_string(&self.get_tutor_data()?)?;
        println!("Saving tutor data to: {:?}", path);
        write_to_file(path, &CCode(json))
    }

    fn get_tutor_data(
        &self,
    ) -> Result<BTreeMap<ModeName, BTreeMap<Name, Chord>>> {
        // TODO think about borrowck
        let mut chords = BTreeMap::new();
        let names: Vec<_> = self.get_sequences(&SeqType::Plain)?
            .keys()
            .cloned()
            .collect();
        for mode in self.modes.keys() {
            let mut mode_chords = BTreeMap::new();
            // chords.insert(mode, BTreeMap::new());
            for name in &names {
                if let Some(chord) = self.get_visual_chord_in_mode(name, mode) {
                    mode_chords.insert(name.to_owned(), chord);
                }
            }
            chords.insert(mode.to_owned(), mode_chords);
        }
        Ok(chords)
    }
}
