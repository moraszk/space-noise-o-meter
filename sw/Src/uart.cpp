#include "uart.hpp"
#include "stm32l010x4.h"

void uart::send_buffer(const char* begin, const char* end){
    for(;begin!=end;begin++){
        USART2->TDR = *begin;
        while( (USART2->ISR & USART_ISR_TC_Msk) == 0);
    }
}

void uart::init()
{

	RCC->APB1ENR = RCC_APB1ENR_USART2EN; //enable usart2 clock

	USART2->BRR = 10000;  // Baud rate of 10000, 
	
	USART2->CR1 = USART_CR1_RE; // RE=1.. Enable the Receiver
	USART2->CR1 = USART_CR1_TE;  // TE=1.. Enable Transmitter

	USART2->CR1 = USART_CR1_UE;   // UE = 1... Enable USART
	
	while ((USART2->ISR & USART_ISR_TEACK) == 0);

	while ((USART2->ISR & USART_ISR_REACK) == 0);
}
