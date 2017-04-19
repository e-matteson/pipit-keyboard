#include "History.h"


History::History(){
}

void History::startGroup(){
  current_group_length = 0;
}

void History::endGroup(){
  if (current_group_length){
    // If any printed/deletable keys were sent, or the chord was unknown,
    //   push the number to the history.
    push(current_group_length);
  }
}

void History::push(int16_t value){
  // Push a value to the front of length_stack.
  for(uint8_t i = HISTORY_SIZE-1; i != 0; i--){
    length_stack[i] = length_stack[i-1];
  }
  length_stack[0] = value;
}

int16_t History::pop(){
  // Pop and return the value at the front of length_stack.
  uint8_t front = length_stack[0];
  for(uint8_t i = 0; i != HISTORY_SIZE-1; i++){
    length_stack[i] = length_stack[i+1];
  }
  length_stack[HISTORY_SIZE-1] = 0;
  return front;
}

int16_t History::peek(){
  // Return the value at the front of length_stack.
  return length_stack[0];
}

bool History::peekIsUnknown(){
  // Return the value at the front of length_stack.
  return length_stack[0] == -1;
}

void History::clear(){
  // Set all history entries to zero.
  for(uint8_t j = 0; j != HISTORY_SIZE; j++){
    length_stack[j] = 0;
  }
}

void History::update(uint8_t key_code, uint8_t mod_byte){
  // Update the length_stack when key_code and mod_byte are sent.
  if(key_code == (KEY_BACKSPACE&0xff)){
    if(length_stack[0] > 0){
      // if previous length is non-zero, decrement it
      length_stack[0]--;
      if(!length_stack[0]){
        // If previous length is now zero, pop if off the stack
        pop();
      }
    }
  }
  else if(shouldKeyResetDeletion(key_code, mod_byte)){
    // If certain keys (movement etc) are sent, reset entire history to zeroes
    //  so that movement keys etc don't misalign the history
    //  and cause you to delete the wrong characters.
    current_group_length = 0;
    clear();
  }
  else if(key_code){
    // If any other non-zero key is sent, increment the current length.
    current_group_length++;
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



void History::handleUnknown(){
  // -1 means an unknown chord was pressed.
#ifndef ENABLE_UNKNOWN_DELETION
  return;
#endif

#ifdef COLLAPSE_UNKNOWN_DELETIONS
  if(peek() == -1){
    // There's already an unknown on the front of the stack, don't add any more.
    return;
  }
#endif

  // Add the unknown to the deletion history.
  current_group_length = -1;
}

