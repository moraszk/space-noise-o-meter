#pragma once
#include <cstdint>

namespace command_sender{
    void sendack(const char* serialstr);
    
    void sendtel(uint8_t serial, const char* payload, uint8_t payload_length);
}
