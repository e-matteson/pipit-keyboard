#include "Sender.h"

Sender::Sender(Comms* comms){
  this->history = new History();
  this->comms = comms;
}

/************* Keypress sending ************/

bool Sender::sendIfEmpty(Chord* chord){
  // TODO test!
  //  If chord is all zeros, send 0 (with any modifiers) and return 0.
  //  Else return 1.

  if (!chord->isEmpty()){
    return 0;
  }
  sendKey(0, chord->getModByte());
  return 1;
}

void Sender::sendPlain(const uint8_t* data, uint8_t data_length, Chord* chord){
  history->startGroup();
  for(uint8_t i = 0; i<data_length-1; i+=2){
    //  get the key, followed by the modifier.
    sendKey(data[i], chord->getModByte() | data[i+1]);
  }
  history->endGroup();
}

void Sender::sendMacro(const uint8_t* data, uint8_t data_length, Chord* chord){
  history->startGroup();
  for(uint8_t i = 0; i<data_length-1; i+=2){
    //  get the key, followed by the modifier.
    sendKey(data[i], chord->getModByte() | data[i+1]);
    delay(comms->proportionalDelay(data_length));
  }
  sendKey(0,0);
  history->endGroup();
}

void Sender::sendWord(const uint8_t* data, uint8_t data_length, Chord* chord){
  history->startGroup();
  // This is the first letter, so send shift if CAPITALIZATION_MODIFIER pressed.
  bool capitalMod = chord->hasCapitalWordmod();
  bool nospaceMod = chord->hasNospaceWordmod();
  sendKey(data[0],
          (capitalMod) ? MODIFIERKEY_SHIFT : 0);

  for(uint8_t i = 1; i<data_length; i++){
    // This is not the first letter, so send the letter without any modifiers.
    delay(comms->proportionalDelay(data_length));
    sendKey(data[i], 0);
  }

  // Append space to end of word, unless the no-space modifier is pressed.
  if(!(nospaceMod)){
    sendKey(KEY_SPACE&0xff, 0);
  }
  sendKey(0,0);
  history->endGroup();
}

void Sender::sendKey(uint8_t key_code, uint8_t mod_byte){

  DEBUG1("sending key: ");
  DEBUG1(key_code);
  DEBUG1(", mod: ");
  DEBUG1_LN(mod_byte | stickymod);

  if(stickymod && key_code){
    this->press(key_code, mod_byte | stickymod);
    stickymod = 0; // reset stickymod after 1 use
  }

  else{
    this->press(key_code, mod_byte);
  }

  history->update(key_code, mod_byte);
}

bool Sender::isSameAsLastSend(uint8_t key_code, uint8_t mod_byte){
  return ((last_sent_keycode == key_code)
          && (last_sent_mod_byte == mod_byte));
}

void Sender::setLastSend(uint8_t key_code, uint8_t mod_byte){
  last_sent_keycode = key_code;
  last_sent_mod_byte = mod_byte;
}

void Sender::setStickymod(uint8_t mod_byte){
  stickymod = mod_byte;
}

void Sender::press(uint8_t key_code, uint8_t mod_byte){
  // If this is a repeated press, send a release first to separate them.
  if(isSameAsLastSend(key_code, mod_byte)){
    if(!(key_code || mod_byte)){
      return; //repeated release, don't send anything
    }
    this->press(0, 0); //repeated press, send release first
  }
  setLastSend(key_code, mod_byte);

  // Actually send the keypress, over USB or bluetooth:
  this->comms->press(key_code, mod_byte);
}


/************** deletion and history ***************/

void Sender::deleteLastWord(){
  // Delete the last sent key sequence by sending the correct number of backspaces.
  // TODO what happens to word history when mode changes?

  int16_t length = history->peek();
  for(int16_t i = 0; i < length; i++){
    sendKey(KEY_BACKSPACE&0xff, 0);
    // For some reason the backspaces get dropped more easily then word letters
    //  so add a longer delay between sends.
    delay(6*comms->proportionalDelay(length));
  }
}


