#include "offline_pi.h"
#include "foc.h"
#include <math.h>
#include <string.h>

float Rs_calculate(float *I, float *U) {
    float numerator = 0.0;
    float denominator = 0.0;

    // Precompute repeated calculations to optimize performance
    float I0_squared = pow(fabs(I[0]), 2);
    float I1_squared = pow(fabs(I[1]), 2);
    float I2_squared = pow(fabs(I[2]), 2);
    float I3_squared = pow(fabs(I[3]), 2);
    float I4_squared = pow(fabs(I[4]), 2);

    float term0 = I0_squared / I[0];
    float term1 = I1_squared / I[1];
    float term2 = I2_squared / I[2];
    float term3 = I3_squared / I[3];
    float term4 = I4_squared / I[4];

    // Numerator calculation
    numerator += (U[1] * term0) - (4 * U[0] * term0);
    numerator += (U[2] * term0) + (U[0] * term1);
    numerator += (U[3] * term0) - (4 * U[1] * term1);
    numerator += (U[4] * term0) + (U[2] * term1);
    numerator += (U[0] * term2) + (U[3] * term1);
    numerator += (U[1] * term2) + (U[4] * term1);
    numerator += -4 * U[2] * term2 + (U[0] * term3);
    numerator += (U[3] * term2) + (U[1] * term3);
    numerator += (U[4] * term2) + (U[2] * term3);
    numerator += (U[0] * term4) - (4 * U[3] * term3);
    numerator += (U[1] * term4) + (U[4] * term3);
    numerator += (U[2] * term4) + (U[3] * term4);
    numerator += -4 * U[4] * term4;

    // Denominator calculation
    denominator += (I[1] * term0) - 4 * I1_squared - 4 * I2_squared;
    denominator += -4 * I3_squared - 4 * I4_squared - 4 * I0_squared;
    denominator += (I[0] * term1) + (I[2] * term0);
    denominator += (I[3] * term0) + (I[0] * term2);
    denominator += (I[4] * term0) + (I[2] * term1);
    denominator += (I[1] * term2) + (I[3] * term1);
    denominator += (I[0] * term3) + (I[4] * term1);
    denominator += (I[1] * term3) + (I[3] * term2);
    denominator += (I[0] * term4) + (I[2] * term3);
    denominator += (I[4] * term2) + (I[1] * term4);
    denominator += (I[2] * term4) + (I[4] * term3);
    denominator += (I[3] * term4);

    return numerator / denominator;
}

void Flash_Write_PartialStruct(Motor_P *data)
{
    HAL_FLASH_Unlock();  // Unlock Flash

    // Write  Flash
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Page = (FLASH_PAGE_ADDR - 0x08000000) / 2048;
    EraseInitStruct.NbPages = 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
    {
        HAL_FLASH_Lock();
        return;
    }

    uint64_t *data64 = (uint64_t*)data;
    for (uint32_t i = 0; i < (24 / 8); i++) 
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_PAGE_ADDR + (i * 8), data64[i]);
    }

    HAL_FLASH_Lock();  // lock Flash
}
void Flash_Read_PartialStruct(Motor_P *data)
{
    memcpy(data, (void*)FLASH_PAGE_ADDR, 24);
}


