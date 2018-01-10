use std::collections::BTreeMap;
use std::path::PathBuf;

use types::{CCode, CTree, GlobalChordInfo, KeyPress, KmapFormat, ModeInfo,
            ModeName, Name, Permutation, Pin, Sequence, SwitchPos, ToC,
            Validate, WordConfig};

// use types::errors::*;
use failure::{Error, ResultExt};

fn default_output_dir() -> PathBuf {
    PathBuf::from("pipit-firmware")
}

fn default_tutor_dir() -> PathBuf {
    PathBuf::from("tutor")
}

validated_struct!{
    #[derive(Deserialize, Debug)]
    #[serde(deny_unknown_fields)]
    pub struct Settings {
        pub options: OptionsConfig,
        pub modes: BTreeMap<ModeName, ModeInfo>,
        pub plain_modifiers: BTreeMap<Name, KeyPress>,
        pub plain_keys: BTreeMap<Name, KeyPress>,
        pub macros: BTreeMap<Name, Sequence>,
        pub other: OtherConfig,
    }
}

validated_struct!{
    #[derive(Deserialize, Debug)]
    #[serde(deny_unknown_fields)]
    pub struct OptionsConfig {
        pub chord_delay: Delay,
        pub held_delay: Delay,
        pub debounce_delay: Delay,
        pub debug_messages: Verbosity,
        pub board_name: BoardName,
        pub row_pins: Vec<Pin>,
        pub column_pins: Vec<Pin>,
        pub kmap_format: KmapFormat,

        pub rgb_led_pins: Option<Vec<Pin>>,
        pub battery_level_pin: Option<Pin>,

        #[serde(default = "default_output_dir")]
        // TODO validate strings!
        pub output_directory: PathBuf,

        #[serde(default = "default_tutor_dir")]
        // TODO validate strings!
        pub tutor_directory: PathBuf,

        #[serde(default = "return_false")]
        pub enable_led_typing_feedback: bool,

        #[serde(default = "return_false")]
        pub enable_audio_typing_feedback: bool,
    }
}

validated_struct!(
    #[derive(Deserialize, Debug, Clone)]
    #[serde(deny_unknown_fields)]
    pub struct OtherConfig {
        pub word_modifiers: Vec<Name>,
        pub anagram_modifiers: Vec<Name>,
        pub commands: Vec<Name>,
        pub dictionary: Vec<WordConfig>,
    }
);

always_valid_enum!{
    #[derive(Deserialize, Debug, Clone, Copy)]
    pub enum Verbosity {
        None,
        Some,
        All,
    }
}

always_valid_enum!{
    #[derive(Deserialize, Debug, Clone, Copy)]
    #[allow(non_camel_case_types)]
    pub enum BoardName {
        FEATHER_M0_BLE,
        TEENSY_LC,
    }
}

#[derive(Deserialize, Debug, Clone, Copy)]
#[serde(deny_unknown_fields)]
pub struct Delay(u16);

////////////////////////////////////////////////////////////////////////////////

impl OptionsConfig {
    pub fn to_vec(&self) -> Vec<CTree> {
        let mut ops = self.get_literal_ops();
        ops.extend(self.get_auto());
        ops
    }

    pub fn global_chord_info(&self) -> GlobalChordInfo {
        let permutation = Permutation::from_to(
            &self.kmap_format.flat_order(),
            &self.firmware_order(),
        );

        GlobalChordInfo {
            num_bytes: self.num_bytes_in_chord(),
            num_switches: self.kmap_format.chord_length(),
            num_matrix_positions: self.num_matrix_positions(),
            to_firmware_order: permutation,
        }
    }

    pub fn output_directory(&self) -> PathBuf {
        self.output_directory.clone()
    }

    pub fn tutor_directory(&self) -> PathBuf {
        self.tutor_directory.clone()
    }

    fn get_literal_ops(&self) -> Vec<CTree> {
        // TODO use macro to avoid writing out field names as strings?

        let mut ops = vec![
            CTree::Define {
                name: "CHORD_DELAY".to_c(),
                value: self.chord_delay.to_c(),
            },
            CTree::Define {
                name: "HELD_DELAY".to_c(),
                value: self.held_delay.to_c(),
            },
            CTree::Define {
                name: "DEBOUNCE_DELAY".to_c(),
                value: self.debounce_delay.to_c(),
            },
            CTree::Define {
                name: "DEBUG_MESSAGES".to_c(),
                value: self.debug_messages.to_c(),
            },
            CTree::Ifdef {
                name: self.board_name.to_c(),
                value: true,
            },
            CTree::Array {
                name: "row_pins".to_c(),
                values: Pin::to_c_vec(&self.row_pins),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            },
            CTree::Array {
                name: "column_pins".to_c(),
                values: Pin::to_c_vec(&self.column_pins),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            },
            CTree::Ifdef {
                name: "ENABLE_LED_TYPING_FEEDBACK".to_c(),
                value: self.enable_led_typing_feedback,
            },
            CTree::Ifdef {
                name: "ENABLE_AUDIO_TYPING_FEEDBACK".to_c(),
                value: self.enable_audio_typing_feedback,
            },
        ];

        if let Some(ref pins) = self.rgb_led_pins {
            ops.push(CTree::Array {
                name: "rgb_led_pins".to_c(),
                values: Pin::to_c_vec(pins),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            });
        }

        if let Some(pin) = self.battery_level_pin {
            ops.push(CTree::Var {
                name: "battery_level_pin".to_c(),
                value: pin.to_c(),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            });
        }
        ops
    }

    fn firmware_order(&self) -> Vec<SwitchPos> {
        // must match the algorithm used in the firmware's scanMatrix()!
        let mut order: Vec<SwitchPos> = Vec::new();
        for c in &self.column_pins {
            for r in &self.row_pins {
                order.push(SwitchPos::new(*r, *c));
            }
        }
        order
    }

    fn get_auto(&self) -> Vec<CTree> {
        /// Generate the OpReq::Auto options that depend only on other
        /// options
        let has_battery = self.battery_level_pin.is_some();

        let enable_rgb_led = self.rgb_led_pins.is_some();
        let num_rgb_led_pins =
            self.rgb_led_pins.as_ref().map_or(0, |v| v.len());

        vec![
            CTree::Define {
                name: "NUM_ROWS".to_c(),
                value: self.num_rows().to_c(),
            },
            CTree::Define {
                name: "NUM_COLUMNS".to_c(),
                value: self.num_columns().to_c(),
            },
            CTree::Define {
                name: "NUM_MATRIX_POSITIONS".to_c(),
                value: self.num_matrix_positions().to_c(),
            },
            CTree::Define {
                name: "NUM_BYTES_IN_CHORD".to_c(),
                value: self.num_bytes_in_chord().to_c(),
            },
            CTree::Define {
                name: "NUM_RGB_LED_PINS".to_c(),
                value: num_rgb_led_pins.to_c(),
            },
            CTree::Ifdef {
                name: "ENABLE_RGB_LED".to_c(),
                value: enable_rgb_led,
            },
            CTree::Ifdef {
                name: "HAS_BATTERY".to_c(),
                value: has_battery,
            },
        ]
    }

    fn num_rows(&self) -> usize {
        self.row_pins.len()
    }

    fn num_columns(&self) -> usize {
        self.column_pins.len()
    }

    fn num_matrix_positions(&self) -> usize {
        self.num_rows() * self.num_columns()
    }

    fn num_bytes_in_chord(&self) -> usize {
        round_up_to_num_bytes(self.num_matrix_positions())
    }
}

impl ToC for BoardName {
    fn to_c(self) -> CCode {
        match self {
            BoardName::FEATHER_M0_BLE => "FEATHER_M0_BLE".to_c(),
            BoardName::TEENSY_LC => "TEENSY_LC".to_c(),
        }
    }
}

impl ToC for Verbosity {
    fn to_c(self) -> CCode {
        match self {
            Verbosity::None => 0,
            Verbosity::Some => 1,
            Verbosity::All => 2,
        }.to_c()
    }
}

impl Validate for Delay {
    fn validate(&self) -> Result<(), Error> {
        Ok(())
    }
}

impl From<Delay> for usize {
    fn from(delay: Delay) -> usize {
        delay.0 as usize
    }
}

impl ToC for Delay {
    fn to_c(self) -> CCode {
        self.0.to_c()
    }
}

fn return_false() -> bool {
    false
}

fn round_up_to_num_bytes(num_bits: usize) -> usize {
    (num_bits as f64 / 8.0).ceil() as usize
}
