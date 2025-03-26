#ifndef __OFFLINE_PI_H__
#define __OFFLINE_PI_H__
#include "foc.h"
extern UI_2s U_2s ;
float Rs_calculate(float *I, float *U);
void Flash_Write_PartialStruct(Motor_P *data);
void Flash_Read_PartialStruct(Motor_P *data);
#endif
