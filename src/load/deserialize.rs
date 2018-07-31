use serde::de::{self, Deserialize, Deserializer, SeqAccess, Visitor};
use std::collections::BTreeMap;
use std::fmt;
use std::path::PathBuf;
use std::str::FromStr;

use types::{
    CCode, CTree, ChordSpec, KeyPress, KmapFormat, ModeInfo, ModeName, Name,
    Permutation, Pin, Sequence, SwitchPos, ToC, Validate, Word,
};

use failure::{Error, ResultExt};
use types::errors::print_error;

fn default_output_dir() -> PathBuf {
    PathBuf::from("pipit-firmware")
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
        pub word_modifiers: Vec<Name>,
        pub anagram_modifiers: Vec<Name>,
        pub commands: Vec<Name>,
        pub dictionary: Vec<Word>,
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
        pub row_pins: Vec<Vec<Pin>>,
        pub column_pins: Vec<Vec<Pin>>,
        pub kmap_format: KmapFormat,

        pub rgb_led_pins: Option<[Pin; 3]>,
        pub battery_level_pin: Option<Pin>,

        #[serde(default = "WordSpacePosition::default")]
        pub word_space_position: WordSpacePosition,

        #[serde(default = "default_output_dir")]
        pub output_directory: PathBuf,

        #[serde(default = "return_false")]
        pub enable_led_typing_feedback: bool,

        #[serde(default = "return_false")]
        pub enable_audio_typing_feedback: bool,

        #[serde(default = "return_true")]
        pub use_standby_interrupts: bool,
    }
}

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

always_valid_enum!{
    #[derive(Deserialize, Debug, Clone, Copy)]
    pub enum WordSpacePosition {
        Before,
        After,
        None,
    }
}

#[derive(Deserialize, Debug, Clone, Copy)]
#[serde(deny_unknown_fields)]
pub struct Delay(u16);

////////////////////////////////////////////////////////////////////////////////

impl OptionsConfig {
    /// Get all the options that can be directly written into to output files.
    /// These were either literally given in the settings file, or could be
    /// easily computed from things given in the settings file, and their
    /// values won't need to be used elsewhere in the rust config code.
    pub fn to_vec(&self) -> Result<Vec<CTree>, Error> {
        let mut ops = self.get_literal_ops();
        ops.extend(self.get_auto_ops()?);
        Ok(ops)
    }

    /// Info about the chord length etc. that the Chord struct needs to know.
    pub fn chord_spec(&self) -> Result<ChordSpec, Error> {
        let permutation = Permutation::from_to(
            &self.kmap_format.kmap_order(),
            &self.firmware_order()?,
        ).context(
            "'kmap_format' contains pin numbers not present in 'row_pins' or \
             'column_pins'",
        )?;

        Ok(ChordSpec {
            num_switches: self.kmap_format.num_switches(),
            to_firmware_order: permutation,
        })
    }

    fn get_literal_ops(&self) -> Vec<CTree> {
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
            CTree::Define {
                name: "WORD_SPACE_POSITION".to_c(),
                value: self.word_space_position.to_c(),
            },
            CTree::DefineIf {
                name: self.board_name.to_c(),
                value: true,
            },
            CTree::CompoundArray {
                name: "row_pins".to_c(),
                values: self
                    .row_pins
                    .iter()
                    .map(|hand| Pin::to_c_vec(hand))
                    .collect(),
                subarray_type: "uint8_t".to_c(),
                is_extern: true,
            },
            CTree::CompoundArray {
                name: "column_pins".to_c(),
                values: self
                    .column_pins
                    .iter()
                    .map(|hand| Pin::to_c_vec(hand))
                    .collect(),
                subarray_type: "uint8_t".to_c(),
                is_extern: true,
            },
            CTree::DefineIf {
                name: "ENABLE_LED_TYPING_FEEDBACK".to_c(),
                value: self.enable_led_typing_feedback,
            },
            CTree::DefineIf {
                name: "ENABLE_AUDIO_TYPING_FEEDBACK".to_c(),
                value: self.enable_audio_typing_feedback,
            },
            CTree::DefineIf {
                name: "USE_STANDBY_INTERRUPTS".to_c(),
                value: self.use_standby_interrupts,
            },
        ];

        if let Some(ref pins) = self.rgb_led_pins {
            ops.push(CTree::Array {
                name: "rgb_led_pins".to_c(),
                values: Pin::to_c_vec(&[pins[0], pins[1], pins[2]]),
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

    /// Generate the OpReq::Auto options that depend only on other
    /// options
    fn get_auto_ops(&self) -> Result<Vec<CTree>, Error> {
        let has_battery = self.battery_level_pin.is_some();

        let enable_rgb_led = self.rgb_led_pins.is_some();
        let num_rgb_led_pins =
            self.rgb_led_pins.as_ref().map_or(0, |v| v.len());

        Ok(vec![
            CTree::Define {
                name: "NUM_ROWS".to_c(),
                value: self.num_rows()?.to_c(),
            },
            CTree::Define {
                name: "NUM_COLUMNS".to_c(),
                value: self.num_columns()?.to_c(),
            },
            CTree::Define {
                name: "NUM_HANDS".to_c(),
                value: self.num_hands()?.to_c(),
            },
            CTree::Define {
                name: "NUM_MATRIX_POSITIONS".to_c(),
                value: self.num_matrix_positions()?.to_c(),
            },
            CTree::Define {
                name: "NUM_RGB_LED_PINS".to_c(),
                value: num_rgb_led_pins.to_c(),
            },
            CTree::DefineIf {
                name: "ENABLE_RGB_LED".to_c(),
                value: enable_rgb_led,
            },
            CTree::DefineIf {
                name: "HAS_BATTERY".to_c(),
                value: has_battery,
            },
        ])
    }

    fn num_rows(&self) -> Result<usize, Error> {
        let len = self.row_pins.get(0).expect("row_pins was empty").len();
        if !self.row_pins.iter().all(|hand| len == hand.len()) {
            bail!("Each hand must have the same number of rows")
        }
        Ok(len)
    }

    fn num_columns(&self) -> Result<usize, Error> {
        let len = self
            .column_pins
            .get(0)
            .expect("column_pins was empty")
            .len();
        if !self.column_pins.iter().all(|hand| len == hand.len()) {
            bail!("Each hand must have the same number of columns")
        }
        Ok(len)
    }

    fn num_hands(&self) -> Result<usize, Error> {
        let len = self.row_pins.len();
        if len != self.column_pins.len() {
            bail!("Row and column pins disagree about the number of hands")
        }
        Ok(len)
    }

    fn num_matrix_positions(&self) -> Result<usize, Error> {
        Ok(self.num_hands()? * self.num_rows()? * self.num_columns()?)
    }

    /// The order in which the firmware will scan matrix positions while
    /// checking for pressed switches. It must match the algorithm used
    /// in the firmware's `scanMatrix()`!
    ///
    /// Chords will need to be converted from kmap order to firmware after
    /// being read from a kmap file.
    ///
    /// Note that there might be more matrix positions than there are physical
    /// switches installed in the keyboard.
    fn firmware_order(&self) -> Result<Vec<SwitchPos>, Error> {
        let mut order: Vec<SwitchPos> = Vec::new();
        for h in 0..self.num_hands()? {
            for c in &self.column_pins[h] {
                for r in &self.row_pins[h] {
                    order.push(SwitchPos::new(*r, *c));
                }
            }
        }
        Ok(order)
    }
}

impl<'de> Deserialize<'de> for Sequence {
    fn deserialize<D>(deserializer: D) -> Result<Sequence, D::Error>
    where
        D: Deserializer<'de>,
    {
        // We create a `Visitor` type, with one method for each data type
        // we support.  The deserializer will call the method corresponding
        // to the data that's actually in the file.
        struct SequenceVisitor;

        impl<'de> Visitor<'de> for SequenceVisitor {
            type Value = Sequence;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                formatter.write_str("a sequence of keypresses")
            }

            // The deserializer found a string, so handle it.
            fn visit_str<E>(self, value: &str) -> Result<Sequence, E>
            where
                E: de::Error,
            {
                Sequence::from_str(value).map_err(|error| {
                    // TODO figure out a proper way to get failure's error info
                    // into de::Error
                    print_error(error);
                    de::Error::custom("invalid sequence string")
                })
            }

            fn visit_seq<A>(self, mut seq: A) -> Result<Self::Value, A::Error>
            where
                A: SeqAccess<'de>,
            {
                let mut values = Vec::new();

                while let Some(value) = seq.next_element()? {
                    values.push(value)
                }

                Ok(Sequence(values))
            }
        }
        deserializer.deserialize_seq(SequenceVisitor)
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

impl ToC for WordSpacePosition {
    fn to_c(self) -> CCode {
        match self {
            WordSpacePosition::Before => 0,
            WordSpacePosition::After => 1,
            WordSpacePosition::None => 2,
        }.to_c()
    }
}

impl Default for WordSpacePosition {
    fn default() -> WordSpacePosition {
        WordSpacePosition::Before
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

fn return_true() -> bool {
    true
}
