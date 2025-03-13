/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Anti_Park.c
 *
 * Code generated for Simulink model 'Anti_Park'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Mar  6 20:17:20 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Anti_Park.h"
#include <math.h>
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void Anti_Park_step(void)
{
  real_T U_alpha_tmp;
  real_T U_alpha_tmp_0;

  /* Fcn: '<S1>/Fcn' incorporates:
   *  Fcn: '<S1>/Fcn1'
   *  Inport: '<Root>/The'
   */
  U_alpha_tmp = sin(rtU.The);
  U_alpha_tmp_0 = cos(rtU.The);

  /* Outport: '<Root>/U_alpha' incorporates:
   *  Fcn: '<S1>/Fcn'
   *  Inport: '<Root>/Uq'
   *  Inport: '<Root>/Vd'
   */
  rtY.U_alpha = U_alpha_tmp_0 * rtU.Vd - U_alpha_tmp * rtU.Uq;

  /* Outport: '<Root>/U_beta' incorporates:
   *  Fcn: '<S1>/Fcn1'
   *  Inport: '<Root>/Uq'
   *  Inport: '<Root>/Vd'
   */
  rtY.U_beta = U_alpha_tmp * rtU.Vd + U_alpha_tmp_0 * rtU.Uq;
}

/* Model initialize function */
void Anti_Park_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
