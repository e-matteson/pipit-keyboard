use std::collections::HashMap;
use std::path::PathBuf;

use svg;
use svg::node::element::{ClipPath, Definitions, Group};
use svg::Document;
use svg::Node;

use serde_yaml;
use unicode_segmentation::UnicodeSegmentation;

use failure::{err_msg, Error, ResultExt};
use types::errors::{LookupErr, MissingErr};
use types::{Chord, ModeName, Name, TutorData};
use util::{read_file, user_confirm, ConfirmDefault};

use cheatsheet::draw::{
    Color, Fill, FillPattern, Font, Label, MyCircle, MyDescription, MyRect, P2,
    V2, Wedge,
};

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

#[derive(Clone, Debug)]
struct Keyboard {
    switches: Vec<Switch>,
}

#[derive(Clone, Debug, Deserialize)]
pub struct KeyboardSpec {
    chord_names: Vec<Name>,
    // TODO add title?
}

#[derive(Clone, Copy, Debug)]
#[allow(dead_code)]
pub enum SwitchStyle {
    Blank,
    Single,
    // TODO rename shared
    Shared0,
    Shared1,
    Shared2,
    Shared3,
    Shared4,
    Shared5,
    Shared6,
    Shared7,
    Shared8,
    Shared9,
    Shared10,
    Shared11,
}

#[derive(Clone, Debug)]
struct Content {
    symbol: Symbol,
    style: SwitchStyle,
}

#[derive(Clone, Debug)]
struct Symbol {
    lines: Vec<String>,
    scale: f64,
}

#[derive(Clone, Debug)]
struct Switch {
    pos: P2,
    contents: Vec<Content>,
}

////////////////////////////////////////////////////////////////////////////////

impl CheatSheet {
    pub fn from_yaml(
        path: &PathBuf,
        data: &TutorData,
    ) -> Result<CheatSheet, Error> {
        let file = read_file(path).with_context(|_| {
            format!("failed to read cheatsheet config file: {:?}", path)
        })?;
        let spec: CheatSheetSpec = serde_yaml::from_str(&file).with_context(
            |_| format!("failed to parse cheatsheet config file: {:?}", path),
        )?;
        CheatSheet::new(spec, data, CheatSheet::config_path_to_svg_path(path)?)
    }

    pub fn new(
        spec: CheatSheetSpec,
        data: &TutorData,
        default_svg_filename: PathBuf,
    ) -> Result<CheatSheet, Error> {
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
            })
            .collect();

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
        Ok(CheatSheet {
            keyboards: all,
            page_width: spec.page_width,
            page_height: spec.page_height,
            default_svg_filename: default_svg_filename,
        })
    }

    fn config_path_to_svg_path(
        config_path: &PathBuf,
    ) -> Result<PathBuf, Error> {
        Ok(config_path
            .with_extension("svg")
            .file_name()
            .ok_or(format_err!("Failed to construct svg filename"))?
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
            let path_str = path.to_str()
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
        Ok(svg::save(path, &doc).context("Failed to save cheatsheet")?)
    }
}

impl Keyboard {
    fn new(pos: P2) -> Keyboard {
        Keyboard {
            switches: Keyboard::positions(pos)
                .into_iter()
                .map(|pos| Switch::new(pos))
                .collect(),
        }
    }

    fn set(
        &mut self,
        chord_names: &[Name],
        data: &TutorData,
        mode: &ModeName,
    ) -> Result<(), Error> {
        assert_eq!(Chord::static_length(), self.switches.len());
        let chords = chord_names
            .iter()
            .map(|name| {
                data.chord(name, mode).ok_or_else(|| LookupErr {
                    key: name.into(),
                    container: "tutor data chords".into(),
                })
            })
            .collect::<Result<Vec<_>, _>>()?;

        let symbols: Result<Vec<_>, Error> =
            chord_names.iter().map(|name| get_symbol(name)).collect();
        let symbols = symbols?;

        let mut chord_style_iter = SwitchStyle::chord_style_iter();

        for (chord, symbol) in chords.into_iter().zip(symbols.into_iter()) {
            let style = if chord.count_pressed() != 1 {
                // Usually this means there's a multi-switch chord.
                // We should also consume a chord style if 0 switches are
                // pressed, meaning this is a blank chord named "", used for
                // skipping colors.
                chord_style_iter.next().ok_or_else(|| {
                    err_msg("ran out of unique switch fill styles")
                })?
            } else {
                SwitchStyle::Single
            };

            let content = Content {
                symbol: symbol.clone(),
                style: style,
            };
            for (index, &bit) in chord.iter().enumerate() {
                if bit {
                    self.switches[index].push_content(content.clone());
                }
            }
        }
        Ok(())
    }

    fn add_to(&self, group: &mut Group) {
        let mut frame_group = Group::new();
        for switch in &self.switches {
            switch.add_frame_to(
                &mut frame_group,
                Color::Black,
                Keyboard::outer_frame_scale(),
            );
        }
        for switch in &self.switches {
            switch.add_frame_to(
                &mut frame_group,
                Color::White,
                Keyboard::inner_frame_scale(),
            );
        }
        group.append(frame_group);
        for switch in &self.switches {
            switch.add_to(group);
        }
    }

    fn outer_frame_scale() -> f64 {
        1.6
    }

    fn inner_frame_scale() -> f64 {
        1.57
    }

    fn height() -> f64 {
        // TODO this could fail if the switch alignment changes! Those 2
        // switches won't always be highest and lowest.
        let positions = Keyboard::positions(P2::origin());
        let err_msg = "failed to calc keyboard height";
        let highest = 2;
        let lowest = 20;
        let height = positions.get(lowest).expect(err_msg).y
            - positions.get(highest).expect(err_msg).y
            + Switch::side_length() * Keyboard::outer_frame_scale();
        height * 1.1
    }

    fn width() -> f64 {
        // TODO this could fail if the switch alignment changes! Those 2
        // switches won't always be highest and lowest.
        let positions = Keyboard::positions(P2::origin());
        let err_msg = "failed to calc keyboard width";
        let highest = 7;
        let lowest = 0;
        let width = positions.get(highest).expect(err_msg).x
            - positions.get(lowest).expect(err_msg).x
            + Switch::side_length();
        width * 1.1
    }

    fn positions(origin: P2) -> Vec<P2> {
        // Order must match tutor's graphical switch order, since we're using
        // the same chord lookup.
        let len = Switch::side_length();
        let y_pinky = len * 0.75;
        let y_ring = len * 0.25;
        let x_col = len * 1.1;
        let y_col = len * 1.1;
        let y_tower = len * 1.2;
        let thumb_from_tower = (len * 1.2, len * 0.5);
        let x_thumb = x_col;
        let y_thumb_medial = len * 0.;
        let y_thumb_radial = len * 0.5;
        let x_col_hand_gap = len * 2.7;

        let frame_width =
            (Keyboard::outer_frame_scale() - 1.) * Switch::side_length() / 2.;
        let frame = V2::new(frame_width, frame_width);

        let offset =
            |positions: &mut Vec<P2>, index: usize, offset: (f64, f64)| {
                let new_pos = positions[index] + offset;
                positions.push(new_pos)
            };

        let mut p = Vec::new();

        // top left row
        p.push(origin + (0., y_pinky) + frame); // 0
        p.push(origin + (x_col, y_ring) + frame); // 1
        p.push(origin + (x_col * 2., 0.) + frame); // 2
        offset(&mut p, 2, (x_col, 0.)); // 3

        let reflect = |positions: &mut Vec<P2>, index: usize| {
            let x_mirror = positions[3].x + len / 2. + x_col_hand_gap;
            let old_pos = positions[index];
            let new_x = x_mirror + (x_mirror - old_pos.x);
            positions.push(P2::new(new_x, old_pos.y))
        };

        // top right row
        for i in (0..4).rev() {
            reflect(&mut p, i); // 4-7
        }

        // bottom left row
        offset(&mut p, 0, (0., y_col)); // 8
        offset(&mut p, 1, (0., y_col)); // 9
        offset(&mut p, 2, (0., y_col)); // 10
        offset(&mut p, 3, (0., y_col)); // 11

        // bottom right row
        for i in (8..12).rev() {
            reflect(&mut p, i); // 12-15
        }

        // left and right towers
        offset(&mut p, 10, (0., y_tower)); // 16
        reflect(&mut p, 16); // 17

        // left thumb
        offset(&mut p, 16, thumb_from_tower); // 18
        offset(&mut p, 18, (x_thumb, y_thumb_medial)); // 19
        offset(&mut p, 19, (x_thumb, y_thumb_radial)); // 20

        // right thumb
        for i in (18..21).rev() {
            reflect(&mut p, i); // 21-23
        }
        p
    }
}

impl Switch {
    fn new(pos: P2) -> Switch {
        Switch {
            pos: pos,
            contents: Vec::new(),
        }
    }

    fn push_content(&mut self, content: Content) {
        self.contents.push(content);
    }

    fn side_length() -> f64 {
        25.
    }
    fn clip_id() -> String {
        "ClipSwitch".into()
    }

    fn size() -> V2 {
        let len = Switch::side_length();
        V2::new(len, len)
    }

    fn font_size(&self) -> f64 {
        Switch::side_length() * 3. / 5.
    }

    fn outline(pos: P2) -> MyRect {
        MyRect::new(P2::new(pos.x, pos.y), Switch::size())
            .stroke(Color::Black, 1.)
            .fillet(5.)
    }

    fn add_clip_definition(defs: &mut Definitions) {
        let clip = Switch::outline(P2::origin()).finalize();
        let clip_path = ClipPath::new().set("id", Switch::clip_id()).add(clip);
        defs.append(clip_path);
    }

    fn radius(&self) -> f64 {
        Switch::side_length() / 2. * 2_f64.sqrt()
    }

    // fn center(&self) -> P2 {
    //     let half = Self::side_length() / 2.;
    //     P2::new(self.pos.x + half, self.pos.y + half)
    // }

    fn relative_center(&self) -> P2 {
        let half_len = Switch::side_length() / 2.;
        P2::new(half_len, half_len)
    }

    fn add_blank_switch(group: &mut Group) {
        let rect = Switch::outline(P2::origin())
            .fill(SwitchStyle::Blank.fill())
            .finalize();
        group.append(rect);
    }

    fn add_chord_pie(&self, num_wedges: usize, group: &mut Group) {
        for (i, content) in self.contents.iter().enumerate() {
            let wedge = Wedge {
                tip_pos: self.relative_center(),
                radius: self.radius(),
                circle_divisions: num_wedges,
                division_num: i,
            };
            group.append(wedge.finalize(content.style.fill()));
            if num_wedges == 2 && content.symbol.is_single_grapheme() {
                group.append(
                    Label {
                        lines: content.symbol.lines.clone(),
                        pos: wedge.label_pos(),
                        size: self.font_size() * content.symbol.scale,
                        color: Color::Black,
                        font: Font::default(),
                    }.finalize(),
                );
            }
        }
        group.append(Switch::outline(P2::origin()).finalize());
    }

    fn add_single_circle(&self, group: &mut Group) {
        let sole_content = &self.contents[0];
        group.append(
            MyCircle::new(self.relative_center(), self.radius())
                .fill(sole_content.style.fill())
                .finalize(),
        );
        group.append(
            Label {
                lines: sole_content.symbol.lines.clone(),
                pos: self.relative_center(),
                size: self.font_size() * sole_content.symbol.scale,
                color: Color::Black,
                font: Font::default(),
            }.finalize(),
        );
        group.append(Switch::outline(P2::origin()).finalize());
    }

    fn clip_and_translate(&self, group: &mut Group) {
        group.assign("clip-path", format!("url(#{})", Switch::clip_id()));
        group.assign(
            "transform",
            format!("translate({},{})", self.pos.x, self.pos.y),
        );
    }

    fn add_frame_to(&self, group: &mut Group, color: Color, scale: f64) {
        let frame_fill = Fill::new_solid(color);
        let frame = Switch::outline(self.pos)
            .fill(frame_fill)
            .reset_stroke()
            .scale(scale)
            .finalize();
        group.append(frame);
    }

    fn add_to(&self, outer_group: &mut Group) {
        let mut inner_group = Group::new();
        let num_wedges = self.contents.len();

        match num_wedges {
            0 => Switch::add_blank_switch(&mut inner_group),
            1 => self.add_single_circle(&mut inner_group),
            _ => self.add_chord_pie(num_wedges, &mut inner_group),
        }
        self.clip_and_translate(&mut inner_group);
        outer_group.append(inner_group);
    }
}

impl SwitchStyle {
    fn chord_style_iter() -> impl Iterator<Item = SwitchStyle> {
        vec![
            SwitchStyle::Shared0,
            SwitchStyle::Shared1,
            SwitchStyle::Shared2,
            SwitchStyle::Shared3,
            SwitchStyle::Shared4,
            SwitchStyle::Shared5,
            SwitchStyle::Shared6,
            SwitchStyle::Shared7,
            SwitchStyle::Shared8,
            SwitchStyle::Shared9,
            SwitchStyle::Shared10,
            SwitchStyle::Shared11,
        ].into_iter()
    }

    pub fn fill(&self) -> Fill {
        match *self {
            SwitchStyle::Blank => Fill::new_solid(Color::LightGrey),
            SwitchStyle::Single => Fill::new_solid(Color::DarkGrey),
            SwitchStyle::Shared0 => Fill::new_solid(Color::Blue),
            SwitchStyle::Shared1 => Fill::new_solid(Color::Red),
            SwitchStyle::Shared2 => Fill::new_solid(Color::Green),
            SwitchStyle::Shared3 => Fill::new_solid(Color::Magenta),
            SwitchStyle::Shared4 => Fill::new_solid(Color::Yellow),
            SwitchStyle::Shared5 => Fill::new_solid(Color::Cyan),
            SwitchStyle::Shared6 => Fill {
                color: Color::Blue,
                pattern: Some(FillPattern::DiagStripes),
            },
            SwitchStyle::Shared7 => Fill {
                color: Color::Red,
                pattern: Some(FillPattern::DiagStripes),
            },
            SwitchStyle::Shared8 => Fill {
                color: Color::Green,
                pattern: Some(FillPattern::DiagStripes),
            },
            SwitchStyle::Shared9 => Fill {
                color: Color::Magenta,
                pattern: Some(FillPattern::DiagStripes),
            },
            SwitchStyle::Shared10 => Fill {
                color: Color::Yellow,
                pattern: Some(FillPattern::DiagStripes),
            },
            SwitchStyle::Shared11 => Fill {
                color: Color::Cyan,
                pattern: Some(FillPattern::DiagStripes),
            },
        }
    }
}

impl Symbol {
    fn from(line: &str, scale: f64) -> Symbol {
        Symbol::from_lines(&[line], scale)
    }

    fn from_lines(lines: &[&str], scale: f64) -> Symbol {
        Symbol {
            lines: lines.into_iter().map(|s| s.to_string()).collect(),
            scale: scale,
        }
    }

    fn is_single_grapheme(&self) -> bool {
        self.lines.len() == 1 && self.lines[0].graphemes(true).count() == 1
    }
}

fn get_symbol(name: &Name) -> Result<Symbol, Error> {
    lazy_static! {
        static ref SYMBOLS: HashMap<Name, Symbol>  = vec![
            // ("mod_shift".into(), Symbol::from("shift", 0.9)),
            ("mod_shift".into(), Symbol::from("⇧", 1.3)),
            ("mod_ctrl".into(), Symbol::from("ctrl", 0.8)),
            ("mod_alt".into(), Symbol::from("alt", 1.)),
            ("mod_gui".into(), Symbol::from("⌘❖", 0.8)),
            ("mod_anagram_1".into(), Symbol::from_lines(&["ana","gram","1"], 0.5)),
            ("mod_anagram_2".into(), Symbol::from_lines(&["ana", "gram","2"], 0.5)),
            ("mod_capital".into(), Symbol::from_lines(&["cap", "mod"], 0.6)),
            ("mod_nospace".into(), Symbol::from_lines(&["no", "space","mod"], 0.5)),
            ("mod_double".into(), Symbol::from_lines(&["double", "mod"], 0.4)),
            ("mod_shorten".into(), Symbol::from_lines(&["shorten", "mod"], 0.4)),
            ("key_a".into(), Symbol::from("a", 1.)),
            ("key_b".into(), Symbol::from("b", 1.)),
            ("key_c".into(), Symbol::from("c", 1.)),
            ("key_d".into(), Symbol::from("d", 1.)),
            ("key_e".into(), Symbol::from("e", 1.)),
            ("key_f".into(), Symbol::from("f", 1.)),
            ("key_g".into(), Symbol::from("g", 1.)),
            ("key_h".into(), Symbol::from("h", 1.)),
            ("key_i".into(), Symbol::from("i", 1.)),
            ("key_j".into(), Symbol::from("j", 1.)),
            ("key_k".into(), Symbol::from("k", 1.)),
            ("key_l".into(), Symbol::from("l", 1.)),
            ("key_m".into(), Symbol::from("m", 1.)),
            ("key_n".into(), Symbol::from("n", 1.)),
            ("key_o".into(), Symbol::from("o", 1.)),
            ("key_p".into(), Symbol::from("p", 1.)),
            ("key_q".into(), Symbol::from("q", 1.)),
            ("key_r".into(), Symbol::from("r", 1.)),
            ("key_s".into(), Symbol::from("s", 1.)),
            ("key_t".into(), Symbol::from("t", 1.)),
            ("key_u".into(), Symbol::from("u", 1.)),
            ("key_v".into(), Symbol::from("v", 1.)),
            ("key_w".into(), Symbol::from("w", 1.)),
            ("key_x".into(), Symbol::from("x", 1.)),
            ("key_y".into(), Symbol::from("y", 1.)),
            ("key_z".into(), Symbol::from("z", 1.)),
            ("key_0".into(), Symbol::from("0", 1.)),
            ("key_1".into(), Symbol::from("1", 1.)),
            ("key_2".into(), Symbol::from("2", 1.)),
            ("key_3".into(), Symbol::from("3", 1.)),
            ("key_4".into(), Symbol::from("4", 1.)),
            ("key_5".into(), Symbol::from("5", 1.)),
            ("key_6".into(), Symbol::from("6", 1.)),
            ("key_7".into(), Symbol::from("7", 1.)),
            ("key_8".into(), Symbol::from("8", 1.)),
            ("key_9".into(), Symbol::from("9", 1.)),
            // ("key_enter".into(), Symbol::from("enter", 0.6)),
            ("key_enter".into(), Symbol::from("⏎", 1.3)),
            ("key_left".into(), Symbol::from("←", 1.2)),
            ("key_right".into(), Symbol::from("→", 1.2)),
            ("key_up".into(), Symbol::from("↑", 1.2)),
            ("key_down".into(), Symbol::from("↓", 1.2)),
            // ("key_backspace".into(), Symbol::from_lines(&["back","space"], 0.5)),
            ("key_backspace".into(), Symbol::from("⌫", 1.)),
            // ("key_space".into(), Symbol::from("space", 0.6)),
            ("key_space".into(), Symbol::from("␣", 1.2)),
            ("key_backslash".into(), Symbol::from("\\", 1.)),
            ("key_right_paren".into(), Symbol::from(")", 1.)),
            ("key_right_curly".into(), Symbol::from("}", 1.)),
            ("key_right_brace".into(), Symbol::from("]", 1.)),
            ("key_right_angle".into(), Symbol::from("ᐳ", 0.8)),
            ("key_left_paren".into(), Symbol::from("(", 1.)),
            ("key_left_curly".into(), Symbol::from("{", 1.)),
            ("key_left_brace".into(), Symbol::from("[", 1.)),
            ("key_left_angle".into(), Symbol::from("ᐸ", 0.8)),
            ("key_f1".into(), Symbol::from("f1", 1.)),
            ("key_f2".into(), Symbol::from("f2", 1.)),
            ("key_f3".into(), Symbol::from("f3", 1.)),
            ("key_f4".into(), Symbol::from("f4", 1.)),
            ("key_f5".into(), Symbol::from("f5", 1.)),
            ("key_f6".into(), Symbol::from("f6", 1.)),
            ("key_f7".into(), Symbol::from("f7", 1.)),
            ("key_f8".into(), Symbol::from("f8", 1.)),
            ("key_f9".into(), Symbol::from("f9", 1.)),
            ("key_tab".into(), Symbol::from("tab", 0.7)),
            ("key_esc".into(), Symbol::from("esc", 0.7)),
            ("key_caps_lock".into(), Symbol::from_lines(&["caps","lock"], 0.6)),
            ("key_home".into(), Symbol::from("home", 0.5)),
            ("key_end".into(), Symbol::from("end", 0.7)),
            ("key_page_up".into(), Symbol::from_lines(&["pg", "up"], 0.8)),
            ("key_page_down".into(), Symbol::from_lines(&["pg", "dn"], 0.8)),
            ("key_printscreen".into(), Symbol::from_lines(&["print", "scrn"], 0.5)),
            ("key_delete".into(), Symbol::from("del", 0.9)),
            ("key_ampersand".into(), Symbol::from("&amp;", 1.)),
            ("key_asterisk".into(), Symbol::from("*", 1.2)),
            ("key_at".into(), Symbol::from("@", 1.)),
            ("key_backslash".into(), Symbol::from("\\", 1.)),
            ("key_bang".into(), Symbol::from("!", 1.)),
            ("key_caret".into(), Symbol::from("^", 1.2)),
            ("key_colon".into(), Symbol::from(":", 1.)),
            ("key_comma".into(), Symbol::from(",", 1.3)),
            ("key_dollar".into(), Symbol::from("$", 1.)),
            ("key_doublequote".into(), Symbol::from("\"", 1.3)),
            ("key_equal".into(), Symbol::from("=", 1.)),
            ("key_grave".into(), Symbol::from("`", 1.3)),
            ("key_hash".into(), Symbol::from("#", 1.)),
            ("key_minus".into(), Symbol::from("-", 1.2)),
            ("key_percent".into(), Symbol::from("%", 1.)),
            ("key_period".into(), Symbol::from(".", 1.3)),
            ("key_pipe".into(), Symbol::from("|", 1.)),
            ("key_plus".into(), Symbol::from("+", 1.)),
            ("key_question".into(), Symbol::from("?", 1.)),
            ("key_quote".into(), Symbol::from("'", 1.3)),
            ("key_semicolon".into(), Symbol::from(";", 1.)),
            ("key_slash".into(), Symbol::from("/", 1.)),
            ("key_tilde".into(), Symbol::from("~", 1.3)),
            ("key_underscore".into(), Symbol::from("_", 1.2)),
            ("command_pause".into(), Symbol::from("pause", 0.4)),
            ("command_delete_word".into(), Symbol::from_lines(&["del", "word"], 0.5)),
            ("command_cycle_word".into(), Symbol::from_lines(&["cycle", "word"], 0.5)),
            ("command_cycle_capital".into(), Symbol::from_lines(&["cycle", "cap"], 0.5)),
            ("command_cycle_nospace".into(), Symbol::from_lines(&["cycle", "space"], 0.5)),
            ("command_left_word".into(), Symbol::from_lines(&["left", "word"], 0.5)),
            ("command_right_word".into(), Symbol::from_lines(&["right", "word"], 0.5)),
            ("command_right_limit".into(), Symbol::from_lines(&["right", "limit"], 0.5)),
            ("command_gaming_mode".into(), Symbol::from_lines(&["game", "mode"], 0.4)),
            ("command_left_hand_mode".into(), Symbol::from_lines(&["left","hand", "mode"], 0.4)),
            ("macro_in_paren".into(), Symbol::from("(|)", 1.)),
            ("macro_in_curly".into(), Symbol::from("{|}", 1.)),
            ("macro_in_brace".into(), Symbol::from("[|]", 1.)),
            ("macro_in_angle".into(), Symbol::from("ᐸ|ᐳ", 0.8)),
            ("".into(), Symbol::from("", 1.)), // used for skipping colors without displaying anything
        ].into_iter().collect();
    }
    Ok(SYMBOLS
        .get(name)
        .ok_or_else(|| MissingErr {
            missing: name.into(),
            container: "cheatsheet symbol lookup".into(),
        })?
        .to_owned())
}
