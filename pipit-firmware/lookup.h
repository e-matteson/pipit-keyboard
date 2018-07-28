#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <Arduino.h>
#include "auto_config.h"
/* #include "conf.h" */
#include "Chord.h"
#include "Key.h"

namespace conf{

  uint8_t lookup(const Chord* chord, seq_type_enum type, Key* keys_out);

};

#endif
