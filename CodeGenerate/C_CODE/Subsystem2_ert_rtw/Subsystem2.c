/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem2.c
 *
 * Code generated for Simulink model 'Subsystem2'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Mar  6 22:00:29 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Subsystem2.h"
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
void Subsystem2_step(void)
{
  real_T I_q_tmp;
  real_T I_q_tmp_0;
  real_T rtb_Fcn;
  real_T rtb_Fcn1;

  /* Fcn: '<S2>/Fcn' incorporates:
   *  Inport: '<Root>/Ia'
   *  Inport: '<Root>/Ib'
   *  Inport: '<Root>/Ic'
   */
  rtb_Fcn = ((rtU.Ia - 0.5 * rtU.Ib) - 0.5 * rtU.Ic) * 2.0 / 3.0;

  /* Fcn: '<S2>/Fcn1' incorporates:
   *  Inport: '<Root>/Ib'
   *  Inport: '<Root>/Ic'
   */
  rtb_Fcn1 = (0.8660254037844386 * rtU.Ib - 0.8660254037844386 * rtU.Ic) * 2.0 /
    3.0;

  /* Fcn: '<S3>/Fcn1' incorporates:
   *  Fcn: '<S3>/Fcn'
   *  Inport: '<Root>/The'
   */
  I_q_tmp = cos(rtU.The);
  I_q_tmp_0 = sin(rtU.The);

  /* Outport: '<Root>/I_q' incorporates:
   *  Fcn: '<S3>/Fcn1'
   */
  rtY.I_q = -I_q_tmp_0 * rtb_Fcn + I_q_tmp * rtb_Fcn1;

  /* Outport: '<Root>/I_d' incorporates:
   *  Fcn: '<S3>/Fcn'
   */
  rtY.I_d = I_q_tmp * rtb_Fcn + I_q_tmp_0 * rtb_Fcn1;
}

/* Model initialize function */
void Subsystem2_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
