#pragma once

#include <stdint.h>
#include "Chord.h"
#include "Entry.h"
#include "Report.h"
#include "auto_config.h"

// The number of recent words/sends that can be deleted

#define HISTORY_SIZE 5
#define PADDING 2

enum class Direction {
  Left,
  Right,
};

enum class Motion {
  Word,
  WordEdge,
  Char,
  Limit,
};

class History {
 public:
  void save(Report* report);
  void startEntry(const Chord* new_chord, bool is_anagrammable);

  uint16_t calcDistance(Motion motion, Direction direction);

  uint16_t repositionCursor(Direction direction, uint16_t distance);
  void backspace();

  Entry* getEntryAtCursor();
  Key* getLastLetterAtCursor();

  bool atEdge(Direction direction);

 private:
  uint8_t saveKeyCode(uint8_t key_code, uint8_t mod_byte);
  bool isCursorAtLimit(Direction direction);
  Entry* getEntryAt(uint8_t cursor_word);
  uint16_t getLengthAtCursor();
  void remove(uint16_t word_position);
  void insertAtCursor(const Entry* entry);
  void splitAtCursor();
  bool shouldKeyClearHistory(uint8_t key_code, uint8_t mod_byte);
  void clear();
  void pushNewEntryIfNeeded();

  struct Cursor {
    uint8_t word = 0;
    uint8_t letter = 0;
  };

  Cursor cursor;
  Entry stack[HISTORY_SIZE + PADDING];
  Entry new_entry;

  bool has_new_entry_been_pushed = 1;
};
