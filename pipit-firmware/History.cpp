#include "History.h"


History::History(){
  // Fill up the stack with new entries. We'll copy their member values around,
  //  instead of creating or destroying Entry objects.
  // Add two extra Entries to the end, that will always stay clear and be ignored
  //  insert and remove. This makes it easier to detect when we're at the end
  //  of the history.
  for(uint8_t i = 0; i < HISTORY_SIZE+PADDING; i++){
    // Assume mode 0 exists and is a reasonable default
    stack[i] = new Entry();
  }
}

void History::startGroup(const Chord* new_chord, bool is_anagrammable){
  // Store the chord we're sending, and whether we're allowed to try anagramming
  //  it later (like a word, but not a macro).
  current.init(new_chord, is_anagrammable);
}

void History::endGroup(){
  if (current.getLength() == 0){
    // No printable characters to add to history.
    // TODO how does this interact with macros containing weird characters?
    return;
  }
  if(!isRightAligned()){
    splitAtCursor();
  }
  insertAtCursor(&current);
}

void History::splitAtCursor(){
  uint16_t right_length = cursor.letter;
  uint16_t left_length = getLengthAtCursor() - right_length;

  Entry* left_entry = getEntryAtCursor();
  left_entry->setAnagrammable(0); // Can't anagram a word fragment...
  left_entry->setLength(left_length);

  Entry right_entry;
  right_entry.copy(left_entry);
  right_entry.setLength(right_length);

  insertAtCursor(&right_entry);
  repositionCursor(LEFT, 1);
}

void History::insertAtCursor(Entry* entry){
  // Insert the entry into the stack.
  uint8_t position = cursor.word;
  for(uint8_t i = HISTORY_SIZE-1; i != position; i--){
    stack[i]->copy(stack[i-1]);
  }
  stack[position]->copy(entry);
}

void History::remove(uint16_t word_position){
  // TODO test
  // Update cursor coordinates:
  if(cursor.word == word_position){
    // We're in this word now! Move cursor out of it.
    repositionCursor(LEFT, calcDistance(WORD, LEFT));
  }
  else if(cursor.word > word_position){
    // We're left of the removed entry, update cursor's word index
    cursor.word--;
  }

  // Remove entry from stack, shifting up all entries behind it.
  for(uint8_t i = word_position; i < HISTORY_SIZE-1; i++){
    getEntryAt(i)->copy(getEntryAt(i+1));
  }
  getEntryAt(HISTORY_SIZE-1)->clear();
}

void History::clear(){
  // Consider the current cursor position 0,0
  cursor.word = 0;
  cursor.letter = 0;
  // Set all history entries to zero.
  for(uint8_t i = 0; i != HISTORY_SIZE; i++){
    stack[i]->clear();
  }
}

void History::backspace(){
  uint16_t word_position = cursor.word;
  if(isLeftAligned()){
    // About to delete the first letter of a word.
    // Cursor will now be inside the previous word.
    repositionCursor(LEFT, 1);
    // cursor.word += 1;
    // cursor.letter = 0;
  }
  Entry* old_entry = getEntryAt(word_position);
  old_entry->decrement();
  if(old_entry->getLength() == 0){
    // If the word's length is now zero, remove it from the history
    remove(word_position);
  }
}


void History::update(uint8_t key_code, uint8_t mod_byte){
  // Update the stack when key_code and mod_byte are sent.
  if(key_code == (KEY_BACKSPACE&0xff)){
    backspace();
  }
  else if(key_code == (KEY_LEFT&0xff)){
    repositionCursor(LEFT, 1);
  }
  else if(key_code == (KEY_RIGHT&0xff)){
    repositionCursor(RIGHT, 1);
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
    current.increment();
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

// TODO how to find out distance_moved without actually modifying anything?
// So that we can find out how many left_arrows to send to move back a word,
// but let sendkey modify the stack+cursor. Pass in a copy of the cursor?
// Or make separate functions for computing distances?
// Redesign cursor/stack coords to make distance computation trivial?
// Store Chord as field of HistoryEntry class!
// Each entry stores its first letter's index from origin? Then they all have to
// be updated on push...

uint16_t History::calcDistance(Motion motion, Direction direction){
  // left is positive distance, right is negative
  // int16_t distance = 0;
  if(isCursorAtLimit(direction)){
    return 0;
  }
  switch(motion){
  case CHAR:
    return 1;
  case WORD:
    if(direction == LEFT){
      return getLengthAtCursor() - cursor.letter;
    }
    else{ // RIGHT
      if(isRightAligned()){
        return getEntryAt(cursor.word - 1)->getLength();
      }
      else{
        return cursor.letter;
      }
    }
  default:
    DEBUG1("WARNING: Unknown motion: ");
    DEBUG1_LN(motion);
    break;
  }
}


uint16_t History::repositionCursor(Direction direction, uint16_t distance){
  uint16_t distance_moved = 0;
  for(int i = 0; i < distance; i++){
    if(isCursorAtLimit(direction)){
      clear(); // Erase the history, we don't know what's back there.
      break;
    }
    if(direction == LEFT){
      if(isLeftAligned()){
        cursor.word += 1;
        cursor.letter = 0;
      }
      else{
        cursor.letter++;
      }
    }
    else{ // RIGHT
      if(isRightAligned()){
        cursor.word--;
        cursor.letter = getLengthAtCursor() - 1;
      }
      else{
        cursor.letter--;
      }
    }
    distance_moved++;
  }
  return distance_moved;
}


uint16_t History::getLengthAtCursor(){
  return getEntryAtCursor()->getLength();
}

Entry* History::getEntryAtCursor(){
  return getEntryAt(cursor.word);
}

Entry* History::getEntryAt(uint8_t cursor_word){
  static const uint8_t max = HISTORY_SIZE+PADDING-1;
  if(cursor_word > max){
    DEBUG1("WARNING: invalid history entry index: ");
    DEBUG1_LN(cursor_word);
    cursor_word = max;
  }
  return stack[cursor_word];
}

bool History::isLeftAligned(){
  return (cursor.letter >= (getLengthAtCursor() - 1)
          || getEntryAtCursor()->isClear());
}

bool History::isRightAligned(){
  return cursor.letter == 0;
}


bool History::isCursorAtLimit(Direction direction){
  if(direction == LEFT){
    // At the beginning of an entry, and the entry to the left is empty.
    // return isLeftAligned() && getEntryAt(cursor.word+1)->isClear();
    return getEntryAtCursor()->isClear() && getEntryAt(cursor.word+1)->isClear();
  }
  else if(direction == RIGHT){
    return isRightAligned() && (cursor.word == 0);
  }
  else{
    DEBUG1_LN("WARNING: invalid direction");
    return 1;
  }
}

void History::printStack(){
  Serial.print("cursor: ");
  Serial.print(cursor.word);
  Serial.print(",");
  Serial.print(cursor.letter);
  Serial.print("\t hist: ");
  for(int i = 0; i < HISTORY_SIZE+PADDING; i++){
    Serial.print(stack[i]->getLength());
    // Serial.print(":");
    // Serial.print(stack[i]->isAnagrammable());
    Serial.print(", ");
  }
  Serial.println("");
}

void History::printCursor(){
  Serial.print("cursor: ");
  Serial.print(cursor.word);
  Serial.print(",");
  Serial.println(cursor.letter);
}
