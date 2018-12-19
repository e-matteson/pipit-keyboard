#pragma once

#include "Comms.h"

#if defined(FEATHER_M0_BLE)

#include <Adafruit_BluefruitLE_SPI.h>

class FeatherComms : public Comms {
 public:
  FeatherComms();
  void setup();
  void press(const Report* report);
  void proportionalDelay(uint8_t data_length, uint8_t multiplier);
  bool toggleWireless();
  void moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan);

 private:
  uint8_t getDelay(uint8_t data_length);
  void setupBluetooth();
  void disableBluetooth();
  void moveMouseWireless(int8_t x, int8_t y, int8_t scroll, int8_t pan);
  void pressWireless(const Report* report);

#ifdef ENABLE_WIRED_FEATHER_HACK
  void pressWired(const Report* report);
#endif

  Adafruit_BluefruitLE_SPI bluetooth;

  bool use_wired = 0;
};

#endif
