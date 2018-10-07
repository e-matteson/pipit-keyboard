#include "Pipit.h"

void Pipit::setup(){
  switches.setup();
  sender.setup();
  feedback.setup();
  feedback.startRoutine(LEDRoutine::Battery);
  feedback.updateLED();
}

void Pipit::loop(){
  switches.update();
  sendIfReady();
  feedback.updateLED();
  shutdownIfSquished();
  delayMicroseconds(100);
}

/// If you define a new command in the settings file, you must add a case for it here!
void Pipit::doCommand(const Key* data, uint8_t length){
  if(length == 0 || data == NULL) {
    DEBUG1_LN("WARNING: invalid command");
    return;
  }

  conf::Command command = static_cast<conf::Command>(data[0].key_code);

  // First check if we should un-pause, because that's the only command
  //  we're allowed to do while paused.
  if(command == conf::Command::command_pause){
    // toggle temporary disabling of typing
    is_paused ^= 1;
    return;
  }
  if(is_paused){
    return;
  }

  switch(command){
    /******************************************/
    /**** Add cases for new commands here! ****/
    /******************************************/

  case conf::Command::command_delete_word:
    sender.deleteLastWord();
    break;

  case conf::Command::command_shorten_last_word:
    sender.move(Motion::Word, Direction::Left);
    sender.backspace();
    sender.move(Motion::Word, Direction::Right);
    break;

  case conf::Command::command_left_word:
    sender.move(Motion::Word, Direction::Left);
    break;

  case conf::Command::command_left_limit:
    sender.move(Motion::Limit, Direction::Left);
    break;

  case conf::Command::command_right_word:
    sender.move(Motion::Word, Direction::Right);
    break;

  case conf::Command::command_right_limit:
    sender.move(Motion::Limit, Direction::Right);
    break;

  case conf::Command::command_cycle_word:
    cycleLastWord(CycleType::Anagram);
    break;

  case conf::Command::command_cycle_capital:
    cycleLastWord(CycleType::Capital);
    break;

  case conf::Command::command_cycle_nospace:
    cycleLastWord(CycleType::Nospace);
    break;

  case conf::Command::command_sticky_ctrl:
    sender.setStickymod(MODIFIERKEY_CTRL&0xff);
    break;

  case conf::Command::command_sticky_shift:
    sender.setStickymod(MODIFIERKEY_SHIFT&0xff);
    break;

  case conf::Command::command_sticky_alt:
    sender.setStickymod(MODIFIERKEY_ALT&0xff);
    break;

  case conf::Command::command_sticky_gui:
    sender.setStickymod(MODIFIERKEY_GUI&0xff);
    break;

  case conf::Command::command_led_battery:
    feedback.startRoutine(LEDRoutine::Battery);
    break;

  case conf::Command::command_led_colors:
    feedback.startRoutine(LEDRoutine::AllColors);
    break;

  case conf::Command::command_led_rainbow:
    feedback.startRoutine(LEDRoutine::Rainbow);
    break;

  case conf::Command::command_toggle_wireless:
    sender.comms.toggleWireless();
    feedback.startRoutine(LEDRoutine::ToggleWireless);
    break;

  case conf::Command::command_scroll_down:
    sender.comms.moveMouse(0,0,-1,0);
    break;

  case conf::Command::command_scroll_up:
    sender.comms.moveMouse(0,0,1,0);
    break;

  case conf::Command::command_pan_left:
    sender.comms.moveMouse(0,0,0,-1);
    break;

  case conf::Command::command_pan_right:
    sender.comms.moveMouse(0,0,0,1);
    break;

  case conf::Command::command_switch_to:
    // This takes an argument specifying which mode to switch to.
    if(length != 2) {
      DEBUG1_LN("WARNING: Wrong number of args for command_switch_to");
      return;
    }
    mode = static_cast<conf::Mode>(data[1].key_code);
    break;

  default:
    DEBUG1("WARNING: Unknown command: ");
    DEBUG1_LN(command);
    break;
  }
}



/// Lookup and send a press or release, if necessary
void Pipit::sendIfReady(){
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
      // is that after pressing `alt+tab', holding `tab` and tapping `alt` has
      // the exact same behavior as holding `alt` and tapping `tab`.
      if(switches.anySwitchDown()) {
        sender.releaseNonMods();
      }
      else {
        sender.releaseAll();
      }
    }
  }
}

/// Search for the chord in all of the lookup arrays of every sequence type, and
/// perform the appropriate action if it's found. For non-gaming modes only -
/// see `processGamingChords()` instead.
void Pipit::processChord(Chord* chord) {
  // If no switch is pressed, just send zero and be done with it.
  // (There can't be mods because we haven't extracted them yet)
  if(sender.sendIfEmptyExceptMods(chord)){
    return;
  };

  // Prepare to store data from the lookup table
  Key data[MAX_KEYS_IN_SEQUENCE];

  // If chord is a known command, do it and return.
  if(uint8_t len = sendIfFound(conf::SeqType::Command, chord, data)){
    doCommand(data, len);
    return;
  }

  if(is_paused){
    return;
  }

  // If chord is a known macro, send it and return.
  if(sendIfFound(conf::SeqType::Macro, chord, data)){
    return;
  }

  // Remove word modifiers from the explicit representation of the chord before
  // looking for matching words.
  chord->extractWordMods();
  chord->extractAnagramMods();

  // If chord is a known word, send it and return.
  if(sendIfFound(conf::SeqType::Word, chord, data)){
    switches.reuseMods(chord);
    return;
  }

  // It wasn't a word, so put the word modifiers back into the explicit representation.
  // Remove the plain modifiers instead, before looking for matching plain_keys.
  chord->restoreAnagramMods();
  chord->restoreWordMods();
  chord->extractPlainMods();

  // If chord is a known plain key, send it and return.
  if(sendIfFound(conf::SeqType::Plain, chord, data)){
    switches.reuseMods(chord);
    return;
  }

  if(sender.sendIfEmptyExceptMods(chord)) {
    // Only modifiers were pressed, send them now. (We know that because if the
    // chord was totally empty, it would have been sent at the top of this
    // function.)
    switches.reuseMods(chord);
    feedback.trigger(conf::SeqType::Plain);
  }
  else{
    // Unknown chord, release all keys
    sender.releaseAll();
    feedback.triggerUnknown();
    DEBUG1_LN("chord not found");
 }
}

// For gaming modes, which act like a normal keyboard and don't recognize
// chords. Only commands, plain_keys, and plain_mods are supported. Lookup each
// individual switch, and if they're all plain_keys, send them all together at
// the end. If any switch is a command or macro, handle it immediately and
// ignore the rest of the switches.
void Pipit::processGamingSwitches(Chord* gaming_switches, uint8_t num_switches) {
  Report report;
  report.is_gaming = true;
  for(uint8_t i = 0; i < num_switches; i++){
    Key data[MAX_KEYS_IN_SEQUENCE];

    Chord* single_switch = gaming_switches+i;
    if(uint8_t length = sendIfFound(conf::SeqType::Command, single_switch, data)){
      doCommand(data, length);
      return;
    }

    if(is_paused){
      return;
    }

    if(sendIfFound(conf::SeqType::Macro, single_switch, data)){
      return;
    }

    // We can't use sendIfFound() here for plain_keys, because we're adding all
    // plain_keys to the report instead of sending each one immediately.
    if(uint8_t length=conf::lookup(single_switch, conf::SeqType::Plain, data)){
      if(length > 1){
        DEBUG1_LN("WARNING: Extra plain_key data ignored");
      }
      report.addKey(data);
      report.addMod(single_switch->getModByte());
      feedback.trigger(conf::SeqType::Plain);
      continue;
    }

    // Failed to find the chord anywhere
    feedback.triggerUnknown();
  }
  sender.sendReport(&report);
}

// Delete the last word (or more precisely, the output of the last chord), and
// replace it with a modified version. The `cycle_type` argument determines
// whether to modify capitalization, spacing, or the anagram number. If the last
// chord can't be cycled, don't send anything.
void Pipit::cycleLastWord(CycleType cycle_type){
  Entry* entry = sender.history.getEntryAtCursor();
  if(!entry->isAnagrammable()){
    feedback.triggerCyclingFailed();
    return;
  }
  Chord new_chord(*entry->getChord());
  Key data[MAX_KEYS_IN_SEQUENCE];

  static const uint8_t num_anagrams = MAX_ANAGRAM_NUM+1;
  for(uint8_t i = 0; i <= num_anagrams; i++) {
    new_chord.cycle(cycle_type);

    if(sendIfFoundForCycling(conf::SeqType::Word, &new_chord, data)) {
      return; // Success
    }
    if(sendIfFoundForCycling(conf::SeqType::Plain, &new_chord, data)) {
      return; // Success
    }

    if(cycle_type != CycleType::Anagram) {
      // If we're not cycling anagrams, give up after we failed the first time.
      // The loop is here just to look for all the anagrams, but is useless for
      // the other cycling types.
      break;
    }
    // Else, this anagram mod wasn't found, try the next one right away.
  }

  feedback.triggerCyclingFailed();
}

uint8_t Pipit::sendIfFound(conf::SeqType type, Chord* chord, Key* data) {
  return sendIfFoundHelper(type, chord, data, 0);
}

uint8_t Pipit::sendIfFoundForCycling(conf::SeqType type, Chord* chord, Key* data) {
  return sendIfFoundHelper(type, chord, data, 1);
}

uint8_t Pipit::sendIfFoundHelper(conf::SeqType type, Chord* chord, Key* data, bool delete_first) {
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

/// Shutdown to save power if a switch has been held down for a very long time,
/// since that probably means the keyboard is squished against something. This
/// mostly happens with battery-powered models that are left on inside a
/// backpack.
void Pipit::shutdownIfSquished(){
  if(!switches.matrix.isSquishedInBackpack()){
    return;
  }
  DEBUG1_LN("WARNING: Switches have been held down too long, you might be inside a backpack.");
  DEBUG1_LN("         Please reboot.");

  // TODO disable bluetooth as well
  switches.matrix.shutdown();
  sender.releaseAll();
  delay(1000);

  // TODO enter deep sleep instead of looping forever.
  noInterrupts();
  while(1);
}
