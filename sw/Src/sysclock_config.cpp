#include "stm32l010x4.h"


void SystemClock_Config(void)
{

	//Set Flash latency to 0
	FLASH->ACR |= FLASH_ACR_LATENCY_Pos;

	//wait until the flash latency is 1
	while(!(FLASH->ACR & FLASH_ACR_LATENCY_Pos))
	{
	}
	
	//Set regu voltage scaling
	PWR->CR |= PWR_CR_VOS_0;
	
	//enable HSE bypass
	RCC->CR |= RCC_CR_HSEBYP; 
	
	//Enable HSE 
	RCC->CR |= RCC_CR_HSEON;
	
	//wait until RCC_CR_HSERDY is 1
	while(!(RCC_CR_HSERDY))
	{
	}
	
	//Set AHB Prescalar 
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	
	//Set APB1 prescalar
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;
	
	//Set APB2 prescalar
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	//configure the system clock source
	RCC->CFGR |= RCC_CFGR_SW_HSE;
	
	
	//wait till system clock is ready
	while (!(RCC_CFGR_SWS & RCC_CFGR_SWS_HSE  ))
	{
	}
	
	//wait 1ms
	//...
	
	//Configure USARTx clock source
	RCC->CCIPR |= (uint32_t)((RCC_CCIPR_USART2SEL << 16U) | 0x00000000U) ;
	
}	
