use std::ops::{Add, Sub};

use svg::{node, Node};
use svg::node::Value;
use svg::node::element::{Circle, Rectangle, Text};
use svg::node::element::path::Parameters;

use unicode_segmentation::UnicodeSegmentation;

#[derive(Clone, Copy, Debug)]
pub struct MyRect {
    pos: P2,
    size: V2,
    stroke: Option<Stroke>,
    fill: Option<Fill>,
    fillet: Option<V2>,
}

#[derive(Clone, Copy, Debug)]
pub struct MyCircle {
    pos: P2,
    radius: f64,
    fill: Option<Fill>,
    stroke: Option<Stroke>,
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

    pub fn _fill(mut self, fill: Fill) -> Self {
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
            element.assign("stroke", stroke.color);
            element.assign("stroke-width", stroke.width);
        }

        if let Some(fill) = self.fill {
            element.assign("fill", fill.color());
        } else {
            element.assign("fill", "none");
        }

        if let Some(fillet) = self.fillet {
            element.assign("rx", fillet.x);
            element.assign("ry", fillet.y);
        }
        element
    }
}

impl MyCircle {
    pub fn new(pos: P2, radius: f64) -> Self {
        Self {
            pos: pos,
            radius: radius,
            stroke: None,
            fill: None,
        }
    }

    pub fn _stroke(mut self, color: Color, width: f64) -> Self {
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

    pub fn finalize(self) -> Circle {
        let mut element = Circle::new()
            .set("cx", self.pos.x)
            .set("cy", self.pos.y)
            .set("r", self.radius);

        if let Some(stroke) = self.stroke {
            element.assign("stroke", stroke.color);
            element.assign("stroke-width", stroke.width);
        }

        if let Some(fill) = self.fill {
            element.assign("fill", fill.color());
        } else {
            element.assign("fill", "none");
        }

        element
    }
}

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
                                                              // println!("{}, {}", self.string, len);
        let scale = if len > 1 { (0.9_f64).powi(len - 1) } else { 1. };
        self.size * scale
    }
}

impl Fill {
    // TODO add patterns to distinguish between same colors.
    pub fn color(&self) -> Color {
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
    pub fn origin() -> P2 {
        P2::new(0., 0.)
    }
}

impl V2 {
    pub fn new(x: f64, y: f64) -> V2 {
        V2 { x: x, y: y }
    }

    pub fn reflect_xy(&self) -> V2 {
        V2::new(self.y, self.x)
    }
}

impl Add<(f64, f64)> for P2 {
    type Output = P2;
    fn add(self, rhs: (f64, f64)) -> P2 {
        P2::new(self.x + rhs.0, self.y + rhs.1)
    }
}

impl Add<V2> for P2 {
    type Output = P2;
    fn add(self, rhs: V2) -> P2 {
        P2::new(self.x + rhs.x, self.y + rhs.y)
    }
}
impl Sub<V2> for P2 {
    type Output = P2;
    fn sub(self, rhs: V2) -> P2 {
        P2::new(self.x - rhs.x, self.y - rhs.y)
    }
}

impl Into<Parameters> for P2 {
    fn into(self) -> Parameters {
        (self.x, self.y).into()
    }
}
impl Into<V2> for P2 {
    fn into(self) -> V2 {
        V2::new(self.x, self.y)
    }
}
impl Into<P2> for V2 {
    fn into(self) -> P2 {
        P2::new(self.x, self.y)
    }
}
