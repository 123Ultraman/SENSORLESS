#include "control.h"
#include "BSP_DWT.h"
#include "string.h"
#ifndef abs
#define abs(x) ((x > 0) ? x : -x)
#endif

/*============================================================================*/
// ���λ���
/*============================================================================*/
static void Trapezoid_Intergral(PID_ *pid)
{
    pid->ITerm = pid->Ki * ((pid->Err + pid->Last_Err) / 2) * pid->dt;
}

/**
 * @brief         �����޷�
 * @param[in]  pid    PID�ṹ��
 * @retval         ���ؿ�
 */
static void Integral_Limit(PID_ *pid)
{
    static float temp_Output, temp_Iout;
    temp_Iout = pid->Iout + pid->ITerm;
    temp_Output = pid->Pout + pid->Iout;
    if (abs(temp_Output) >= pid->MaxOut) /*����ﵽ�޷�*/
    {
        if (pid->Err * pid->Iout > 0) // ����ȴ�����ۻ�
        {
            pid->ITerm = 0; // ��ǰ����������
                            //   if (abs(pid->Err) < 1)
                            //   pid->Iout = 0;
        }
    }

    if (temp_Iout > pid->IntegralLimit)
    {
        pid->ITerm = 0; // �����ֱ���
        pid->Iout = pid->IntegralLimit;
    }
    if (temp_Iout < -pid->IntegralLimit)
    {
        pid->ITerm = 0; // �����ֱ���
        pid->Iout = -pid->IntegralLimit;
    }
}

/**
 * @brief         ����޷�
 * @param[in]  pid    PID�ṹ��
 * @retval         ���ؿ�
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
 * @brief          PID����
 * @param[in]  pid    PID�ṹ��
 * @param[in]  measure    ����ֵ
 * @param[in]  ref    ����ֵ
 * @retval         ���ؿ�
 */
float PIDCalculate(PID_ *pid,float measure,float ref)
{
    pid->dt = DWT_GetDeltaT(&pid->DWT_CNT);
    pid->Measure = measure;
    pid->Ref = ref;
    pid->Err = pid->Ref - pid->Measure;
    pid->Pout = pid->Kp * pid->Err;
    pid->ITerm = pid->Ki * pid->Err;
    Trapezoid_Intergral(pid);//���λ���
    Integral_Limit(pid);     // �����޷�

    pid->Iout += pid->ITerm;                         // �ۼӻ���
    pid->OutPut = pid->Pout+pid->Iout; // �������

    Output_Limit(pid);//����޷�

    // ���浱ǰ����,�����´μ���
    pid->Last_Measure = pid->Measure;
    pid->Last_Output = pid->OutPut;
    pid->Last_Err = pid->Err;
    pid->Last_ITerm = pid->ITerm;

    return pid->OutPut;
}
