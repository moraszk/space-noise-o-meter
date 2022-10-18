#include "watchdog.hpp"

void wdg::init()
{
 
		//1. Enable the IWDG by writing 0x0000 CCCC in the IWDG key register (IWDG_KR)
		IWDG->KR = 0xCCCC << IWDG_KR_KEY_Pos;	

		//2. Enable register access by writing 0x0000 5555 in the IWDG key register (IWDG_KR)
		IWDG->KR = 0x5555 << IWDG_KR_KEY_Pos;
		
		//3. Write the prescaler by programming the IWDG prescaler register (IWDG_PR) from 0 to 7
		IWDG->PR = IWDG_PR_PR_0;

		//4. Write the IWDG reload register (IWDG_RLR).
		IWDG->RLR = 0x4F;
		
		//5. Wait for the registers to be updated (IWDG_SR = 0x0000 0000).
		while(IWDG->SR)
		{
			//add time out
		}
		
		//6. Refresh the counter value with IWDG_RLR (IWDG_KR = 0x0000 AAAA).
		IWDG->KR = 0x4F << IWDG_KR_KEY_Pos;
		
}
