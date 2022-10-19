#pragma once

#include "utils.hpp"
#include <iterator>
#include <array>
#include "checksum.hpp"
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include "command.hpp"

const constexpr static size_t rx_buffer_size = command::longest_reply.size() + 1;
const constexpr static size_t mrc_ingress_buffer_len = 4;

namespace CommandReceiver{
	enum class Command {
		RUN,
		OFF,
		RQT,
		CMD,
		ACK,
		TEL,
		UNKNOWN
	};

	class mrc_frame {
		const constexpr static size_t dst_offset = 1;
		const constexpr static size_t command_offset = 3;
		const constexpr static size_t checksum_backset = 6;
		const constexpr static size_t serial_backset = 9;

		std::array<char,rx_buffer_size> buff;
		size_t size;
		uint16_t baud;
	public:
		mrc_frame(): buff{}, size{0} {}

		mrc_frame(const std::string& in): buff{}, size{}{
			auto copiedbuffend = std::copy(in.cbegin(), in.cend(), buff.begin());
			size = copiedbuffend - buff.begin();
		}

		mrc_frame(const std::array<char,rx_buffer_size>& buff, const size_t size, uint16_t t1, uint16_t t2):
			buff{buff}, size{size}
		{
			//t's are measured from the \n character rising edge differenecs

			//t1 equals to two baud time
			//t2 equals to five baud time

			constexpr uint32_t normal_baud_time = 10000000/10000; //AHB Clock per baud
			constexpr uint32_t t1_normal_value = normal_baud_time * 2;
			constexpr uint32_t t2_normal_value = normal_baud_time * 5;
			constexpr uint32_t allowed_error = normal_baud_time * 0.03 * 7;

			if( ( (t2*2) > (t1*5) + allowed_error ) || ( (t2*2) < (t1*5) - allowed_error ) ){
				baud = 0;
			} else {
				baud = (t1+t2)/ 7;
			}
		}

		size_t getSize() const {
			return size;
		}

		unsigned getBaud() const {
			return baud;
		}

		uint16_t getChecksum() const {
			return utils::hex2int<uint16_t>(buff.data() + size - checksum_backset);
		}

		command::Destinition getDestinition() const {
			if (__builtin_strncmp(buff.data()+dst_offset, "SU", 2) == 0) return command::Destinition::SU;
			else
			if (__builtin_strncmp(buff.data()+dst_offset, "DE", 2) == 0) return command::Destinition::DE;
			else
			if (__builtin_strncmp(buff.data()+dst_offset, "GY", 2) == 0) return command::Destinition::GY;
			else
			if (__builtin_strncmp(buff.data()+dst_offset, "SZ", 2) == 0) return command::Destinition::SZ;
			else
			if (__builtin_strncmp(buff.data()+dst_offset, "OB", 2) == 0) return command::Destinition::OBU;
			else
			return command::Destinition::UNKNOWN;
		}
		
		CommandReceiver::Command getCommand() const {
			if (__builtin_strncmp(buff.data()+command_offset, "RQT", 3) == 0) return CommandReceiver::Command::RQT;
			else
			if (__builtin_strncmp(buff.data()+command_offset, "TEL", 3) == 0) return CommandReceiver::Command::TEL;
			else
			if (__builtin_strncmp(buff.data()+command_offset, "RUN", 3) == 0) return CommandReceiver::Command::RUN;
			else
			if (__builtin_strncmp(buff.data()+command_offset, "CMD", 3) == 0) return CommandReceiver::Command::CMD;
			else
			if (__builtin_strncmp(buff.data()+command_offset, "ACK", 3) == 0) return CommandReceiver::Command::ACK;
			else
			if (__builtin_strncmp(buff.data()+command_offset, "OFF", 3) == 0) return CommandReceiver::Command::OFF;
			else
			return CommandReceiver::Command::UNKNOWN;
		}

		uint16_t calculate_checksum() const {
			return checksum::get_checksum(buff.begin()+1, buff.begin()+(size-checksum_backset-1));
		}

		bool isValid() const {
			if (size < serial_backset+1) return false;

			if(
				buff[0] != '$' ||
 				buff[size-1] != '\n' ||
				buff[size-2] != '\r' ||
				buff[size-checksum_backset-1] != '*'  ||
				buff[size-serial_backset-1] != '#'
			  )
				return false;

			if (this->getChecksum() != this->calculate_checksum())
				return false;

			//if (this->getCommand() == CommandReceiver::Command::UNKNOWN)
			//	return false;

			return true;
		}

		uint8_t getSerial() const {
			return utils::hex2int<uint8_t>(buff.data()+size-serial_backset);
		}
		
		const char * getSerialStr() const {
			return buff.data()+size-serial_backset;
		}
	};

	extern utils::ringbuffer<CommandReceiver::mrc_frame, mrc_ingress_buffer_len> mrc_ingress_buffer;
}
