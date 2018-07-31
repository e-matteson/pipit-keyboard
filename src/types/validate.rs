use std::collections::BTreeMap;
use std::path::PathBuf;

use types::CCode;

// use types::errors::*;
use failure::{Error, ResultExt};

// require Deserialize?

pub trait Validate {
    fn validate(&self) -> Result<(), Error>;
}

////////////////////////////////////////////////////////////////////////////////

impl<K, V> Validate for BTreeMap<K, V>
where
    K: Validate + ToString,
    V: Validate,
{
    fn validate(&self) -> Result<(), Error> {
        for (key, val) in self {
            key.validate().context("Invalid entry")?;
            val.validate()
                .context(format!("Invalid value for: '{}'", key.to_string()))?;
        }
        Ok(())
    }
}

impl<T> Validate for Vec<T>
where
    T: Validate,
{
    fn validate(&self) -> Result<(), Error> {
        for x in self {
            x.validate()?;
        }
        Ok(())
    }
}

impl<T> Validate for [T; 3]
where
    T: Validate,
{
    fn validate(&self) -> Result<(), Error> {
        self[0].validate()?;
        self[1].validate()?;
        self[2].validate()?;
        Ok(())
    }
}

impl<T> Validate for Option<T>
where
    T: Validate,
{
    fn validate(&self) -> Result<(), Error> {
        // A None value is always valid.
        if let Some(ref contents) = self {
            contents.validate()?;
        }
        Ok(())
    }
}

impl Validate for PathBuf {
    fn validate(&self) -> Result<(), Error> {
        // Always valid.
        Ok(())
    }
}

impl Validate for bool {
    fn validate(&self) -> Result<(), Error> {
        // Primitive types are always valid.
        Ok(())
    }
}

// impl Validate for String {
//     fn validate(&self) -> Result<(), Error> {
//         // Primitive types are always valid.
//         Ok(())
//     }
// }

impl Validate for CCode {
    fn validate(&self) -> Result<(), Error> {
        // TODO sanitize?
        Ok(())
    }
}

// #[derive(Deserialize, Debug)]
// #[serde(deny_unknown_fields)]
macro_rules! validated_struct {
    (
        $( #[$nested_macro:meta] )*
            pub struct $struct_type:ident {
                $(
                    $( #[$attribute:meta] )*
                        pub $field:ident : $field_type:ty,
                )*
            }
    )
        => {
            $( #[$nested_macro] )*
                pub struct $struct_type {
                    $(
                        $( #[$attribute] )*
                            pub $field: $field_type,
                    )*
                }
            impl Validate for $struct_type {
                fn validate(&self) -> Result<(), Error> {
                    $(
                        &self.$field.validate()
                            .context(
                                format!("Invalid value in: '{}'", stringify!($field))
                            )?;
                    )*
                        Ok(())
                }
            }
        };
}

macro_rules! always_valid_enum {
    (
        $( #[$nested_macro:meta] )*
            pub enum $enum_type:ident {
                $(
                    $( #[$attribute:meta] )*
                        $field:ident,
                )*
            }
    )
        => {
            $( #[$nested_macro] )*
                pub enum $enum_type {
                    $(
                        $( #[$attribute] )*
                            $field,
                    )*
                }
            impl Validate for $enum_type {
                fn validate(&self) -> Result<(), Error> {
                    Ok(())
                }
            }
        };
}
