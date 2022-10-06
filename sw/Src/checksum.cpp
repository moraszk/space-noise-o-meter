#include "checksum.hpp"

uint16_t checksum::fastmod255(uint16_t x)
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

void checksum::fletcher16_init(uint16_t *sum)
{
  sum[0] = 0u;
  sum[1] = 0u;
}

void checksum::fletcher16_update(uint16_t *sum, uint8_t data)
{
  sum[0] = fastmod255(sum[0] + (uint16_t) data);
  sum[1] = fastmod255(sum[1] + sum[0]);
}

uint16_t checksum::fletcher16_get_chksum (uint16_t * sum)
{
  return ((sum[0] & 0x00FF) + ((sum[1] & 0x00FF) << 8u)) ;
}

uint16_t checksum::get_checksum(const char* from, const char* const to){
  uint16_t f16_sum[2];
  checksum::fletcher16_init(f16_sum);
  for(; from != to; from++)
      checksum::fletcher16_update(f16_sum, *from);

  return checksum::fletcher16_get_chksum(f16_sum);
}

