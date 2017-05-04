#ifndef SENDER_H_
#define SENDER_H_

#include <Arduino.h>
#include "auto_config.h"
#include "History.h"
#include "Feedback.h"
#include "Chord.h"
#include "Comms.h"


class Sender{
public:
  Sender(Comms* comms);

  bool sendIfEmpty(Chord* chord);
  void sendPlain(const uint8_t* data, uint8_t data_length, Chord* chord);
  void sendMacro(const uint8_t* data, uint8_t data_length, Chord* chord);
  void sendWord(const uint8_t* data, uint8_t data_length, Chord* chord);
  void sendKey(uint8_t key_code, uint8_t mod_byte);

  void deleteLastWord();

  void setStickymod(uint8_t mod_byte);


private:
  bool isSameAsLastSend(uint8_t key_code, uint8_t mod_byte);
  void setLastSend(uint8_t key_code, uint8_t mod_byte);
  void press(uint8_t key_code, uint8_t mod_byte);


  Comms* comms;
  Feedback* feedback;
  History* history;

  uint8_t stickymod = 0; //For programs that use a key like Insert as a fake modifier
  // TODO store stickymod as a Chord?

  /***** optimized releases *****/
  uint8_t last_sent_keycode = 0;
  uint8_t last_sent_mod_byte = 0;


};

#endif
