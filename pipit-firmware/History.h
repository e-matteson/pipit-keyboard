#ifndef HISTORY_H_
#define HISTORY_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"

// The number of recent words/sends that can be deleted
#define HISTORY_SIZE 20

class History{

public:
  History();
  void update(uint8_t key_code, uint8_t mod_byte);
  int16_t peek();
  int16_t pop();
  void startGroup();
  void endGroup();

private:
  bool shouldKeyResetDeletion(uint8_t key_code, uint8_t mod_byte);
  void clear();
  void push(int16_t value);

  int16_t length_stack[HISTORY_SIZE] = {0};
  int16_t current_group_length = 0;
};


#endif
