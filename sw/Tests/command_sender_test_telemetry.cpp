#include <iostream>
#include "uart.hpp"
#include "command_sender.hpp"

#include "../Src/command_sender_tel.cpp"
#include "../Src/utils.cpp"
#include "../Src/quotes.cpp"
#include "checksum.hpp"
#include "../Src/checksum.cpp"
#include "../Src/command_sender.cpp"
#include "../Src/measure_memory.cpp"

//TODO include file
sat_stat sat_status;

sat_stat::sat_stat(){
    __builtin_bzero(this, sizeof(decltype(*this)));
    this->signature = expected_signature;
}


#include <string>

std::string test = {};

void uart::send_buffer(const char* begin, const char* end){
    test = {begin, end};
}


int main(){
    sat_status.bootnum=50;
    
    char serial[] = "FF";
    
    /*std::cout << test << std::endl;
    for(char c: test){
        std::cout << utils::char2hex(c)[0] << utils::char2hex(c)[1] << ' ';
    }
    std::cout << std::endl;*/
    
    //          ,------the chunk counter starts from 1
    for(int i = 1; i< sat_stat__number_of_chunks;i++)
        command_sender::sendtel(serial);
    
    command_sender::sendtel(serial);
    //std::cout << test << std::endl;
    if (test != "$SUTEL,00MgAAAAAAAAAAAAAA#FF*4411\r\n")
        return -1;
    
    command_sender::sendtel(serial);
    //std::cout << test << std::endl;
    if (test == "$SUTEL,00MgAAAAAAAAAAAAAA#FF*4411\r\n")
        return -1;
        
    return 0;
}
