#include "utils.cpp"
#include "utils.hpp"
#include <cstring>
#include <iostream>
#include <string_view>

// out base64 should return only [a-zA-Z0-9+-]
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size != 12)
    return 0;
  std::array<unsigned char, 12> test1 = {Data[0], Data[1], Data[2],  Data[3],
                                         Data[4], Data[5], Data[6],  Data[7],
                                         Data[8], Data[9], Data[10], Data[11]};
  std::array<char, 16> out;
  utils::base64::encode<12>(out, test1.begin());
  for (int i = 0; i < 16; i++) {
    char c = out[i];
    if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || '0' <= c && c <= '9' ||
        c == '+' || c == '-') {
      continue;
    }
    throw std::runtime_error("Invalid character in base64 output");
  }
  return 0; // Values other than 0 and -1 are reserved for future use.
}
