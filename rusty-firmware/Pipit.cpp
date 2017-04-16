#include "Pipit.h"

Pipit::Pipit(){
  comms = new Comms();
  lookup = new Lookup();
  chord = new Chord();
  saved_chord = new Chord();
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
    chord->clear();
    switches->makeChordBytes(chord);
    processChord(chord);
  }
  else if(switches->readyToRelease()){
    // Make sure all keys are released
    if(!is_paused){
      sender->sendKey(0,0);
    }
  }
}

void Pipit::processChord(Chord* new_chord){
  wordhistory->startWord();
  processChordHelper(new_chord);
  wordhistory->endWord();
}

void Pipit::processChordHelper(Chord* new_chord){
  // Lookup the chord in the lookup arrays and perform the corresponding action.
  // last_wordmod should be null, unless called from cycleAnagram().

  // If the chord is all zeros (meaning no switch is pressed),
  //  just send zero and be done with it.
  if(!sender->sendIfEmpty(new_chord)){
    return;
  };
  // uint8_t mod_byte_storage = 0;
  uint8_t data[MAX_LOOKUP_DATA_LENGTH] = {0};
  for(int i = 0; i < MAX_LOOKUP_DATA_LENGTH; i++){
    data[i] = 1;
  }
  uint8_t data_length = 0;
  // uint8_t wordmod_storage[NUM_BYTES_IN_CHORD] = {0};


  // If chord is a known special_function, do it and return.
  if((data_length=lookup->special(new_chord, data))){
    doSpecialFunction(data[0]);
    feedback->triggerSpecial();
    return;
  }

  if(is_paused){
    return;
  }

  // If chord is a known macro, send it and return.
  if((data_length=lookup->macro(new_chord, data))){
    sender->sendMacro(data, data_length, new_chord);
    resetLastWord();
    feedback->triggerMacro();
    return;
  }

  new_chord->blankWordmodCapital();
  new_chord->blankWordmodNospace();

  // If chord is a known word, send it and return.
  if((data_length=lookup->word(new_chord, data))){
    sender->sendWord(data, data_length, new_chord);
    storeLastWord();
    feedback->triggerWord();
    return;
  }
  new_chord->restoreWordmods();

  // Blank out all modifier switches.
  new_chord->blankCtrl();
  new_chord->blankGUI();
  new_chord->blankShift();
  new_chord->blankAlt();

  // If chord is a known plain key, send it and return.
  if((data_length=lookup->plain(new_chord, data))){
    sender->sendPlain(data, data_length, new_chord);
    resetLastWord();
    feedback->triggerPlain();
    return;
  }

  // Else, chord not found anywhere!
  if(!sender->sendIfEmpty(new_chord)){
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

void Pipit::storeLastWord(){
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



/************** Special functions *************/

void Pipit::doSpecialFunction(uint8_t code){
  // First check if we should un-pause, because that's the only special function
  //  we're allowed to do while paused.
  if(code == SPECIAL_PAUSE){
    // toggle temporary disabling of typing
    is_paused ^= 1;
    return;
  }

  if(is_paused){
    // if paused, don't do any of the following functions
    return;
  }
  switch(code){
    /**** add cases for new special_functions here ****/
  case SPECIAL_DELETE_WORD:
    deleteLastWord();
    break;

  case SPECIAL_STICKYMOD:
    // Prepare to send the stickymod key together with the next pressed key,
    //  or abort an unused stickymod.
    sender->setOrAbortStickymod();
    break;

  case SPECIAL_LEFTRIGHT:
    // abuse the stickymod feature to send left and right arrows at the same time
    sender->setOrAbortStickymod(KEY_RIGHT & 0xff);
    sender->sendKey(KEY_LEFT & 0xff, 0);
    sender->sendKey(0,0);
    break;

  case SPECIAL_LED_BATTERY:
    feedback->startRoutine(BATTERY_ROUTINE);
    break;

  case SPECIAL_LED_COLORS:
    feedback->startRoutine(ALL_COLORS_ROUTINE);
    break;

  case SPECIAL_LED_RAINBOW:
    feedback->startRoutine(RAINBOW_ROUTINE);
    break;

  case SPECIAL_CYCLE_ANAGRAM:
    cycleAnagram();
    break;


  default:
    DEBUG1("WARNING: Unknown special function: ");
    DEBUG1_LN(code);
    break;
  }
}


