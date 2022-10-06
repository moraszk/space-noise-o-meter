#pragma once
#include <concepts>

namespace utils{
    template<std::integral T>
    constexpr auto hex2int(const char* const in) -> T{
        T ret = 0;
        
        for(const char* i = in; i<in+(sizeof(T)*2); i++){ 
            const char c = *i;
            ret<<=4;
            
                 if(c <= 'F' && c >= 'A') ret += c-('A'-10);
            else if(c <= 'f' && c >= 'a') ret += c-('a'-10);
            else if(c <= '9' && c >= '1') ret += c-'0';
        }
        
        return ret;
    }
}
