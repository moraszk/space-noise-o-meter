#include "gpio.hpp"
#include <array>
#include <algorithm>

namespace gpio{
	enum mode_type : uint8_t {
		input = 0,
		output = 1,
		alter = 2,
		ad = 3
	};

	enum pull_type : uint8_t {
		nopull = 0,
		pullup = 1,
		pulldown = 2,
		reserved = 3
	};
	
	enum alter_type: uint8_t{
		AF0 = 0,
		AF1 = 1,
		AF2 = 2,
		AF3 = 3,
		AF4 = 4,
		AF5 = 5,
		AF6 = 6,
		AF7 = 7
	};
	
	struct pin{
		mode_type mode;
		pull_type pull;
		alter_type alter;
	};
	
	namespace calculator{
		template<typename T>
		consteval uint32_t twobit_prop2reg(std::array<T, 16> prop) noexcept{
			std::reverse(prop.begin(), prop.end());
			uint32_t ret = 0;
			for(uint8_t m: prop){
				ret<<=2;
				ret+=m;
			}
			return ret;
		}
		
		consteval uint32_t MODER(
			std::array<mode_type, 16> modes //Order 0-1-2-3-4-5...-14-15
		) noexcept {
			return twobit_prop2reg(modes);
		}
		
		consteval uint32_t MODER(
			std::array<pin, 16> pins //Order 0-1-2-3-4-5...-14-15
		) noexcept {
			std::array<mode_type, 16> modes = {mode_type::ad};
			for(size_t i = 0; i<16;i++){
				modes[i]=pins[i].mode;
			}
				
			return MODER(modes);
		}
		
		consteval uint32_t PUPDR(
				std::array<pull_type, 16> modes //Order 0-1-2-3-4-5...-14-15
			) noexcept{
				return twobit_prop2reg(modes);
		}
		
		consteval uint32_t PUPDR(
				std::array<pin, 16> pins //Order 0-1-2-3-4-5...-14-15
			) noexcept{
				std::array<pull_type, 16> modes = {nopull};
				for(size_t i = 0; i<16;i++){
					modes[i]=pins[i].pull;
				}
					
				return PUPDR(modes);
		}
		
		consteval uint32_t AFRH(
			std::array<pin, 16> pins //Order 0-1-2-3-4-5...-14-15
		) noexcept {
			std::array<alter_type, 16> modes = {alter_type::AF0};
			for(size_t i = 0; i<16;i++){
				modes[i]=pins[i].alter;
			}
			
			std::reverse(modes.begin(), modes.end());
			uint32_t ret = 0;
			for(int i=0; i<8; i++){
				ret<<=4;
				ret+=modes[i];
			}
			
			return ret;
		}
		
		consteval uint32_t AFRL(
			std::array<pin, 16> pins //Order 0-1-2-3-4-5...-14-15
		) noexcept {
			std::array<alter_type, 16> modes = {alter_type::AF0};
			for(size_t i = 0; i<16;i++){
				modes[i]=pins[i].alter;
			}
			
			std::reverse(modes.begin(), modes.end());
			uint32_t ret = 0;
			for(int i=8; i<16; i++){
				ret<<=4;
				ret+=modes[i];
			}
			
			return ret;
		}
	}

	namespace static_tests{
		static_assert(calculator::MODER(
			{
			input, input, input, input,
			input, input, input, input,
			input, input, input, input,
			input, input, input, input

			}) == 0);

		static_assert(calculator::MODER(
		{
			input, input, input, input,
			input, input, input, input,
			input, input, input, input,
			input, input, input, input

		}) == 0);

		static_assert(calculator::MODER(
			{
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			}) == 0xffffffff);

		static_assert(calculator::MODER(
			{
			input, input, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			}) == 0xfffffff0);

		static_assert(calculator::MODER(
			{
			ad, ad, ad, ad,
			input, ad, ad, ad,
			ad, ad, ad, ad,
			ad, alter, alter, ad,
			}) == 0xebfffcff, "Port A default MODE register"
		);
		
		
		static_assert(calculator::PUPDR(
			{
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, pullup, pulldown, nopull,
			}
		) == 0x24000000, "Default PortA value");
	}
	
}

namespace{
	using namespace gpio;
	
	const constexpr std::array<gpio::pin, 16> porta = {{
		{ .mode= ad, .pull=nopull, .alter=AF0 }, //0  -- HSE
		{ .mode= ad, .pull=nopull, .alter=AF0 }, //1  -- Half_vref
		{ .mode= ad, .pull=nopull, .alter=AF0 }, //2  -- Hall_exp
		{ .mode= ad, .pull=nopull, .alter=AF0 }, //3  -- Temperature
		{ .mode= input, .pull=pulldown, .alter=AF0 }, //4  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //5  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //6  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //7  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //8  -- NC
		{ .mode= alter, .pull=nopull, .alter=AF4 }, //9  -- TX 
		{ .mode= alter, .pull=nopull, .alter=AF4 }, //10 -- RX
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //11 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //12 -- NC
		{ .mode= alter, .pull=pulldown, .alter=AF0 }, //13 -- SWDIO TODO turn off swd in production
		{ .mode= alter, .pull=pulldown, .alter=AF0 }, //14 -- SWCLK TODO turn off swd in production
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //15 -- NC
	}};
	
	const constexpr std::array<gpio::pin, 16> portb = {{
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //0  -- NC
		{ .mode= alter, .pull=pullup, .alter=AF5 }, //1  -- RX TIM capture
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //2  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //3  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //4  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //5  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //6  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //7  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //8  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //9  -- BOOT0 tied to gnd
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //10 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //11 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //12 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //13 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //14 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //15 -- NC
	}};
	
	const constexpr std::array<gpio::pin, 16> portc = {{
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //0  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //1  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //2  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //3  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //4  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //5  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //6  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //7  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //8  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //9  -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //10 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //11 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //12 -- NC
		{ .mode= ad, .pull=pulldown, .alter=AF0 }, //13 -- NC
		{ .mode= output, .pull=nopull, .alter=AF0 }, //14 -- Hall_on control
		{ .mode= input, .pull=nopull, .alter=AF0 }, //15 -- Oscillator status signal
	}};
}

void gpio::init(){
		static_assert(gpio::calculator::MODER(porta)+1, "this functino should be computed compile time");
		static_assert(gpio::calculator::PUPDR(porta)+1, "this functino should be computed compile time");
		static_assert(gpio::calculator::AFRL(porta)+1 , "this functino should be computed compile time");
		static_assert(gpio::calculator::AFRH(porta)+1 , "this functino should be computed compile time");
		
		GPIOA->MODER = gpio::calculator::MODER(porta);
		GPIOA->PUPDR = gpio::calculator::PUPDR(porta);
		GPIOA->AFR[0] = gpio::calculator::AFRL(porta);
		GPIOA->AFR[1] = gpio::calculator::AFRH(porta);
		
		GPIOA->OSPEEDR = 0xc0c0003; //TODO check
		
		GPIOB->MODER = gpio::calculator::MODER(portb);
		GPIOB->PUPDR = gpio::calculator::PUPDR(portb);
		GPIOB->AFR[0] = gpio::calculator::AFRL(portb);
		GPIOB->AFR[1] = gpio::calculator::AFRH(portb);
		
		GPIOC->MODER = gpio::calculator::MODER(portc);
		GPIOC->PUPDR = gpio::calculator::PUPDR(portc);
		GPIOC->AFR[0] = gpio::calculator::AFRL(portc);
		GPIOC->AFR[1] = gpio::calculator::AFRH(portc);		
}
