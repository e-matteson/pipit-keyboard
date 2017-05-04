#include "Pipit.h"

Pipit::Pipit(){
  switches = new Switches();
  lookup = new Lookup();
  comms = new Comms();
  sender = new Sender(comms);
  feedback = new Feedback();
  saved_chord = new Chord(mode);
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
  // delayMicroseconds(50);
  delayMicroseconds(500);
  feedback->updateLED();
}

// TODO re-introduce this when we have a global standby mode
// void Pipit::updateConnection(){
//   if(connection_timer->isDone()){
//     if(!comms->isConnected()){
//       num_disconnect_readings++;
//       connection_timer->setResetValue(CONNECTION_CHECK_DELAY_SHORT);
//       if(num_disconnect_readings > disconnect_readings_threshold){
//         DEBUG1_LN("not connected");
//         feedback->startRoutine(BLE_NO_CONNECTION_ROUTINE);
//       }
//     }
//     else{
//       DEBUG1_LN("connected");
//       connection_timer->setResetValue(CONNECTION_CHECK_DELAY_LONG);
//       num_disconnect_readings = 0;
//     }
//     connection_timer->reset();
//   }
// }

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
  if((data_length=lookup->command(chord, data))){
    doCommand(data[0]);
    feedback->triggerCommand();
    return;
  }

  if(is_paused){
    return;
  }

  // If chord is a known macro, send it and return.
  if((data_length=lookup->macro(chord, data))){
    sender->sendMacro(data, data_length, chord);
    resetLastWord();
    feedback->triggerMacro();
    return;
  }

  // If chord is a known word, send it and return.
  chord->blankWordmods();
  if((data_length=lookup->word(chord, data))){
    sender->sendWord(data, data_length, chord);
    // switches->reuseWordmods(chord)
    storeLastWord(chord);
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
  if((data_length=lookup->plain(chord, data))){
    sender->sendPlain(data, data_length, chord);
    // switches->reuseMods(chord)
    resetLastWord();
    feedback->triggerPlain();
    return;
  }

  if(sender->sendIfEmpty(chord)){
    // Only modifiers were pressed, send them now, and trigger plain key feedback
    feedback->triggerPlain();
    resetLastWord();
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
  if(code == COMMAND_PAUSE){
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

  case COMMAND_DELETE_WORD:
    sender->deleteLastWord();
    break;

  case COMMAND_STICKY_CTRL:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case COMMAND_STICKY_SHIFT:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case COMMAND_STICKY_ALT:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case COMMAND_STICKY_GUI:
    sender->setStickymod(MODIFIERKEY_CTRL & 0xff);
    break;

  case COMMAND_LED_BATTERY:
    feedback->startRoutine(BATTERY_ROUTINE);
    break;

  case COMMAND_LED_COLORS:
    feedback->startRoutine(ALL_COLORS_ROUTINE);
    break;

  case COMMAND_LED_RAINBOW:
    feedback->startRoutine(RAINBOW_ROUTINE);
    break;

  case COMMAND_CYCLE_ANAGRAM:
    cycleAnagram();
    break;

  case COMMAND_DEFAULT_MODE:
    // TODO should anything else change when changing mode?
    mode = mode_enum::DEFAULT_MODE;
    break;

  case COMMAND_LEFT_HAND_MODE:
    mode = mode_enum::LEFT_HAND_MODE;
    break;

  // case COMMAND_KRITA_MODE:
  //   mode = mode_enum::KRITA_MODE;
  //   break;

  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(code);
    break;
  }
}



void Pipit::storeLastWord(Chord* chord){
  was_last_send_a_word = 1;
  saved_chord->copy(chord);
}

void Pipit::resetLastWord(){
  was_last_send_a_word = 0;
}

void Pipit::cycleAnagram(){
  if(!was_last_send_a_word){
    feedback->triggerUnknown();
    return;
  }

  uint8_t original_num = saved_chord->getAnagramNum();
  uint8_t data[MAX_LOOKUP_DATA_LENGTH] = {0};
  uint8_t data_length = 0;

  while (saved_chord->cycleAnagramModifier() != original_num) {
    if((data_length=lookup->word(saved_chord, data))){
      sender->deleteLastWord();
      sender->sendWord(data, data_length, saved_chord);
      feedback->triggerWord();
      return;
    }
  }

  DEBUG1_LN("WARNING: no anagram found");
  feedback->triggerUnknown();
}
