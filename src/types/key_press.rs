use failure::{Error, ResultExt};
use types::errors::*;
use types::{CCode, Name, Spelling, ToC, Validate};

use std::collections::BTreeMap;
use std::str::FromStr;
use std::string::ToString;

// Used for when a keypress contains only modifiers and no key.
pub const BLANK_KEY: &str = "BLANK_KEY";

// TODO KeyPress is also used to store command codes, which is kinda a hack.
// Rename?
#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KeyPress {
    pub key: Option<CCode>,
    #[serde(default = "Vec::new")]
    pub mods: Vec<CCode>,
}

#[derive(Debug)]
struct KeyDef {
    keypress: KeyPress,
    spelling: Option<Spelling>,
    scancode: Option<u8>,
}

pub struct KeyDefs;

lazy_static!{
    static ref TABLE: Vec<KeyDef> = vec![
        // keypress                                   spelling    scancode
        (KeyPress::new_mod("MODIFIERKEY_CTRL"),        None,       Some(1)),
        (KeyPress::new_mod("MODIFIERKEY_SHIFT"),       None,       Some(2)),
        (KeyPress::new_mod("MODIFIERKEY_ALT"),         None,       Some(4)),
        (KeyPress::new_mod("MODIFIERKEY_GUI"),         None,       Some(8)),
        (KeyPress::new_mod("MODIFIERKEY_LEFT_CTRL"),   None,       Some(1)),
        (KeyPress::new_mod("MODIFIERKEY_LEFT_SHIFT"),  None,       Some(2)),
        (KeyPress::new_mod("MODIFIERKEY_LEFT_ALT"),    None,       Some(4)),
        (KeyPress::new_mod("MODIFIERKEY_LEFT_GUI"),    None,       Some(8)),
        (KeyPress::new_mod("MODIFIERKEY_RIGHT_CTRL"),  None,       Some(16)),
        (KeyPress::new_mod("MODIFIERKEY_RIGHT_SHIFT"), None,       Some(32)),
        (KeyPress::new_mod("MODIFIERKEY_RIGHT_ALT"),   None,       Some(64)),
        (KeyPress::new_mod("MODIFIERKEY_RIGHT_GUI"),   None,       Some(128)),
        (KeyPress::new_key("KEY_A"),                   Some("a"),  Some(4)),
        (KeyPress::new_key("KEY_B"),                   Some("b"),  Some(5)),
        (KeyPress::new_key("KEY_C"),                   Some("c"),  Some(6)),
        (KeyPress::new_key("KEY_D"),                   Some("d"),  Some(7)),
        (KeyPress::new_key("KEY_E"),                   Some("e"),  Some(8)),
        (KeyPress::new_key("KEY_F"),                   Some("f"),  Some(9)),
        (KeyPress::new_key("KEY_G"),                   Some("g"),  Some(10)),
        (KeyPress::new_key("KEY_H"),                   Some("h"),  Some(11)),
        (KeyPress::new_key("KEY_I"),                   Some("i"),  Some(12)),
        (KeyPress::new_key("KEY_J"),                   Some("j"),  Some(13)),
        (KeyPress::new_key("KEY_K"),                   Some("k"),  Some(14)),
        (KeyPress::new_key("KEY_L"),                   Some("l"),  Some(15)),
        (KeyPress::new_key("KEY_M"),                   Some("m"),  Some(16)),
        (KeyPress::new_key("KEY_N"),                   Some("n"),  Some(17)),
        (KeyPress::new_key("KEY_O"),                   Some("o"),  Some(18)),
        (KeyPress::new_key("KEY_P"),                   Some("p"),  Some(19)),
        (KeyPress::new_key("KEY_Q"),                   Some("q"),  Some(20)),
        (KeyPress::new_key("KEY_R"),                   Some("r"),  Some(21)),
        (KeyPress::new_key("KEY_S"),                   Some("s"),  Some(22)),
        (KeyPress::new_key("KEY_T"),                   Some("t"),  Some(23)),
        (KeyPress::new_key("KEY_U"),                   Some("u"),  Some(24)),
        (KeyPress::new_key("KEY_V"),                   Some("v"),  Some(25)),
        (KeyPress::new_key("KEY_W"),                   Some("w"),  Some(26)),
        (KeyPress::new_key("KEY_X"),                   Some("x"),  Some(27)),
        (KeyPress::new_key("KEY_Y"),                   Some("y"),  Some(28)),
        (KeyPress::new_key("KEY_Z"),                   Some("z"),  Some(29)),
        (KeyPress::new_key("KEY_1"),                   Some("1"),  Some(30)),
        (KeyPress::new_cap("KEY_1"),                   Some("!"),  None),
        (KeyPress::new_key("KEY_2"),                   Some("2"),  Some(31)),
        (KeyPress::new_cap("KEY_2"),                   Some("@"),  None),
        (KeyPress::new_key("KEY_3"),                   Some("3"),  Some(32)),
        (KeyPress::new_cap("KEY_3"),                   Some("#"),  None),
        (KeyPress::new_key("KEY_4"),                   Some("4"),  Some(33)),
        (KeyPress::new_cap("KEY_4"),                   Some("$"),  None),
        (KeyPress::new_key("KEY_5"),                   Some("5"),  Some(34)),
        (KeyPress::new_cap("KEY_5"),                   Some("%"),  None),
        (KeyPress::new_key("KEY_6"),                   Some("6"),  Some(35)),
        (KeyPress::new_cap("KEY_6"),                   Some("^"),  None),
        (KeyPress::new_key("KEY_7"),                   Some("7"),  Some(36)),
        (KeyPress::new_cap("KEY_7"),                   Some("&"),  None),
        (KeyPress::new_key("KEY_8"),                   Some("8"),  Some(37)),
        (KeyPress::new_cap("KEY_8"),                   Some("*"),  None),
        (KeyPress::new_key("KEY_9"),                   Some("9"),  Some(38)),
        (KeyPress::new_cap("KEY_9"),                   Some("("),  None),
        (KeyPress::new_key("KEY_0"),                   Some("0"),  Some(39)),
        (KeyPress::new_cap("KEY_0"),                   Some(")"),  None),
        (KeyPress::new_key("KEY_ENTER"),               Some("\n"), Some(40)),
        (KeyPress::new_key("KEY_ESC"),                 None,       Some(41)),
        (KeyPress::new_key("KEY_BACKSPACE"),           None,       Some(42)),
        (KeyPress::new_key("KEY_TAB"),                 Some("\t"), Some(43)),
        (KeyPress::new_key("KEY_SPACE"),               Some(" "),  Some(44)),
        (KeyPress::new_key("KEY_MINUS"),               Some("-"),  Some(45)),
        (KeyPress::new_cap("KEY_MINUS"),               Some("_"),  None),
        (KeyPress::new_key("KEY_EQUAL"),               Some("="),  Some(46)),
        (KeyPress::new_cap("KEY_EQUAL"),               Some("+"),  None),
        (KeyPress::new_key("KEY_LEFT_BRACE"),          Some("["),  Some(47)),
        (KeyPress::new_cap("KEY_LEFT_BRACE"),          Some("{"),  None),
        (KeyPress::new_key("KEY_RIGHT_BRACE"),         Some("]"),  Some(48)),
        (KeyPress::new_cap("KEY_RIGHT_BRACE"),         Some("}"),  None),
        (KeyPress::new_key("KEY_BACKSLASH"),           Some("\\"), Some(49)),
        (KeyPress::new_cap("KEY_BACKSLASH"),           Some("|"),  None),
        (KeyPress::new_key("KEY_NON_US_NUM"),          None,       Some(50)),
        (KeyPress::new_key("KEY_SEMICOLON"),           Some(";"),  Some(51)),
        (KeyPress::new_cap("KEY_SEMICOLON"),           Some(":"),  None),
        (KeyPress::new_key("KEY_QUOTE"),               Some("'"), Some(52)),
        (KeyPress::new_cap("KEY_QUOTE"),               Some("\""), None),
        // Tilde and grave are apparently swapped in the teensy usb library
        (KeyPress::new_key("KEY_TILDE"),               Some("`"),  Some(53)),
        (KeyPress::new_cap("KEY_TILDE"),               Some("~"),  None),
        (KeyPress::new_key("KEY_COMMA"),               Some(","),  Some(54)),
        (KeyPress::new_cap("KEY_COMMA"),               Some("<"),  None),
        (KeyPress::new_key("KEY_PERIOD"),              Some("."),  Some(55)),
        (KeyPress::new_cap("KEY_PERIOD"),              Some(">"),  None),
        (KeyPress::new_key("KEY_SLASH"),               Some("/"),  Some(56)),
        (KeyPress::new_cap("KEY_SLASH"),               Some("?"),  None),
        (KeyPress::new_key("KEY_CAPS_LOCK"),           None,       Some(57)),
        (KeyPress::new_key("KEY_F1"),                  None,       Some(58)),
        (KeyPress::new_key("KEY_F2"),                  None,       Some(59)),
        (KeyPress::new_key("KEY_F3"),                  None,       Some(60)),
        (KeyPress::new_key("KEY_F4"),                  None,       Some(61)),
        (KeyPress::new_key("KEY_F5"),                  None,       Some(62)),
        (KeyPress::new_key("KEY_F6"),                  None,       Some(63)),
        (KeyPress::new_key("KEY_F7"),                  None,       Some(64)),
        (KeyPress::new_key("KEY_F8"),                  None,       Some(65)),
        (KeyPress::new_key("KEY_F9"),                  None,       Some(66)),
        (KeyPress::new_key("KEY_F10"),                 None,       Some(67)),
        (KeyPress::new_key("KEY_F11"),                 None,       Some(68)),
        (KeyPress::new_key("KEY_F12"),                 None,       Some(69)),
        (KeyPress::new_key("KEY_PRINTSCREEN"),         None,       Some(70)),
        (KeyPress::new_key("KEY_SCROLL_LOCK"),         None,       Some(71)),
        (KeyPress::new_key("KEY_PAUSE"),               None,       Some(72)),
        (KeyPress::new_key("KEY_INSERT"),              None,       Some(73)),
        (KeyPress::new_key("KEY_HOME"),                Some("◀"),       Some(74)),
        (KeyPress::new_key("KEY_PAGE_UP"),             Some("▲"),       Some(75)),
        (KeyPress::new_key("KEY_DELETE"),              None,       Some(76)),
        (KeyPress::new_key("KEY_END"),                 Some("▶"),       Some(77)),
        (KeyPress::new_key("KEY_PAGE_DOWN"),           Some("▼"),       Some(78)),
        (KeyPress::new_key("KEY_RIGHT"),               Some("→"),  Some(79)),
        (KeyPress::new_key("KEY_LEFT"),                Some("←"),  Some(80)),
        (KeyPress::new_key("KEY_DOWN"),                Some("↓"),  Some(81)),
        (KeyPress::new_key("KEY_UP"),                  Some("↑"),  Some(82)),
        (KeyPress::new_key("KEY_NUM_LOCK"),            None,       Some(83)),
        (KeyPress::new_key("KEYPAD_SLASH"),            None,       Some(84)),
        (KeyPress::new_key("KEYPAD_ASTERIX"),          None,       Some(85)),
        (KeyPress::new_key("KEYPAD_MINUS"),            None,       Some(86)),
        (KeyPress::new_key("KEYPAD_PLUS"),             None,       Some(87)),
        (KeyPress::new_key("KEYPAD_ENTER"),            None,       Some(88)),
        (KeyPress::new_key("KEYPAD_1"),                None,       Some(89)),
        (KeyPress::new_key("KEYPAD_2"),                None,       Some(90)),
        (KeyPress::new_key("KEYPAD_3"),                None,       Some(91)),
        (KeyPress::new_key("KEYPAD_4"),                None,       Some(92)),
        (KeyPress::new_key("KEYPAD_5"),                None,       Some(93)),
        (KeyPress::new_key("KEYPAD_6"),                None,       Some(94)),
        (KeyPress::new_key("KEYPAD_7"),                None,       Some(95)),
        (KeyPress::new_key("KEYPAD_8"),                None,       Some(96)),
        (KeyPress::new_key("KEYPAD_9"),                None,       Some(97)),
        (KeyPress::new_key("KEYPAD_0"),                None,       Some(98)),
        (KeyPress::new_key("KEYPAD_PERIOD"),           None,       Some(99)),
        (KeyPress::new_key("KEY_MENU"),                None,       Some(101)),
        (KeyPress::new_key("KEY_F13"),                 None,       Some(104)),
        (KeyPress::new_key("KEY_F14"),                 None,       Some(105)),
        (KeyPress::new_key("KEY_F15"),                 None,       Some(106)),
        (KeyPress::new_key("KEY_F16"),                 None,       Some(107)),
        (KeyPress::new_key("KEY_F17"),                 None,       Some(108)),
        (KeyPress::new_key("KEY_F18"),                 None,       Some(109)),
        (KeyPress::new_key("KEY_F19"),                 None,       Some(110)),
        (KeyPress::new_key("KEY_F20"),                 None,       Some(111)),
        (KeyPress::new_key("KEY_F21"),                 None,       Some(112)),
        (KeyPress::new_key("KEY_F22"),                 None,       Some(113)),
        (KeyPress::new_key("KEY_F23"),                 None,       Some(114)),
        (KeyPress::new_key("KEY_F24"),                 None,       Some(115)),
    ].into_iter()
        .map(|x| KeyDef {
            keypress: x.0,
            spelling: x.1.map(|s| Spelling::new(s).expect("bad keydef spelling")),
            scancode: x.2,
        })
        .collect();
}

////////////////////////////////////////////////////////////////////////////////

impl KeyPress {
    fn new_key<T>(keycode: T) -> Self
    where
        T: ToC,
    {
        Self {
            key: Some(keycode.to_c()),
            mods: Vec::new(),
        }
    }

    fn new_cap<T>(keycode: T) -> Self
    where
        T: ToC,
    {
        Self {
            key: Some(keycode.to_c()),
            mods: vec!["MODIFIERKEY_SHIFT".to_c()],
        }
    }

    fn new_mod<T>(modifier: T) -> Self
    where
        T: ToC,
    {
        Self {
            key: None,
            mods: vec![modifier.to_c()],
        }
    }

    pub fn new_fake(command_code: &Name) -> Self {
        // We also use KeyPresses to store command codes
        Self {
            key: Some(command_code.to_c()),
            mods: Vec::new(),
        }
    }

    pub fn key_or_blank(&self) -> CCode {
        if let Some(key_code) = &self.key {
            key_code.to_owned()
        } else {
            Self::blank()
        }
    }

    /// Blanks are used in the huffman encoded sequences, to represent when a
    /// keypress contains only a mod - the key is stored as BLANK_KEY.
    pub fn blank() -> CCode {
        BLANK_KEY.to_c()
    }

    fn capitalize(&mut self) {
        let shift = "MODIFIERKEY_SHIFT".to_c();
        if !self.mods.contains(&shift) {
            self.mods.push(shift);
        }
    }

    pub fn ensure_non_empty(&self) -> Result<(), Error> {
        if self.key.is_none() && self.mods.is_empty() {
            Err(BadValueErr {
                value: "(empty)".into(),
                thing: "KeyPress".into(),
            }).context("KeyPress must contain at least one key or modifier")?
        } else {
            Ok(())
        }
    }

    fn lone_mod(&self) -> Result<CCode, Error> {
        Ok(if self.mods.len() == 1 {
            self.mods[0].clone()
        } else {
            Err(BadValueErr {
                thing: "number of modifiers".into(),
                value: self.mods.len().to_string(),
            }).context("Expected KeyPress to contain exactly one modifier")?
        })
    }
}

impl Default for KeyPress {
    fn default() -> Self {
        Self {
            key: None,
            mods: Vec::new(),
        }
    }
}

impl Validate for KeyPress {
    fn validate(&self) -> Result<(), Error> {
        self.ensure_non_empty()?;
        if let Some(ref s) = self.key {
            KeyDefs::ensure_defined_key_or_mod(s)?;
        }
        for modifier in &self.mods {
            KeyDefs::ensure_defined_key_or_mod(modifier)?;
        }
        Ok(())
    }
}

impl FromStr for KeyPress {
    type Err = Error;

    fn from_str(character_string: &str) -> Result<Self, Self::Err> {
        let spelling = Spelling::new(character_string)?;
        let keypress = KeyDefs::keypress_from_spelling(spelling)?;
        Ok(keypress.ok_or_else(|| BadValueErr {
            thing: "character".into(),
            value: character_string.into(),
        })?)
    }
}

impl KeyDef {
    fn has_spelling(&self, spelling: Spelling) -> bool {
        self.spelling.map_or(false, |x| x == spelling)
    }

    fn has_mod(&self, modifier: &CCode) -> bool {
        self.keypress.mods.contains(modifier)
    }

    fn has_keycode_or_mod(&self, keycode: &CCode) -> bool {
        if let Some(x) = self.keypress.key.as_ref() {
            x == keycode
        } else {
            self.has_mod(keycode)
        }
    }
}

impl KeyDefs {
    pub fn spelling_from_keypress(
        keypress: &KeyPress,
    ) -> Result<Option<Spelling>, Error> {
        Ok(TABLE
            .iter()
            .find(|ref def| &def.keypress == keypress)
            .ok_or_else(|| MissingErr {
                missing: format!(
                    "entry for plain_key/plain_mod '{:?}'",
                    keypress
                ),
                container: "key definition table".into(),
            })?.spelling)
    }

    fn keypress_from_spelling(
        spelling: Spelling,
    ) -> Result<Option<KeyPress>, Error> {
        let is_capitalized = spelling.is_uppercase();

        let keypress =
            Self::def_from_spelling(spelling.to_lowercase()).map(|def| {
                let mut k = def.keypress.clone();
                if is_capitalized {
                    k.capitalize()
                }
                k
            });
        Ok(keypress)
    }

    fn def_from_spelling(spelling: Spelling) -> Option<&'static KeyDef> {
        TABLE.iter().find(|def| def.has_spelling(spelling))
    }

    /// Get the c-preprocessor names of all keycodes/modifiers and their
    /// scancodes. Doesn't distinguish between keycodes and modifiers
    pub fn scancode_table() -> &'static BTreeMap<&'static CCode, u8> {
        lazy_static! {
            static ref SCANCODES: BTreeMap<&'static CCode, u8> = TABLE
                .iter()
                .filter_map(|def| def.scancode.map(|scancode| {
                    // TODO clean up?
                    let cdefine = match (&def.keypress.key, &def.keypress.mods)
                    {
                        (Some(key), mods) if !mods.is_empty() => panic!(
                            "bad keydef entry, entries with modifiers shouldn't \
                             include a scancode: {:?} {:?}",
                            key, mods
                        ),
                        (_, mods) if mods.len() > 1 =>
                            panic!("bad keydef entry, has more than 1 mod"),
                        (None, mods) if mods.is_empty() => {
                            panic!("bad keydef entry, no keycode or mod")
                        }
                        (Some(ref key), _) => key,
                        (_, mods) if mods.len() == 1 => &mods[0],
                        _ => panic!("bad keydef entry"),
                    };
                    (cdefine, scancode)
                }))
                .collect();
        }
        &SCANCODES
    }

    fn ensure_defined_key_or_mod(keycode: &CCode) -> Result<(), Error> {
        if TABLE.iter().any(|def| def.has_keycode_or_mod(keycode)) {
            Ok(())
        } else {
            Err(BadValueErr {
                thing: "keycode or mod".into(),
                value: keycode.to_string(),
            }).context("Not defined in the firmware")?
        }
    }

    pub fn ensure_plain_mod(keypress: &KeyPress) -> Result<(), Error> {
        let modifier = keypress.lone_mod()?;
        if TABLE.iter().any(|def| def.has_mod(&modifier)) {
            Ok(())
        } else {
            Err(BadValueErr {
                thing: "modifier".into(),
                value: modifier.to_string(),
            }).context("Not defined in the firmware")?
        }
    }
}
