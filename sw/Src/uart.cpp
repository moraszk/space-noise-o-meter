#include "uart.hpp"
#include "stm32l010x4.h"

void uart::send_buffer(const char* begin, const char* end){
    for(;begin!=end;begin++){
        USART2->TDR = *begin;
        while( (USART2->ISR & USART_ISR_TC_Msk) == 0);
    }
}
