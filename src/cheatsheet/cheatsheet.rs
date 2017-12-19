use std::collections::HashMap;
use std::f64::consts::PI;
use std::io::prelude::*;
use std::fs::File;

use svg;
use svg::Document;
use svg::Node;
use svg::node::element::{ClipPath, Definitions, Group, Path};
use svg::node::element::path::Data;

use toml;

use tutor::TutorData;
use types::{Chord, Name};
use types::errors::*;
use cheatsheet::draw::{Color, Fill, FillPattern, Font, Label, MyCircle,
                       MyRect, P2, V2};


#[derive(Clone, Debug)]
pub struct CheatSheet {
    keyboards: Vec<Keyboard>,
}

#[derive(Clone, Debug, Deserialize)]
pub struct CheatSheetSpec {
    keyboards: Vec<KeyboardSpec>,
    // TODO add title?
}

#[derive(Clone, Debug)]
struct Keyboard {
    switches: Vec<Switch>,
}

#[derive(Clone, Debug, Deserialize)]
pub struct KeyboardSpec {
    keys: Vec<Name>,
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
    symbol: String,
    style: SwitchStyle,
}

#[derive(Clone, Debug)]
struct Switch {
    pos: P2,
    contents: Vec<Content>,
}

#[derive(Clone, Debug)]
struct Wedge {
    tip_pos: P2,
    radius: f64,
    circle_divisions: usize,
    division_num: usize,
}
////////////////////////////////////////////////////////////////////////////////

impl CheatSheet {
    pub fn from_toml(path: &str, data: &TutorData) -> CheatSheet {
        let spec: CheatSheetSpec = toml::from_str(
            &read_file(path).expect("failed to read"),
        ).expect("failed to parse");
        CheatSheet::new(spec, data)
    }

    pub fn new(spec: CheatSheetSpec, data: &TutorData) -> CheatSheet {
        // TODO make spacing even, make page breaks?
        let mut col_1_pos = P2::new(10., 10.);
        let mut col_2_pos = col_1_pos + V2::new(Keyboard::width(), 0.);
        let height = V2::new(0., Keyboard::height());
        let mut all = Vec::new();
        for (i, kb_spec) in spec.keyboards.iter().enumerate() {
            let mut pos = if i % 2 == 0 {
                &mut col_1_pos
            } else {
                &mut col_2_pos
            };
            let mut keyboard = Keyboard::new(*pos);
            keyboard.set_keys(&kb_spec.keys, data);
            all.push(keyboard);
            *pos = *pos + height;
        }
        CheatSheet { keyboards: all }
    }

    pub fn save(&self, filename: &str) {
        // TODO add metadata
        let page_width = Keyboard::width() * 2.;
        let page_height = Keyboard::height() * 7.;

        let mut group = Group::new();

        for kb in &self.keyboards {
            kb.add_to(&mut group);
        }

        let mut defs = Definitions::new();
        // let background = Rectangle::new()
        //     .set("x", 0)
        //     .set("y", 0)
        //     .set("width", page_width)
        //     .set("height", page_height);
        let background =
            MyRect::new(P2::origin(), V2::new(page_width, page_height));
        FillPattern::add_all_definitions(background, &mut defs);
        Switch::add_clip_definition(&mut defs);

        let mut doc =
            Document::new().set("viewBox", (0, 0, page_width, page_height));
        doc.append(defs);
        doc.append(group);
        svg::save(filename, &doc).unwrap();
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

    fn set_keys(&mut self, keys: &[Name], data: &TutorData) {
        assert_eq!(Chord::chord_length(), self.switches.len());
        let chords: Vec<_> = keys.iter()
            .map(|key| data.get_chord(key).expect("chord not found"))
            .collect();

        let symbols: Vec<_> = keys.iter().map(|key| get_symbol(key)).collect();

        let mut chord_style_iter = SwitchStyle::chord_style_iter();

        for (chord, symbol) in chords.into_iter().zip(symbols.into_iter()) {
            let style = if chord.count_switches() > 1 {
                chord_style_iter
                    .next()
                    .expect("ran out of unique switch fill styles")
            } else {
                SwitchStyle::Single
            };

            let content = Content {
                symbol: symbol.clone(),
                style: style,
            };
            for (index, &bit) in chord.iter().enumerate() {
                if bit {
                    self.switches[index].add_content(content.clone());
                }
            }
        }
    }

    fn add_to(&self, group: &mut Group) {
        for switch in &self.switches {
            switch.add_to(group);
        }
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
            + Switch::side_length();
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
        width * 1.05
    }

    fn positions(origin: P2) -> Vec<P2> {
        // Order must match tutor's graphical switch order, since we're using
        // the same chord lookup.
        let len = Switch::side_length();
        let y_pinky = len * 0.75;
        let y_ring = len * 0.25;
        let x_col = len * 1.25;
        let y_col = len * 1.2;
        let y_tower = len * 1.3;
        let thumb_from_tower = (len * 1.5, len * 0.5);
        let x_thumb = x_col;
        let y_thumb_medial = len * 0.;
        let y_thumb_radial = len * 0.5;
        let x_col_hand_gap = len * 3.;

        let offset =
            |positions: &mut Vec<P2>, index: usize, offset: (f64, f64)| {
                let new_pos = positions[index] + offset;
                positions.push(new_pos)
            };

        let mut p = Vec::new();

        // top left row
        p.push(origin + (0., y_pinky)); // 0
        p.push(origin + (x_col, y_ring)); // 1
        p.push(origin + (x_col * 2., 0.)); // 2
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

    fn add_content(&mut self, content: Content) {
        self.contents.push(content);
    }

    fn side_length() -> f64 {
        // 50.
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
        // 15.
        Switch::side_length() * 3. / 5.
    }

    // fn center(&self) -> P2 {
    //     let half = Self::side_length() / 2.;
    //     P2::new(self.pos.x + half, self.pos.y + half)
    // }

    // fn sole_content(&self) -> Option<Content> {
    //     if self.contents.len() == 1 {
    //         self.contents.get(0).cloned()
    //     } else {
    //         None
    //     }
    // }

    fn outline(pos: P2) -> MyRect {
        MyRect::new(P2::new(pos.x, pos.y), Switch::size())
            .stroke(Color::Black, 1.)
            .fillet(5.)
    }

    fn add_clip_definition(defs: &mut Definitions) {
        let clip = Switch::outline(P2::origin()).finalize();
        let clip_path = ClipPath::new()
            .set("id", Switch::clip_id())
        // .set("clipPathUnits", "objectBoundingBox")
            .add(clip);
        defs.append(clip_path);
    }

    fn radius(&self) -> f64 {
        Switch::side_length() / 2. * 2_f64.sqrt()
    }

    fn relative_center(&self) -> P2 {
        let half_len = Switch::side_length() / 2.;
        P2::new(half_len, half_len)
    }

    fn add_blank_switch(group: &mut Group) {
        let rect = Switch::outline(P2::origin())
            .fill(SwitchStyle::Blank.fill())
            .finalize();
        // SwitchStyle::Blank.fill().assign_to(&mut rect);
        group.append(rect);
    }

    fn add_chord_pie(&self, num_wedges: usize, group: &mut Group) {
        for (i, content) in self.contents.iter().enumerate() {
            group.append(
                Wedge {
                    tip_pos: self.relative_center(),
                    radius: self.radius(),
                    circle_divisions: num_wedges,
                    division_num: i,
                }.finalize(content.style.fill()),
            );
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
                string: sole_content.symbol.clone(),
                pos: self.relative_center(),
                size: self.font_size(),
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

    fn add_to(&self, outer_group: &mut Group) {
        let mut inner_group = Group::new();
        let num_wedges = self.contents.len();

        if num_wedges == 0 {
            Switch::add_blank_switch(&mut inner_group);
        } else if num_wedges == 1 {
            self.add_single_circle(&mut inner_group);
        } else {
            self.add_chord_pie(num_wedges, &mut inner_group);
        }
        self.clip_and_translate(&mut inner_group);
        outer_group.append(inner_group);
    }
}

impl Wedge {
    fn arc_start(&self) -> P2 {
        self.tip_pos
            + polar_vec(self.radius, self.rotation_radians()).reflect_xy()
    }

    fn arc_end(&self) -> P2 {
        self.tip_pos
            + polar_vec(
                self.radius,
                self.rotation_radians() + self.width_radians(),
            ).reflect_xy()
    }

    fn rotation_radians(&self) -> f64 {
        self.width_radians() * (self.division_num as f64)
    }

    fn width_radians(&self) -> f64 {
        PI * 2. / (self.circle_divisions as f64)
    }

    fn is_large_arc(&self) -> bool {
        self.width_radians() > PI
    }

    fn finalize(&self, fill: Fill) -> Path {
        let mut path = Path::new().set("d", self.to_data());
        fill.assign_to(&mut path);
        path
    }

    fn to_data(&self) -> Data {
        Data::new()
            .move_to(self.tip_pos)
            .line_to(self.arc_start())
            .elliptical_arc_to(
                ArcArgs {
                    radius: P2::new(self.radius, self.radius),
                    x_axis_rotation: 0.,
                    large_arc_flag: self.is_large_arc(),
                    sweep_flag: false,
                    end: self.arc_end(),
                }.finalize(),
            )
            .close()
    }

    // fn debug(&self) -> Group {
    //     Group::new()
    //         .add(mark(self.arc_start()))
    //         .add(mark(self.arc_end()))
    //         .add(mark(self.tip_pos))
    // }
}

// fn mark(pos: P2) -> Circle {
//     Circle::new()
//         .set("cx", pos.x)
//         .set("cy", pos.y)
//         .set("fill", Color::Red)
//         .set("r", 5)
// }

struct ArcArgs {
    radius: P2,
    x_axis_rotation: f64,
    large_arc_flag: bool,
    sweep_flag: bool,
    end: P2,
}

impl ArcArgs {
    fn finalize(&self) -> (f64, f64, f64, f64, f64, f64, f64) {
        (
            self.radius.x,
            self.radius.y,
            self.x_axis_rotation,
            if self.large_arc_flag { 1. } else { 0. },
            if self.sweep_flag { 1. } else { 0. },
            self.end.x,
            self.end.y,
        )
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
            SwitchStyle::Shared0 => Fill::new_solid(Color::Red),
            SwitchStyle::Shared1 => Fill::new_solid(Color::Yellow),
            SwitchStyle::Shared2 => Fill::new_solid(Color::Green),
            SwitchStyle::Shared3 => Fill::new_solid(Color::Cyan),
            SwitchStyle::Shared4 => Fill::new_solid(Color::Blue),
            SwitchStyle::Shared5 => Fill::new_solid(Color::Magenta),
            SwitchStyle::Shared6 => Fill {
                color: Color::Red,
                pattern: Some(FillPattern::Checkers),
            },
            SwitchStyle::Shared7 => Fill {
                color: Color::Yellow,
                pattern: Some(FillPattern::Checkers),
            },
            SwitchStyle::Shared8 => Fill {
                color: Color::Green,
                pattern: Some(FillPattern::Checkers),
            },
            SwitchStyle::Shared9 => Fill {
                color: Color::Cyan,
                pattern: Some(FillPattern::Checkers),
            },
            SwitchStyle::Shared10 => Fill {
                color: Color::Blue,
                pattern: Some(FillPattern::Checkers),
            },
            SwitchStyle::Shared11 => Fill {
                color: Color::Magenta,
                pattern: Some(FillPattern::Checkers),
            },
        }
    }
}


fn polar_vec(radius: f64, radians: f64) -> V2 {
    let x = radians.cos() * radius;
    let y = radians.sin() * radius;
    V2::new(x, y)
}


fn get_symbol(key: &Name) -> String {
    // TODO share with tutor?
    lazy_static! {
        static ref SYMBOLS: HashMap<Name, String>  = vec![
            // ("mod_shift".into(), "⇧".into()),
            ("mod_shift".into(), "shift".into()),
            ("mod_ctrl".into(), "ctrl".into()),
            ("mod_alt".into(), "alt".into()),
            ("mod_gui".into(), "⌘❖".into()),
            ("mod_anagram_1".into(), "a1".into()),
            ("mod_anagram_2".into(), "a2".into()),
            ("mod_capital".into(), "cap".into()),
            ("mod_nospace".into(), "NoSpc".into()),
            ("mod_double".into(), "double".into()),
            ("key_a".into(), "a".into()),
            ("key_b".into(), "b".into()),
            ("key_c".into(), "c".into()),
            ("key_d".into(), "d".into()),
            ("key_e".into(), "e".into()),
            ("key_f".into(), "f".into()),
            ("key_g".into(), "g".into()),
            ("key_h".into(), "h".into()),
            ("key_i".into(), "i".into()),
            ("key_j".into(), "j".into()),
            ("key_k".into(), "k".into()),
            ("key_l".into(), "l".into()),
            ("key_m".into(), "m".into()),
            ("key_n".into(), "n".into()),
            ("key_o".into(), "o".into()),
            ("key_p".into(), "p".into()),
            ("key_q".into(), "q".into()),
            ("key_r".into(), "r".into()),
            ("key_s".into(), "s".into()),
            ("key_t".into(), "t".into()),
            ("key_u".into(), "u".into()),
            ("key_v".into(), "v".into()),
            ("key_w".into(), "w".into()),
            ("key_x".into(), "x".into()),
            ("key_y".into(), "y".into()),
            ("key_z".into(), "z".into()),
            ("key_0".into(), "0".into()),
            ("key_1".into(), "1".into()),
            ("key_2".into(), "2".into()),
            ("key_3".into(), "3".into()),
            ("key_4".into(), "4".into()),
            ("key_5".into(), "5".into()),
            ("key_6".into(), "6".into()),
            ("key_7".into(), "7".into()),
            ("key_8".into(), "8".into()),
            ("key_9".into(), "9".into()),
            // ("key_enter".into(), "⏎".into()),
            ("key_enter".into(), "enter".into()),
            ("key_left".into(), "←".into()),
            ("key_right".into(), "→".into()),
            ("key_up".into(), "↑".into()),
            ("key_down".into(), "↓".into()),
            // ("key_backspace".into(), "⌫".into()),
            ("key_backspace".into(), "bak".into()),
            // ("key_space".into(), "␣".into()),
            ("key_space".into(), "spc".into()),
            ("key_backslash".into(), "\\".into()),
            ("key_right_paren".into(), ")".into()),
            ("key_right_angle".into(), "&gt;".into()), // TODO scale as if len==1
            ("key_right_curly".into(), "}".into()),
            ("key_right_brace".into(), "]".into()),
            ("key_left_paren".into(), "(".into()),
            ("key_left_angle".into(), "&lt;".into()), // TODO scale as if len==1
            ("key_left_curly".into(), "{".into()),
            ("key_left_brace".into(), "[".into()),
            ("key_f1".into(), "f1".into()),
            ("key_f2".into(), "f2".into()),
            ("key_f3".into(), "f3".into()),
            ("key_f4".into(), "f4".into()),
            ("key_f5".into(), "f5".into()),
            ("key_f6".into(), "f6".into()),
            ("key_f7".into(), "f7".into()),
            ("key_f8".into(), "f8".into()),
            ("key_f9".into(), "f9".into()),
            ("key_tab".into(), "tab".into()),
            ("key_esc".into(), "esc".into()),
            ("key_caps_lock".into(), "caplock".into()),
            ("key_home".into(), "home".into()),
            ("key_end".into(), "end".into()),
            ("key_page_up".into(), "PgUp".into()),
            ("key_page_down".into(), "PgDn".into()),
            ("key_printscreen".into(), "print".into()),
            ("key_delete".into(), "del".into()),
            ("key_ampersand".into(), "&amp;".into()),
            ("key_asterisk".into(), "*".into()),
            ("key_at".into(), "@".into()),
            ("key_backslash".into(), "\\".into()),
            ("key_bang".into(), "!".into()),
            ("key_caret".into(), "^".into()),
            ("key_colon".into(), ":".into()),
            ("key_comma".into(), ",".into()),
            ("key_dollar".into(), "$".into()),
            ("key_doublequote".into(), "\"".into()),
            ("key_equal".into(), "=".into()),
            ("key_grave".into(), "`".into()),
            ("key_hash".into(), "#".into()),
            ("key_minus".into(), "-".into()),
            ("key_percent".into(), "%".into()),
            ("key_period".into(), ".".into()),
            ("key_pipe".into(), "|".into()),
            ("key_plus".into(), "+".into()),
            ("key_question".into(), "?".into()),
            ("key_quote".into(), "'".into()),
            ("key_semicolon".into(), ";".into()),
            ("key_slash".into(), "/".into()),
            ("key_tilde".into(), "~".into()),
            ("key_underscore".into(), "_".into()),
            ("command_pause".into(), "pause".into()),
            ("command_delete_word".into(), "DelWord".into()),
            ("command_cycle_word".into(), "CycleWord".into()),
            ("command_gaming_mode".into(), "GameMode".into()),
            ("command_left_hand_mode".into(), "LeftHandMode".into()),
            ("macro_in_paren".into(), "()".into()),
            ("macro_in_curly".into(), "{}".into()),
            ("macro_in_brace".into(), "[]".into()),
            ("macro_in_angle".into(), "&lt;&gt;".into()),

        ].into_iter().collect();
    }
    SYMBOLS.get(key).expect("no symbol for key").to_owned()
}

fn read_file(path: &str) -> Result<String> {
    let mut f: File = File::open(path)?;
    let mut buffer = String::new();
    f.read_to_string(&mut buffer)?;
    Ok(buffer)
}
