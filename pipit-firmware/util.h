#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#include "auto_config.h"

uint32_t makeMask32(uint8_t length);
uint16_t makeMask16(uint8_t length);
uint32_t getUnalignedBits(const uint8_t* address, uint32_t start_bit_offset,
                          uint8_t num_bits);
bool areBitsEqual(const uint32_t a, const uint32_t b, uint32_t mask);
bool isByteMaskSet(const uint8_t mask, const uint8_t byte);

#endif
