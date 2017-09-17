
use std::collections::BTreeMap;

use types::{Chord, KeyPress, KmapFormat, ModeInfo, ModeName, Name, COption,
            Sequence, ToC, WordInfo};

fn default_output_dir() -> String {
    "pipit-firmware/".into()
}

#[derive(Deserialize, Debug)]
#[serde(deny_unknown_fields)]
pub struct Settings {
    pub modes: BTreeMap<ModeName, ModeInfo>,
    pub options: OptionsConfig,
    pub plain_modifiers: BTreeMap<Name, KeyPress>,
    pub plain_keys: BTreeMap<Name, KeyPress>,
    pub macros: BTreeMap<Name, Sequence>,
    pub other: OtherConfig,
}

#[derive(Deserialize, Debug)]
#[serde(deny_unknown_fields)]
pub struct OptionsConfig {
    pub chord_delay: usize,
    pub held_delay: usize,
    pub debounce_delay: usize,
    pub debug_messages: usize,
    pub board_name: CCode,
    pub row_pins: Vec<u8>,
    pub column_pins: Vec<u8>,
    pub kmap_format: KmapFormat,

    pub rgb_led_pins: Option<Vec<u8>>,
    pub battery_level_pin: Option<u8>,

    #[serde(default = "default_output_dir")]
    pub output_directory: String,

    #[serde(default = "return_false")]
    pub enable_led_typing_feedback: bool,
}

#[derive(Deserialize, Debug)]
#[serde(deny_unknown_fields)]
pub struct OtherConfig {
    pub word_modifiers: Vec<Name>,
    pub anagram_modifiers: Vec<Name>,
    pub commands: Vec<Name>,
    pub dictionary: Vec<WordConfig>,
}

#[derive(Deserialize, Debug, Clone)]
#[serde(deny_unknown_fields)]
pub struct WordConfig {
    pub word: String,
    pub anagram: Option<u8>,
    pub chord: Option<String>,
}

////////////////////////////////////////////////////////////////////////////////

impl OptionsConfig {
    pub fn to_vec(&self) -> Vec<COption> {
        let mut ops = self.get_literal_ops();
        ops.extend(self.get_auto());
        ops
    }

    fn get_literal_ops(&self) -> Vec<COption> {
        // TODO use macro to avoid writing out field names as strings?
        let mut ops = vec![
            COption::DefineInt("CHORD_DELAY".to_c(), self.chord_delay),
            COption::DefineInt("HELD_DELAY".to_c(), self.held_delay),
            COption::DefineInt("DEBOUNCE_DELAY".to_c(), self.debounce_delay),
            COption::DefineInt("DEBUG_MESSAGES".to_c(), self.debug_messages),
            COption::Ifdef(self.board_name, true),
            COption::Array1D("row_pins".to_c(), self.row_pins.clone()),
            COption::Array1D("column_pins".to_c(), self.column_pins.clone()),
            COption::Ifdef(
                "ENABLE_LED_TYPING_FEEDBACK".to_c(),
                self.enable_led_typing_feedback,
            ),
        ];

        if self.rgb_led_pins.is_some() {
            let v = self.rgb_led_pins.clone();
            ops.push(COption::Array1D("rgb_led_pins".to_c(), v.unwrap()))
        }

        if self.battery_level_pin.is_some() {
            ops.push(COption::Uint8(
                "battery_level_pin".to_c(),
                self.battery_level_pin.unwrap(),
            ))
        }
        ops
    }

    pub fn get_auto(&self) -> Vec<COption> {
        /// Generate the OpReq::Auto options that depend only on other
        /// options
        let num_rows = self.row_pins.len();
        let num_columns = self.column_pins.len();
        let num_matrix_positions = num_rows * num_columns;
        let num_bytes_in_chord = round_up_to_num_bytes(num_matrix_positions);
        let has_battery = self.battery_level_pin.is_some();

        let enable_rgb_led = self.rgb_led_pins.is_some();
        let num_rgb_led_pins =
            self.rgb_led_pins.as_ref().map_or(0, |v| v.len());

        // TODO don't magically set Chord's static var here!
        Chord::set_num_bytes(num_bytes_in_chord);

        vec![
            COption::DefineInt("NUM_ROWS".to_c(), num_rows),
            COption::DefineInt("NUM_COLUMNS".to_c(), num_columns),
            COption::DefineInt(
                "NUM_MATRIX_POSITIONS".to_c(),
                num_matrix_positions,
            ),
            COption::DefineInt("NUM_BYTES_IN_CHORD".to_c(), num_bytes_in_chord),
            COption::DefineInt("NUM_RGB_LED_PINS".to_c(), num_rgb_led_pins),
            COption::Ifdef("ENABLE_RGB_LED".to_c(), enable_rgb_led),
            COption::Ifdef("HAS_BATTERY".to_c(), has_battery),
        ]
    }
}

impl From<WordConfig> for WordInfo {
    fn from(conf: WordConfig) -> Self {
        WordInfo {
            chord_spelling: conf.chord.unwrap_or(conf.word.clone()),
            seq_spelling: conf.word,
            anagram_num: conf.anagram.unwrap_or(0),
        }
    }
}


fn return_false() -> bool {
    false
}

// fn yes() -> bool {
//     true
// }

fn round_up_to_num_bytes(num_bits: usize) -> usize {
    (num_bits as f64 / 8.0).ceil() as usize
}
