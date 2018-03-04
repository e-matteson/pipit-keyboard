#include "Sender.h"


Sender::Sender(Comms* comms){
  this->history = new History();
  this->comms = comms;
}

/************* Keypress sending ************/

bool Sender::sendIfEmpty(const Chord* chord){
  // If chord is all zeros, send 0 (with any modifiers) and return 0.
  // Else return 1.
  if (!chord->isEmpty()){
    return 0;
  }
  sendKeyAndMod(0, chord->getModByte());
  return 1;
}

void Sender::sendPlain(const Key* data, uint8_t data_length, const Chord* chord){
  // TODO should we make plain entries anagrammable? For capitalization cycling?
  //  But shift and capital might be on different keys anyway...
  history->startEntry(chord, 0);
  Key key;
  for(uint8_t i = 0; i<data_length; i++){
    // Get the key, followed by the modifier.
    key.copy(data+i);
    key.addMod(chord->getModByte());
    sendKey(&key);
  }
  history->endEntry();
}

void Sender::sendMacro(const Key* data, uint8_t data_length, const Chord* chord){
  history->startEntry(chord, 0);
  Key key;
  for(uint8_t i = 0; i<data_length; i++){
    //  get the key, followed by the modifier.
    key.copy(data+i);
    sendKey(&key);
    delay(comms->proportionalDelay(data_length));
  }
  sendRelease();
  history->endEntry();
}

// void Sender::maybeSendSpace(bool nospaceMod) {
//   // Used for prepending or appending spaces to words, unless the no-space modifier is pressed.
//   if(!nospaceMod){
//     Key key;
//     key.set(KEY_SPACE&0xff, 0);
//     sendKey(&key);
//   }
// }

void Sender::sendWord(const Key* data, uint8_t data_length, Chord* chord){
  Key key;

  if(chord->hasModShorten()) {
    sendBackspace();
  }

  if(chord->hasModDouble()) {
    history->getLastLetterAtCursor(&key);
  }

#if WORD_SPACE_POSITION == 0
  // doubleMod and shortenMod would be kinda useless with a space here...
  // So they should prevent us from ever prepending a space.
  // The chord is edited before being stored in the history, so that the nospace
  // will persist if we cycle the word later.
  if(chord->hasModShorten() || chord->hasModDouble()) {
    chord->setModNospace();
  }
#endif

  history->startEntry(chord, 1);

  if(chord->hasModDouble()) {
    sendKey(&key);
  }

#if WORD_SPACE_POSITION == 0
  // doubleMod and shortenMod would be kinda useless with a space here...
  if(!chord->hasModNospace()){
    sendSpace();
  }
#endif

  // This is the first letter, so capitalize it if necessary
  key.copy(data+0);
  if(chord->hasModCapital()){
    key.addMod(MODIFIERKEY_SHIFT&0xff);
  }
  sendKey(&key);

  for(uint8_t i = 1; i<data_length; i++){
    // This is not the first letter, so send the letter without any modifiers.
    delay(comms->proportionalDelay(data_length));
    sendKey(data+i);
  }

#if WORD_SPACE_POSITION == 1
  if(!chord->hasModNospace()){
    sendSpace();
  }
#endif

  sendRelease();
  history->endEntry();
}


void Sender::sendRelease(){
  sendKeyAndMod(0,0);
}

void Sender::sendBackspace(){
  sendKeyAndMod(KEY_BACKSPACE&0xff, 0);
}

void Sender::sendSpace() {
  sendKeyAndMod(KEY_SPACE&0xff, 0);
}

void Sender::sendKeyAndMod(uint8_t key_code, uint8_t mod_byte){
  Key key;
  key.set(key_code, mod_byte);
  sendKey(&key);
}

void Sender::sendKey(const Key* key){
  Report report;
  report.addKey(key);
  sendReport(&report);
}

void Sender::sendReport(Report* report){
  if(stickymod && !report->isEmpty()){
    report->addMod(stickymod);
    stickymod = 0; // reset stickymod after 1 use
  }
  this->press(report);
  history->save(report);
}

void Sender::setStickymod(uint8_t mod_byte){
  stickymod = stickymod | mod_byte;
}

void Sender::press(const Report* report){
  if(last_report.needsExtraRelease(report)){
    Report empty;
    this->press(&empty); //repeated press, send release first
  }
  if(report->isEmpty() && last_report.isEmpty()){
    return; //repeated release, don't send anything
  }
  last_report.copy(report);

  report->printDebug();

  // Actually send the keypress, over USB or bluetooth:
  this->comms->press(report);
}


