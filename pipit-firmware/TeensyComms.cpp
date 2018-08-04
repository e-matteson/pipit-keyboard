#include "TeensyComms.h"

#ifdef TEENSY_LC

TeensyComms::TeensyComms(){}

void TeensyComms::setup(){
  // nothing to setup
}

void TeensyComms::proportionalDelay(uint8_t data_length, uint8_t multiplier){
  // don't need to sleep between USB keypresses
}

void TeensyComms::toggleWireless(){
  // no wireless option!
}

void TeensyComms::press(const Report* report){
    Keyboard.set_key1(report->get(0));
    Keyboard.set_key2(report->get(1));
    Keyboard.set_key3(report->get(2));
    Keyboard.set_key4(report->get(3));
    Keyboard.set_key5(report->get(4));
    Keyboard.set_key6(report->get(5));
    Keyboard.set_modifier(report->getMod());
    Keyboard.send_now();
}

#endif
