#include "Pipit.h"

#define CONNECTION_CHECK_DELAY_SHORT 3000
#define CONNECTION_CHECK_DELAY_LONG 6000

Pipit::Pipit(){
  switches = new Switches();
  lookup = new Lookup();
  comms = new Comms();
  sender = new Sender(comms);
  feedback = new Feedback();

  loop_timer = new Timer(loop_delay_micros, 1, Timer::MICROSECONDS);
  connection_timer = new Timer(CONNECTION_CHECK_DELAY_LONG, 1, Timer::MILLISECONDS);
}

void Pipit::setup(){
  switches->setup();
  feedback->startRoutine(BOOT_ROUTINE);
  feedback->updateLED();
  comms->setup();
}

void Pipit::loop(){
  switches->update();
  sendIfReady();
  updateConnection();
  feedback->updateLED();
  shutdownIfSquished();
  delayMicroseconds(loop_timer->remaining());
  loop_timer->start();
}

void Pipit::shutdownIfSquished(){
  if(!switches->matrix->isSquishedInBackpack()){
    return;
  }
  DEBUG1_LN("WARNING: Switches have been held down too long, you might be inside a backpack.");
  DEBUG1_LN("         Please reboot.");
  // TODO disable other things? like bluetooth?
  switches->matrix->shutdown();
  sender->sendKey(0,0);
  delay(1000);
  exit(0); // Exit the firmware! Must reboot to use keyboard again.
}

void Pipit::updateConnection(){
  if(!switches->matrix->isInStandby()){
    // Switches have been pressed recently, don't check connection for a while
    connection_timer->start();
    return;
  }
  if(!connection_timer->isDone()){
    return;
  }
  if(comms->isConnected()){
    DEBUG1_LN("connected");
    num_disconnect_readings = 0;
    connection_timer->start(CONNECTION_CHECK_DELAY_LONG);
    return;
  }

  num_disconnect_readings++;
  if(num_disconnect_readings > disconnect_readings_threshold){
    DEBUG1_LN("not connected");
    feedback->startRoutine(BLE_NO_CONNECTION_ROUTINE);
  }
  connection_timer->start(CONNECTION_CHECK_DELAY_SHORT);
}

void Pipit::sendIfReady(){
  // Lookup and send a press or release, if necessary
  if(switches->readyToPress()){
    // Lookup the chord and send the corresponding key sequence.
    Chord chord(mode);
    switches->makeChordBytes(&chord);
    processChord(&chord);
  }
  else if(switches->readyToRelease()){
    // Make sure all keys are released
    if(!is_paused){
      sender->sendKey(0,0);
    }
  }
}

void Pipit::processChord(Chord* chord){
  // Lookup the chord in the lookup arrays and perform the corresponding action.

  // If no switch is pressed, just send zero and be done with it.
  if(sender->sendIfEmpty(chord)){
    return;
  };

  uint8_t data[MAX_LOOKUP_DATA_LENGTH] = {0};
  uint8_t data_length = 0;

  // If chord is a known command, do it and return.
  // if((data_length=lookup->command(chord, data))){
  if((data_length=lookup->get(conf::COMMAND, chord, data))){
    doCommand(data[0]);
    feedback->triggerCommand();
    return;
  }

  if(is_paused){
    return;
  }

  // If chord is a known macro, send it and return.
  if((data_length=lookup->get(conf::MACRO, chord, data))){
    sender->sendMacro(data, data_length, chord);
    feedback->triggerMacro();
    return;
  }

  // If chord is a known word, send it and return.
  chord->blankWordmods();
  if((data_length=lookup->get(conf::WORD, chord, data))){
    sender->sendWord(data, data_length, chord);
    // switches->reuseWordmods(chord)
    feedback->triggerWord();
    return;
  }

  chord->restoreWordmods();

  // Blank out all modifier switches.
  chord->blankCtrl();
  chord->blankGUI();
  chord->blankShift();
  chord->blankAlt();

  // If chord is a known plain key, send it and return.
  if((data_length=lookup->get(conf::PLAIN, chord, data))){
    sender->sendPlain(data, data_length, chord);
    // switches->reuseMods(chord)
    feedback->triggerPlain();
    return;
  }

  if(sender->sendIfEmpty(chord)){
    // Only modifiers were pressed, send them now, and trigger plain key feedback
    feedback->triggerPlain();
  }
  else{
    // Unknown chord, release all keys
    sender->sendKey(0,0);
    feedback->triggerUnknown();
 }
  DEBUG1_LN("chord not found");
}


void Pipit::doCommand(uint8_t code){
  // First check if we should un-pause, because that's the only command
  //  we're allowed to do while paused.
  if(code == conf::COMMAND_PAUSE){
    // toggle temporary disabling of typing
    is_paused ^= 1;
    return;
  }

  if(is_paused){
    // if paused, don't do any of the following functions
    return;
  }
  switch(code){
    /**** add cases for new commands here ****/

  case conf::COMMAND_DELETE_WORD:
    deleteLastWord();
    break;

  case conf::COMMAND_LEFT_WORD:
    move(WORD, LEFT);
    break;

  case conf::COMMAND_LEFT_LIMIT:
    move(LIMIT, LEFT);
    break;

  case conf::COMMAND_RIGHT_WORD:
    move(WORD, RIGHT);
    break;

  case conf::COMMAND_RIGHT_LIMIT:
    move(LIMIT, RIGHT);
    break;

  case conf::COMMAND_CYCLE_WORD:
    cycleLastWord();
    break;

  case conf::COMMAND_STICKY_CTRL:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case conf::COMMAND_STICKY_SHIFT:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case conf::COMMAND_STICKY_ALT:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case conf::COMMAND_STICKY_GUI:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case conf::COMMAND_LED_BATTERY:
    feedback->startRoutine(BATTERY_ROUTINE);
    break;

  case conf::COMMAND_LED_COLORS:
    feedback->startRoutine(ALL_COLORS_ROUTINE);
    break;

  case conf::COMMAND_LED_RAINBOW:
    feedback->startRoutine(RAINBOW_ROUTINE);
    break;

  case conf::COMMAND_DEFAULT_MODE:
    // TODO should anything else change when changing mode?
    mode = conf::mode_enum::DEFAULT_MODE;
    break;

  case conf::COMMAND_LEFT_HAND_MODE:
    mode = conf::mode_enum::LEFT_HAND_MODE;
    break;

  // case conf::COMMAND_KRITA_MODE:
  //   mode = conf::mode_enum::KRITA_MODE;
  //   break;

  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(code);
    break;
  }
}

/********** High-level editing commands **********/

void Pipit::move(Motion motion, Direction direction){
  uint16_t count = sender->history->calcDistance(motion, direction);
  uint8_t key = (direction == LEFT) ? KEY_LEFT&0xff : KEY_RIGHT&0xff;
  for(int16_t i = 0; i < count; i++){
    sender->sendKey(key, 0);
    delay(6*comms->proportionalDelay(count));
  }
}

void Pipit::deleteLastWord(){
  // Delete the last sent key sequence by sending the correct number of backspaces.
  move(WORD_EDGE, RIGHT);
  int16_t count = sender->history->calcDistance(WORD, LEFT);
  for(int16_t i = 0; i < count; i++){
    sender->sendKey(KEY_BACKSPACE&0xff, 0);
    // For some reason the backspaces get dropped more easily then word letters
    //  so add a longer delay between sends.
    delay(6*comms->proportionalDelay(count));
  }
}

void Pipit::cycleLastWord(){
  Entry* entry = sender->history->getEntryAtCursor();
  if(!entry->isAnagrammable()){
    feedback->triggerUnknown();
    return;
  }
  Chord new_chord;
  new_chord.copy(entry->getChord());
  uint8_t original_num = new_chord.getAnagramNum();

  uint8_t data[MAX_LOOKUP_DATA_LENGTH] = {0};
  uint8_t data_length = 0;

  while(1) {
    new_chord.cycleAnagramModifier();
    if(new_chord.getAnagramNum() == original_num){
      // We've tried all the anagram modifiers, stop.
      feedback->triggerUnknown();
      return; // Fail
    }
    if((data_length=lookup->get(conf::WORD, &new_chord, data))){
      // This anagram mod was found!
      deleteLastWord();
      sender->sendWord(data, data_length, &new_chord);
      feedback->triggerWord();
      return; // Success
    }
    // Else, this anagram mod wasn't found, try the next one right away.
  }
}
