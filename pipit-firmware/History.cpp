#include "History.h"


History::History(){
  // Fill up the stack with new chords. We'll copy their member values around,
  //  instead of creating or destroying chord objects.
  for(uint8_t i = 0; i < HISTORY_SIZE; i++){
    // Assume mode 0 exists and is a reasonable default
    stack[i] = new Chord();
  }
}

void History::startGroup(const Chord* new_chord, bool is_anagrammable){
  // Store the chord we're sending, and whether we're allowed to try anagramming
  //  it later (like a word, but not a macro).
  current.copy(new_chord);
  current.setAnagrammable(is_anagrammable);
}

void History::endGroup(){
  if (current.getNumKeys() != 0){
    // If any printed/deletable keys were sent
    //   push the number to the history.
    push(&current);
  }
}

void History::push(const Chord* new_chord){
  // Push a chord to the front of the stack.
  for(uint8_t i = HISTORY_SIZE-1; i != 0; i--){
    stack[i]->copy(stack[i-1]);
  }
  stack[0]->copy(new_chord);
}

int16_t History::pop(){
  // Remove the chord at the front of the stack. Return its num_keys_sent.
  uint8_t out = stack[0]->getNumKeys();
  for(uint8_t i = 0; i != HISTORY_SIZE-1; i++){
    stack[i]->copy(stack[i+1]);
  }
  stack[HISTORY_SIZE-1]->clear();
  return out;
}

Chord* History::peek(){
  // Return a pointer to the chord at the front of stack.
  return stack[0];
}

void History::clear(){
  // Set all history entries to zero.
  for(uint8_t i = 0; i != HISTORY_SIZE; i++){
    stack[i]->clear();
  }
}

void History::update(uint8_t key_code, uint8_t mod_byte){
  // Update the stack when key_code and mod_byte are sent.
  if(key_code == (KEY_BACKSPACE&0xff)){
    if(stack[0]->getNumKeys() > 0){
      // if previous length is non-zero, decrement it
      stack[0]->decrementNumKeys();
      if(stack[0]->getNumKeys() == 0){
        // If previous length is now zero, pop if off the stack
        // And if this chord was just a backspace, it pops itself
        pop();
      }
    }
  }
  else if(shouldKeyResetDeletion(key_code, mod_byte)){
    // If certain keys (movement etc) are sent, reset entire history to zeroes
    //  so that movement keys etc don't misalign the history
    //  and cause you to delete the wrong characters.
    // TODO how will this interact with moving back a word?
    current.clear();
    clear();
  }
  else if(key_code > 0){
    // If any other non-zero key is sent, increment the current length.
    // current_group_length++;
    current.incrementNumKeys();
  }
}

bool History::shouldKeyResetDeletion(uint8_t key_code, uint8_t mod_byte){
  // This is a list of non-printing / movement keys that should reset deletion history.
  static const uint8_t reset_keys[] = {
    KEY_UP&0xff, KEY_DOWN&0xff, KEY_LEFT&0xff, KEY_RIGHT&0xff, KEY_HOME&0xff,
    KEY_END&0xff, KEY_PAGE_UP&0xff, KEY_PAGE_DOWN&0xff, KEY_ESC&0xff,
    KEY_TAB&0xff, KEY_CAPS_LOCK&0xff, KEY_PRINTSCREEN&0xff,
    KEY_SCROLL_LOCK&0xff, KEY_DELETE&0xff, KEY_NUM_LOCK&0xff, KEY_F1&0xff,
    KEY_F2&0xff, KEY_F3&0xff, KEY_F4&0xff, KEY_F5&0xff, KEY_F6&0xff, KEY_F7&0xff,
    KEY_F8&0xff, KEY_F9&0xff, KEY_F10&0xff, KEY_F11&0xff, KEY_F12&0xff
  };

  static const uint8_t reset_mods[] = {
    MODIFIERKEY_GUI&0xff, MODIFIERKEY_ALT&0xff, MODIFIERKEY_CTRL&0xff
  };

  static const uint8_t reset_keys_length = sizeof(reset_keys)/sizeof(reset_keys[0]);
  static const uint8_t reset_mods_length = sizeof(reset_mods)/sizeof(reset_mods[0]);

  for(uint8_t i = 0; i != reset_keys_length; i++){
    if(key_code == reset_keys[i]){
      return true;
    }
  }
  for(uint8_t i = 0; i != reset_mods_length; i++){
    if(mod_byte & reset_mods[i]){
      return true;
    }
  }
  return false;
}

void History::printStack(){
  Serial.print("hist: ");
  for(int i = 0; i < HISTORY_SIZE; i++){
    Serial.print(stack[i]->getNumKeys());
    Serial.print(":");
    Serial.print(stack[i]->isAnagrammable());
    Serial.print(", ");
  }
  Serial.println("");
}
