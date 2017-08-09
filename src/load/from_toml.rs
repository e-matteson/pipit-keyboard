use std::collections::BTreeMap;
use std::marker::Sized;


use toml::Value;

use types::{Options, OpDef, OpType, OpVal, Sequence, KeyPress, SwitchPos,
            KmapInfo, KmapPath, Name, WordInfo, ModeInfo, ModeName};

use types::errors::*;
use types;




pub trait FromToml {
    fn from_toml(toml_value: &Value) -> types::errors::Result<Self>
        where Self: Sized;
}

impl FromToml for Options {
    fn from_toml(toml_value: &Value) -> Result<Options> {
        let mut options = Options::new();
        let map = toml_to_map(toml_value)?;
        for key in map.keys(){
            let op_def: &mut OpDef = options.get_mut(key)?;
            let val = map.get(key)
                .ok_or(
                    ErrorKind::MissingValue(
                        "key".into(),
                        Some(key.to_owned())
                    )
                )?;
            let op_val = op_def.value_from_toml(val)
                .chain_err(|| format!("bad value for key: '{}'", key))?;
            op_def.val = Some(op_val);
        }
        Ok(options)
    }
}

impl OpDef {
    fn value_from_toml(&self, val: &Value) -> Result<OpVal>{
        let op_val = match self.op_type {
            OpType::DefineString | OpType::IfdefValue =>
                OpVal::Str(String::from_toml(val)?),
            OpType::DefineInt =>
                OpVal::Int32(i32::from_toml(val)?),
            OpType::Uint8 =>
                OpVal::Uint8(u8::from_toml(val)?),
            OpType::IfdefKey =>
                OpVal::Bool(bool::from_toml(val)?),
            OpType::Mode {..} =>
                OpVal::StrVec(Vec::from_toml(val)?),
            OpType::Array1D =>
                OpVal::Vec(Vec::from_toml(val)?),
            OpType::Array2D =>
                OpVal::Vec2(Vec::from_toml(val)?),
            OpType::ArrayKmap =>
                OpVal::VecKmap(Vec::from_toml(val)?),
        };
        Ok(op_val)
    }
}

impl FromToml for BTreeMap<Name, Sequence> {
    fn from_toml(toml_table: &Value) -> Result<BTreeMap<Name, Sequence>>{
        // use table directly?
        let map = toml_to_map(toml_table)?;
        let mut new_map = BTreeMap::new();
        for (key,val) in &map{
            let seq = Sequence::from_toml(val)
                .chain_err(|| format!("invalid Sequence for: '{}'", key))?;
            new_map.insert(Name::from(key), seq);
        }
        Ok(new_map)
    }
}


impl FromToml for Vec<Name> {
    fn from_toml(toml_array: &Value) -> Result<Vec<Name>>{
        Ok(toml_to_vec(toml_array, Name::from_toml)?)
    }
}

impl FromToml for Vec<String> {
    fn from_toml(toml_array: &Value) -> Result<Vec<String>>{
        Ok(toml_to_vec(toml_array, String::from_toml)?)
    }
}

impl FromToml for Vec<u8> {
    fn from_toml(toml_array: &Value) -> Result<Vec<u8>>{
        Ok(toml_to_vec(toml_array, u8::from_toml)?)
    }
}

impl FromToml for Vec<Vec<u8>> {
    fn from_toml(toml_array: &Value) -> Result<Vec<Vec<u8>>>{
        Ok(toml_to_vec(toml_array, Vec::from_toml)?)
    }
}

impl FromToml for WordInfo {
    fn from_toml(toml_table: &Value) -> Result<WordInfo> {
        let entry = toml_to_map(toml_table)?;

        let seq_spelling = String::from_toml(
            entry.get("word")
                .ok_or_else(|| ErrorKind::MissingValue("word name".into(), None))?
        )?;

        WordInfo::helper(entry, seq_spelling.clone())
            .chain_err(
                || ErrorKind::BadValue(
                    format!("entry for '{}'", seq_spelling), None
                )
            )
    }
}

impl WordInfo {
    pub fn helper(entry: BTreeMap<String, Value>, seq_spelling: String)
              -> Result<WordInfo>
    {
        let chord_spelling = entry.get("chord")
            .map_or(Ok(seq_spelling.clone()), String::from_toml)
            .chain_err(|| ErrorKind::BadValue("chord".into(), None))?;

        let anagram_num: u8 = entry.get("anagram")
            .map_or(
                Ok(0),
                u8::from_toml
            ).chain_err(|| ErrorKind::BadValue("chord".into(), None))?;

        check_keys(&entry, &["word".into(), "chord".into(), "anagram".into()])?;

        Ok(
            WordInfo{
                seq_spelling: seq_spelling,
                chord_spelling: chord_spelling,
                anagram_num: anagram_num
            }
        )
    }
}

fn check_keys(entry: &BTreeMap<String, Value>, expected_keys: &[String])
              -> Result<()>
{
    for key in entry.keys(){
        if !expected_keys.contains(key) {
            bail!(ErrorKind::UnexpectedKey(key.to_owned()));
        }
    }
    Ok(())

}

impl FromToml for Sequence {
    fn from_toml(toml_value: &Value) -> Result<Sequence>{
        let key_vec =
            match *toml_value {
                Value::Table(_) =>
                    vec![KeyPress::from_toml(toml_value)?],
                Value::Array(_) =>
                    toml_to_vec(toml_value, KeyPress::from_toml)?,
                _ =>
                    panic!("Invalid key sequence"),
            };
        Ok(Sequence(key_vec))
    }
}

impl FromToml for KeyPress {
    fn from_toml(toml_table: &Value) -> Result<KeyPress>{
        // mod can be either a single string, or a list of strings
        // TODO don't duplicate errors so much
        // TODO be consistent about when it mentions KeyPress in error and when
        //   it doesn't
        let map = toml_to_map(toml_table)?;

        if map.is_empty() {
           bail!(ErrorKind::BadValue("KeyPress".into(), None))
        }

        check_keys(&map, &["key".into(), "mod".into()])
            .chain_err(|| ErrorKind::BadValue("KeyPress".into(), None))?;

        let key = match map.get("key") {
            Some(v) =>
                Some(String::from_toml(v)?),
            None =>
                None,
        };

        // TODO refactor without matches?
        let modifiers: Option<Vec<String>> = match map.get("mod") {
            Some(v) =>
                Some(
                    match *v {
                        Value::Array(_) => Vec::from_toml(v)?,
                        _ => vec![String::from_toml(v)?],
                    }
                ),
            None =>
                None,
        };
        Ok(KeyPress::new(key, modifiers)?)
    }
}

impl FromToml for KmapInfo {
    fn from_toml(toml_value: &Value) -> Result<KmapInfo >{
        Ok(
            KmapInfo {
                path: KmapPath::from_toml(get_key(toml_value, "file")?)?,
                use_words: match toml_value.get("words") {
                    Some(x) =>
                        bool::from_toml(x)?,
                    None =>
                        false,
                }
            }
        )
    }
}

impl FromToml for KmapPath {
    fn from_toml(toml_value: &Value) -> Result<KmapPath >{
        Ok(KmapPath(String::from_toml(toml_value)?))
    }
}

impl FromToml for Name {
    fn from_toml(toml_value: &Value) -> Result<Name >{
        Ok(Name(String::from_toml(toml_value)?))
    }
}

impl FromToml for ModeName {
    fn from_toml(toml_value: &Value) -> Result<ModeName >{
        Ok(ModeName(String::from_toml(toml_value)?))
    }
}

impl FromToml for SwitchPos {
    fn from_toml(toml_array: &Value) -> Result<SwitchPos >{
        let int_vec = toml_to_vec(toml_array, u8::from_toml)?;
        if int_vec.len() != 2 {
            bail!(
                ErrorKind::BadValue(
                    "switch position".into(),
                    Some(format!("{:?}", int_vec))
                )
            );
        }
        Ok(SwitchPos {row: int_vec[0] as usize, col: int_vec[1] as usize})
    }
}

impl FromToml for ModeInfo {
    fn from_toml(toml_map: &Value) -> Result<ModeInfo >{
        let kmap_array = get_key(toml_map, "keymaps")?;
        // let is_gaming = toml_map.get("gaming")
        //     .map_or(false, |b| bool::from_toml(b));
        let is_gaming = match toml_map.get("gaming") {
            Some(b) => bool::from_toml(b)?,
            None    => false, // default value if "gaming" not specified
        };
        let m =
            ModeInfo {
                keymaps: toml_to_vec(kmap_array, KmapInfo::from_toml)?,
                is_gaming: is_gaming,
            };
        Ok(m)
    }
}

impl FromToml for Vec<Vec<SwitchPos>> {
    fn from_toml(toml_array: &Value) -> Result<Vec<Vec<SwitchPos>>>{
        Ok(
            toml_to_vec(toml_array,
                    |d1| Ok(toml_to_vec(d1, |d2| Ok(SwitchPos::from_toml(d2)?))?)
            )?
        )
    }
}

impl FromToml for bool {
    fn from_toml(toml_value: &Value) -> Result<bool >{
        // TODO refactor without match?
        match *toml_value {
            Value::Boolean(b) =>
                Ok(b),
            _ =>
                Err(ErrorKind::BadValue("bool".into(), None).into()),
        }
    }
}

impl FromToml for String {
    fn from_toml(toml_value: &Value) -> Result<String >{
        match *toml_value {
            Value::String(ref s) =>
                Ok(s.clone()),
            _ =>
                Err(ErrorKind::BadValue("String".into(), None).into()),
        }
    }
}

impl FromToml for u8 {
    fn from_toml(toml_value: &Value) -> Result<u8 >{
        match *toml_value {
            Value::Integer(i) if (i >= 0 && i <= 255) =>
                Ok(i as u8),
            _ =>
                Err(ErrorKind::BadValue("u8 integer".into(), None).into()),
        }
    }
}

impl FromToml for i32 {
    fn from_toml(toml_value: &Value) -> Result<i32 >{
        match *toml_value {
            // TODO check if integers are in i32 range
            Value::Integer(i) =>
                Ok(i as i32),
            _ =>
                Err(ErrorKind::BadValue("i32 integer".into(), None).into()),
        }
    }
}

pub fn toml_to_map(toml_table: &Value) -> Result<BTreeMap<String, Value>>{
    // TODO refactor
    match *toml_table {
        Value::Table(ref m) => {
            Ok(m.clone())
        },
        _ =>
            Err(ErrorKind::BadValue("toml table".into(), None).into()),
    }
}

pub fn toml_to_vec<T, F>(toml_array: &Value, f: F) -> Result<Vec<T>>
    where F: Fn(&Value)->Result<T>
{
    // TODO refactor
    let v = match *toml_array {
        Value::Array(ref v) =>
            v,
        _ =>
            bail!(ErrorKind::BadValue("array".into(), None)),
    };
    // TODO any way to combine map and ?
    let mut new_vec = Vec::new();
    for (n, x) in v.iter().enumerate(){
        new_vec.push(
            f(x).chain_err(||format!("at index: {}", n))?
        );
    }
    Ok(new_vec)
}

pub fn get_key<'a>(toml_table: &'a Value, key: &str) -> Result<&'a Value> {
    // TODO include name in error
    // TODO check if it's a table
    toml_table.get(key).ok_or_else(
        || ErrorKind::MissingValue("key".into(), Some(key.into())).into()
    )
}
