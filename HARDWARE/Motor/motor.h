#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "sys.h"
#define PWMA1   TIM3->CCR3  //PB0
#define PWMA2   TIM3->CCR4  //PB1
#define PWMB1   TIM4->CCR4  //PB8
#define PWMB2   TIM4->CCR3  //PB9
void PWM1_Init(u16 arr,u16 psc);
void PWM2_Init(u16 arr,u16 psc);
void Motor_Gpio_init(void);
void Set_Pwm_Motor1(int motor_a);
void Set_Pwm_Motor2(int motor_b);
void Set_Pwm_Motor(int motor);
void motor_test(void);
#endif
