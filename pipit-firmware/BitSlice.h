#pragma once

#include <cstdint>

// Undefine these arduino macros that conflict with std::min/std::max, breaking other std lib stuff
#undef max
#undef min
#include <algorithm>

template<typename T>
class BitSlice {
public:

  constexpr BitSlice (const T* address_, size_t start_bit_offset_, size_t num_bits_)
    : address(address_), start_bit_offset(start_bit_offset_), num_bits(num_bits_) {
  }

  constexpr BitSlice<T> slice_to(size_t end_index) const {
    return BitSlice<T> (address, start_bit_offset, std::min(end_index, num_bits));
  }

  // Shrink the BitSlice by moving its starting point forward by the given distance.
  void skip(size_t distance) {
    distance = std::min(distance, num_bits);
    num_bits -= distance;
    start_bit_offset += distance;
  }

  constexpr bool test(size_t bit_index) const {
    return address[block_index(bit_index)] & bit_mask(bit_index);
  }

  constexpr size_t size() const {
    return num_bits;
  }

  bool has_prefix(const BitSlice<T>& prefix) const {
    if (prefix.size() > size()) {
      return false;
    }
    return prefix == slice_to(prefix.size());
  }

  // Return true if they're the same length and all their bits are equal. Two
  // empty BitSlices are considered equal.
  bool operator==(const BitSlice<T>& rhs) const {
    if (size() != rhs.size()) {
      return false;
    }
    for(size_t i = 0; i < size(); i++) {
      if (test(i) != rhs.test(i)) {
        return false;
      }
    }
    return true;
  }

private:

  constexpr size_t block_index(size_t bit_index) const {
    return (start_bit_offset + bit_index) / std::numeric_limits<T>::digits;
  }

  constexpr size_t bit_offset(size_t bit_index) const {
    return (start_bit_offset + bit_index) % std::numeric_limits<T>::digits;
  }

  constexpr T bit_mask(size_t bit_index) const {
    return 0x1 << bit_offset(bit_index);
  }

  const T* address;
  size_t start_bit_offset;
  size_t num_bits;
};
