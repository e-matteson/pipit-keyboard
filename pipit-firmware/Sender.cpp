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

void Sender::sendType(conf::seq_type_enum type, const Key* data, uint8_t data_length, Chord* chord){
  switch(type) {
    case conf::PLAIN: sendPlain(data, data_length, chord); break;
    case conf::WORD: sendWord(data, data_length, chord); break;
    case conf::MACRO: sendMacro(data, data_length, chord); break;
    default: DEBUG1_LN("seq type cannot be sent");
  }

}

void Sender::sendPlain(const Key* data, uint8_t data_length, const Chord* chord){
  history->startEntry(chord, 1);
  Key key;
  for(uint8_t i = 0; i<data_length; i++){
    // Get the key, followed by the modifier.
    key.copy(data+i);
    key.addMod(chord->getModByte());
    // Let the chord change the key's capitalization, like if cycle_capital was pressed.
    chord->editCaps(&key, 1);
    sendKey(&key);
  }
}

void Sender::sendMacro(const Key* data, uint8_t data_length, const Chord* chord){
  history->startEntry(chord, 0);
  Key key;
  for(uint8_t i = 0; i<data_length; i++){
    //  get the key, followed by the modifier.
    key.copy(data+i);
    sendKey(&key);
    comms->proportionalDelay(data_length, 1);
  }
  sendRelease();
}

void Sender::sendWord(const Key* data, uint8_t data_length, Chord* chord){

  if (WORD_SPACE_POSITION == 0) {
    // doubleMod and shortenMod would be kinda useless with a space here...
    // So they should prevent us from ever prepending a space.
    // The chord is edited before being stored in the history, so that the nospace
    // will persist if we cycle the word later.
    if(chord->hasModShorten() || chord->hasModDouble()) {
      chord->setModNospace();
    }
  }

  if(chord->hasModShorten()) {
    sendBackspace();
    comms->proportionalDelay(data_length, 1);
  }

  Key key;
  if(chord->hasModDouble()) {
    // First, get the letter we want to double from the old history entry.
    history->getLastLetterAtCursor(&key);
  }

  // Then, send the letter we want to double, as part of the new history entry.
  history->startEntry(chord, 1);
  if(chord->hasModDouble()) {
    sendKey(&key);
    comms->proportionalDelay(data_length, 1);
  }

  if (WORD_SPACE_POSITION == 0) {
    if(!chord->hasModNospace()){
      sendSpace();
      comms->proportionalDelay(data_length, 1);
    }
  }

  Key new_data[data_length];
  memcpy(new_data, data, data_length*sizeof(Key));
  chord->editCaps(new_data, data_length);

  for(uint8_t i = 0; i<data_length; i++){
    sendKey(new_data+i);
    comms->proportionalDelay(data_length, 1);
  }

  if (WORD_SPACE_POSITION == 1){
    if(!chord->hasModNospace()){
      sendSpace();
      comms->proportionalDelay(data_length, 1);
    }
  }

  sendRelease();
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


