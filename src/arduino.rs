use std::process::Command;

use error::{Error, ResultExt};
use types::BoardName;

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

        let context = match status.code() {
            Some(0) => return Ok(()),
            Some(1) => "Build failed or upload failed",
            Some(2) => "Sketch not found",
            Some(3) => "Invalid (argument for) commandline option",
            Some(4) => "Preference passed to --get-pref does not exist",
            None => "Arduino IDE process was terminated",
            _ => "Arduino IDE failed with unknown exit status",
        };
        Err(Error::Arduino.context(context))
    }
}

impl BoardName {
    fn ide_name(&self) -> &'static str {
        match self {
            BoardName::TeensyLC => unimplemented!(),
        }
    }
    // fn parameters(&self) -> Option<&'static str> {
    //     match self {
    //         BoardName::TeensyLC => unimplemented!(),
    //     }
    // }
}
