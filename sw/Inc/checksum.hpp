#pragma once

#include <cstdint>

namespace checksum{
    uint16_t fastmod255(uint16_t x);
    void fletcher16_init(uint16_t * sum);
    void fletcher16_update(uint16_t * sum, uint8_t data);
    uint16_t fletcher16_get_chksum(uint16_t * sum);
    
    //! Calculates flatcher16 checksum, does NOT include *to
    /*!
        \param from from where the checksum is calculated (it is included)
        \param to untis this address the checksum is calculated (excluded)
    */
    uint16_t get_checksum(const char* from, const char* const to);
}
