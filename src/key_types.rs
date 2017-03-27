

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
pub struct SwitchPos {
    pub row: i64,
    pub col: i64,
}
