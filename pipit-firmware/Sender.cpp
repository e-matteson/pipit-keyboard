#include "Sender.h"
#include <Arduino.h>

/************* Editing Commands *********/

void Sender::move(Motion motion, Direction direction) {
  uint16_t count = history.calcDistance(motion, direction);

  for (uint16_t i = 0; i < count; i++) {
    if (direction == Direction::Left) {
      leftArrow();
    } else {
      rightArrow();
    }
  }
}

void Sender::deleteLastWord() {
  // Delete the last sent key sequence by sending the correct number of
  // backspaces.
  move(Motion::WordEdge, Direction::Right);
  uint16_t count = history.calcDistance(Motion::Word, Direction::Left);
  for (uint16_t i = 0; i < count; i++) {
    backspace();
  }
}

/************* Keypress sending ************/

void Sender::sendMods(const Chord* chord) {
  // Send only the chord's mods
  sendKeyAndMod(0, chord->getModByte());
}

void Sender::sendPlain(const Key* keys, uint8_t keys_length,
                       const Chord* chord) {
  history.startEntry(chord, 1);
  // TODO should we modify the input Keys instead of copying to the temporary
  // value?
  Key key;
  for (uint8_t i = 0; i < keys_length; i++) {
    key = keys[i];
    key.addMod(chord->getModByte());
    // Let the chord change the key's capitalization, like if cycle_capital was
    // pressed.
    chord->editCaps(&key, 1);
    sendKey(&key);
  }
}

void Sender::sendMacro(const Key* keys, uint8_t keys_length,
                       const Chord* chord) {
  history.startEntry(chord, 0);
  for (uint8_t i = 0; i < keys_length; i++) {
    sendKey(keys + i);
    // Some applications can't react to keypresses fast enough, pause.
    delay(40);
  }
  releaseAll();
}

// Send the word. May modify the chord - don't use it again after calling this.
void Sender::sendWord(const Key* keys, uint8_t keys_length, Chord* chord) {
  if (conf::SPACE_POS == WordSpacePosition::Before) {
    // doubleMod and shortenMod would be kinda useless with a space here...
    // So they should prevent us from ever prepending a space.
    // The chord is edited before being stored in the history, so that the
    // nospace will persist if we cycle the word later.
    if (chord->hasModShorten() || chord->hasModDouble()) {
      chord->setModNospace();
    }
  }

  if (chord->hasModShorten()) {
    backspace();
  }

  if (chord->hasModDouble()) {
    // First, get the letter we want to double from the old history entry.
    // Then, send it as part of the new history entry.
    Key* doubled_key = history.getLastLetterAtCursor();
    history.startEntry(chord, 1);
    sendKey(doubled_key);
  } else {
    // Just start the new history entry as usual
    history.startEntry(chord, 1);
  }

  if (conf::SPACE_POS == WordSpacePosition::Before) {
    if (!chord->hasModNospace()) {
      space();
    }
  }

  // TODO we only need to copy it if the capitalization is actually changing...
  Key new_keys[keys_length];
  memcpy(new_keys, keys, keys_length * sizeof(Key));
  chord->editCaps(new_keys, keys_length);

  for (uint8_t i = 0; i < keys_length; i++) {
    sendKey(new_keys + i);
  }

  if (conf::SPACE_POS == WordSpacePosition::After) {
    if (!chord->hasModNospace()) {
      space();
    }
  }

  releaseAll();
}

void Sender::releaseAll() { sendKeyAndMod(0, 0); }

void Sender::releaseNonMods() {
  Report mods_only;
  mods_only.copyModsFrom(&last_report);
  sendReport(&mods_only);
}

void Sender::backspace() { sendKeyAndMod(KEY_BACKSPACE & 0xff, 0); }

void Sender::space() { sendKeyAndMod(KEY_SPACE & 0xff, 0); }

void Sender::leftArrow() { sendKeyAndMod(KEY_LEFT & 0xff, 0); }

void Sender::rightArrow() { sendKeyAndMod(KEY_RIGHT & 0xff, 0); }

void Sender::sendKeyAndMod(uint8_t key_code, uint8_t mod_byte) {
  Key key(key_code, mod_byte);
  sendKey(&key);
}

void Sender::sendKey(const Key* key) {
  Report report;
  report.addKey(key);
  sendReport(&report);
}

void Sender::sendReport(Report* report) {
  if (stickymod && !report->isEmpty()) {
    report->addMod(stickymod);
    stickymod = 0;  // reset stickymod after 1 use
  }
  this->press(report);
  history.save(report);
}

void Sender::press(const Report* report) {
  if (last_report.needsExtraRelease(report)) {
    // The same press was repeated twice, so send a release to separate them.
    // Mods can stay pressed / be pressed early, though. That lets alt-tabbing
    // work.
    Report mods_only;
    mods_only.copyModsFrom(report);
    this->press(&mods_only);
  }
  if (report->isEmpty() && last_report.isEmpty()) {
    return;  // repeated release, don't send anything
  }
  last_report = *report;

  report->printDebug();

  // Actually send the keypress, over USB or bluetooth:
  comms.press(report);
}

void Sender::setStickymod(uint8_t mod_byte) { stickymod |= mod_byte; }
