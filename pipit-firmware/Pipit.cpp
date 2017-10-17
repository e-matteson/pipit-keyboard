#include "Pipit.h"


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
    /******************************************/
    /**** Add cases for new commands here! ****/
    /******************************************/

  case conf::COMMAND_DEFAULT_MODE:
    mode = conf::mode_enum::DEFAULT_MODE;
    break;

  case conf::COMMAND_LEFT_HAND_MODE:
    mode = conf::mode_enum::LEFT_HAND_MODE;
    break;

  case conf::COMMAND_GAMING_MODE:
    mode = conf::mode_enum::GAMING_MODE;
    break;

  case conf::COMMAND_DELETE_WORD:
    deleteLastWord();
    break;

  case conf::COMMAND_SHORTEN_LAST_WORD:
    move(WORD, LEFT);
    sender->sendBackspace();
    move(WORD, RIGHT);
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
    cycleLastWordAnagram();
    break;

  case conf::COMMAND_CYCLE_CAPITAL:
    cycleLastWordCapital();
    break;

  case conf::COMMAND_STICKY_CTRL:
    sender->setStickymod(MODIFIERKEY_CTRL&0xff);
    break;

  case conf::COMMAND_STICKY_SHIFT:
    sender->setStickymod(MODIFIERKEY_SHIFT&0xff);
    break;

  case conf::COMMAND_STICKY_ALT:
    sender->setStickymod(MODIFIERKEY_ALT&0xff);
    break;

  case conf::COMMAND_STICKY_GUI:
    sender->setStickymod(MODIFIERKEY_GUI&0xff);
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

  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(code);
    break;
  }
}

Pipit::Pipit(){
  switches = new Switches();
  lookup = new Lookup();
  comms = new Comms();
  sender = new Sender(comms);
  feedback = new Feedback();

  loop_timer = new Timer(loop_delay_micros, 1, Timer::MICROSECONDS);
  connection_timer = new Timer(connection_check_delay_long, 1, Timer::MILLISECONDS);
}

void Pipit::setup(){
  switches->setup();
  feedback->startRoutine(BATTERY_ROUTINE);
  // feedback->startRoutine(BOOT_ROUTINE);
  feedback->updateLED();
  comms->setup();
}

void Pipit::loop(){
  switches->update();
  sendIfReady();
  // updateConnection();
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
  sender->sendRelease();
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
    connection_timer->start(connection_check_delay_long);
    return;
  }

  num_disconnect_readings++;
  if(num_disconnect_readings > disconnect_readings_threshold){
    DEBUG1_LN("not connected");
    feedback->startRoutine(BLE_NO_CONNECTION_ROUTINE);
  }
  connection_timer->start(connection_check_delay_short);
}

void Pipit::sendIfReady(){
  // Lookup and send a press or release, if necessary
  bool is_gaming = conf::getMode(mode)->is_gaming;
  if(switches->readyToPress(is_gaming)){
    // Lookup the chord and send the corresponding key sequence.
    if(is_gaming){
      Chord gaming_chords[NUM_MATRIX_POSITIONS];
      for(uint8_t i = 0; i < NUM_MATRIX_POSITIONS; i++){
        gaming_chords[i].setMode(mode);
      }
      uint8_t num_chords = switches->fillGamingChords(gaming_chords);
      processGamingChords(gaming_chords, num_chords);
      return;
    }

    Chord chord(mode);
    switches->fillChord(&chord);
    processChord(&chord);
    return;
  }

  if(switches->readyToRelease(is_gaming)){
    // Make sure all keys are released
    if(!is_paused){
      sender->sendRelease();
    }
  }
}

void Pipit::processChord(Chord* chord){
  // Lookup the chord in the lookup arrays and perform the corresponding action.

  // If no switch is pressed, just send zero and be done with it.
  if(sender->sendIfEmpty(chord)){
    return;
  };

  Key data[MAX_LOOKUP_DATA_LENGTH];
  uint8_t data_length = 0;

  // If chord is a known command, do it and return.
  if((data_length=lookup->get(conf::COMMAND, chord, data))){
    doCommand(data[0].key_code);
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
  chord->extractWordMods();
  chord->extractAnagramMods();
  if((data_length=lookup->get(conf::WORD, chord, data))){
    sender->sendWord(data, data_length, chord);
    switches->reuseMods(chord);
    feedback->triggerWord();
    return;
  }

  chord->restoreAnagramMods();
  chord->restoreWordMods();

  // extract out all modifier switches.
  chord->extractPlainMods();

  // If chord is a known plain key, send it and return.
  if((data_length=lookup->get(conf::PLAIN, chord, data))){
    sender->sendPlain(data, data_length, chord);
    switches->reuseMods(chord);
    feedback->triggerPlain();
    return;
  }

  if(sender->sendIfEmpty(chord)){
    // Only modifiers were pressed, send them now, and trigger plain key feedback
    switches->reuseMods(chord);
    feedback->triggerPlain();
  }
  else{
    // Unknown chord, release all keys
    sender->sendRelease();
    feedback->triggerUnknown();
 }
  DEBUG1_LN("chord not found");
}

void Pipit::processGamingChords(Chord* gaming_chords, uint8_t num_chords){
  // For gaming modes. Only commands, plain_keys, and plain_mods are
  //  supported. Lookup each individual switch, and if they're plain_keys, send
  //  them all together at the end. If any switch is a command, do the command
  //  immediately and ignore the rest of the switches.
  SixKeys keys;
  for(uint8_t i = 0; i < num_chords; i++){
    Chord* chord = gaming_chords+i;
    Key data[MAX_LOOKUP_DATA_LENGTH];
    uint8_t data_length = 0;

    if((data_length=lookup->get(conf::COMMAND, chord, data))){
      // Some key was a command, do that command and nothing else.
      doCommand(data[0].key_code);
      feedback->triggerCommand();
      return;
    }

    if(is_paused){
      return;
    }

    if((data_length=lookup->get(conf::PLAIN, chord, data))){
      if(data_length > 1){
        DEBUG1_LN("WARNING: Extra plain_key data ignored");
      }
      keys.add(data);
      feedback->triggerPlain();
      continue;
    }

    chord->extractPlainMods();
    uint8_t mod_byte = chord->getModByte();
    if(mod_byte){
      keys.addMod(mod_byte);
      continue;
    }
    feedback->triggerUnknown();
  }
  sender->sendKeys(&keys);
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
    sender->sendBackspace();
    // For some reason the backspaces get dropped more easily then word letters
    //  so add a longer delay between sends.
    delay(6*comms->proportionalDelay(count));
  }
}

void Pipit::cycleLastWordCapital(){
  Entry* entry = sender->history->getEntryAtCursor();
  if(!entry->isAnagrammable()){
    feedback->triggerNoAnagram();
    return;
  }
  Chord new_chord;
  new_chord.copy(entry->getChord());
  new_chord.toggleCapital();

  // We need to lookup the chord again, even though only the capitalization is
  // changing, because the history doesn't store the characters in a word.
  Key data[MAX_LOOKUP_DATA_LENGTH];
  uint8_t data_length = 0;
  if((data_length=lookup->get(conf::WORD, &new_chord, data))){
    deleteLastWord();
    sender->sendWord(data, data_length, &new_chord);
    feedback->triggerWord();
    return; // Success
  }
  // The lookup should never fail...
  feedback->triggerNoAnagram();
}

void Pipit::cycleLastWordAnagram(){
  Entry* entry = sender->history->getEntryAtCursor();
  if(!entry->isAnagrammable()){
    feedback->triggerNoAnagram();
    return;
  }
  Chord new_chord;
  new_chord.copy(entry->getChord());
  uint8_t original_num = new_chord.getAnagramNum();

  Key data[MAX_LOOKUP_DATA_LENGTH];
  uint8_t data_length = 0;
  for(uint8_t i = 0; i <= NUM_ANAGRAMS; i++) {
    new_chord.cycleAnagramModifier();
    if(new_chord.getAnagramNum() == original_num){
      // We've tried all the anagram modifiers, stop.
      // (The for loop should stop us too, just in case)
      feedback->triggerNoAnagram();
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
