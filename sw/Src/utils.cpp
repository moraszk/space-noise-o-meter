#include "utils.hpp"
#include <cstdint>
#include <ranges>
#include <numeric>
#include <string_view>
#include <array>

namespace{
    /*consteval std::array<char, 64> base64_lookup_table(){
        std::array<char, 64> ret;

        std::iota(ret.begin(), ret.begin()+('Z'-'A')+1, 'A' );
        std::iota(ret.begin()+('Z'-'A')+2, ret.begin()+2*('Z'-'A')+3, 'a' );
        std::iota(ret.begin()+2*('Z'-'A')+2, ret.begin()+2*('Z'-'A')+13, '0' );
        ret[62]='X';
        ret[63]='X';

        return ret;
    }

    static_assert(std::string_view{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-"}==std::string_view{base64_lookup_table().data()});
    
    constexpr std::array<char, 64> lookup = base64_lookup_table();*/
    std::array<char, 65> constexpr encode_table = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-"}; //TODO FIX!!!!!!!!!
}

//Source: https://matgomes.com/base64-encode-decode-cpp/
std::array<char, 4> utils::base64::encode_triplet(std::uint8_t a, std::uint8_t b, std::uint8_t c){
    std::uint32_t const concat_bits = (a << 16) | (b << 8) | c;

    auto const b64_char1 = encode_table[(concat_bits >> 18) & 0b0011'1111];
    auto const b64_char2 = encode_table[(concat_bits >> 12) & 0b0011'1111];
    auto const b64_char3 = encode_table[(concat_bits >> 6) & 0b0011'1111];
    auto const b64_char4 = encode_table[concat_bits & 0b0011'1111];
    return {b64_char1, b64_char2, b64_char3, b64_char4};
}
