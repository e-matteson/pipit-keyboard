#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include "auto_config.h"


class Battery{
public:
  Battery();
  int8_t getLevel();
  float getVoltage();

private:
  uint16_t readingToLevel(uint16_t reading);
  float readingToVoltage(uint16_t reading);
  uint16_t readBattery();

  // uint16_t voltageToReading(float voltage);

  // const uint8_t empty_level = 0; // level that indicates battery is empty
  // const uint8_t full_level = 4; // level that indicates battery is fully charged
  // const float full_voltage = 4.6;
  // const float full_voltage = 4.2; // what we consider an almost fully charged battery
  // const float empty_voltage = 3.5; // what we consider a dead battery

  const float ref_voltage = 3.3; // reference for analogRead

  // uint16_t empty_reading;
  // uint16_t full_reading;

};

#endif
