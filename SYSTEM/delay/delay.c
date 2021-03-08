#include "delay.h"

u32 a;
static __IO u32 TimingDelay;
/**************************????????*********************************************/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms????
	 * SystemFrequency / 100000	 10us????
	 * SystemFrequency / 1000000 1us????
	 */
	if (SysTick_Config(SystemCoreClock/1000000))	// ST3.5.0???
	{ 
		while (1);
	}
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
/***************************************************************************************/
/*************************??????**************************************************/
void Delay_us(u32 nTime)           
{ 
	TimingDelay = nTime;	
  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
/***************************************************************************************/
/*************************??????**************************************************/
void Delay_ms(u32 nTime)           
{ 
	TimingDelay = nTime*1000;	
  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
/***************************************************************************************/
/**************************??????*************************************************/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/***************************************************************************************/


void SysTick_Handler(void) {   
	TimingDelay_Decrement();
}



