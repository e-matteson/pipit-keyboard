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
            fn format(&self, name: &CCode) -> Format {
                let h = format!("extern const {} {};\n", stringify!($struct_type), name);
                let mut c = format!("const {} {} = {{\n", stringify!($struct_type), name);
                $(c += &format!("  {}, // {}\n", self.$field.to_c(), stringify!($field));)*
                c += "}\n";
                Format {
                    h: CCode(h),
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
