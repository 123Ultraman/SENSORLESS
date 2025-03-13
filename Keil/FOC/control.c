#include "control.h"
#include "BSP_DWT.h"

#ifndef abs
#define abs(x) ((x > 0) ? x : -x)
#endif

/*============================================================================*/
// 梯形积分
/*============================================================================*/
static void Trapezoid_Intergral(PID_ *pid)
{
    pid->ITerm = pid->Ki * ((pid->Err + pid->Last_Err) / 2) * pid->dt;
}

/**
 * @brief         积分限幅
 * @param[in]  pid    PID结构体
 * @retval         返回空
 */
static void Integral_Limit(PID_ *pid)
{
    static float temp_Output, temp_Iout;
    temp_Iout = pid->Iout + pid->ITerm;
    temp_Output = pid->Pout + pid->Iout;
    if (abs(temp_Output) >= pid->MaxOut) /*输出达到限幅*/
    {
        if (pid->Err * pid->Iout > 0) // 积分却还在累积
        {
            pid->ITerm = 0; // 当前积分项置零
                            //   if (abs(pid->Err) < 1)
                            //   pid->Iout = 0;
        }
    }

    if (temp_Iout > pid->IntegralLimit)
    {
        pid->ITerm = 0; // 抗积分饱和
        pid->Iout = pid->IntegralLimit;
    }
    if (temp_Iout < -pid->IntegralLimit)
    {
        pid->ITerm = 0; // 抗积分饱和
        pid->Iout = -pid->IntegralLimit;
    }
}

/**
 * @brief         输出限幅
 * @param[in]  pid    PID结构体
 * @retval         返回空
 */
static void Output_Limit(PID_ *pid)
{
    if (pid->OutPut > pid->MaxOut)
    {
        pid->OutPut = pid->MaxOut;
    }
    if (pid->OutPut < -(pid->MaxOut))
    {
        pid->OutPut = -(pid->MaxOut);
    }
}

void PID_Curr_Init(PID_ *pid_curr_iq,PID_ *pid_curr_id,float Udc)
{
    memset(pid_curr_iq, 0, sizeof(PID_));
    DWT_GetDeltaT(&pid_curr_iq->DWT_CNT);
//    pid_curr_iq->Kp =Kp_curr;
//    pid_curr_iq->Ki =Ki_curr;
    pid_curr_iq->IntegralLimit = 6.0f;
    pid_curr_iq->MaxOut =6.0f;
	
	
		memset(pid_curr_id, 0, sizeof(PID_));
		DWT_GetDeltaT(&pid_curr_id->DWT_CNT);
//		pid_curr_id->Kp = Kp_curr;
//    pid_curr_id->Ki = Ki_curr;
    pid_curr_id->IntegralLimit = 6.0f;
    pid_curr_id->MaxOut= 6.0f;
}

void PID_Speed_Init(PID_ *pid_speed,float Udc)
{
		memset(pid_speed, 0, sizeof(PID_));
    DWT_GetDeltaT(&pid_speed->DWT_CNT);
    pid_speed->Kp = 0.01f;
    pid_speed->Ki = 0.5f;
    pid_speed->IntegralLimit = 0.5f;
    pid_speed->MaxOut =0.5f;
}

/**
 * @brief          PID计算
 * @param[in]  pid    PID结构体
 * @param[in]  measure    测量值
 * @param[in]  ref    期望值
 * @retval         返回空
 */
float PIDCalculate(PID_ *pid,float measure,float ref)
{
    pid->dt = DWT_GetDeltaT(&pid->DWT_CNT);
    pid->Measure = measure;
    pid->Ref = ref;
    pid->Err = pid->Ref - pid->Measure;
    pid->Pout = pid->Kp * pid->Err;
    pid->ITerm = pid->Ki * pid->Err;
    Trapezoid_Intergral(pid);//梯形积分
    Integral_Limit(pid);     // 积分限幅

    pid->Iout += pid->ITerm;                         // 累加积分
    pid->OutPut = pid->Pout+pid->Iout; // 计算输出

    Output_Limit(pid);//输出限幅

    // 保存当前数据,用于下次计算
    pid->Last_Measure = pid->Measure;
    pid->Last_Output = pid->OutPut;
    pid->Last_Err = pid->Err;
    pid->Last_ITerm = pid->ITerm;

    return pid->OutPut;
}
