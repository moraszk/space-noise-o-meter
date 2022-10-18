#pragma once
#include <cstdint>

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
        
    //! Dumps what is above to a base64 string
    // @param begin: the string where the result should be dumped
    // @return end: a pointer pointing after the last char
    char* dump(char* begin, uint8_t chunkid);
};

extern struct sat_stat sat_status;


consteval size_t round_up(size_t whole, size_t partlen){
    if(whole % partlen == 0)
        return whole/partlen;
    else
        return whole/partlen +1;
}
static const constexpr std::size_t sat_status:number_of_chunks = 
    round_up(
        (sizeof(sat_stat)-sizeof(uint64_t)), 
        sat_status::chunk_length
    );
