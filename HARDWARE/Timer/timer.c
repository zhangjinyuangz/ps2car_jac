/**********************************************************************************/
#include "timer.h"


/**********************定时器3中断配置函数*********************************************/
void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**************************************************************************************/

/**************************************************************************************/
/************************定时器3配置函数***********************************************/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
	  TIM_DeInit(TIM2);											/* 重新启动定时器 */

    TIM_TimeBaseStructure.TIM_Period=9;		 				/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_Prescaler=71;						/* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=0; 		/* 外部时钟采样分频 */
	  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/* 向上计数模式 */
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);						/* 清除溢出中断标志 */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);					/* 开启中断触发*/   
	  TIM_Cmd(TIM2,DISABLE);	
}



/**************************************************************************************/
/************************定时器初始化函数*********************************************/
void Timer_Init(void)
{

	 TIM2_NVIC_Configuration();
	 TIM2_Configuration();


}
/**************************************************************************************/
/************************开启定时器函数************************************************/
void Timer_ON(void)
{	
	TIM_Cmd(TIM2,ENABLE);

}
/**************************************************************************************/
/************************关闭定时器函数************************************************/
void Timer_OFF(void)
{	
	TIM_Cmd(TIM2,DISABLE);

}
/**************************************************************************************/

