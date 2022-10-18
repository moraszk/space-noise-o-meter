#include "gpio.hpp"
#include "CommandReceiver.hpp"
#include "command_sender.hpp"
#include "status.hpp"
#include "watchdog.hpp"
#include "uart.hpp"

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
	wdg::init();
	uart::init();
	
	
	while(true){
		if( !CommandReceiver::mrc_ingress_buffer.empty() ) {
			CommandReceiver::mrc_frame frame = CommandReceiver::mrc_ingress_buffer.get();

			if(frame.isValid() && frame.getBaud() != 0){} //TODO to be inserted
			
			if(frame.getDestinition() == CommandReceiver::Destinition::SU){
				switch(frame.getCommand()){
					case CommandReceiver::Command::RUN:
						if(sat_status.experiment == sat_stat::experiment::NO_EXPERIMENT)
							sat_status.experiment = sat_stat::experiment::ADC_NOISE;
						command_sender::sendack(frame.getSerial());
						break;
					case CommandReceiver::Command::OFF:
						sat_status.experiment = sat_stat::experiment::NO_EXPERIMENT;
						command_sender::sendack(frame.getSerial());
						break;
					case CommandReceiver::Command::CMD:
						if(sat_status.experiment == sat_stat::experiment::NO_EXPERIMENT){
							sat_status.communication.command_without_run++;
							break;
						}
						//TODO parse command
					case CommandReceiver::Command::RQT:
						if(sat_status.experiment == sat_stat::experiment::NO_EXPERIMENT){
							sat_status.communication.command_without_run++;
							break;
						}
						//TODO encapsulate telemetry
					default:
						sat_status.communication.unknown_command++;
				}
			} else {
				switch(frame.getCommand()){
					case CommandReceiver::Command::ACK:
					case CommandReceiver::Command::TEL:
						frame.getDestinition();
						frame.getBaud();
						//from other modules, save baud to register
						break;
					default:
						//from OBS, save baud to register
						frame.getBaud();
				}
			}
		}
		//to useful stuff
	}
}
