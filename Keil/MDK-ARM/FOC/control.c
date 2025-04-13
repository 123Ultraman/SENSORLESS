#include "math.h"
#include "FOC.h"
#include "algorithm.h"
#include "offline_pi.h"
#include "arm_math.h"
#include "control.h"
int ZeroSpeedCnt = 0;
float AngleSum = 0;
uint32_t ADC1_value[4];
uint32_t ADC2_value[2];
extern  FW_STATE_TYPE FW_STATE;
STSTEM_STATE_TYPE SYSTEM_STATE = ADC_CALIBRATION;
FOC_MODE_TYPE FOC_MODE = IDIE_STATE;
MOTOR_HandleTypeDef Motor = MOTOR_DEFAULT;

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
     HFSVI_Sensorless_Init(&HFSVI);
     SysTick->LOAD = 17000000-1;
 }

/**
  * @brief  ADC1 interrupts the callback function,to runs FOC
  * @param 	ADC_HandleTypeDef* hadc 
  * @retval none
  */
 void HAL_ADC_ConvCpltCallback ( ADC_HandleTypeDef* hadc ) 
 {
     static float offset[3] = {2201.0f};
     static int LED_Count = 0;
     static int Count = 0;
     SysTick->VAL = SysTick->LOAD;
    //  if(hadc == &hadc2)
    //  {
    //  timecount = ADC2_value[0] * ADC2_value[1];
    //  }
     if(hadc == &hadc1)
     {
        //current sampling,10khz
        Motor.Last_I_2s.Alpha = Motor.I_2s.Alpha;
        Motor.Last_I_2s.Beta = Motor.I_2s.Beta;
        Motor.Last_U_2s.Alpha = Motor.U_2s.Alpha;
        Motor.Last_U_2s.Beta = Motor.U_2s.Beta;
        Motor.I_3s.A = ( -(int)ADC1_value[0] + offset[0] ) / K_adc;
        Motor.I_3s.B = ( -(int)ADC1_value[1] + offset[1] ) / K_adc;
        Motor.I_3s.C = ( -(int)ADC1_value[2] + offset[2] ) / K_adc;
        Clark(&Motor.I_3s,&Motor.I_2s);
        // Park(&Motor.I_2s,&Motor.I_2r,Motor.FOC_Parameter.AngleE_rad);
        
        //zero speed check
        ZeroSpeedCnt ++;
        if(ZeroSpeedCnt >= ZeroSpeedCntMax)
        {
            ZeroSpeedCnt = 0;
            Motor.FOC_Parameter.SpeedMachReal = 0;
        }
        AngleSum = (float)(TIM2->CNT) / (float)TIM2_CLK * 6.0f * Motor.FOC_Parameter.SpeedMachReal*Pn;
        Motor.FOC_Parameter.AngleE = fmod((Motor.FOC_Parameter.AngleBase + AngleSum),360.0f);
        Motor.FOC_Parameter.AngleE_rad = Motor.FOC_Parameter.AngleE*0.017453292519943f;///1/180*pi;
        //protection
        // Protection();
        
        switch (SYSTEM_STATE)
        {
            static float RS_IDENTIFI_U_ALPHA[5] = {0};
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
                    SYSTEM_STATE = FOC_RUN;
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
                    SYSTEM_STATE = PARAMETER_IDENTIFY_Rs;
                    RS_IDENTIFI_U_ALPHA[0] = Motor.U_2s.Alpha;
                    RS_IDENTIFI_U_ALPHA[1] = Motor.U_2s.Alpha+0.01f*Motor.Motor_Parameter.Udc;
                    RS_IDENTIFI_U_ALPHA[2] = Motor.U_2s.Alpha+0.02f*Motor.Motor_Parameter.Udc;
                    RS_IDENTIFI_U_ALPHA[3] = Motor.U_2s.Alpha+0.03f*Motor.Motor_Parameter.Udc;
                    RS_IDENTIFI_U_ALPHA[4] = Motor.U_2s.Alpha+0.04f*Motor.Motor_Parameter.Udc;
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
                    Motor.U_2s.Beta = 0.3f*Motor.Motor_Parameter.Udc;
                    Motor.U_2s.Alpha = 0;
                }
                else if (stage == 1)  // alpha axis positioning: Beta=0, Alpha=3
                {
                    Motor.U_2s.Beta = 0;
                    Motor.U_2s.Alpha = 0.3f*Motor.Motor_Parameter.Udc;
                }
                else if (stage >= 2 && stage <= 6)  // alpha voltage injection
                {
                    Motor.U_2s.Beta = 0;
                    Motor.U_2s.Alpha = RS_IDENTIFI_U_ALPHA[stage - 2];

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
                    Motor.Motor_Parameter.Rs = Rs_calculate(I_alpha, RS_IDENTIFI_U_ALPHA) - 0.73f;//0.73:the turn-on resistance of mos
                }
                // count control
                if (Count < 70000)
                {
                    Count++;
                }
                else
                {
                    Count = 0;  //clean the count
                    SYSTEM_STATE = PARAMETER_IDENTIFY_L;  //switch state to indentify L
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
                    Motor.U_2r.Q = 0.2f*Motor.Motor_Parameter.Udc;
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
                    SYSTEM_STATE = PARAMETER_IDENTIFY_Flux;  //switch state to flux indentification
                    Motor.SpeedPID.Kp = 1.0E-4F;
                    Motor.SpeedPID.Ki = 2.0E-3F;
                    Motor.IqPID.Kp = 1.0F;
                    Motor.IqPID.Ki = 0;
                    Motor.IdPID.Kp = 0.0001F;
                    Motor.IdPID.Ki = 0.01F;
                }
            }
            break;
            
            //flux indentification
            case PARAMETER_IDENTIFY_Flux:
            {	
                float temp1 = 0,temp2 = 0;
                static float sum1 = 0; 
    
                //open loop to run motor and calculate flux
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
                    //wait foe the motor to stop runing
                    if(Motor.FOC_Parameter.SpeedMachReal == 0)
                    {
                        Count = 0;  //clean count
                        SYSTEM_STATE = PARAMETER_IDENTIFY_J;  //switch state to PARAMETER_IDENTIFY_J
                        Motor.Motor_Parameter.flux = sum1 / 10000;
                        sum1 = 0;
                        //prepare for J identification
                        Motor.U_2r.Q = 0;
                        Motor.U_2r.D = 0;
                        Motor.U_2s.Alpha = 0;
                        Motor.U_2s.Beta = 0;
                        Motor.SpeedPID.Iout = 0;
                        Motor.SpeedPID.OutPut = 0;
                        Motor.IqPID.Iout = 0;
                        Motor.IqPID.OutPut = 0;
                        Motor.IdPID.Iout = 0;
                        Motor.IdPID.OutPut = 0;

                        Motor.SpeedPID.Kp = 1.0E-4F;
                        Motor.SpeedPID.Ki = 2.0E-3F;
                        Motor.SpeedPID.MaxOut = 10;
                        Motor.SpeedPID.IntegralLimit = 10;

                        Motor.IqPID.Kp = 1.0F;
                        Motor.IqPID.Ki = 0.01F;
                        Motor.IqPID.MaxOut = threshold;
                        Motor.IqPID.IntegralLimit = threshold;

                        Motor.IdPID.Kp = 0.0001F;
                        Motor.IdPID.Ki = 0.01F;
                        Motor.IdPID.MaxOut = threshold;
                        Motor.IdPID.IntegralLimit = threshold;
                        PWM_Start();
                    }  
                }
            }
            break;
            
            case PARAMETER_IDENTIFY_J:
            {
                ////close loop to run motor and calculate J
                Motor.FOC_Parameter.SpeedMachRef = 3000;
                //speed loop
                PIDCalculate(&Motor.SpeedPID,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef);
                //current loop
                PIDCalculate(&Motor.IqPID,Motor.I_2r.Q,Motor.SpeedPID.OutPut);
                PIDCalculate(&Motor.IdPID,Motor.I_2r.D,0);
                
                Motor.U_2r.Q = Motor.IqPID.OutPut;
                Motor.U_2r.D = Motor.IdPID.OutPut;
                
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
                    SYSTEM_STATE = FOC_RUN;  //switch state to FOC_RUN
                    PWM_Stop();
                    HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET );
                    Flash_Write_PartialStruct(&Motor.Motor_Parameter);
                    Motor.U_2r.Q = 0;
                    Motor.U_2r.D = 0;
                    Motor.U_2s.Alpha = 0;
                    Motor.U_2s.Beta = 0;
                    Motor.SpeedPID.Iout = 0;
                    Motor.SpeedPID.OutPut = 0;
                    Motor.IqPID.Iout = 0;
                    Motor.IqPID.OutPut = 0;
                    Motor.IdPID.Iout = 0;
                    Motor.IdPID.OutPut = 0;
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
                switch (FOC_MODE)
                {		
                    case OPEN_LOOP:
                    {	
                        if(LED_Count%10000 == 0)
                        {
                            HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                        }
                        Motor.U_2r.Q = (float)(2*(int)ADC1_value[3]-4095)*0.0016919f;//1/4095.0f*6.9282f = 0.001691868131868;
                        Motor.U_2r.D = 0;
                        AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
                        SVPWM_120(&Motor.U_2s);
                        break;
                    }
                    case SPEED_CLOSE_LOOP:
                    {
                        if(LED_Count%5000 == 0)
                        {
                            HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                        }
                        Motor.FOC_Parameter.SpeedMachRef = (float)(2*(int)ADC1_value[3]-4095)*2;
                        PIDCalculate(&Motor.SpeedPID,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef);
                        Motor.U_2r.Q = Motor.SpeedPID.OutPut;
                        AntiPark(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
                        SVPWM(&Motor.U_2s);
                        break;
                    }

                    case SPEED_CURRENT_CLOSE_LOOP_FLUX_OBSERVER:
                    {
                        flux_observer(Motor.U_2s.Alpha,Motor.U_2s.Beta,Motor.I_2s.Alpha,Motor.I_2s.Beta,&observer);
                        Park(&Motor.I_2s,&Motor.I_2r,observer.theta);
                        if(LED_Count%2500 == 0)
                        {
                            HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                        }
                        Motor.FOC_Parameter.SpeedMachRef = ((float)ADC1_value[3]/4095.0f)*7300.0f;
                        //speed loop 
                        PIDCalculate(&Motor.SpeedPID,observer.Speed,Motor.FOC_Parameter.SpeedMachRef);
                        //current loop
                        PIDCalculate(&Motor.IqPID,Motor.I_2r.Q,Motor.SpeedPID.OutPut);
                        PIDCalculate(&Motor.IdPID,Motor.I_2r.D,0);
                        Motor.U_2r.Q = Motor.IqPID.OutPut;
                        Motor.U_2r.D = Motor.IdPID.OutPut;

                        AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,observer.theta);
                        SVPWM_120(&Motor.U_2s);
                        break;
                    }

                    case SPEED_CURRENT_CLOSE_LOOP_OVERMODU_FW:
                    {
                        if(LED_Count%1250 == 0)
                        {
                            HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                        }
                        HFSVI_Sensorless(&HFSVI,&Motor);
                        Motor.FOC_Parameter.SpeedMachRef = ((float)ADC1_value[3]/4095.0f)*7450.0f;
                        switch(FW_STATE)
                        {
                            case NO_FIELD_WEAKEN:
                            //speed loop
                            PIDCalculate(&Motor.SpeedPID,Motor.FOC_Parameter.SpeedMachReal,Motor.FOC_Parameter.SpeedMachRef);
                            //current loop
                            PIDCalculate(&Motor.IqPID,Motor.I_2r.Q,Motor.SpeedPID.OutPut);
                            PIDCalculate(&Motor.IdPID,Motor.I_2r.D,0);
                            Motor.U_2r.Q = Motor.IqPID.OutPut;
                            Motor.U_2r.D = Motor.IdPID.OutPut+HFSVI.Uh*HFSVI.singalUh;
                            
                            break;

                            case FIELD_WEAKEN:
                            flux_weaken();
                            break;

                            default: break;
                        }
                        AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,Motor.FOC_Parameter.AngleE_rad);
                        SVPWM_120(&Motor.U_2s);
                        
                        break;
                    }

                    case SPEED_CURRENT_CLOSE_LOOP_HFSVI:
                    {
                        static float IA[60] = {0};
                        static float IB[60] = {0};
                        if (Count <= 11062)
                        {
                            Count++;
                        }
                        if (Count <= 10000)  // beta axis positioning: Beta=3, Alpha=0
                        {
                            HFSVI_Sensorless(&HFSVI,&Motor);
                            Park(&Motor.I_2s,&Motor.I_2r,HFSVI.theta);
                            PIDCalculate(&Motor.IqPID,Motor.I_2r.Q,0);
                            PIDCalculate(&Motor.IdPID,Motor.I_2r.D,0);
                            Motor.U_2r.Q = Motor.IqPID.OutPut;
                            Motor.U_2r.D = Motor.IdPID.OutPut + HFSVI.Uh*HFSVI.singalUh;//injection
                            AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,HFSVI.theta);
                            SVPWM_120(&Motor.U_2s);
                        }
                        else if(Count >= 10000 && Count < 11000)
                        {
                            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Period/2);
                            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Period/2);
                            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Period/2);
                        }
                        else if(Count >= 11000&& Count <= 11060)
                        {
                            
                            if(Count >= 11000&& Count <= 11015)
                            {
                                Motor.U_2r.Q = 0;
                                Motor.U_2r.D = 7;//injection
                                AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,HFSVI.theta);
                                SVPWM_120(&Motor.U_2s);
                            }
                            else if(Count >= 11030&& Count <= 11045)
                            {
                                Motor.U_2r.Q = 0;
                                Motor.U_2r.D = 7;//injection
                                AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,HFSVI.theta+pi);
                                SVPWM_120(&Motor.U_2s);
                            }
                            else
                            {
                                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Period/2);
                                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Period/2);
                                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Period/2);
                            }
                            if(Count >= 11000&& Count <= 11060)
                            {
                                Park(&Motor.I_2s,&Motor.I_2r,HFSVI.theta);
                                // IA[Count-11000] = arm_abs_f32(Motor.I_2r.D);
                                // IB[Count-11000] = arm_abs_f32(Motor.I_2r.Q);
                                arm_abs_f32(&Motor.I_2r.D,&IA[Count-11000],1);
                                arm_abs_f32(&Motor.I_2r.Q,&IB[Count-11000],1);
                            }
                        }
                        else if (Count == 11061)
                        {
                            float max_value1 = 0;
                            uint32_t max_index1 = 0;
                            float max_value2 = 0;
                            uint32_t max_index2 = 0;
                            // float theta0 = 0;
                            // float theta1 = 0;
                            arm_max_f32(IA,30,&max_value1,&max_index1);
                            arm_max_f32(&IA[30],30,&max_value2,&max_index2);
                            // theta0 = HFSVI.theta;
                            if(max_value1 < max_value2)
                            {
                                HFSVI.theta = HFSVI.theta+pi;
                                if (HFSVI.theta > 2*pi)
                                {
                                    HFSVI.theta = HFSVI.theta - 2*pi;
                                }
                                else if (HFSVI.theta < 0)
                                {
                                    HFSVI.theta = HFSVI.theta + 2*pi;
                                }
                            }
                            // theta1 = HFSVI.theta;
                            Park(&Motor.I_2s,&Motor.I_2r,HFSVI.theta);
                            Motor.FOC_Parameter.SpeedMachRef = 1000;
                            //speed loop
                            PIDCalculate(&Motor.SpeedPID,HFSVI.Speed,Motor.FOC_Parameter.SpeedMachRef);
                            //current loop
                            PIDCalculate(&Motor.IqPID,Motor.I_2r.Q,Motor.SpeedPID.OutPut);
                            PIDCalculate(&Motor.IdPID,Motor.I_2r.D,0);
                            Motor.U_2r.Q = Motor.IqPID.OutPut;
                            Motor.U_2r.D = Motor.IdPID.OutPut + HFSVI.Uh*HFSVI.singalUh;//injection
                            AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,HFSVI.theta);
                            SVPWM_120(&Motor.U_2s);
                        }
                        else
                        {
                            HFSVI_Sensorless(&HFSVI,&Motor);
                            Park(&Motor.I_2s,&Motor.I_2r,HFSVI.theta);
                            if(LED_Count%625 == 0)
                            {
                                HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                            }
                            //Motor.FOC_Parameter.SpeedMachRef = ((float)ADC1_value[3]/4095.0f)*7300.0f;
                            Motor.FOC_Parameter.SpeedMachRef = -2000;
                            //speed loop
                            PIDCalculate(&Motor.SpeedPID,HFSVI.Speed,Motor.FOC_Parameter.SpeedMachRef);
                            //current loop
                            PIDCalculate(&Motor.IqPID,Motor.I_2r.Q,Motor.SpeedPID.OutPut);
                            PIDCalculate(&Motor.IdPID,Motor.I_2r.D,0);
                            Motor.U_2r.Q = Motor.IqPID.OutPut;
                            Motor.U_2r.D = Motor.IdPID.OutPut + HFSVI.Uh*HFSVI.singalUh;//injection
                            AntiPark_Overmodulation(&Motor.U_2s,&Motor.U_2r,HFSVI.theta);
                            SVPWM_120(&Motor.U_2s);
                        }
                        break;
                    }
                    default:PWM_Stop();break;
                }
                break;
            }

            case WARNING_STATE:
            {
                //protection state,turn on the LED
                PWM_Stop();
                HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
                break;
            }
            default:PWM_Stop();break;
        }
     }
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
     if(SYSTEM_STATE == FOC_RUN)
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
                FOC_MODE  ++;
                PWM_Start();
                if(FOC_MODE > 4 )//HFSVI mode is not available
                {
                    FOC_MODE =  IDIE_STATE;
                }
                switch(FOC_MODE)
                {
                    case IDIE_STATE:
                        PWM_Stop();
                        HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
                        break;
                    case SPEED_CLOSE_LOOP:
                    {
                        Motor.SpeedPID.Kp = 1.0E-3f;
                        Motor.SpeedPID.Ki = 1.0E-2f;
                        Motor.SpeedPID.MaxOut = 6.914319;   //6.914319 is the most voltage of linear modulation space
                        Motor.SpeedPID.IntegralLimit = 6.914319;
                        // Motor.SpeedPI.Kp = 1.0E-3f;
                        // Motor.SpeedPI.Ki = 1.0E-6f;
                        break;
                    }
                    case SPEED_CURRENT_CLOSE_LOOP_FLUX_OBSERVER:
                    {
                        Non_flux_Init(&observer);
                        Motor.SpeedPID.Kp = 1.0E-4F;
                        Motor.SpeedPID.Ki = 2.0E-3F;
                        Motor.SpeedPID.MaxOut = 10;
                        Motor.SpeedPID.IntegralLimit = 10;

                        Motor.IqPID.Kp = 1.0F;
                        Motor.IqPID.Ki = 0.01F;
                        Motor.IqPID.MaxOut = 6.914319;
                        Motor.IqPID.IntegralLimit = 6.914319;

                        Motor.IdPID.Kp = 0.0001F;
                        Motor.IdPID.Ki = 0.01F;
                        Motor.IdPID.MaxOut = 6.914319;
                        Motor.IdPID.IntegralLimit = 6.914319;
                        break;
                    }
                    case SPEED_CURRENT_CLOSE_LOOP_OVERMODU_FW:
                    {
                        HFSVI_Sensorless_Init(&HFSVI);
                        Motor.SpeedPID.Kp = 1.0E-4F;
                        Motor.SpeedPID.Ki = 2.0E-3F;
                        Motor.SpeedPID.MaxOut = 50;
                        Motor.SpeedPID.IntegralLimit = 50;

                        Motor.IqPID.Kp = 1.0F;
                        Motor.IqPID.Ki = 0.01F;
                        Motor.IqPID.MaxOut = threshold;
                        Motor.IqPID.IntegralLimit = threshold;

                        Motor.IdPID.Kp = 0.0001F;
                        Motor.IdPID.Ki = 0.01F;
                        Motor.IdPID.MaxOut = threshold;
                        Motor.IdPID.IntegralLimit = threshold;
                        break;
                    }
                    case SPEED_CURRENT_CLOSE_LOOP_HFSVI:
                    {
                        HFSVI_Sensorless_Init(&HFSVI);
                        HFSVI.PLL.Kp = 200;
                        HFSVI.PLL.Ki = 50000;
                        HFSVI.Uh = 1;
                        Motor.SpeedPID.Kp = 2.0E-2F;
                        Motor.SpeedPID.Ki = 1.0E-3F;
                        Motor.SpeedPID.MaxOut = 10;
                        Motor.SpeedPID.IntegralLimit = 10;

                        Motor.IqPID.Kp = 0.001F;
                        Motor.IqPID.Ki = 0.01F;
                        Motor.IqPID.MaxOut = threshold;
                        Motor.IqPID.IntegralLimit = threshold;

                        Motor.IdPID.Kp = 0.001F;
                        Motor.IdPID.Ki = 0.05F;
                        Motor.IdPID.MaxOut = threshold;
                        Motor.IdPID.IntegralLimit = threshold;
                        break;
                    }
                    default:break;
                }
                Motor.U_2r.Q = 0;
                Motor.U_2r.D = 0;
                Motor.U_2s.Alpha = 0;
                Motor.U_2s.Beta = 0;
                Motor.SpeedPID.Iout = 0;
                Motor.SpeedPID.OutPut = 0;
                Motor.IqPID.Iout = 0;
                Motor.IqPID.OutPut = 0;
                Motor.IdPID.Iout = 0;
                Motor.IdPID.OutPut = 0;
            }
            else//if long pressed,start parameter indentification
            {
                SYSTEM_STATE = RS_IDENTIFY_VOLTAGE_DESIGM;
                Motor.Motor_Parameter.Pd = 1e5;
                Motor.Motor_Parameter.Pq = 1e5;
                Motor.Motor_Parameter.Pj = 1e5;
                Motor.Motor_Parameter.u = 0.99;
                Motor.Motor_Parameter.Ts_Ld = 1;
                Motor.Motor_Parameter.Ts_Lq = 1;
                FOC_MODE = IDIE_STATE;
                HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
                PWM_Start();
            }
         }
     }
 }
 
 
 