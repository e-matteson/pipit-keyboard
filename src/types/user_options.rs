use std::path::PathBuf;

use error::{Error, ResultExt};
use types::{
    BoardName, ChordSpec, KmapFormat, Permutation, Pin, SwitchPos, Validate,
};

fn default_output_dir() -> PathBuf {
    PathBuf::from("pipit-firmware")
}

validated_struct! {
    #[derive(Deserialize, Debug)]
    #[serde(deny_unknown_fields)]
    pub struct UserOptions {
        pub chord_delay: Delay,
        pub held_delay: Delay,

        #[serde(default = "return_false")]
        pub debug_messages: bool,
        pub board_name: BoardName,
        pub row_pins: Vec<Pin>,
        pub column_pins: Vec<Pin>,
        pub kmap_format: KmapFormat,

        pub rgb_led_pins: Option<[Pin; 3]>,

        #[serde(default)]
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

always_valid_enum! {
    #[derive(Deserialize, Debug, Clone, Copy)]
    pub enum WordSpacePosition {
        Before,
        After,
        None,
    }
}

#[derive(Deserialize, Debug, Clone, Copy)]
#[serde(deny_unknown_fields)]
pub struct Delay(pub u16);

impl UserOptions {
    /// Info about the chord length etc. that the Chord struct needs to know.
    pub fn chord_spec(&self) -> Result<ChordSpec, Error> {
        let permutation = Permutation::from_to(
            &self.kmap_format.kmap_order(),
            &self.firmware_order()?,
        )
        .context(
            "'kmap_format' contains pin numbers not present in 'row_pins' or \
             'column_pins'",
        )?;

        Ok(ChordSpec {
            num_switches: self.kmap_format.num_switches(),
            to_firmware_order: permutation,
        })
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
        for c in &self.column_pins {
            for r in &self.row_pins {
                order.push(SwitchPos::new(*r, *c));
            }
        }
        Ok(order)
    }
}

impl Default for WordSpacePosition {
    fn default() -> Self {
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

fn return_false() -> bool {
    false
}

fn return_true() -> bool {
    true
}
