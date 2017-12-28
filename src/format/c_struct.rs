// Macro for creating a struct that knows the names of it's own fields.
// This allows it to format itself as a C struct.
// use types::CTree;

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
            fn render(&self, name: CCode) -> CTree {
                CTree::StructInstance{
                    name: name,
                    fields: vec![
                        $( Field{name: stringify!($field).to_c(), value: (&self.$field).to_c()}, )*
                    ],
                    c_type: stringify!($struct_type).to_c(),
                    // TODO always false?
                    is_extern: false,
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
