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

			bool known_cmd = false;

			if (frame.getDestinition() == command::Destinition::SU)
			{
				switch(frame.getCommand()){
					case CommandReceiver::Command::RUN:
						if(sat_status.experiment == sat_stat::experiment::OFF)
							sat_status.experiment = sat_stat::experiment::TEMP;
						command_sender::sendack(frame.getSerialStr());
						break;
					case CommandReceiver::Command::OFF:
						sat_status.experiment = sat_stat::experiment::OFF;
						command_sender::sendack(frame.getSerialStr());
						break;
					case CommandReceiver::Command::CMD:
						if(sat_status.experiment == sat_stat::experiment::OFF){
							sat_status.communication.command_without_run++;
							break;
						}
						known_cmd = telecommand::parse_command(frame.getPayload());
						break;
					case CommandReceiver::Command::RQT:
						if(sat_status.experiment == sat_stat::experiment::OFF){
							sat_status.communication.command_without_run++;
							break;
						}
						command_sender::sendtel(frame.getSerialStr());
						break;
					default:
						sat_status.communication.unknown_command++;
				}
			}

			if (known_cmd) {
				switch (sat_status.experiment){
					case sat_stat::experiment::UART_RATES:
					{
						if (frame.getDestinition() == command::Destinition::SU && frame.getBaud() != 0)
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
							{
								// save baud of other modules
								const command::Destinition dest = frame.getDestinition();
								if (dest != command::Destinition::UNKNOWN)
								{
									measure_memory.baud_rate.register_measure(dest, frame.getBaud());
								}
								break;
							}
							default:
								break;
							}
						}
					}
					break;
					case sat_stat::experiment::ADC_NOISE:
					{
						measure_memory.adc_noise.counter++;
						if (measure_memory.adc_noise.counter > measure_memory.adc_noise.delay){
							measure_memory.adc_noise.counter=0;
							measure_memory.adc_noise.register_measure();
						}
					}
					break;
					case sat_stat::experiment::HALL:
					case sat_stat::experiment::TEMP:
					case sat_stat::experiment::OFF:
					case sat_stat::experiment::QUOTES:
					default:
						break;
				}
			}
		}

		sat_status.clock = gpio::oscillator::get();
		wdg::refresh();
	}
}
