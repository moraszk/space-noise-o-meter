#pragma once
#include <cstdint>
#include "utils.hpp"

struct sat_stat;
extern struct sat_stat sat_status;

struct sat_stat{
private:
    constexpr const static uint64_t expected_signature = 0xeddaacdcabbaedda; //Three well-known bands
    uint64_t signature;

    sat_stat(sat_stat&) = delete;
    void operator=(sat_stat&) = delete;
    
public:
    static const constexpr std::size_t chunk_length = 12;
    static const constexpr std::size_t chunk_length_in_base64 = chunk_length * 4 / 3;
    
    sat_stat();

    uint8_t bootnum;
    uint8_t unknown_interrupt;
    struct {
        uint8_t frame_error;
        uint8_t noise_error;
        uint8_t overrun_error;
        uint8_t too_long_message;
        uint8_t midpacket_char;
        uint16_t received_char;
        uint16_t idle;
    } uart;
    
    uint8_t clock;
    
    struct {
        uint8_t command_without_run : 4;
        uint8_t unknown_command : 4;
    } communication;
    
    enum class experiment : uint8_t{
        NO_EXPERIMENT = 0,
        ADC_NOISE,
        UART_RATES,
        QUOTES,
        TEMP,
        HALL
    } experiment;
        
    const unsigned char * getchunk(const std::size_t chunk){
        unsigned char* begin_data = reinterpret_cast<unsigned char*>(&sat_status.bootnum);
        return begin_data + (chunk_length*chunk);
    }
};

const constinit std::size_t sat_stat__number_of_chunks = 
    utils::round_up(
        (sizeof(sat_stat)-sizeof(uint64_t)), 
        sat_stat::chunk_length
    );
