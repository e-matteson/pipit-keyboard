
pub type Sequence = Vec<KeyPress>;

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Clone)]
pub struct KeyPress{
    pub key: String,
    pub modifier: String,
}

impl KeyPress{
    pub fn new_blank() -> KeyPress {
        KeyPress{
            key: "0".to_owned(),
            modifier: "0".to_owned(),
        }
    }
}
