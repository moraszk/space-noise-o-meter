#include <iostream>
#include "utils.hpp"
#include <cstring>
#include "utils.cpp"

int main(){
    std::array<char, 16> out;
    char zero[1]={0};
    
    std::array<char, 12> test1 = {'M', 'a','n', 'M', 'a', 'n' , 'M' ,'a', 'n', 'M', 'a', 'n'};
    utils::base64::encode<12>(out, test1.begin());
    //std::cout << std::endl << out.data() << std::endl;
    int t1 = strncmp(out.data(), "TWFuTWFuTWFuTWFu", 16) == 0 ? 0 :1;

    std::array<char, 12> test2 = {'A', 'S','D', 'Q', 'W', 'E' , '1' ,'2', '3', 't', 'z', 'u'};
    utils::base64::encode<12>(out, test2.begin());
    //std::cout << std::endl << out.data() << std::endl;
    int t2 = strncmp(out.data(), "QVNEUVdFMTIzdHp1", 16) == 0 ? 0 :1;

    std::array<char, 12> test3 = {'y', 'x','c', '0', '1', '0' , '1' ,'6', '9', 'i', 'g', 'j'};
    utils::base64::encode<12>(out, test3.begin());
    //std::cout << std::endl << out.data() << std::endl;
    int t3 = strncmp(out.data(), "eXhjMDEwMTY5aWdq", 16) == 0 ? 0 :1;
    return t1 + t2 + t3;
}
