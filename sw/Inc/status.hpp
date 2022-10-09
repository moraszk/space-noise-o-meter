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
    struct {
        uint16_t frame_error;
        uint16_t noise_error;
        uint16_t overrun_error;
        uint16_t idle;
        uint16_t received_char;
        uint16_t too_long_message;
        uint16_t midpacket_char;
    } uart;
};

extern struct sat_stat sat_status;
