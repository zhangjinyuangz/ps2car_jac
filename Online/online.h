#ifndef  __ONLINE_H__
#define  __ONLINE_H__
int Is_Car_Front(const char *string);
int Is_Car_Back(const char *string);
int Is_Car_Left(const char *string);
int Is_Car_Right(const char *string);
int Is_Car_Stop(const char *string);
int Is_Duoji_Angle(const char *string);
void DJ_angle_control(const char *string);
void DJ_angle_control_1(const char *string);
void DJ_angle_control_2(const char *string);
void DJ_angle_control_3(const char *string);
void DJ_angle_control_4(const char *string);
void DJ_angle_control_5(const  char *string);
int Is_Duoji1_Angle(const char *string);
int Is_Duoji2_Angle(const char *string);
int Is_Duoji3_Angle(const char *string);
int Is_Duoji4_Angle(const char *string);
int Is_Duoji5_Angle(const char *string);
unsigned char ASC_To_Valu(unsigned char asc);
void App_control(const char *string);
void OneLine(const char *str);
int Is_Zhongli(const char *string);
int Is_DJ_angle(const char *string);
void Servor_parse(const char *str);

#endif

