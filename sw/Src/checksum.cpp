#include "checksum.hpp"

namespace checksum{
  uint16_t fastmod255(uint16_t x)
  {
    // max( x ) == 510
    if(x < 255u)
    {
      return x;
    }
    x = x - 255u;
    if (x < 255u)
    {
      return x;
    }
    x = x - 255u;
    return x;
  }

  void fletcher16_update(uint16_t *sum, uint8_t data)
  {
    sum[0] = fastmod255(sum[0] + (uint16_t) data);
    sum[1] = fastmod255(sum[1] + sum[0]);
  }

  uint16_t fletcher16_get_chksum (uint16_t * sum)
  {
    return ((sum[0] & 0x00FF) + ((sum[1] & 0x00FF) << 8u)) ;
  }
}

uint16_t checksum::get_checksum(const char* begin, const char* const end){
  uint16_t f16_sum[2] = {0, 0};
  for(; begin < end; begin++)
      checksum::fletcher16_update(f16_sum, *begin);

  return checksum::fletcher16_get_chksum(f16_sum);
}

uint16_t checksum::get_checksum(const char* begin, uint32_t maximum_len){
  uint16_t f16_sum[2] = {0, 0};
  for(;
      *begin != '*' && maximum_len!=0;
      begin++, maximum_len--)
      checksum::fletcher16_update(f16_sum, *begin);

  return checksum::fletcher16_get_chksum(f16_sum);
}
