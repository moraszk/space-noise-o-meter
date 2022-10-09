#include "stm32l010x4.h"

void SystemClock_Config(void){
	FLASH->ACR = FLASH_ACR_LATENCY_Pos; //One wait state flash

	//wait until the flash latency is 1
	while(!(FLASH->ACR & FLASH_ACR_LATENCY_Pos)); //???? TODO

	PWR->CR = PWR_CR_VOS_1; //1.5V Core voltage

	//Enable HSE 
	RCC->CR = RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_MSION;
	
	//wait until RCC_CR_HSERDY is 1
	while(!(RCC_CR_HSERDY));
	
	RCC->CR = RCC_CR_HSEON | RCC_CR_HSEBYP; // RCC_CR_MSION -- msi is not needed in operation

	//Set AHB Prescalar 
	RCC->CFGR = RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_SW_HSE;
	
	//wait till system clock is ready
	while (!(RCC_CFGR_SWS & RCC_CFGR_SWS_HSE));

	RCC->APB1ENR = RCC_APB1ENR_USART2EN | RCC_APB1ENR_TIM2EN;
	RCC->IOPENR = RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN | RCC_IOPENR_GPIOCEN;
}
