//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

////////////////////////////////////////////////////////////////////////////////// 	   
#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"	    	//包含stm32库系统头文件						
#include "usart.h"		  			//包含串口通信设置头文件
#include "delay.h"						//包含系统定时器库头文件
#include "led.h"
#include "beep.h"
#include "common.h"
#include "timer.h"
#include "motor.h"
#include "servor.h"
#include "online.h"
#include "ps2.h"
uint16 CPWM[9]= {1500,1500,1500,1500,1500,1500,1500,1500,1500};
unsigned int dj1=1500;
unsigned int dj2=1500;
unsigned int dj3=1500;
unsigned int dj4=1500;
unsigned int dj5=1500;
unsigned int dj6=1600;
 char buf[30];

unsigned char flag_scan_ps2;
char uart2_buf[255];
char uart1_buf[255];
unsigned char i=0;
u32 key, key_bak;
u8 ps2_mode=0;
uint8 flag_vpwm=0;
u32 Motor_Pwm=1000;
int LX_AD=0;
int LY_AD=0;
int RX_AD=0;
int RY_AD=0;
int ps2_count=0;
u32 systick_ms;
void scan_ps2(void);
void ps2_handle(void);
int main(void)
{   
	SysTick_Init();		//系统滴答定时器初始化 		
	LED_Init();	      //LED 初始化函数
	Beep_Init();      //蜂鸣器初始化函数
	Beep_Test();      //蜂鸣器测试
	Led_Test(); 
	PS2_Init();
	Timer_Init();
	Timer_ON();
	Uart_Init(2);	
	Uart_Init(1);	
	Servor_GPIO_Config();
	USART_Config(USART2,115200);
	USART_Config(USART1,115200);
	Motor_Gpio_init();
	PWM1_Init(1000,5);  // 初始化电机工作频率 72/(5+1)  12KHZ
	PWM2_Init(1000,5);  // 初始化电机工作频率 72/(5+1)  12KHZ
	while (1)
	{	
		ps2_handle();
		App_control_car();
		scan_ps2();	  
	}
} 


void ps2_handle(void) {
	//ps2_SONY
		Delay_ms(32);
		flag_scan_ps2=1;
	
}


/**************************************************************************
函数功能：获取PS2无线手柄按键值，定时器每隔段时间进行读取PS2_DataKey()
入口参数：无
返回  值：无 
**************************************************************************/
void scan_ps2(void)
{

	if (flag_scan_ps2)   //定时时间到
	{	
		flag_scan_ps2 = 0;
		key = PS2_DataKey(); 
		LY_AD=PS2_AnologData(PSS_LY);
		LX_AD=PS2_AnologData(PSS_LX);
		RY_AD=PS2_AnologData(PSS_RY);	
		RX_AD=PS2_AnologData(PSS_RX);	
		ps2_mode=PS2_RedLight();
		if(ps2_mode==0)
		{		 
			//UART_Put_Inf("LX_AD:",LX_AD);
			//UART_Put_Inf("RY_AD:",RY_AD);
			
			switch(key)
					{
//				case 	PSB_PAD_LEFT:CPWM[1]-=25;if(CPWM[1]<=800) CPWM[1]=800;break;
//				case 	PSB_PAD_RIGHT:CPWM[1]+=25;if(CPWM[1]>=2200) CPWM[1]=2200;break;
				case 	PSB_PAD_UP:CPWM[1]+=50;if(CPWM[1]>=2200) CPWM[1]=2200;break; 
				case 	PSB_PAD_DOWN:CPWM[1]-=50;if(CPWM[1]<=800) CPWM[1]=800;break; 
				case 	PSB_TRIANGLE:CPWM[1]-=75;if(CPWM[1]<=800) CPWM[1]=800;break; 
				case 	PSB_CROSS:CPWM[1]+=75;if(CPWM[1]>=2200)  CPWM[1]=2200;break; 
				case 	PSB_PINK:CPWM[1]-=100;if(CPWM[1]<=800) CPWM[1]=800;break; 
				case 	PSB_CIRCLE:CPWM[1]+=100;if(CPWM[1]>=2200)  CPWM[1]=2200;break; 
				case 	PSB_L1:CPWM[1]-=125;if(CPWM[1]<=800) CPWM[1]=800;break; 
				case 	PSB_L2:Beep_Yell();Set_Pwm_Motor(0);break; 
				case 	PSB_R1:CPWM[1]+=125;if(CPWM[1]>=2200)  CPWM[1]=2200;break;
				case 	PSB_R2:Beep_Yell();Set_Pwm_Motor(800);break; 
				default:break;
					}
				
				
				if(key == PSB_PAD_LEFT)				
				{
					CPWM[1]-=25;					
				}
				else if(key == PSB_PAD_RIGHT)
				{
					CPWM[1]+=25;
				}
				
	
		
				
				//5.490196078    一个摇杆模拟量等于舵机转动5.49个舵机模拟量
				//回正：在120~136的时候，舵机回正：1500
				//左转：在0~120的时候，舵机左转，极限是800
				//右转：在136~255的时候，舵机右转，极限是2200
				if(LX_AD>120 && LX_AD<=136) 
				{
					CPWM[1]=1500;
				}
				else if(LX_AD>=0 && LX_AD<=120) //左转
				{
					CPWM[1]=1500-(120-LX_AD)*5.4;
					if(CPWM[1]<=800) CPWM[1]=800;
				}
				else if(LX_AD>136 && LX_AD<=255) //右转
				{
					CPWM[1]=1500+(LX_AD-136)*5.4;
					if(CPWM[1]>=2200) CPWM[1]=2200;
				}
				
				
				
			 if(RY_AD>120 && RY_AD<=136) 
				{
					Set_Pwm_Motor(0);
				}
				else if(RY_AD>=0 && RY_AD<=120)  //前进
				{
					Set_Pwm_Motor((136-RY_AD)*2*11);
				}
				else if(RY_AD>136 && RY_AD<=255) //后退
				{
					Set_Pwm_Motor(-(RY_AD-136)*2*11);
				}
									
				}

		}
	}
	
	

