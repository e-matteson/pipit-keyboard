#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include "auto_config.h"
#include "Report.h"

#ifdef FEATHER_M0_BLE
#include <Adafruit_BluefruitLE_SPI.h>
#endif

// Parent class that defines an interface for sending keypresses over either a
// Bluetooth or Wired connection. It also includes some bluetooth status and
// configuration functions, which are not meaningful for a wired connection.

class Comms {
public:
  Comms();
  void setup();
  void press(const Report* report);
  bool isConnected();
  void proportionalDelay(uint8_t data_length, uint8_t multiplier);

private:
  uint8_t getDelay(uint8_t data_length);
  void setupBluetooth();

  void warnNoBluetooth();

#ifdef FEATHER_M0_BLE
  // Construct bluetooth controller.
  Adafruit_BluefruitLE_SPI* bluetooth;
#endif

};


#endif
