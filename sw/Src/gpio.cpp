#include "gpio.hpp"

void gpio::init(){
	
            RCC->IOPENR |= RCC_IOPENR_GPIOCEN;		//enable gpio port C clock
            RCC->IOPENR |= RCC_IOPENR_GPIOAEN;		//enable gpio port A clock
            RCC->IOPENR |= RCC_IOPENR_GPIOBEN;		//enable gpio port B clock
            GPIOC->BRR |= GPIO_BSRR_BS_14;			//reset GPIO output pin
		
		
    // hall pin gpio init
        GPIOC->BSRR = 1 << gpio::hall::pin;		
		}
        
    	if((GPIO_MODER_MODE0_0 == GPIO_MODER_MODE0_0 ) || (GPIO_MODER_MODE0_0 == GPIO_MODER_MODE0_1))	
			{
				GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEED2_0 ;	
				
				GPIOC->OTYPER |= (0x00000000U) ;	//output mode config
				
			}
			
				GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
			
				
				GPIOC->MODER |= GPIO_MODER_MODE0;
			
    
    // oscillator pin gpio init 
                GPIOC->BSRR = 1 << gpio::oscillator::pin;
        
            	GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
			
				
				GPIOC->MODER |= GPIO_MODER_MODE0;
			
		

            
            
            

