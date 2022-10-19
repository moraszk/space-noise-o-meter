#include "../Src/checksum.cpp"
#include "../Src/utils.cpp"
#include "checksum.hpp"
#include "command.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

#define class struct

#include "CommandReceiver.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (rx_buffer_size == 0)
    throw std::runtime_error("rx_buffer_size is 0");
  if (Size > 19)
    return 0;

  char str[Size + 1];
  memcpy(str, reinterpret_cast<const char *>(Data), Size);
  str[Size] = 0;

  std::string t1str(str);

  if (rx_buffer_size <= Size)
    return 0;

  const CommandReceiver::mrc_frame t1(t1str);

  if (!t1.isValid()) {
    return 0;
  }

  t1.getSize();
  t1.getChecksum();
  t1.getDestinition();
  t1.getCommand();
  t1.calculate_checksum();
  return 0;
}
