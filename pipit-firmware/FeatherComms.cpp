#include "FeatherComms.h"

#ifdef FEATHER_M0_BLE

// // My hacky modified version of the default arduino keyboard library. The
// // default version won't work!
// // Used for USB sending on the feather, only.
// // It includes redefinitons of some KEY_*, with incorrect scancodes. So make
// // sure we don't include this somewhere it can clobber the correct scancodes!
#ifdef ENABLE_WIRED_FEATHER_HACK
#include <Keyboard.h>
#endif

// TODO look up and document the magic bluetooth args
FeatherComms::FeatherComms() : bluetooth(8, 7, 4)  {
}

void FeatherComms::setup(){
  setupBluetooth();

#ifdef ENABLE_WIRED_FEATHER_HACK
  Keyboard.begin();
#endif
}

void FeatherComms::setupBluetooth(){
  // if we're not using the feather, do nothing
  bool success = 1;
  success |= bluetooth.begin(0); // arg is verbosity

  // Delete all stored data, or it won't reconnect to paired hosts?!
  // success |= bluetooth.factoryReset();

  bluetooth.echo(false); // Disable command echo
  // TODO does the F() macro do anything?
  success |= bluetooth.sendCommandCheckOK(F("AT+GAPDEVNAME=pipit"));

  success |= bluetooth.sendCommandCheckOK(F("AT+BLEPOWERLEVEL=0"));
  success |= bluetooth.sendCommandCheckOK(F("AT+GAPCONNECTABLE=1"));

  // Enable keyboard service
  success |= bluetooth.sendCommandCheckOK(F("AT+BleHIDEn=On"));

  // Must perform software reset after enabling a service
  success |= bluetooth.reset();

  // int32_t* reply;
  // success = bluetooth.sendCommandWithIntReply(F("AT+BLEPOWERLEVEL"), reply);
  // Serial.println(*reply);

  if(success){
    DEBUG1_LN("bluetooth setup done");
  }
  else{
    DEBUG1_LN("WARNING: bluetooth setup may have failed");
  }
}

void FeatherComms::press(const Report* report){
#ifdef ENABLE_WIRED_FEATHER_HACK
  if (use_wired) {
    pressWired(report);
  } else {
    pressWireless(report);
  }
  return;
#endif

  pressWireless(report);
}

void FeatherComms::pressWired(const Report* report){
#ifdef ENABLE_WIRED_FEATHER_HACK
  Keyboard.set_key1(report->get(0));
  Keyboard.set_key2(report->get(1));
  Keyboard.set_key3(report->get(2));
  Keyboard.set_key4(report->get(3));
  Keyboard.set_key5(report->get(4));
  Keyboard.set_key6(report->get(5));
  Keyboard.set_modifier(report->getMod());
  Keyboard.send_now();
#endif
}

void FeatherComms::pressWireless(const Report* report){
  static const char cmd_template[] = "AT+BleKeyboardCode=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x";
  char cmd[45] = {0};
  sprintf(cmd, cmd_template,
          report->getMod(),
          report->get(0),
          report->get(1),
          report->get(2),
          report->get(3),
          report->get(4),
          report->get(5));
  bluetooth.println(cmd);
}

void FeatherComms::proportionalDelay(uint8_t data_length, uint8_t multiplier){
  delay(multiplier * getDelay(data_length));
}

uint8_t FeatherComms::getDelay(uint8_t data_length){
  if(use_wired){
    // Little or no delay is needed between presses over USB
    return 0;
  }

  // When sending long words/macros over bluetooth, some letters in the middle
  // get lost unless there's a delay between presses. This seems to help, without
  // slowing down short words too much.
  if(data_length > 10){
    return 2;
  }
  return 1;
}

void FeatherComms::toggleWireless(){
  use_wired ^= 1;
}

#endif

