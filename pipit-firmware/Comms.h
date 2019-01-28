#pragma once

#include <stdint.h>

#include "Report.h"
#include "auto_config.h"

class Comms {
 public:
  void press(const Report* report);
  void moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan);
};
