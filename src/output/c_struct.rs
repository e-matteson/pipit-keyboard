// Macro for creating a struct that knows the names of it's own fields.
// This allows it to format itself as a C struct.
// use types::CTree;

macro_rules! c_struct {
    ( struct $struct_type: ident { $( $field:ident : $field_type:ty,)* }) => {
        #[derive(Debug, PartialEq, Eq)]
        struct $struct_type {
            $($field: $field_type,)*
        }
        impl $struct_type {
            #[allow(dead_code)]
            fn render(&self, name: CIdent) -> CTree {
                CTree::ConstDef {
                    name: name,
                    c_type: Self::c_type(),
                    value: Box::new(
                        self.initializer()
                        )
                }
            }

            fn initializer(&self) -> CTree {
                CTree::StructInit{
                    values: vec![
                        $( (&self.$field).to_owned().into(), )*
                    ],
                    struct_type: Self::c_type(),
                }
            }

            fn c_type() -> CType {
                CType::Custom(stringify!($struct_type).to_string())
            }
        }
    };
}
