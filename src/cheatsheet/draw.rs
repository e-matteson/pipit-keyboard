use std::ops::{Add, Div, MulAssign, Sub};
use std::f64::consts::PI;

use svg::{node, Node};
use svg::node::Value;
use svg::node::element::{Circle, Definitions, Group, Line, Mask, Path,
                         Pattern, Rectangle, Text};
use svg::node::element::path::Parameters;
use svg::node::element::path::Data;
// use unicode_segmentation::UnicodeSegmentation;

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

#[derive(Clone, Copy, Debug)]
pub struct Wedge {
    pub tip_pos: P2,
    pub radius: f64,
    pub circle_divisions: usize,
    pub division_num: usize,
}

#[derive(Clone, Copy, Debug)]
struct ArcArgs {
    radius: P2,
    x_axis_rotation: f64,
    large_arc_flag: bool,
    sweep_flag: bool,
    end: P2,
}

#[derive(Clone, Debug)]
pub struct Label {
    pub lines: Vec<String>,
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

#[derive(Clone, Copy, Debug)]
pub enum FillPattern {
    Checkers,
    VertStripes,
    HorizStripes,
    DiagStripes,
    Dots,
}

#[derive(Clone, Copy, Debug)]
#[allow(dead_code)]
pub struct Fill {
    pub color: Color,
    pub pattern: Option<FillPattern>,
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

    pub fn reset_stroke(mut self) -> Self {
        self.stroke = None;
        self
    }

    pub fn fill(mut self, fill: Fill) -> Self {
        self.fill = Some(fill);
        self
    }

    pub fn reset_fill(mut self) -> Self {
        self.fill = None;
        self
    }

    pub fn fillet(mut self, radius: f64) -> Self {
        assert!(radius >= 0.);
        self.fillet = Some(V2::new(radius, radius));
        self
    }

    pub fn reset_fillet(mut self) -> Self {
        self.fillet = None;
        self
    }

    pub fn center(&self) -> P2 {
        self.pos + self.size / 2.
    }

    pub fn scale(mut self, factor: f64) -> Self {
        // Scale the switch uniformly around its center
        let center = self.center();
        self.size *= factor;
        self.pos = center - self.size / 2.;
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
            // TODO put None option in fill enum
            fill.assign_to(&mut element);
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
            fill.assign_to(&mut element);
        } else {
            element.assign("fill", "none");
        }

        element
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

    pub fn finalize(&self, fill: Fill) -> Path {
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

    pub fn label_pos(&self) -> P2 {
        self.tip_pos
            + polar_vec(
                self.radius / 3.,
                self.rotation_radians() + self.width_radians() / 2.,
            ).reflect_xy()
    }
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

impl Label {
    pub fn finalize(self) -> Group {
        let mut g = Group::new();
        let mut y = self.pos.y - self.total_height() / 2.;
        let line_height = self.line_height();
        for line in self.lines {
            let text = Text::new()
                .set("x", self.pos.x)
                .set("y", y)
                .set("font-size", self.size)
                .set("font-style", self.font.style)
                .set("font-weight", self.font.weight)
                .set("font-family", self.font.family.clone())
                .set("dominant-baseline", "central") // center vertically
                .set("text-anchor", TextAnchor::Middle) // center horizontally
                .set("fill", self.color)
                .add(node::Text::new(line.to_owned()));

            g.append(text);
            y += line_height;
        }
        g
    }

    fn line_height(&self) -> f64 {
        // self.size * 1.1
        self.size
    }

    fn total_height(&self) -> f64 {
        self.line_height() * ((self.lines.len() as f64) - 1.)
    }
}

impl Fill {
    pub fn new_solid(color: Color) -> Fill {
        Fill {
            color: color,
            pattern: None,
        }
    }

    pub fn assign_to<T>(&self, node: &mut T)
    where
        T: Node,
    {
        node.assign("fill", self.color);
        if let Some(pattern) = self.pattern {
            node.assign("mask", pattern.mask_url());
        }
    }
}

impl FillPattern {
    fn mask_url(&self) -> String {
        format!("url(#{})", self.mask_id())
    }

    fn pattern_url(&self) -> String {
        format!("url(#{})", self.pattern_id())
    }

    fn pattern_id(&self) -> String {
        format!("Pattern{}", self.id_base())
    }

    fn mask_id(&self) -> String {
        format!("Mask{}", self.id_base())
    }
    fn id_base(&self) -> String {
        match *self {
            FillPattern::Checkers => "Checkers".into(),
            FillPattern::VertStripes => "VertStripes".into(),
            FillPattern::HorizStripes => "HorizStripes".into(),
            FillPattern::DiagStripes => "DiagStripes".into(),
            FillPattern::Dots => "Dots".into(),
        }
    }

    pub fn add_all_definitions(background: MyRect, defs: &mut Definitions) {
        FillPattern::Checkers.add_definition(background, defs);
        FillPattern::VertStripes.add_definition(background, defs);
        FillPattern::HorizStripes.add_definition(background, defs);
        FillPattern::DiagStripes.add_definition(background, defs);
        FillPattern::Dots.add_definition(background, defs);
    }

    pub fn add_definition(&self, background: MyRect, defs: &mut Definitions) {
        let pattern = match *self {
            FillPattern::Checkers => FillPattern::checkers_pattern(),
            FillPattern::VertStripes => FillPattern::vert_stripes_pattern(),
            FillPattern::HorizStripes => FillPattern::horiz_stripes_pattern(),
            FillPattern::DiagStripes => FillPattern::diag_stripes_pattern(),
            FillPattern::Dots => FillPattern::dots_pattern(),
        }.set("id", self.pattern_id());

        let rect = background.finalize().set("fill", self.pattern_url());
        let mask = Mask::new().set("id", self.mask_id()).add(rect);
        defs.append(pattern);
        defs.append(mask);
    }

    fn checkers_pattern() -> Pattern {
        let size = 4.;
        let rect1 = Rectangle::new()
            .set("x", 0.)
            .set("y", 0.)
            .set("width", size)
            .set("height", size)
            .set("fill", "white");

        let rect2 = Rectangle::new()
            .set("x", size)
            .set("y", size)
            .set("width", size)
            .set("height", size)
            .set("fill", "white");

        let rect3 = Rectangle::new()
            .set("x", 0.)
            .set("y", 0.)
            .set("width", 2. * size)
            .set("height", 2. * size)
            .set("fill", "white")
            .set("fill-opacity", "0.3");

        let pattern = Pattern::new()
            .set("x", 0)
            .set("y", 0)
            .set("width", size * 2.)
            .set("height", size * 2.)
            .set("patternUnits", "userSpaceOnUse")
            .add(rect1)
            .add(rect2)
            .add(rect3);
        pattern
    }

    fn vert_stripes_pattern() -> Pattern {
        let size = 2.;
        let rect1 = Rectangle::new()
            .set("x", 0.)
            .set("y", 0.)
            .set("width", size)
            .set("height", 2. * size)
            .set("fill", "white")
            .set("fill-opacity", 0.5);
        let rect2 = Rectangle::new()
            .set("x", size)
            .set("y", 0.)
            .set("width", size)
            .set("height", 2. * size)
            .set("fill", "white");

        let pattern = Pattern::new()
            .set("x", 0)
            .set("y", 0)
            .set("width", size * 2.)
            .set("height", size * 2.)
            .set("patternUnits", "userSpaceOnUse")
            .add(rect1)
            .add(rect2);
        pattern
    }

    fn horiz_stripes_pattern() -> Pattern {
        let size = 2.;
        let rect1 = Rectangle::new()
            .set("x", 0.)
            .set("y", 0.)
            .set("width", 2. * size)
            .set("height", size)
            .set("fill", "white")
            .set("fill-opacity", 0.5);
        let rect2 = Rectangle::new()
            .set("x", 0.)
            .set("y", size)
            .set("width", 2. * size)
            .set("height", size)
            .set("fill", "white");

        let pattern = Pattern::new()
            .set("x", 0)
            .set("y", 0)
            .set("width", size * 2.)
            .set("height", size * 2.)
            .set("patternUnits", "userSpaceOnUse")
            .add(rect1)
            .add(rect2);
        pattern
    }

    fn diag_stripes_pattern() -> Pattern {
        let size = 4.;
        let line1 = Line::new()
            .set("x1", 0)
            .set("y1", 0)
            .set("x2", 0)
            .set("y2", size)
            .set("stroke", "white")
            .set("stroke-width", size);

        let line2 = Line::new()
            .set("x1", size / 2.)
            .set("y1", 0)
            .set("x2", size / 2.)
            .set("y2", size)
            .set("stroke", "white")
            .set("stroke-opacity", 0.3)
            .set("stroke-width", size);

        Pattern::new()
            .set("x", 0)
            .set("y", 0)
            .set("width", size)
            .set("height", size)
            .set("patternTransform", "rotate(45 0 0)")
            .set("patternUnits", "userSpaceOnUse")
            .add(line1)
            .add(line2)
    }

    fn dots_pattern() -> Pattern {
        let radius = 4.;
        let side = 4. * radius;
        let dot = Circle::new()
            .set("cx", radius)
            .set("cy", radius)
            .set("r", radius)
            .set("fill", "white");

        Pattern::new()
            .set("x", 0)
            .set("y", 0)
            .set("width", side)
            .set("height", side)
            .set("patternUnits", "userSpaceOnUse")
            .add(dot)
    }
}

impl Into<Value> for Color {
    fn into(self) -> Value {
        match self {
            Color::Red => "#fa99b7",
            Color::Yellow => "#eba676",
            Color::Green => "#a7be74",
            Color::Cyan => "#48c9b4",
            Color::Blue => "#3ac3f5",
            Color::Magenta => "#b9acf6",
            Color::Black => "#000000",
            Color::White => "#ffffff",
            Color::LightGrey => "#eeeeee",
            Color::DarkGrey => "#b6b6b6",
        }.into()
    }
}

impl Default for Font {
    fn default() -> Font {
        Font {
            family: "sans-serif".into(),
            // weight: FontWeight::Normal,
            weight: FontWeight::Bolder,
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

impl Div<f64> for V2 {
    type Output = V2;
    fn div(self, rhs: f64) -> V2 {
        V2::new(self.x / rhs, self.y / rhs)
    }
}

impl MulAssign<f64> for V2 {
    fn mul_assign(&mut self, rhs: f64) {
        self.x *= rhs;
        self.y *= rhs;
        // P2::new(self.x / rhs, self.y / rhs)
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

fn polar_vec(radius: f64, radians: f64) -> V2 {
    let x = radians.cos() * radius;
    let y = radians.sin() * radius;
    V2::new(x, y)
}

// pub fn mark(pos: P2) -> Circle {
//     Circle::new()
//         .set("cx", pos.x)
//         .set("cy", pos.y)
//         .set("fill", Color::Red)
//         .set("r", 5)
// }
