#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "main.h"
#include "stdint.h"

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float MaxOut;

    float IntegralLimit; // »ý·ÖÏÞ·ù

    float Measure;
    float Last_Measure;
    float Err;
    float Last_Err;
    float Last_ITerm;
    float Pout;
    float Iout;
    float Dout;
    float ITerm;
    float OutPut;
    float Last_Output;
    float Last_Dout;

    float Ref;

    uint32_t DWT_CNT;
    float dt;
}PID_;

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float MaxOut;
}PID_Init;

void Trapezoid_Intergral(PID_ *pid);
void Integral_Limit(PID_ *pid);
void Output_Limit(PID_ *pid);
void PID_Curr_Init(PID_ *pid_curr_iq,PID_ *pid_curr_id, float Udc);
float PIDCalculate(PID_ *pid, float measure, float ref);
void PID_Speed_Init(PID_ *pid_speed,float Udc);

#endif
