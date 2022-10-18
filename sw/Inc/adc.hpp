#pragma once
#include <cstdint>
#include "stm32l010x4.h"

namespace adc{
	
	void init_noise();
	void init_hall_sensor();
	void init_temp();
	}
