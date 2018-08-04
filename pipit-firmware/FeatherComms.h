#include "Comms.h"

#if defined(FEATHER_M0_BLE)
#ifndef FEATHERCOMMS_H
#define FEATHERCOMMS_H

#include <Adafruit_BluefruitLE_SPI.h>

class FeatherComms: public Comms {
 public:
  FeatherComms();
  void setup();
  void press(const Report* report);
  void proportionalDelay(uint8_t data_length, uint8_t multiplier);
  void toggleWireless();

 private:
  uint8_t getDelay(uint8_t data_length);
  void setupBluetooth();
  void disableBluetooth();
  void pressWired(const Report* report);
  void pressWireless(const Report* report);

  // Construct bluetooth controller.
  Adafruit_BluefruitLE_SPI* bluetooth;

  bool use_wired = 0;
};


#endif
#endif
