#include "foc.h"
#include "math.h"
#include "offline_pi.h"
#include "stdio.h"
#include "VESC_control.h"
uint8_t Flag = 0;
int ZeroSpeedCnt = 0;
float AngleSum = 0;
float offset[3] = {2201.0};
extern UART_HandleTypeDef huart2;
MOTOR_HandleTypeDef Motor = MOTOR_DEFAULT;
SystStatusEnum State = ADC_CALIBRATION;
FaultStateStruct FaultState = {OK};

//温度表
const float T1[] = T1_Table;
const int Rt_ADCvalue[] = Rt_ADCvalue_Table;
	/**
  * @brief  初始化函数
  * @param 	none
  * @retval none
  */
void FocInit(void)
{
	//硬件外设初始化
	CordicInit();
	HAL_TIM_Base_Start(&htim1);
  HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);
	//开启PWM
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	//开启ADC采样
	HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1,ADC1_value,4);
	HAL_ADCEx_Calibration_Start(&hadc2,ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2,ADC2_value,2);
	//配置ADC采样电压2.9V
	VREFBUF->CSR = 0x21;
	//flash电机参数读取
	Flash_Read_PartialStruct(&Motor.Motor_Parameter);
	Non_flux_Init(&observer);
}

/**
  * @brief  CORDIC初始化函数
  * @param 	none
  * @retval none
  */
HAL_StatusTypeDef CordicInit(void)
{
	CORDIC_ConfigTypeDef sConfig;
	sConfig.Function = CORDIC_FUNCTION_SINE;
	sConfig.InSize = CORDIC_INSIZE_32BITS;
	sConfig.NbRead = CORDIC_NBREAD_2;
	sConfig.NbWrite =CORDIC_NBWRITE_1;
	sConfig.OutSize = CORDIC_OUTSIZE_32BITS;
	sConfig.Precision = CORDIC_PRECISION_6CYCLES;
	sConfig.Scale = CORDIC_SCALE_0;
	
	if(HAL_CORDIC_Configure(&hcordic,&sConfig) == HAL_OK)
		return HAL_OK;
	else return HAL_ERROR;
}

/**
  * @brief  CORDIC计算sin和cos
  * @param 	Theta 角度
  * @param 	pSinCos 结果，第一位是sin，第二位是cos
  * @retval none
  */

void Theta2SinCos(float Theta, float* pSinCos)
{
	hcordic.Instance->WDATA = Theta * THETA_360_Q31;
	pSinCos[0] = (int32_t)(hcordic.Instance->RDATA) / VALUE_Q31_FLOAT;
	pSinCos[1] = (int32_t)(hcordic.Instance->RDATA) / VALUE_Q31_FLOAT;
}

/**
  * @brief  等幅值克拉克变换，三相静止坐标系电流到两相精致静止坐标系电流
  * @param 	Motor.I_3s 三相静止坐标系电流
  * @param 	Motor.I_2s 两相静止坐标系电流
  * @retval none
  */
void Clark(UI_3s* UI_3s,UI_2s* UI_2s)
{
	UI_2s->Alpha = (UI_3s->A - VALUE_1_2*UI_3s->B - VALUE_1_2*UI_3s->C)*VALUE_2_3;
	UI_2s->Beta = (VALUE_SQRT3_2*UI_3s->B - VALUE_SQRT3_2*UI_3s->C)*VALUE_2_3;
}

/**
  * @brief  克拉克反变换，两相静止坐标系电流到三相静止坐标系电流
  * @param 	Motor.I_3s 三相静止坐标系电流
  * @param 	Motor.I_2s 两相静止坐标系电流
  * @retval none
  */
void AntiClark(UI_3s* UI_3s,UI_2s* UI_2s)
{
	UI_3s->A = UI_2s->Alpha;
	UI_3s->B = -VALUE_1_2 * UI_2s->Alpha + VALUE_SQRT3_2 * UI_2s->Beta;
	UI_3s->C = -VALUE_1_2 * UI_2s->Alpha - VALUE_SQRT3_2 * UI_2s->Beta;
}

/**
  * @brief  帕克变换，两相静止坐标系到两相旋转坐标系
  * @param 	UI_2s 两相静止坐标系电流
  * @param 	UI_2r 两相旋转坐标系电流
  * @retval none
  */
void Park(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E)
{
	float pSinCos[2];
	Theta2SinCos(Theta_E,pSinCos);
	UI_2r->D = pSinCos[1] * UI_2s->Alpha + pSinCos[0] * UI_2s->Beta;
	UI_2r->Q = -pSinCos[0] * UI_2s->Alpha + pSinCos[1] * UI_2s->Beta;
}

/**
  * @brief  帕克反变换，两相旋转坐标系到两相静止坐标系
  * @param 	UI_2s 两相静止坐标系电流
  * @param 	UI_2r 两相旋转坐标系电流
  * @retval none
  */
void AntiPark(UI_2s* UI_2s,UI_2r* UI_2r,float Theta_E)
{
	float pSinCos[2];
	Theta2SinCos(Theta_E,pSinCos);
	UI_2s->Alpha = pSinCos[1] * UI_2r->D - pSinCos[0] * UI_2r->Q;
	UI_2s->Beta = pSinCos[0] * UI_2r->D + pSinCos[1] * UI_2r->Q;
}

/**
  * @brief  SVPWM调制
  * @param 	UI_2s 两相静止坐标系电压
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
  * @brief  PI控制器
  * @param 	PI结构体
  * @retval none
  */

void PIControler(PI_Structure* PI,float real_value,float set_value)
{
	PI->last_error = PI->error;
	PI->error = set_value - real_value;
	PI->integral = PI->integral + PI->Ki * PI->error;
	PI->gain = PI->Kp * PI->error;
	
	if (PI->integral>6)
	{
		PI->integral = 6;
	}
	else if (PI->integral< (-6))
	{
		PI->integral = -6;
	}
	
	if (PI->gain>6)
	{
		PI->gain = 6;
	}
	else if (PI->gain< (-6))
	{
		PI->gain = -6;
	}
	
	PI->output = PI->gain + PI->integral;
	if (PI->output>6)
	{
		PI->output = 6;
	}
	else if (PI->output< (-6))
	{
		PI->output = -6;
	}
}
/**
  * @brief  开启PWM
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
  * @brief  停止PWM
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
  * @brief  温度查表
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
		return 1.0150000e+02;
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
	// 返回 NaN，表示逻辑错误
  return NAN;
}

void Protection(void)
{
  //L6230报警
	if (!HAL_GPIO_ReadPin(Fault_GPIO_Port,Fault_Pin))
	{
		FaultState.L6230Fault = error;
	}
	//Motor.Motor_Parameter.VBUS = ADC_value[4] / 4096 *2.9 * (169 + 9.31 ) / 9.31;
	Motor.Motor_Parameter.VBUS = ADC2_value[0] *0.013573956f;//母线电压采样
	//过压保护
	if(Motor.Motor_Parameter.VBUS>VBUS_MAX)
	{
		FaultState.Overvoltage = error;
		PWM_Stop();
	}
	//欠压保护
	else if(Motor.Motor_Parameter.VBUS<VBUS_MIN)
	{
		FaultState.Undervoltage = error;
		PWM_Stop();
	}
	//过温保护
	Motor.Motor_Parameter.temperature = temperature_lookup(ADC2_value[1]);//温度采样，查表
	if(Motor.Motor_Parameter.temperature>temperature_MAX)
	{
		FaultState.Overtemperature = error;
		PWM_Stop();
	}
	//过流保护
	if(Motor.I_3s.A>current_MAX||Motor.I_3s.B>current_MAX||Motor.I_3s.C>current_MAX)
	{
		FaultState.Overcurrent = error;
		PWM_Stop();
	}
}

/**
  * @brief  ADC转换完成中断回调函数，此中断中完成FOC算法
  * @param 	ADC_HandleTypeDef* hadc 
  * @retval none
  */
void HAL_ADC_ConvCpltCallback ( ADC_HandleTypeDef* hadc ) 
{
	if(hadc == &hadc1)
	{
	static int LED_Count = 0;
	static int Count = 0;
	//电流计算
	Motor.Last_I_2s.Alpha = Motor.I_2s.Alpha;
	Motor.Last_I_2s.Beta = Motor.I_2s.Beta;
	Motor.Last_U_2s.Alpha = Motor.U_2s.Alpha;
	Motor.Last_U_2s.Beta = Motor.U_2s.Beta;
	Motor.I_3s.A = ( -(int)ADC1_value[0] + offset[0] ) / K_adc;
	Motor.I_3s.B = ( -(int)ADC1_value[1] + offset[1] ) / K_adc;
	Motor.I_3s.C = ( -(int)ADC1_value[2] + offset[2] ) / K_adc;
	Clark(&Motor.I_3s,&Motor.I_2s);
	Park(&Motor.I_2s,&Motor.I_2r,Motor.FOC_Parameter.AngleE);
	
	//电机角度计算
	ZeroSpeedCnt ++;
	if(ZeroSpeedCnt>ZeroSpeedCntMax)
	{
		ZeroSpeedCnt = 0;
		Motor.FOC_Parameter.SpeedElecReal = 0;
	}
	AngleSum = (float)(TIM2->CNT) / (float)TIM2_CLK * 6.0f * Motor.FOC_Parameter.SpeedElecReal;
	Motor.FOC_Parameter.AngleE = fmod((Motor.FOC_Parameter.AngleBase + AngleSum),360.0f);
	
	//保护
	Protection();

	switch (State)
	{
		//校准ADC
		static float U_alpha[5] = {0};
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
		
		//电阻辨识电压设计
		case RS_IDENTIFY_VOLTAGE_DESIGM:
		{
				Count ++;
				if(Count>=500)
				{
						Count = 0;
						Motor.U_2s.Beta = 0;
						Motor.U_2s.Alpha +=0.001f*Motor.Motor_Parameter.Udc;
				}
						SVPWM(&Motor.U_2s);  // 执行SVPWM
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
		//电阻辨识
		case PARAMETER_IDENTIFY_Rs:
		{
				static float I_alpha[5] = {0};
			  static float i_sum = 0;
				const int stage_duration = 10000;  // 每个阶段的计数范围
				int stage = Count / stage_duration; // 计算当前处于哪个阶段

				if (stage == 0)  // 第一阶段: Beta=3, Alpha=0
				{
						Motor.U_2s.Beta = 3;
						Motor.U_2s.Alpha = 0;
				}
				else if (stage == 1)  // 第二阶段: Beta=0, Alpha=3
				{
						Motor.U_2s.Beta = 0;
						Motor.U_2s.Alpha = 3;
				}
				else if (stage >= 2 && stage <= 6)  // 第三到第七阶段: Alpha 取数组值
				{
						Motor.U_2s.Beta = 0;
						Motor.U_2s.Alpha = U_alpha[stage - 2];

						// 在最后1000次进行电流累加
						if (Count % stage_duration >= 9000)
						{
								i_sum += Motor.I_3s.A;
								if (Count % stage_duration == 9999)  // 结束该阶段时计算平均值
								{
										I_alpha[stage - 2] = i_sum / 1000;
										i_sum = 0;
								}
						}
				}
				else  // 计算 Motor.Motor_Parameter.Rs
				{
						Motor.Motor_Parameter.Rs = Rs_calculate(I_alpha, U_alpha) - 0.73f;
						
						// printf("Motor.Motor_Parameter.Rs等于：%f\r\n", Motor.Motor_Parameter.Rs);
				}
			    // 计数控制
				if (Count < 70000)
				{
						Count++;  // 计数递增
				}
				else
				{
						Count = 0;  // 复位计数
						State = PARAMETER_IDENTIFY_L;  // 切换到下一个状态
				}
				SVPWM(&Motor.U_2s);  // 执行SVPWM
		}
		break;	
		
		//电感辨识
		case PARAMETER_IDENTIFY_L:
		{
			const int stage_duration = 10000;  // 每个阶段的计数范围
			int stage = Count / stage_duration; // 计算当前处于哪个阶段
			float angle = 0;
			if (stage == 0)  // 第一阶段: Beta=3, Alpha=0
			{
					Motor.U_2s.Beta = 0.2f*Motor.Motor_Parameter.Udc;
					Motor.U_2s.Alpha = 0;
					SVPWM(&Motor.U_2s);
			}
			else if (stage == 1)  // 第二阶段: Beta=0, Alpha=3
			{
					Motor.U_2s.Beta = 0;
					Motor.U_2s.Alpha = 0.2f*Motor.Motor_Parameter.Udc;
					SVPWM(&Motor.U_2s);	
			}
			else if (stage >= 2 && stage <= 6)  // 第三到第七阶段: Alpha 取数组值
			{
					
					angle = 36.0f * (Count % 10);
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
			//计数控制
			if (Count < 70000)
			{
					Count++;  // 计数递增
			}
			else
			{
					Count = 0;  // 复位计数
					State = PARAMETER_IDENTIFY_Flux;  // 切换到下一个状态
					Motor.SpeedPI.Kp = 1.0E-4F;
					Motor.SpeedPI.Ki = 2.0E-7F;
					Motor.IqPI.Kp = 1.0F;
					Motor.IqPI.Ki = 0;
					Motor.IdPI.Kp = 0.0001F;
					Motor.IdPI.Ki = 0.000001F;
			}
		}
		break;
		
		//磁链辨识
		case PARAMETER_IDENTIFY_Flux:
		{	
			float temp1 = 0,temp2 = 0;
			static float sum1 = 0; 

			//计数控制
			if (Count < 100000)
			{
					Count++;  // 计数递增
					Motor.U_2r.Q = 6;
					Motor.U_2r.D = 0;
					AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE);
					SVPWM(&Motor.U_2s);
					//We = SpeedElecReal/60*2pi*Pn = SpeedElecReal*0.104719755f
					temp2 = Motor.FOC_Parameter.SpeedElecReal * 0.209439510f;
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
					if(Motor.FOC_Parameter.SpeedElecReal == 0)
					{
							Count = 0;  // 复位计数
							State = PARAMETER_IDENTIFY_J;  // 切换到下一个状态
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
			Motor.FOC_Parameter.SpeedElecRef = 3000;
			PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedElecReal,Motor.FOC_Parameter.SpeedElecRef);
			PIControler(&Motor.IqPI,Motor.I_2r.Q,Motor.SpeedPI.output);
			PIControler(&Motor.IdPI,Motor.I_2r.D,0);
			
			Motor.U_2r.Q = Motor.IqPI.output;
			Motor.U_2r.D = Motor.IdPI.output;
			
			AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE);
			SVPWM(&Motor.U_2s);
			
			
			float temp1 = 0 ,Wm = 0;
			static float sum = 0 ,temp2 = 1;
			temp1 = Motor.I_2r.Q*Motor.Motor_Parameter.flux*3*Ts;
			sum = sum + temp1;
			Wm = Motor.FOC_Parameter.SpeedElecReal * 0.104719755f;//Wm = SpeedElecReal/60*2pi = SpeedElecReal*0.104719755f
			Motor.Motor_Parameter.Pj = Motor.Motor_Parameter.Pj / Motor.Motor_Parameter.u;
			Motor.Motor_Parameter.Pj = Motor.Motor_Parameter.Pj - (Motor.Motor_Parameter.Pj \
			*Motor.Motor_Parameter.Pj)*(sum*sum)/(1+sum*sum*Motor.Motor_Parameter.Pj);
			temp2 = temp2 + Motor.Motor_Parameter.Pj*sum*(Wm - sum * temp2);
			
			
			//计数控制
			if (Count < 20000)
			{
					Count++;  // 计数递增
			}
			else
			{
					
					Motor.Motor_Parameter.J = 1/temp2;
					temp2 = 1;
					Count = 0;  // 复位计数
					State = FOC_RUN;  // 切换到下一个状态
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
			LED_Count ++;
			if(LED_Count>=200000)
			{
					LED_Count = 0;
			}
			switch (Flag)
			{
					
					case 1:
					{
							if(LED_Count%10000 == 0)
							{
									HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							Motor.U_2r.Q = (float)(2*(int)ADC1_value[3]-4095)/4095.0f*6.0f;
							AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE);
							SVPWM(&Motor.U_2s);  
							break;
					}
					case 2:
					{
							if(LED_Count%5000 == 0)
							{
									HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							Motor.FOC_Parameter.SpeedElecRef = (float)(2*(int)ADC1_value[3]-4095);
							PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedElecReal,Motor.FOC_Parameter.SpeedElecRef);
							Motor.U_2r.Q = Motor.SpeedPI.output;
							AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE);
							SVPWM(&Motor.U_2s);
							break;
					}
					case 3:
					{		
							if(LED_Count%2500 == 0)
							{
									HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							Motor.FOC_Parameter.SpeedElecRef = (float)(2*(int)ADC1_value[3]-4095);
							PIControler(&Motor.SpeedPI,Motor.FOC_Parameter.SpeedElecReal,Motor.FOC_Parameter.SpeedElecRef);
						
							PIControler(&Motor.IqPI,Motor.I_2r.Q,Motor.SpeedPI.output);
							PIControler(&Motor.IdPI,Motor.I_2r.D,0);
							
							Motor.U_2r.Q = Motor.IqPI.output;
							Motor.U_2r.D = Motor.IdPI.output;
							
							AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE);
							SVPWM(&Motor.U_2s);
							break;
					}
					case 4:
					{
							if(LED_Count%1250 == 0)
							{
									HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
							}
							Motor.FOC_Parameter.SpeedElecRef = (float)(2*(int)ADC1_value[3]-4095);
							PIControler(&Motor.SpeedPI,observer.Speed,Motor.FOC_Parameter.SpeedElecRef);
						
							PIControler(&Motor.IqPI,Motor.I_2r.Q,Motor.SpeedPI.output);
							PIControler(&Motor.IdPI,Motor.I_2r.D,0);
							
							Motor.U_2r.Q = Motor.IqPI.output;
							Motor.U_2r.D = Motor.IdPI.output;
							
							AntiPark(&Motor.U_2s,&Motor.U_2r,observer.theta*57.295779513f);
							SVPWM(&Motor.U_2s);
							
							break;
					}
					default:break;
			}
			flux_observer(Motor.U_2s.Alpha,Motor.U_2s.Beta,Motor.I_2s.Alpha,Motor.I_2s.Beta,&observer);
			
			float temp[4];
			uint8_t tx_buffer[1 + sizeof(temp) + 1];
			temp[0] = observer.cos_theta;
			temp[1] = observer.sin_theta;
			temp[2] = observer.Speed;
			temp[3] = observer.theta;
			tx_buffer[0] = 'S';

			// 复制 float 数组到 tx_buffer
			memcpy(&tx_buffer[1], temp, sizeof(temp));

			// 帧尾 'E'
			tx_buffer[1 + sizeof(temp)] = 'E';
			HAL_UART_Transmit_DMA(&huart2,(uint8_t*)tx_buffer,sizeof(tx_buffer));
			break;
			
		default:PWM_Stop();break;
	}
	}
} 

/**
  * @brief  定时器二捕获中断回调函数，用于更新HALL
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
		LastSpeedElecReal = Motor.FOC_Parameter.SpeedElecReal;
		Motor.FOC_Parameter.SpeedElecReal = K_SPEED/TIM2->CCR1;
		//滤波
//		Motor.FOC_Parameter.SpeedElecReal = 0.5f * Motor.FOC_Parameter.SpeedElecReal + 0.5f * LastSpeedElecReal;
		switch(HALL)
		{
			case 1:Motor.FOC_Parameter.AngleBase = 210;
			if(LastHall == 5){Motor.FOC_Parameter.SpeedElecReal = -Motor.FOC_Parameter.SpeedElecReal;}break;
			case 2:Motor.FOC_Parameter.AngleBase = 90;
			if(LastHall == 3){Motor.FOC_Parameter.SpeedElecReal = -Motor.FOC_Parameter.SpeedElecReal;}break;
			case 3:Motor.FOC_Parameter.AngleBase = 150;
			if(LastHall == 1){Motor.FOC_Parameter.SpeedElecReal = -Motor.FOC_Parameter.SpeedElecReal;}break;
			case 4:Motor.FOC_Parameter.AngleBase = 330;
			if(LastHall == 6){Motor.FOC_Parameter.SpeedElecReal = -Motor.FOC_Parameter.SpeedElecReal;}break;
			case 5:Motor.FOC_Parameter.AngleBase = 270;
			if(LastHall == 4){Motor.FOC_Parameter.SpeedElecReal = -Motor.FOC_Parameter.SpeedElecReal;}break;
			case 6:Motor.FOC_Parameter.AngleBase = 30;
			if(LastHall == 2){Motor.FOC_Parameter.SpeedElecReal = -Motor.FOC_Parameter.SpeedElecReal;}break;
			default: break;
		}
	}
}

/**
  * @brief  按键外部中断，更新Flag
  * @param 	外部中断GPIO_Pin口
  * @retval none
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	static int start_time = 0;
	if(State == FOC_RUN)
	{
		if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_SET)  // 按下 (高电平)
		{
				start_time = HAL_GetTick();  // 记录按下时间
		}
		else  // 松开 (高电平)
		{
				uint32_t hold_time = HAL_GetTick() - start_time;  // 计算按下时长
				if (hold_time < 1000)//短按
				{
					Flag++;
					PWM_Start();
					if(Flag > 4 )
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
						case 3:
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
				else//长按
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
