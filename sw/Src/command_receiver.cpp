#include "CommandReceiver.hpp"
#include "stat.h"
#include <cstdio>
#include "stm32l010x4.h"

CommandReceiver::command last_comm;
bool last_comm_processed=false;

void USART2_IRQHandler(void) {
    static enum class rxsate {WAITNEWPACKET, MIDDLE} state = rxsate::WAITNEWPACKET;
    static std::array<char,rx_buffer_size> new_msg_buffer = { 0 };
    static size_t index = 0;
    
    if(LL_USART_IsActiveFlag_FE(USART6)){
        sat_stat.uart.frame_error++;
    }
    if(LL_USART_IsActiveFlag_NE(USART6)){
        sat_stat.uart.noise_error++;
    }
    if(LL_USART_IsActiveFlag_ORE(USART6)){
        sat_stat.uart.overrun_error++;
    }
    if(LL_USART_IsActiveFlag_IDLE(USART6)){
        sat_stat.uart.idle++;
    }
    
	if (LL_USART_IsActiveFlag_RXNE(USART6)) {
		uint8_t received_char = USART6->DR;
        sat_stat.uart.received_char++;
        switch (state){
            case rxsate::WAITNEWPACKET:
                if(received_char == '$'){
                    index = 0;
                    state = rxsate::MIDDLE;
            case rxsate::MIDDLE:
                    new_msg_buffer[index++] = received_char;
                    if(received_char == '\n'){
                        state=rxsate::WAITNEWPACKET;
                        last_comm = CommandReceiver::command{new_msg_buffer, index};
                    } else if(index == rx_buffer_size){
                        sat_stat.uart.buffer_overflow++;
                        state=rxsate::WAITNEWPACKET;
                    }
                    break;
                } else {
            default:
                    sat_stat.uart.midpackage_garbage++;
                    state=rxsate::WAITNEWPACKET;
                }
        }
	}
}

