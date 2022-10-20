#include "gpio.hpp"
#include "CommandReceiver.hpp"
#include "command_sender.hpp"
#include "status.hpp"
#include "watchdog.hpp"
#include "uart.hpp"
#include "measure_memory.hpp"

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

namespace{
	CommandReceiver::mrc_frame frame;
}

int main(void){
	gpio::init();
	wdg::init();
	uart::init();


	while(true){
		if( !CommandReceiver::mrc_ingress_buffer.empty() ) {
			frame = CommandReceiver::mrc_ingress_buffer.get();

			if (!frame.isValid()) {
				continue;
			}

			if(frame.getDestinition() == command::Destinition::SU){
				switch(frame.getCommand()){
					case CommandReceiver::Command::RUN:
						if(sat_status.experiment == sat_stat::experiment::NO_EXPERIMENT)
							sat_status.experiment = sat_stat::experiment::ADC_NOISE;
						command_sender::sendack(frame.getSerialStr());
						break;
					case CommandReceiver::Command::OFF:
						sat_status.experiment = sat_stat::experiment::NO_EXPERIMENT;
						command_sender::sendack(frame.getSerialStr());
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
						command_sender::sendtel(frame.getSerialStr());
					default:
						sat_status.communication.unknown_command++;
				}
			}
			else if (frame.getBaud() != 0)
			{
				switch (frame.getCommand())
				{
				case CommandReceiver::Command::UNKNOWN:
					break;
				case CommandReceiver::Command::ACK:
				case CommandReceiver::Command::TEL:
					// save baud of other modules
					const command::Destinition dest = frame.getDestinition();
					if (dest != command::Destinition::UNKNOWN)
					{
						measure_memory.baud_rate.register_measure(dest, frame.getBaud());
					}
					break;
				default:
					measure_memory.baud_rate.register_measure(command::Destinition::OBC, frame.getBaud());
				}
			}
		}

		sat_status.clock = gpio::oscillator::get();
	}
	wdg::refresh();
}
