//! This module handles the details of writing the configuration data to output
//! files.

use self::kmap_builder::KmapBuilder;
use self::mode_builder::ModeBuilder;

#[macro_use]
mod c_struct;

mod format_c;
mod kmap_builder;
mod mode_builder;
mod render;
