#include "status.hpp"
#include <cstdint>
#include "utils.hpp"

char* sat_stat::dump(char* begin, uint8_t chunkid){
    chunkid%=number_of_chunks;
    
    char* begin_data = reinterpret_cast<char*>(&sat_status.bootnum);
    std::array<char, chunk_length_in_base64> temp_buff;
    
    utils::base64::encode<chunk_length, char *>(temp_buff, begin_data);
}

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

