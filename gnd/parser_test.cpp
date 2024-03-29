#include <iostream>
#include <string_view>
#define private public
#include "status.hpp"
#include "../sw/Src/tictactoe.cpp"

namespace{
    std::string_view constexpr encode_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
    static_assert(encode_table.size() == 64, "Base64 lookup table not 64 long");

    size_t getSerial(const std::string& in){
        auto first = encode_table.find(in[0]);
        auto sec = encode_table.find(in[1]);
        return first * encode_table.size() + sec;
    }

    constexpr size_t chunk_size = 12;
    constexpr size_t number_of_chunks = 4;

    std::array<unsigned char, 3> base64decode(const char* in){
        size_t vals[] = {encode_table.find(in[0]),
        encode_table.find(in[1]),
        encode_table.find(in[2]),
        encode_table.find(in[3]),};

        return
        {
            static_cast<unsigned char>((vals[0] << 2) + (vals[1] >> 4)),
            static_cast<unsigned char>((vals[1] << 4) + (vals[2] >> 2)),
            static_cast<unsigned char>((vals[2] << 6) + (vals[3] >> 0)),
        };
    }
}

sat_stat::sat_stat() = default;

int main(){
    sat_stat parsed;

    union u{
        std::array<char, sizeof(sat_stat)> raw;
        sat_stat parsed;
        u(){};
    } work;

    std::string input;
	while (std::cin >> input){
        std::cout << getSerial(input) << std::endl;

        std::cout << "Serial: " << getSerial(input) << std::endl;

        for(size_t i = 0; i < number_of_chunks; i++){
            auto chunk = base64decode(input.c_str()+2+(i*4));

            std::cout << std::hex << static_cast<unsigned>(chunk[0]) << ' ' << static_cast<unsigned>(chunk[1]) << ' ' << static_cast<unsigned>(chunk[2]) <<  ' ';
            std::copy(chunk.begin(), chunk.begin()+3, reinterpret_cast<unsigned char*>(&work.parsed.bootnum)+(getSerial(input)*chunk_size)+i*3);
        }
        std::cout << std::endl;
    }

    std::cout << "Bootnum: " << static_cast<unsigned>(work.parsed.bootnum) << std::endl;
    std::cout << "Experiment: ";
    switch(work.parsed.experiment){
        case sat_stat::experiment::OFF: std::cout << "OFF"; break;
        case sat_stat::experiment::ADC_NOISE: std::cout << "ADC_NOISE"; break;
        case sat_stat::experiment::UART_RATES: std::cout << "UART_RATES"; break;
        case sat_stat::experiment::TEMP: std::cout << "TEMP"; break;
        case sat_stat::experiment::QUOTES: std::cout << "QUOTES"; break;
        case sat_stat::experiment::HALL: std::cout << "HALL"; break;
    }
    std::cout << std::endl;
    
    //                STM vref [V] ---,                0 degree offset of lm61   -------,    ,----slope of lm61
    std::cout << "Temperature: " << (1.224*work.parsed.adc.temp/work.parsed.adc.vref - 0.6)/.01 << " degree celsius" << std::endl;
    std::cout << "VCC: " << 1.224*(1<<12)/work.parsed.adc.vref << " volts" << std::endl;
    std::cout << "Oscillator: " << (work.parsed.clock ? "SECONDARY" : "PRIMARY") << std::endl;
    std::cout << "Voltage divider: " << (1.224*work.parsed.adc.half_vref/work.parsed.adc.vref) << " volts" << std::endl;
    std::cout << "UART received chars " << work.parsed.uart.received_char << std::endl;
    std::cout << "UART idles " << work.parsed.uart.idle << std::endl;
    std::cout << "UART errors: " << work.parsed.uart.frame_error + work.parsed.uart.midpacket_char + work.parsed.uart.noise_error + work.parsed.uart.overrun_error << std::endl;
    std::cout << "Measure errors: " << work.parsed.measure.errors << std::endl;;
    std::cout << "Comm errors: " << std::dec << static_cast<size_t>(work.parsed.communication.command_without_run) + work.parsed.communication.mrc_buffer_overflow + static_cast<size_t>(work.parsed.communication.unknown_command) << " from wihch unknown command: " << static_cast<size_t>(work.parsed.communication.unknown_command) << std::endl;
    std::cout << "Unkown interrupts: " << static_cast<size_t>(work.parsed.unknown_interrupt) << std::endl;

    std::cout << work.parsed.tictactoe.get_board()[0] << '|' << work.parsed.tictactoe.get_board()[1] << '|' << work.parsed.tictactoe.get_board()[2] << '|' << std::endl << work.parsed.tictactoe.get_board()[3] << '|' << work.parsed.tictactoe.get_board()[4] << '|' << work.parsed.tictactoe.get_board()[5] << '|' << std::endl <<
    work.parsed.tictactoe.get_board()[6] << '|' << work.parsed.tictactoe.get_board()[7] << '|' << work.parsed.tictactoe.get_board()[8] << '|' << std::endl;
    return 0;
}
