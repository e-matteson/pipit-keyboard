use itertools::Itertools;
use std::fs::{create_dir_all, OpenOptions};
use std::io::Write;
use std::ops::AddAssign;
use std::path::PathBuf;

use error::{Error, ResultExt};
use types::{AnagramNum, CIdent, CLiteral, CTree, CType, Delay, Pin};

#[derive(Debug, Default)]
pub struct COut(pub String);

impl COut {
    pub fn new() -> COut {
        COut(String::new())
    }

    pub fn save(
        &self,
        directory: &PathBuf,
        name_base: &str,
    ) -> Result<PathBuf, Error> {
        create_dir_all(directory)?;
        let mut path = directory.to_owned();
        path.push(name_base);
        path.set_extension("h");
        write_to_file(path.clone(), &self.0)?;
        Ok(path)
    }
}

////////////////////////////////////////////////////////////////////////////////

impl CTree {
    pub fn format(&self) -> Result<COut, Error> {
        Ok(match *self {
            CTree::Include { ref path } => format_include(path),
            CTree::Literal(ref literal) => COut(literal.to_string()),
            CTree::Comment(ref text) => COut(format!("/*\n{}\n*/\n", text)),
            CTree::Quote(ref text) => COut(text.to_owned()),
            CTree::Ident(ref ident) => COut(ident.to_string()),
            CTree::Type(ref c_type) => c_type.format(),
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
            } => COut(format!(
                "static_cast<{}>({})",
                new_type.format().0,
                value.format()?.0
            )),
        })
    }
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
        format!(" : {} ", parent_type.format().0)
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
    f += contents.format()?;
    f += format!("\n}} // end namespace {}\n", name);
    Ok(f)
}

fn format_group(v: &[CTree]) -> Result<COut, Error> {
    let mut f = COut::new();
    for node in v {
        f += node.format()?;
    }
    Ok(f)
}

fn format_const_def(
    name: &CIdent,
    value: &CTree,
    c_type: &CType,
) -> Result<COut, Error> {
    Ok(COut(format!(
        "{} const {} = {};\n\n",
        c_type.format().0,
        name,
        value.format()?.0,
    )))
}

fn format_struct_init(
    struct_type: &CType,
    values: &[CTree],
) -> Result<COut, Error> {
    let elements: String = values
        .iter()
        .map(|value| Ok(format!("{}", value.format()?.0)))
        .collect::<Result<Vec<_>, Error>>()?
        .iter()
        .join(",\n  ");
    Ok(COut(format!("{} {{{}}}", struct_type.format().0, elements)))
}

fn format_array_init(values: &[CTree]) -> Result<COut, Error> {
    let elements: Vec<String> = values
        .iter()
        .map(|tree| Ok(tree.format()?.0))
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

fn write_to_file(full_path: PathBuf, s: &str) -> Result<(), Error> {
    // let path = Path::new(full_path);
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(full_path)
        .context("Failed to open output file")?;

    file.set_len(0).context("Failed to clear output file")?;

    file.write_all(s.as_bytes())
        .context("Failed to write to output file")?;
    Ok(())
}

impl AddAssign<COut> for COut {
    fn add_assign(&mut self, rhs: COut) {
        self.0 += &rhs.0;
    }
}

impl AddAssign<String> for COut {
    fn add_assign(&mut self, rhs: String) {
        self.0 += &rhs;
    }
}

impl<'a> AddAssign<&'a COut> for COut {
    fn add_assign(&mut self, rhs: &'a COut) {
        self.0 += &rhs.0;
    }
}

impl CType {
    fn format(&self) -> COut {
        COut(match self {
            CType::U8 => "uint8_t".to_string(),
            CType::U16 => "uint16_t".to_string(),
            CType::U32 => "uint32_t".to_string(),
            CType::Bool => "bool".to_string(),
            CType::Custom(contents) => contents.to_string(),
            CType::Pointer(ctype) => ctype.format().0 + " const*",
            CType::Array(element_type, length) => {
                format!("c_array_t<{}, {}>", element_type.format().0, length)
            }
            CType::StdArray(element_type, length) => {
                format!("std::array<{}, {}>", element_type.format().0, length)
            }
        })
    }
}

impl Into<CTree> for AnagramNum {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for Delay {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.0.to_string()))
    }
}

impl Into<CTree> for Pin {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.0.to_string()))
    }
}

impl Into<CTree> for u8 {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for u16 {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for usize {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for bool {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}
