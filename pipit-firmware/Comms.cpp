// This is a horrible mess of #ifdefs.
// I'm not sure how else to make the project compile for other boards.

#include "Comms.h"


Comms::Comms(){
#if defined(FEATHER_M0_BLE)
  this->bluetooth = new Adafruit_BluefruitLE_SPI(8, 7, 4);
#endif
}

void Comms::setup(){
  setupBluetooth();
}


void Comms::setupBluetooth(){
  // if we're not using the feather, do nothing
#if defined(FEATHER_M0_BLE)

  bool success = 1;
  success |= bluetooth->begin(0); // arg is verbosity

  // Delete all stored data, or it won't reconnect to paired hosts?!
  // success |= bluetooth->factoryReset();

  bluetooth->echo(false); // Disable command echo
  // TODO does the F() macro do anything?
  // Change name
  success |= bluetooth->sendCommandCheckOK(F( "AT+GAPDEVNAME=pipit" ));
  // Enable keyboard service
  success |= bluetooth->sendCommandCheckOK(F("AT+BleHIDEn=On"));
  // Must perform software reset after enabling a service
  success |= bluetooth->reset();

  // int32_t* reply;
  // success = bluetooth->sendCommandWithIntReply(F("AT+BLEPOWERLEVEL"), reply);
  // Serial.println(*reply);
  if(success){
    DEBUG1_LN("bluetooth setup done");
  }
  else{
    DEBUG1_LN("WARNING: bluetooth setup may have failed");
  }
#endif
}

void Comms::press(const Report* report){
#if defined(TEENSY_LC)

  Keyboard.set_key1(report->get(0));
  Keyboard.set_key2(report->get(1));
  Keyboard.set_key3(report->get(2));
  Keyboard.set_key4(report->get(3));
  Keyboard.set_key5(report->get(4));
  Keyboard.set_key6(report->get(5));
  Keyboard.set_modifier(report->getMod());
  Keyboard.send_now();

#elif defined(FEATHER_M0_BLE)

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
  bluetooth->println(cmd);

#endif
}

bool Comms::isConnected(){
#if defined(TEENSY_LC)

  warnNoBluetooth();
  return 1;

#elif defined(FEATHER_M0_BLE)

  // "debounce" the connection status, it often reports brief disconnects
  // DEBUG1_LN("checking connection...");
  return bluetooth->isConnected();
#endif
}


void Comms::warnNoBluetooth(){
  DEBUG1_LN("WARNING: Bluetooth not available.");
}

uint8_t Comms::proportionalDelay(uint8_t data_length){
#if defined(TEENSY_LC)
  // Little or no delay is needed between presses over USB
  return 1;

#elif defined(FEATHER_M0_BLE)
  // When sending long words/macros over bluetooth, some letters in the middle
  // get lost unless there's a delay between presses. This seems to help, without
  // slowing down short words too much.
  if(data_length > 10){
    return 3;
  }
  else{
    return 1;
  }

#endif
}
