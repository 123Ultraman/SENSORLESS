#include "foc.h"
#include "math.h"
#include "cordic.h"
#include "dma.h"
#include "offline_pi.h"
#include "stdio.h"
#include "sensorless.h"
#include "arm_math.h"
uint8_t Flag = 0;
int ZeroSpeedCnt = 0;
float AngleSum = 0;
float offset[3] = {2201.0};
extern UART_HandleTypeDef huart2;
extern int Field_State;
MOTOR_HandleTypeDef Motor = MOTOR_DEFAULT;
SystStatusEnum State = ADC_CALIBRATION;
FaultStateStruct FaultState = {OK};
//temperature LOOK_UP_Table
const float T1[] = T1_Table;
const int Rt_ADCvalue[] = Rt_ADCvalue_Table;

	/**
  * @brief  FocInit
  * @param 	none
  * @retval none
  */
void FocInit(void)
{
	//Hardware init
	CordicInit();
	HAL_TIM_Base_Start(&htim1);
  	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);
	//Enable PWM
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	//Enable and calibrate ADC
	HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1,ADC1_value,4);
	HAL_ADCEx_Calibration_Start(&hadc2,ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2,ADC2_value,2);
	//set the ADC reference vlotage to 2.9v
	VREFBUF->CSR = 0x21;
	//read motor parameters form flash
	Flash_Read_PartialStruct(&Motor.Motor_Parameter);
	Non_flux_Init(&observer);
	SysTick->LOAD = 17000000-1;
}

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
  * @brief  PI controler
  * @param 	PI structure
  * @retval none
  */

void PIControler(PI_Structure* PIStruct,float real_value,float set_value,float limti_value)
{
	PIStruct->last_error = PIStruct->error;
	PIStruct->error = set_value - real_value;
	PIStruct->integral = PIStruct->integral + PIStruct->Ki * PIStruct->error;
	PIStruct->gain = PIStruct->Kp * PIStruct->error;
	
	if (PIStruct->integral>limti_value)
	{
		PIStruct->integral = limti_value;
	}
	else if (PIStruct->integral< (-limti_value))
	{
		PIStruct->integral = -limti_value;
	}
	
	if (PIStruct->gain>limti_value)
	{
		PIStruct->gain = limti_value;
	}
	else if (PIStruct->gain< (-limti_value))
	{
		PIStruct->gain = -limti_value;
	}
	
	PIStruct->output = PIStruct->gain + PIStruct->integral;
	if (PIStruct->output> limti_value)
	{
		PIStruct->output = limti_value;
	}
	else if (PIStruct->output< (-limti_value))
	{
		PIStruct->output = -limti_value;
	}
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
  //L6230 warning 
	if (!HAL_GPIO_ReadPin(Fault_GPIO_Port,Fault_Pin))
	{
		FaultState.L6230Fault = error;
	}
	//Motor.Motor_Parameter.VBUS = ADC_value[4] / 4096 *2.9 * (169 + 9.31 ) / 9.31;
	Motor.Motor_Parameter.VBUS = ADC2_value[0] *0.013573956f;//calculate VBUS
	//overvoltage warning
	if(Motor.Motor_Parameter.VBUS>VBUS_MAX)
	{
		FaultState.Overvoltage = error;
		PWM_Stop();
	}
	//undervoltage warning
	else if(Motor.Motor_Parameter.VBUS<VBUS_MIN)
	{
		FaultState.Undervoltage = error;
		PWM_Stop();
	}
	//overvoltage warning
	Motor.Motor_Parameter.temperature = temperature_lookup(ADC2_value[1]);//calculate temperature
	if(Motor.Motor_Parameter.temperature>temperature_MAX)
	{
		FaultState.Overtemperature = error;
		PWM_Stop();
	}
	//overcurrent warning
	if(Motor.I_3s.A>current_MAX||Motor.I_3s.B>current_MAX||Motor.I_3s.C>current_MAX)
	{
		FaultState.Overcurrent = error;
		PWM_Stop();
	}
}

/**
  * @brief  ADC interrupts the callback function,to runs FOC
  * @param 	ADC_HandleTypeDef* hadc 
  * @retval none
  */
void HAL_ADC_ConvCpltCallback ( ADC_HandleTypeDef* hadc ) 
{
	static int time_count1 = 0;
	time_count1 = 0;
	SysTick->VAL = SysTick->LOAD;
	if(hadc == &hadc1)
	{
	static int LED_Count = 0;
	static int Count = 0;
	//current sampling
	Motor.Last_I_2s.Alpha = Motor.I_2s.Alpha;
	Motor.Last_I_2s.Beta = Motor.I_2s.Beta;
	Motor.Last_U_2s.Alpha = Motor.U_2s.Alpha;
	Motor.Last_U_2s.Beta = Motor.U_2s.Beta;
	Motor.I_3s.A = ( -(int)ADC1_value[0] + offset[0] ) / K_adc;
	Motor.I_3s.B = ( -(int)ADC1_value[1] + offset[1] ) / K_adc;
	Motor.I_3s.C = ( -(int)ADC1_value[2] + offset[2] ) / K_adc;
	Clark(&Motor.I_3s,&Motor.I_2s);
	Park(&Motor.I_2s,&Motor.I_2r,Motor.FOC_Parameter.AngleE_rad);
	
	//zero speed check
	ZeroSpeedCnt ++;
	if(ZeroSpeedCnt>ZeroSpeedCntMax)
	{
		ZeroSpeedCnt = 0;
		Motor.FOC_Parameter.SpeedMachReal = 0;
	}
	AngleSum = (float)(TIM2->CNT) / (float)TIM2_CLK * 6.0f * Motor.FOC_Parameter.SpeedMachReal*Pn;
	Motor.FOC_Parameter.AngleE = fmod((Motor.FOC_Parameter.AngleBase + AngleSum),360.0f);
	Motor.FOC_Parameter.AngleE_rad = Motor.FOC_Parameter.AngleE*0.017453292519943f;///1/180*pi;
	//protection
	Protection();

	switch (State)
	{
		static float U_alpha[5] = {0};
		//ADC_CALIBRATION,only run once
		case ADC_CALIBRATION:
		{
			static int sum[4] = {0};
			if(Count<1000)
			{
				Count++;
				sum[0] = sum[0] + ADC1_value[0];
				sum[1] = sum[1] + ADC1_value[1];
				sum[2] = sum[2] + ADC1_value[2];
				sum[3] = sum[3] + ADC2_value[0];
			}
			else 
			{
					offset[0] = sum[0] / 1000;
					offset[1] = sum[1] / 1000;
					offset[2] = sum[2] / 1000;
					Motor.Motor_Parameter.Udc = sum[3]*0.00001357371f; //Motor.Motor_Parameter.Udc = sum[3]/1000/ 4096 *2.9 * (169 + 9.31 ) / 9.31;
					Count = 0;
					State = FOC_RUN;
			}
		}
			break;
		
		//Rs indentification voltage design
		case RS_IDENTIFY_VOLTAGE_DESIGM:
		{
				Count ++;
				if(Count>=500)
				{
						Count = 0;
						Motor.U_2s.Beta = 0;
						Motor.U_2s.Alpha +=0.001f*Motor.Motor_Parameter.Udc;
				}
						SVPWM(&Motor.U_2s); 
				if(Motor.I_2s.Alpha>0.5*CURRENT_BASE)
				{
						Count = 0;
						State = PARAMETER_IDENTIFY_Rs;
						U_alpha[0] = Motor.U_2s.Alpha;
						U_alpha[1] = Motor.U_2s.Alpha+0.1f;
						U_alpha[2] = Motor.U_2s.Alpha+0.2f;
						U_alpha[3] = Motor.U_2s.Alpha+0.3f;
						U_alpha[4] = Motor.U_2s.Alpha+0.4f;
				}
		}
		break;
		//Rs indentification
		case PARAMETER_IDENTIFY_Rs:
		{
				static float I_alpha[5] = {0};
			  	static float i_sum = 0;
				const int stage_duration = 10000;  //every step voltage hold 1 second
				int stage = Count / stage_duration; //flag of switch step voltage

				if (stage == 0)  // beta axis positioning: Beta=3, Alpha=0
				{
						Motor.U_2s.Beta = 3;
						Motor.U_2s.Alpha = 0;
				}
				else if (stage == 1)  // alpha axis positioning: Beta=0, Alpha=3
				{
						Motor.U_2s.Beta = 0;
						Motor.U_2s.Alpha = 3;
				}
				else if (stage >= 2 && stage <= 6)  // alpha voltage injection
				{
						Motor.U_2s.Beta = 0;
						Motor.U_2s.Alpha = U_alpha[stage - 2];

						//sample at the last thousand count 
						if (Count % stage_duration >= 9000)
						{
								i_sum += Motor.I_3s.A;
								if (Count % stage_duration == 9999)  //calculate average alpha current
								{
										I_alpha[stage - 2] = i_sum / 1000;
										i_sum = 0;
								}
						}
				}
				else  // calculate Motor.Motor_Parameter.Rs
				{
						Motor.Motor_Parameter.Rs = Rs_calculate(I_alpha, U_alpha) - 0.73f;//0.73:the turn-on resistance of mos
				}
			    // count control
				if (Count < 70000)
				{
						Count++;
				}
				else
				{
						Count = 0;  //clean the count
						State = PARAMETER_IDENTIFY_L;  //to indentify L
				}
				SVPWM(&Motor.U_2s);
		}
		break;	
		
		//Ls identification
		case PARAMETER_IDENTIFY_L:
		{
			const int stage_duration = 10000;  //every step voltage hold 1 second
			int stage = Count / stage_duration; //flag of switch step voltage
			float angle = 0;
			if (stage == 0)  // beta axis positioning: Beta=3, Alpha=0
			{
					Motor.U_2s.Beta = 0.2f*Motor.Motor_Parameter.Udc;
					Motor.U_2s.Alpha = 0;
					SVPWM(&Motor.U_2s);
			}
			else if (stage == 1)  //  alpha axis positioning: Beta=0, Alpha=3
			{
					Motor.U_2s.Beta = 0;
					Motor.U_2s.Alpha = 0.2f*Motor.Motor_Parameter.Udc;
					SVPWM(&Motor.U_2s);	
			}
			else if (stage >= 2 && stage <= 6)  //high frequency injection for 5 seconds
			{
					
					angle = 0.6283185f * (Count % 10);
					Motor.U_2r.Q = 2;
					Motor.U_2r.D = 0;
					AntiPark(&Motor.U_2s,&Motor.U_2r,angle);
					SVPWM(&Motor.U_2s);
					
					float u1,u2,u3,u4;
			
					u1 = Motor.I_2s.Alpha - Motor.Last_I_2s.Alpha;
					u2 = Motor.I_2s.Beta - Motor.Last_I_2s.Beta;
					u3 = Motor.Last_U_2s.Alpha - Motor.Motor_Parameter.Rs*Motor.Last_I_2s.Alpha;
					u4 = Motor.Last_U_2s.Beta - Motor.Motor_Parameter.Rs*Motor.Last_I_2s.Beta;
				
					Motor.Motor_Parameter.Pd = Motor.Motor_Parameter.Pd/Motor.Motor_Parameter.u;
					Motor.Motor_Parameter.Pd = Motor.Motor_Parameter.Pd - (Motor.Motor_Parameter.Pd*Motor.Motor_Parameter.Pd)*(u3*u3)/(1+u3*u3*Motor.Motor_Parameter.Pd);
					Motor.Motor_Parameter.Ts_Ld = Motor.Motor_Parameter.Ts_Ld + Motor.Motor_Parameter.Pd*u3*(u1-u3*Motor.Motor_Parameter.Ts_Ld);
					
					Motor.Motor_Parameter.Pq = Motor.Motor_Parameter.Pq/Motor.Motor_Parameter.u;
					Motor.Motor_Parameter.Pq = Motor.Motor_Parameter.Pq - (Motor.Motor_Parameter.Pq*Motor.Motor_Parameter.Pq)*(u4*u4)/(1+u4*u4*Motor.Motor_Parameter.Pq);
					Motor.Motor_Parameter.Ts_Lq = Motor.Motor_Parameter.Ts_Lq + Motor.Motor_Parameter.Pq*u4*(u2-u4*Motor.Motor_Parameter.Ts_Lq);
					
					Motor.Motor_Parameter.Ld = Ts/Motor.Motor_Parameter.Ts_Ld;
					Motor.Motor_Parameter.Lq = Ts/Motor.Motor_Parameter.Ts_Lq;
			}
			//count control
			if (Count < 70000)
			{
					Count++; 
			}
			else
			{
					Count = 0;  //clean count 
					State = PARAMETER_IDENTIFY_Flux;  //switch state to flux indentification
					Motor.SpeedPI.Kp = 1.0E-4F;
					Motor.SpeedPI.Ki = 2.0E-7F;
					Motor.IqPI.Kp = 1.0F;
					Motor.IqPI.Ki = 0;
					Motor.IdPI.Kp = 0.0001F;
					Motor.IdPI.Ki = 0.000001F;
			}
		}
		break;
		
		//flux indentification
		case PARAMETER_IDENTIFY_Flux:
		{	
			float temp1 = 0,temp2 = 0;
			static float sum1 = 0; 

			//close loop to run motor and calculate flux
			if (Count < 100000)
			{
					Count++; 
					Motor.U_2r.Q = 6;
					Motor.U_2r.D = 0;
					AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
					SVPWM(&Motor.U_2s);
					//We = SpeedMachReal/60*2pi*Pn = SpeedMachReal*0.104719755f
					temp2 = Motor.FOC_Parameter.SpeedMachReal * 0.209439510f;
					temp1 = (Motor.U_2r.Q - Motor.Motor_Parameter.Rs*Motor.I_2r.Q  \
					- temp2 * Motor.Motor_Parameter.Ld * Motor.I_2r.D)/ temp2;
					if (Count >= 90000 && Count < 100000)
					{
						sum1 = sum1 + temp1;
						
					}
			}
			else if(Count >= 100000)
			{
					PWM_Stop();
					if(Motor.FOC_Parameter.SpeedMachReal == 0)
					{
							Count = 0;  //clean count
							State = PARAMETER_IDENTIFY_J;  //switch state to PARAMETER_IDENTIFY_J
							Motor.Motor_Parameter.flux = sum1 / 10000;
							sum1 = 0;
							Motor.U_2r.Q = 0;
							Motor.U_2r.D = 0;
							Motor.U_2s.Alpha = 0;
							Motor.U_2s.Beta = 0;
							Motor.SpeedPI.integral = 0;
							Motor.SpeedPI.output = 0;
							Motor.IqPI.integral = 0;
							Motor.IqPI.output = 0;
							Motor.IdPI.integral = 0;
							Motor.IdPI.output = 0;
							Motor.SpeedPI.Kp = 1.0E-4F;
							Motor.SpeedPI.Ki = 2.0E-7F;
							Motor.IqPI.Kp = 1.0F;
							Motor.IqPI.Ki = 0;
							Motor.IdPI.Kp = 0.0001F;
							Motor.IdPI.Ki = 0.000001F;
							PWM_Start();
					}
					
			}
		}
		break;
		
		case PARAMETER_IDENTIFY_J:
		{
			Motor.FOC_Parameter.SpeedMachRef = 3000;
			PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef,8);
			PIControler(&Motor.IqPI,Motor.I_2r.Q,Motor.SpeedPI.output,8);
			PIControler(&Motor.IdPI,Motor.I_2r.D,0,8);
			
			Motor.U_2r.Q = Motor.IqPI.output;
			Motor.U_2r.D = Motor.IdPI.output;
			
			AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
			SVPWM(&Motor.U_2s);
			
			
			float temp1 = 0 ,Wm = 0;
			static float sum = 0 ,temp2 = 1;
			temp1 = Motor.I_2r.Q*Motor.Motor_Parameter.flux*3*Ts;
			sum = sum + temp1;
			Wm = Motor.FOC_Parameter.SpeedMachReal * 0.104719755f;//Wm = SpeedMachReal/60*2pi = SpeedMachReal*0.104719755f
			Motor.Motor_Parameter.Pj = Motor.Motor_Parameter.Pj / Motor.Motor_Parameter.u;
			Motor.Motor_Parameter.Pj = Motor.Motor_Parameter.Pj - (Motor.Motor_Parameter.Pj \
			*Motor.Motor_Parameter.Pj)*(sum*sum)/(1+sum*sum*Motor.Motor_Parameter.Pj);
			temp2 = temp2 + Motor.Motor_Parameter.Pj*sum*(Wm - sum * temp2);
			
			
			//count control
			if (Count < 20000)
			{
					Count++; 
			}
			else
			{
					
					Motor.Motor_Parameter.J = 1/temp2;
					temp2 = 1;
					Count = 0;  
					State = FOC_RUN;  //switch state to FOC_RUN
					PWM_Stop();
					HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET );
					Flash_Write_PartialStruct(&Motor.Motor_Parameter);
					Motor.U_2r.Q = 0;
					Motor.U_2r.D = 0;
					Motor.U_2s.Alpha = 0;
					Motor.U_2s.Beta = 0;
					Motor.SpeedPI.integral = 0;
					Motor.SpeedPI.output = 0;
					Motor.IqPI.integral = 0;
					Motor.IqPI.output = 0;
					Motor.IdPI.integral = 0;
					Motor.IdPI.output = 0;
			}
		}
		break;
		
		case FOC_RUN:
		{
			LED_Count ++;
			if(LED_Count>=200000)
			{
					LED_Count = 0;
			}
			switch (Flag)
			{		
					case 3:
					{	
							if(LED_Count%10000 == 0)
							{
								HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							// Motor.U_2r.Q = (float)(2*(int)ADC1_value[3]-4095)/4095.0f*6.9282f;
							Motor.U_2r.D = -(float)((float)ADC1_value[3])/4095.0f*5.0f;
							// arm_sqrt_f32(SQ(threshold) - SQ(Motor.U_2r.D),&Motor.U_2r.Q);	
							arm_sqrt_f32(SQ(threshold)- SQ(Motor.U_2r.D),&Motor.U_2r.Q);	
							AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,observer.theta);
 							SVPWM_120(&Motor.U_2s);
							break;
					}
					case 2:
					{
							if(LED_Count%5000 == 0)
							{
								HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							Motor.FOC_Parameter.SpeedMachRef = (float)(2*(int)ADC1_value[3]-4095)*2;
							PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef,8);
							Motor.U_2r.Q = Motor.SpeedPI.output;
							AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
							SVPWM(&Motor.U_2s);
							break;
					}
					case 1:
					{		
							if(LED_Count%2500 == 0)
							{
								HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							// Motor.FOC_Parameter.SpeedMachRef = ((float)ADC1_value[3]/4095.0f)*7600.0f;
							static int speedcount = 0;
							if(speedcount <= 50000)
							{
								speedcount ++;
								Motor.FOC_Parameter.SpeedMachRef = speedcount/50000.0f*7450.0f;
							}
							else
							{
								Motor.FOC_Parameter.SpeedMachRef = 7450.0f;
							}
							// Motor.FOC_Parameter.SpeedMachRef = 7200.0f;
							switch(Field_State)
							{
								case 0:
								//speed loop
								PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef,100);
								//current loop
								PIControler(&Motor.IqPI,Motor.I_2r.Q,Motor.SpeedPI.output,7.639442);
								PIControler(&Motor.IdPI,Motor.I_2r.D,0,7.639442);
								Motor.U_2r.Q = Motor.IqPI.output;
								Motor.U_2r.D = Motor.IdPI.output;
								break;

								case 1:
								flux_weaken();
								break;

								default: break;
							}

							// //speed loop
							// PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef,8);
							// //current loop
							// PIControler(&Motor.IqPI,Motor.I_2r.Q,Motor.SpeedPI.output,10);
							// PIControler(&Motor.IdPI,Motor.I_2r.D,0,10);
							// Motor.U_2r.Q = Motor.IqPI.output;
							// Motor.U_2r.D = Motor.IdPI.output;

							AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
 							SVPWM_120(&Motor.U_2s);
							break;
					}
					default:break;
			}
			// flux_observer(Motor.U_2s.Alpha,Motor.U_2s.Beta,Motor.I_2s.Alpha,Motor.I_2s.Beta,&observer);
			break;
		}
		default:PWM_Stop();break;
	}
	}
time_count1 = SysTick->LOAD - SysTick->VAL;
} 

/**
  * @brief  HALL calculate
  * @param 	TIM_HandleTypeDef *  htim
  * @retval none
  */
void HAL_TIM_IC_CaptureCallback( TIM_HandleTypeDef *  htim ) 
{
	static uint8_t HALL = 0;
	if(htim == &htim2)
	{
		static float LastSpeedElecReal = 0;
		static int LastHall = 0;
		AngleSum = 0;
		LastHall = HALL;
		ZeroSpeedCnt = 0;
		HALL = (HAL_GPIO_ReadPin(HALL_A_GPIO_Port,HALL_A_Pin)<<2 |  HAL_GPIO_ReadPin(HALL_B_GPIO_Port,HALL_B_Pin)<<1
		| HAL_GPIO_ReadPin(HALL_C_GPIO_Port,HALL_C_Pin));
		LastSpeedElecReal = Motor.FOC_Parameter.SpeedMachReal;
		Motor.FOC_Parameter.SpeedMachReal = K_SPEED/TIM2->CCR1;
		switch(HALL)
		{
			case 1:Motor.FOC_Parameter.AngleBase = 210;
			if(LastHall == 5){Motor.FOC_Parameter.SpeedMachReal = -Motor.FOC_Parameter.SpeedMachReal;}break;
			case 2:Motor.FOC_Parameter.AngleBase = 90;
			if(LastHall == 3){Motor.FOC_Parameter.SpeedMachReal = -Motor.FOC_Parameter.SpeedMachReal;}break;
			case 3:Motor.FOC_Parameter.AngleBase = 150;
			if(LastHall == 1){Motor.FOC_Parameter.SpeedMachReal = -Motor.FOC_Parameter.SpeedMachReal;}break;
			case 4:Motor.FOC_Parameter.AngleBase = 330;
			if(LastHall == 6){Motor.FOC_Parameter.SpeedMachReal = -Motor.FOC_Parameter.SpeedMachReal;}break;
			case 5:Motor.FOC_Parameter.AngleBase = 270;
			if(LastHall == 4){Motor.FOC_Parameter.SpeedMachReal = -Motor.FOC_Parameter.SpeedMachReal;}break;
			case 6:Motor.FOC_Parameter.AngleBase = 30;
			if(LastHall == 2){Motor.FOC_Parameter.SpeedMachReal = -Motor.FOC_Parameter.SpeedMachReal;}break;
			default: break;
		}
		Motor.FOC_Parameter.SpeedMachReal = 0.5f * Motor.FOC_Parameter.SpeedMachReal + 0.5f * LastSpeedElecReal;
	}
}

/**
  * @brief  Key exit
  * @param 	GPIO_PIN
  * @retval none
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	static int start_time = 0;
	if(State == FOC_RUN)
	{
		if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_SET)  //when the KEY is pressed,start clock
		{
				start_time = HAL_GetTick();  //start clock
		}
		else  //the KEY is released
		{
				uint32_t hold_time = HAL_GetTick() - start_time;  //calculate the time of pressed
				if (hold_time < 1000)//if short pressed,switch foc mode 
				{
					Flag++;
					PWM_Start();
					if(Flag > 3 )
					{
						Flag = 0;
					}
					switch(Flag)
					{
						case 0:
							PWM_Stop();
							HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET );
							break;
						case 2:
						{
							Motor.SpeedPI.Kp = 1.0E-3f;
							Motor.SpeedPI.Ki = 1.0E-6f;
							break;
						}
						case 1:
						{
							Motor.SpeedPI.Kp = 1.0E-4F;
							Motor.SpeedPI.Ki = 2.0E-7F;
							Motor.IqPI.Kp = 1.0F;
							Motor.IqPI.Ki = 0;
							Motor.IdPI.Kp = 0.0001F;
							Motor.IdPI.Ki = 0.000001F;
							break;
						}
						default:break;
					}
						Motor.U_2r.Q = 0;
						Motor.U_2r.D = 0;
						Motor.U_2s.Alpha = 0;
						Motor.U_2s.Beta = 0;
						Motor.SpeedPI.integral = 0;
						Motor.SpeedPI.output = 0;
						Motor.IqPI.integral = 0;
						Motor.IqPI.output = 0;
						Motor.IdPI.integral = 0;
						Motor.IdPI.output = 0;
				}
				else//if long pressed,start parameter indentification
				{
						State = RS_IDENTIFY_VOLTAGE_DESIGM;
						Motor.Motor_Parameter.Pd = 1e5;
						Motor.Motor_Parameter.Pq = 1e5;
						Motor.Motor_Parameter.Pj = 1e5;
						Motor.Motor_Parameter.u = 0.99;
						Motor.Motor_Parameter.Ts_Ld = 1;
						Motor.Motor_Parameter.Ts_Lq = 1;
						Flag = 0;
						HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET );
						PWM_Start();
				}
		}
	}
}
