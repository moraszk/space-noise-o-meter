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
#include "command.hpp"

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
    sat_status.experiment=sat_stat::experiment::UART_RATES;
    
    char serial[] = "FF";
    
    command_sender::sendtel(serial);
    
    //          ,------the chunk counter starts from 1
    for(int i = 1; i< sat_stat__number_of_chunks;i++)
        command_sender::sendtel(serial);
    
    //Now we are adter the sat_stat telemetries
    
    measure_memory.baud_rate.register_measure(command::Destinition::OBC, 0);
    measure_memory.baud_rate.register_measure(command::Destinition::OBC, 1);
    measure_memory.baud_rate.register_measure(command::Destinition::OBC, 2);
    measure_memory.baud_rate.register_measure(command::Destinition::OBC, 3);
    measure_memory.baud_rate.register_measure(command::Destinition::OBC, 4);
    
    for(int i=0;i<60;i++){
        command_sender::sendtel(serial);
        std::cout << test;
    }
    
    return 0;
}
