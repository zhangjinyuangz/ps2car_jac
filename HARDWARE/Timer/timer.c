/**********************************************************************************/
#include "timer.h"


/**********************��ʱ��3�ж����ú���*********************************************/
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
/************************��ʱ��3���ú���***********************************************/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
	  TIM_DeInit(TIM2);											/* ����������ʱ�� */

    TIM_TimeBaseStructure.TIM_Period=9;		 				/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    TIM_TimeBaseStructure.TIM_Prescaler=71;						/* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=0; 		/* �ⲿʱ�Ӳ�����Ƶ */
	  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);						/* �������жϱ�־ */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);					/* �����жϴ���*/   
	  TIM_Cmd(TIM2,DISABLE);	
}



/**************************************************************************************/
/************************��ʱ����ʼ������*********************************************/
void Timer_Init(void)
{

	 TIM2_NVIC_Configuration();
	 TIM2_Configuration();


}
/**************************************************************************************/
/************************������ʱ������************************************************/
void Timer_ON(void)
{	
	TIM_Cmd(TIM2,ENABLE);

}
/**************************************************************************************/
/************************�رն�ʱ������************************************************/
void Timer_OFF(void)
{	
	TIM_Cmd(TIM2,DISABLE);

}
/**************************************************************************************/

