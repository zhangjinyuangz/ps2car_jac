#include "led.h"
#include "delay.h"


/**************************************************************************
�������ܣ�LED IO��ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void LED_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;     //LED-->PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO���ٶ�Ϊ50MHZ
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB14	
	GPIO_SetBits(GPIOB,GPIO_Pin_14);				//PB.14 �����

}
 /**************************************************************************
�������ܣ�LED ���Ժ��� ����LED 500msȻ��Ϩ��500ms ѭ��2��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void Led_Test(void)
{
		LED1(ON);
	  Delay_ms(500);
	  LED1(OFF);
	  Delay_ms(500);
		LED1(ON);
	  Delay_ms(500);
		LED1(OFF);
	  Delay_ms(500);
	 
}
