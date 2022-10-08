#pragma once
#include <cstdint>
#include "stm32l010x4.h"

namespace adc{
	
	namespace gpio_pin_1
	{
		constexpr const static uint8_t pin =	(0x00000002U);
		constexpr const static uint8_t mode =	GPIO_MODER_MODE0;
		constexpr const static uint8_t pull =	(0x00000000U);
		
		constexpr auto& port = GPIOA;
		
		inline static void on()
		{
				adc::gpio_pin_1::port->BSRR = 1 << adc::gpio_pin_1::pin;		
		}
		

		inline static void off()
		{
				adc::gpio_pin_1::port->BSRR = 1 << adc::gpio_pin_1::pin << 16;			
		}
		
		
	}
	
	namespace gpio_pin_2
	{
		constexpr const static uint8_t pin =	(0x00000004U);
		constexpr const static uint8_t mode =	GPIO_MODER_MODE0;
		constexpr const static uint8_t pull =	(0x00000000U);	
		
		constexpr auto& port = GPIOA;
		
		inline static void on()
		{
				adc::gpio_pin_2::port->BSRR = 1 << adc::gpio_pin_2::pin;		
		}
		

		inline static void off()
		{
				adc::gpio_pin_2::port->BSRR = 1 << adc::gpio_pin_2::pin << 16;			
		}
		
	}
	
	namespace gpio_pin_3
	{
		constexpr const static uint8_t pin =	(0x00000008U);
		constexpr const static uint8_t mode =	GPIO_MODER_MODE0;
		constexpr const static uint8_t pull =	(0x00000000U);	
		
		constexpr auto& port = GPIOA;
		
		inline static void on()
		{
				adc::gpio_pin_3::port->BSRR = 1 << adc::gpio_pin_3::pin;		
		}
		

		inline static void off()
		{
				adc::gpio_pin_3::port->BSRR = 1 << adc::gpio_pin_3::pin << 16;			
		}
		
	}
	
	namespace adc_reg
	{
		constexpr const static uint32_t TriggerSource = 	(0x00000000U);
		constexpr const static uint32_t SequencerDiscont =	(0x00000000U);
		constexpr const static uint32_t ContinuousMode =	(0x00000000U);
		constexpr const static uint32_t DMATransfer =		(0x00000000U);
		constexpr const static uint32_t Overrun =			(0x00000000U);
		
		
		constexpr auto& port = ADC1;
		
	}
	
	namespace adc_ini
	{
		constexpr const static uint32_t Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV1;
		constexpr const static uint32_t Resolution = (0x00000000U);
		constexpr const static uint32_t DataAlignment = (0x00000000U);
		constexpr const static uint32_t LowPowerMode = (0x00000000U);
		
		
		constexpr auto& port = ADC1;
		
		
	}
	
	
	
	
	
	void init();
	}
