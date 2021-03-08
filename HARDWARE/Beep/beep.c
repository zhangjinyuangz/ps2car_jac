#include "beep.h"
#include "delay.h"
/**************************************************************************
�������ܣ�������IO��ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/

void Beep_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitStructure;    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;  //������-->PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������   �������:���������,�͵�ƽ,������������; ����ṹһ����ָ���������ֱܷ����������źŵĿ���,������һ�������ܵ�ͨ��ʱ����һ����ֹ���ߵ͵�ƽ�� IC �ĵ�Դ�Ͷ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO���ٶ�Ϊ50MHZ
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//���ݲ�����ʼ��PB12	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);				 //PB12 �����

}
/**************************************************************************
�������ܣ����������Ժ���
��ڲ�������
����  ֵ���� 
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
