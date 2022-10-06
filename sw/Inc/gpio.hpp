#pragma once
#include <cstdint>
#include "stm32l010x4.h"

namespace gpio{
	namespace hall {
		constexpr const static uint8_t pin = 14;
		constexpr auto& port = GPIOC;

		inline static void on(){
			gpio::hall::port->BSRR = 1 << gpio::HAL::pin;			
		}

		inline static void off(){
			gpio::hall::port->BSRR = 1 << gpio::HAL::pin << 16;			
		}
	}

	namespace oscillator {
		constexpr const static uint8_t pin = 15;
		constexpr auto& port = GPIOC;

		enum class stat{
			PRIMARY,
			SECONDARY
		}

		inline static get(){
			using gpio::oscillator::stat;

			return 
				(gpio::oscillator::port->IDR & (1 << gpio::oscillator::pin) )
				?
				SECONDARY
				:
				PRIMARY;
		}
	}

	void init();
}
