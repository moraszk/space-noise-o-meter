#include "adc.hpp"

void adc::init_measure()
{

		RCC->APB2ENR = RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR = RCC_IOPENR_GPIOAEN;			//GPIO port A control 
		
		
		//Configure regular channel
		ADC1->CHSELR = 0xE; // (enable PA1 , PA2 , PA3)
		
		
		//adc reg init
		ADC1->CFGR1 = ADC_CFGR1_EXTSEL_2|  // TRG3--> 011 (bit 8- bit 6)
					  ADC_CFGR1_EXTEN |	   // 00 --> szoftverbol allithatjuk (bit 11- bit 10)
					  ADC_CFGR1_CONT |	   // bit 13 --> 1
					  ADC_CFGR1_OVRMOD |   // bit 12 --> 0
					  ADC_CFGR1_SCANDIR |  // bit 2 --> 0
					  ADC_CFGR1_RES | 	   //?? //TODO
					  ADC_CFGR1_ALIGN |    // bit 5 --> 0
					  ADC_CFGR1_WAIT |	   // ?? //TODO
					  ADC_CFGR1_AUTOFF |   // ?? //TODO
					  ADC_CFGR2_CKMODE;    // ?? ekkor kell az ADC_CR_ADEN -t torolni
		
					 // ADC_CFGR1_DISCEN ?? //TODO
					 // ADC_CFGR1_DMAEN , ADC_CFGR1_DMACFG			  
			  
					  
		//set sampling time
		ADC1->SMPR = 0x7; // 12.5 ADC clock cycles 
		
		
		//set common frequency mode
		ADC->CCR = ADC_CCR_LFMEN; // bit 25 --> 0 low frequency mode disabled
								  // bit 22 --> 0 VREFINT disabled
								  // bit 21 - 18 --> ?? //TODO ADC prescalar
		
		
		//disable eoc IT , disable eos IT
		//ADC1->IER = !(ADC_IER_EOCIE | ADC_IER_EOSIE);
		
		
		//enable internal regulator
		ADC1->CR = (ADC_CR_ADCAL | // bit 31 --> 0
					//ADC_CR_ADSTP | // bit 4 --> 0 //TODO
					ADC_CR_ADSTART | // ?? //TODO bit 2 --> 0
					//ADC_CR_ADDIS | bit 1 --> 0 
					ADC_CR_ADEN) | // bit 0 --> 1
					ADC_CR_ADVREGEN; // bit 28 --> 1
	
	
}


void adc::init_hall_sensor()
{
	



	
}
