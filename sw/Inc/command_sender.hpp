#pragma once
#include <cstdint>
#include <string_view>
#include <array>
#include "command.hpp"

namespace command_sender{
    void sendack(const char* serialstr);
    
    void sendtel(const char* serialstr);

    extern std::array<char, command::longest_reply.size() + 1> output_buffer; //+1 for the closing zero in C. Just to be safe....
}
