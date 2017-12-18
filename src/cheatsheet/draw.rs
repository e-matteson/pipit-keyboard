use std::ops::Add;

// use svg;
// use svg::Document;
use svg::node;
use svg::node::Value;
use svg::node::element::{Rectangle, Text};

use unicode_segmentation::UnicodeSegmentation;

#[derive(Clone, Copy, Debug)]
pub struct MyRect {
    pos: P2,
    size: V2,
    stroke: Option<Stroke>,
    fill: Option<Fill>,
    fillet: Option<V2>,
}

#[derive(Clone, Debug)]
pub struct Label {
    pub string: String,
    pub pos: P2,
    pub color: Color,
    pub size: f64,
    pub font: Font,
}


#[derive(Clone, Debug)]
pub struct Font {
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
#[allow(dead_code)]
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
#[allow(dead_code)]
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
#[allow(dead_code)]
pub enum FontStyle {
    Normal,
    Italic,
    Oblique,
}

#[derive(Clone, Copy, Debug)]
#[allow(dead_code)]
pub enum FontWeight {
    Normal,
    Bold,
    Bolder,
    Lighter,
}

#[derive(Clone, Copy, Debug)]
#[allow(dead_code)]
pub enum TextAnchor {
    Start,
    Middle,
    End,
}

#[derive(Clone, Copy, Debug)]
pub struct P2 {
    pub x: f64,
    pub y: f64,
}

#[derive(Clone, Copy, Debug)]
pub struct V2 {
    pub x: f64,
    pub y: f64,
}

////////////////////////////////////////////////////////////////////////////////

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

    pub fn finalize(self) -> Rectangle {
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



impl Default for Font {
    fn default() -> Font {
        Font {
            family: "sans-serif".into(),
            weight: FontWeight::Normal,
            style: FontStyle::Normal,
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

impl P2 {
    pub fn new(x: f64, y: f64) -> P2 {
        P2 { x: x, y: y }
    }
}

impl V2 {
    pub fn new(x: f64, y: f64) -> V2 {
        V2 { x: x, y: y }
    }
}

impl Add<(f64, f64)> for P2 {
    type Output = P2;
    fn add(self, rhs: (f64, f64)) -> P2 {
        P2::new(self.x + rhs.0, self.y + rhs.1)
    }
}
