
void TIM2_Init(void)
{		
		RCC->APB1ENR = RCC_APB1ENR_TIM2EN;  //enable TIM2 clock
	
		TIM2->CCMR1 &= ~TIM_CCMR1_CC1S; //clear capture / compare 1 selection bits
		TIM2->CCMR1 = TIM_CCMR1_CC1S_0; //CC1S[1:0] for channel 1
		
		TIM2->CCMR1 = TIM_CCER_CC1P;	//active transition rising edge

		TIM2->CCER = TIM_CCER_CC1E;	//enable capture for channel 1
		
		TIM2->DIER = TIM_DIER_CC1IE;	//allow channel 1 of timer 2 to generate interrupts
		
		TIM2->DIER = TIM_DIER_CC1DE;	// --||-- ... generate DMA request

		TIM2->CR1 = TIM_CR1_CEN; 	//enable timer2 counter
}