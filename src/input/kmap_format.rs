use std::fmt::{self, Debug};

use super::pin::Pin;
use error::Error;
use types::Validate;

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapFormat(Vec<Vec<SwitchPos>>);

#[derive(Debug, PartialEq, Eq, Clone, Copy, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct SwitchPos {
    pub row: Pin,
    pub col: Pin,
}

impl KmapFormat {
    pub fn num_switches(&self) -> usize {
        let mut count = 0;
        for row in &self.0 {
            for _ in row {
                count += 1;
            }
        }
        count
    }

    /// The order of switches in a chord, as written in a kmap file. This will
    /// need to be converted to firmware order later.
    pub fn kmap_order(&self) -> Vec<SwitchPos> {
        let mut flat: Vec<SwitchPos> = Vec::new();
        for row in &self.0 {
            flat.extend_from_slice(row);
        }
        flat
    }

    pub fn switches_per_line(&self) -> Vec<usize> {
        self.0.iter().map(|v| v.len()).collect()
    }

    pub fn block_length(&self) -> usize {
        // 1 extra for the first line with the names
        1 + self.0.len()
    }
}

impl Validate for KmapFormat {
    fn validate(&self) -> Result<(), Error> {
        for row in &self.0 {
            for switch_pos in row.iter() {
                switch_pos.validate()?;
            }
        }
        Ok(())
    }
}

impl SwitchPos {
    pub fn new(row: Pin, col: Pin) -> Self {
        Self {
            // row: row as usize,
            // col: col as usize,
            row,
            col,
        }
    }
}

impl Validate for SwitchPos {
    fn validate(&self) -> Result<(), Error> {
        self.row.validate()?;
        self.col.validate()?;
        Ok(())
    }
}

impl fmt::Display for SwitchPos {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[{:?},{:?}]", self.row, self.col)
    }
}
