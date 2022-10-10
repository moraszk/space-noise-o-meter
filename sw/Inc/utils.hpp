#pragma once
#include <concepts>
#include <array>
#include <cstdint>
#include <iterator>

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
        
        template<std::size_t in_long, std::input_iterator InIt>
        void encode(std::array<char, in_long*4/3>& out, InIt in){
            static_assert((in_long%3) == 0, "Only whole char triplets are implemented!");
            for(
                std::size_t i=0, j=0;
                i<16;
                j+=3,i+=4
            ){
                std::array coded = encode_triplet(in[0+j], in[1+j], in[2+j]);
                std::copy(coded.begin(), coded.end(), out.begin()+i);
            }
        }

        //template<std::size_t s, typename T>
        //void encode(std::array<T, s*4/3>&, const std::array<T, s>)  -> void encode<s>; TODO deduction guide

    }
}
