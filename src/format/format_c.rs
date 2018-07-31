use itertools::Itertools;
use std::fmt::Display;
use std::fs::OpenOptions;
use std::io::Write;
use std::ops::AddAssign;
use std::path::Path;
use std::path::PathBuf;

use failure::{Error, Fail, ResultExt};
use types::errors::BadValueErr;
use types::{CCode, CTree, Field, ToC};

#[derive(Debug, Default)]
pub struct CFiles {
    pub h: CCode, // for header file
    pub c: CCode, // for cpp file
}

////////////////////////////////////////////////////////////////////////////////

impl CTree {
    pub fn format(&self) -> Result<CFiles, Error> {
        Ok(match *self {
            CTree::Include { ref path } => format_include(path),
            CTree::LiteralH(ref text) => CFiles::with_h(text),
            CTree::LiteralC(ref text) => CFiles::with_c(text),
            CTree::Group(ref vec) => format_group(vec)?,
            CTree::Define {
                ref name,
                ref value,
            } => format_define(name, value),
            CTree::DefineIf { ref name, value } => if value {
                format_define(name, &CCode::new())
            } else {
                CFiles::new()
            },
            CTree::Ifndef {
                ref conditional,
                ref contents,
            } => format_ifndef(conditional, contents)?,
            CTree::Var {
                ref name,
                ref value,
                ref c_type,
                is_extern,
            } => format_var(name, value, c_type, is_extern),
            CTree::Array {
                ref name,
                ref values,
                ref c_type,
                is_extern,
            } => format_array(name, values, c_type, is_extern),
            CTree::CompoundArray {
                ref name,
                ref values,
                ref subarray_type,
                is_extern,
            } => format_compound_array(name, values, subarray_type, is_extern)?,
            CTree::EnumDecl {
                ref name,
                ref variants,
                ref size,
            } => format_enum_decl(name, variants, size),
            CTree::StructInstance {
                ref name,
                ref c_type,
                ref fields,
                is_extern,
            } => format_struct_instance(name, c_type, fields, is_extern),
            CTree::Namespace {
                ref name,
                ref contents,
            } => format_namespace(name, contents)?,
            CTree::IncludeGuard {
                ref header_name,
                ref contents,
            } => format_include_guard(header_name, contents)?,
        })
    }

    pub fn initializer(&self) -> CCode {
        // TODO reorganize this. Is it really the best way to get struct
        // initializers (for arrays of structs)?
        match *self {
            CTree::StructInstance { ref fields, .. } => {
                format_struct_initializer(fields)
            }
            CTree::Include { .. }
            | CTree::LiteralH(..)
            | CTree::LiteralC(..)
            | CTree::Group(..)
            | CTree::Define { .. }
            | CTree::DefineIf { .. }
            | CTree::Ifndef { .. }
            | CTree::Var { .. }
            | CTree::Array { .. }
            | CTree::CompoundArray { .. }
            | CTree::EnumDecl { .. }
            | CTree::Namespace { .. }
            | CTree::IncludeGuard { .. } => unimplemented!(),
        }
    }
}

impl CFiles {
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

    pub fn append_newline(&mut self) {
        self.h += "\n";
        self.c += "\n";
    }

    pub fn save(
        &self,
        directory: &PathBuf,
        name_base: &str,
    ) -> Result<Vec<PathBuf>, Error> {
        let mut base = directory.to_owned();
        base.push(name_base);

        let mut h_path = base.clone();
        h_path.set_extension("h");

        let mut cpp_path = base;
        cpp_path.set_extension("cpp");

        write_to_file(h_path.clone(), &self.h)?;
        write_to_file(cpp_path.clone(), &self.c)?;
        Ok(vec![h_path, cpp_path])
    }
}

impl AddAssign<CFiles> for CFiles {
    fn add_assign(&mut self, rhs: CFiles) {
        self.append(&rhs)
    }
}

impl<'a> AddAssign<&'a CFiles> for CFiles {
    fn add_assign(&mut self, rhs: &'a CFiles) {
        self.append(rhs)
    }
}

fn format_enum_decl(
    name: &CCode,
    variants: &[CCode],
    size: &Option<CCode>,
) -> CFiles {
    let contents = variants
        .into_iter()
        .enumerate()
        .fold(String::new(), |acc, (index, field)| {
            format!("{}  {} = {},\n", acc, field, index)
        });
    let inheritance = if let Some(ref parent_type) = size {
        format!(" : {} ", parent_type)
    } else {
        String::new()
    };
    CFiles {
        h: CCode(format!(
            "enum {}{}{{\n{}}};\n\n",
            name, inheritance, contents
        )),
        c: CCode::new(),
    }
}

fn format_define(name: &CCode, value: &CCode) -> CFiles {
    // Name will be written in all-caps.
    CFiles {
        h: CCode(format!("#define {} {}\n", name.to_uppercase(), value)),
        c: CCode::new(),
    }
}

fn format_include(path: &CCode) -> CFiles {
    CFiles::with_h(&format!("#include {}\n", path).to_c())
}

fn format_ifndef(
    conditional: &CCode,
    contents: &CTree,
) -> Result<CFiles, Error> {
    let mut f = CFiles::new();
    f += CFiles::with_h(&format!("\n#ifndef {}\n", conditional));
    f += contents.format()?;
    f += CFiles::with_h(&format!("#endif // ifndef {}\n\n", conditional));
    Ok(f)
}

fn format_include_guard(
    header_name: &str,
    contents: &CTree,
) -> Result<CFiles, Error> {
    let id = make_guard_id(header_name)?;
    let mut f = CFiles {
        h: format!("#ifndef {}\n#define {}\n", id, id).to_c(),
        c: format!("#include \"{}\"\n", header_name).to_c(),
    };
    f += contents.format()?;
    f += CFiles::with_h(&format!("#endif // {}\n", id));
    Ok(f)
}

fn format_namespace(name: &CCode, contents: &CTree) -> Result<CFiles, Error> {
    let open = format!("namespace {} {{\n", name).to_c();
    let close = format!("\n}} // end namespace {}\n", name).to_c();
    let mut f = CFiles::with(&open);
    f += contents.format()?;
    f += CFiles::with(&close);
    Ok(f)
}

fn format_group(v: &[CTree]) -> Result<CFiles, Error> {
    let mut f = CFiles::new();
    for node in v {
        f += node.format()?
    }
    Ok(f)
}

fn format_compound_array(
    name: &CCode,
    values: &[Vec<CCode>],
    subarray_type: &CCode,
    is_extern: bool,
) -> Result<CFiles, Error> {
    // TODO prepend underscore? special meaning?
    let subarray_names: Vec<_> = (0..values.len())
        .map(|x| CCode(format!("{}_{}", name, x)))
        .collect();
    let mut g = Vec::new();
    for (sub_name, sub_values) in subarray_names.iter().zip(values.into_iter())
    {
        g.push(CTree::Array {
            name: sub_name.to_owned(),
            values: sub_values.to_owned(),
            c_type: subarray_type.to_c(),
            is_extern: false,
        });
    }

    g.push(CTree::Array {
        name: name.to_owned(),
        values: subarray_names,
        c_type: format!("{}*", subarray_type).to_c(),
        is_extern,
    });
    CTree::Group(g).format()
}

fn format_var(
    name: &CCode,
    value: &CCode,
    c_type: &CCode,
    is_extern: bool,
) -> CFiles {
    let h = if is_extern {
        format!("extern const {} {};\n", c_type, name).to_c()
    } else {
        CCode::new()
    };
    CFiles {
        h,
        c: CCode(format!("const {} {} = {};\n\n", c_type, name, value)),
    }
}

fn format_struct_instance(
    name: &CCode,
    c_type: &CCode,
    fields: &[Field],
    is_extern: bool,
) -> CFiles {
    format_var(name, &format_struct_initializer(fields), c_type, is_extern)
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
) -> CFiles {
    let h = if is_extern {
        CCode(format!("extern const {} {}[];\n", c_type, name))
    } else {
        CCode::new()
    };

    CFiles {
        h,
        c: CCode(format!(
            "const {} {}[] = {};\n\n",
            c_type,
            name,
            make_c_array_contents(values)
        )),
    }
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

fn make_guard_id(h_file_name: &str) -> Result<CCode, Error> {
    // TODO remove unsafe characters, like the python version
    let header_error = || BadValueErr {
        thing: "header file path".into(),
        value: h_file_name.into(),
    };

    let p: String = Path::new(h_file_name)
        .file_name()
        .ok_or_else(|| {
            header_error().context("unable to extract file name from path")
        })?.to_str()
        .expect("failed to get file name as str?")
        .to_string()
        .to_uppercase()
        .chars()
        .map(|c| if c.is_alphanumeric() { c } else { '_' })
        .collect();

    let first = p.chars().nth(0).ok_or_else(|| {
        header_error().context("unable to get first character of file name")
    })?;
    if !first.is_alphabetic() && first != '_' {
        Err(header_error()).context(
            "file name must begin with an alphabet letter or underscore",
        )?;
    }
    Ok(CCode(p + "_"))
}

pub fn write_to_file(full_path: PathBuf, s: &CCode) -> Result<(), Error> {
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
