#include "online.h"	
#include "motor.h"
#include "timer.h"
#include "usart.h"
#include "common.h"
#include "beep.h"
#include<string.h>
#include<stdlib.h>
#define TRUE   1
#define FALSE  0
uint16 UartRec[8]={1500,1500,1500,1500,1500,1500,1500,1500};
unsigned int pwm_num;

extern uint16 CPWM[9];
extern u32 Motor_Pwm;

int Is_Car_Front(const char *string)
{
	if(strncmp(string,"<BUPD>",6)==0 || strncmp(string,"BUPD",4)==0)
		return TRUE;
	else
		return FALSE;	
}

int Is_Car_Back(const char *string)
{
	if(strncmp(string,"<BDND>",6)==0 || strncmp(string,"BDND",4)==0)
		return TRUE;
	else
		return FALSE;	
}

int Is_Car_Left(const char *string)
{
	if(strncmp(string,"<BLTD>",6)==0||strncmp(string,"BLTD",4)==0)
		return TRUE;
	else
		return FALSE;	
}

int Is_Car_Right(const char *string)
{
	if(strncmp(string,"<BRTD>",6)==0 || strncmp(string,"BRTD",4)==0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Speed_Add(const char *string)
{
		if(strncmp(string,"BUAD",4)==0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Speed_Slow(const char *string)
{
		if(strncmp(string,"BUMD",4)==0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_KD(const char *string)
{
		if(strncmp(string,"BUKD",4)==0)	
		return TRUE;
	else
		return FALSE;
}
int Is_Car_horning(const char *string)
{
		if(strncmp(string,"BUSD",4)==0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Nohorning(const char *string)
{
		if(strncmp(string,"BUSN",4)==0)	
		return TRUE;
	else
		return FALSE;
}

int Is_Car_Stop(const char *string)
{
	if((strncmp(string,"<BLTU>",6)==0) || (strncmp(string,"<BDNU>",6)==0) || \
		   (strncmp(string,"<BUPU>",6)==0)||(strncmp(string,"<BRTU>",6)==0) ||(strncmp(string,"BSTD",4)==0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}




int Is_Duoji_Angle(const char *string)
{
	if(strncmp(string,"<SUP-",5)==0 )
	{
		return TRUE;
	}
	else
		return FALSE;	
}

int Is_Duoji1_Angle(const char *string)
{
	if(strncmp(string,"<SLT-",5)==0 )
	{
		return TRUE;
	}
	else
		return FALSE;	
}

int Is_Duoji2_Angle(const char *string)
{
	if(strncmp(string,"<SDN-",5)==0)
	{
		return TRUE;
	}
	else
		return FALSE;	
}

int Is_Duoji3_Angle(const char *string)
{
	if(strncmp(string,"<SRT-",5)==0)
	{
		return TRUE;
	}
	else
		return FALSE;	
}

int Is_Duoji4_Angle(const char *string)
{
	if(strncmp(string,"<SDL-",5)==0)
	{
		return TRUE;
	}
	else
		return FALSE;	
}

int Is_Duoji5_Angle(const char *string)
{
	if(strncmp(string,"<SDR-",5)==0 )
	{
		return TRUE;
	}
	else
		return FALSE;	
}



int Is_Zhongli(const char *string)
{
	if(strncmp(string,"<ZL",3)==0)
		return TRUE;
	else
		return FALSE;	
}

void DJ_angle_control(const char *string)
{
	const char *pb = string;
	unsigned int angle;
	pb = strstr(string,"<SUP-");
	if(NULL!=pb )
	{
		pb = strchr(pb,'-');
			pb++;
			angle = atol(pb);

	//	Uart_SendString("angle:");
	//	printf("angle1:%d",angle);
    CPWM[1] = angle;
	}
}

void DJ_angle_control_1(const char *string)
{
	const char *pb = string;
	unsigned int angle;
	pb = strstr(string,"<SLT-");
	
	if(NULL!=pb )
	{
		pb = strchr(pb,'-');

			pb++;
			angle = atol(pb);	
		//printf("angle2:%d",angle);
		CPWM[2] = angle;
   }

}

void DJ_angle_control_2(const char *string)
{
	const char *pb = string;
	unsigned int angle;
	pb = strstr(string,"<SDN-");
	if(NULL!=pb )
	{
		pb = strchr(pb,'-');
			pb++;
			angle = atol(pb);
		//printf("angle3:%d",angle);
    CPWM[3] = angle;
	}

}

void DJ_angle_control_3(const char *string)
{
	const char *pb = string;
	unsigned int angle;
	pb = strstr(string,"<SRT-");

	if(NULL!=pb)
	{
		pb = strchr(pb,'-');
			pb++;
			angle = atol(pb);
		//printf("angle4:%d",angle);
    CPWM[4]=angle;
	}

}

void DJ_angle_control_4(const char *string)
{
	const char *pb = string;
	unsigned int angle;
	pb = strstr(string,"<SDL-");

	if(NULL!=pb)
	{
		pb = strchr(pb,'-');	
			pb++;
			angle = atol(pb);

		//printf("angle5:%d",angle);
    CPWM[5]=angle;
	}

}

void DJ_angle_control_5(const char *string)
{
	const char *pb = string;
	unsigned int angle;
	pb = strstr(string,"<SDR-");
	if(NULL!=pb )
	{
		pb = strchr(pb,'-');	
			pb++;
			angle = atol(pb); 
		//printf("angle6:%d",angle);
    CPWM[6]=angle;
	}

}


void Servor_parse(const char *str)
{
	unsigned char motor_num=0;		   
	unsigned int  motor_jidu=0;	  
	unsigned int motor_time=0;	  
	unsigned char num_now=0;		   
	unsigned char jidu_now=0;		  
	unsigned char time_now=0;		   
	unsigned char flag_num=0;		  
	unsigned char flag_jidu=0;		  
	unsigned char flag_time=0;		   
	unsigned int i=0;

	while( str[i]!='\n'  && i < 500)
	{
		if(flag_num==1)	 				
		{
			if(str[i]!='P')				
			{
				num_now=ASC_To_Valu(str[i]);
				motor_num=motor_num*10+num_now;
			}
			else  					
				flag_num=0;
		}

		if(flag_jidu==1)			
		{
			if((str[i]!='T')&(str[i]!='#'))	
			{							
				jidu_now=ASC_To_Valu(str[i]);
				motor_jidu=motor_jidu*10+jidu_now;
			}
			else  						
			{
				flag_jidu=0;
				if(motor_jidu>2500)
					motor_jidu=2500;
			  UartRec[motor_num]=motor_jidu;
				pwm_num=motor_num;
				motor_jidu=0;
				motor_num=0;
			}
		}

		if(flag_time==1)				
		{
			time_now=ASC_To_Valu(str[i]);
			motor_time=motor_time*10+time_now;
			UartRec[0]=motor_time;	   
			if(str[i+1]=='\r')
			{	
				if(motor_time<=100)		
					CPWM[pwm_num]=UartRec[pwm_num];
			}
		}
	
		if(str[i]=='#')
			flag_num=1;
		if(str[i]=='P')
			flag_jidu=1;
		if(str[i]=='T')
			flag_time=1;
		i++;
	}	  
}

#if 0
void OneLine(const char *str)
{
	 char X_Postion=0;
   char Y_Postion=0;
   char Z_Postion=0;
   char x_now=0,y_now=0,z_now=0;
	 char flag_x=0;
   char flag_y=0;
   char flag_z=0;
	unsigned char i=0;
	char sign=1;
	while(str[i]!='>')
	{
		if(flag_x==1)
		{
			if(str[i]!='Y')
			{  
				if(str[i]=='-')
				{
					sign=-1;
					i++;
				}
				else
				{
					sign=1;
				}
				x_now = ASC_To_Valu(str[i]);	
			  X_Postion = (X_Postion*10+x_now)*sign;
			}
			else
			{
				flag_x=0;
			}
		}
		if(flag_y==1)
		{
			if((str[i]!='Z')&(str[i]!='X'))
			{
				if(str[i]=='-')
				{
					sign=-1;
					i++;
				}
				else
				{
					sign=1;
				}
				
				y_now = ASC_To_Valu(str[i]);
				Y_Postion=(Y_Postion*10+y_now)*sign;
			}
			else
			{
				flag_y=0;
			}
		}
		if(flag_z==1)
		{
				if(str[i]=='-')
				{
					sign=-1;
					i++;
				}
				else
				{
					sign=1;
				}
			z_now = ASC_To_Valu(str[i]);
			Z_Postion = (Z_Postion*10+z_now)*sign;
			if(str[i+1]=='>')
			{

				if((Y_Postion>-30&&Y_Postion<30) && (X_Postion>=-30 && X_Postion<30))
				{
						//CAR_STOP;	
				}
				if(Y_Postion>=0)
				{
				  if(Y_Postion>=30 && Y_Postion<=99)
					{
					//	CAR_BACKWARD;
					//	UART_Put_Inf("Y:",Y_Postion);
					}
					else 
					{
					//	CAR_STOP;
					}
				}
				else 
				{
					if(Y_Postion>-99 && Y_Postion<=-30)
					{
					//	CAR_FORWARD;
						Y_Postion=-Y_Postion;
						//UART_Put_Inf("--Y:",Y_Postion);
					}
					else
					{
					//	CAR_STOP;
						//UART_Put_Inf("STOP:",Y_Postion);
					}
				}
			    if(X_Postion>=0)
				{
					if(X_Postion>=30 &&  X_Postion<99)
					{
					//	duoji_pulse = 1200;
				    //		UART_Put_Inf("DJ:",duoji_pulse);
					   // CAR_LEFT;
					}
					else
					{
					//	duoji_pulse	= 1500;
					//	UART_Put_Inf("DJ:",duoji_pulse);
				   	   // CAR_STOP;
					}
				}
				else
				{
					if(X_Postion>=-99 &&  X_Postion<-30)
					{
					 //	duoji_pulse	= 1800;
					//	UART_Put_Inf("DJ:",duoji_pulse);
					  //  CAR_RIGHT;
					}
					else
					{
	                 // duoji_pulse	= 1500;;
					//	UART_Put_Inf("DJ:",duoji_pulse);
					    //CAR_STOP;
					}
				}
			}
		}
		if(str[i]=='X')
			flag_x=1;
		if(str[i]=='Y')
			flag_y=1;
		if(str[i]=='Z')
			flag_z=1;
		i++;
	}
}

#endif


void App_control(const char *str)
{
	 if(Is_Car_Front(str))
		{
			Set_Pwm_Motor1(Motor_Pwm);
			Set_Pwm_Motor2(Motor_Pwm);

		}
	else if(Is_Car_Back(str))
		{
			
			Set_Pwm_Motor1(-Motor_Pwm);
			Set_Pwm_Motor2(-Motor_Pwm);
		}
	else if(Is_Car_Left(str))
		{
			Set_Pwm_Motor1(Motor_Pwm);
			Set_Pwm_Motor2(-Motor_Pwm);
		}
	else if(Is_Car_Right(str))
		{
			Set_Pwm_Motor1(-Motor_Pwm);
			Set_Pwm_Motor2(Motor_Pwm);
		}
	else if(Is_Car_Stop(str))
		{
			Set_Pwm_Motor1(0);
			Set_Pwm_Motor2(0);
		}
  else if(Is_Duoji_Angle(str))
		{
			DJ_angle_control(str);
		}
	else if(Is_Duoji1_Angle(str))
	 {
     DJ_angle_control_1(str);
   }
	 else if(Is_Duoji2_Angle(str))
	 {
     DJ_angle_control_2(str);
   }
	 else if(Is_Duoji3_Angle(str) )
	 {
     DJ_angle_control_3(str);
   }
   	 else if(Is_Duoji4_Angle(str))
	 {
     DJ_angle_control_4(str);
   }
   	 else if(Is_Duoji5_Angle(str))
	 {
     DJ_angle_control_5(str);
   }
	 else if(Is_Car_Speed_Add(str))
	 {
			Motor_Pwm+=100;
		  if(Motor_Pwm>=1000) Motor_Pwm=1000;
	 }
	 else if(Is_Car_Speed_Slow(str))
	 {
			Motor_Pwm-=100;
		  if(Motor_Pwm<=700) Motor_Pwm=700;
   }
	 else if(Is_Car_horning(str))
	 {
			Beep=~Beep;
   }
	 else if(Is_Car_Nohorning(str))
	 {
		  BEEP(OFF);
   }
	 else 
	 {
		Servor_parse(str);
   }
}
