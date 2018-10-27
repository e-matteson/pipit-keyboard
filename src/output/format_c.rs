use itertools::Itertools;
use std::fmt::Display;
use std::fs::OpenOptions;
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
            CTree::Define {
                ref name,
                ref value,
            } => format_define(name, value),
            CTree::DefineIf {
                ref name,
                is_defined,
            } => if is_defined {
                format_define(name, &CCode::new())
            } else {
                CFilePair::new()
            },
            CTree::Ifndef {
                ref conditional,
                ref contents,
            } => format_ifndef(conditional, contents, file_name_base)?,
            CTree::ConstVar {
                ref name,
                ref value,
                ref c_type,
                is_extern,
            } => format_const_var(name, value, c_type, is_extern),
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
            } => format_compound_array(
                name,
                values,
                subarray_type,
                is_extern,
                file_name_base,
            )?,
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
            | CTree::Define { .. }
            | CTree::DefineIf { .. }
            | CTree::Ifndef { .. }
            | CTree::ConstVar { .. }
            | CTree::Array { .. }
            | CTree::CompoundArray { .. }
            | CTree::EnumDecl { .. }
            | CTree::Namespace { .. } => unimplemented!(),
        }
    }
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

fn format_enum_decl(
    name: &CCode,
    variants: &[CCode],
    size: &Option<CCode>,
) -> CFilePair {
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
    CFilePair::with_h(&format!("#include {}\n", path).to_c())
}

fn format_include_self(file_name_base: &str) -> CFilePair {
    CFilePair::with_c(&format!("#include \"{}.h\"\n", file_name_base).to_c())
}

fn format_ifndef(
    conditional: &CCode,
    contents: &CTree,
    file_name_base: &str,
) -> Result<CFilePair, Error> {
    let mut f = CFilePair::new();
    f += CFilePair::with_h(&format!("\n#ifndef {}\n", conditional));
    f += contents.format(file_name_base)?;
    f += CFilePair::with_h(&format!("#endif // ifndef {}\n\n", conditional));
    Ok(f)
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

fn format_compound_array(
    name: &CCode,
    values: &[Vec<CCode>],
    subarray_type: &CCode,
    is_extern: bool,
    file_name_base: &str,
) -> Result<CFilePair, Error> {
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
    CTree::Group(g).format(file_name_base)
}

fn format_const_var(
    name: &CCode,
    value: &CCode,
    c_type: &CCode,
    is_extern: bool,
) -> CFilePair {
    let h = if is_extern {
        format!("extern const {} {};\n", c_type, name).to_c()
    } else {
        CCode::new()
    };
    CFilePair {
        h,
        c: CCode(format!("const {} {} = {};\n\n", c_type, name, value)),
    }
}

fn format_struct_instance(
    name: &CCode,
    c_type: &CCode,
    fields: &[Field],
    is_extern: bool,
) -> CFilePair {
    format_const_var(
        name,
        &format_struct_initializer(fields),
        c_type,
        is_extern,
    )
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
) -> CFilePair {
    let length = values.len();
    let h = if is_extern {
        CCode(format!("extern const {} {}[{}];\n", c_type, name, length))
    } else {
        CCode::new()
    };

    CFilePair {
        h,
        c: CCode(format!(
            "const {} {}[{}] = {};\n\n",
            c_type,
            name,
            length,
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
