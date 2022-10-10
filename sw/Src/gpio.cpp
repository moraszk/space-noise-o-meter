#include "gpio.hpp"

#include <array>
enum gpio_mode : uint8_t {
		input = 0,
		output=1,
		alter = 2,
		ad=3
};

consteval uint32_t modecalculator(
	const std::array<gpio_mode, 2> modes
) noexcept {
	uint32_t ret = 0;
	for(gpio_mode m: modes){
		ret<<=2;
		ret+=m;
	}
	return ret;
}

static_assert(modecalculator({ad, input}) == 12);

void gpio::init(){
	
            RCC->IOPENR |= RCC_IOPENR_GPIOCEN;		//enable gpio port C clock
            RCC->IOPENR |= RCC_IOPENR_GPIOAEN;		//enable gpio port A clock
            RCC->IOPENR |= RCC_IOPENR_GPIOBEN;		//enable gpio port B clock
            GPIOC->BRR |= GPIO_BSRR_BS_14;			//reset GPIO output pin
		
		
    // hall pin gpio init
        GPIOC->BSRR = 1 << gpio::hall::pin;		

        
    	if((GPIO_MODER_MODE0_0 == GPIO_MODER_MODE0_0 ) || (GPIO_MODER_MODE0_0 == GPIO_MODER_MODE0_1))	
			{
				GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEED2_0 ;	
				
				GPIOC->OTYPER |= (0x00000000U) ;	//output mode config
				
			}
			
				GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
			
				//                              ,-----HALL measure
				GPIOC->MODER = modecalculator({ad, input});
				//                                   `----OSC stat
			
    
    // oscillator pin gpio init 
                GPIOC->BSRR = 1 << gpio::oscillator::pin;
        
            	GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
			
				
				GPIOC->MODER |= GPIO_MODER_MODE0;
			
		
}
            
            
            

