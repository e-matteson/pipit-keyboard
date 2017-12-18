use tutor::TutorData;
use types::{Chord, Name};

use std::ops::Add;
use std::collections::HashMap;

use svg;
use svg::Document;
use svg::{node, Node};
use svg::node::Value;
use svg::node::element::{Rectangle, Text};

use unicode_segmentation::UnicodeSegmentation;

#[derive(Clone, Debug)]
pub struct CheatSheet {
    keyboards: Vec<Keyboard>,
}

#[derive(Clone, Debug)]
struct Keyboard {
    switches: Vec<Switch>,
}

#[derive(Clone, Debug)]
struct KeyboardSpec {
    keys: Vec<Name>,
    // TODO add title?
}

#[derive(Clone, Copy, Debug)]
enum DisplayStyle {
    Single, // none shared, all singles with no colors
    Chords,
}

#[derive(Clone, Debug)]
struct Content {
    symbol: String,
    fill: Fill,
}

#[derive(Clone, Debug)]
struct Switch {
    pos: P2,
    contents: Option<Content>,
}

#[derive(Clone, Copy, Debug)]
struct MyRect {
    pos: P2,
    size: V2,
    stroke: Option<Stroke>,
    fill: Option<Fill>,
    fillet: Option<V2>,
}

#[derive(Clone, Debug)]
struct Label {
    string: String,
    pos: P2,
    color: Color,
    size: f64,
    font: Font,
}


#[derive(Clone, Debug)]
struct Font {
    family: String,
    weight: FontWeight,
    style: FontStyle,
    // TODO add font-stretch?
}

#[derive(Clone, Copy, Debug)]
struct Stroke {
    color: Color,
    width: f64,
}

#[derive(Clone, Copy, Debug)]
pub enum Color {
    Red,
    Yellow,
    Green,
    Cyan,
    Blue,
    Magenta,
    Black,
    White,
    LightGrey,
    DarkGrey,
}

// #[derive(Clone, Copy, Debug)]
// pub enum Pattern {
//     Solid,
// }

#[derive(Clone, Copy, Debug)]
pub enum Fill {
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

#[derive(Clone, Copy, Debug)]
pub enum FontStyle {
    Normal,
    Italic,
    Oblique,
}

#[derive(Clone, Copy, Debug)]
pub enum FontWeight {
    Normal,
    Bold,
    Bolder,
    Lighter,
}

#[derive(Clone, Copy, Debug)]
pub enum TextAnchor {
    Start,
    Middle,
    End,
}

#[derive(Clone, Copy, Debug)]
struct P2 {
    x: f64,
    y: f64,
}

#[derive(Clone, Copy, Debug)]
struct V2 {
    x: f64,
    y: f64,
}


////////////////////////////////////////////////////////////////////////////////
impl CheatSheet {
    pub fn new(data: &TutorData) -> CheatSheet {
        let mut keyboard = Keyboard::new(P2::new(10., 10.));
        keyboard.set_keys(
            // &[
            //     "key_b".into(),
            //     "key_w".into(),
            //     "key_k".into(),
            //     "key_j".into(),
            //     "key_1".into(),
            //     "key_0".into(),
            //     // "key_5".into(),
            //     // "key_4".into(),
            //     "key_enter".into(),
            //     // "key_page_down".into(),
            // ],
            &[
                "key_a".into(),
                "key_c".into(),
                "key_d".into(),
                "key_e".into(),
                "key_f".into(),
                "key_h".into(),
                "key_i".into(),
                "key_l".into(),
                "key_m".into(),
                "key_n".into(),
                "key_o".into(),
                "key_p".into(),
                "key_r".into(),
                "key_s".into(),
                "key_t".into(),
                "key_u".into(),
                "key_space".into(),
                "key_backspace".into(),
                "key_up".into(),
                "key_down".into(),
                "mod_shift".into(),
                "mod_ctrl".into(),
                "mod_gui".into(),
                "mod_alt".into(),
                // "key_page_down".into(),
            ],
            data,
        );

        CheatSheet {
            keyboards: vec![keyboard],
        }
    }

    pub fn save(&self, filename: &str) {
        let page_width = 1000;
        let page_height = 300;

        let mut document =
            Document::new().set("viewBox", (0, 0, page_width, page_height));
        for kb in &self.keyboards {
            kb.add_to(&mut document);
        }
        svg::save(filename, &document).unwrap();
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
        // TODO use actual Chords methods: len, iter
        assert_eq!(Chord::chord_length(), self.switches.len());

        let chords: Vec<_> = keys.iter()
            .map(|key| data.get_chord(key).expect("chord not found"))
            .collect();

        let symbols: Vec<_> = keys.iter().map(|key| get_symbol(key)).collect();

        let style = Keyboard::pick_display_style(&chords);
        let mut fills = style.fill_iter();

        for (chord, symbol) in chords.into_iter().zip(symbols.into_iter()) {
            let content = Content {
                symbol: symbol.clone(),
                fill: fills
                    .next()
                    .expect("ran out of unique switch fill styles"),
            };
            for (index, &bit) in chord.iter().enumerate() {
                if bit {
                    self.switches[index].set_content(content.clone());
                }
            }
        }
    }

    fn pick_display_style(chords: &[Chord]) -> DisplayStyle {
        // TODO clean up refs in iterators
        let chord_sizes: Vec<_> =
            chords.iter().map(|c| c.count_switches()).collect();
        let num_singles = chord_sizes.iter().filter(|&&x| x == 1).count();
        let num_multis = chord_sizes.iter().filter(|&&x| x > 1).count();

        // TODO better messages, return Result
        println!("{}, {}", num_singles, num_multis);
        match (num_singles, num_multis) {
            (_, 0) => DisplayStyle::Single,
            (0, _) => DisplayStyle::Chords,
            _ => panic!("can't mix single switch and multi-switch chords"),
        }
    }

    fn add_to(&self, doc: &mut Document) {
        for switch in &self.switches {
            switch.add_to(doc);
        }
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
        let x_col_hand_gap = len * 4.;

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

impl Add<(f64, f64)> for P2 {
    type Output = P2;
    fn add(self, rhs: (f64, f64)) -> P2 {
        P2::new(self.x + rhs.0, self.y + rhs.1)
    }
}

impl Default for Font {
    fn default() -> Font {
        Font {
            family: "sans-serif".into(),
            weight: FontWeight::Normal,
            style: FontStyle::Normal,
        }
    }
}

impl Switch {
    fn new(pos: P2) -> Switch {
        Switch {
            pos: pos,
            contents: None,
        }
    }

    fn set_content(&mut self, symbol: Content) {
        self.contents = Some(symbol);
    }

    fn side_length() -> f64 {
        50.
    }
    fn size() -> V2 {
        let len = Switch::side_length();
        V2::new(len, len)
    }

    fn font_size(&self) -> f64 {
        30.
    }

    fn center(&self) -> P2 {
        let half = Self::side_length() / 2.;
        P2::new(self.pos.x + half, self.pos.y + half)
    }

    fn fill(&self) -> Fill {
        if let Some(ref contents) = self.contents {
            contents.fill
        } else {
            Fill::Blank
        }
    }

    fn add_to(&self, doc: &mut Document) {
        doc.append(
            MyRect::new(self.pos, Switch::size())
                .fill(self.fill())
                .stroke(Color::Black, 3.)
                .fillet(5.)
                .finalize(),
        );

        if let Some(ref content) = self.contents {
            doc.append(
                Label {
                    string: content.symbol.clone(),
                    // pos: self.center() + (0., self.font_size() / 4.),
                    pos: self.center(),
                    size: self.font_size(),
                    color: Color::Black,
                    font: Font::default(),
                }.finalize(),
            );
        }
    }
}


impl Into<Value> for FontStyle {
    fn into(self) -> Value {
        match self {
            FontStyle::Normal => "normal",
            FontStyle::Italic => "italic",
            FontStyle::Oblique => "oblique",
        }.into()
    }
}

impl Into<Value> for FontWeight {
    fn into(self) -> Value {
        match self {
            FontWeight::Normal => "normal",
            FontWeight::Bold => "bold",
            FontWeight::Bolder => "bolder",
            FontWeight::Lighter => "lighter",
        }.into()
    }
}

impl Into<Value> for TextAnchor {
    fn into(self) -> Value {
        match self {
            TextAnchor::Start => "start",
            TextAnchor::Middle => "middle",
            TextAnchor::End => "end",
        }.into()
    }
}

// style="font-style:normal;font-weight:normal;font-size:40px;line-height:1.25;
// font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;
// fill-opacity:1;stroke:none"
impl Label {
    pub fn finalize(self) -> Text {
        let size = self.scaled_size();
        let text = Text::new()
            .set("x", self.pos.x)
            .set("y", self.pos.y)
            .set("font-size", size)
            .set("font-style", self.font.style)
            .set("font-weight", self.font.weight)
            .set("font-family", self.font.family)
            .set("dominant-baseline", "central") // center vertically
            .set("text-anchor", TextAnchor::Middle) // center horizontally
            .set("fill", self.color)
            .add(node::Text::new(self.string));
        text
    }

    pub fn scaled_size(&self) -> f64 {
        let len = self.string.graphemes(true).count() as i32; // lossy cast
        println!("{}, {}", self.string, len);
        let scale = if len > 1 { (0.9_f64).powi(len - 1) } else { 1. };
        self.size * scale
    }
}


impl MyRect {
    pub fn new(pos: P2, size: V2) -> Self {
        Self {
            pos: pos,
            size: size,
            stroke: None,
            fill: None,
            fillet: None,
        }
    }

    pub fn stroke(mut self, color: Color, width: f64) -> Self {
        self.stroke = Some(Stroke {
            color: color,
            width: width,
        });
        self
    }

    pub fn fill(mut self, fill: Fill) -> Self {
        self.fill = Some(fill);
        self
    }

    pub fn fillet(mut self, radius: f64) -> Self {
        assert!(radius >= 0.);
        self.fillet = Some(V2::new(radius, radius));
        self
    }

    fn finalize(self) -> Rectangle {
        let mut element = Rectangle::new()
            .set("x", self.pos.x)
            .set("y", self.pos.y)
            .set("width", self.size.x)
            .set("height", self.size.y);

        if let Some(stroke) = self.stroke {
            element = element
                .set("stroke", stroke.color)
                .set("stroke-width", stroke.width);
        }

        if let Some(fill) = self.fill {
            element = element.set("fill", fill.color());
        }

        if let Some(fillet) = self.fillet {
            element = element.set("rx", fillet.x).set("ry", fillet.y);
        }
        element
    }
}

// #[test]
// fn test_complex_rect() {
//     let rect = MyRect::new(P2::new(50., 25.), V2::new(100., 200.))
//         .fill(Color::Red)
//         .stroke(Color::Blue, 3.)
//         .fillet(5.)
//         .finalize();
//     assert!(
//         rect.to_string()
//             == "<rect fill=\"red\" height=\"200\" rx=\"5\" ry=\"5\" \
//                 stroke=\"blue\" stroke-width=\"3\" width=\"100\" x=\"50\" \
//                 y=\"25\"/>"
//     )
// }

// #[test]
// fn test_simple_rect() {
//     let rect = MyRect::new(P2::new(0., 0.), V2::new(30., 50.)).finalize();
//     assert_eq!(
//         rect.to_string(),
//         "<rect height=\"50\" width=\"30\" x=\"0\" y=\"0\"/>"
//     )
// }

impl Into<Value> for Color {
    fn into(self) -> Value {
        match self {
            Color::Red => "#fc9c93",
            Color::Yellow => "#cdb36b",
            Color::Green => "#7ac68f",
            Color::Cyan => "#01c8d9",
            Color::Blue => "#80b9fe",
            Color::Magenta => "#e49fdb",
            Color::Black => "#000000",
            Color::White => "#ffffff",
            Color::LightGrey => "#b6b6b6",
            Color::DarkGrey => "#3b3b3b",
        }.into()
    }
}

impl Fill {
    // TODO add patterns to distinguish between same colors.
    fn color(&self) -> Color {
        match *self {
            Fill::Blank => Color::White,
            Fill::Single => Color::LightGrey,
            Fill::Shared0 | Fill::Shared6 => Color::Red,
            Fill::Shared1 | Fill::Shared7 => Color::Yellow,
            Fill::Shared2 | Fill::Shared8 => Color::Green,
            Fill::Shared3 | Fill::Shared9 => Color::Cyan,
            Fill::Shared4 | Fill::Shared10 => Color::Blue,
            Fill::Shared5 | Fill::Shared11 => Color::Magenta,
        }
    }
}

impl DisplayStyle {
    fn fill_iter(&self) -> impl Iterator<Item = Fill> {
        let v: Vec<_> = match *self {
            DisplayStyle::Single => ::std::iter::repeat(Fill::Single)
                .take(Chord::chord_length())
                .collect(),
            DisplayStyle::Chords => vec![
                Fill::Shared0,
                Fill::Shared1,
                Fill::Shared2,
                Fill::Shared3,
                Fill::Shared4,
                Fill::Shared5,
                Fill::Shared6,
                Fill::Shared7,
            ],
        };
        v.into_iter()
    }
}

impl P2 {
    fn new(x: f64, y: f64) -> P2 {
        P2 { x: x, y: y }
    }
}

impl V2 {
    fn new(x: f64, y: f64) -> V2 {
        V2 { x: x, y: y }
    }
}

fn get_symbol(key: &Name) -> String {
    // TODO add all symbols
    // TODO share with tutor?
    lazy_static! {
        static ref SYMBOLS: HashMap<Name, String>  = vec![
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
            ("key_enter".into(), "⏎".into()),
            ("key_left".into(), "←".into()),
            ("key_right".into(), "→".into()),
            ("key_up".into(), "↑".into()),
            ("key_down".into(), "↓".into()),
            // ("key_backspace".into(), "⌫".into()),
            ("key_backspace".into(), "bak".into()),
            // ("key_space".into(), "␣".into()),
            ("key_space".into(), "spc".into()),
            ("mod_shift".into(), "⇧".into()),
            ("mod_ctrl".into(), "ctrl".into()),
            ("mod_alt".into(), "alt".into()),
            ("mod_gui".into(), "⌘/❖".into()),
        ].into_iter().collect();
    }
    SYMBOLS.get(key).expect("no symbol for key").to_owned()
}
