#include "checksum.hpp" 
#include "../Src/checksum.cpp"

int main(){
    const char buff[] = "$CMDHP,05,0D80,0001D97C*";
    
    uint16_t f16_sum[2];
    checksum::fletcher16_init(f16_sum);
    for(const char* i = buff+1; *i != '*'; i++)
        checksum::fletcher16_update(f16_sum, *i);

    return checksum::fletcher16_get_chksum(f16_sum) == 0xad8a;
}
