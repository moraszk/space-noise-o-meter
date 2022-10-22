#include "gpio.hpp"
#include "CommandReceiver.hpp"
#include "command_sender.hpp"
#include "status.hpp"
#include "watchdog.hpp"
#include "uart.hpp"
#include "dma.hpp"
#include "adc.hpp"
#include "timer.hpp"
#include "measure_memory.hpp"
#include "telecommand.hpp"

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
	//wdg::init();
	gpio::init();
	timer::init();
	dma::init();
	adc::init();
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
						telecommand::parse_command(frame.getPayload());
						break;
					case CommandReceiver::Command::RQT:
						if(sat_status.experiment == sat_stat::experiment::NO_EXPERIMENT){
							sat_status.communication.command_without_run++;
							break;
						}
						command_sender::sendtel(frame.getSerialStr());
						break;
					default:
						sat_status.communication.unknown_command++;
				}
			}
			else if (sat_status.experiment == sat_stat::experiment::UART_RATES && frame.getBaud() != 0)
			{
				switch (frame.getCommand())
				{
				case CommandReceiver::Command::RQT:
				case CommandReceiver::Command::RUN:
				case CommandReceiver::Command::OFF:
				case CommandReceiver::Command::CMD:
					measure_memory.baud_rate.register_measure(command::Destinition::OBC, frame.getBaud());
					break;
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
				}
			}
		}

		sat_status.clock = gpio::oscillator::get();
	}
	wdg::refresh();
}
