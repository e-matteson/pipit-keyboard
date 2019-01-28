/**********************************************************************
Copyright (C) 2019 e-matteson (e.r.matteson@gmail.com)

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
#pragma GCC diagnostic error "-Werror"

#include "Pipit.h"

Pipit pipit;

void setup() {
#ifdef ENABLE_SERIAL_DEBUG
  Serial.begin(115200);  // for sending feedback codes and debug messages
#endif
  pipit.setup();
}

void loop() { pipit.loop(); }
