#include "sensorless.h"
#include "foc.h"
#include "arm_common_tables.h"
#include "arm_math.h"
//#include "fast_math_functions.h"    
#include "stdio.h"
VESC_Observer observer;
extern MOTOR_HandleTypeDef Motor;
int Field_State = 0;
float Uref = 0;
float theta = 0;
float atan_theta = 0,modulu = 0;
static int State = 0,count = 0;
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


void LPF(VESC_Observer *observer)
{
	float LPFFilter=0.008f;
	observer->Speed=((observer->PLL.Out/Pn)*30.0f/(PI*observer->dt)-observer->Speed_pre)*LPFFilter+observer->Speed_pre;
	observer->Speed_pre=observer->Speed;

}

float VESC_sin,VESC_cos;

//�����Դ����۲���

void Non_flux_Init(VESC_Observer *observer)
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

void flux_observer(float V_alpha, float V_beta, float i_alpha, float i_beta,VESC_Observer *observer)
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
    
    //���໷
    observer->PLL.err = observer->sin_theta * VESC_cos - observer->cos_theta *VESC_sin;
    observer->PLL.iterm += observer->PLL.Ki * observer->PLL.err*observer->dt;
    observer->PLL.Out = observer->PLL.err * observer->PLL.Kp + observer->PLL.iterm;
    LPF(observer);
    observer->theta = observer->theta + observer->PLL.Out;

    while(observer->theta>2*PI) {
        observer->theta -= 2*PI;
    }
    while(observer->theta<0.0f) {
        observer->theta += 2*PI;
    }
    
    VESC_sin = arm_sin_f32(observer->theta);
    VESC_cos = arm_cos_f32(observer->theta);
}

void AntiPark_Overmodulation(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E)
{
	//����ǶȺ�ģ��
	atan_theta = atan2f(UI_2r->Q,UI_2r->D);
	arm_sqrt_f32((UI_2r->D*UI_2r->D+UI_2r->Q*UI_2r->Q),&modulu);
	
	Field_State = Get_Field_State(modulu,&Motor.I_2r,Motor.FOC_Parameter.SpeedMachRef);
	
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
        // ��������Tx �� Ty �����ܶ�С��0
        printf("Error: Both Tx and Ty cannot be less than 0.\n");
        return;
    }
		
		// ���� T0
    float T_max = fmax(fmax(Ta, Tb), Tc);
    float T0 = Period_2 - T_max;
		
		// ���� Tcm1, Tcm2, Tcm3
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

    if (T3_abs <= Period_2 && T4_abs <= Period_2) {
        *T1 = T3;
        *T2 = T4;
    } else if (T3_abs >= Period_2 && T4_abs >= Period_2) {
        *T1 = Period_2;
        *T2 = Period_2;
    } else if (T3_abs >= T4_abs) {
        if (T3_abs - T4_abs >= Period_2) {
            *T1 = Period_2;
            *T2 = 0.0f;
        } else {
            *T1 = Period_2;
            *T2 = Period_2 * T4 / T3;
        }
    } else {
        if (T4_abs - T3_abs >= Period_2) {
            *T1 = 0.0f;
            *T2 = Period_2;
        } else {
            *T1 = Period_2 * T3 / T4;
            *T2 = Period_2;
        }
    }
}



float U_ref_lookup(float F1_vaule)
{
	static int length = sizeof(F1) / sizeof(F1[0]);
	//���Ե�������ֱ�����
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
    static int count = 0;  // ά�ִ���״̬�ļ�����
	
    if (count > 0) 
	{
		// ���Ѵ������������ 1000 ��
		count++;
		if (count >= 1000) 
		{
			count = 0;  // ��λ����
		}
		return threshold;
	}
	
	else 
	{
		if (modulus >= threshold)
		{
			count = 1;  // ��������
			return threshold;
		}
		else
		{
			return modulus;  // �����������1
		}
	}
}

int Get_Field_State(float modulu,UI_2r* I_2r,float SpeedRef)
{

	switch(State)
	{
		case 0:
		{
			if(modulu > threshold)
			{
				count ++;
			}
			else
			{
				count = 0;
			}
			
			if(count >= 20 && SpeedRef >= 7000)
			{
				State = 1;
				count = 0;
			}
			break;
		}

		case 1:
		{
			if(modulu <= threshold)
			{
				count ++;
			}
			else
			{
				count = 0;
			}
			
			if(count >= 20 && SpeedRef <= 7000)
			{
				State = 0;
				count = 0;
			}
			break;
		}
		
		default: break;
	}
	return State;
}

void flux_weaken(float SpeedRef,float SpeedReal)
{
	PIControler(&Motor.FWSpeedPI,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef);
	// Motor.U_2r.D = PIControler(&Motor.FWCurrentPI,Motor.I_2r.D,Motor.FWSpeedPI.output);
	arm_sqrt_f32(SQ(threshold) - SQ(Motor.U_2r.D),&Motor.U_2r.Q);
}
