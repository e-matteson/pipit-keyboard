#pragma once

#include <stdint.h>

#include "Chord.h"
#include "Key.h"
#include "auto_config.h"

namespace conf {

uint8_t lookup(const Chord* chord, SeqType type, Key* keys_out);

};
