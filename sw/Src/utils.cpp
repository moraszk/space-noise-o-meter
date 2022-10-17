#include "utils.hpp"
#include <cstdint>
#include <ranges>
#include <numeric>
#include <string_view>
#include <array>

namespace{
    std::string_view constexpr encode_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
    static_assert(encode_table.size() == 64, "Base64 lookup table not 64 long");
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
