#pragma once
#include <cstdint>

struct sat_stat{
private:
    constexpr const static uint64_t expected_signature = 0xeddaacdcabbaedda; //Three well-known bands
    uint64_t signature;
public:
    uint16_t bootnum;

    sat_stat(){
        if(signature!=expected_signature){ //If the memory signiture is broken
            //init the struct with zeroes
            __builtin_bzero(this, sizeof(decltype(*this)));
        }
        bootnum++;
    }
};

extern volatile struct sat_stat sat_status;
