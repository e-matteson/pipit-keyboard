mod draw;
mod keyboard;
mod switch;

use std::path::PathBuf;

use serde_yaml;
use svg;
use svg::node::element::{Definitions, Group};
use svg::Document;
use svg::Node;

use failure::{Error, ResultExt};

use cheatsheet::keyboard::{Keyboard, KeyboardSpec};
use cheatsheet::switch::Switch;
use types::{ModeName, TutorData};
use util::{read_file, user_confirm, ConfirmDefault};

use cheatsheet::draw::{FillPattern, MyDescription, MyRect, P2, V2};

#[derive(Clone, Debug)]
pub struct CheatSheet {
    keyboards: Vec<Keyboard>,
    page_width: f64,
    page_height: f64,
    default_svg_filename: PathBuf,
}

#[derive(Clone, Debug, Deserialize)]
pub struct CheatSheetSpec {
    keyboards: Vec<Option<KeyboardSpec>>,
    page_width: f64,
    page_height: f64,
    mode: ModeName,
    // TODO add title?
}

////////////////////////////////////////////////////////////////////////////////

impl CheatSheet {
    pub fn from_yaml(path: &PathBuf, data: &TutorData) -> Result<Self, Error> {
        let file = read_file(path).with_context(|_| {
            format!("failed to read cheatsheet config file: {:?}", path)
        })?;
        let spec: CheatSheetSpec =
            serde_yaml::from_str(&file).with_context(|_| {
                format!("failed to parse cheatsheet config file: {:?}", path)
            })?;
        Self::new(&spec, data, Self::config_path_to_svg_path(path)?)
    }

    pub fn new(
        spec: &CheatSheetSpec,
        data: &TutorData,
        default_svg_filename: PathBuf,
    ) -> Result<Self, Error> {
        // TODO keyboards are not exactly centered
        let num_cols = 2.;
        let num_rows = (spec.keyboards.len() as f64 / num_cols).ceil();

        let x_padding =
            (spec.page_width - num_cols * Keyboard::width()) / (num_cols + 1.);
        let y_padding = (spec.page_height - num_rows * Keyboard::height())
            / (num_rows + 1.);

        let mut col_positions: Vec<_> = (0..num_cols as usize)
            .map(|c| {
                let c = c as f64;
                P2::new((c + 1.) * x_padding + c * Keyboard::width(), y_padding)
            }).collect();

        let height = V2::new(0., Keyboard::height() + y_padding);

        let mut all = Vec::new();
        for (i, kb_spec) in spec.keyboards.iter().enumerate() {
            let mut pos = col_positions
                .get_mut(i % (num_cols as usize))
                .expect("bug in CheatSheet::new()");

            if let Some(kb_spec) = kb_spec {
                let mut keyboard = Keyboard::new(*pos);
                keyboard
                    .set(&kb_spec.chord_names, data, &spec.mode)
                    .context(format!(
                        "Failed to create image of keyboard #{}",
                        i
                    ))?;

                all.push(keyboard);
            }
            // Otherwise, the config told us to just leave a blank space where
            // this keyboard would be.

            *pos = *pos + height;
        }
        Ok(Self {
            keyboards: all,
            page_width: spec.page_width,
            page_height: spec.page_height,
            default_svg_filename,
        })
    }

    fn config_path_to_svg_path(
        config_path: &PathBuf,
    ) -> Result<PathBuf, Error> {
        Ok(config_path
            .with_extension("svg")
            .file_name()
            .ok_or_else(|| format_err!("Failed to construct svg filename"))?
            .into())
    }

    fn render(&self) -> Document {
        // TODO add metadata
        let mut group = Group::new();

        for kb in &self.keyboards {
            kb.add_to(&mut group);
        }

        let mut defs = Definitions::new();

        let background = MyRect::new(
            P2::origin(),
            V2::new(self.page_width, self.page_height),
        );
        FillPattern::add_all_definitions(background, &mut defs);
        Switch::add_clip_definition(&mut defs);

        let desc = MyDescription::new(
            "Cheatsheet reference for a layout of a pipit keyboard. \
             https://github.com/e-matteson/pipit-keyboard",
        ).finalize();

        let mut doc = Document::new()
            .set("viewBox", (0, 0, self.page_width, self.page_height));

        doc.append(desc);
        doc.append(defs);
        doc.append(group);
        doc
    }

    pub fn save(&self, filename: Option<&str>) -> Result<(), Error> {
        let path = if let Some(s) = filename {
            PathBuf::from(s)
        } else {
            self.default_svg_filename.clone()
        };

        // Using extra brackets because non-lexical lifetimes aren't in stable
        // yet, and it doesn't know to stop borrowing `path` after creating
        // `path_str`.
        {
            let path_str = path
                .to_str()
                .to_owned()
                .ok_or_else(|| format_err!("Invalid path: {:?}", path))?;

            if path.exists() {
                let confirmed = user_confirm(
                &format!(
                    "The file '{}' already exists, do you want to overwrite it?",
                    path_str),
                ConfirmDefault::No,
            )?;
                if !confirmed {
                    println!("Cheatsheet not saved.");
                    return Ok(());
                }
            }

            println!("Saving cheatsheet as '{}'.", path_str);
        }
        let doc = self.render();
        svg::save(path, &doc).context("Failed to save cheatsheet")?;
        Ok(())
    }
}
