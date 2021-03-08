#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(u32 nTime);
void Delay_ms(u32 nTime);  
void tb_delay(u32 t);


#endif
