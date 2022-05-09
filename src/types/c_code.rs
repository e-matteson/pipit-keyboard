use std::fmt;

pub trait CEnumVariant: Sized {
    /// The type name of C++ enum
    fn enum_type() -> CIdent;

    /// The unqualified name of this variant in the C++ enum
    fn enum_variant(&self) -> CIdent;

    /// The qualified name of this variant in the C++ enum
    fn qualified_enum_variant(&self) -> CIdent {
        CIdent(format!(
            "{}::{}",
            Self::enum_type().0,
            self.enum_variant().0
        ))
    }

    /// The underlying type determining the size of the C++ enum
    fn underlying_type() -> Option<CType> {
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
            enum_type: Self::enum_type(),
            underlying_type: Self::underlying_type(),
            variants: variants.map(|x| x.enum_variant()).collect(),
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum CType {
    U8,
    U16,
    U32,
    Bool,
    Custom(String),
    Pointer(Box<CType>),
    Array(Box<CType>, usize),
    StdArray(Box<CType>, usize),
}

impl CType {
    pub fn pointer(pointed_to: CType) -> CType {
        CType::Pointer(Box::new(pointed_to))
    }

    pub fn array(element_type: CType, length: usize) -> CType {
        CType::Array(Box::new(element_type), length)
    }

    pub fn std_array(element_type: CType, length: usize) -> CType {
        CType::StdArray(Box::new(element_type), length)
    }

    pub fn custom<T>(name: T) -> CType
    where
        T: ToString,
    {
        CType::Custom(name.to_string())
    }
}

#[derive(
    Clone, Hash, Debug, Default, Eq, PartialEq, Ord, PartialOrd, Deserialize,
)]
#[serde(deny_unknown_fields)]
pub struct CIdent(pub String);

#[derive(
    Clone, Hash, Debug, Default, Eq, PartialEq, Ord, PartialOrd, Deserialize,
)]
#[serde(deny_unknown_fields)]
pub struct CLiteral(pub String);

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum CTree {
    /// Define a preprocessor macro (with no value) if `is_defined` is true.
    DefineIf {
        name: CIdent,
        is_defined: bool,
    },
    ConstDef {
        name: CIdent,
        c_type: CType,
        value: Box<CTree>,
    },
    EnumDecl {
        enum_type: CIdent,
        variants: Vec<CIdent>,
        underlying_type: Option<CType>,
    },
    ArrayInit {
        values: Vec<CTree>,
    },
    StructInit {
        struct_type: CType,
        values: Vec<CTree>,
    },
    /// Wrap the given CTree in a namespace block.
    Namespace {
        name: CIdent,
        contents: Box<CTree>,
    },
    /// Include the given file (with quotes or angle brackets included) in the
    /// header file.
    Include {
        path: String,
    },
    Quote(String),
    Ident(CIdent),
    Type(CType),
    Literal(CLiteral),
    Address(CIdent),
    Comment(String),
    Group(Vec<CTree>),
    Cast {
        value: Box<CTree>,
        new_type: CType,
    },
}

impl CTree {
    pub fn array_def(
        name: CIdent,
        element_type: CType,
        values: Vec<CTree>,
    ) -> CTree {
        CTree::ConstDef {
            name,
            c_type: CType::array(element_type, values.len()),
            value: Box::new(CTree::ArrayInit { values }),
        }
    }

    pub fn std_array_def(
        name: CIdent,
        element_type: CType,
        values: Vec<CTree>,
    ) -> CTree {
        CTree::ConstDef {
            name,
            c_type: CType::std_array(element_type, values.len()),
            value: Box::new(CTree::ArrayInit { values }),
        }
    }
}

impl<'a> Into<CTree> for &'a CTree {
    fn into(self) -> CTree {
        self.to_owned()
    }
}

impl Into<CTree> for CIdent {
    fn into(self) -> CTree {
        CTree::Ident(self)
    }
}

impl Into<CTree> for CLiteral {
    fn into(self) -> CTree {
        CTree::Literal(self)
    }
}

impl Into<CIdent> for String {
    fn into(self) -> CIdent {
        CIdent(self)
    }
}

impl<'a> Into<CIdent> for &'a str {
    fn into(self) -> CIdent {
        CIdent(self.to_owned())
    }
}

impl fmt::Display for CIdent {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl fmt::Display for CLiteral {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}
