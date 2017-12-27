// #![recursion_limit = "1024"]

error_chain! {

    // Automatic conversions between this error chain and other
    // error types not defined by the `error_chain!`. These will be
    // wrapped in a new error with, in the first case, the
    // `ErrorKind::Fmt` variant. The description and cause will
    // forward to the description and cause of the original error.
    //
    // Optionally, some attributes can be added to a variant.
    //
    // This section can be empty.
    foreign_links {
        Fmt(::std::fmt::Error);
        Io(::std::io::Error) #[cfg(unix)];
        Toml(::toml::de::Error);
    }

    // Define additional `ErrorKind` variants. The syntax here is
    // the same as `quick_error!`, but the `from()` and `cause()`
    // syntax is not supported.
    errors {
        UnexpectedKey(s: String) {
            description("Unexpected key in settings")
                display("unexpected key: '{}'", s)
        }
        MissingValue(expected_type: String, for_thing: Option<String>) {
            description("Missing value")
                display("missing {}{}",
                        expected_type,
                        match *for_thing {
                            Some(ref s) => format!(" for: '{}'", s),
                            None => String::new(),
                        }
                )
        }
        OutOfRange(name: String, min: usize, max: usize) {
            description("Input out of range")
                display("Out of range: {}, ({}, {})", name, min, max)
        }
        BadValue(expected_type: String, value: Option<String>) {
            description("Bad value in settings")
                display("invalid {}{}",
                        expected_type,
                        match *value {
                            None => String::new(),
                            Some(ref s) => format!(": '{}'", s),
                        }
                )
        }
        Permute {
            description("Unable to permute")
                display("Unable to permute this sequence, because it has the wrong length")
        }
        KmapPins(s: String) {
            description(
                "Switch positions in kmap format don't match row or column pins"
            )
                display(
                    "invalid position in kmap_format: {}. Check row_pins and \
                     col_pins.",
                    s
                )
        }
        KmapSyntax(l: usize) {
            description("Syntax error in kmap file")
                display("syntax error near line {}. Is kmap_format correct?", l)
        }
        NumArgs(n: usize) {
            description("Invalid commandline arguments")
                display("Wrong number of arguments : '{}'", n)
        }
    }
}
