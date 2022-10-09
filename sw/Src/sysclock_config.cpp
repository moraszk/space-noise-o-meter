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
	
	
	
	    // RCC pin gpio init
        GPIOC->BSRR = 1 << (0x00000002U);
        
        if((GPIO_MODER_MODE0_1 == GPIO_MODER_MODE0_0 ) || (GPIO_MODER_MODE0_1 == GPIO_MODER_MODE0_1))
            {
                GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEED2_0;	
                    
                GPIOC->OTYPER |= (0x00000000U);	//output mode config
                    
            }
                
                GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
                
                    if(GPIO_MODER_MODE0_1 == GPIO_MODER_MODE0_1)
                    {
                        if(GPIOC < GPIO_BSRR_BS_8)
                        {
                            GPIOC->AFR[0] |= GPIO_AFRL_AFSEL0; //??
                        }
                        else
                        {
                            GPIOC->AFR[1] |= GPIO_AFRH_AFSEL8; //??
                        }
                        
                    }
                
        GPIOC->MODER |= GPIO_MODER_MODE0;
			
                
	
	
	
	
	
	
}	