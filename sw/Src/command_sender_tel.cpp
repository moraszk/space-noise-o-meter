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
    void sendtel_ll(const char* serial_str, std::array<char, 16>& base64_payload, uint8_t chunkid){
        static const constexpr std::string_view tel_heading = "$SUTEL,";
                
        tel_heading.copy(output_buffer.data(), tel_heading.size());
        
        const std::array<char, 2>& chunkhexstr = utils::char2hex(chunkid);
        output_buffer[tel_heading.size()]= chunkhexstr[0];
        output_buffer[tel_heading.size()+1]= chunkhexstr[1];
        
        __builtin_memcpy(output_buffer.data()+tel_heading.size()+2,
                            base64_payload.data(),
                        base64_payload.size()
        );
        
        output_buffer[tel_heading.size()+base64_payload.size()+2]='#';
        
        output_buffer[tel_heading.size()+base64_payload.size()+1+2]   = serial_str [0];
        output_buffer[tel_heading.size()+base64_payload.size()+1+1+2] = serial_str [1];
        
        output_buffer[tel_heading.size()+base64_payload.size()+2+1+2] = '*';
        
        uint16_t checksum = checksum::get_checksum(
            output_buffer.begin()+1,
            output_buffer.begin()+tel_heading.size()+2+base64_payload.size()+1+2
        );
        
        utils::copyashex(checksum, &output_buffer[tel_heading.size()+3+base64_payload.size()+1+2]);
        
        output_buffer[tel_heading.size()+7+base64_payload.size()+1+2] = '\r';
        output_buffer[tel_heading.size()+8+base64_payload.size()+1+2] = '\n';
        
        uart::send_buffer(output_buffer.data(), output_buffer.data()+tel_heading.size()+9+1+base64_payload.size()+2);
    }
    
    void sendtel(const char* serial_str){
        static size_t chunk_id [[gnu::section(".noinit")]];
        chunk_id++;
        
        const unsigned char * begin;
        std::array<char, 16> payload;
        
        switch(sat_status.experiment){
            case sat_stat::experiment::NO_EXPERIMENT:
                if (chunk_id >= sat_stat__number_of_chunks)
                    chunk_id=0;
                begin = sat_status.getchunk(chunk_id);
                break;
            case sat_stat::experiment::ADC_NOISE:
            case sat_stat::experiment::UART_RATES:
                if (chunk_id >= sat_stat__number_of_chunks + measure_memory.number_of_chunks)
                    chunk_id = 0;
                
               if(chunk_id < sat_stat__number_of_chunks){
                    begin = sat_status.getchunk(chunk_id);
                } else{
                    begin = measure_memory.get_chunk_begin(chunk_id-sat_stat__number_of_chunks);
                }
                break;
            case sat_stat::experiment::QUOTES:
                if (chunk_id >= sat_stat__number_of_chunks + quotes::number_of_chunks)
                    chunk_id = 0;
                
                if(chunk_id < sat_stat__number_of_chunks){
                    begin = sat_status.getchunk(chunk_id);
                } else{
                    begin = quotes::get_chunk(chunk_id-sat_stat__number_of_chunks);
                }
            case sat_stat::experiment::TEMP:
            case sat_stat::experiment::HALL:
            default:
                //TODO
                (void)6;
        }
            
        
        utils::base64::encode<12>(payload, begin);
        
        sendtel_ll(serial_str, payload, chunk_id);
    }
}
