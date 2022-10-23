#include <cstdint>
#include <iostream>
#include "utils.hpp"
#include "../Src/utils.cpp"

int main(){
    for(int i=0;i<1000;i++)
        std::cout << utils::char2ID(i)[0] << utils::char2ID(i)[1] << std::endl;

	return 0;
}

