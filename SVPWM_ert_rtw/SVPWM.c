/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SVPWM.c
 *
 * Code generated for Simulink model 'SVPWM'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Mar  6 18:28:19 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "SVPWM.h"
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void SVPWM_step(void)
{
  int32_T rtb_N_calculator;
  real32_T rtb_MultiportSwitch;
  real32_T rtb_MultiportSwitch1;
  real32_T rtb_Switch;
  real32_T rtb_Switch_tmp;

  /* Fcn: '<S2>/N_calculator' incorporates:
   *  Fcn: '<S2>/Uref2'
   *  Fcn: '<S2>/Uref3'
   *  Inport: '<Root>/alpha'
   *  Inport: '<Root>/beta'
   *  Switch: '<S2>/A'
   *  Switch: '<S2>/B'
   *  Switch: '<S2>/C'
   */
  rtb_N_calculator = (((1.73205078F * rtU.alpha - rtU.beta) / 2.0F > 0.0F) *
                      (int32_T)2.0 + (rtU.beta > 0.0F)) + ((-rtU.beta -
    1.73205078F * rtU.alpha) / 2.0F > 0.0F) * (int32_T)4.0;

  /* MultiPortSwitch: '<S3>/Multiport Switch' incorporates:
   *  Fcn: '<S5>/X_Calculator'
   *  Fcn: '<S5>/Y_Calculator'
   *  Fcn: '<S5>/Z_Calculator'
   *  Gain: '<S3>/Gain'
   *  Gain: '<S3>/Gain1'
   *  Gain: '<S3>/Gain2'
   *  Inport: '<Root>/Period'
   *  Inport: '<Root>/Udc'
   *  Inport: '<Root>/alpha'
   *  Inport: '<Root>/beta'
   */
  switch (rtb_N_calculator) {
   case 1:
    rtb_MultiportSwitch = (-0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc;

    /* MultiPortSwitch: '<S3>/Multiport Switch1' incorporates:
     *  Fcn: '<S5>/Y_Calculator'
     *  Fcn: '<S5>/Z_Calculator'
     *  Inport: '<Root>/Period'
     *  Inport: '<Root>/Udc'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/beta'
     */
    rtb_MultiportSwitch1 = (0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc;
    break;

   case 2:
    rtb_MultiportSwitch = (0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc;

    /* MultiPortSwitch: '<S3>/Multiport Switch1' incorporates:
     *  Fcn: '<S5>/X_Calculator'
     *  Fcn: '<S5>/Y_Calculator'
     *  Gain: '<S3>/Gain'
     *  Inport: '<Root>/Period'
     *  Inport: '<Root>/Udc'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/beta'
     */
    rtb_MultiportSwitch1 = -(1.73205078F * rtU.beta * rtU.Period / rtU.Udc);
    break;

   case 3:
    rtb_MultiportSwitch = -((-0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc);

    /* MultiPortSwitch: '<S3>/Multiport Switch1' incorporates:
     *  Fcn: '<S5>/X_Calculator'
     *  Fcn: '<S5>/Z_Calculator'
     *  Gain: '<S3>/Gain2'
     *  Inport: '<Root>/Period'
     *  Inport: '<Root>/Udc'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/beta'
     */
    rtb_MultiportSwitch1 = 1.73205078F * rtU.beta * rtU.Period / rtU.Udc;
    break;

   case 4:
    rtb_MultiportSwitch = -(1.73205078F * rtU.beta * rtU.Period / rtU.Udc);

    /* MultiPortSwitch: '<S3>/Multiport Switch1' incorporates:
     *  Fcn: '<S5>/X_Calculator'
     *  Fcn: '<S5>/Z_Calculator'
     *  Gain: '<S3>/Gain'
     *  Inport: '<Root>/Period'
     *  Inport: '<Root>/Udc'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/beta'
     */
    rtb_MultiportSwitch1 = (-0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc;
    break;

   case 5:
    rtb_MultiportSwitch = 1.73205078F * rtU.beta * rtU.Period / rtU.Udc;

    /* MultiPortSwitch: '<S3>/Multiport Switch1' incorporates:
     *  Fcn: '<S5>/X_Calculator'
     *  Fcn: '<S5>/Y_Calculator'
     *  Gain: '<S3>/Gain1'
     *  Inport: '<Root>/Period'
     *  Inport: '<Root>/Udc'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/beta'
     */
    rtb_MultiportSwitch1 = -((0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc);
    break;

   default:
    rtb_MultiportSwitch = -((0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc);

    /* MultiPortSwitch: '<S3>/Multiport Switch1' incorporates:
     *  Fcn: '<S5>/Y_Calculator'
     *  Fcn: '<S5>/Z_Calculator'
     *  Gain: '<S3>/Gain1'
     *  Gain: '<S3>/Gain2'
     *  Inport: '<Root>/Period'
     *  Inport: '<Root>/Udc'
     *  Inport: '<Root>/alpha'
     *  Inport: '<Root>/beta'
     */
    rtb_MultiportSwitch1 = -((-0.866025388F * rtU.alpha + 0.5F * rtU.beta) *
      (1.73205078F * rtU.Period) / rtU.Udc);
    break;
  }

  /* End of MultiPortSwitch: '<S3>/Multiport Switch' */

  /* Switch: '<S3>/Switch' incorporates:
   *  Fcn: '<S3>/T1_Calculator'
   *  Fcn: '<S3>/T2_Calculator'
   *  Fcn: '<S3>/T_Calculator'
   *  Inport: '<Root>/Period'
   *  Switch: '<S3>/Switch1'
   */
  if ((rtU.Period - rtb_MultiportSwitch) - rtb_MultiportSwitch1 > 0.0F) {
    rtb_Switch = rtb_MultiportSwitch;
  } else {
    /* Fcn: '<S3>/T1_Calculator' incorporates:
     *  Fcn: '<S3>/T2_Calculator'
     */
    rtb_Switch_tmp = rtb_MultiportSwitch + rtb_MultiportSwitch1;
    rtb_Switch = rtb_MultiportSwitch * rtU.Period / rtb_Switch_tmp;
    rtb_MultiportSwitch1 = rtb_MultiportSwitch1 * rtU.Period / rtb_Switch_tmp;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Sum: '<S4>/Tb' incorporates:
   *  Inport: '<Root>/Period'
   *  Sum: '<S4>/Tc'
   */
  rtb_Switch_tmp = rtU.Period + rtb_Switch;

  /* Gain: '<S4>/Gain1' incorporates:
   *  Sum: '<S4>/Tb'
   */
  rtb_MultiportSwitch = (rtb_Switch_tmp - rtb_MultiportSwitch1) * 0.25F;

  /* Gain: '<S4>/Gain' incorporates:
   *  Inport: '<Root>/Period'
   *  Sum: '<S4>/Ta'
   */
  rtb_Switch = ((rtU.Period - rtb_Switch) - rtb_MultiportSwitch1) * 0.25F;

  /* Gain: '<S4>/Gain2' incorporates:
   *  Sum: '<S4>/Tc'
   */
  rtb_MultiportSwitch1 = (rtb_Switch_tmp + rtb_MultiportSwitch1) * 0.25F;

  /* MultiPortSwitch: '<S4>/1' */
  switch (rtb_N_calculator) {
   case 1:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S4>/2'
     */
    rtY.Tcm2 = rtb_Switch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S4>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch1;
    break;

   case 2:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_Switch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S4>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S4>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch;
    break;

   case 3:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_Switch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S4>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S4>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch1;
    break;

   case 4:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S4>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S4>/3'
     */
    rtY.Tcm3 = rtb_Switch;
    break;

   case 5:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S4>/2'
     */
    rtY.Tcm2 = rtb_Switch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S4>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch;
    break;

   default:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S4>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S4>/3'
     */
    rtY.Tcm3 = rtb_Switch;
    break;
  }

  /* End of MultiPortSwitch: '<S4>/1' */
}

/* Model initialize function */
void SVPWM_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
