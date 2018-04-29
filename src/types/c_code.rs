use std::fmt;
use std::borrow::Borrow;
use std::ops::AddAssign;

use types::{AnagramNum, ModeName, Name, SeqType};

#[derive(Clone, Hash, Debug, Default, Eq, PartialEq, Ord, PartialOrd,
         Deserialize)]
#[serde(deny_unknown_fields)]
pub struct CCode(pub String);

pub trait ToC {
    fn to_c(self) -> CCode;
}

// pub trait RenderCTree {
//     fn definitions(self) -> CTree;
//     fn name(self) -> CTree;
// }

#[derive(Debug, Clone)]
pub enum CTree {
    Define {
        name: CCode,
        value: CCode,
    },
    DefineIf {
        name: CCode,
        value: bool,
    },
    Ifndef {
        conditional: CCode,
        contents: Box<CTree>,
    },
    Var {
        name: CCode,
        value: CCode,
        c_type: CCode,
        is_extern: bool,
    },
    Array {
        name: CCode,
        values: Vec<CCode>,
        c_type: CCode,
        is_extern: bool,
    },
    CompoundArray {
        name: CCode,
        values: Vec<Vec<CCode>>,
        subarray_type: CCode,
        is_extern: bool,
    },
    EnumDecl {
        name: CCode,
        variants: Vec<CCode>,
        size: Option<CCode>,
    },
    StructInstance {
        name: CCode,
        fields: Vec<Field>,
        c_type: CCode,
        is_extern: bool,
    },
    Namespace {
        name: CCode,
        contents: Box<CTree>,
    },
    Include {
        path: CCode,
    },
    IncludeGuard {
        header_name: String,
        contents: Box<CTree>,
    },
    // Typedef { name: CCode, value: CCode },
    LiteralH(CCode),
    LiteralC(CCode),
    Group(Vec<CTree>),
    /* CommentC(CCode),
     * CommentH(CCode), */
}

#[derive(Debug, Clone)]
pub struct Field {
    pub name: CCode,
    pub value: CCode,
}

impl CCode {
    pub fn new() -> CCode {
        CCode(String::new())
    }

    pub fn to_uppercase(&self) -> CCode {
        CCode(self.0.to_uppercase())
    }

    pub fn join(v: &[CCode], separator: &str) -> CCode {
        CCode(v.join(separator))
    }

    pub fn vec<T>(v: &[T]) -> Vec<CCode>
    where
        T: ToC + Clone,
    {
        v.iter().map(|ref item| item.to_c()).collect()
    }

    pub fn map_prepend<T>(prefix: T, v: &[CCode]) -> Vec<CCode>
    where
        T: ToC + Clone,
    {
        let prefix = prefix.to_c();
        v.into_iter()
            .map(|c| format!("{}{}", prefix, c).to_c())
            .collect()
    }
}

impl<'a> Borrow<str> for CCode {
    fn borrow(&self) -> &str {
        &(self.0)
    }
}

impl<'a> Borrow<str> for &'a CCode {
    fn borrow(&self) -> &str {
        &(self.0)
    }
}

impl fmt::Display for CCode {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl AddAssign<CCode> for CCode {
    fn add_assign(&mut self, rhs: CCode) {
        self.0 += &rhs.0;
    }
}

impl<'a> AddAssign<&'a CCode> for CCode {
    fn add_assign(&mut self, rhs: &'a CCode) {
        self.0 += &rhs.0;
    }
}

impl AddAssign<String> for CCode {
    fn add_assign(&mut self, rhs: String) {
        self.0 += &rhs;
    }
}

impl<'a> AddAssign<&'a str> for CCode {
    fn add_assign(&mut self, rhs: &'a str) {
        self.0 += rhs;
    }
}

impl<'a, T> ToC for &'a T
where
    T: ToC + Clone,
{
    fn to_c(self) -> CCode {
        self.to_owned().to_c()
    }
}

impl<'a, T> ToC for &'a mut T
where
    T: ToC + Clone,
{
    fn to_c(self) -> CCode {
        self.to_owned().to_c()
    }
}

impl ToC for String {
    // TODO why clone?
    fn to_c(self) -> CCode {
        // CCode(self.clone())
        CCode(self)
    }
}

impl<'a> ToC for &'a str {
    fn to_c(self) -> CCode {
        CCode(self.to_owned())
    }
}

impl ToC for CCode {
    fn to_c(self) -> CCode {
        self.clone()
    }
}

impl ToC for Name {
    fn to_c(self) -> CCode {
        CCode(self.0.to_owned())
    }
}

impl ToC for ModeName {
    fn to_c(self) -> CCode {
        CCode(self.0.to_owned())
    }
}

impl ToC for SeqType {
    fn to_c(self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for AnagramNum {
    fn to_c(self) -> CCode {
        self.0.to_c()
    }
}

impl ToC for bool {
    fn to_c(self) -> CCode {
        let s = if self { "1" } else { "0" };
        CCode(s.to_owned())
    }
}

impl ToC for i32 {
    fn to_c(self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for u8 {
    fn to_c(self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for u32 {
    fn to_c(self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for u16 {
    fn to_c(self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for usize {
    fn to_c(self) -> CCode {
        CCode(self.to_string())
    }
}

impl<T> ToC for Vec<T>
where
    T: ToC,
{
    /// Format the Vec like a c array initializer.
    fn to_c(self) -> CCode {
        let strings: Vec<String> =
            self.into_iter().map(|x| x.to_c().into()).collect();
        CCode(format!("{{ {} }}", strings.join(", ")))
    }
}

impl Into<String> for CCode {
    fn into(self) -> String {
        self.0
    }
}

impl<'a> Into<String> for &'a CCode {
    fn into(self) -> String {
        (&self.0).to_owned()
    }
}
