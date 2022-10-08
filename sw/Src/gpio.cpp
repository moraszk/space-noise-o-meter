#include "gpio.hpp"

void gpio::init(){
	
            RCC->IOPENR |= RCC_IOPENR_GPIOCEN;		//enable gpio port C clock
            RCC->IOPENR |= RCC_IOPENR_GPIOAEN;		//enable gpio port A clock
            RCC->IOPENR |= RCC_IOPENR_GPIOBEN;		//enable gpio port B clock
            GPIOC->BRR |= GPIO_BSRR_BS_14;			//reset GPIO output pin
		
		
    // hall pin gpio init
        gpio::hall::on();
    
    	if((gpio::hall::mode == GPIO_MODER_MODE0_0 ) || (gpio::hall::mode == GPIO_MODER_MODE0_1))	
			{
				gpio::hall::port->OSPEEDR |= GPIO_OSPEEDER_OSPEED2_0 << gpio::hall::speed;	
				
				gpio::hall::port->OTYPER |= gpio::hall::output_type << gpio::hall::pin;	//output mode config
				
			}
			
				gpio::hall::port->PUPDR |= GPIO_PUPDR_PUPD0 << gpio::hall::pull;
			
				
				gpio::hall::port->MODER |= GPIO_MODER_MODE0 << gpio::hall::mode;
			
    
    // oscillator pin gpio init            
    	gpio::oscillator::on();
        
            	gpio::oscillator::port->PUPDR |= GPIO_PUPDR_PUPD0 << gpio::oscillator::pull;
			
				
				gpio::oscillator::port->MODER |= GPIO_MODER_MODE0 << gpio::oscillator::mode;
			
		
    // RCC pin gpio init
        gpio::RCC::on();
                
        if((gpio::RCC::mode == GPIO_MODER_MODE0_0 ) || (gpio::RCC::mode == GPIO_MODER_MODE0_1))
            {
                gpio::RCC::port->OSPEEDR |= GPIO_OSPEEDER_OSPEED2_0 << gpio::RCC::speed;	
                    
                gpio::RCC::port->OTYPER |= gpio::RCC::output_type << gpio::RCC::pin;	//output mode config
                    
            }
                
                gpio::RCC::port->PUPDR |= GPIO_PUPDR_PUPD0 << gpio::RCC::pull;
                
                    if(gpio::RCC::mode == GPIO_MODER_MODE0_1)
                    {
                        if(gpio::RCC::port < GPIO_BSRR_BS_8)
                        {
                            gpio::RCC::port->AFR[0] |= GPIO_AFRL_AFSEL0 << gpio::RCC::alternate; //??
                        }
                        else
                        {
                            gpio::RCC::port->AFR[1] |= GPIO_AFRH_AFSEL8 << gpio::RCC::alternate; //??
                        }
                        
                    }
                
        gpio::RCC::port->MODER |= GPIO_MODER_MODE0 << gpio::RCC::mode;
			
                
            
            
            
}
