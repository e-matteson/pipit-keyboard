#include "Pipit.h"


void Pipit::doCommand(uint8_t code){
  // First check if we should un-pause, because that's the only command
  //  we're allowed to do while paused.
  if(code == conf::command_enum::COMMAND_PAUSE){
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

  case conf::command_enum::COMMAND_DEFAULT_MODE:
    mode = conf::mode_enum::DEFAULT_MODE;
    break;

  case conf::command_enum::COMMAND_WINDOWS_MODE:
    mode = conf::mode_enum::WINDOWS_MODE;
    break;

  case conf::command_enum::COMMAND_LEFT_HAND_MODE:
    mode = conf::mode_enum::LEFT_HAND_MODE;
    break;

  case conf::command_enum::COMMAND_GAMING_MODE:
    mode = conf::mode_enum::GAMING_MODE;
    break;

  case conf::command_enum::COMMAND_DELETE_WORD:
    deleteLastWord();
    break;

  case conf::command_enum::COMMAND_SHORTEN_LAST_WORD:
    move(WORD, LEFT);
    sender->sendBackspace();
    move(WORD, RIGHT);
    break;

  case conf::command_enum::COMMAND_LEFT_WORD:
    move(WORD, LEFT);
    break;

  case conf::command_enum::COMMAND_LEFT_LIMIT:
    move(LIMIT, LEFT);
    break;

  case conf::command_enum::COMMAND_RIGHT_WORD:
    move(WORD, RIGHT);
    break;

  case conf::command_enum::COMMAND_RIGHT_LIMIT:
    move(LIMIT, RIGHT);
    break;

  case conf::command_enum::COMMAND_CYCLE_WORD:
    cycleLastWordAnagram();
    break;

  case conf::command_enum::COMMAND_CYCLE_CAPITAL:
    cycleLastWordCapital();
    break;

  case conf::command_enum::COMMAND_CYCLE_NOSPACE:
    cycleLastWordNospace();
    break;

  case conf::command_enum::COMMAND_STICKY_CTRL:
    sender->setStickymod(MODIFIERKEY_CTRL&0xff);
    break;

  case conf::command_enum::COMMAND_STICKY_SHIFT:
    sender->setStickymod(MODIFIERKEY_SHIFT&0xff);
    break;

  case conf::command_enum::COMMAND_STICKY_ALT:
    sender->setStickymod(MODIFIERKEY_ALT&0xff);
    break;

  case conf::command_enum::COMMAND_STICKY_GUI:
    sender->setStickymod(MODIFIERKEY_GUI&0xff);
    break;

  case conf::command_enum::COMMAND_LED_BATTERY:
    feedback->startRoutine(BATTERY_ROUTINE);
    break;

  case conf::command_enum::COMMAND_LED_COLORS:
    feedback->startRoutine(ALL_COLORS_ROUTINE);
    break;

  case conf::command_enum::COMMAND_LED_RAINBOW:
    feedback->startRoutine(RAINBOW_ROUTINE);
    break;

  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(code);
    break;
  }
}

Pipit::Pipit(){
#ifdef FEATHER_M0_BLE
  comms = new FeatherComms();
#elif defined(TEENSY_LC)
  comms = new TeensyComms();
#endif

  switches = new Switches();
  sender = new Sender(comms);
  feedback = new Feedback();

  // loop_timer = new Timer(loop_delay_micros, 1, Timer::MICROSECONDS);
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
  feedback->updateLED();
  shutdownIfSquished();
  // delay(loop_timer->remaining());
  // loop_timer->start();
  delayMicroseconds(100);
}

void Pipit::shutdownIfSquished(){
  if(!switches->matrix->isSquishedInBackpack()){
    return;
  }
  DEBUG1_LN("WARNING: Switches have been held down too long, you might be inside a backpack.");
  DEBUG1_LN("         Please reboot.");
  // TODO disable other things? like bluetooth?
  switches->matrix->shutdown();
  sender->releaseAll();
  delay(1000);
  exit(0); // Exit the firmware! Must reboot to use keyboard again.
}


void Pipit::sendIfReady(){
  // Lookup and send a press or release, if necessary
  bool is_gaming = conf::isGaming(mode);
  if(switches->readyToPress(is_gaming)){
    // Lookup the chord and send the corresponding key sequence.
    if(is_gaming){
      Chord gaming_switches[NUM_MATRIX_POSITIONS];
      for(uint8_t i = 0; i < NUM_MATRIX_POSITIONS; i++){
        gaming_switches[i].setMode(mode);
      }
      uint8_t num_switches = switches->fillGamingSwitches(gaming_switches);
      processGamingSwitches(gaming_switches, num_switches);
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
      // If you pressed a mix of mods and plain keys, the mod release won't be
      // sent until all keys are up. This lets you hold `alt` and tap `tab` to
      // cycle through windows. The only weird edge cases I'm aware of: holding
      // `tab` and tapping `alt` has the exact same behavior as holding `alt`
      // and tapping `tab`.
      if(switches->anySwitchDown()) {
        sender->releaseNonMods();
      }
      else {
        sender->releaseAll();
      }
    }
  }
}

void Pipit::processChord(Chord* chord){
  // Lookup the chord in the lookup arrays and perform the corresponding action.

  // If no switch is pressed, just send zero and be done with it.
  // (there can't be mods because we haven't extracted them yet)
  if(sender->sendIfEmptyExceptMods(chord)){
    return;
  };

  Key data[MAX_KEYS_IN_SEQUENCE];

  // If chord is a known command, do it and return.
  if(sendIfFound(conf::seq_type_enum::COMMAND, chord, data)){
    doCommand(data[0].key_code);
    return;
  }

  if(is_paused){
    return;
  }

  // If chord is a known macro, send it and return.
  if(sendIfFound(conf::seq_type_enum::MACRO, chord, data)){
    return;
  }

  // If chord is a known word, send it and return.
  chord->extractWordMods();
  chord->extractAnagramMods();
  if(sendIfFound(conf::seq_type_enum::WORD, chord, data)){
    switches->reuseMods(chord);
    return;
  }

  chord->restoreAnagramMods();
  chord->restoreWordMods();
  chord->extractPlainMods();

  // If chord is a known plain key, send it and return.
  if(sendIfFound(conf::seq_type_enum::PLAIN, chord, data)){
    switches->reuseMods(chord);
    return;
  }

  if(sender->sendIfEmptyExceptMods(chord)){
    // Only modifiers were pressed, send them now. (We know that because if the
    // chord was totally empty, it would have been sent earlier)
    switches->reuseMods(chord);
    feedback->trigger(conf::seq_type_enum::PLAIN);
  }
  else{
    // Unknown chord, release all keys
    sender->releaseAll();
    feedback->triggerUnknown();
    DEBUG1_LN("chord not found");
 }
}

void Pipit::processGamingSwitches(Chord* gaming_switches, uint8_t num_switches){
  // For gaming modes. Only commands, plain_keys, and plain_mods are
  //  supported. Lookup each individual switch, and if they're plain_keys, send
  //  them all together at the end. If any switch is a command or macro, handle it
  //  immediately and ignore the rest of the switches.
  Report report;
  report.is_gaming = true;
  for(uint8_t i = 0; i < num_switches; i++){
    Key data[MAX_KEYS_IN_SEQUENCE];

    Chord* chord = gaming_switches+i;
    if(sendIfFound(conf::seq_type_enum::COMMAND, chord, data)){
      doCommand(data[0].key_code);
      return;
    }

    if(is_paused){
      return;
    }

    if(sendIfFound(conf::seq_type_enum::MACRO, chord, data)){
      return;
    }

    uint8_t data_length = 0;
    if((data_length=conf::lookup(chord, conf::seq_type_enum::PLAIN, data))){
      if(data_length > 1){
        DEBUG1_LN("WARNING: Extra plain_key data ignored");
      }
      report.addKey(data);
      report.addMod(chord->getModByte());
      feedback->trigger(conf::seq_type_enum::PLAIN);
      continue;
    }

    feedback->triggerUnknown();
  }
  sender->sendReport(&report);
}



/********** High-level editing commands **********/

void Pipit::move(Motion motion, Direction direction){
  uint16_t count = sender->history->calcDistance(motion, direction);

  for(int16_t i = 0; i < count; i++){
    if(direction == LEFT) {
      sender->sendLeftArrow();
    }
    else{
      sender->sendRightArrow();
    }
    comms->proportionalDelay(count, 6);
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
    comms->proportionalDelay(count, 6);
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
  new_chord.cycleCapital();

  // We need to lookup the chord again, even though only the capitalization is
  // changing, because the history doesn't store the characters in a word.
  Key data[MAX_KEYS_IN_SEQUENCE];
  if(sendIfFoundForCycling(conf::seq_type_enum::WORD, &new_chord, data)) {
    return; // Success
  }
  if(sendIfFoundForCycling(conf::seq_type_enum::PLAIN, &new_chord, data)) {
    return; // Success
  }
  feedback->triggerNoAnagram();
}

void Pipit::cycleLastWordNospace(){
  // TODO share code with cycleLastWordCapital
  Entry* entry = sender->history->getEntryAtCursor();
  if(!entry->isAnagrammable()){
    feedback->triggerNoAnagram();
    return;
  }

  Chord new_chord;
  new_chord.copy(entry->getChord());
  new_chord.cycleNospace();

  // We need to lookup the chord again, even though only the capitalization is
  // changing, because the history doesn't store the characters in a word.
  Key data[MAX_KEYS_IN_SEQUENCE];
  if(sendIfFoundForCycling(conf::seq_type_enum::WORD, &new_chord, data)) {
    return; // Success
  }
  if(sendIfFoundForCycling(conf::seq_type_enum::PLAIN, &new_chord, data)) {
    return; // Success
  }
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

  Key data[MAX_KEYS_IN_SEQUENCE];
  for(uint8_t i = 0; i <= NUM_ANAGRAMS; i++) {
    new_chord.cycleAnagram();
    if(new_chord.getAnagramNum() == original_num){
      // We've tried all the anagram modifiers, stop.
      // (The for loop should stop us too, just in case)
      feedback->triggerNoAnagram();
      return; // Fail
    }
    if(sendIfFoundForCycling(conf::seq_type_enum::WORD, &new_chord, data)) {
      return; // Success
    }
    if(sendIfFoundForCycling(conf::seq_type_enum::PLAIN, &new_chord, data)) {
      return; // Success
    }
    // Else, this anagram mod wasn't found, try the next one right away.
  }
}

uint8_t Pipit::sendIfFound(conf::seq_type_enum type, Chord* chord, Key* data) {
  return sendIfFoundHelper(type, chord, data, 0);
}

uint8_t Pipit::sendIfFoundForCycling(conf::seq_type_enum type, Chord* chord, Key* data) {
  return sendIfFoundHelper(type, chord, data, 1);
}

uint8_t Pipit::sendIfFoundHelper(conf::seq_type_enum type, Chord* chord, Key* data, bool delete_first) {
  // TODO renam data -> keys
  uint8_t data_length = conf::lookup(chord, type, data);
  if(data_length){
    if(delete_first) {
      deleteLastWord();
    }
    sender->sendType(type, data, data_length, chord);
    feedback->trigger(type);
    return data_length; // Success
  }
  return 0; // Fail
}
