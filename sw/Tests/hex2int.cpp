#include <cstdint>
#include <iostream>
#include "utils.hpp"

int main(){
	if (utils::hex2int<uint8_t>("ff") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("Ff") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("04") != 0x04) return -1;
	if (utils::hex2int<uint8_t>("40") != 0x40) return -1;
	if (utils::hex2int<uint8_t>("00") != 0x00) return -1;
	
	if (utils::hex2int<uint8_t>("ff000") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("Ff000") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("04000") != 0x04) return -1;
	if (utils::hex2int<uint8_t>("40000") != 0x40) return -1;
	if (utils::hex2int<uint8_t>("00000") != 0x00) return -1;

	if (utils::hex2int<uint8_t>("fffff") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("Fffff") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("04fff") != 0x04) return -1;
	if (utils::hex2int<uint8_t>("40fff") != 0x40) return -1;
	if (utils::hex2int<uint8_t>("00fff") != 0x00) return -1;

	if (utils::hex2int<uint8_t>("ff,") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("Ff,") != 0xff) return -1;
	if (utils::hex2int<uint8_t>("04,") != 0x04) return -1;
	if (utils::hex2int<uint8_t>("40,") != 0x40) return -1;
	if (utils::hex2int<uint8_t>("00,") != 0x00) return -1;

	if (utils::hex2int<uint16_t>("ffff") != 0xffff) return -1;
	if (utils::hex2int<uint16_t>("00Ff") != 0x00ff) return -1;
	if (utils::hex2int<uint16_t>("ae04") != 0xae04) return -1;
	if (utils::hex2int<uint16_t>("0000") != 0x0000) return -1;

	if (utils::hex2int<uint16_t>("ffff,,,") != 0xffff) return -1;
	if (utils::hex2int<uint16_t>("00Ff,,,") != 0x00ff) return -1;
	if (utils::hex2int<uint16_t>("ae04,,,") != 0xae04) return -1;
	if (utils::hex2int<uint16_t>("0000,,,") != 0x0000) return -1;

	if (utils::hex2int<uint32_t>("ffffffff") != 0xffffffff) return -1;
	if (utils::hex2int<uint32_t>("000000Ff") != 0x000000ff) return -1;
	if (utils::hex2int<uint32_t>("aeaeae04") != 0xaeaeae04) return -1;
	if (utils::hex2int<uint32_t>("00000000") != 0x00000000) return -1;

	if (utils::hex2int<uint16_t>("qqqq") != 0x0000) return -1;
	if (utils::hex2int<uint16_t>("qqFf") != 0x00ff) return -1;
	if (utils::hex2int<uint16_t>("##04") != 0x0004) return -1;
	if (utils::hex2int<uint16_t>("0=-;") != 0x0000) return -1;
	
	return 0;
}
