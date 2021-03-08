#include "beep.h"
#include "delay.h"
/**************************************************************************
函数功能：蜂鸣器IO初始化
入口参数：无
返回  值：无 
**************************************************************************/

void Beep_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;  //蜂鸣器-->PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出   推挽输出:可以输出高,低电平,连接数字器件; 推挽结构一般是指两个三极管分别受两互补信号的控制,总是在一个三极管导通的时候另一个截止。高低电平由 IC 的电源低定。
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHZ
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//根据参数初始化PB12	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);				 //PB12 输出高

}
/**************************************************************************
函数功能：蜂鸣器测试函数
入口参数：无
返回  值：无 
**************************************************************************/ 
void Beep_Test(void)
{
BEEP(ON);  
Delay_ms(500);
BEEP(OFF);
Delay_ms(500);
}

void Beep_Yell(void)
{
BEEP(ON); 
Delay_ms(10);	
BEEP(OFF);
Delay_ms(10);
}
