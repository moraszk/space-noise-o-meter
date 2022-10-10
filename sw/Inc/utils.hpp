#pragma once
#include <concepts>
#include <array>
#include <cstdint>

namespace utils{
    template<std::integral T>
    constexpr auto hex2int(const char* const in) -> T{
        T ret = 0;
        
        for(const char* i = in; i<in+(sizeof(T)*2); i++){ 
            const char c = *i;
            ret<<=4;
            
                 if(c <= 'F' && c >= 'A') ret += c-('A'-10);
            else if(c <= 'f' && c >= 'a') ret += c-('a'-10);
            else if(c <= '9' && c >= '1') ret += c-'0';
        }
        
        return ret;
    }
    
    namespace base64{
        std::array<char, 4> encode_triplet(std::uint8_t a, std::uint8_t b, std::uint8_t c);
        
        template<std::size_t in_long>
        void encode(std::array<uint8_t, in_long*4/3>& out, const std::array<uint8_t, in_long> in){
            for(
                std::size_t i=0;
                i<16;
                in+=3,i+=4
            ){
                std::array coded = encode_triplet(in[0], in[1], in[2]);
                std::copy(coded.begin(), coded.end(), out.begin()+i);
            }
        }
    }
}
