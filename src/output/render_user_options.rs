use error::Error;
use types::{
    CCode, CEnumVariant, CTree, Delay, Pin, ToC, UserOptions, WordSpacePosition,
};

impl UserOptions {
    /// Get all the options that can be directly written into to output files.
    /// These were either literally given in the settings file, or could be
    /// easily computed from things given in the settings file, and their
    /// values won't need to be used elsewhere in the rust config code.
    pub fn render(&self) -> CTree {
        let mut group = self.get_literal_ops();
        group.extend(self.get_auto_ops());
        CTree::Group(group)
    }

    /// Get options that must be written to a separate config file that will be
    /// loaded earlier than the main one.
    pub fn render_early(&self) -> Result<CTree, Error> {
        let group = vec![CTree::PublicConst {
            name: "NUM_MATRIX_POSITIONS".to_c(),
            value: self.num_matrix_positions()?.to_c(),
            c_type: "uint8_t".to_c(),
        }];
        Ok(CTree::Group(group))
    }

    fn num_rows(&self) -> Result<usize, Error> {
        let len = self.row_pins.len();
        if len == 0 {
            Err(Error::Empty("row_pins".to_owned()))
        } else {
            Ok(len)
        }
    }

    fn num_columns(&self) -> Result<usize, Error> {
        let len = self.column_pins.len();
        if len == 0 {
            Err(Error::Empty("column_pins".to_owned()))
        } else {
            Ok(len)
        }
    }

    fn num_matrix_positions(&self) -> Result<usize, Error> {
        Ok(self.num_rows()? * self.num_columns()?)
    }

    fn get_literal_ops(&self) -> Vec<CTree> {
        let mut ops = vec![
            CTree::PublicConst {
                name: "CHORD_DELAY".to_c(),
                value: self.chord_delay.to_c(),
                c_type: "uint32_t".to_c(),
            },
            CTree::PublicConst {
                name: "HELD_DELAY".to_c(),
                value: self.held_delay.to_c(),
                c_type: "uint32_t".to_c(),
            },
            CTree::DefineIf {
                name: "DEBUG_MESSAGES".to_c(),
                is_defined: self.debug_messages,
            },
            CTree::PublicConst {
                name: "SPACE_POS".to_c(),
                value: self.word_space_position.qualified_enum_variant(),
                c_type: WordSpacePosition::enum_type(),
            },
            CTree::DefineIf {
                name: self.board_name.to_c(),
                is_defined: true,
            },
            CTree::StdArray {
                name: "row_pins".to_c(),
                values: Pin::c_vec(&self.row_pins),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            },
            CTree::StdArray {
                name: "column_pins".to_c(),
                values: Pin::c_vec(&self.column_pins),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            },
            CTree::DefineIf {
                name: "ENABLE_LED_TYPING_FEEDBACK".to_c(),
                is_defined: self.enable_led_typing_feedback,
            },
            CTree::DefineIf {
                name: "ENABLE_AUDIO_TYPING_FEEDBACK".to_c(),
                is_defined: self.enable_audio_typing_feedback,
            },
            CTree::PublicConst {
                name: "USE_STANDBY_INTERRUPTS".to_c(),
                value: self.use_standby_interrupts.to_c(),
                c_type: "bool".to_c(),
            },
        ];

        if let Some(ref pins) = self.rgb_led_pins {
            ops.push(CTree::StdArray {
                name: "rgb_led_pins".to_c(),
                values: Pin::c_vec(pins),
                c_type: "uint8_t".to_c(),
                is_extern: true,
            });
        }

        ops
    }

    /// Generate the OpReq::Auto options that depend only on other
    /// options
    fn get_auto_ops(&self) -> Vec<CTree> {
        let enable_rgb_led = self.rgb_led_pins.is_some();
        vec![CTree::DefineIf {
            name: "ENABLE_RGB_LED".to_c(),
            is_defined: enable_rgb_led,
        }]
    }
}

impl ToC for Delay {
    fn to_c(self) -> CCode {
        self.0.to_c()
    }
}

impl CEnumVariant for WordSpacePosition {
    /// The type name of C++ enum
    fn enum_type() -> CCode {
        "WordSpacePosition".to_c()
    }

    /// The variant name of this SeqType in the C++ enum
    fn enum_variant(&self) -> CCode {
        match self {
            WordSpacePosition::Before => "Before",
            WordSpacePosition::After => "After",
            WordSpacePosition::None => "None",
        }
        .to_c()
    }

    /// The underlying type determining the size of the C++ enum
    fn underlying_type() -> Option<CCode> {
        None
    }
}

// TODO  should Pin stuff be in a different file?
impl Pin {
    pub fn c_vec(pin_vec: &[Self]) -> Vec<CCode> {
        pin_vec.iter().map(|pin| pin.to_c()).collect()
    }
}

impl ToC for Pin {
    fn to_c(self) -> CCode {
        self.0.to_c()
    }
}
