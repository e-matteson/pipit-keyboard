use std::slice::Iter;


// TODO KeyPress is also used to store command codes, which is kinda a hack. Rename?

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Clone)]
pub struct KeyPress{
    pub key: String,
    pub modifier: String,
}

impl KeyPress{
    pub fn new(key: usize, modifier: usize) -> KeyPress {
        KeyPress{
            key: format!("{}", key),
            modifier: format!("{}", modifier),
        }
    }
    pub fn new_fake(code: &str) -> KeyPress {
        // We also use KeyPresses to store command codes
        KeyPress{
            key: code.to_owned(),
            modifier: "0".to_owned(),
        }
    }
    pub fn new_blank() -> KeyPress {
        KeyPress{
            key: "0".to_owned(),
            modifier: "0".to_owned(),
        }
    }
    pub fn is_mod_blank(&self) -> bool {
        self.modifier == "0"
    }
}


#[derive(Debug)]
#[derive(Clone)]
pub struct Sequence (
    pub Vec<KeyPress>
);

impl Sequence {
    pub fn new() -> Sequence {
        Sequence(Vec::new())
    }

    pub fn extend (&mut self, other: Sequence) {
        self.0.extend(other.0)
    }

    pub fn push (&mut self, keypress: KeyPress) {
        self.0.push(keypress)
    }

    pub fn len (&self) -> usize {
        self.0.len()
    }

    pub fn keypresses(&self) -> Iter<KeyPress> {
        self.0.iter()
    }

    pub fn get_only_value(&self) -> &str{

        assert_eq!(self.len(), 1);
        let only_key = &self.0[0];
        assert!(only_key.is_mod_blank());
        &only_key.key
    }

}
