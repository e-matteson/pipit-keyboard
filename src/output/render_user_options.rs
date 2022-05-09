use error::Error;
use types::{
    CEnumVariant, CIdent, CTree, CType, UserOptions, WordSpacePosition,
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
        let group = vec![CTree::ConstDef {
            name: "NUM_MATRIX_POSITIONS".into(),
            value: Box::new(self.num_matrix_positions()?.into()),
            c_type: CType::U8,
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
            CTree::ConstDef {
                name: "CHORD_DELAY".into(),
                value: Box::new(self.chord_delay.into()),
                c_type: CType::U32,
            },
            CTree::ConstDef {
                name: "HELD_DELAY".into(),
                value: Box::new(self.held_delay.into()),
                c_type: CType::U32,
            },
            CTree::DefineIf {
                name: "DEBUG_MESSAGES".into(),
                is_defined: self.debug_messages,
            },
            CTree::ConstDef {
                name: "SPACE_POS".into(),
                value: Box::new(
                    self.word_space_position.qualified_enum_variant().into(),
                ),
                c_type: CType::custom(WordSpacePosition::enum_type().0),
            },
            CTree::DefineIf {
                name: self.board_name.into(),
                is_defined: true,
            },
            CTree::std_array_def(
                "row_pins".into(),
                CType::U8,
                self.row_pins.iter().map(|pin| (*pin).into()).collect(),
            ),
            CTree::std_array_def(
                "column_pins".into(),
                CType::U8,
                self.column_pins.iter().map(|pin| (*pin).into()).collect(),
            ),
            CTree::DefineIf {
                name: "ENABLE_LED_TYPING_FEEDBACK".into(),
                is_defined: self.enable_led_typing_feedback,
            },
            CTree::DefineIf {
                name: "ENABLE_AUDIO_TYPING_FEEDBACK".into(),
                is_defined: self.enable_audio_typing_feedback,
            },
            CTree::ConstDef {
                name: "USE_STANDBY_INTERRUPTS".into(),
                value: Box::new(self.use_standby_interrupts.into()),
                c_type: CType::Bool,
            },
        ];

        if let Some(ref pins) = self.rgb_led_pins {
            ops.push(CTree::std_array_def(
                "rgb_led_pins".into(),
                CType::U8,
                pins.iter().map(|pin| (*pin).into()).collect(),
            ));
        }

        ops
    }

    /// Generate the OpReq::Auto options that depend only on other
    /// options
    fn get_auto_ops(&self) -> Vec<CTree> {
        let enable_rgb_led = self.rgb_led_pins.is_some();
        vec![CTree::DefineIf {
            name: "ENABLE_RGB_LED".into(),
            is_defined: enable_rgb_led,
        }]
    }
}

impl CEnumVariant for WordSpacePosition {
    /// The type name of C++ enum
    fn enum_type() -> CIdent {
        "WordSpacePosition".into()
    }

    /// The variant name of this SeqType in the C++ enum
    fn enum_variant(&self) -> CIdent {
        match self {
            WordSpacePosition::Before => "Before",
            WordSpacePosition::After => "After",
            WordSpacePosition::None => "None",
        }
        .into()
    }

    /// The underlying type determining the size of the C++ enum
    fn underlying_type() -> Option<CType> {
        None
    }
}
