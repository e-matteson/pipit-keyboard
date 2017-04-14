
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
