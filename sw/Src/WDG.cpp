#include "watchdog.hpp"
#include "stm32l010x4.h"

void wdg::init()
{
	IWDG->KR = 0x0000CCCCU;
	IWDG->KR = 0x00005555U;
	IWDG->PR = (IWDG_PR_PR_2 | IWDG_PR_PR_1);
	IWDG->RLR = 4095;
}

void wdg::refresh()
{
	IWDG->KR = 0x0000AAAAU;
}

