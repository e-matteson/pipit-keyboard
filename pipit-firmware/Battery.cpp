#include "Battery.h"


Battery::Battery(){
  // empty_reading = voltageToReading(empty_voltage);
  // full_reading = voltageToReading(full_voltage);
}


int8_t Battery::getLevel(){
#ifndef HAS_BATTERY
  return -1;
#endif
  // Return battery level, in the range (0, full_level)
  uint16_t reading = readBattery();
  return readingToLevel(reading);
}

uint16_t Battery::readingToLevel(uint16_t reading){
  float voltage = readingToVoltage(reading);

  DEBUG1("battery voltage: ");
  DEBUG1_LN(voltage);

  // return map(reading, empty_reading, full_reading, empty_level, full_level);
  if (voltage > 4.36) {
    return 4;  // plugged in, battery disconnected
  }
  if (voltage > 4.2) {
    return 3;  // fully charged
  }
  if (voltage > 3.95) {
    return 2;
  }
  if (voltage > 3.7) {
    return 1;
  }
  return 0; // nearly dead
}

float Battery::readingToVoltage(uint16_t reading){
  // multiply by 2 because of the built-in voltage divider
  return reading * 2.0 * ref_voltage / 1024.0;
}

// uint16_t Battery::voltageToReading(float voltage){
//   return (voltage * 1024.0) / (2.0 * ref_voltage);
// }



uint16_t Battery::readBattery(){
#ifndef HAS_BATTERY
  return 0;
#else
  return analogRead(battery_level_pin);
#endif
}

float Battery::getVoltage(){
#ifndef HAS_BATTERY
  return 0;
#endif
  return readingToVoltage(readBattery());

}
