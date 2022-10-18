#pragma once
#include <string_view>

namespace command{
    const constexpr std::string_view longest_reply = "$SUTEL,1234567890123456789#00*1234\r\n";
    
    enum class Destinition : uint8_t {
		DE = 1,
		GY = 2,
		SZ = 3,
		OBU = 4,
		OBC = 0,
		UNKNOWN =5,
		SU = 6,
	};
}
