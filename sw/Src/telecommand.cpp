#include "telecommand.hpp"
#include "stm32l010x4.h"
#include "measure_memory.hpp"
#include "status.hpp"
#include "gpio.hpp"

namespace telecommand{

    enum class telecommand : char
    {
        reboot = 'R',
        zero_stat = 'Z',
        meas_uart = 'U',
        meas_noise = 'N',
        meas_hall = 'H',
        meas_quotes = 'Q',
        meas_temp = 'T',
        meas_no_experiment = 'E',
        hall_vref_on = 'V',
        tictactoe0 = '0', // invalid moves result in a loss so the game is over
        tictactoe1 = '1',
        tictactoe2 = '2',
        tictactoe3 = '3',
        tictactoe4 = '4',
        tictactoe5 = '5',
        tictactoe6 = '6',
        tictactoe7 = '7',
        tictactoe8 = '8',
        tictactoe9 = '9',
    };

    //cmd example ",A"
    bool parse_command(const char* cmd){
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
                measure_memory.zero();
                break;
            case telecommand::meas_noise:
                sat_status.experiment = sat_stat::experiment::ADC_NOISE;
                measure_memory.zero();
                measure_memory.adc_noise.center = sat_status.adc.half_vref;
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
            case telecommand::tictactoe0:
            case telecommand::tictactoe1:
            case telecommand::tictactoe2:
            case telecommand::tictactoe3:
            case telecommand::tictactoe4:
            case telecommand::tictactoe5:
            case telecommand::tictactoe6:
            case telecommand::tictactoe7:
            case telecommand::tictactoe8:
            case telecommand::tictactoe9:
                sat_status.tictactoe.move(static_cast<uint8_t>(comm) - static_cast<uint8_t>(telecommand::tictactoe0));
                break;
            default:
                sat_status.communication.unknown_command++;
                return false;
        }
        return true;
    }
}

