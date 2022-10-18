#include "command_sender.hpp"
#include <string_view>
#include <array>
#include "checksum.hpp"
#include "uart.hpp"
#include "utils.hpp"
#include "measure_memory.hpp"
#include "status.hpp"
#include "quotes.hpp"

namespace command_sender{    
    std::array<char, longest_reply.size() + 1> output_buffer; //+1 for the closing zero in C. Just to be safe....
}
