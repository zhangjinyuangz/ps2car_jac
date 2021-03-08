#include "sys.h"
#include "usart.h"	
#include "common.h"
#include "online.h"
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

u16 USART_RX_STA=0;       //����״̬���	  

u8 flag_recful=0;

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0); //ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
/**************************************************************************
�������ܣ�����1�ж���������
��ڲ�������
����  ֵ����
**************************************************************************/

void Uart1_NVIC_Init(void)
{
	  //Usart1 NVIC ����
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}
/**************************************************************************
�������ܣ�����2�ж���������
��ڲ�������
����  ֵ����
**************************************************************************/
void Uart2_NVIC_Init(void)
{
	  //Usart2 NVIC ����
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}
/**************************************************************************
�������ܣ�����1 IO��س�ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void Uart1_Gpio_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
		//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO�˿�ʱ�����50MHZ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

}
/**************************************************************************
�������ܣ�����1��س�ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void Uart2_Gpio_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//ʹ��USART2��GPIOAʱ��
		//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

}
/**************************************************************************
�������ܣ���ʼ��ѡ���Ӧ����
��ڲ�����uart_num  ���ں�ѡ�� ��Χ��1-2
����  ֵ����
**************************************************************************/
void Uart_Init(u16 uart_num)
{
	if(uart_num==1)
	{
		Uart1_NVIC_Init();  //����1�ж����������ʼ��
		Uart1_Gpio_Config();//����1��ӦIO��ʼ��
		
	}
	else if(uart_num==2)
	{
		Uart2_NVIC_Init();  //����2�ж����������ʼ��
		Uart2_Gpio_Config(); //����2��ӦIO��ʼ��
	}
}
/**************************************************************************
�������ܣ����ڳ�ʼ��������ã�����������
��ڲ�����USART_TypeDef* TUSARTx ��ѡ���ʼ����Ӧ����  bound��������ѡ��  ʵ����USART_Config(USART1,115200)  ��ʼ������1�������ò�����Ϊ115200
����  ֵ����
**************************************************************************/
void USART_Config(USART_TypeDef* TUSARTx,u32 bound) 
{
  
	USART_InitTypeDef USART_InitStructure;
 
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(TUSARTx, &USART_InitStructure); //��ʼ������
  USART_ITConfig(TUSARTx, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(TUSARTx, ENABLE);                    //ʹ�ܴ���

}

/**************************************************************************
�������ܣ����ڷ���һ���ַ�
��ڲ�����USART_TypeDef* TUSARTx ��ѡ���ʼ����Ӧ����  data Ҫ���͵��ַ�
����  ֵ����
**************************************************************************/

void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data)  
{  
    USART_SendData(USARTx, Data);  
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}  
}  

/**************************************************************************
�������ܣ����ڷ���һ���ַ���
��ڲ�����USART_TypeDef* TUSARTx ��ѡ���ʼ����Ӧ����  *str Ҫ���͵��ַ���
����  ֵ����
**************************************************************************/

void UART_PutStr (USART_TypeDef* USARTx,const char *str) 
{
	unsigned int i = 0;
	while(*str != '\0' && i < 500)
	{
		UART_PutChar(USARTx, *str++); 
		i++;
	}
}
/**************************************************************************
�������ܣ���һ���޷���������ת���ɶ�Ӧ�ַ�������ͨ������1���ͳ�ȥ
��ڲ���: unit16 data
����  ֵ����
**************************************************************************/
void UART_Put_Num(uint16  dat)
{
 char temp[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 u32tostr(dat,temp);
 UART_PutStr(USART1,temp); 
}
/**************************************************************************
�������ܣ���һ���޷���������ת���ɶ�Ӧ�ַ�������ͨ������1���ͳ�ȥ
��ڲ���: �ַ���*inf  �޷������� dat
����  ֵ����
**************************************************************************/
void UART_Put_Inf(const char *inf,uint16 dat)
{
 UART_PutStr (USART1,inf); 
 UART_Put_Num(dat);
 UART_PutStr (USART1,"\n");  
}
/**************************************************************************
�������ܣ�����1�ж���ں��� 
��ڲ���: ��
����  ֵ����
**************************************************************************/
void USART1_IRQHandler(void)                
{
	static unsigned int i=0;
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{ 
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);	
					
		if(!flag_recful)
		{
			USART_RX_BUF[i]=Res;
			i++;
		
		if(USART_RX_BUF[i-1]=='\r'||USART_RX_BUF[i-1]=='>'||i>255)
		{
			  USART_RX_BUF[i] = 0;
			  flag_recful=1;
				i=0;
			}
		}
		else
		{

       }
		
	 } 
} 
/**************************************************************************
�������ܣ�����2�ж���ں���  ���� '#'�ַ� ��ͷ����"\r\n"Ϊ���������ַ���
��ڲ���: ��
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void) 
{

		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
		{ 
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);

		}

}

void App_control_car(void)
{
    if(flag_recful)
	{
	  //printf("%s",USART_RX_BUF);
	  flag_recful=0;
	  App_control(USART_RX_BUF);
	}
}






