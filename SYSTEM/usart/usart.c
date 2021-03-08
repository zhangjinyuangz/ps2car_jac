#include "sys.h"
#include "usart.h"	
#include "common.h"
#include "online.h"
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

u16 USART_RX_STA=0;       //接收状态标记	  

u8 flag_recful=0;

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0); //循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
/**************************************************************************
函数功能：串口1中断向量管理
入口参数：无
返回  值：无
**************************************************************************/

void Uart1_NVIC_Init(void)
{
	  //Usart1 NVIC 配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}
/**************************************************************************
函数功能：串口2中断向量管理
入口参数：无
返回  值：无
**************************************************************************/
void Uart2_NVIC_Init(void)
{
	  //Usart2 NVIC 配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}
/**************************************************************************
函数功能：串口1 IO相关初始化
入口参数：无
返回  值：无
**************************************************************************/
void Uart1_Gpio_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
		//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO端口时钟输出50MHZ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

}
/**************************************************************************
函数功能：串口1相关初始化
入口参数：无
返回  值：无
**************************************************************************/
void Uart2_Gpio_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART2，GPIOA时钟
		//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

}
/**************************************************************************
函数功能：初始化选择对应串口
入口参数：uart_num  串口号选择 范围：1-2
返回  值：无
**************************************************************************/
void Uart_Init(u16 uart_num)
{
	if(uart_num==1)
	{
		Uart1_NVIC_Init();  //串口1中断向量管理初始化
		Uart1_Gpio_Config();//串口1对应IO初始化
		
	}
	else if(uart_num==2)
	{
		Uart2_NVIC_Init();  //串口2中断向量管理初始化
		Uart2_Gpio_Config(); //串口2对应IO初始化
	}
}
/**************************************************************************
函数功能：串口初始化相关设置，波特率设置
入口参数：USART_TypeDef* TUSARTx 可选择初始化对应串口  bound：波特率选择  实例：USART_Config(USART1,115200)  初始化串口1并且设置波特率为115200
返回  值：无
**************************************************************************/
void USART_Config(USART_TypeDef* TUSARTx,u32 bound) 
{
  
	USART_InitTypeDef USART_InitStructure;
 
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(TUSARTx, &USART_InitStructure); //初始化串口
  USART_ITConfig(TUSARTx, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(TUSARTx, ENABLE);                    //使能串口

}

/**************************************************************************
函数功能：串口发送一个字符
入口参数：USART_TypeDef* TUSARTx 可选择初始化对应串口  data 要发送的字符
返回  值：无
**************************************************************************/

void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data)  
{  
    USART_SendData(USARTx, Data);  
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}  
}  

/**************************************************************************
函数功能：串口发送一个字符串
入口参数：USART_TypeDef* TUSARTx 可选择初始化对应串口  *str 要发送的字符串
返回  值：无
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
函数功能：将一个无符号整型数转换成对应字符串，在通过串口1发送出去
入口参数: unit16 data
返回  值：无
**************************************************************************/
void UART_Put_Num(uint16  dat)
{
 char temp[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 u32tostr(dat,temp);
 UART_PutStr(USART1,temp); 
}
/**************************************************************************
函数功能：将一个无符号整型数转换成对应字符串，在通过串口1发送出去
入口参数: 字符串*inf  无符号整型 dat
返回  值：无
**************************************************************************/
void UART_Put_Inf(const char *inf,uint16 dat)
{
 UART_PutStr (USART1,inf); 
 UART_Put_Num(dat);
 UART_PutStr (USART1,"\n");  
}
/**************************************************************************
函数功能：串口1中断入口函数 
入口参数: 无
返回  值：无
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
函数功能：串口2中断入口函数  接收 '#'字符 开头并以"\r\n"为结束符的字符串
入口参数: 无
返回  值：无
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






