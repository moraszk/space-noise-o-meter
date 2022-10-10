#include "gpio.hpp"
#include <array>
#include <algorithm>

namespace gpio{
	namespace mode{
		enum gpio_mode : uint8_t {
				input = 0,
				output = 1,
				alter = 2,
				ad = 3
		};

		consteval uint32_t modecalculator(
			std::array<gpio_mode, 16> modes //Order 0-1-2-3-4-5...-14-15
		) noexcept {
			std::reverse(modes.begin(), modes.end());
			uint32_t ret = 0;
			for(uint8_t m: modes){
				ret<<=2;
				ret+=m;
			}
			return ret;
		}

		static_assert(modecalculator(
			{
			input, input, input, input,
			input, input, input, input,
			input, input, input, input,
			input, input, input, input

			}) == 0);

		static_assert(modecalculator(
		{
			input, input, input, input,
			input, input, input, input,
			input, input, input, input,
			input, input, input, input

		}) == 0);

		static_assert(modecalculator(
			{
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			}) == 0xffffffff);

		static_assert(modecalculator(
			{
			input, input, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			ad, ad, ad, ad,
			}) == 0xfffffff0);

		static_assert(
			modecalculator({
			ad, ad, ad, ad,
			input, ad, ad, ad,
			ad, ad, ad, ad,
			ad, alter, alter, ad,
			}) == 0xebfffcff, "Port A default MODE register"
		);
	}

	namespace pull{
		enum gpio_pull : uint8_t {
				nopull = 0,
				pullup = 1,
				pulldown = 2,
				reserved = 3
		};

		consteval uint32_t pullcalculator(
			std::array<gpio_pull, 16> modes //Order 0-1-2-3-4-5...-14-15
		) noexcept {
			std::reverse(modes.begin(), modes.end());
			uint32_t ret = 0;
			for(uint8_t m: modes){
				ret<<=2;
				ret+=m;
			}
			return ret;
		}

		static_assert(pullcalculator(
			{
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, pullup, pulldown, nopull,
			}
		) == 0x24000000, "Default PortA value");
	}

}

void gpio::init(){

	{
		using namespace gpio::mode;
		GPIOA->MODER = modecalculator(
			{
			ad, ad, ad, ad, // 0 OSC - 1 half_vref - 2 hall_exp - 3 cap_exp
			input, ad, ad, ad, // 4 NC - 5 NC - 6 NC - 7 NC
			ad, ad, ad, ad, // 8 NC - 9 TX - 10 RX - 11 NC
			ad, alter, alter, ad, // 12 NC - 13 SWDIO - 14 SWCLK - 15 NC TODO turn off swd in production
			}
		);

		GPIOB->MODER = modecalculator(
			{
			ad, alter, ad, ad, // 0 - 1 TIM_CH - 2 - 3
			ad, ad, ad, ad, // 4 - 5 - 6 - 7
			ad, ad, ad, ad, // 8 - 9 BOOT - 10 - 11
			ad, ad, ad, ad, // 12 - 13 - 14 - 15
			}
		);


		GPIOC->MODER = modecalculator(
			{
			ad, ad, ad, ad, // 0 - 1 - 2 - 3
			ad, ad, ad, ad, // 4 - 5 - 6 - 7
			ad, ad, ad, ad, // 8 - 9 - 10 - 11
			ad, ad, ad, ad, // 12 - 13 - 14 HALL_ON - 15 OSC_STAT
			}
		);
	}

	{
		using namespace gpio::pull;
		GPIOA->PUPDR = pullcalculator(
			{
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, pullup, pulldown, nopull, //TODO in production, turn off swd
			}
		);

		GPIOB->PUPDR = pullcalculator(
			{
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			}
		);

		GPIOC->PUPDR = pullcalculator(
			{
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			nopull, nopull, nopull, nopull,
			}
		);
	}
    // hall pin gpio init
        GPIOC->BSRR = 1 << gpio::hall::pin;		

        
    	if((GPIO_MODER_MODE0_0 == GPIO_MODER_MODE0_0 ) || (GPIO_MODER_MODE0_0 == GPIO_MODER_MODE0_1))	
			{
				GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEED2_0 ;	
				
				GPIOC->OTYPER |= (0x00000000U) ;	//output mode config
				
			}
			
				GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
			
				//                              ,-----HALL measure
				GPIOC->MODER = modecalculator({ad, input});
				//                                   `----OSC stat
			
    
    // oscillator pin gpio init 
                GPIOC->BSRR = 1 << gpio::oscillator::pin;
        
            	GPIOC->PUPDR |= GPIO_PUPDR_PUPD0;
			
				
				GPIOC->MODER |= GPIO_MODER_MODE0;
			
		
}
            
            
            

