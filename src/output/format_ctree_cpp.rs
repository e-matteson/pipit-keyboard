use itertools::Itertools;

use super::format_ctree_shared::COut;
use error::Error;
use types::{CIdent, CTree, CType};

impl CTree {
    pub fn format_to_cpp(&self) -> Result<COut, Error> {
        Ok(match *self {
            CTree::Include { ref path } => format_include(path),
            CTree::Literal(ref literal) => COut(literal.to_string()),
            CTree::Comment(ref text) => COut(format!("/*\n{}\n*/\n", text)),
            CTree::Quote(ref text) => COut(text.to_owned()),
            CTree::Ident(ref ident) => COut(ident.to_string()),
            CTree::Type(ref c_type) => c_type.format_to_cpp(),
            CTree::Address(ref ident) => {
                COut(format!("&{}", ident.to_string()))
            }
            CTree::Group(ref vec) => format_group(vec)?,
            CTree::DefineIf {
                ref name,
                is_defined,
            } => {
                if is_defined {
                    format_define(name)
                } else {
                    COut::new()
                }
            }
            CTree::ConstDef {
                ref name,
                ref value,
                ref c_type,
            } => format_const_def(name, value, c_type)?,
            CTree::ArrayInit { ref values } => format_array_init(values)?,
            CTree::EnumDecl {
                ref enum_type,
                ref variants,
                ref underlying_type,
            } => format_enum_decl(enum_type, variants, underlying_type),
            CTree::StructInit {
                ref struct_type,
                ref values,
            } => format_struct_init(struct_type, values)?,
            CTree::Namespace {
                ref name,
                ref contents,
            } => format_namespace(name, contents)?,
            CTree::Cast {
                ref value,
                ref new_type,
            } => format_cast(value, new_type)?,
        })
    }
}

fn format_cast(value: &CTree, new_type: &CType) -> Result<COut, Error> {
    Ok(COut(format!(
        "static_cast<{}>({})",
        new_type.format_to_cpp().0,
        value.format_to_cpp()?.0
    )))
}

fn format_enum_decl(
    enum_type: &CIdent,
    variants: &[CIdent],
    underlying_type: &Option<CType>,
) -> COut {
    let contents = variants
        .iter()
        .enumerate()
        .fold(String::new(), |acc, (index, field)| {
            format!("{}  {} = {},\n", acc, field, index)
        });
    let inheritance = if let Some(ref parent_type) = underlying_type {
        format!(" : {} ", parent_type.format_to_cpp().0)
    } else {
        String::new()
    };
    COut(format!(
        "enum class {}{}{{\n{}}};\n\n",
        enum_type, inheritance, contents
    ))
}

fn format_define(name: &CIdent) -> COut {
    // Name will be written in all-caps.
    COut(format!("#define {}\n", name.0.to_uppercase()))
}

fn format_include(path: &str) -> COut {
    COut(format!("#include {}\n", path))
}

fn format_namespace(name: &CIdent, contents: &CTree) -> Result<COut, Error> {
    let mut f = COut(format!("namespace {} {{\n", name));
    f += contents.format_to_cpp()?;
    f += format!("\n}} // end namespace {}\n", name);
    Ok(f)
}

fn format_const_def(
    name: &CIdent,
    value: &CTree,
    c_type: &CType,
) -> Result<COut, Error> {
    Ok(COut(format!(
        "{} const {} = {};\n\n",
        c_type.format_to_cpp().0,
        name,
        value.format_to_cpp()?.0,
    )))
}

fn format_struct_init(
    struct_type: &CType,
    values: &[CTree],
) -> Result<COut, Error> {
    let elements: String = values
        .iter()
        .map(|value| Ok(format!("{}", value.format_to_cpp()?.0)))
        .collect::<Result<Vec<_>, Error>>()?
        .iter()
        .join(",\n  ");
    Ok(COut(format!(
        "{} {{{}}}",
        struct_type.format_to_cpp().0,
        elements
    )))
}

fn format_array_init(values: &[CTree]) -> Result<COut, Error> {
    let elements: Vec<String> = values
        .iter()
        .map(|tree| Ok(tree.format_to_cpp()?.0))
        .collect::<Result<Vec<_>, Error>>()?;

    let items_per_line = 4;
    let mut lines: Vec<String> = Vec::new();
    let chunks = elements
        .iter()
        .map(|x| x.to_string())
        .chunks(items_per_line);
    for chunk in &chunks {
        let tmp: Vec<_> = chunk.collect();
        lines.push(tmp.join(", "));
    }

    Ok(COut(format!("{{{}}}", lines.join(",\n  "))))
}

pub fn format_group(v: &[CTree]) -> Result<COut, Error> {
    let mut f = COut::new();
    for node in v {
        f += node.format_to_cpp()?;
    }
    Ok(f)
}

impl CType {
    fn format_to_cpp(&self) -> COut {
        COut(match self {
            CType::U8 => "uint8_t".to_string(),
            CType::U16 => "uint16_t".to_string(),
            CType::U32 => "uint32_t".to_string(),
            CType::Bool => "bool".to_string(),
            CType::Custom(contents) => contents.to_string(),
            CType::Pointer(ctype) => ctype.format_to_cpp().0 + " const*",
            CType::Array(element_type, length) => {
                format!(
                    "c_array_t<{}, {}>",
                    element_type.format_to_cpp().0,
                    length
                )
            }
            CType::StdArray(element_type, length) => {
                format!(
                    "std::array<{}, {}>",
                    element_type.format_to_cpp().0,
                    length
                )
            }
        })
    }
}
