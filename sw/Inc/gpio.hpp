#pragma once
#include <cstdint>
#include "stm32l010x4.h"

namespace gpio{
	
	namespace clock
	{
		
		inline static get_C_EN() 				//check port C clock enable
		{
			return (RCC_IOPENR_IOPCEN) ? 1 : 0;
		}
		
		inline static get_A_EN()				//check port A clock enable
		{
			return (RCC_IOPENR_IOPAEN) ? 1 : 0;
		}
		
		inline static get_B_EN()				//check port B clock enable
		{
			return (RCC_IOPENR_IOPBEN) ? 1 : 0;
		}
		
	}
	
	
	namespace hall {    
		constexpr const static uint8_t pin = 14;
		constexpr const static uint8_t mode = GPIO_MODER_MODE0_0;
		constexpr const static uint8_t speed = (0x00000000U);
		constexpr const static uint8_t output_type = (0x00000000U) ; 
		constexpr const static uint8_t pull = (0x00000000U) ;
		
		constexpr auto& port = GPIOC;
		
		
		inline static void on()
		{
				gpio::hall::port->BSRR = 1 << gpio::hall::pin;		
		}
		

		inline static void off()
		{
			gpio::hall::port->BSRR = 1 << gpio::hall::pin << 16;			
		}
		
	}

	
	namespace oscillator { // pin15 input
		constexpr const static uint8_t pin = 15;
		constexpr const static uint8_t mode = (0x00000000U);
		constexpr const static uint8_t pull = (0x00000000U);
		
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

	
	namespace RCC 
	{
		constexpr const static uint8_t pin = (0x00000002U);
		constexpr const static uint8_t mode = GPIO_MODER_MODE0_1 ;
		constexpr const static uint8_t speed = (0x00000000U) ;
		constexpr const static uint8_t output_type = (0x00000000U) ;
		constexpr const static uint8_t pull = (0x00000000U)  ;
		constexpr const static uint8_t alternate = (0x0000005U);
			
		constexpr auto& port = GPIOC;

		
		inline static void on()
		{
				gpio::RCC::port->BSRR = 1 << gpio::RCC::pin;		
		}
		

		inline static void off()
		{
				gpio::RCC::port->BSRR = 1 << gpio::RCC::pin << 16;			
		}
		
		
	}
	
	
	
	
	
	void init();
}
