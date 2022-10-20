#include "uart.hpp"
#include "stm32l010x4.h"

void uart::send_buffer(const char* begin, const char* end){
    for(;begin!=end;begin++){
        USART2->TDR = *begin;
        while( (USART2->ISR & USART_ISR_TC_Msk) == 0);
    }
}

void uart::init(){  
	USART2->BRR = (10000000 /*MHz*/) / (10000/*baud*/); //Using 16 bit oversampling
	
	USART2->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE;
	
	while ((USART2->ISR & USART_ISR_TEACK) == 0);
	while ((USART2->ISR & USART_ISR_REACK) == 0);
    
    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
}
