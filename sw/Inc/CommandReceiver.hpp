#pragma once

#include "utils.hpp"
#include <iterator>
#include <array>
#include "checksum.hpp"
#include <cstring>
#include <algorithm>

const constexpr static size_t rx_buffer_size = 64; //TODO recalculate
const constexpr static size_t command_buffer_len = 4; //TODO recalculate

namespace CommandReceiver{
	enum class Command {
		SURUN,
		SUOFF,
		SURQT,
		SUCMD,
		UNKNOWN
	};

	class mrc_frame {
		const constexpr static size_t command_offset = 1;
		const constexpr static size_t checksum_backset = 6;
		const constexpr static size_t serial_backset = 9;

		std::array<char,rx_buffer_size> buff;
		size_t size;
	public:
		mrc_frame(): buff{}, size{0} {}

		mrc_frame(const std::string& in): buff{}, size{}{
			auto copiedbuffend = std::copy(in.cbegin(), in.cend(), buff.begin());
			size = copiedbuffend - buff.begin();
		}

		mrc_frame(const std::array<char,rx_buffer_size>& buff, const size_t size):
			buff{buff}, size{size} {}

		size_t getSize() const {
			return size;
		}

		uint16_t getChecksum() const {
			return utils::hex2int<uint16_t>(buff.data() + size - checksum_backset);
		}

		CommandReceiver::Command getCommand() const {
			if (strncmp(buff.data()+command_offset, "SURUN", 5) == 0) return CommandReceiver::Command::SURUN;
			else
			if (strncmp(buff.data()+command_offset, "SUOFF", 5) == 0) return CommandReceiver::Command::SUOFF;
			else
			if (strncmp(buff.data()+command_offset, "SURQT", 5) == 0) return CommandReceiver::Command::SURQT;
			else
			if (strncmp(buff.data()+command_offset, "SUCMD", 5) == 0) return CommandReceiver::Command::SUCMD;
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
	};

	extern utils::ringbuffer<CommandReceiver::mrc_frame, 4> mrc_ingress_buffer;
}
