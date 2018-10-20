#pragma once

#include <stdint.h>

#include "auto_config.h"
#include "Chord.h"
#include "Key.h"

namespace conf {

uint8_t lookup(const Chord* chord, SeqType type, Key* keys_out);

};
