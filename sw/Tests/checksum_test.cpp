#include "checksum.hpp" 
#include "../Src/checksum.cpp"
#include <string_view>
#include <iostream>

int main(){
    {
    const std::string_view example = "$SURUN,05,0D80,0001D97C#7B*";

    //std::cout << example << std::hex << checksum::get_checksum(example.begin()+1, example.end()-1) << std::endl;

    if (checksum::get_checksum(example.begin()+1, example.end()-1) != 0x38bb)
        return 1;
    }

    //----------------------------------------------------------

    {
    const std::string_view example = "$CMDHP,05,0D80,0001D97C#7B*";

    //std::cout << example << std::hex << checksum::get_checksum(example.begin()+1, example.end()-1) << std::endl;

    if (checksum::get_checksum(example.begin()+1, example.end()-1) != 0xAD8A)
        return 1;
    }

    //----------------------------------------------------------

    {
    const std::string_view example = "$SURUN,05,0001D97C#7B*";

    //std::cout << example << std::hex << checksum::get_checksum(example.begin()+1, example.end()-1) << std::endl;

    if (checksum::get_checksum(example.begin()+1, example.end()-1) != 0xCFB2)
        return 1;
    }

        //----------------------------------------------------------

    {
    const std::string_view example = "$SURUN,05,0001D97C#7B*";

    //std::cout << example << std::hex << checksum::get_checksum(example.begin()+1, example.end()-1) << std::endl;

    if (checksum::get_checksum(example.begin()+1, 50) != 0xCFB2)
        return 1;
    }
    
    return 0;
}
