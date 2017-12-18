use std::collections::HashMap;

use svg;
use svg::Document;
use svg::Node;


use tutor::TutorData;
use types::{Chord, Name};
use cheatsheet::draw::{Color, Fill, Font, Label, MyRect, P2, V2};


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
            ("mod_gui".into(), "⌘❖".into()),
        ].into_iter().collect();
    }
    SYMBOLS.get(key).expect("no symbol for key").to_owned()
}
