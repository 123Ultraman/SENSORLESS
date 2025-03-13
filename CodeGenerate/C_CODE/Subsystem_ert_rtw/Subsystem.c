/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.c
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Mar  7 15:14:37 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Subsystem.h"
#include <math.h>
#include "rtwtypes.h"

/* Exported block parameters */
real_T Udc = 300.0;                    /* Variable: Udc
                                        * Referenced by: '<S1>/Constant10'
                                        */

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void Subsystem_step(void)
{
  real_T rtb_A;
  real_T rtb_Fcn1;
  real_T rtb_Integrator_l_tmp;
  real_T rtb_Integrator_m;
  real_T rtb_MultiportSwitch;
  real_T rtb_N_calculator;
  real_T rtb_Sum3;
  real_T rtb_Sum4;
  real_T rtb_Sum7;
  real_T rtb_Tsamp;

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain3'
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In2'
   */
  rtb_Sum3 = rtU.In1 - 1.0 / Pn * rtU.Theta * 9.5492965855137211;

  /* SampleTimeMath: '<S144>/Tsamp' incorporates:
   *  Gain: '<S140>/Derivative Gain'
   *
   * About '<S144>/Tsamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Tsamp = 0.001 * rtb_Sum3 * 10000.0;

  /* Fcn: '<S3>/Fcn' incorporates:
   *  Inport: '<Root>/ias'
   *  Inport: '<Root>/ibs'
   *  Inport: '<Root>/ics'
   */
  rtb_Sum7 = ((rtU.ias - 0.5 * rtU.ibs) - 0.5 * rtU.ics) * 2.0 / 3.0;

  /* Fcn: '<S3>/Fcn1' incorporates:
   *  Inport: '<Root>/ibs'
   *  Inport: '<Root>/ics'
   */
  rtb_Integrator_m = (0.8660254037844386 * rtU.ibs - 0.8660254037844386 *
                      rtU.ics) * 2.0 / 3.0;

  /* Fcn: '<S6>/Fcn1' incorporates:
   *  Fcn: '<S2>/Fcn'
   *  Fcn: '<S2>/Fcn1'
   *  Fcn: '<S6>/Fcn'
   *  Inport: '<Root>/The'
   */
  rtb_N_calculator = cos(rtU.Theta_b);
  rtb_MultiportSwitch = sin(rtU.Theta_b);

  /* Sum: '<S158>/Sum' incorporates:
   *  Delay: '<S142>/UD'
   *  DiscreteIntegrator: '<S149>/Integrator'
   *  Gain: '<S154>/Proportional Gain'
   *  Sum: '<S142>/Diff'
   */
  rtb_Sum4 = (0.1 * rtb_Sum3 + rtDW.Integrator_DSTATE) + (rtb_Tsamp -
    rtDW.UD_DSTATE);

  /* Saturate: '<S156>/Saturation' */
  if (rtb_Sum4 > 500.0) {
    rtb_Sum4 = 500.0;
  } else if (rtb_Sum4 < -500.0) {
    rtb_Sum4 = -500.0;
  }

  /* Sum: '<S1>/Sum4' incorporates:
   *  Fcn: '<S6>/Fcn1'
   *  Saturate: '<S156>/Saturation'
   */
  rtb_Sum4 -= -rtb_MultiportSwitch * rtb_Sum7 + rtb_N_calculator *
    rtb_Integrator_m;

  /* Sum: '<S104>/Sum' incorporates:
   *  DiscreteIntegrator: '<S95>/Integrator'
   *  Gain: '<S100>/Proportional Gain'
   */
  rtb_Fcn1 = 3.8947 * rtb_Sum4 + rtDW.Integrator_DSTATE_a;

  /* Saturate: '<S102>/Saturation' */
  if (rtb_Fcn1 > 50.0) {
    rtb_Fcn1 = 50.0;
  } else if (rtb_Fcn1 < -50.0) {
    rtb_Fcn1 = -50.0;
  }

  /* End of Saturate: '<S102>/Saturation' */

  /* Sum: '<S1>/Sum7' incorporates:
   *  Constant: '<S1>/Id_ref'
   *  Fcn: '<S6>/Fcn'
   */
  rtb_Sum7 = 0.0 - (rtb_N_calculator * rtb_Sum7 + rtb_MultiportSwitch *
                    rtb_Integrator_m);

  /* Sum: '<S52>/Sum' incorporates:
   *  DiscreteIntegrator: '<S43>/Integrator'
   *  Gain: '<S48>/Proportional Gain'
   */
  rtb_A = 4.3057 * rtb_Sum7 + rtDW.Integrator_DSTATE_k;

  /* Saturate: '<S50>/Saturation' */
  if (rtb_A > 50.0) {
    rtb_A = 50.0;
  } else if (rtb_A < -50.0) {
    rtb_A = -50.0;
  }

  /* End of Saturate: '<S50>/Saturation' */

  /* Fcn: '<S2>/Fcn' */
  rtb_Integrator_m = rtb_N_calculator * rtb_A - rtb_MultiportSwitch * rtb_Fcn1;

  /* Fcn: '<S2>/Fcn1' */
  rtb_Fcn1 = rtb_MultiportSwitch * rtb_A + rtb_N_calculator * rtb_Fcn1;

  /* Fcn: '<S167>/N_calculator' incorporates:
   *  Fcn: '<S167>/Uref1'
   *  Fcn: '<S167>/Uref2'
   *  Fcn: '<S167>/Uref3'
   *  Switch: '<S167>/A'
   *  Switch: '<S167>/B'
   *  Switch: '<S167>/C'
   */
  rtb_N_calculator = (((1.7320508075688772 * rtb_Integrator_m - rtb_Fcn1) / 2.0 >
                       0.0) * (int32_T)2.0 + (rtb_Fcn1 > 0.0)) + ((-rtb_Fcn1 -
    1.7320508075688772 * rtb_Integrator_m) / 2.0 > 0.0) * (int32_T)4.0;

  /* MultiPortSwitch: '<S168>/Multiport Switch' incorporates:
   *  Constant: '<S1>/Constant10'
   *  Constant: '<S1>/Constant9'
   *  Fcn: '<S170>/X_Calculator'
   *  Fcn: '<S170>/Y_Calculator'
   *  Fcn: '<S170>/Z_Calculator'
   *  Gain: '<S168>/Gain'
   *  Gain: '<S168>/Gain1'
   *  Gain: '<S168>/Gain2'
   */
  switch ((int32_T)rtb_N_calculator) {
   case 1:
    rtb_MultiportSwitch = (-0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_Fcn1) * (1.7320508075688772 * Period) / Udc;

    /* MultiPortSwitch: '<S168>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S170>/Y_Calculator'
     *  Fcn: '<S170>/Z_Calculator'
     */
    rtb_A = (0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_Fcn1) *
      (1.7320508075688772 * Period) / Udc;
    break;

   case 2:
    rtb_MultiportSwitch = (0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_Fcn1) * (1.7320508075688772 * Period) / Udc;

    /* MultiPortSwitch: '<S168>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S170>/X_Calculator'
     *  Fcn: '<S170>/Y_Calculator'
     *  Gain: '<S168>/Gain'
     */
    rtb_A = -(1.7320508075688772 * rtb_Fcn1 * Period / Udc);
    break;

   case 3:
    rtb_MultiportSwitch = -((-0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_Fcn1) * (1.7320508075688772 * Period) / Udc);

    /* MultiPortSwitch: '<S168>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S170>/X_Calculator'
     *  Fcn: '<S170>/Z_Calculator'
     *  Gain: '<S168>/Gain2'
     */
    rtb_A = 1.7320508075688772 * rtb_Fcn1 * Period / Udc;
    break;

   case 4:
    rtb_MultiportSwitch = -(1.7320508075688772 * rtb_Fcn1 * Period / Udc);

    /* MultiPortSwitch: '<S168>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S170>/X_Calculator'
     *  Fcn: '<S170>/Z_Calculator'
     *  Gain: '<S168>/Gain'
     */
    rtb_A = (-0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_Fcn1) *
      (1.7320508075688772 * Period) / Udc;
    break;

   case 5:
    rtb_MultiportSwitch = 1.7320508075688772 * rtb_Fcn1 * Period / Udc;

    /* MultiPortSwitch: '<S168>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S170>/X_Calculator'
     *  Fcn: '<S170>/Y_Calculator'
     *  Gain: '<S168>/Gain1'
     */
    rtb_A = -((0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_Fcn1) *
              (1.7320508075688772 * Period) / Udc);
    break;

   default:
    rtb_MultiportSwitch = -((0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_Fcn1) * (1.7320508075688772 * Period) / Udc);

    /* MultiPortSwitch: '<S168>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S170>/Y_Calculator'
     *  Fcn: '<S170>/Z_Calculator'
     *  Gain: '<S168>/Gain1'
     *  Gain: '<S168>/Gain2'
     */
    rtb_A = -((-0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_Fcn1) *
              (1.7320508075688772 * Period) / Udc);
    break;
  }

  /* End of MultiPortSwitch: '<S168>/Multiport Switch' */

  /* Switch: '<S168>/Switch' incorporates:
   *  Constant: '<S1>/Constant9'
   *  Fcn: '<S168>/T1_Calculator'
   *  Fcn: '<S168>/T2_Calculator'
   *  Fcn: '<S168>/T_Calculator'
   *  Switch: '<S168>/Switch1'
   */
  if ((Period - rtb_MultiportSwitch) - rtb_A > 0.0) {
    rtb_Fcn1 = rtb_MultiportSwitch;
  } else {
    /* Fcn: '<S168>/T1_Calculator' incorporates:
     *  Fcn: '<S168>/T2_Calculator'
     */
    rtb_Integrator_m = rtb_MultiportSwitch + rtb_A;
    rtb_Fcn1 = rtb_MultiportSwitch * Period / rtb_Integrator_m;
    rtb_A = rtb_A * Period / rtb_Integrator_m;
  }

  /* End of Switch: '<S168>/Switch' */

  /* Sum: '<S169>/Tb' incorporates:
   *  Constant: '<S1>/Constant9'
   *  Sum: '<S169>/Tc'
   */
  rtb_Integrator_l_tmp = Period + rtb_Fcn1;

  /* Gain: '<S169>/Gain1' incorporates:
   *  Sum: '<S169>/Tb'
   */
  rtb_Integrator_m = (rtb_Integrator_l_tmp - rtb_A) * 0.25;

  /* Gain: '<S169>/Gain' incorporates:
   *  Constant: '<S1>/Constant9'
   *  Sum: '<S169>/Ta'
   */
  rtb_MultiportSwitch = ((Period - rtb_Fcn1) - rtb_A) * 0.25;

  /* Gain: '<S169>/Gain2' incorporates:
   *  Sum: '<S169>/Tc'
   */
  rtb_A = (rtb_Integrator_l_tmp + rtb_A) * 0.25;

  /* MultiPortSwitch: '<S169>/1' */
  switch ((int32_T)rtb_N_calculator) {
   case 1:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_Integrator_m;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S169>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S169>/3'
     */
    rtY.Tcm3 = rtb_A;
    break;

   case 2:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S169>/2'
     */
    rtY.Tcm2 = rtb_A;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S169>/3'
     */
    rtY.Tcm3 = rtb_Integrator_m;
    break;

   case 3:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S169>/2'
     */
    rtY.Tcm2 = rtb_Integrator_m;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S169>/3'
     */
    rtY.Tcm3 = rtb_A;
    break;

   case 4:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_A;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S169>/2'
     */
    rtY.Tcm2 = rtb_Integrator_m;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S169>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch;
    break;

   case 5:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_A;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S169>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S169>/3'
     */
    rtY.Tcm3 = rtb_Integrator_m;
    break;

   default:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_Integrator_m;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S169>/2'
     */
    rtY.Tcm2 = rtb_A;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S169>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch;
    break;
  }

  /* End of MultiPortSwitch: '<S169>/1' */

  /* Update for DiscreteIntegrator: '<S149>/Integrator' incorporates:
   *  Gain: '<S146>/Integral Gain'
   */
  rtDW.Integrator_DSTATE += 50.0 * rtb_Sum3 * 0.0001;
  if (rtDW.Integrator_DSTATE > 500.0) {
    rtDW.Integrator_DSTATE = 500.0;
  } else if (rtDW.Integrator_DSTATE < -500.0) {
    rtDW.Integrator_DSTATE = -500.0;
  }

  /* End of Update for DiscreteIntegrator: '<S149>/Integrator' */

  /* Update for Delay: '<S142>/UD' */
  rtDW.UD_DSTATE = rtb_Tsamp;

  /* Update for DiscreteIntegrator: '<S95>/Integrator' incorporates:
   *  Gain: '<S92>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_a += 100.0 * rtb_Sum4 * 0.0001;
  if (rtDW.Integrator_DSTATE_a > 100.0) {
    rtDW.Integrator_DSTATE_a = 100.0;
  } else if (rtDW.Integrator_DSTATE_a < -100.0) {
    rtDW.Integrator_DSTATE_a = -100.0;
  }

  /* End of Update for DiscreteIntegrator: '<S95>/Integrator' */

  /* Update for DiscreteIntegrator: '<S43>/Integrator' incorporates:
   *  Gain: '<S40>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_k += 100.0 * rtb_Sum7 * 0.0001;
  if (rtDW.Integrator_DSTATE_k > 100.0) {
    rtDW.Integrator_DSTATE_k = 100.0;
  } else if (rtDW.Integrator_DSTATE_k < -100.0) {
    rtDW.Integrator_DSTATE_k = -100.0;
  }

  /* End of Update for DiscreteIntegrator: '<S43>/Integrator' */
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
