#include "adc.hpp"

void adc::init()
{

		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;			//ADC1 clock enable
		RCC->IOPENR |= RCC_IOPENR_GPIOAEN;			//GPIO port A control 
	
		//gpio_pin_1 init
		adc::gpio_pin_1::on();
		
		adc::gpio_pin_1::port->PUPDR |= GPIO_PUPDR_PUPD0 << adc::gpio_pin_2::pull;
			
		adc::gpio_pin_1::port->MODER |= GPIO_MODER_MODE0 << adc::gpio_pin_2::mode;
		
		//gpio_pin_2 init
		adc::gpio_pin_2::on();
		
		adc::gpio_pin_2::port->PUPDR |= GPIO_PUPDR_PUPD0 << adc::gpio_pin_2::pull;
			
		adc::gpio_pin_2::port->MODER |= GPIO_MODER_MODE0 << adc::gpio_pin_2::mode;
		
		//gpio_pin_3 init
		adc::gpio_pin_3::on();
		
		adc::gpio_pin_3::port->PUPDR |= GPIO_PUPDR_PUPD0 << adc::gpio_pin_3::pull;
			
		adc::gpio_pin_3::port->MODER |= GPIO_MODER_MODE0 << adc::gpio_pin_3::mode;
		
		
		//Configure regular channel
		//TODO 
		// ADC1->CHSELR |= (ADC_CFGR1_AWDCH_0 | ADC_CHSELR_CHSEL1);  
		// ADC1->CHSELR |= (ADC_CFGR1_AWDCH_1 | ADC_CHSELR_CHSEL2);  
		// ADC1->CHSELR |= ((ADC_CFGR1_AWDCH_1 | ADC_CFGR1_AWDCH_0) | ADC_CHSELR_CHSEL3);		
		
		//adc reg init
		if(((ADC1_CR |= ADC_CR_ADEN)== ADC_CR_ADEN) == 0U) //TODO
		{
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_EXTSEL;
			//adc::adc_reg::port->CFGR1 |= ADC_CFGR1_EXTSEL;
			//TODO mindegyiket atirni namesapcessel
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_EXTEN << adc::adc_reg::TriggerSource;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_DISCEN << adc::adc_reg::SequencerDiscont;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_CONT << adc::adc_reg::ContinuousMode;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_DMAEN << adc::adc_reg::DMATransfer; //TODO a dmaen vagy dmacfg-ba kene beletenni?
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_DMACFG;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_OVRMOD << adc::adc_reg::Overrun;
				
		}
		
		//set sampling time
		adc::adc_reg::port->SMPR |= ADC_SMPR_SMP; //ADC_SMPR_SMP >> (0x00000000U) 
		
		//set oversampling scope
		adc::adc_reg::port->CFGR2 |= ADC_CFGR2_OVSE; //ADC_CFGR2_OVSE >> (0x00000000U) //TODO ezt bele kell irni?
		
		//set sequencer scan direction
		adc::adc_reg::port->CFGR1 |= ADC_CFGR1_SCANDIR; // ADC_CFGR1_SCANDIR >> (0x00000000U) 
		
		//set common frequency mode
		ADC->CCR |= ADC_CCR_LFMEN; //TODO
		
		//disable eoc IT
		adc::adc_reg::port->IER &= !(ADC_IER_EOCIE);
		
		//disable eos IT
		adc::adc_reg::port->IER &= !(ADC_IER_EOSIE);
		
		//adc intt
		if() // check ADC is enabled
		{
			adc::adc_reg::port->CFGR1 |= DC_CFGR1_RES		<<	adc::adc_ini::Resolution;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_ALIGN	<<	adc:.adc_ini::DataAlignment;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_WAIT;
			adc::adc_reg::port->CFGR1 |= ADC_CFGR1_AUTOFF	<<	adc:.adc_ini::LowPowerMode;
			
			adc::adc_reg::port |= ADC_CFGR2_CKMODE	<<	adc::adc_ini::Clock;
			
		}	
		
		//enable internal regulator
		adc::adc_reg::port->CR |= ADC_CR_BITS_PROPERTY_RS << ADC_CR_ADVREGEN; //TODO ??
	
		//wait
	
	
}
