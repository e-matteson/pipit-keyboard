use svg::node::element::Group;
use svg::Node;

use cheatsheet::switch::{Content, Switch, SwitchStyle, Symbol};
use error::Error;
use types::{ModeName, Name, TutorData};

use cheatsheet::draw::{Color, P2, V2};

#[derive(Clone, Debug)]
pub struct Keyboard {
    switches: Vec<Switch>,
}

#[derive(Clone, Debug, Deserialize)]
pub struct KeyboardSpec {
    pub chord_names: Vec<Name>,
    // TODO add title?
}

impl Keyboard {
    pub fn new(pos: P2) -> Self {
        Self {
            switches: Self::positions(pos)
                .into_iter()
                .map(Switch::new)
                .collect(),
        }
    }

    pub fn set(
        &mut self,
        chord_names: &[Name],
        data: &TutorData,
        mode: &ModeName,
    ) -> Result<(), Error> {
        assert_eq!(data.chord_spec.num_switches, self.switches.len());
        let chords = chord_names
            .iter()
            .map(|name| data.chord(name, mode))
            .collect::<Result<Vec<_>, _>>()?;

        let symbols = chord_names
            .iter()
            .map(Symbol::from_name)
            .collect::<Result<Vec<_>, _>>()?;

        let mut chord_style_iter = SwitchStyle::chord_style_iter();

        for (chord, symbol) in chords.into_iter().zip(symbols.into_iter()) {
            let style = if chord.count_pressed() == 1 {
                SwitchStyle::Single
            } else {
                // Usually this means there's a multi-switch chord.
                // We should also consume a chord style if 0 switches are
                // pressed, meaning this is a blank chord named "", used for
                // skipping colors.
                chord_style_iter.next().ok_or(Error::Style)?
            };

            let content = Content {
                symbol: symbol.clone(),
                style,
            };
            for (index, bit) in chord.iter().enumerate() {
                if bit {
                    self.switches[index].push_content(content.clone());
                }
            }
        }
        Ok(())
    }

    pub fn add_to(&self, group: &mut Group) {
        let mut frame_group = Group::new();
        for switch in &self.switches {
            switch.add_frame_to(
                &mut frame_group,
                Color::Black,
                Self::outer_frame_scale(),
            );
        }
        for switch in &self.switches {
            switch.add_frame_to(
                &mut frame_group,
                Color::White,
                Self::inner_frame_scale(),
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

    pub fn height() -> f64 {
        // TODO this could fail if the switch alignment changes! Those 2
        // switches won't always be highest and lowest.
        let positions = Self::positions(P2::origin());
        let err_msg = "failed to calc keyboard height";
        let highest = 2;
        let lowest = 20;
        let height = positions.get(lowest).expect(err_msg).y
            - positions.get(highest).expect(err_msg).y
            + Switch::side_length() * Self::outer_frame_scale();
        height * 1.1
    }

    pub fn width() -> f64 {
        // TODO this could fail if the switch alignment changes! Those 2
        // switches won't always be highest and lowest.
        let positions = Self::positions(P2::origin());
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
            (Self::outer_frame_scale() - 1.) * Switch::side_length() / 2.;
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
