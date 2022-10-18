#include <iostream>
#include "utils.hpp"
#include <cstring>
#include "utils.cpp"
#include <string_view>

int main(){
    /*using namespace std::literals;
    
    for(int i =0 ;i < 256;i++){
        std::cout << utils::char2hex(i).data()[0] << hex_lookup[i].data()[1] << std::endl;
    }*/
    
    if (strncmp(utils::char2hex(0x00).data(), "00", 2) != 0) return 2;
    if (strncmp(utils::char2hex(0x0a).data(), "0a", 2) != 0) return 3;
    if (strncmp(utils::char2hex(0xb0).data(), "b0", 2) != 0) return 4;
    if (strncmp(utils::char2hex(0xff).data(), "ff", 2) != 0) return 5;
    
    return 0;
}
