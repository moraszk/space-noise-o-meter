#include "stm32l010x4.h"

extern "C" void SystemClock_Config(void);

void SystemClock_Config(void){
	RCC->CIER = 0x00000000; //Turn off every interrupt
	
	FLASH->ACR = FLASH_ACR_LATENCY; //One wait state flash

	//wait until the flash latency is 1
	while(!(FLASH->ACR & FLASH_ACR_LATENCY));

	PWR->CR = PWR_CR_VOS_1; //1.5V Core voltage

	//Enable HSE
	RCC->CR = RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_MSION;

	//wait until RCC_CR_HSERDY is 1
	while(!(RCC_CR_HSERDY));

	RCC->CR = RCC_CR_HSEON | RCC_CR_HSEBYP; // RCC_CR_MSION -- msi is not needed in operation

	//Set AHB Prescalar
	RCC->CFGR = RCC_CFGR_SW_HSE | RCC_CFGR_SWS_HSE;

	//wait till system clock is ready
	while (!(RCC_CFGR_SWS & RCC_CFGR_SWS_HSE));

	RCC->CCIPR = RCC_CCIPR_USART2SEL_0;
	RCC->IOPENR = RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN | RCC_IOPENR_GPIOCEN;
	RCC->APB1ENR = RCC_APB1ENR_USART2EN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_PWREN;
	RCC->APB2ENR = RCC_APB2ENR_ADC1EN | RCC_APB2ENR_SYSCFGEN;
	RCC->AHBENR = RCC_AHBENR_DMA1EN;
}
