use failure::Error;

#[derive(Debug, Fail)]
#[fail(display = "Invalid ratio: {}", _0)]
pub struct RatioError(pub f32);

// foreign_links {
//     Fmt(::std::fmt::Error);
//     Io(::std::io::Error) #[cfg(unix)];
//     Toml(::toml::de::Error);
// }

#[derive(Debug, Fail)]
#[fail(display = "Missing '{}' from '{}'", missing, container)]
pub struct MissingErr {
    pub missing: String,
    pub container: String,
}

#[derive(Debug, Fail)]
#[fail(display = "Couldn't find '{}' in '{}'", key, container)]
pub struct LookupErr {
    pub key: String,
    pub container: String,
}

#[derive(Debug, Fail)]
#[fail(display = "Conflict: '{}' already exists in '{}'", key, container)]
pub struct ConflictErr {
    pub key: String,
    pub container: String,
}

#[derive(Debug, Fail)]
#[fail(display = "Out of range: '{}' is '{}', must be in range ({}, {})",
       name, value, min, max)]
pub struct OutOfRangeErr {
    pub name: String,
    pub value: usize,
    pub min: usize,
    pub max: usize,
}

#[derive(Debug, Fail)]
#[fail(display = "Invalid {}: '{}'", thing, value)]
pub struct BadValueErr {
    pub thing: String,
    pub value: String,
}

#[derive(Debug, Fail)]
#[fail(display = "Unable to permute: wrong length")]
pub struct PermuteErr;

// #[derive(Debug, Fail)]
// #[fail(display = "Failed to do file input or output")]
// pub struct FileErr;

#[derive(Debug, Fail)]
#[fail(display = "Syntax error near line {}. Is kmap_format correct?", _0)]
pub struct KmapSyntaxErr(pub usize);

#[derive(Debug, Fail)]
#[fail(display = "Wrong number of arguments: '{}'", _0)]
pub struct NumArgsErr(pub usize);

pub fn print_and_panic(e: Error) -> ! {
    print_error(e);
    panic!("returned error")
}

pub fn print_error(e: Error) {
    let mut causes = e.causes();
    if let Some(first) = causes.next() {
        println!("error: {}", first);
    }
    for cause in causes {
        println!("cause: {}", cause);
    }
}
