#include "Battery.h"

int8_t Battery::getLevel() {
#ifdef HAS_BATTERY
  // Return battery level, in the range (0, full_level)
  uint16_t reading = readBattery();
  return readingToLevel(reading);
#endif

  return -1;
}

uint16_t Battery::readingToLevel(uint16_t reading) {
  DEBUG1("battery reading: ");
  DEBUG1_LN(reading);

  if (reading > 676) {
    return 4;  // plugged in, battery disconnected
  }
  if (reading > 605) {
    return 3;  // fully charged
  }
  if (reading > 590) {
    return 2;
  }
  if (reading > 574) {
    return 1;
  }
  return 0;  // nearly dead
}

uint16_t Battery::readBattery() {
#ifdef HAS_BATTERY
  return analogRead(conf::battery_level_pin);
#endif

  return 0;
}
