
pub type Chord = Vec<bool>;

pub type Sequence = Vec<KeyPress>;

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
pub struct KeyPress{
    /// Used for defining key sequences
    pub key: String,
    pub modifier: String,
}

// impl FromIter for KeyPress{

// }

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Clone)]
pub struct SwitchPos {
    pub row: usize,
    pub col: usize,
}

impl SwitchPos{
    pub fn new(row: i64, col: i64) -> SwitchPos {
        SwitchPos{
            row: row as usize,
            col: col as usize,
        }
    }
}
