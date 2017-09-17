// Macro for creating a struct that knows the names of it's own fields.
// This allows it to format itself as a C struct.

macro_rules! c_struct {
    ( struct $struct_type: ident { $( $field:ident : $field_type:ty),* }) => {
        #[derive(Debug)]
        struct $struct_type {
            $($field: $field_type,)*
        }
        impl $struct_type {
            // TODO inline for efficiency?
            // TODO optionally extern?
            // TODO whats up with semicolons? diff between kmap and mode?
            fn format(&self, name: &CCode) -> CFiles {
                let mut c = format!(
                    "const {} {} = {{\n",
                    stringify!($struct_type),
                    name
                );
                $(c += &format!(
                    "  {}, // {}\n",
                    (&self.$field).to_c(),
                    stringify!($field));
                )*
                c += "};\n";
                CFiles {
                    h: CCode::new(),
                    c: CCode(c),
                }
            }
        }
    };
}

// c_struct!(
//     struct ModeStruct {
//         foo : i64,
//         bar : bool
//     }
// );
