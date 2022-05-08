use itertools::Itertools;
use std::fmt::Display;
use std::fs::{create_dir_all, OpenOptions};
use std::io::Write;
use std::ops::AddAssign;
use std::path::PathBuf;

use error::{Error, ResultExt};
use types::{CCode, CTree, Field, ToC};

#[derive(Debug, Default)]
pub struct CFilePair {
    pub h: CCode, // for header file
    pub c: CCode, // for cpp file
}

////////////////////////////////////////////////////////////////////////////////

impl CTree {
    pub fn format(&self, file_name_base: &str) -> Result<CFilePair, Error> {
        Ok(match *self {
            CTree::IncludeH { ref path } => format_include_h(path),
            CTree::IncludeSelf => format_include_self(file_name_base),
            CTree::LiteralH(ref text) => CFilePair::with_h(text),
            CTree::LiteralC(ref text) => CFilePair::with_c(text),
            CTree::Group(ref vec) => format_group(vec, file_name_base)?,
            CTree::DefineIf {
                ref name,
                is_defined,
            } => {
                if is_defined {
                    format_define(name, &CCode::new())
                } else {
                    CFilePair::new()
                }
            }
            CTree::PublicConst {
                ref name,
                ref value,
                ref c_type,
            } => format_public_const(name, value, c_type),
            CTree::PrivateConst {
                ref name,
                ref value,
                ref c_type,
            } => format_private_const(name, value, c_type),
            CTree::Array {
                ref name,
                ref values,
                ref c_type,
                is_extern,
            } => format_array(name, values, c_type, is_extern, false),
            CTree::StdArray {
                ref name,
                ref values,
                ref c_type,
                is_extern,
            } => format_array(name, values, c_type, is_extern, true),
            CTree::EnumDecl {
                ref name,
                ref variants,
                ref size,
            } => format_enum_decl(name, variants, size),
            CTree::StructInstance {
                ref name,
                ref c_type,
                ref fields,
            } => format_struct_instance(name, c_type, fields),
            CTree::Namespace {
                ref name,
                ref contents,
            } => format_namespace(name, contents, file_name_base)?,
        })
    }

    pub fn initializer(&self) -> CCode {
        // TODO reorganize this. Is it really the best way to get struct
        // initializers (for arrays of structs)?
        match *self {
            CTree::StructInstance { ref fields, .. } => {
                format_struct_initializer(fields)
            }
            CTree::IncludeH { .. }
            | CTree::IncludeSelf
            | CTree::LiteralH(..)
            | CTree::LiteralC(..)
            | CTree::Group(..)
            | CTree::DefineIf { .. }
            | CTree::PublicConst { .. }
            | CTree::PrivateConst { .. }
            | CTree::Array { .. }
            | CTree::StdArray { .. }
            | CTree::EnumDecl { .. }
            | CTree::Namespace { .. } => unimplemented!(),
        }
    }
}

fn format_enum_decl(
    name: &CCode,
    variants: &[CCode],
    size: &Option<CCode>,
) -> CFilePair {
    let contents = variants
        .iter()
        .enumerate()
        .fold(String::new(), |acc, (index, field)| {
            format!("{}  {} = {},\n", acc, field, index)
        });
    let inheritance = if let Some(ref parent_type) = size {
        format!(" : {} ", parent_type)
    } else {
        String::new()
    };
    CFilePair {
        h: CCode(format!(
            "enum class {}{}{{\n{}}};\n\n",
            name, inheritance, contents
        )),
        c: CCode::new(),
    }
}

fn format_define(name: &CCode, value: &CCode) -> CFilePair {
    // Name will be written in all-caps.
    CFilePair {
        h: CCode(format!("#define {} {}\n", name.to_uppercase(), value)),
        c: CCode::new(),
    }
}

fn format_include_h(path: &CCode) -> CFilePair {
    CFilePair::with_h(format!("#include {}\n", path))
}

fn format_include_self(file_name_base: &str) -> CFilePair {
    CFilePair::with_c(format!("#include \"{}.h\"\n", file_name_base))
}

fn format_namespace(
    name: &CCode,
    contents: &CTree,
    file_name_base: &str,
) -> Result<CFilePair, Error> {
    let open = format!("namespace {} {{\n", name).to_c();
    let close = format!("\n}} // end namespace {}\n", name).to_c();
    let mut f = CFilePair::with(&open);
    f += contents.format(file_name_base)?;
    f += CFilePair::with(&close);
    Ok(f)
}

fn format_group(v: &[CTree], file_name_base: &str) -> Result<CFilePair, Error> {
    let mut f = CFilePair::new();
    for node in v {
        f += node.format(file_name_base)?
    }
    Ok(f)
}

fn format_public_const(
    name: &CCode,
    value: &CCode,
    c_type: &CCode,
) -> CFilePair {
    CFilePair {
        h: CCode(format!("const {} {} = {};\n\n", c_type, name, value)),
        c: CCode::new(),
    }
}
fn format_private_const(
    name: &CCode,
    value: &CCode,
    c_type: &CCode,
) -> CFilePair {
    CFilePair {
        h: CCode::new(),
        c: CCode(format!("const {} {} = {};\n\n", c_type, name, value)),
    }
}

fn format_struct_instance(
    name: &CCode,
    c_type: &CCode,
    fields: &[Field],
) -> CFilePair {
    format_private_const(name, &format_struct_initializer(fields), c_type)
}

fn format_struct_initializer(fields: &[Field]) -> CCode {
    let mut lines = Vec::new();
    lines.push("{".into());
    for field in fields {
        lines.push(format!("  {}, // {}", field.value, field.name));
    }
    lines.push("}".into());
    CCode(lines.join("\n"))
}

fn format_array(
    name: &CCode,
    values: &[CCode],
    c_type: &CCode,
    is_extern: bool,
    is_std: bool,
) -> CFilePair {
    let length = values.len();
    let h = if is_extern {
        if is_std {
            format!(
                "extern const std::array<{},{}> {};\n",
                c_type, length, name,
            )
        } else {
            format!("extern const {} {}[{}];\n", c_type, name, length)
        }
        .to_c()
    } else {
        CCode::new()
    };
    let initializer = make_c_array_contents(values);
    let c = if is_std {
        format!(
            "const std::array<{},{}> {} = {};\n",
            c_type, length, name, initializer
        )
    } else {
        format!(
            "const {} {}[{}] = {};\n\n",
            c_type, name, length, initializer
        )
    }
    .to_c();

    CFilePair { h, c }
}

fn make_c_array_contents<T>(v: &[T]) -> CCode
where
    T: Display,
{
    let lines = wrap_in_braces(&to_code_vec(v));
    CCode::join(&lines, "\n")
}

fn wrap_in_braces(lines: &[CCode]) -> Vec<CCode> {
    let mut new: Vec<_> =
        lines.iter().map(|s| CCode(format!(" {}", s))).collect();
    new.insert(0, "{".to_c());
    new.push("}".to_c());
    new
}

fn to_code_vec<T>(v: &[T]) -> Vec<CCode>
where
    T: Display,
{
    // TODO rename
    let items_per_line = 4;
    let mut lines: Vec<String> = Vec::new();
    //  TODO use slice chunks instead of itertools?
    let chunks = &v.iter().map(|x| x.to_string()).chunks(items_per_line);
    for chunk in chunks {
        let tmp: Vec<_> = chunk.collect();
        lines.push(tmp.join(", ") + ", ");
    }
    let code_lines: Vec<_> = lines.into_iter().map(CCode).collect();
    code_lines
}

fn write_to_file(full_path: PathBuf, s: &CCode) -> Result<(), Error> {
    // let path = Path::new(full_path);
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(full_path)
        .context("Failed to open output file")?;

    file.set_len(0).context("Failed to clear output file")?;

    file.write_all(s.to_string().as_bytes())
        .context("Failed to write to output file")?;
    Ok(())
}

impl CFilePair {
    pub fn new() -> Self {
        Self {
            h: CCode::new(),
            c: CCode::new(),
        }
    }

    pub fn with_c<T>(contents: T) -> Self
    where
        T: ToC,
    {
        Self {
            h: CCode::new(),
            c: contents.to_c(),
        }
    }

    pub fn with_h<T>(contents: T) -> Self
    where
        T: ToC,
    {
        Self {
            h: contents.to_c(),
            c: CCode::new(),
        }
    }

    pub fn with<T>(contents: T) -> Self
    where
        T: ToC,
    {
        let contents = contents.to_c();
        Self {
            h: contents.clone(),
            c: contents,
        }
    }

    pub fn append(&mut self, other: &Self) {
        self.h += &other.h;
        self.c += &other.c;
    }

    pub fn save(
        &self,
        directory: &PathBuf,
        name_base: &str,
    ) -> Result<Vec<PathBuf>, Error> {
        create_dir_all(directory)?;
        let mut path_base = directory.to_owned();
        path_base.push(name_base);

        let mut saved_paths = Vec::new();

        // TODO if the c file tries to include an empty h file, it will fail to
        // compile...
        // TODO share code between c and h?
        if !self.h.is_empty() {
            let mut path = path_base.clone();
            path.set_extension("h");
            write_to_file(path.clone(), &self.h)?;
            saved_paths.push(path);
        }

        if !self.c.is_empty() {
            let mut path = path_base.clone();
            path.set_extension("cpp");
            write_to_file(path.clone(), &self.c)?;
            saved_paths.push(path);
        }

        Ok(saved_paths)
    }
}

impl AddAssign<CFilePair> for CFilePair {
    fn add_assign(&mut self, rhs: CFilePair) {
        self.append(&rhs)
    }
}

impl<'a> AddAssign<&'a CFilePair> for CFilePair {
    fn add_assign(&mut self, rhs: &'a CFilePair) {
        self.append(rhs)
    }
}
