#include <array>
#include <cstdint>
#include "utils.hpp"
#include "../Src/utils.cpp"

int main(){
    utils::ringbuffer<uint8_t, 5> rb;
    uint32_t ret = 0;
    
    rb.put('a');
    rb.put('b');
    rb.put('c');
    ret+=rb.get()-'a';
    rb.put('d');
    ret+=rb.get()-'b';
    rb.put('e');
    ret+=rb.get()-'c';
    ret+=rb.get()-'d';
    rb.put('f');
    ret+=rb.get()-'e';
    rb.put('g');
    rb.put('h');
    ret+=rb.empty() ? 1 : 0;
    ret+=rb.get()-'f';
    ret+=rb.get()-'g';
    ret+=rb.get()-'h';
    ret+=rb.empty() ? 0 : 1;
    return ret;
}
