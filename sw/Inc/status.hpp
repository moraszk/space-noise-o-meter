#pragma once
#include <cstdint>

struct sat_stat{
private:
    constexpr const static uint64_t expected_signature = 0xeddaacdcabbaedda; //Three well-known bands
    uint64_t signature;
public:
    uint16_t bootnum;

    sat_stat();
    sat_stat(sat_stat&) = delete;
    void operator=(sat_stat&) = delete;
};

extern volatile struct sat_stat sat_status;
