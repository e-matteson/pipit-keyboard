#include "Comms.h"

#if defined(TEENSY_LC)
#ifndef TEENSYCOMMS_H
#define TEENSYCOMMS_H

class TeensyComms : public Comms {
 public:
  void setup();
  void press(const Report* report);
  void proportionalDelay(uint8_t data_length, uint8_t multiplier);
  void toggleWireless();
  void moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan);
};

#endif
#endif
