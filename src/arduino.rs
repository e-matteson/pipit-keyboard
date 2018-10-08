use std::process::Command;

use types::BoardName;

use failure::{Error, ResultExt};
// use types::errors::*;

pub struct ArduinoIDE {
    board: BoardName,
}

enum ArduinoCommand {
    Verify,
    Upload { port: Option<String> },
}

impl ArduinoCommand {
    fn args(&self) -> Vec<String> {
        match self {
            ArduinoCommand::Verify => vec!["--verify".to_owned()],
            ArduinoCommand::Upload { ref port } => {
                let mut v = vec!["--upload".to_owned()];
                if let Some(port) = port {
                    v.push("--port".to_owned());
                    v.push(port.to_owned());
                }
                v
            }
        }
    }
}

impl ArduinoIDE {
    pub fn new(board: BoardName) -> Self {
        Self { board }
    }
    pub fn verify(&self) -> Result<(), Error> {
        self.run(ArduinoCommand::Verify)
    }

    pub fn upload(&self, port: Option<&str>) -> Result<(), Error> {
        self.run(ArduinoCommand::Upload {
            port: port.map(|s| s.to_owned()),
        })
    }

    /// The name/location of the arduino IDE
    fn executable() -> &'static str {
        "arduino"
    }

    /// The path to the .ino file, relative to the crate root. The Arduino IDE
    /// requires the file name to match the name of the directory it is in.
    fn sketch_file() -> &'static str {
        "pipit-firmware/pipit-firmware.ino"
    }

    /// Open the Arduino IDE non-interactively in a new process, and tell it to
    /// run the given comand.
    fn run(&self, command: ArduinoCommand) -> Result<(), Error> {
        println!("\nOpening the Arduino IDE.");
        let status = Command::new(Self::executable())
            .args(command.args())
            .args(&["--board", self.board.ide_name()])
            .arg(Self::sketch_file())
            .status()
            .context("Failed to open Arduino IDE")?;

        // TODO use real error types
        match status.code() {
            Some(0) => Ok(()),
            Some(1) => bail!("Build failed or upload failed"),
            Some(2) => bail!("Sketch not found"),
            Some(3) => bail!("Invalid (argument for) commandline option"),
            Some(4) => bail!("Preference passed to --get-pref does not exist"),
            None => bail!("Arduino IDE process was terminated"),
            _ => bail!("Arduino IDE failed with unknown exit status"),
        }
    }
}

impl BoardName {
    fn ide_name(&self) -> &'static str {
        match self {
            BoardName::FeatherM0BLE => "adafruit:samd:adafruit_feather_m0",
            BoardName::TeensyLC => unimplemented!(),
        }
    }
    // fn parameters(&self) -> Option<&'static str> {
    //     match self {
    //         BoardName::FeatherM0BLE => None
    //         BoardName::TeensyLC => unimplemented!(),
    //     }
    // }
}
