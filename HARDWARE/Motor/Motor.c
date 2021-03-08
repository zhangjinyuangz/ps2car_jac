#include "motor.h"
#include "delay.h"

  /**************************************************************************

**************************************************************************/

void Motor_Gpio_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);// ①使能 tim1 时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
   //设置该引脚为复用输出功能,输出TIM3 CH3 CH4 PWM脉冲波形  
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 |GPIO_Pin_8|GPIO_Pin_9; //TIM3_CH3 //TIM3_CH4
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void PWM1_Init(u16 arr,u16 psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		
	TIM_TimeBaseStructure.TIM_Period = arr;							//设置在下一个更新事件装入活动的自动重装载寄存器周期的值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;						//设置用来作为 TIMx 时钟频率除数的预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//重复寄存器，用于自动更新
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 				//②初始化 TIMx

	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //脉宽调制模式 通道1  设置模式是PWM还是输出比较，这里是PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能  使能PWM输出到端口
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//使能互补端输出
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //死区后输出状态
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//死区后互补端输出状态
	TIM_OCInitStructure.TIM_Pulse = 0; 							//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //设置互补端输出极性
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//CH1 预装载使能
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//CH1 预装载使能
	
	TIM_Cmd(TIM3, ENABLE); //④使能 TIM3
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE); //⑤MOE 主输出使能
	
	TIM_SetAutoreload(TIM3, arr);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);	
	return;
}

void PWM2_Init(u16 arr,u16 psc)
{		 		
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);// ①使能 tim1 时钟
	//GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE); 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//			
  //  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	TIM_TimeBaseStructure.TIM_Period = arr;							//设置在下一个更新事件装入活动的自动重装载寄存器周期的值 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc;						//设置用来作为 TIMx 时钟频率除数的预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//重复寄存器，用于自动更新
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				//②初始化 TIMx

	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //脉宽调制模式 通道1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//使能互补端输出
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //死区后输出状态
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//死区后互补端输出状态
	TIM_OCInitStructure.TIM_Pulse = 0; 							//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //设置互补端输出极性
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH1 预装载使能
	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 			//③初始化外设 TIMx	
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH1 预装载使能
	
	TIM_Cmd(TIM4, ENABLE); //④使能 TIM2
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE); //⑤MOE 主输出使能
	
	TIM_SetAutoreload(TIM4, arr);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
	
	return;

	
} 



void Set_Pwm_Motor1(int motor_a)
{
		if(motor_a<0)			PWMA1=-motor_a,PWMA2=0;
		else 	            PWMA2= motor_a,PWMA1=0;
}


void Set_Pwm_Motor2(int motor_b)
{
		if(motor_b<0)			PWMB1=-motor_b,PWMB2=0;
		else 	            PWMB2=motor_b,PWMB1=0;
}

void Set_Pwm_Motor(int motor)
{
	if(motor<0)					PWMA1=-motor,PWMB1=-motor,PWMA2=0,PWMB2=0;
	else 								PWMA2=motor,PWMB2=motor,PWMA1=0,PWMB1=0;
}
