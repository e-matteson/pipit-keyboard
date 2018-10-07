#include "History.h"



void History::startEntry(const Chord* new_chord, bool is_anagrammable){
  // Store the chord we're sending, and whether we're allowed to try anagramming
  //  it later (like a word, but not a macro).
  new_entry.init(new_chord, is_anagrammable);
  has_new_entry_been_pushed = 0;
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
  repositionCursor(Direction::Left, 1);
}

void History::insertAtCursor(Entry* entry){
  if(isCursorAtLimit(Direction::Left)) {
    // There won't be space to add a new entry here, past the end of the stack.
    // Pop the front of the stack to make space.
    remove(0);
  }

  // Insert the entry into the stack.
  uint8_t position = cursor.word;
  for(uint8_t i = HISTORY_SIZE-1; i > position; i--){
    stack[i].copy(stack + (i-1));
  }
  stack[position].copy(entry);
}

void History::remove(uint16_t word_position){
  // Update cursor coordinates:
  if(cursor.word == word_position){
    // We're in this word now! Move cursor out of it.
    repositionCursor(Direction::Left, calcDistance(Motion::Word, Direction::Left));
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
  // Consider the current cursor position to be (0,0), wherever that is.
  cursor.word = 0;
  cursor.letter = 0;
  // Set all history entries to zero.
  for(uint8_t i = 0; i != HISTORY_SIZE; i++){
    stack[i].clear();
  }
}

void History::backspace(){
  uint16_t word_position = cursor.word;
  if(atEdge(Direction::Left)){
    // About to delete the first letter of a word.
    // Cursor will now be inside the previous word.
    repositionCursor(Direction::Left, 1);
  }
  Entry* old_entry = getEntryAt(word_position);
  old_entry->decrement();
  if(old_entry->getLength() == 0){
    // If the word's length is now zero, remove it from the history
    remove(word_position);
  }
}


void History::save(Report* report){
  for(uint8_t i = 0; i < report->numKeys(); i++){
    saveKeyCode(report->get(i), report->getMod());
  }
}

void History::saveKeyCode(uint8_t key_code, uint8_t mod_byte){
  // Update the stack when key_code and mod_byte are sent.
  if(key_code == (KEY_BACKSPACE&0xff)){
    backspace();
  }
  else if(key_code == (KEY_LEFT&0xff)){
    repositionCursor(Direction::Left, 1);
  }
  else if(key_code == (KEY_RIGHT&0xff)){
    repositionCursor(Direction::Right, 1);
  }
  else if(shouldKeyClearHistory(key_code, mod_byte)){
    // If certain keys (movement etc) are sent, clear the entire history
    //  so that movement keys etc don't misalign the history
    //  and cause you to delete the wrong characters.
    new_entry.clear();
    clear();
  }
  else if(key_code > 0){
    // If any other non-zero key is sent, increment the current length.
    pushNewEntryIfNeeded();
    getEntryAtCursor()->setLastLetter(key_code, mod_byte);
    getEntryAtCursor()->increment();
  }
}

void History::pushNewEntryIfNeeded() {
  // We procrastinate on pushing the new empty entry on to the stack until the
  // first time we actually need to increment it. That way, if it's never
  // incremented, we're not left with a crufty empty entry on the stack
  // that we need to find and pop.
  if(has_new_entry_been_pushed) {
    return;
  }

  if(!atEdge(Direction::Right)){
    // Split current entry in two, so new entry will be added in the middle.
    splitAtCursor();
  }
  insertAtCursor(&new_entry);
  has_new_entry_been_pushed = 1;
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
  case Motion::Char:
    return 1;
  case Motion::Word:
    if(direction == Direction::Left){
      return getLengthAtCursor() - cursor.letter;
    }
    else{ // Direction::Right
      if(atEdge(Direction::Right)){
        return getEntryAt(cursor.word - 1)->getLength();
      }
      return cursor.letter;
    }
  case Motion::WordEdge:
    if(atEdge(direction)){
      return 0;
    }
    return calcDistance(Motion::Word, direction);
  case Motion::Limit:
    {
      // First, get dist to nearest word boundary.
      uint16_t distance = calcDistance(Motion::WordEdge, direction);
      // Then, get all the word lengths from there to the end of stack.
      uint8_t start = (direction == Direction::Left) ? cursor.word+1  : 0;
      uint8_t end = (direction == Direction::Left)   ? HISTORY_SIZE-1 : cursor.word-1;
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
    if(direction == Direction::Left){
      if(atEdge(Direction::Left)){
        cursor.word += 1;
        cursor.letter = 0;
      }
      else{
        cursor.letter++;
      }
    }
    else{ // Direction::Right
      if(atEdge(Direction::Right)){
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
  return stack + cursor_word;
}

bool History::atEdge(Direction direction){
  bool out;
  if(direction == Direction::Left){
    out = (getEntryAtCursor()->isClear()
           || cursor.letter >= (getLengthAtCursor() - 1));
  }
  else{ // Direction::Right
    out = (cursor.letter == 0);
  }
  return out;
}


bool History::isCursorAtLimit(Direction direction){
  if(direction == Direction::Left){
    // TODO if we're ever on an empty entry, is that good enough? Could get rid of the 2nd padding.
    // But what if we have an empty entry in the middle we haven't deleted yet.
    return getEntryAtCursor()->isClear() && getEntryAt(cursor.word+1)->isClear();
  }
  else if(direction == Direction::Right){
    return atEdge(Direction::Right) && (cursor.word == 0);
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
    stack[i].getLastLetter(&last_key);

    Serial.print(stack[i].getLength());
    // Serial.print(" ");
    // Serial.print(last_key.key_code);
    // Serial.print(" ");
    // Serial.print(last_key.mod_byte);
    // Serial.print(":");
    // Serial.print(stack[i].isAnagrammable());
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
