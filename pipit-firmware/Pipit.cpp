#include "Pipit.h"


void Pipit::doCommand(const Key* data, uint8_t length){
  if(length == 0 || data == 0) {
    DEBUG1_LN("WARNING: invalid command");
    return;
  }

  conf::command_enum command = (conf::command_enum) data[0].key_code;

  // First check if we should un-pause, because that's the only command
  //  we're allowed to do while paused.
  if(command == conf::command_enum::COMMAND_PAUSE){
    // toggle temporary disabling of typing
    is_paused ^= 1;
    return;
  }
  if(is_paused){
    // if paused, don't do any of the following functions
    return;
  }
  switch(command){
    /******************************************/
    /**** Add cases for new commands here! ****/
    /******************************************/

  case conf::command_enum::COMMAND_DELETE_WORD:
    sender.deleteLastWord();
    break;

  case conf::command_enum::COMMAND_SHORTEN_LAST_WORD:
    sender.move(Motion::WORD, Direction::LEFT);
    sender.backspace();
    sender.move(Motion::WORD, Direction::RIGHT);
    break;

  case conf::command_enum::COMMAND_LEFT_WORD:
    sender.move(Motion::WORD, Direction::LEFT);
    break;

  case conf::command_enum::COMMAND_LEFT_LIMIT:
    sender.move(Motion::LIMIT, Direction::LEFT);
    break;

  case conf::command_enum::COMMAND_RIGHT_WORD:
    sender.move(Motion::WORD, Direction::RIGHT);
    break;

  case conf::command_enum::COMMAND_RIGHT_LIMIT:
    sender.move(Motion::LIMIT, Direction::RIGHT);
    break;

  case conf::command_enum::COMMAND_CYCLE_WORD:
    cycleLastWord(CycleType::CYCLE_ANAGRAM);
    break;

  case conf::command_enum::COMMAND_CYCLE_CAPITAL:
    cycleLastWord(CycleType::CYCLE_CAPITAL);
    break;

  case conf::command_enum::COMMAND_CYCLE_NOSPACE:
    cycleLastWord(CycleType::CYCLE_NOSPACE);
    break;

  case conf::command_enum::COMMAND_STICKY_CTRL:
    sender.setStickymod(MODIFIERKEY_CTRL&0xff);
    break;

  case conf::command_enum::COMMAND_STICKY_SHIFT:
    sender.setStickymod(MODIFIERKEY_SHIFT&0xff);
    break;

  case conf::command_enum::COMMAND_STICKY_ALT:
    sender.setStickymod(MODIFIERKEY_ALT&0xff);
    break;

  case conf::command_enum::COMMAND_STICKY_GUI:
    sender.setStickymod(MODIFIERKEY_GUI&0xff);
    break;

  case conf::command_enum::COMMAND_LED_BATTERY:
    feedback.startRoutine(BATTERY_ROUTINE);
    break;

  case conf::command_enum::COMMAND_LED_COLORS:
    feedback.startRoutine(ALL_COLORS_ROUTINE);
    break;

  case conf::command_enum::COMMAND_LED_RAINBOW:
    feedback.startRoutine(RAINBOW_ROUTINE);
    break;

  case conf::command_enum::COMMAND_TOGGLE_WIRELESS:
    sender.comms.toggleWireless();
    feedback.startRoutine(TOGGLE_WIRELESS_ROUTINE);
    break;

  case conf::command_enum::COMMAND_SCROLL_DOWN:
    sender.comms.moveMouse(0,0,-1,0);
    break;

  case conf::command_enum::COMMAND_SCROLL_UP:
    sender.comms.moveMouse(0,0,1,0);
    break;

  case conf::command_enum::COMMAND_PAN_LEFT:
    sender.comms.moveMouse(0,0,0,-1);
    break;

  case conf::command_enum::COMMAND_PAN_RIGHT:
    sender.comms.moveMouse(0,0,0,1);
    break;

  case conf::command_enum::SWITCH_TO:
    if(length != 2) {
      DEBUG1_LN("WARNING: wrong num of args for switch_to");
      return;
    }
    mode = (conf::mode_enum) data[1].key_code;
    break;
  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(command);
    break;
  }
}


void Pipit::setup(){
  switches.setup();
  sender.setup();
  feedback.setup();
  feedback.startRoutine(BATTERY_ROUTINE);
  feedback.updateLED();
}

void Pipit::loop(){
  switches.update();
  sendIfReady();
  feedback.updateLED();
  shutdownIfSquished();
  delayMicroseconds(100);
}

void Pipit::shutdownIfSquished(){
  if(!switches.matrix.isSquishedInBackpack()){
    return;
  }
  DEBUG1_LN("WARNING: Switches have been held down too long, you might be inside a backpack.");
  DEBUG1_LN("         Please reboot.");
  // TODO disable other things? like bluetooth?
  switches.matrix.shutdown();
  sender.releaseAll();
  delay(1000);
  exit(0); // Exit the firmware! Must reboot to use keyboard again.
}


void Pipit::sendIfReady(){
  // Lookup and send a press or release, if necessary
  bool is_gaming = conf::isGaming(mode);
  if(switches.readyToPress(is_gaming)){
    // Lookup the chord and send the corresponding key sequence.
    if(is_gaming){
      Chord gaming_switches[NUM_MATRIX_POSITIONS];
      for(uint8_t i = 0; i < NUM_MATRIX_POSITIONS; i++){
        gaming_switches[i].setMode(mode);
      }
      uint8_t num_switches = switches.fillGamingSwitches(gaming_switches);
      processGamingSwitches(gaming_switches, num_switches);
      return;
    }

    Chord chord(mode);
    switches.fillChord(&chord);
    processChord(&chord);
    return;
  }

  if(switches.readyToRelease(is_gaming)){
    // Make sure all keys are released
    if(!is_paused){
      // If you pressed a mix of plain mods and plain keys, the mod release
      // won't be sent until all keys are up. This lets you hold `alt` and tap
      // `tab` to cycle through windows. The only weird edge case I'm aware of
      // is that holding `tab` and tapping `alt` has the exact same behavior as
      // holding `alt` and tapping `tab`.
      if(switches.anySwitchDown()) {
        sender.releaseNonMods();
      }
      else {
        sender.releaseAll();
      }
    }
  }
}

void Pipit::processChord(Chord* chord){
  // Lookup the chord in the lookup arrays and perform the corresponding action.

  // If no switch is pressed, just send zero and be done with it.
  // (there can't be mods because we haven't extracted them yet)
  if(sender.sendIfEmptyExceptMods(chord)){
    return;
  };

  Key data[MAX_KEYS_IN_SEQUENCE];

  // If chord is a known command, do it and return.
  if(uint8_t len = sendIfFound(conf::seq_type_enum::COMMAND, chord, data)){
    doCommand(data, len);
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
    switches.reuseMods(chord);
    return;
  }

  chord->restoreAnagramMods();
  chord->restoreWordMods();
  chord->extractPlainMods();

  // If chord is a known plain key, send it and return.
  if(sendIfFound(conf::seq_type_enum::PLAIN, chord, data)){
    switches.reuseMods(chord);
    return;
  }

  if(sender.sendIfEmptyExceptMods(chord)){
    // Only modifiers were pressed, send them now. (We know that because if the
    // chord was totally empty, it would have been sent earlier)
    switches.reuseMods(chord);
    feedback.trigger(conf::seq_type_enum::PLAIN);
  }
  else{
    // Unknown chord, release all keys
    sender.releaseAll();
    feedback.triggerUnknown();
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
    if(uint8_t length = sendIfFound(conf::seq_type_enum::COMMAND, chord, data)){
      doCommand(data, length);
      return;
    }

    if(is_paused){
      return;
    }

    if(sendIfFound(conf::seq_type_enum::MACRO, chord, data)){
      return;
    }

    // TODO why can't we use normal sendIfFound() here? Because we're adding to the report, not sending, right.
    if(uint8_t length=conf::lookup(chord, conf::seq_type_enum::PLAIN, data)){
      if(length > 1){
        DEBUG1_LN("WARNING: Extra plain_key data ignored");
      }
      report.addKey(data);
      report.addMod(chord->getModByte());
      feedback.trigger(conf::seq_type_enum::PLAIN);
      continue;
    }

    feedback.triggerUnknown();
  }
  sender.sendReport(&report);
}


void Pipit::cycleLastWord(CycleType cycle_type){
  Entry* entry = sender.history.getEntryAtCursor();
  if(!entry->isAnagrammable()){
    feedback.triggerNoAnagram();
    return;
  }
  Chord new_chord;
  new_chord.copy(entry->getChord());
  Key data[MAX_KEYS_IN_SEQUENCE];

  static const uint8_t num_anagrams = MAX_ANAGRAM_NUM+1;
  for(uint8_t i = 0; i <= num_anagrams; i++) {
    new_chord.cycle(cycle_type);

    if(sendIfFoundForCycling(conf::seq_type_enum::WORD, &new_chord, data)) {
      return; // Success
    }
    if(sendIfFoundForCycling(conf::seq_type_enum::PLAIN, &new_chord, data)) {
      return; // Success
    }

    if(cycle_type != CycleType::CYCLE_ANAGRAM) {
      // Give up after we failed the first time, if we're not cycling anagrams.
      // The loop is here just to look for all the anagrams, but is useless for
      // the other cycling types.
      feedback.triggerNoAnagram();
      return;
    }
    // Else, this anagram mod wasn't found, try the next one right away.
  }

  // We've tried all the anagram modifiers and failed!
  feedback.triggerNoAnagram();
}

uint8_t Pipit::sendIfFound(conf::seq_type_enum type, Chord* chord, Key* data) {
  return sendIfFoundHelper(type, chord, data, 0);
}

uint8_t Pipit::sendIfFoundForCycling(conf::seq_type_enum type, Chord* chord, Key* data) {
  return sendIfFoundHelper(type, chord, data, 1);
}

uint8_t Pipit::sendIfFoundHelper(conf::seq_type_enum type, Chord* chord, Key* data, bool delete_first) {
  // TODO renam data -> keys

  if(uint8_t length = conf::lookup(chord, type, data)){
    if(delete_first) {
      sender.deleteLastWord();
    }
    sender.sendType(type, data, length, chord);
    feedback.trigger(type);
    return length; // Success
  }
  return 0; // Fail
}
