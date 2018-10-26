Pipit Keyboard
==============

Firmware, configuration tools and a typing tutor for a small, ergonomic chording keyboard with only 24 switches.

Common letters are typed by pressing a single switch, and rarer letters are typed by pressing 2 switches at once - like playing a piano chord. The keyboard also stores a customizable dictionary of 4000+ words and macros that can each be entered with a single chord.

You can change the keymap, dictionary, and other settings by editing config files. You then run the configuration tool once to generate updated firmware, and load the new firmware onto the keyboard\'s microcontroller.

The firmware is compatible with several varieties of arduino-compatible ARM microcontroller boards. It currently suppports the `Adafruit Feather BLE M0` (for a wireless keyboard) and the `Teensy LC` (for a wired keyboard).

![keyboard photo](https://raw.githubusercontent.com/e-matteson/pipit-guide/master/src/assets/v2_with_hand.png)


[User Guide](https://e-matteson.github.io/pipit-guide/)
-------------------------------------------------------

Brief instructions
------------------

See the [User Guide](https://e-matteson.github.io/pipit-guide/) for more detail.

### Loading firmware

-   Install [rust](https://www.rust-lang.org) and the [Arduino IDE](https://www.arduino.cc/en/Main/Software) (along with support for your microcontroller).
-   Clone this repository.
-   Configure the keyboard by editing `settings/settings.yaml`.
-   Run the configuration tool to generate the firmware: `$ cargo run`
-   Open `pipit-firmware/pipit-firmware.ino` in the Arduino IDE, and upload to your microcontroller.

### Trying out the typing tutor

The typing tutor teaches you the layout of the keyboard. It gives you a line of text to copy, and guides you with a hint showing how to type the next letter.

-   Install [rust](https://www.rust-lang.org)
-   Clone this repository.
-   Compile and run the typing tutor in your terminal: `$ cargo run -- --tutor`

![tutor screenshot](https://raw.githubusercontent.com/e-matteson/pipit-guide/master/src/assets/quickbrownfox.png)

Contributing
------------

Feedback, issue reports, and pull requests are very welcome. If you make new settings files or `.kmap` files, consider contributing them to the repository for others to use.

License
-------

The code in this project is licensed under GPLv3 or later. The original author is e-matteson (e.r.matteson\@gmail.com).
