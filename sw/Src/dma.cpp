#include "dma.hpp"
#include "stm32l010x4.h"
#include <bit>
#include <cstdint>
#include "status.hpp"

void dma::init(){    
    DMA1_Channel1->CNDTR=4;
    DMA1_Channel1->CPAR=std::bit_cast<uint32_t>(&ADC1->DR);
    DMA1_Channel1->CMAR=std::bit_cast<uint32_t>(&sat_status.adc);
    DMA1_Channel1->CCR = DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_EN;
}
