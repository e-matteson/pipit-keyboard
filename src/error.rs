use serde_yaml;
use std::error;
use std::fmt;
use std::io;

#[derive(Debug)]
pub enum Error {
    Missing {
        missing: String,
        container: String,
    },
    LookupErr {
        key: String,
        container: String,
    },
    ConflictErr {
        key: String,
        container: String,
    },
    OutOfRangeErr {
        name: String,
        value: usize,
        min: usize,
        max: usize,
    },
    BadValueErr {
        thing: String,
        value: String,
    },
    Empty(String),
    PermuteLength,
    PermuteWouldDrop,
    Arduino,
    KmapSyntaxErr {
        line: usize,
    },
    Style,
    Io(io::Error),
    SerdeYaml(serde_yaml::Error),
    Context {
        message: String,
        cause: Box<Error>,
    },
}

pub trait ResultExt<T> {
    /// Convert the error type to a Error, and add the context message
    /// around it.
    fn context(self, message: &str) -> Result<T, Error>;

    /// Like `context()` but take a closure containing a potentionally costly
    /// operation that will only be executed if there was an error.
    fn with_context<F>(self, message_creator: F) -> Result<T, Error>
    where
        F: Fn() -> String;
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Error::Missing { missing, container } => {
                write!(f, "Missing '{}' from '{}'", missing, container)
            }
            Error::LookupErr { key, container } => {
                write!(f, "Couldn't find '{}' in '{}'", key, container)
            }
            Error::ConflictErr { key, container } => {
                write!(f, "There cannot be more than one '{}' in '{}'", key, container)
            }
            Error::OutOfRangeErr {
                name,
                value,
                min,
                max,
            } => write!(
                f,
                "Out of range: '{}' is '{}', must be in range ({}, {})",
                name, value, min, max
            ),
            Error::BadValueErr { thing, value } => {
                write!(f, "Invalid {}: '{}'", thing, value)
            }
            Error::Empty (thing) => {
                write!(f, "{} is empty", thing)
            }
            Error::PermuteLength => write!(f, "Unable to permute: input sequence is the wrong length"),
            Error::PermuteWouldDrop => write!(f, "Unable to create permutation: an element in the old sequence is not present in the new sequence"),
            Error::KmapSyntaxErr{line} => write!(f, "Syntax error in kmap file near line {}.", line),
            Error::Style => write!(f, "Ran out of unique switch fill styles"),
            Error::Arduino => write!(f, "Error in Arduino IDE"),
            Error::Io(err) => write!(f, "Input/output error: {}", err),
            Error::SerdeYaml(err) => write!(f, "Yaml file error: {}", err),
            Error::Context { message, cause } => {
                write!(f, "{}\n  caused by: {}", message, cause)
            }
        }
    }
}

impl From<io::Error> for Error {
    fn from(io_err: io::Error) -> Error {
        Error::Io(io_err)
    }
}

impl From<serde_yaml::Error> for Error {
    fn from(err: serde_yaml::Error) -> Error {
        Error::SerdeYaml(err)
    }
}

impl error::Error for Error {
    fn cause(&self) -> Option<&error::Error> {
        match self {
            Error::Context { ref cause, .. } => Some(cause),
            Error::Io(ref cause) => Some(cause),
            _ => None,
        }
    }
}

impl Error {
    // TODO this is the same API as ResultExt... impl that instead?
    /// Wrap the error with a message providing more context about what went
    /// wrong.
    pub fn context(self, message: &str) -> Self {
        Error::Context {
            message: message.to_owned(),
            cause: Box::new(self),
        }
    }

    /// Like `context()` but take a closure containing a potentionally costly
    /// operation that will only be executed if there was an error.
    pub fn with_context<T>(self, message_creator: T) -> Self
    where
        T: Fn() -> String,
    {
        self.context(&message_creator())
    }
}

impl<T, E> ResultExt<T> for Result<T, E>
where
    Error: From<E>,
{
    fn context(self, message: &str) -> Result<T, Error> {
        self.map_err(|err| Error::from(err).context(message))
    }

    fn with_context<F>(self, message_creator: F) -> Result<T, Error>
    where
        F: Fn() -> String,
    {
        self.context(&message_creator())
    }
}
