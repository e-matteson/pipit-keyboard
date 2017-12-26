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
  sendKey(0, chord->getModByte());
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

void Sender::sendWord(const Key* data, uint8_t data_length, const Chord* chord){
  Key key;
  bool capitalMod = chord->hasModCapital();
  bool nospaceMod = chord->hasModNospace();
  bool doubleMod = chord->hasModDouble();

  if(doubleMod) {
    history->getLastLetterAtCursor(&key);
  }

  history->startEntry(chord, 1);

  // TODO doubleMod without nospace is kinda useless...
  if(doubleMod) {
    sendKey(&key);
  }

  // Prepend space to the start of word, unless the no-space modifier is pressed.
  if(!nospaceMod){
    key.set(KEY_SPACE&0xff, 0);
    sendKey(&key);
  }

  // This is the first letter, so capitalize it if necessary
  key.copy(data+0);
  if(capitalMod){
    key.addMod(MODIFIERKEY_SHIFT&0xff);
  }
  sendKey(&key);

  for(uint8_t i = 1; i<data_length; i++){
    // This is not the first letter, so send the letter without any modifiers.
    delay(comms->proportionalDelay(data_length));
    sendKey(data+i);
  }

  sendRelease();
  history->endEntry();
}

void Sender::sendRelease(){
  sendKey(0,0);
}

void Sender::sendBackspace(){
  sendKey(KEY_BACKSPACE&0xff, 0);
}

void Sender::sendKey(uint8_t key_code, uint8_t mod_byte){
  Key key;
  key.set(key_code, mod_byte);
  sendKey(&key);
}

void Sender::sendKey(const Key* key){
  SixKeys keys;
  keys.add(key);
  sendKeys(&keys);
}

void Sender::sendKeys(SixKeys* keys){
  if(stickymod && !keys->isEmpty()){
    keys->addMod(stickymod);
    stickymod = 0; // reset stickymod after 1 use
  }
  this->press(keys);
  history->save(keys);
}

bool Sender::isSameAsLastSend(const SixKeys* keys){
  return last_keys.isEqual(keys);
}

void Sender::setLastSend(const SixKeys* keys){
  last_keys.copy(keys);
}

void Sender::setStickymod(uint8_t mod_byte){
  stickymod = stickymod | mod_byte;
}

void Sender::press(const SixKeys* keys){
  // If this is a repeated press, send a release first to separate them.
  if(isSameAsLastSend(keys)){
    if(keys->isEmpty()){
      return; //repeated release, don't send anything
    }
    SixKeys empty;
    this->press(&empty); //repeated press, send release first
  }
  setLastSend(keys);
  keys->printDebug();

  // Actually send the keypress, over USB or bluetooth:
  this->comms->press(keys);
}


