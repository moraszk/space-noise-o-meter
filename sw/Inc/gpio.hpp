#pragma once
#include <cstdint>
#include "stm32l010x4.h"

namespace gpio{
	
	namespace hall {    
		constexpr const static uint8_t pin = 14;
		
		inline static void on()
		{
			GPIOC->BSRR = 1 << gpio::hall::pin;
		}
	
		inline static void off()
		{
			GPIOC->BSRR = 1 << gpio::hall::pin << 16;
		}
		
	}

	
	namespace oscillator {
		constexpr const static uint8_t pin = 15;
		
		enum stat : uint8_t{
			PRIMARY = 0,
			SECONDARY = 1
		};

		inline stat static get(){
			return 
				(GPIOC->IDR & (1 << gpio::oscillator::pin) )
				?
				stat::SECONDARY
				:
				stat::PRIMARY;
		}
	}

	void init();
}
