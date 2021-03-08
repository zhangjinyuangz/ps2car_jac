#include "servor.h"
#include "usart.h"
#include "delay.h"
#include "common.h"
u8 count2;				 //每个变量用作8路舵机先后赋值控制
#define MAXPWM 2505		 //舵机最大PWM控制脉宽2.5ms宏定义
extern uint16 CPWM[9];
extern uint8 flag_vpwm;
#define	LED PBout(14) 
unsigned int led_time=0;
extern unsigned char flag_scan_ps2;
u8 time=0;

void Servor_GPIO_Config(void)	
{
	GPIO_InitTypeDef GPIO_InitStructure;	
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
}
/************************GPIO电平反转函数1*****************************************/ 
void Flip_GPIO_One(void)
{
	switch(count2)
	{  		
		case 1: TIM2->ARR=CPWM[1];				 //功能同上
				GPIO_SetBits(GPIOB,GPIO_Pin_15);  
				break;
		
		case 2:	TIM2->ARR=MAXPWM-CPWM[1]; 
				GPIO_ResetBits(GPIOB,GPIO_Pin_15); 
				break;

		case 3:	TIM2->ARR=CPWM[2]; 
				GPIO_SetBits(GPIOA,GPIO_Pin_8); 
				break;
		
		case 4:	TIM2->ARR=MAXPWM-CPWM[2];  
				GPIO_ResetBits(GPIOA,GPIO_Pin_8); 
				break;

		case 5:	TIM2->ARR=CPWM[3];  
				GPIO_SetBits(GPIOB,GPIO_Pin_5); 
				break;
		
		case 6:	TIM2->ARR=MAXPWM-CPWM[3];  
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				break;

		case 7:	TIM2->ARR=CPWM[4];  
				GPIO_SetBits(GPIOB,GPIO_Pin_4); 
				break;
		
		case 8:	TIM2->ARR=MAXPWM-CPWM[4];  
				GPIO_ResetBits(GPIOB,GPIO_Pin_4);
				break;

		case 9:	TIM2->ARR=CPWM[5];  
				GPIO_SetBits(GPIOB,GPIO_Pin_3); 
				break;
		
		case 10:TIM2->ARR=MAXPWM-CPWM[5];  
				GPIO_ResetBits(GPIOB,GPIO_Pin_3);
				break;

		case 11:TIM2->ARR=CPWM[6];  
				GPIO_SetBits(GPIOA,GPIO_Pin_15); 
				break;
		
		case 12:TIM2->ARR=MAXPWM-CPWM[6];  
				GPIO_ResetBits(GPIOA,GPIO_Pin_15);
				break;

		case 13:TIM2->ARR=CPWM[7];  
				//GPIO_SetBits(GPIOB,GPIO_Pin_5); 
				break;
		
		case 14:TIM2->ARR=MAXPWM-CPWM[7];  
				//GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				break;

		case 15:TIM2->ARR=CPWM[8];  
				//GPIO_SetBits(GPIOB,GPIO_Pin_4); 
				break;
		
		case 16:TIM2->ARR=MAXPWM-CPWM[8]; 
				//GPIO_ResetBits(GPIOB,GPIO_Pin_4); 
			led_time++;
			if(led_time==25)
			{
		   led_time=0;
			 LED=~LED;
			}
			count2=0; 
			break;
	}	
	count2++;
}

/************************舵机控制函数1*********************************************/
void Servo1(void)
{		
//	count2++; 
	Flip_GPIO_One();						 //反转IO电平

}


