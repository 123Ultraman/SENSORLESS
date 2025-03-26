
/******************************************************************************
 * @file     fast_math_functions.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.10.0
 * @date     08 July 2021
 * Target Processor: Cortex-M and Cortex-A cores
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 
#ifndef FAST_MATH_FUNCTIONS_H_
#define FAST_MATH_FUNCTIONS_H_

//#include "arm_math_types.h"
//#include "arm_math_memory.h"

//#include "none.h"
//#include "utils.h"

//#include "basic_math_functions.h"

//#include <math.h>

#ifdef   __cplusplus
extern "C"
{
#endif

  /**
   * @brief Macros required for SINE and COSINE Fast math approximations
   */

#define FAST_MATH_TABLE_SIZE  512
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
  
#ifndef PI
  #define PI               3.14159265358979f
#endif

#ifndef PI_F64 
  #define PI_F64 3.14159265358979323846
#endif



  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result
     @return  error status.
   */
  arm_status arm_atan2_f32(float32_t y,float32_t x,float32_t *result);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FAST_MATH_FUNCTIONS_H_ */
