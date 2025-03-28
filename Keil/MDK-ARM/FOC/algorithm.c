#include "algorithm.h"
#include "foc.h"
#include "arm_common_tables.h"
#include "arm_math.h"  
#include "stdio.h"
#include "FOC.h"
Observer observer;
float D = 0,Q = 0;
extern MOTOR_HandleTypeDef Motor;
FW_STATE_TYPE FW_STATE = NO_FIELD_WEAKEN;

int utils_truncate_number_abs(float *number, float max)
{
    int did_trunc = 0;

    if (*number > max)
    {
        *number = max;
        did_trunc = 1;
    }
    else if (*number < -max)
    {
        *number = -max;
        did_trunc = 1;
    }

    return did_trunc;
}


void LPF(Observer *observer,float LPFFilter)
{
	observer->Speed=((observer->PLL.Out/Pn)*30.0f/(PI*observer->dt)-observer->Speed_pre)*LPFFilter+observer->Speed_pre;
	observer->Speed_pre=observer->Speed;

}

float sin_value,cos_value;

//init flux observer

void Non_flux_Init(Observer *observer)
{
    observer->Gain = 400000;//50000000;
    observer->PLL.Kp = 0.2;
    observer->PLL.Ki = 1.0;
    observer->x1_hat=0;
    observer->x1_hat_pre=0;
    observer->x2_hat=0;
    observer->x2_hat_pre=0;
    observer->theta=0.0f;
}

void flux_observer(float V_alpha, float V_beta, float i_alpha, float i_beta,Observer *observer)
{
    observer->dt = Ts;
    float y1, y2,n1,n2;
    y1 = -RS * i_alpha + V_alpha;
    y2 = -RS * i_beta + V_beta;

    n1 = observer->x1_hat_pre - LS * i_alpha;
    n2 = observer->x2_hat_pre - LS * i_beta;

    observer->err = SQ(PHI) - (SQ(n1) + SQ(n2));
    
//    if(observer->err>0.0)
//    observer->err=0.0f;

    observer->x1_hat = (observer->Gain * n1 * observer->err + y1) * observer->dt + observer->x1_hat_pre;
    observer->x2_hat = (observer->Gain * n2 * observer->err + y2) * observer->dt + observer->x2_hat_pre;
      
    UTILS_NAN_ZERO(observer->x1_hat);
    UTILS_NAN_ZERO(observer->x2_hat);
      
    observer->x1_hat_pre = observer->x1_hat;
    observer->x2_hat_pre = observer->x2_hat;

    observer->cos_theta = (observer->x1_hat - LS * i_alpha) / PHI;
    observer->sin_theta = (observer->x2_hat - LS * i_beta) / PHI;

    UTILS_NAN_ZERO(observer->cos_theta);
    UTILS_NAN_ZERO(observer->sin_theta);
    
    //PLL Phase-locked loop
    observer->PLL.err = observer->sin_theta * cos_value - observer->cos_theta *sin_value;
    observer->PLL.iterm += observer->PLL.Ki * observer->PLL.err*observer->dt;
    observer->PLL.Out = observer->PLL.err * observer->PLL.Kp + observer->PLL.iterm;
    LPF(observer,0.008f);
    observer->theta = observer->theta + observer->PLL.Out;

    while(observer->theta>2*PI) {
        observer->theta -= 2*PI;
    }
    while(observer->theta<0.0f) {
        observer->theta += 2*PI;
    }
    
    sin_value = arm_sin_f32(observer->theta);
    cos_value = arm_cos_f32(observer->theta);
}

void AntiPark_Overmodulation(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E)
{
	float Uref = 0;
	float theta = 0;
	float atan_theta = 0,modulu = 0;
	//calculate theta and modulu
	atan_theta = atan2f(UI_2r->Q,UI_2r->D);
	arm_sqrt_f32((UI_2r->D*UI_2r->D+UI_2r->Q*UI_2r->Q),&modulu);
	
	FW_STATE = Get_Field_State(modulu,Motor.FOC_Parameter.SpeedMachRef);
	
	Uref = U_ref_lookup(modulu);
	theta = atan_theta + Theta_E;

//	printf("%f,%f,%f,%f/r/n",atan_theta1,atan_theta2,modulu1,modulu2);
	UI_2s->Alpha = arm_cos_f32(theta)*Uref;
	UI_2s->Beta  = arm_sin_f32(theta)*Uref;
}

void SVPWM_120(UI_2s* UI_2s)
{	
	float Tx = 0.0f,Ty = 0.0f,Ta = 0.0f, Tb = 0.0f, Tc = 0.0f;
	int Tcm1 = 0,Tcm2 = 0,Tcm3 = 0;
	// -sqrt(3) * Period / 2.0f / U_dc * (sqrt(3) * 0.5f * UI_2s->Alpha + 0.5f * UI_2s->Beta)
    Tx = -1.0625000e+03f * UI_2s->Alpha - 6.1343463e+02f * UI_2s->Beta; 
    Ty = -1.2268693e+03f * UI_2s->Beta;		//-sqrt(3) * Period / 2.0f / U_dc * UI_2s->Beta

    if (Tx >= 0 && Ty >= 0) 
		{
        Tc = 0.0f;
        myfun(Tx, Ty,&Ta, &Tb);
    } 
		else if (Tx <= Ty && Tx <= 0) 
		{
        Ta = 0.0f;
        myfun(Ty - Tx, -Tx, &Tb, &Tc);
    } 
		else if (Tx > Ty && Ty <= 0) 
		{
        Tb = 0.0f;
        myfun(Tx - Ty, -Ty, &Ta, &Tc);
    } 
		else 
		{
        //Tx and Ty cannot both be 0
        printf("Error: Both Tx and Ty cannot be less than 0.\n");
        return;
    }
		
		// calculate To
    float T_max = fmax(fmax(Ta, Tb), Tc);
    float T0 = Period_2 - T_max;
		
		// Tcm1, Tcm2, Tcm3
    Tcm1 = (int)(Ta + T0 / 2.0f);
    Tcm2 = (int)(Tb + T0 / 2.0f);
    Tcm3 = (int)(Tc + T0 / 2.0f);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Tcm1);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Tcm2);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Tcm3);
		
}

void myfun(float T3, float T4, float* T1, float* T2) 
{
	float T3_abs = 0;
    float T4_abs = 0;
	arm_abs_f32(&T3,&T3_abs,1);
	arm_abs_f32(&T4,&T4_abs,1);

    if (T3_abs <= Period_2 && T4_abs <= Period_2) 
	{
        *T1 = T3;
        *T2 = T4;
    } 
	else if (T3_abs >= Period_2 && T4_abs >= Period_2) 
	{
        *T1 = Period_2;
        *T2 = Period_2;
    } 
	else if (T3_abs >= T4_abs) 
	{
        if (T3_abs - T4_abs >= Period_2) 
		{
            *T1 = Period_2;
            *T2 = 0.0f;
        } 
		else 
		{
            *T1 = Period_2;
            *T2 = Period_2 * T4 / T3;
        }
    } 
	else 
	{
        if (T4_abs - T3_abs >= Period_2) 
		{
            *T1 = 0.0f;
            *T2 = Period_2;
        } 
		else 
		{
            *T1 = Period_2 * T3 / T4;
            *T2 = Period_2;
        }
    }
}

float U_ref_lookup(float F1_vaule)
{
	static int length = sizeof(F1) / sizeof(F1[0]);
	//look up table
	if (F1_vaule<=U1)
	{
			return F1_vaule;
	}
	else if(F1_vaule>=F1[length-1])
	{
			return U_ref[length-1];
	}
	else
	{
			for (int i = 0; i < length; i++)
			{
				if(F1_vaule>=F1[i]&&F1_vaule<F1[i+1])
				{
					return U_ref[i];
				}
			}
	}
	return NAN;
}

float Hysteresis(float modulus) 
{
    static int count = 0; 
	
    if (count > 0) 
	{
		//hold 1000 times
		count++;
		if (count >= 1000) 
		{
			count = 0;  //clear count
		}
		return threshold;
	}
	
	else 
	{
		if (modulus >= threshold)
		{
			count = 1;  //begin hold
			return threshold;
		}
		else
		{
			return modulus;  //normally,return modulus itself
		}
	}
}

FW_STATE_TYPE Get_Field_State(float modulu,float SpeedRef)
{
	static FW_STATE_TYPE State = NO_FIELD_WEAKEN;
	static int count = 0;
	switch(State)
	{
		case NO_FIELD_WEAKEN:
		{
			if(modulu >= threshold)
			{
				count ++;
			}
			else
			{
				count = 0;
			}
			
			if(count >= 20 && SpeedRef >= 6500)
			{
				State = FIELD_WEAKEN;
				count = 0;
				flux_weaken_init(-0.001,-0.01,0.002,0.3);
			}
			break;
		}

		case FIELD_WEAKEN:
		{
			if(SpeedRef <= 6500)
			{
				count ++;
			}
			else
			{
				count = 0;
			}
			
			if(count >= 50 && SpeedRef <= 6500)
			{
				State = NO_FIELD_WEAKEN;
				count = 0;
			}
			break;
		}
		
		default: break;
	}
	return State;
}

void flux_weaken_init(float SpeedKp,float SpeedKi,float CurrentKp,float CurrentKi)
{
	Motor.FWSpeedPID.Kp = SpeedKp;
	Motor.FWSpeedPID.Ki = SpeedKp;
	Motor.FWCurrentPID.Kp = CurrentKp;
	Motor.FWCurrentPID.Ki = CurrentKi;
	Motor.FWSpeedPID.Err = 0;
	Motor.FWSpeedPID.Iout = 0;
	Motor.FWSpeedPID.Last_Err = 0;
	Motor.FWSpeedPID.OutPut = 0;
	Motor.FWSpeedPID.Pout= 0;
	Motor.FWCurrentPID.Err = 0;
	Motor.FWCurrentPID.Iout = 0;
	Motor.FWCurrentPID.Last_Err = 0;
	Motor.FWCurrentPID.OutPut = 0;
	Motor.FWCurrentPID.Pout = 0;
	Motor.FWSpeedPID.MaxOut = 10;
	Motor.FWSpeedPID.IntegralLimit = 10;
	Motor.FWCurrentPID.MaxOut = 4.0F;
	Motor.FWCurrentPID.IntegralLimit = 4.0F;
}

void flux_weaken(void)
{
	PIDCalculate(&Motor.FWSpeedPID,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef);
	PIDCalculate(&Motor.FWCurrentPID,Motor.I_2r.D,Motor.FWSpeedPID.OutPut);
	// PIControler(&Motor.FWSpeedPI,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef,10);
	// PIControler(&Motor.FWCurrentPI,Motor.I_2r.D,Motor.FWSpeedPI.output,4);
	Motor.U_2r.D = Motor.FWCurrentPID.OutPut;
	arm_sqrt_f32(SQ(threshold) - SQ(Motor.U_2r.D),&Motor.U_2r.Q);
}
