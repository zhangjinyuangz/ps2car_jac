#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "sys.h" 
#include "common.h"

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	


void USART_Config(USART_TypeDef* TUSARTx,u32 bound); 
void Uart_Init(u16 uart_num);
void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data);
void UART_PutStr (USART_TypeDef* USARTx, const char *str);
void UART_Put_Num(uint16 dat);
void UART_Put_Inf(const char *inf,uint16 dat);
void DealRec(void);
void uart_init(u32 bound);
void App_control_car(void);
#endif


