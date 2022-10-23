#include "telecommand.hpp"
#include "stm32l010x4.h"
#include "measure_memory.hpp"
#include "status.hpp"
#include "gpio.hpp"

namespace telecommand{

    enum class telecommand : char {
        reboot = 'R',
        zero_stat = 'Z',
        meas_uart = 'U',
        meas_noise = 'N',
        meas_hall = 'H',
        meas_quotes = 'Q',
        meas_temp = 'T',
        meas_no_experiment = 'E',
        hall_vref_on = 'V'
    };

    //cmd example ",A"
    void parse_command(const char* cmd){
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
            case telecommand::meas_noise:
                sat_status.experiment = sat_stat::experiment::ADC_NOISE;
                break;
            case telecommand::meas_hall:
                sat_status.experiment = sat_stat::experiment::HALL;
                break;
            case telecommand::meas_quotes:
                sat_status.experiment = sat_stat::experiment::QUOTES;
                break;
            case telecommand::meas_temp:
                sat_status.experiment = sat_stat::experiment::TEMP;
                break;
            case telecommand::hall_vref_on:
                gpio::hall::on();
                break;
            default:
                sat_status.communication.unknown_command++;
        }
    }
}

