#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include "auto_config.h"
#include "Report.h"


// Parent class that defines an interface for sending keypresses over either a
// Bluetooth or Wired connection.

class Comms {
public:
  virtual void setup();
  virtual void press(const Report* report);
  virtual void proportionalDelay(uint8_t data_length, uint8_t multiplier);
  virtual void toggleWireless();
  virtual void moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan);
};


#endif
