#include "../Src/checksum.cpp"
#include "utils.cpp"
#include "utils.hpp"
#include <cstring>
#include <iostream>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  const char *begin = reinterpret_cast<const char *>(Data);
  uint32_t s = Size;
  checksum::get_checksum(begin, s);
  checksum::get_checksum(begin, begin + Size);
  return 0;
}
