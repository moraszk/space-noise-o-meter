#include "gpio.hpp"

/*
 * Bootup process:
 * 
 * -- startup.s:
 * -----set stack pointer
 * -----Copy non-const static variables to memory
 * -----Zerofill the non initialized variables
 * -----Call SystemClock_Config (sysclock_config.cpp)
 * ---------Turn off every interupt
 * ---------Set flash latency
 * ---------Turn on HSE
 * ---------Turn on peripherial clocks
 * -----Call static_cosntructors
 * -----Call main (this file)
 * ---------See below....
 * -----Call unknown interrupt/hard fault when main returns
 */

int main(void){
	gpio::init();
	
	while(true){
		//to useful stuff
	}
}
