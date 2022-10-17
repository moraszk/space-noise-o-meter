#pragma once
#include <cstdint>

struct sat_stat{
private:
    constexpr const static uint64_t expected_signature = 0xeddaacdcabbaedda; //Three well-known bands
    uint64_t signature;

    sat_stat(sat_stat&) = delete;
    void operator=(sat_stat&) = delete;
public:
    sat_stat();

    uint16_t bootnum;
    uint8_t unknown_interrupt;
    struct {
        uint16_t frame_error;
        uint16_t noise_error;
        uint16_t overrun_error;
        uint16_t idle;
        uint16_t received_char;
        uint16_t too_long_message;
        uint16_t midpacket_char;
    } uart;
    
    struct {
        uint8_t command_without_run;
        uint8_t unknown_command;
    } communication;
    
    enum class experiment : uint8_t{
        NO_EXPERIMENT = 0,
        ADC_NOISE,
        UART_RATES,
        QUOTES,
        TEMP,
        HALL
    } experiment;
};

extern struct sat_stat sat_status;
