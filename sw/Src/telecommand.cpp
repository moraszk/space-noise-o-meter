#include "telecommand.hpp"
#include "core_cm0plus.h"
#include "measure_memory.hpp"
#include "status.hpp"

namespace telecommand{
    
    enum class telecommand : unsigned char {
        reboot = 'R',
        zero_stat = 'Z',
        meas_uart = 'M'
    };
    
    //cmd example ",A"
    void parse_command(const unsigned char* cmd){
        telecommand comm {cmd[1]};
        switch(comm){
            case telecommand::reboot:
                NVIC_SystemReset();
                break;
            case telecommand::zero_stat:
                measure_memory.zero();
                break;
            case telecommand::meas_uart:
                sat_status.experiment = sat_stat::experiment::UART_RATES;
                break;
        }
    }
}

