#include <iostream>
#include "utils.hpp"
#include <cstring>
#include "utils.cpp"

int main(){
    std::array<uint8_t, 16> out;
    char zero[1]={0};
    
    std::array<uint8_t, 12> test1 = {'M', 'a','n', 'M', 'a', 'n' , 'M' ,'a', 'n', 'M', 'a', 'n'};
    utils::base64::encode<12>(out, test1);
    std::cout << std::endl << out.data() << std::endl;
    return strncmp(out.data(), "TWFuTWFuTWFuTWFu", 16);
    return 0;
}
