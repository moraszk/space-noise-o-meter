#include <algorithm>
#include <array>
#include <cstdio>
#include <string_view>

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
        "Build with the donations of our sponsors: RET Elektronika and Eurocircuits",
        "Outher quotes"
    );
}

namespace quotes{
    static std::array<char, 16> nextdatagram;
    
    void CalculateNextDatagram(){
            static size_t quotepartindex = 0;
            
    }
}
