#include "TeensyComms.h"
#include <Arduino.h>

#ifdef TEENSY_LC

void TeensyComms::setup() {
  // nothing to setup
}

void TeensyComms::proportionalDelay(uint8_t data_length, uint8_t multiplier) {
  // don't need to sleep between USB keypresses
}

void TeensyComms::toggleWireless() {
  // no wireless option!
}

void TeensyComms::press(const Report* report) {
  Keyboard.set_key1(report->get(0));
  Keyboard.set_key2(report->get(1));
  Keyboard.set_key3(report->get(2));
  Keyboard.set_key4(report->get(3));
  Keyboard.set_key5(report->get(4));
  Keyboard.set_key6(report->get(5));
  Keyboard.set_modifier(report->getMod());
  Keyboard.send_now();
}

void TeensyComms::moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan) {
  if (scroll != 0) {
    Mouse.scroll(scroll);
  }
  if (x != 0 || y != 0) {
    Mouse.move(x, y);
  }
  if (pan != 0) {
    DEBUG1_LN("WARNING: mouse panning is not implemented");
  }
}
#endif
