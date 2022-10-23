#include "utils.hpp"
#include <cstdint>
#include <ranges>
#include <numeric>
#include <string_view>
#include <array>
#include <algorithm>

namespace{
    std::string_view constexpr encode_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
    static_assert(encode_table.size() == 64, "Base64 lookup table not 64 long");
    
    consteval std::array<char, 2> byte2hex(int in){
        const constexpr std::string_view hex_values = "0123456789ABCDEF";
        static_assert(hex_values.size() == 16, "Bad hex lookup-table");
        
        return {
            hex_values.at(in / 16)
            ,
            hex_values.at(in % 16)
        };
    }

    inline std::array<char, 2> byte2ID(int in){
        return {
            encode_table[in / encode_table.size()]
            ,
            encode_table[in % encode_table.size()]
        };
    }

    static_assert(byte2hex(10)[0]=='0' && byte2hex(10)[1]=='A', "Byte2hex test failed");
    static_assert(byte2hex(0x1b)[0]=='1' && byte2hex(0x1b)[1]=='B', "Byte2hex test failed");
    static_assert(byte2hex(0xb0)[0]=='B' && byte2hex(0xb0)[1]=='0', "Byte2hex test failed");
    
    consteval std::array<std::array<char, 2>, 256> lookup_generator(){
        std::array<std::array<char, 2>, 256> ret = {{}};
        for(size_t i = 0; i < 256; i++){
            ret[i] = byte2hex(i);
        }
        return ret;
    }
    
    constexpr std::array<std::array<char, 2>, 256> hex_lookup = lookup_generator(); //TODO constinit?
    
    static_assert(hex_lookup[10].data()[0] == '0' && hex_lookup[10].data()[1 == 'A'], "Hex test failed");
}

//Source: https://matgomes.com/base64-encode-decode-cpp/
std::array<char, 4> utils::base64::encode_triplet(std::uint8_t a, std::uint8_t b, std::uint8_t c){
    std::uint32_t const concat_bits = (a << 16) | (b << 8) | c;

    return {
        encode_table[(concat_bits >> 18) & 0b0011'1111],
        encode_table[(concat_bits >> 12) & 0b0011'1111],
        encode_table[(concat_bits >> 6) & 0b0011'1111],
        encode_table[concat_bits & 0b0011'1111]
        };
}

const std::array<char, 2>& utils::char2hex(const unsigned char in){
    return hex_lookup[in];
}

const std::array<char, 2> utils::char2ID(const size_t in){
    return byte2ID(in);
}

void utils::copyashex(const uint16_t number, char* begin){
        auto secondbyte = char2hex(number&0xff);
        auto firstbyte  = char2hex(number>>8);
        *begin = firstbyte[0];
        begin++;
        *begin = firstbyte[1];
        begin++;
        *begin = secondbyte[0];
        begin++;
        *begin = secondbyte[1];
    }
