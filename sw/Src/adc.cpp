#include "adc.hpp"

void adc::init_measure()
{

		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR |= RCC_IOPENR_GPIOAEN;			//GPIO port A control 
	
		//gpio_pin_1 init
		
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD0;
			
		GPIOA->MODER |= GPIO_MODER_MODE0;
		
		//gpio_pin_2 init
		
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD0;
			
		GPIOA->MODER |= GPIO_MODER_MODE0;
		
		//gpio_pin_3 init
		
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD0;
			
		GPIOA->MODER |= GPIO_MODER_MODE0;
		
		
		//Configure regular channel
		//TODO 
		// ADC1->CHSELR |= (ADC_CFGR1_AWDCH_0 | ADC_CHSELR_CHSEL1);  
		// ADC1->CHSELR |= (ADC_CFGR1_AWDCH_1 | ADC_CHSELR_CHSEL2);  
		// ADC1->CHSELR |= ((ADC_CFGR1_AWDCH_1 | ADC_CFGR1_AWDCH_0) | ADC_CHSELR_CHSEL3);		
		
		//adc reg init
		if(((ADC1_CR |= ADC_CR_ADEN)== ADC_CR_ADEN) == 0U) //TODO
		{
			ADC1->CFGR1 |= ADC_CFGR1_EXTSEL;
			ADC1->CFGR1 |= ADC_CFGR1_EXTEN;
			ADC1->CFGR1 |= ADC_CFGR1_DISCEN;
			ADC1->CFGR1 |= ADC_CFGR1_CONT;
			ADC1->CFGR1 |= ADC_CFGR1_DMAEN;
			ADC1->CFGR1 |= ADC_CFGR1_DMACFG;
			ADC1->CFGR1 |= ADC_CFGR1_OVRMOD;
				
		}
		
		//set sampling time
		ADC1->SMPR |= ADC_SMPR_SMP; //ADC_SMPR_SMP >> (0x00000000U) 
		
		
		//set sequencer scan direction
		ADC1->CFGR1 |= ADC_CFGR1_SCANDIR; // ADC_CFGR1_SCANDIR >> (0x00000000U) 
		
		//set common frequency mode
		ADC->CCR |= ADC_CCR_LFMEN; //TODO
		
		//disable eoc IT
		ADC1->IER &= !(ADC_IER_EOCIE);
		
		//disable eos IT
		ADC1->IER &= !(ADC_IER_EOSIE);
		
		//adc intt
		if() // check ADC is enabled
		{
			ADC1->CFGR1 |= DC_CFGR1_RES;
			ADC1->CFGR1 |= ADC_CFGR1_ALIGN;
			ADC1->CFGR1 |= ADC_CFGR1_WAIT;
			ADC1->CFGR1 |= ADC_CFGR1_AUTOFF;
			
			ADC1 |= ADC_CFGR2_CKMODE;
			
		}	
		
		//enable internal regulator
		ADC1->CR |= ADC_CR_BITS_PROPERTY_RS << ADC_CR_ADVREGEN; //TODO ??
	
		//wait
	
}


void adc::init_hall_sensor()
{



	
}
