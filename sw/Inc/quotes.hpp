#pragma once
#include <cstdint>

namespace quotes{   
    unsigned char* get_chunk(std::size_t chunk);
    extern std::size_t number_of_chunks;
}
