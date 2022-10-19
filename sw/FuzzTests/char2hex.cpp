#include "utils.cpp"
#include "utils.hpp"
#include <cstring>
#include <iostream>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size != 1) {
    return 0;
  }
  const unsigned char in = Data[0];
  std::array<char, 2> out = utils::char2hex(in);

  char const hex_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                              '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  if (hex_chars[(in & 0xF0) >> 4] != out[0] || hex_chars[in & 0x0F] != out[1]) {
    throw std::runtime_error("char2hex failed");
  }

  return 0; // Values other than 0 and -1 are reserved for future use.
}
