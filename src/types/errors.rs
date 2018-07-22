use failure::Error;

#[derive(Debug, Fail)]
#[fail(display = "Invalid ratio: {}", _0)]
pub struct RatioError(pub f32);

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
#[fail(
    display = "Out of range: '{}' is '{}', must be in range ({}, {})",
    name,
    value,
    min,
    max
)]
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
pub enum PermuteErr {
    #[fail(display = "Unable to permute: input sequence is the wrong length")]
    Length,
    #[fail(
        display = "Unable to create permutation: an element in the old \
                   sequence is not present in the new sequence"
    )]
    WouldDrop,
}

#[derive(Debug, Fail)]
#[fail(display = "Syntax error in kmap file near line {}.", _0)]
pub struct KmapSyntaxErr(pub usize);

pub fn pretty_unwrap<T>(result: Result<T, Error>) -> T
where
    T: Sized,
{
    result.unwrap_or_else(|e| print_and_panic(e))
}

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
