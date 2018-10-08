#include "util.h"

uint32_t makeMask32(uint8_t length) {
  // The first "length" bits are 1, and the rest are 0
  if (length >= 32) {
    return ~((uint32_t)0);
  }
  return (1 << length) - 1;
}

uint16_t makeMask16(uint8_t length) {
  // The first "length" bits are 1, and the rest are 0
  if (length >= 16) {
    return ~((uint16_t)0);
  }
  return (1 << length) - 1;
}

bool bitToBool(const uint8_t* address, uint32_t bit_offset) {
  uint32_t byte_offset = bit_offset / 8;
  uint8_t local_bit_offset = bit_offset % 8;

  uint8_t byte = address[byte_offset];
  return (byte >> local_bit_offset) & 0x01;
}

uint32_t getUnalignedBits(const uint8_t* address, uint32_t start_bit_offset,
                          uint8_t num_bits) {
  if (num_bits > 32) {
    // Needs to fit in uint32_t!
    DEBUG1_LN("ERROR: getUnalignedBits can only get up to 32 bits!");
    return 0;
  }

  uint32_t out = 0;
  for (int16_t i = num_bits - 1; i >= 0; i--) {
    if (bitToBool(address, start_bit_offset + i)) {
      out |= (1 << i);
    }
  }
  return out;
}

bool areBitsEqual(const uint32_t a, const uint32_t b, uint32_t mask) {
  return (a & mask) == (b & mask);
}

bool isByteMaskSet(const uint8_t mask, const uint8_t byte) {
  return mask == (byte & mask);
}
