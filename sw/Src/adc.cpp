#include "adc.hpp"

void adc::init(){
	ADC->CCR=ADC_CCR_VREFEN | ADC_CCR_LFMEN | ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0;
	
	//TODO move calibrtion to a telecommand
	ADC1->CHSELR = ADC_CHSELR_CHSEL1 | ADC_CHSELR_CHSEL2 | ADC_CHSELR_CHSEL3 | ADC_CHSELR_CHSEL17;
	ADC1->SMPR = ADC_SMPR_SMP;
	ADC1->CFGR1 = ADC_CFGR1_CONT;
	ADC1->CFGR2 = ADC_CFGR2_CKMODE_1;
	ADC1->SMPR = 4;
	
	ADC1->CR = ADC_CR_ADVREGEN | ADC_CR_ADCAL;
	
	while ((ADC1->CR & ADC_CR_ADCAL) != 0);
	
	ADC1->CR = ADC_CR_ADVREGEN;
	ADC1->CFGR1 = ADC_CFGR1_CONT | ADC_CFGR1_DMACFG | ADC_CFGR1_DMAEN;
	ADC1->CR = ADC_CR_ADVREGEN | ADC_CR_ADEN;
	
	while (ADC1->ISR & ADC_ISR_ADRDY);
	
	ADC1->CR = ADC_CR_ADVREGEN | ADC_CR_ADEN | ADC_CR_ADSTART;
}
