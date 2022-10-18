#include "adc.hpp"

void adc::init_noise()
{
	//TIM2_CH4 kell nenkunk
	
		ADC1->CR = ADC_CR_ADVREGEN;

		RCC->APB2ENR = RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR = RCC_IOPENR_GPIOAEN;			//GPIO port A control 
		
		//Configure regular channel
		ADC1->CHSELR = ADC_CHSELR_CHSEL1; //PA1
		ADC1->SMPR = ADC_SMPR_SMP;
		
		ADC1->CR = ADC_CR_ADCAL;
					
		while ((ADC1->CR & ADC_CR_ADCAL) != 0){}
		
		ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
		
		
		RCC->CR = RCC_CR_HSEON;
		while ((RCC->CR & RCC_CR_HSERDY) == 0) { }
		
		//adc reg init
		ADC1->CFGR1 &= ~ADC_CFGR1_EXTSEL;
		ADC1->CFGR1 = ADC_CFGR1_CONT;  //  cont(cont mode)
		
}


void adc::init_hall_sensor()
{

		ADC1->CR = ADC_CR_ADVREGEN;
	
		RCC->APB2ENR = RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR = RCC_IOPENR_GPIOAEN;			//GPIO port A control 
		
		ADC1->CHSELR = ADC_CHSELR_CHSEL2; //PA2
		ADC1->SMPR = ADC_SMPR_SMP;
		
		ADC1->CR = ADC_CR_ADCAL;
					
		while ((ADC1->CR & ADC_CR_ADCAL) != 0){}
		
		ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
		
		
		RCC->CR = RCC_CR_HSEON;
		while ((RCC->CR & RCC_CR_HSERDY) == 0) { }
		
		
		//adc reg init
		ADC1->CFGR1 &= ~ADC_CFGR1_EXTSEL;
		ADC1->CFGR1 = ADC_CFGR1_CONT; //  cont(cont mode)
			
}


void adc::init_temp()
{

		ADC1->CR = ADC_CR_ADVREGEN;

		RCC->APB2ENR = RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR = RCC_IOPENR_GPIOAEN;			//GPIO port A control 
		
		ADC1->CHSELR = ADC_CHSELR_CHSEL3; //PA3
		ADC1->SMPR = ADC_SMPR_SMP;
		
		ADC1->CR = ADC_CR_ADCAL;
					
		while ((ADC1->CR & ADC_CR_ADCAL) != 0){}
		
		ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
		
		
		RCC->CR = RCC_CR_HSEON;
		while ((RCC->CR & RCC_CR_HSERDY) == 0) { }
		
		
		//adc reg init
		ADC1->CFGR1 &= ~ADC_CFGR1_EXTSEL;
		ADC1->CFGR1 = ADC_CFGR1_CONT;  //  cont(cont mode)

}






