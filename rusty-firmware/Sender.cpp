#include "Sender.h"

Sender::Sender(WordHistory* wordhistory, Comms* comms){
  this->wordhistory = wordhistory;
  this->comms = comms;
}

/************* Keypress sending ************/

uint8_t Sender::sendIfEmpty(Chord* chord){
  // TODO test!
  //  If chord is all zeros, send 0 (with any modifiers) and return 0.
  //  Else return 1.

  if (!chord->isEmpty()){
    return 1;
  }
  sendKey(0, chord->getModByte());
  return 0;
}

void Sender::sendPlain(const uint8_t* data, uint8_t data_length, Chord* chord){
  for(uint8_t i = 0; i<data_length-1; i+=2){
    //  get the key, followed by the modifier.
    sendKey(data[i], chord->getModByte() | data[i+1]);
  }
}

void Sender::sendMacro(const uint8_t* data, uint8_t data_length, Chord* chord){
  for(uint8_t i = 0; i<data_length-1; i+=2){
    //  get the key, followed by the modifier.
    sendKey(data[i], chord->getModByte() | data[i+1]);
    delay(comms->proportionalDelay(data_length));
  }
  sendKey(0,0);
}

void Sender::sendWord(const uint8_t* data, uint8_t data_length, Chord* chord){
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
}

void Sender::sendKey(uint8_t key_code, uint8_t mod_byte){

  DEBUG1("sending key: ");
  DEBUG1(key_code);
  DEBUG1(", mod: ");
  DEBUG1_LN(mod_byte);

  if(stickymod && key_code){
    // For programs that use a key like Insert as a fake modifier.
    // Don't send the stickymod yet if the keycode is zero
    // The stickymod MUST be sent slightly before the other key
    this->press(0, stickymod,  mod_byte);
    delay(1);
    this->press(key_code, stickymod,  mod_byte);
    // unset stickymod after 1 use
    stickymod = 0;
  }
  else{
    this->press(key_code, 0, mod_byte);
  }

  // Update word length history, for word deletion.
  wordhistory->update(key_code, mod_byte);
}

bool Sender::isSameAsLastSend(uint8_t key_code1, uint8_t key_code2, uint8_t mod_byte){
  return ((last_sent_keycode1 == key_code1)
          && (last_sent_keycode2 == key_code2)
          && (last_sent_mod_byte == mod_byte));
}

void Sender::setLastSend(uint8_t key_code1, uint8_t key_code2, uint8_t mod_byte){
  last_sent_keycode1 = key_code1;
  last_sent_keycode2 = key_code2;
  last_sent_mod_byte = mod_byte;
}

void Sender::setOrAbortStickymod(uint8_t key_code){
  // set stickymod to any key
  stickymod = stickymod ? 0 : key_code;
}

void Sender::setOrAbortStickymod(){
  // set stickymod to its default key
  setOrAbortStickymod(STICKYMOD_KEY & 0xff);
}

void Sender::press(uint8_t key_code1, uint8_t key_code2, uint8_t mod_byte){
  // If this is a repeated press, send a release first to separate them.
  if(isSameAsLastSend(key_code1, key_code2, mod_byte)){
    if(!(key_code1 || key_code2 || mod_byte)){
      return; //repeated release, don't send anything
    }
    this->press(0, 0, 0); //repeated press, send release first
  }
  setLastSend(key_code1, key_code2, mod_byte);

  // Actually send the keypress, over USB or bluetooth:
  this->comms->press(key_code1, key_code2, mod_byte);
}

