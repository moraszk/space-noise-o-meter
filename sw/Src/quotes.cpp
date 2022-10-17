#include <algorithm>
#include <array>
#include <cstdio>
#include <string_view>
#include "utils.hpp"

using namespace std::literals;

template<size_t SeparatorSize, size_t... ArraySizes>
constexpr auto concat(const char (&separator)[SeparatorSize], const char (&... strs)[ArraySizes]) noexcept {
    static_assert(SeparatorSize > 0 && sizeof...(strs) > 0 && ((ArraySizes > 0) && ...));
    std::array<char, ((ArraySizes - 1) + ...) + (sizeof...(strs) - 1) * (SeparatorSize - 1) + 1> result = {0};
    std::size_t index{};

    ((  std::copy_n(std::begin(strs), ArraySizes - 1, std::begin(result) + index),
        //index > 0 ? std::copy_n(std::begin(separator), SeparatorSize - 1, std::begin(result) + index - (SeparatorSize - 1)) : std::begin(result),
        index > 0 ? std::copy_n(std::begin(separator), SeparatorSize - 1, std::begin(result) + index - (SeparatorSize - 1)) : std::begin(result),
        index += (ArraySizes - 1 + SeparatorSize - 1)), ...);
    return result;
}

static_assert(std::string_view{concat(", ", "hello", "world", "test").data()} == "hello, world, test"sv);

namespace{
    const constexpr std::array book = concat(
        "||", //Separator
        
        //Quotes
        "Hello",
        "World",
        "Build with the donations of our sponsors: RET Elektronika, Eurocircuits, FDH Kft.",
        "Outher quotesfffdvdddddddddddddddd"
    );

    const constexpr size_t datagram_lenght_ascii = 12;
    const constexpr size_t datagram_length_base64 = datagram_lenght_ascii * 4 / 3;

    static_assert(datagram_lenght_ascii < 19 -1 , "Maximum telemetry answer 19 (minus one char for classification)");
}

namespace quotes{
    static std::array<char, 16> nextdatagram;
    
    void CalculateNextDatagram(){
            static size_t quotepartindex = 0;
            utils::base64::encode<12>(nextdatagram, book.begin()+quotepartindex);

            static_assert( (book.size()%datagram_lenght_ascii) == 0, "Overflow when encoding the book");
            quotepartindex+=datagram_lenght_ascii;
            quotepartindex%=book.size();
    }
}
