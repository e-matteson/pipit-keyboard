#include "Pipit.h"

Pipit::Pipit(){
  comms = new Comms();
  lookup = new Lookup();
  saved_chord = new Chord(mode);
  wordhistory = new WordHistory();

  switches = new Switches();
  feedback = new Feedback();
  sender = new Sender(wordhistory, comms);
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
  delayMicroseconds(50);
  feedback->updateLED();
}


// void Pipit::updateConnection(){
//   if(timers->connectionCheck()->isDone()){
//     if(!comms->isConnected()){
//       num_disconnect_readings++;
//       timers->connectionCheck()->setResetValue(CONNECTION_CHECK_DELAY_SHORT);
//       if(num_disconnect_readings > disconnect_readings_threshold){
//         DEBUG1_LN("not connected");
//         feedback->startRoutine(BLE_NO_CONNECTION_ROUTINE);
//       }
//     }
//     else{
//       DEBUG1_LN("connected");
//       timers->connectionCheck()->setResetValue(CONNECTION_CHECK_DELAY_LONG);
//       num_disconnect_readings = 0;
//     }
//     timers->connectionCheck()->reset();
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
  wordhistory->startWord();
  processChordHelper(chord);
  wordhistory->endWord();
}

void Pipit::processChordHelper(Chord* chord){
  // Lookup the chord in the lookup arrays and perform the corresponding action.
  // last_wordmod should be null, unless called from cycleAnagram().

  // If the chord is all zeros (meaning no switch is pressed),
  //  just send zero and be done with it.
  if(!sender->sendIfEmpty(chord)){
    return;
  };

  // TODO why did I initialize data to 1's? just debugging?
  uint8_t data[MAX_LOOKUP_DATA_LENGTH] = {0};
  for(int i = 0; i < MAX_LOOKUP_DATA_LENGTH; i++){
    data[i] = 1;
  }
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

  chord->blankWordmodAnagrams();
  chord->blankWordmodCapital();
  chord->blankWordmodNospace();

  // If chord is a known word, send it and return.
  if((data_length=lookup->word(chord, data))){
    sender->sendWord(data, data_length, chord);
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
    resetLastWord();
    feedback->triggerPlain();
    return;
  }

  // Else, chord not found anywhere!
  if(!sender->sendIfEmpty(chord)){
    // Only modifiers were pressed, send them now, and trigger plain key feedback
    feedback->triggerPlain();
    resetLastWord();
  }
  else{
    // Unknown chord, release all keys
    sender->sendKey(0,0);
    wordhistory->handleUnknown();
    feedback->triggerUnknown();
 }
  DEBUG1_LN("chord not found");
}

void Pipit::resetLastWord(){
  was_last_send_a_word = 0;
}

void Pipit::storeLastWord(Chord* chord){
  was_last_send_a_word = 1;
  saved_chord->copy(chord);
}

void Pipit::cycleAnagram(){
  if(!was_last_send_a_word){
    return;
  }
  saved_chord->cycleAnagramModifier();
  deleteLastWord();
  processChord(saved_chord);
}

/************** word deletion ***************/

int16_t  Pipit::deleteLastWord(){
  // TODO what happens to word history when mode changes?
  // Delete the last sent key sequence by sending the right number of backspaces.
  int16_t length = wordhistory->peek();

  // TODO nothing outside WordHistory should need to know what -1 means...
  //  But, nothing in WordHistory should call sender
  if(length == -1){
    // Last chord was unknown. Pop stack entry, don't delete anything.
    wordhistory->pop();
  }
  else{
    for(int16_t i = 0; i != length; i++){
      sender->sendKey(KEY_BACKSPACE&0xff, 0);
      // For some reason the backspaces get dropped more easily then word letters
      //  so add a longer delay between sends.
      delay(6*comms->proportionalDelay(length));
    }
  }
  return length;
}



/************** Commands *************/

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
    deleteLastWord();
    break;

  case COMMAND_STICKYMOD:
    // Prepare to send the stickymod key together with the next pressed key,
    //  or abort an unused stickymod.
    sender->setOrAbortStickymod();
    break;

  case COMMAND_LEFTRIGHT:
    // abuse the stickymod feature to send left and right arrows at the same time
    sender->setOrAbortStickymod(KEY_RIGHT & 0xff);
    sender->sendKey(KEY_LEFT & 0xff, 0);
    sender->sendKey(0,0);
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

  case COMMAND_KRITA_MODE:
    mode = mode_enum::KRITA_MODE;
    break;

  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(code);
    break;
  }
}


