/**********************************************************************
Copyright (C) 2016 e-matteson (e.r.matteson@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

// // Treat all compiler warnings as errors
// // The Adafruit_BLE.h library has warnings, though.
// #pragma GCC diagnostic error "-Werror"

#include "Pipit.h"

// #include "OneShot.h"
// #include "Timer.h"

Pipit pipit;

// uint8_t red = 10;
// uint8_t green = 11;
// uint8_t blue = 12;
//
// FeatherOneShot one_shot(0x2FFF);
//
// void colorISR() {
//   static bool toggle = true;
//   if (toggle) {
//     digitalWrite(red, 0);
//     digitalWrite(green, 1);
//     digitalWrite(blue, 0);
//     OneShot::getInstance()->schedule(0x2FF);
//   } else {
//     digitalWrite(red, 1);
//     digitalWrite(green, 0);
//     digitalWrite(blue, 0);
//     OneShot::getInstance()->schedule(0x4FFF);
//   }
//   toggle ^= true;
// }

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(10, 1);
  digitalWrite(11, 1);
  digitalWrite(12, 1);

#ifdef ENABLE_SERIAL_DEBUG
  Serial.begin(115200);  // for sending feedback codes and debug messages
#endif
  delay(500);
  pipit.setup();
}

void loop() { pipit.loop(); }
