#ifndef __FOC_H__
#define __FOC_H__

#include "main.h"

typedef struct UI_3s
{
	float A;
	float B;
	float C;
}UI_3s;

typedef struct UI_2s
{
	float Alpha;
	float Beta;
}UI_2s;

typedef struct UI_2r
{
	float Q;
	float D;
}UI_2r;



typedef struct FOC_P
{
	float AngleE;
	float AngleBase;
	float SpeedMachReal;
	float SpeedMachRef;
}FOC_P;

typedef struct Motor_P
{
	float Rs;
	float Ld;
	float Lq;
	float flux;
	float J;
	float temperature;
	float Ts_Ld;
	float Ts_Lq;
	float u;
	float Pd;
	float Pq;
	float Pj;
	float VBUS;
	float Udc;
}Motor_P;


typedef struct PI_Structure
{
	float Kp;
	float Ki;
	float error;
	float last_error;
	float integral;
	float gain;
	float output;
}PI_Structure;



typedef enum
{
	ADC_CALIBRATION,
	RS_IDENTIFY_VOLTAGE_DESIGM,
	PARAMETER_IDENTIFY_Rs,
	PARAMETER_IDENTIFY_L,
	PARAMETER_IDENTIFY_Flux,
	PARAMETER_IDENTIFY_J,
	FOC_RUN,
}SystStatusEnum;

typedef enum
{
	OK,
	error,
} StateType;

typedef struct FaultStateStruct
{
	StateType Overtemperature;
	StateType Overvoltage;
	StateType Undervoltage;
	StateType Overcurrent;
	StateType L6230Fault;
} FaultStateStruct;

typedef struct MOTOR_HandleTypeDef
{
	FOC_P FOC_Parameter;
	
	UI_2r U_2r;
	UI_2s U_2s;
	UI_2s Last_U_2s;
	UI_2r I_2r;
	UI_2s I_2s;
	UI_2s Last_I_2s;
	UI_3s I_3s;
	PI_Structure SpeedPI;
	PI_Structure IqPI;
	PI_Structure IdPI;
	
	Motor_P Motor_Parameter;
}MOTOR_HandleTypeDef;

extern CORDIC_HandleTypeDef hcordic;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern uint32_t ADC1_value[4];
extern uint32_t ADC2_value[2];
HAL_StatusTypeDef CordicInit(void);
void Theta2SinCos(float Theta, float* pSinCos);
void Clark(UI_3s* UI_3s,UI_2s* UI_2s);
void AntiClark(UI_3s* UI_3s,UI_2s* UI_2s);
void Park(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E);
void AntiPark(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E);
void SVPWM(UI_2s* UI_2s);
void PWM_Start(void);
void PWM_Stop(void);
void PIControler(PI_Structure* PI,float real_value,float set_value);
void FocInit(void);
float temperature_lookup(int ADC_value);
void Protection(void);
#define RS						0.60f
#define LS            0.00045f
#define PHI           0.0058

#define VALUE_1_3						0.333333333333333f              //1/3
#define VALUE_2_3           0.666666666666667f              //2/3
#define VALUE_1_2           0.5f                            //1/2
#define VALUE_SQRT3_2       0.866025403784438f              //SQRT(3)/2
#define THETA_360_Q31       11930464                        //1/180*2^31
#define VALUE_Q31_FLOAT     2147483648.0f                   //浮点数转定点数   2^31
#define VALUE_SQRT3         1.732050807568878f							//sqrt(3
#define VALUE_1_SQRT3       0.577350269189626f              //  1/sqrt(3)
#define Ts                  0.0001f                          //控制周期0.0001s
#define Period              17000                            //计数值 
#define Period_4            2125                            //8500/4
#define Pn                  2                               //极对数
#define TIM2_CLK            170000000                       //定时器二频率
#define TIM1_CLK            170000000                       //定时器一频率
#define K_SPEED             TIM2_CLK/(6*Pn)*60              //Speed_rel = K_SPEED/TIM2->CCR1,RPM
#define ZeroSpeedCntMax     2000                            //两秒内HALL信号未改变判断为零速
#define K_adc               712.092F                        //电流采样系数    0.33*(2.2/(0.68+2.2))*((2.2+2.2)/2.2)/2.9*4096
#define VBUS_MAX            24                              //过压保护阈值
#define VBUS_MIN            6                               //欠压保护阈值
#define MOTOR_DEFAULT       {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0,0,0,0,1,0,1,1,0.99,1e5,1e5,1e5,12,12}}
#define temperature_MAX     80                              //过温保护阈值
#define current_MAX         10                               //过流保护阈值
#define FLASH_PAGE_ADDR  		0x0801F800  										// 最后一页 Flash 起始地址
#define CURRENT_BASE        1.0                               //电机电流额定值                             
#define T1_Table {                                                               \
        0.0000000e+00, 5.0000000e-01, 1.0000000e+00, 1.5000000e+00, 2.0000000e+00, \
        2.5000000e+00, 3.0000000e+00, 3.5000000e+00, 4.0000000e+00, 4.5000000e+00, \
        5.0000000e+00, 5.5000000e+00, 6.0000000e+00, 6.5000000e+00, 7.0000000e+00, \
        7.5000000e+00, 8.0000000e+00, 8.5000000e+00, 9.0000000e+00, 9.5000000e+00, \
        1.0000000e+01, 1.0500000e+01, 1.1000000e+01, 1.1500000e+01, 1.2000000e+01, \
        1.2500000e+01, 1.3000000e+01, 1.3500000e+01, 1.4000000e+01, 1.4500000e+01, \
        1.5000000e+01, 1.5500000e+01, 1.6000000e+01, 1.6500000e+01, 1.7000000e+01, \
        1.7500000e+01, 1.8000000e+01, 1.8500000e+01, 1.9000000e+01, 1.9500000e+01, \
        2.0000000e+01, 2.0500000e+01, 2.1000000e+01, 2.1500000e+01, 2.2000000e+01, \
        2.2500000e+01, 2.3000000e+01, 2.3500000e+01, 2.4000000e+01, 2.4500000e+01, \
        2.5000000e+01, 2.5500000e+01, 2.6000000e+01, 2.6500000e+01, 2.7000000e+01, \
        2.7500000e+01, 2.8000000e+01, 2.8500000e+01, 2.9000000e+01, 2.9500000e+01, \
        3.0000000e+01, 3.0500000e+01, 3.1000000e+01, 3.1500000e+01, 3.2000000e+01, \
        3.2500000e+01, 3.3000000e+01, 3.3500000e+01, 3.4000000e+01, 3.4500000e+01, \
        3.5000000e+01, 3.5500000e+01, 3.6000000e+01, 3.6500000e+01, 3.7000000e+01, \
        3.7500000e+01, 3.8000000e+01, 3.8500000e+01, 3.9000000e+01, 3.9500000e+01, \
        4.0000000e+01, 4.0500000e+01, 4.1000000e+01, 4.1500000e+01, 4.2000000e+01, \
        4.2500000e+01, 4.3000000e+01, 4.3500000e+01, 4.4000000e+01, 4.4500000e+01, \
        4.5000000e+01, 4.5500000e+01, 4.6000000e+01, 4.6500000e+01, 4.7000000e+01, \
        4.7500000e+01, 4.8000000e+01, 4.8500000e+01, 4.9000000e+01, 4.9500000e+01, \
        5.0000000e+01, 5.0500000e+01, 5.1000000e+01, 5.1500000e+01, 5.2000000e+01, \
        5.2500000e+01, 5.3000000e+01, 5.3500000e+01, 5.4000000e+01, 5.4500000e+01, \
        5.5000000e+01, 5.5500000e+01, 5.6000000e+01, 5.6500000e+01, 5.7000000e+01, \
        5.7500000e+01, 5.8000000e+01, 5.8500000e+01, 5.9000000e+01, 5.9500000e+01, \
        6.0000000e+01, 6.0500000e+01, 6.1000000e+01, 6.1500000e+01, 6.2000000e+01, \
        6.2500000e+01, 6.3000000e+01, 6.3500000e+01, 6.4000000e+01, 6.4500000e+01, \
        6.5000000e+01, 6.5500000e+01, 6.6000000e+01, 6.6500000e+01, 6.7000000e+01, \
        6.7500000e+01, 6.8000000e+01, 6.8500000e+01, 6.9000000e+01, 6.9500000e+01, \
        7.0000000e+01, 7.0500000e+01, 7.1000000e+01, 7.1500000e+01, 7.2000000e+01, \
        7.2500000e+01, 7.3000000e+01, 7.3500000e+01, 7.4000000e+01, 7.4500000e+01, \
        7.5000000e+01, 7.5500000e+01, 7.6000000e+01, 7.6500000e+01, 7.7000000e+01, \
        7.7500000e+01, 7.8000000e+01, 7.8500000e+01, 7.9000000e+01, 7.9500000e+01, \
        8.0000000e+01, 8.0500000e+01, 8.1000000e+01, 8.1500000e+01, 8.2000000e+01, \
        8.2500000e+01, 8.3000000e+01, 8.3500000e+01, 8.4000000e+01, 8.4500000e+01, \
        8.5000000e+01, 8.5500000e+01, 8.6000000e+01, 8.6500000e+01, 8.7000000e+01, \
        8.7500000e+01, 8.8000000e+01, 8.8500000e+01, 8.9000000e+01, 8.9500000e+01, \
        9.0000000e+01, 9.0500000e+01, 9.1000000e+01, 9.1500000e+01, 9.2000000e+01, \
        9.2500000e+01, 9.3000000e+01, 9.3500000e+01, 9.4000000e+01, 9.4500000e+01, \
        9.5000000e+01, 9.5500000e+01, 9.6000000e+01, 9.6500000e+01, 9.7000000e+01, \
        9.7500000e+01, 9.8000000e+01, 9.8500000e+01, 9.9000000e+01, 9.9500000e+01, \
        1.0000000e+02, 1.0050000e+02, 1.0100000e+02, 1.0150000e+02 \
    }
#define Rt_ADCvalue_Table  {           \
        565, 578, 592, 606, 620, 634, 649, 663, 678, 694, \
        709, 725, 740, 757, 773, 789, 806, 823, 840, 858, \
        875, 893, 911, 929, 948, 966, 985, 1004, 1023, 1043, \
        1062, 1082, 1102, 1122, 1143, 1163, 1184, 1205, 1226, \
        1247, 1268, 1290, 1312, 1333, 1355, 1377, 1400, 1422, \
        1444, 1467, 1490, 1513, 1535, 1558, 1582, 1605, 1628, \
        1651, 1675, 1698, 1722, 1745, 1769, 1793, 1816, 1840, \
        1864, 1888, 1912, 1936, 1960, 1983, 2007, 2031, 2055, \
        2079, 2102, 2126, 2150, 2174, 2197, 2221, 2245, 2268, \
        2291, 2315, 2338, 2361, 2384, 2407, 2430, 2453, 2476, \
        2499, 2521, 2544, 2566, 2588, 2611, 2633, 2645, 2666, \
        2688, 2709, 2731, 2753, 2774, 2795, 2816, 2838, 2859, \
        2880, 2901, 2922, 2943, 2964, 2985, 3006, 3025, 3044, \
        3063, 3082, 3100, 3119, 3137, 3155, 3173, 3191, 3208, \
        3226, 3243, 3260, 3277, 3294, 3311, 3327, 3343, 3360, \
        3375, 3391, 3407, 3423, 3438, 3453, 3468, 3482, 3497, \
        3512, 3526, 3540, 3554, 3568, 3581, 3595, 3608, 3621, \
        3634, 3647, 3660, 3673, 3685, 3697, 3709, 3721, 3733, \
        3745, 3756, 3768, 3779, 3790, 3801, 3812, 3823, 3833, \
        3844, 3854, 3864, 3874, 3884, 3894, 3903, 3913, 3922, \
        3931, 3940, 3950, 3959, 3968, 3976, 3985, 3993, 4002, \
        4010, 4018, 4026, 4034, 4042, 4050, 4057, 4065, 4072, \
        4079, 4087, 4094    \
    }
#endif

