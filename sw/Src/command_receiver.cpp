#include "CommandReceiver.hpp"
#include "status.hpp"
#include <cstdio>
#include "stm32l010x4.h"
#include "utils.hpp"
#include "dma.hpp"

utils::ringbuffer<CommandReceiver::mrc_frame, mrc_ingress_buffer_len> CommandReceiver::mrc_ingress_buffer;

extern "C" void USART2_IRQHandler(void);

void USART2_IRQHandler(void) {
    static enum class rxsate {WAITNEWPACKET, MIDDLE} state = rxsate::WAITNEWPACKET;
    static std::array<char,rx_buffer_size> new_msg_buffer = { 0 };
    static size_t index = 0;
    
    if(USART2->ISR & USART_ISR_FE){
        sat_status.uart.frame_error++;
        USART2->ICR = USART_ICR_FECF;
    }
    if(USART2->ISR & USART_ISR_NE){
        sat_status.uart.noise_error++;
        USART2->ICR = USART_ICR_NCF;
    }
    if(USART2->ISR & USART_ISR_ORE){
        sat_status.uart.overrun_error++;
        USART2->ICR = USART_ICR_ORECF;
    }
    if(USART2->ISR & USART_ISR_IDLE){
        sat_status.uart.idle++;
        USART2->ICR = USART_ICR_IDLECF;
    }
    
	if (USART2->ISR & USART_ISR_RXNE){
		uint8_t received_char = USART2->RDR;
        sat_status.uart.received_char++;
        switch (state){
            case rxsate::WAITNEWPACKET:
                if(received_char == '$'){
                    index = 0;
                    state = rxsate::MIDDLE;
            case rxsate::MIDDLE:
                    new_msg_buffer[index++] = received_char;

                    if(received_char == '\r') {
                        dma::start_timer_capture();
                    }

                    if(received_char == '\n'){
                        state=rxsate::WAITNEWPACKET;

                        if( 
                            CommandReceiver::mrc_ingress_buffer.put(
                                    new_msg_buffer, 
                                    index, 
                                    sat_status.timer_capture[2] - sat_status.timer_capture[1],
                                    sat_status.timer_capture[3] - sat_status.timer_capture[2]
                            )
                          )
                        {
                            sat_status.communication.mrc_buffer_overflow++;
                        }
                    } else if(index == rx_buffer_size){
                        sat_status.uart.too_long_message++;
                        state=rxsate::WAITNEWPACKET;
                    }
                    break;
                } else {
                [[fallthrough]];
            default:
                    sat_status.uart.midpacket_char++;
                    state=rxsate::WAITNEWPACKET;
                }
        }
	}
}

