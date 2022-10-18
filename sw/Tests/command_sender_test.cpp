#include <iostream>
#include "uart.hpp"
#include "command_sender.hpp"

#include "command_sender_ack.cpp"
#include "checksum.hpp"
#include "checksum.cpp"
#include "utils.cpp"
#include "command_sender.cpp"

#include <string>

std::string test = {};

void uart::send_buffer(const char* begin, const char* end){
    test = {begin, end};
}


int main(){
    char serial[] = "FF";
    
    command_sender::sendack(serial);
    
    /*for(char c: test){
        std::cout << utils::char2hex(c)[0] << utils::char2hex(c)[1] << ' ';
    }*/
    
    if (test != "$SUACK#FF*3128\r\n")
        return -1;
    
    
    
    return 0;
}
