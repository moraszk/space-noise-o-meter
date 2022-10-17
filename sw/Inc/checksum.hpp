#pragma once

#include <cstdint>

namespace checksum{
    //! Calculates flatcher16 checksum, does NOT include *end
    /*!
        \param begin from where the checksum is calculated (it is included)
        \param end untis this address the checksum is calculated (excluded)
    */
    uint16_t get_checksum(const char* begin, const char*const end);
    
    //! Calculates flatcher16 checksum until a '*' char is found
    /*!
        \param begin from where the checksum is calculated (it is included)
        \param number of chars to calculate at maximum
    */
    uint16_t get_checksum(const char* begin, uint32_t maximum_len);
}
