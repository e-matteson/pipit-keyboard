#include "Comms.h"

#if defined(FEATHER_M0_BLE)
#ifndef FEATHERCOMMS_H
#define FEATHERCOMMS_H

#include <Adafruit_BluefruitLE_SPI.h>

class FeatherComms : public Comms {
 public:
  FeatherComms();
  void setup();
  void press(const Report* report);
  void proportionalDelay(uint8_t data_length, uint8_t multiplier);
  void toggleWireless();
  void moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan);

 private:
  uint8_t getDelay(uint8_t data_length);
  void setupBluetooth();
  void disableBluetooth();
  void pressWired(const Report* report);
  void pressWireless(const Report* report);
  void moveMouseWireless(int8_t x, int8_t y, int8_t scroll, int8_t pan);

  Adafruit_BluefruitLE_SPI bluetooth;

  bool use_wired = 0;
};

#endif
#endif
