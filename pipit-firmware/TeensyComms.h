#include "Comms.h"

#if defined(TEENSY_LC)
#ifndef TEENSYCOMMS_H
#define TEENSYCOMMS_H


class TeensyComms: public Comms {
 public:
  TeensyComms();
  void setup();
  void press(const Report* report);
  void proportionalDelay(uint8_t data_length, uint8_t multiplier);
  // void toggleWireless();
};


#endif
#endif
