#include "status.hpp"
#include "stm32l010x4.h"


extern "C" {
    void HardFault_Handler(){
        sat_status.unknown_interrupt++;
        NVIC_SystemReset();
    }
}
