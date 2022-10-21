#include "timer.hpp"
#include "stm32l010x4.h"

void timer::init(void){
	TIM2->CCMR2 = TIM_CCMR2_CC4S_0 | TIM_CCMR2_IC4F_0 | TIM_CCMR2_IC4F_1;
	
	TIM2->CCER = TIM_CCER_CC4E;
	TIM2->DIER = TIM_DIER_CC4DE;
	
	TIM2->CR1 = TIM_CR1_CEN;
}
