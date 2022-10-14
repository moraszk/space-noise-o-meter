#include "status.hpp"

sat_stat sat_status [[gnu::section(".noinit")]];

#pragma GCC diagnostic ignored "-Wuninitialized"
sat_stat::sat_stat(){
    if(signature!=expected_signature){ //If the memory signiture is broken
        //init the struct with zeroes
        __builtin_bzero(this, sizeof(decltype(*this)));
        this->signature = expected_signature;
    }
    bootnum++;
}
