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
		SUCMD
		INVALID
	};

	class command {
		const constexpr static size_t command_offset = 1;
		const constexpr static size_t checksum_backset = 6;
		const constexpr static size_t serial_backset = 9;

		std::array<char,rx_buffer_size> buff;
		size_t size;
	public:
		command(): buff{}, size{0} {}

		command(const std::string& in): buff{}, size{}{
			auto copiedbuffend = std::copy(in.cbegin(), in.cend(), buff.begin());
			size = copiedbuffend - buff.begin();
		}

		command(const std::array<char,rx_buffer_size>& buff, const size_t size):
			buff{buff}, size{size} {}

		size_t getSize() const {
			return size;
		}

		uint16_t getChecksum() const {
			return utils::hex2int<uint16_t>(buff.data() + size - checksum_backset);
		}

		CommandReceiver::Command getCommand() const {
			if (strncmp(buff.data()+command_offset, "USZST", 5) == 0) return CommandReceiver::Command::CODE_USZST;
			else
			if (strncmp(buff.data()+command_offset, "USZDS", 5) == 0) return CommandReceiver::Command::CODE_USZDS;
			else
			if (strncmp(buff.data()+command_offset, "USZQA", 5) == 0) return CommandReceiver::Command::CODE_USZQA;
			else
			if (strncmp(buff.data()+command_offset, "USZQD", 5) == 0) return CommandReceiver::Command::CODE_USZQD;
			else
			return CommandReceiver::Command::INVALID;
		}

		uint16_t calculate_checksum() const {
			uint16_t f16_sum[2];
			checksum::fletcher16_init(f16_sum);
			for(const char* i = buff.data()+1; *i != '*'; i++)
				checksum::fletcher16_update(f16_sum, *i);

			return checksum::fletcher16_get_chksum(f16_sum);
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

			if (this->getCommand() == CommandReceiver::Command::INVALID)
				return false;

			return true;
		}

		size_t getNumberOfParams() const{
			return std::count(buff.cbegin() + command_offset, buff.cbegin() + this->getSize() - serial_backset, ',');
		}

		char getParamC (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return *(i+1);
						}
					}
			}
			return '\0';
		}

		uint8_t getParam8 (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return utils::hex2int<uint8_t>(i+1);
						}
					}
			}
			return 0;
		}

		uint16_t getParam16 (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return utils::hex2int<uint16_t>(i+1);
						}
					}
			}
			return 0;
		}

		uint32_t getParam32 (size_t param_num) const {
			for(const char* i = buff.data()+command_offset; *i != '#'; i++){
					if (*i == ','){
						param_num--;
						if(param_num == 0){
							return utils::hex2int<uint32_t>(i+1);
						}
					}
			}
			return 0;
		}

		uint8_t getSerial() const {
			return utils::hex2int<uint8_t>(buff.data()+size-serial_backset);
		}
	};
}

extern CommandReceiver::command last_comm;
extern bool last_comm_processed;
