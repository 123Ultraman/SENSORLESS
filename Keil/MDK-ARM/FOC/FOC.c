#include "foc.h"
#include "math.h"
#include "dma.h"
#include "offline_pi.h"
#include "algorithm.h"
#include "arm_math.h"
#include "BSP_DWT.h"
#include "string.h"
#include "control.h"
//temperature LOOK_UP_Table
const float T1[] = T1_Table;
const int Rt_ADCvalue[] = Rt_ADCvalue_Table;
extern STSTEM_STATE_TYPE SYSTEM_STATE;
FaultStateStruct FaultState = {OK};

/**
  * @brief  CORDIC init
  * @param 	none
  * @retval none
  */
HAL_StatusTypeDef CordicInit(void)
{
	CORDIC_ConfigTypeDef sConfig;
	sConfig.Function = CORDIC_FUNCTION_PHASE;
	sConfig.InSize = CORDIC_INSIZE_32BITS;
	sConfig.OutSize = CORDIC_OUTSIZE_32BITS;
	sConfig.NbRead = CORDIC_NBREAD_2;
	sConfig.NbWrite =CORDIC_NBWRITE_2;
	sConfig.Precision = CORDIC_PRECISION_6CYCLES;
	sConfig.Scale = CORDIC_SCALE_0;
	
	if(HAL_CORDIC_Configure(&hcordic,&sConfig) == HAL_OK)
		return HAL_OK;
	else return HAL_ERROR;
}

/**
  * @brief  CORDIC calculate sin and cos
  * @param 	Theta electrical angle expressed in indians
  * @param 	pSinCos pSinCos[0]--sin(theta)   pSinCos[1]--cos(theta)
  * @retval none
  */

void Theta2SinCos(float Theta, float* pSinCos)
{
	hcordic.Instance->WDATA = Theta * THETA_360_Q31;
	pSinCos[0] = (int32_t)(hcordic.Instance->RDATA) / VALUE_Q31_FLOAT;
	pSinCos[1] = (int32_t)(hcordic.Instance->RDATA) / VALUE_Q31_FLOAT;
}

/**
  * @brief  CORDIC calculate atan2 and modulu
  * @param 	x x axis value
  * @param 	y y axis value
  * @param RES  resule array
  * @retval none
  */
void atan2_cordic(float x, float y, float* RES)
{
	float absx = 0,absy = 0;
	arm_abs_f32(&x,&absx,1);
	arm_abs_f32(&y,&absy,1);
    //normalize x and y
    float max_val = fmaxf(absx, absy);
	float scale = 0;
    x /= (max_val*2);
    y /= (max_val*2);
	scale = max_val*2;
	
	int32_t cordic_input[2] = { x*VALUE_Q31_FLOAT, y*VALUE_Q31_FLOAT };
    int32_t cordic_output[2] = {0};  //CORDIC input and output array

    HAL_CORDIC_Calculate_DMA(&hcordic, cordic_input, cordic_output, 1, CORDIC_DMA_DIR_IN_OUT);
		
	RES[0] = (float)(cordic_output[0])*1.4629181e-9f;  //  1/2^31*pi calculate the angle expressed in indians
    RES[1] = (float)(cordic_output[1])/ VALUE_Q31_FLOAT * scale; // calculate the modulu
}


/**
  * @brief  clark transform
  * @param 	Motor.I_3s three-phase static coordinate current
  * @param 	Motor.I_2s two-phase dynamic coordinate current
  * @retval none
  */
void Clark(UI_3s* UI_3s,UI_2s* UI_2s)
{
	UI_2s->Alpha = (UI_3s->A - VALUE_1_2*UI_3s->B - VALUE_1_2*UI_3s->C)*VALUE_2_3;
	UI_2s->Beta = (VALUE_SQRT3_2*UI_3s->B - VALUE_SQRT3_2*UI_3s->C)*VALUE_2_3;
}

/**
  * @brief  anticlark transform
  * @param 	Motor.I_3s three-phase static coordinate current
  * @param 	Motor.I_2s two-phase static coordinate current
  * @retval none
  */
void AntiClark(UI_3s* UI_3s,UI_2s* UI_2s)
{
	UI_3s->A = UI_2s->Alpha;
	UI_3s->B = -VALUE_1_2 * UI_2s->Alpha + VALUE_SQRT3_2 * UI_2s->Beta;
	UI_3s->C = -VALUE_1_2 * UI_2s->Alpha - VALUE_SQRT3_2 * UI_2s->Beta;
}

/**
  * @brief  park transform
  * @param 	UI_2s two-phase static coordinate voltage
  * @param 	UI_2r two-phase dynamic coordinate voltage
  * @retval none
  */
void Park(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E)
{
//	float theta = Theta_E*0.017453292519943f;//  1/180*pi
	UI_2r->D = arm_cos_f32(Theta_E) * UI_2s->Alpha + arm_sin_f32(Theta_E) * UI_2s->Beta;
	UI_2r->Q = -arm_sin_f32(Theta_E) * UI_2s->Alpha + arm_cos_f32(Theta_E)* UI_2s->Beta;
}

/**
  * @brief  antipark transform
  * @param 	UI_2s two-phase static coordinate voltage
  * @param 	UI_2r two-phase dynamic coordinate voltage
  * @retval none
  */
void AntiPark(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E)
{
//	float theta = Theta_E*0.017453292519943f;//  1/180*pi
	UI_2s->Alpha = arm_cos_f32(Theta_E) * UI_2r->D - arm_sin_f32(Theta_E) * UI_2r->Q;
	UI_2s->Beta = arm_sin_f32(Theta_E) * UI_2r->D + arm_cos_f32(Theta_E) * UI_2r->Q;
}

/**
  * @brief  SVPWM
  * @param 	UI_2s two-phase dynamic coordinate voltage
  * @retval none
  */

void SVPWM(UI_2s* UI_2s)
{

	float Uref1 = 0,Uref2 = 0,Uref3 = 0, X = 0, Y = 0, Z = 0 ,T1 = 0 ,T2 = 0;
	int Ta = 0,Tb = 0,Tc = 0;
	int Tcm1 = 0,Tcm2 = 0,Tcm3 = 0;
	int N = 0;
	Uref1 = UI_2s->Beta;
	Uref2 = -UI_2s->Beta * VALUE_1_2 + UI_2s->Alpha * VALUE_SQRT3_2;
	Uref3 = -UI_2s->Beta * VALUE_1_2 - UI_2s->Alpha * VALUE_SQRT3_2;
	N = ( Uref1 > 0 )|( Uref2 > 0 ) << 1 |( Uref3 > 0 ) << 2;
	X = VALUE_SQRT3 * UI_2s->Beta / Motor.Motor_Parameter.Udc *Period;
	Y = VALUE_SQRT3 * ( UI_2s->Beta * VALUE_1_2 + UI_2s->Alpha  * VALUE_SQRT3_2 ) / Motor.Motor_Parameter.Udc * Period;
	Z = VALUE_SQRT3 * ( UI_2s->Beta * VALUE_1_2 - UI_2s->Alpha  * VALUE_SQRT3_2 ) / Motor.Motor_Parameter.Udc * Period;
	
	switch(N)
	{
		case 1:T1 = Z;T2 = Y;break;
		case 2:T1 = Y;T2 = -X;break;
		case 3:T1 = -Z;T2 = X;break;
		case 4:T1 = -X;T2 = Z;break;
		case 5:T1 = X;T2 = -Y;break;
		case 6:T1 = -Y;T2 = -Z;break;
		default: break;
	}
	if(T1 + T2 > Period)
	{
		T1 = T1/(T1+T2) * Period;
		T1 = T2/(T1+T2) * Period;
	}
	Ta = (int)( ( Period - T1 - T2 ) / 4 );
	Tb = (int)( ( Period + T1 - T2 ) / 4 );
	Tc = (int)( ( Period + T1 + T2 ) / 4 );
	switch(N)
	{
		case 1:Tcm1 = Tb,Tcm2 = Ta,Tcm3 = Tc;	break;
		case 2:Tcm1 = Ta,Tcm2 = Tc,Tcm3 = Tb;	break;
		case 3:Tcm1 = Ta,Tcm2 = Tb,Tcm3 = Tc;	break;
		case 4:Tcm1 = Tc,Tcm2 = Tb,Tcm3 = Ta;	break;
		case 5:Tcm1 = Tc,Tcm2 = Ta,Tcm3 = Tb;	break;
		case 6:Tcm1 = Tb,Tcm2 = Tc,Tcm3 = Ta;	break;
		default: break;
	}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Tcm1);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Tcm2);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Tcm3);
}

/**
 * @brief   Trapezoidal integral
 * @param[in]  none
 * @retval     none
 */
static void Trapezoid_Intergral(PID_Structure *pid)
{
    pid->ITerm = pid->Ki * ((pid->Err + pid->Last_Err) / 2) * pid->dt;
}

/**
 * @brief         Integral limiting
 * @param[in]  pid    PID structure
 * @retval         none
 */
static void Integral_Limit(PID_Structure *pid)
{
    static float temp_Output, temp_Iout;
    temp_Iout = pid->Iout + pid->ITerm;
    temp_Output = pid->Pout + pid->Iout;
    if (abs(temp_Output) >= pid->MaxOut) //achieve the limit of output
    {
        if (pid->Err * pid->Iout > 0) //but the integral keep going
        {
            pid->ITerm = 0; // The current integral term is set to zero
                            //   if (abs(pid->Err) < 1)
                            //   pid->Iout = 0;
        }
    }

    if (temp_Iout > pid->IntegralLimit)
    {
        pid->ITerm = 0; //stop integral
        pid->Iout = pid->IntegralLimit;
    }
    if (temp_Iout < -pid->IntegralLimit)
    {
        pid->ITerm = 0; //stop integral
        pid->Iout = -pid->IntegralLimit;
    }
}

/**
 * @brief         output limiting
 * @param[in]  pid    PID structure
 * @retval         none
 */
static void Output_Limit(PID_Structure *pid)
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

void PID_Curr_Init(PID_Structure *pid_curr_iq,PID_Structure *pid_curr_id,float Udc)
{
    memset(pid_curr_iq, 0, sizeof(PID_Structure));
    DWT_GetDeltaT(&pid_curr_iq->DWT_CNT);
//    pid_curr_iq->Kp =Kp_curr;
//    pid_curr_iq->Ki =Ki_curr;
    pid_curr_iq->IntegralLimit = 6.0f;
    pid_curr_iq->MaxOut =6.0f;
	
	
		memset(pid_curr_id, 0, sizeof(PID_Structure));
		DWT_GetDeltaT(&pid_curr_id->DWT_CNT);
//		pid_curr_id->Kp = Kp_curr;
//    pid_curr_id->Ki = Ki_curr;
    pid_curr_id->IntegralLimit = 6.0f;
    pid_curr_id->MaxOut= 6.0f;
}

void PID_Speed_Init(PID_Structure *pid_speed,float Udc)
{
		memset(pid_speed, 0, sizeof(PID_Structure));
    DWT_GetDeltaT(&pid_speed->DWT_CNT);
    pid_speed->Kp = 0.01f;
    pid_speed->Ki = 0.5f;
    pid_speed->IntegralLimit = 0.5f;
    pid_speed->MaxOut =0.5f;
}

/**
 * @brief          PID controler
 * @param[in]  pid    PID structure
 * @param[in]  measure  the measured value
 * @param[in]  ref    the reference value
 * @retval         output of PID controler
 */
float PIDCalculate(PID_Structure *pid,float measure,float ref)
{
    pid->dt = Ts;
    pid->Measure = measure;
    pid->Ref = ref;
    pid->Err = pid->Ref - pid->Measure;
    pid->Pout = pid->Kp * pid->Err;
    pid->ITerm = pid->Ki * pid->Err;
    Trapezoid_Intergral(pid);
    Integral_Limit(pid);     //intergral limiting

    pid->Iout += pid->ITerm;           // intergral
    pid->OutPut = pid->Pout+pid->Iout; // the is no Dout

    Output_Limit(pid);

    // save current value for the next cycle
    pid->Last_Measure = pid->Measure;
    pid->Last_Output = pid->OutPut;
    pid->Last_Err = pid->Err;
    pid->Last_ITerm = pid->ITerm;

    return pid->OutPut;
}

/**
 * @brief          PID controler
 * @param[in]  pid    PID structure
 * @param[in]  measure  the measured value
 * @param[in]  ref    the reference value
 * @retval         output of PID controler
 */
float PIDCalculate_Q(PID_Structure *pid,float measure,float ref)
{
    pid->dt = Ts;
    pid->Measure = measure;
    pid->Ref = ref;
    pid->Err = pid->Ref - pid->Measure;
    pid->Pout = pid->Kp * pid->Err;
    pid->ITerm = pid->Ki * pid->Err;
    Trapezoid_Intergral(pid);
    // Integral_Limit(pid);     //intergral limiting

	static float temp_Output, temp_Iout;
    temp_Iout = pid->Iout + pid->ITerm;
    temp_Output = pid->Pout + pid->Iout;
    // if (abs(temp_Output) >= pid->MaxOut) //achieve the limit of output
    // {
    //     if (pid->Err * pid->Iout > 0) //but the integral keep going
    //     {
    //         pid->ITerm = 0; // The current integral term is set to zero
    //                         //   if (abs(pid->Err) < 1)
    //                         //   pid->Iout = 0;
    //     }
    // }

    if (temp_Iout > pid->IntegralLimit)
    {
        // pid->ITerm = 0; //stop integral
        pid->Iout = pid->IntegralLimit;
    }
    if (temp_Iout < -pid->IntegralLimit)
    {
        // pid->ITerm = 0; //stop integral
        pid->Iout = -pid->IntegralLimit;
    }

    pid->Iout += pid->ITerm;           // intergral
    pid->OutPut = pid->Pout+pid->Iout; // the is no Dout

    Output_Limit(pid);

    // save current value for the next cycle
    pid->Last_Measure = pid->Measure;
    pid->Last_Output = pid->OutPut;
    pid->Last_Err = pid->Err;
    pid->Last_ITerm = pid->ITerm;

    return pid->OutPut;
}

/**
  * @brief  start PWM
  * @param 	none
  * @retval none
  */
void PWM_Start(void)
{
	HAL_GPIO_WritePin(L6230_EN_GPIO_Port,L6230_EN_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(PWM_EN_A_GPIO_Port,PWM_EN_A_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(PWM_EN_B_GPIO_Port,PWM_EN_B_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(PWM_EN_C_GPIO_Port,PWM_EN_C_Pin,GPIO_PIN_SET);
}

/**
  * @brief  ͣstop PWM
  * @param 	none
  * @retval none
  */

void PWM_Stop(void)
{
	HAL_GPIO_WritePin(L6230_EN_GPIO_Port,L6230_EN_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_EN_A_GPIO_Port,PWM_EN_A_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_EN_B_GPIO_Port,PWM_EN_B_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWM_EN_C_GPIO_Port,PWM_EN_C_Pin,GPIO_PIN_RESET);
}

/**
  * @brief  temperature_lookup
  * @param 	none
  * @retval none
  */

float temperature_lookup(int ADC_value)
{
	static int length = sizeof(Rt_ADCvalue) / sizeof(Rt_ADCvalue[0]);
	if(ADC_value<=Rt_ADCvalue[0])
	{
		return 0;
	}
	else if(ADC_value>=Rt_ADCvalue[length-1])
	{
		return 1.0150000e+02;//maxmum temperature
	}
	else 
	{
		for (int i = 0; i < length; i++)
		{
			if(ADC_value>=Rt_ADCvalue[i]&&ADC_value<Rt_ADCvalue[i+1])
			{
				return T1[i];
			}
		}
	}
	// error to return NAN
  return NAN;
}

void Protection(void)
{
	static int FaultCount = 0;
	//Motor.Motor_Parameter.VBUS = ADC_value[4] / 4096 *2.9 * (169 + 9.31 ) / 9.31;
	Motor.Motor_Parameter.VBUS = ADC2_value[0] *0.013573956f;//calculate VBUS
	//overvoltage warning
	Motor.Motor_Parameter.temperature = temperature_lookup(ADC2_value[1]);//calculate temperature
    //L6230 warning 
	if (!HAL_GPIO_ReadPin(Fault_GPIO_Port,Fault_Pin))
	{
		FaultState.L6230Fault = error;
	}
	//overvoltage warning
	else if(Motor.Motor_Parameter.VBUS>VBUS_MAX)
	{
		FaultState.Overvoltage = error;
		FaultCount ++ ;
	}
	//undervoltage warning
	else if(Motor.Motor_Parameter.VBUS<VBUS_MIN)
	{
		FaultState.Undervoltage = error;
		FaultCount ++ ;
	}

	else if(Motor.Motor_Parameter.temperature>temperature_MAX)
	{
		FaultState.Overtemperature = error;
		FaultCount ++ ;
	}
	//overcurrent warning
	else if(Motor.I_3s.A>current_MAX||Motor.I_3s.B>current_MAX||Motor.I_3s.C>current_MAX)
	{
		FaultState.Overcurrent = error;
		FaultCount ++ ;
	}
	else
	{
		FaultState.L6230Fault = OK;
		FaultState.Overcurrent = OK;
		FaultState.Overtemperature = OK;
		FaultState.Overvoltage = OK;
		FaultState.Undervoltage = OK;
	}

	if(FaultCount >= 10000)
	{
		SYSTEM_STATE = WARNING_STATE;
	}



}

