#ifndef OBSERVE_H
#define OBSERVE_H

#include "stdint.h"
typedef struct PLL_VESC
{
    float err;
    float Kp;
    float Ki;
    float iterm;
    float Out;
}PLL_VESC;

typedef struct VESC_Observer
{
    float x1_hat;
    float x2_hat;
    float x1_hat_pre;
    float x2_hat_pre;
    float Gain;
    float err;
    float dt;
    uint32_t DWT_CNT;
    float cos_theta;
    float sin_theta;
    float theta;
    float theta_pre;
		float Last_theta;
		float Speed;
		float Speed_pre;
		float ud;
		float uq;
    float filtered_PLL_Out;
    float theta_atan2;
    float previous_theta;
    float omega ;
    PLL_VESC PLL;
} VESC_Observer;

//检查浮点数是否为非数值或者无穷大
#define UTILS_IS_INF(x) ((x) == (1.0 / 0.0) || (x) == (-1.0 / 0.0))
#define UTILS_IS_NAN(x) ((x) != (x)) // 判断是否为非数值
#define UTILS_NAN_ZERO(x) (x = UTILS_IS_NAN(x) ? 0.0f : x)
// 求平方
#define SQ(x) ((x) * (x))

extern VESC_Observer observer;
float utils_fast_atan2(float y, float x);
int utils_truncate_number_abs(float *number, float max);
void Non_flux_Init(VESC_Observer *observer);
void flux_observer(float V_alpha, float V_beta, float i_alpha, float i_beta, VESC_Observer *observer);
#endif