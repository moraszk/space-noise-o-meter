#include "adc.hpp"

void adc::init_measure()
{

		RCC->APB2ENR = RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR = RCC_IOPENR_GPIOAEN;			//GPIO port A control 
		
		//Configure regular channel
		//TODO 
		// ADC1->CHSELR |= (ADC_CFGR1_AWDCH_0 | ADC_CHSELR_CHSEL1);  
		// ADC1->CHSELR |= (ADC_CFGR1_AWDCH_1 | ADC_CHSELR_CHSEL2);  
		// ADC1->CHSELR |= ((ADC_CFGR1_AWDCH_1 | ADC_CFGR1_AWDCH_0) | ADC_CHSELR_CHSEL3);		
		
		//adc reg init
		if(((ADC1|= ADC_CR_ADEN)== ADC_CR_ADEN) == 0U) //TODO
		{
			ADC1->CFGR1 = ADC_CFGR1_EXTSEL | ADC_CFGR1_EXTEN | ADC_CFGR1_DISCEN | ADC_CFGR1_CONT | ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG | ADC_CFGR1_OVRMOD;
			
		}
		
		//set sampling time
		ADC1->SMPR = ADC_SMPR_SMP; //ADC_SMPR_SMP >> (0x00000000U) 
		
		
		//set sequencer scan direction
		ADC1->CFGR1 = ADC_CFGR1_SCANDIR; // ADC_CFGR1_SCANDIR >> (0x00000000U) 
		
		//set common frequency mode
		ADC->CCR = ADC_CCR_LFMEN; //TODO
		
		//disable eoc IT , disable eos IT
		ADC1->IER = !(ADC_IER_EOCIE | ADC_IER_EOSIE);
		
		//adc intt
		if() // check ADC is enabled
		{
			ADC1->CFGR1 = ADC_CFGR1_RES | ADC_CFGR1_ALIGN | ADC_CFGR1_WAIT | ADC_CFGR1_AUTOFF | ADC_CFGR2_CKMODE;
		
		}	
		
		//enable internal regulator
		ADC1->CR = (ADC_CR_ADCAL | ADC_CR_ADSTP | ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN) | ADC_CR_ADVREGEN; 
	
		//wait
	
}


void adc::init_hall_sensor()
{



	
}
