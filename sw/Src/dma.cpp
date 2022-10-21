#include "dma.hpp"
#include "stm32l010x4.h"
#include <bit>
#include <cstdint>
#include "status.hpp"

void dma::init(){
    //Channel input config
    DMA1_CSELR->CSELR = (1<<15);
    
    //ADC channel
    DMA1_Channel1->CNDTR=4;
    DMA1_Channel1->CPAR=std::bit_cast<uint32_t>(&ADC1->DR);
    DMA1_Channel1->CMAR=std::bit_cast<uint32_t>(&sat_status.adc);
    DMA1_Channel1->CCR = DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_EN;
    
    //Timer channel
    DMA1_Channel4->CPAR=std::bit_cast<uint32_t>(&TIM2->CCR4);
    DMA1_Channel4->CMAR=std::bit_cast<uint32_t>(sat_status.timer_capture.data());;
}

void dma::start_timer_capture(){ //TODO inline
    DMA1_Channel4->CNDTR=sat_status.timer_capture.size();
    DMA1_Channel4->CCR = DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_MINC | DMA_CCR_EN;
}
