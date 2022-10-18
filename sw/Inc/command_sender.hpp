#pragma once
#include <cstdint>
#include <string_view>
#include <array>

namespace command_sender{
    void sendack(const char* serialstr);
    
    void sendtel(uint8_t serial, const char* payload, uint8_t payload_length);

    const constexpr std::string_view longest_reply = "$SUTEL,1234567890123456789#00*1234\r\n";

    extern std::array<char, longest_reply.size() + 1> output_buffer; //+1 for the closing zero in C. Just to be safe....
}
