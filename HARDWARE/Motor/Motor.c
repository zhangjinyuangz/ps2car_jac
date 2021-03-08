#include "motor.h"
#include "delay.h"

  /**************************************************************************

**************************************************************************/

void Motor_Gpio_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);// ��ʹ�� tim1 ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
   //���ø�����Ϊ�����������,���TIM3 CH3 CH4 PWM���岨��  
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 |GPIO_Pin_8|GPIO_Pin_9; //TIM3_CH3 //TIM3_CH4
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void PWM1_Init(u16 arr,u16 psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		
	TIM_TimeBaseStructure.TIM_Period = arr;							//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;						//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//�ظ��Ĵ����������Զ�����
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 				//�ڳ�ʼ�� TIMx

	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //�������ģʽ ͨ��1  ����ģʽ��PWM��������Ƚϣ�������PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��  ʹ��PWM������˿�
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//ʹ�ܻ��������
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //���������״̬
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//�����󻥲������״̬
	TIM_OCInitStructure.TIM_Pulse = 0; 							//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //���û������������
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 			//�۳�ʼ������ TIMx	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//CH1 Ԥװ��ʹ��
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 			//�۳�ʼ������ TIMx	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//CH1 Ԥװ��ʹ��
	
	TIM_Cmd(TIM3, ENABLE); //��ʹ�� TIM3
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE); //��MOE �����ʹ��
	
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
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);// ��ʹ�� tim1 ʱ��
	//GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE); 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//			
  //  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	TIM_TimeBaseStructure.TIM_Period = arr;							//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc;						//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					//�ظ��Ĵ����������Զ�����
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				//�ڳ�ʼ�� TIMx

	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //�������ģʽ ͨ��1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//ʹ�ܻ��������
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //���������״̬
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//�����󻥲������״̬
	TIM_OCInitStructure.TIM_Pulse = 0; 							//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //���û������������
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 			//�۳�ʼ������ TIMx	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH1 Ԥװ��ʹ��
	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 			//�۳�ʼ������ TIMx	
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//CH1 Ԥװ��ʹ��
	
	TIM_Cmd(TIM4, ENABLE); //��ʹ�� TIM2
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE); //��MOE �����ʹ��
	
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
