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

void History::startEntry(const Chord* new_chord, bool is_anagrammable){
  // Store the chord we're sending, and whether we're allowed to try anagramming
  //  it later (like a word, but not a macro).
  current.init(new_chord, is_anagrammable);
}

void History::endEntry(){
  if (current.getLength() == 0){
    // Nothing to add to history.
    return;
  }
  if(!atEdge(RIGHT)){
    // Split current entry in two, so new entry will be added in the middle.
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
  if(atEdge(LEFT)){
    // About to delete the first letter of a word.
    // Cursor will now be inside the previous word.
    repositionCursor(LEFT, 1);
  }
  Entry* old_entry = getEntryAt(word_position);
  old_entry->decrement();
  if(old_entry->getLength() == 0){
    // If the word's length is now zero, remove it from the history
    remove(word_position);
  }
}


void History::save(SixKeys* keys){
  for(uint8_t i = 0; i < keys->numKeys(); i++){
    saveKeyCode(keys->get(i), keys->getMod());
  }
}

void History::saveKeyCode(uint8_t key_code, uint8_t mod_byte){
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
  else if(shouldKeyClearHistory(key_code, mod_byte)){
    // If certain keys (movement etc) are sent, clear the entire history
    //  so that movement keys etc don't misalign the history
    //  and cause you to delete the wrong characters.
    current.clear();
    clear();
  }
  else if(key_code > 0){
    // If any other non-zero key is sent, increment the current length.
    current.setLastLetter(key_code, mod_byte);
    current.increment();
  }
}

bool History::shouldKeyClearHistory(uint8_t key_code, uint8_t mod_byte){
  // This is a list of non-printing / movement keys that should clear history.
  static const uint8_t reset_keys[] = {
    KEY_UP&0xff, KEY_DOWN&0xff, KEY_HOME&0xff, KEY_END&0xff,
    KEY_PAGE_UP&0xff, KEY_PAGE_DOWN&0xff, KEY_ESC&0xff,
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
      return 1;
    }
  }
  for(uint8_t i = 0; i != reset_mods_length; i++){
    if(mod_byte & reset_mods[i]){
      return 1;
    }
  }
  return 0;
}

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
      if(atEdge(RIGHT)){
        return getEntryAt(cursor.word - 1)->getLength();
      }
      return cursor.letter;
    }
  case WORD_EDGE:
    if(atEdge(direction)){
      return 0;
    }
    return calcDistance(WORD, direction);
  case LIMIT:
    {
      // First, get dist to nearest word boundary.
      uint16_t distance = calcDistance(WORD_EDGE, direction);
      // Then, get all the word lengths from there to the end of stack.
      uint8_t start = (direction == LEFT) ? cursor.word+1  : 0;
      uint8_t end = (direction == LEFT)   ? HISTORY_SIZE-1 : cursor.word-1;
      for(uint8_t i = start; i <= end; i++){
        distance += getEntryAt(i)->getLength();
      }
      return distance;
    }
  default:
    DEBUG1("WARNING: Unknown motion: ");
    DEBUG1_LN(motion);
    return 0;
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
      if(atEdge(LEFT)){
        cursor.word += 1;
        cursor.letter = 0;
      }
      else{
        cursor.letter++;
      }
    }
    else{ // RIGHT
      if(atEdge(RIGHT)){
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

void History::getLastLetterAtCursor(Key* key){
  getEntryAt(cursor.word)->getLastLetter(key);
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

bool History::atEdge(Direction direction){
  bool out;
  if(direction == LEFT){
    out = (getEntryAtCursor()->isClear()
           || cursor.letter >= (getLengthAtCursor() - 1));
  }
  else{ // RIGHT
    out = (cursor.letter == 0);
  }
  return out;
}


bool History::isCursorAtLimit(Direction direction){
  if(direction == LEFT){
    // At the beginning of an entry, and the entry to the left is empty.
    // return atEdge(LEFT) && getEntryAt(cursor.word+1)->isClear();
    return getEntryAtCursor()->isClear() && getEntryAt(cursor.word+1)->isClear();
  }
  else if(direction == RIGHT){
    return atEdge(RIGHT) && (cursor.word == 0);
  }
  else{
    DEBUG1_LN("WARNING: invalid direction");
    return 1;
  }
}

void History::printStack(){
  Key last_key;
  Serial.print("cursor: ");
  Serial.print(cursor.word);
  Serial.print(",");
  Serial.print(cursor.letter);
  Serial.print("\t hist: ");
  for(int i = 0; i < HISTORY_SIZE+PADDING; i++){
    stack[i]->getLastLetter(&last_key);

    Serial.print(stack[i]->getLength());
    Serial.print(" ");
    Serial.print(last_key.key_code);
    Serial.print(" ");
    Serial.print(last_key.mod_byte);
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
