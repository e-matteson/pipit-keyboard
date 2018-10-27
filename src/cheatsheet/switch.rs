use std::collections::HashMap;
use svg::node::element::{ClipPath, Definitions, Group};
use svg::Node;
use unicode_segmentation::UnicodeSegmentation;

use cheatsheet::draw::{
    Color, Fill, FillPattern, Font, Label, MyCircle, MyRect, Wedge, P2, V2,
};
use error::Error;
use types::Name;

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
pub struct Content {
    pub symbol: Symbol,
    pub style: SwitchStyle,
}

#[derive(Clone, Debug)]
pub struct Symbol {
    lines: Vec<String>,
    scale: f64,
}

#[derive(Clone, Debug)]
pub struct Switch {
    pos: P2,
    contents: Vec<Content>,
}

impl Switch {
    pub fn new(pos: P2) -> Self {
        Self {
            pos,
            contents: Vec::new(),
        }
    }

    pub fn push_content(&mut self, content: Content) {
        self.contents.push(content);
    }

    pub fn side_length() -> f64 {
        25.
    }
    fn clip_id() -> String {
        "ClipSwitch".into()
    }

    fn size() -> V2 {
        let len = Self::side_length();
        V2::new(len, len)
    }

    fn font_size(&self) -> f64 {
        Self::side_length() * 3. / 5.
    }

    fn outline(pos: P2) -> MyRect {
        MyRect::new(P2::new(pos.x, pos.y), Self::size())
            .stroke(Color::Black, 1.)
            .fillet(5.)
    }

    pub fn add_clip_definition(defs: &mut Definitions) {
        let clip = Self::outline(P2::origin()).finalize();
        let clip_path = ClipPath::new().set("id", Self::clip_id()).add(clip);
        defs.append(clip_path);
    }

    fn radius(&self) -> f64 {
        Self::side_length() / 2. * 2_f64.sqrt()
    }

    // fn center(&self) -> P2 {
    //     let half = Self::side_length() / 2.;
    //     P2::new(self.pos.x + half, self.pos.y + half)
    // }

    fn relative_center(&self) -> P2 {
        let half_len = Self::side_length() / 2.;
        P2::new(half_len, half_len)
    }

    fn add_blank_switch(group: &mut Group) {
        let rect = Self::outline(P2::origin())
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
        group.append(Self::outline(P2::origin()).finalize());
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
        group.append(Self::outline(P2::origin()).finalize());
    }

    fn clip_and_translate(&self, group: &mut Group) {
        group.assign("clip-path", format!("url(#{})", Self::clip_id()));
        group.assign(
            "transform",
            format!("translate({},{})", self.pos.x, self.pos.y),
        );
    }

    pub fn add_frame_to(&self, group: &mut Group, color: Color, scale: f64) {
        let frame_fill = Fill::new_solid(color);
        let frame = Self::outline(self.pos)
            .fill(frame_fill)
            .reset_stroke()
            .scale(scale)
            .finalize();
        group.append(frame);
    }

    pub fn add_to(&self, outer_group: &mut Group) {
        let mut inner_group = Group::new();
        let num_wedges = self.contents.len();

        match num_wedges {
            0 => Self::add_blank_switch(&mut inner_group),
            1 => self.add_single_circle(&mut inner_group),
            _ => self.add_chord_pie(num_wedges, &mut inner_group),
        }
        self.clip_and_translate(&mut inner_group);
        outer_group.append(inner_group);
    }
}

impl SwitchStyle {
    pub fn chord_style_iter() -> impl Iterator<Item = SwitchStyle> {
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

    pub fn fill(self) -> Fill {
        match self {
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
    fn from(line: &str, scale: f64) -> Self {
        Self::from_lines(&[line], scale)
    }

    fn from_lines(lines: &[&str], scale: f64) -> Self {
        Self {
            lines: lines.into_iter().map(|s| s.to_string()).collect(),
            scale,
        }
    }

    pub fn from_name(name: &Name) -> Result<Self, Error> {
        get_symbol(name)
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
    // TODO map?
    Ok(SYMBOLS
        .get(name)
        .ok_or_else(|| Error::Missing {
            missing: name.into(),
            container: "cheatsheet symbol lookup".to_owned(),
        })?.to_owned())
}
