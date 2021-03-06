use std::borrow::Borrow;
use std::fmt;
use std::ops::AddAssign;

use types::{AnagramNum, ModeName, Name, SeqType};

#[derive(
    Clone, Hash, Debug, Default, Eq, PartialEq, Ord, PartialOrd, Deserialize,
)]
#[serde(deny_unknown_fields)]
pub struct CCode(pub String);

pub trait ToC {
    fn to_c(self) -> CCode;
}

pub trait CEnumVariant: Sized {
    /// The type name of C++ enum
    fn enum_type() -> CCode;

    /// The unqualified name of this variant in the C++ enum
    fn enum_variant(&self) -> CCode;

    /// The qualified name of this variant in the C++ enum
    fn qualified_enum_variant(&self) -> CCode {
        format!("{}::{}", Self::enum_type(), self.enum_variant()).to_c()
    }

    /// The underlying type determining the size of the C++ enum
    fn underlying_type() -> Option<CCode> {
        None
    }

    /// Declare a c enum using the given variants.
    fn render_c_enum<'a, T>(variants: T) -> CTree
    where
        T: Iterator<Item = &'a Self>,
        Self: 'a,
    {
        // TODO ensure variants are unique?
        CTree::EnumDecl {
            name: Self::enum_type(),
            size: Self::underlying_type(),
            variants: variants.map(|x| x.enum_variant()).collect(),
        }
    }
}

// TODO get rid of unused variants
#[derive(Debug, Clone)]
pub enum CTree {
    /// Define a preprocessor macro with the given name and value.
    Define {
        name: CCode,
        value: CCode,
    },
    /// Define a preprocessor macro (with no value) if `is_defined` is true.
    DefineIf {
        name: CCode,
        is_defined: bool,
    },
    /// Wrap the contents in a preprocessor ifndef block.
    Ifndef {
        conditional: CCode,
        contents: Box<CTree>,
    },
    // Declare and initialize a const variable.
    ConstVar {
        name: CCode,
        value: CCode,
        c_type: CCode,
        is_extern: bool,
    },
    StdArray {
        name: CCode,
        values: Vec<CCode>,
        c_type: CCode,
        is_extern: bool,
    },
    Array {
        name: CCode,
        values: Vec<CCode>,
        c_type: CCode,
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
    /// Wrap the given CTree in a namespace block.
    Namespace {
        name: CCode,
        contents: Box<CTree>,
    },
    /// Include the given file (with quotes or angle brackets included) in the
    /// header file.
    IncludeH {
        path: CCode,
    },
    /// Include the name of this header file in this cpp file.
    IncludeSelf,
    LiteralH(CCode),
    LiteralC(CCode),
    Group(Vec<CTree>),
}

#[derive(Debug, Clone)]
pub struct Field {
    pub name: CCode,
    pub value: CCode,
}

impl CCode {
    pub fn new() -> Self {
        CCode(String::new())
    }

    pub fn is_empty(&self) -> bool {
        self.0.is_empty()
    }

    pub fn to_uppercase(&self) -> Self {
        CCode(self.0.to_uppercase())
    }

    pub fn join(v: &[Self], separator: &str) -> Self {
        CCode(v.join(separator))
    }

    pub fn vec<T>(v: &[T]) -> Vec<Self>
    where
        T: ToC + Clone,
    {
        v.iter().map(|ref item| item.to_c()).collect()
    }

    pub fn map_prepend<T>(prefix: T, v: &[Self]) -> Vec<Self>
    where
        T: ToC + Clone,
    {
        let prefix = prefix.to_c();
        v.iter()
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
    fn to_c(self) -> CCode {
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
        self.get().to_c()
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
