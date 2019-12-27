use error::Error;
use types::{CCode, ToC, Validate};

#[derive(Debug, PartialEq, Eq, Clone, Copy, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Pin(pub u8);

impl Pin {
    pub fn c_vec(pin_vec: &[Self]) -> Vec<CCode> {
        pin_vec.iter().map(|pin| pin.to_c()).collect()
    }
}

impl Validate for Pin {
    #[allow(clippy::absurd_extreme_comparisons)]
    fn validate(&self) -> Result<(), Error> {
        const MIN_PIN_NUM: u8 = 0;
        const MAX_PIN_NUM: u8 = 30; // TODO pick real value

        if self.0 <= MAX_PIN_NUM && self.0 >= MIN_PIN_NUM {
            Ok(())
        } else {
            Err(Error::OutOfRangeErr {
                name: "pin number".into(),
                value: self.0 as usize,
                min: MIN_PIN_NUM as usize,
                max: MAX_PIN_NUM as usize,
            })
        }
    }
}

impl From<Pin> for usize {
    fn from(pin: Pin) -> usize {
        pin.0 as usize
    }
}

impl From<Pin> for u8 {
    fn from(pin: Pin) -> u8 {
        pin.0
    }
}

impl ToC for Pin {
    fn to_c(self) -> CCode {
        self.0.to_c()
    }
}
