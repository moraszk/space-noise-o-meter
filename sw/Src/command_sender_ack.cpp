#include "command_sender.hpp"
#include <string_view>
#include <array>
#include "checksum.hpp"
#include "uart.hpp"
#include "utils.hpp"

namespace command_sender{
    void sendack(const char* serial_str){
        static const constexpr std::string_view ack_heading = "$SUACK#";
        
        ack_heading.copy(output_buffer.data(), ack_heading.size());
        
        output_buffer[ack_heading.size()]   = serial_str [0];
        output_buffer[ack_heading.size()+1] = serial_str [1];
        
        output_buffer[ack_heading.size()+2] = '*';
        
        uint16_t checksum = checksum::get_checksum(
            output_buffer.begin()+1,
            output_buffer.begin()+ack_heading.size()+2
        );
        
        utils::copyashex(checksum, &output_buffer[ack_heading.size()+3]);
        
        output_buffer[ack_heading.size()+7] = '\r';
        output_buffer[ack_heading.size()+8] = '\n';
        
        uart::send_buffer(output_buffer.data(), output_buffer.data()+ack_heading.size()+9);
    }
}
