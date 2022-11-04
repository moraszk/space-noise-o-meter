#include <string>
#include <iterator>
#include <array>
#include "checksum.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include "../Src/checksum.cpp"
#include "../Src/utils.cpp"
#include "command.hpp"

#define class struct

#include "CommandReceiver.hpp"


void test0() {

  char str[] = "";

  std::string t1str(str);
  if (rx_buffer_size < t1str.size())
    throw new std::runtime_error("Buffer size error");

  const CommandReceiver::mrc_frame t1(t1str);

  if (t1.isValid()) {
    throw new std::runtime_error("Should not be valid");
  }
}

void test1(){
    std::string t1str {"$SURUN,05,0001D97C#7B*CFB2\r\n"};
    if (rx_buffer_size < t1str.size())  throw new std::runtime_error("Buffer size error");

    const CommandReceiver::mrc_frame t1(t1str);

    if(t1.getSize() != t1str.size()) throw new std::runtime_error("Size error");
    if(t1.getChecksum() != 0xcfb2) throw new std::runtime_error("Checksum error");
    if(t1.getDestinition() != command::Destinition::SU) throw new std::runtime_error("Dst error");
    if(t1.getCommand() != CommandReceiver::Command::RUN) throw new std::runtime_error("Command error");
    if(t1.calculate_checksum() != 0xcfb2) throw new std::runtime_error("Checksum error2");
    if(!t1.isValid()) throw new std::runtime_error("Validity check error");
    if(strncmp(",05", t1.getPayload(), 3) != 0) throw new std::runtime_error("payload error");
/*    if(t1.getNumberOfParams() != 3)  throw new std::runtime_error("Param number error");

    if(t1.getParam32(3) != 0x0001D97C)  throw new std::runtime_error("Param read error");
    if(t1.getParam16(2) != 0x0d80)  throw new std::runtime_error("Param read error");
    if(t1.getParam8(1) != 0x05)  throw new std::runtime_error("Param read error");*/

    if(t1.getSerial() != 0x7b)   throw new std::runtime_error("Serial error");
}

void test2(){
    std::string t2str {"$USZQD,Q,09,0484,0001DDC8#FF*704A\r\n"};
    if (rx_buffer_size < t2str.size())  throw new std::runtime_error("Buffer size error");

    const CommandReceiver::mrc_frame t2(t2str);

    if(t2.getSize() != t2str.size()) throw new std::runtime_error("Size error");
    if(t2.getChecksum() != 0x704a) throw new std::runtime_error("Checksum error");
    if(t2.getCommand() != CommandReceiver::Command::UNKNOWN) throw new std::runtime_error("Command error");
    if(t2.calculate_checksum() != 0x704a) throw new std::runtime_error("Checksum error2");
    if(!t2.isValid()) throw new std::runtime_error("Validity check error");
    /*
    if(t2.getNumberOfParams() != 4)  throw new std::runtime_error("Param number error");

    if(t2.getParam32(4) != 0x0001DDC8)  throw new std::runtime_error("Param read error");
    if(t2.getParam16(3) != 0x0484)  throw new std::runtime_error("Param read error");
    if(t2.getParam8(2) != 0x09)  throw new std::runtime_error("Param read error");
    if(t2.getParamC(1) != 'Q')  throw new std::runtime_error("Param read error");
    */
    if(t2.getSerial() != 0xff)   throw new std::runtime_error("Serial error");
}

void test3(){
    {
        const CommandReceiver::mrc_frame t3("$USZQD,Q,09,0484,0001DDC8#FF*704B\r\n");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
    {
        const CommandReceiver::mrc_frame t3("$USZQD,Q,09,0484,0001DDC8-FF*704A\r\n");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
    {
        const CommandReceiver::mrc_frame t3("$USZQD,Q,09,0484,0001DDC8#FF-704A\r\n");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
    {
        const CommandReceiver::mrc_frame t3("$USZQD,Q,09,0484,0001DDC8#FF*704A\r\t");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
    {
        const CommandReceiver::mrc_frame t3("$USZQD,Q,09,0484,0001DDC8#FF*704A\t\n");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
    {
        const CommandReceiver::mrc_frame t3("aUSZQD,Q,09,0484,0001DDC8#FF*704A\r\n");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
    //{
    //    const CommandReceiver::mrc_frame t3("$BSZQQ,Q,09,0484,0001DDC8#FF*704A\r\n");
    //    if(t3.isValid()) throw new std::runtime_error("Validity check error");
    //}
    {
        const CommandReceiver::mrc_frame t3("a");
        if(t3.isValid()) throw new std::runtime_error("Validity check error");
    }
}

int main(){
	try{
        test0();
		test1();
        test2();
        test3();
	} catch(const std::exception* e){
		std::cout << " " << e->what();
		return -1;
	}
	return 0;
}
