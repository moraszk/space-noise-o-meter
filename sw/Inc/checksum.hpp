#pragma once

#include <cstdint>

namespace checksum{
    //! Calculates flatcher16 checksum, does NOT include *end
    /*!
        \param begin from where the checksum is calculated (it is included)
        \param end untis this address the checksum is calculated (excluded)
    */
    uint16_t get_checksum(const char* begin, const char*const end);
}
