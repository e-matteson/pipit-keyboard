#pragma once

#include "auto_config.h"

class Battery {
 public:
  int8_t getLevel();

 private:
  uint16_t readingToLevel(uint16_t reading);
  uint16_t readBattery();

  // const float ref_voltage = 3.3; // reference for analogRead
};
