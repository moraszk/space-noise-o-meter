#pragma once
#include <string_view>

namespace command{
    const constexpr std::string_view longest_reply = "$SUTEL,1234567890123456789#00*1234\r\n";

    enum class Destinition : uint8_t {
		// University of Debrecen
		DE = 1,
		// University of Győr
		GY = 2,
		// University of Szeged
		SZ = 3,
		// University of Óbuda
		OBU = 4,
		// On-Board Computer
		OBC = 0,
		UNKNOWN =5,
	    // University of Szeged - student (this project)
		SU = 6,
	};
}
