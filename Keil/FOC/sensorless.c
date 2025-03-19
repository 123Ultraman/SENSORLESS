#include "sensorless.h"
#include "foc.h"
#include "arm_common_tables.h"
#include "arm_math.h"

VESC_Observer observer;

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

//非线性磁链观测器

void Non_flux_Init(VESC_Observer *observer)
{
    observer->Gain = 300000;//50000000;
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
    float y1, y2,n1,n2,d_theta;
    y1 = -RS * i_alpha + V_alpha;
    y2 = -RS * i_beta + V_beta;

    n1 = observer->x1_hat_pre - LS * i_alpha;
    n2 = observer->x2_hat_pre - LS * i_beta;

    observer->err = SQ(PHI) - (SQ(n1) + SQ(n2));
    
//    if(observer->err>0.0)
//        observer->err=0.0f;

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
    
    //锁相环
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


