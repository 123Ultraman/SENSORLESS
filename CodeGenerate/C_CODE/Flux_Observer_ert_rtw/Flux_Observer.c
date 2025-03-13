/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flux_Observer.c
 *
 * Code generated for Simulink model 'Flux_Observer'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Mar 13 15:15:06 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Flux_Observer.h"
#include <math.h>
#include "rtwtypes.h"
#include <float.h>
#include "math.h"

/* Exported block signals */
real32_T cos_theta;                    /* '<S10>/Gain8' */
real32_T sin_theta;                    /* '<S10>/Gain9' */

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_modd_snf(real_T u0, real_T u1);
static uint32_T plook_evenc(real_T u, real_T bp0, real_T bpSpace, uint32_T
  maxIndex, real_T *fraction);
static real_T intrp1d_l(uint32_T bpIndex, real_T frac, const real_T table[]);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

/* Return rtNaN needed by the generated code. */
static real_T rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)isinf(value);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)isinf(value);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

static uint32_T plook_evenc(real_T u, real_T bp0, real_T bpSpace, uint32_T
  maxIndex, real_T *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'even'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp0) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else {
    real_T fbpIndex;
    real_T invSpc;
    invSpc = 1.0 / bpSpace;
    fbpIndex = (u - bp0) * invSpc;
    if (fbpIndex < maxIndex) {
      bpIndex = (uint32_T)fbpIndex;
      *fraction = (u - ((real_T)(uint32_T)fbpIndex * bpSpace + bp0)) * invSpc;
    } else {
      bpIndex = maxIndex - 1U;
      *fraction = 1.0;
    }
  }

  return bpIndex;
}

static real_T intrp1d_l(uint32_T bpIndex, real_T frac, const real_T table[])
{
  real_T yL_0d0;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[bpIndex];
  return (table[bpIndex + 1U] - yL_0d0) * frac + yL_0d0;
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      real_T q;
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Model step function */
void Flux_Observer_step(void)
{
  real_T rtb_B;
  real_T rtb_Integrator_d_tmp;
  real_T rtb_Integrator_g;
  real_T rtb_Integrator_m;
  real_T rtb_Mod1;
  real_T rtb_MultiportSwitch;
  real_T rtb_MultiportSwitch1;
  real_T rtb_N_calculator;
  real_T rtb_Sum3;
  real_T rtb_Sum7;
  real32_T rtb_Sum6;
  real32_T rtb_etax1;
  real32_T rtb_etax1_tmp;
  real32_T rtb_etax2;
  real32_T rtb_etax2_tmp;
  uint32_T bpIdx;
  boolean_T negFlag;
  static const real_T tableData_c[16] = { 0.0, 0.10452846326765346,
    0.20791169081775931, 0.3090169943749474, 0.40673664307580015,
    0.49999999999999994, 0.58778525229247314, 0.66913060635885824,
    0.74314482547739424, 0.80901699437494745, 0.8660254037844386,
    0.91354545764260087, 0.95105651629515353, 0.97814760073380569,
    0.99452189536827329, 1.0 };

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

  /* Outputs for Atomic SubSystem: '<S1>/Flux_observer' */
  /* Gain: '<S10>/Gain3' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  Gain: '<S10>/Gain6'
   */
  rtb_etax1_tmp = L * (real32_T)rtb_Sum7;

  /* Sum: '<S10>/Sum3' incorporates:
   *  Delay: '<S10>/Delay'
   *  Gain: '<S10>/Gain3'
   */
  rtb_etax1 = rtDW.Delay_DSTATE_k - rtb_etax1_tmp;

  /* Gain: '<S10>/Gain2' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   *  Gain: '<S10>/Gain7'
   */
  rtb_etax2_tmp = L * (real32_T)rtb_Integrator_m;

  /* Sum: '<S10>/Sum2' incorporates:
   *  Delay: '<S10>/Delay1'
   *  Gain: '<S10>/Gain2'
   */
  rtb_etax2 = rtDW.Delay1_DSTATE_f - rtb_etax2_tmp;

  /* Sum: '<S10>/Sum6' incorporates:
   *  Constant: '<S10>/Constant'
   *  Math: '<S10>/Square1'
   *  Math: '<S10>/Square2'
   *  Math: '<S10>/Square3'
   *  Sum: '<S10>/Sum4'
   */
  rtb_Sum6 = flux * flux - (rtb_etax1 * rtb_etax1 + rtb_etax2 * rtb_etax2);

  /* Sum: '<S10>/Sum8' incorporates:
   *  Constant: '<S10>/Constant1'
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  DataTypeConversion: '<S1>/Data Type Conversion2'
   *  Delay: '<S10>/Delay'
   *  Delay: '<S1>/Delay1'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain4'
   *  Product: '<S10>/Product'
   *  Sum: '<S10>/Sum'
   *  Sum: '<S10>/Sum7'
   */
  rtb_etax1 = (rtb_etax1 * rtb_Sum6 * gamma + ((real32_T)rtDW.Delay1_DSTATE - Rs
    * (real32_T)rtb_Sum7)) * Ts + rtDW.Delay_DSTATE_k;

  /* Gain: '<S10>/Gain8' incorporates:
   *  Sum: '<S10>/Sum9'
   */
  cos_theta = (rtb_etax1 - rtb_etax1_tmp) * (1.0F / flux);

  /* Math: '<S11>/Mod1' incorporates:
   *  Constant: '<S11>/Constant3'
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   */
  rtb_Mod1 = rt_modd_snf(rtDW.DiscreteTimeIntegrator_DSTATE, 6.2831853071795862);

  /* Trigonometry: '<S11>/Sin' */
  rtb_Integrator_g = rtb_Mod1 / 6.2831853071795862;
  if (rtb_Integrator_g > 0.5) {
    rtb_Integrator_g -= 0.5;
    negFlag = true;
  } else {
    negFlag = false;
  }

  if (rtb_Integrator_g > 0.25) {
    rtb_Integrator_g = 0.5 - rtb_Integrator_g;
  }

  bpIdx = plook_evenc(rtb_Integrator_g, 0.0, 0.016666666666666666, 15U,
                      &rtb_N_calculator);
  rtb_Integrator_g = intrp1d_l(bpIdx, rtb_N_calculator, tableData_c);
  if (negFlag) {
    rtb_Integrator_g = -rtb_Integrator_g;
  }

  /* End of Trigonometry: '<S11>/Sin' */

  /* Product: '<S11>/Product1' */
  rtb_B = cos_theta * rtb_Integrator_g;

  /* Sum: '<S10>/Sum10' incorporates:
   *  Constant: '<S10>/Constant1'
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   *  DataTypeConversion: '<S1>/Data Type Conversion3'
   *  Delay: '<S10>/Delay1'
   *  Delay: '<S1>/Delay'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain5'
   *  Product: '<S10>/Product1'
   *  Sum: '<S10>/Sum1'
   *  Sum: '<S10>/Sum5'
   */
  rtb_etax2 = (rtb_Sum6 * rtb_etax2 * gamma + ((real32_T)rtDW.Delay_DSTATE - Rs *
    (real32_T)rtb_Integrator_m)) * Ts + rtDW.Delay1_DSTATE_f;

  /* Gain: '<S10>/Gain9' incorporates:
   *  Sum: '<S10>/Sum11'
   */
  sin_theta = (rtb_etax2 - rtb_etax2_tmp) * (1.0F / flux);

  /* Trigonometry: '<S11>/Cos' */
  rtb_Integrator_g = rtb_Mod1 / 6.2831853071795862 + 0.25;
  if (rtb_Integrator_g >= 1.0) {
    rtb_Integrator_g--;
  }

  if (rtb_Integrator_g > 0.5) {
    rtb_Integrator_g -= 0.5;
    negFlag = true;
  } else {
    negFlag = false;
  }

  if (rtb_Integrator_g > 0.25) {
    rtb_Integrator_g = 0.5 - rtb_Integrator_g;
  }

  bpIdx = plook_evenc(rtb_Integrator_g, 0.0, 0.016666666666666666, 15U,
                      &rtb_N_calculator);
  rtb_Integrator_g = intrp1d_l(bpIdx, rtb_N_calculator, tableData_c);
  if (negFlag) {
    rtb_Integrator_g = -rtb_Integrator_g;
  }

  /* End of Trigonometry: '<S11>/Cos' */

  /* Sum: '<S11>/Sum' incorporates:
   *  Product: '<S11>/Product'
   */
  rtb_Integrator_g = sin_theta * rtb_Integrator_g - rtb_B;

  /* Sum: '<S58>/Sum' incorporates:
   *  DiscreteIntegrator: '<S49>/Integrator'
   *  Gain: '<S54>/Proportional Gain'
   */
  rtb_B = PLL_P * rtb_Integrator_g + rtDW.Integrator_DSTATE_m;

  /* S-Function (sdspbiquad): '<S12>/Digital Filter' */
  rtb_N_calculator = (0.073801721165179412 * rtb_B - -1.2505164308487404 *
                      rtDW.DigitalFilter_FILT_STATES[0]) - 0.54572331550945785 *
    rtDW.DigitalFilter_FILT_STATES[1];
  rtb_Sum3 = (2.0 * rtDW.DigitalFilter_FILT_STATES[0] + rtb_N_calculator) +
    rtDW.DigitalFilter_FILT_STATES[1];
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = rtb_N_calculator;
  rtb_N_calculator = (0.24523727525278555 * rtb_Sum3 - -0.50952544949442879 *
                      rtDW.DigitalFilter_FILT_STATES[2]) - 0.0 *
    rtDW.DigitalFilter_FILT_STATES[3];
  rtb_Sum3 = (rtb_N_calculator + rtDW.DigitalFilter_FILT_STATES[2]) + 0.0 *
    rtDW.DigitalFilter_FILT_STATES[3];
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = rtb_N_calculator;

  /* Update for Delay: '<S10>/Delay' */
  rtDW.Delay_DSTATE_k = rtb_etax1;

  /* Update for Delay: '<S10>/Delay1' */
  rtDW.Delay1_DSTATE_f = rtb_etax2;

  /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE += 0.0001 * rtb_B;

  /* Update for DiscreteIntegrator: '<S49>/Integrator' incorporates:
   *  Gain: '<S46>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_m += PLL_I * rtb_Integrator_g * 0.0001;

  /* End of Outputs for SubSystem: '<S1>/Flux_observer' */

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain3'
   *  Inport: '<Root>/SpeedRef'
   */
  rtb_Sum3 = rtU.SpeedRef - 1.0 / Pn * rtb_Sum3 * 9.5492965855137211;

  /* Fcn: '<S7>/Fcn1' incorporates:
   *  Fcn: '<S2>/Fcn'
   *  Fcn: '<S2>/Fcn1'
   *  Fcn: '<S7>/Fcn'
   */
  rtb_N_calculator = cos(rtb_Mod1);
  rtb_MultiportSwitch = sin(rtb_Mod1);

  /* Sum: '<S214>/Sum' incorporates:
   *  DiscreteIntegrator: '<S205>/Integrator'
   *  Gain: '<S210>/Proportional Gain'
   */
  rtb_Mod1 = 0.05 * rtb_Sum3 + rtDW.Integrator_DSTATE;

  /* Saturate: '<S212>/Saturation' */
  if (rtb_Mod1 > 500.0) {
    rtb_Mod1 = 500.0;
  } else if (rtb_Mod1 < -500.0) {
    rtb_Mod1 = -500.0;
  }

  /* Sum: '<S1>/Sum4' incorporates:
   *  Fcn: '<S7>/Fcn1'
   *  Saturate: '<S212>/Saturation'
   */
  rtb_Mod1 -= -rtb_MultiportSwitch * rtb_Sum7 + rtb_N_calculator *
    rtb_Integrator_m;

  /* Sum: '<S162>/Sum' incorporates:
   *  DiscreteIntegrator: '<S153>/Integrator'
   *  Gain: '<S158>/Proportional Gain'
   */
  rtb_B = 2.0 * rtb_Mod1 + rtDW.Integrator_DSTATE_a;

  /* Saturate: '<S160>/Saturation' */
  if (rtb_B > 50.0) {
    rtb_B = 50.0;
  } else if (rtb_B < -50.0) {
    rtb_B = -50.0;
  }

  /* End of Saturate: '<S160>/Saturation' */

  /* Sum: '<S1>/Sum7' incorporates:
   *  Constant: '<S1>/Id_ref'
   *  Fcn: '<S7>/Fcn'
   */
  rtb_Sum7 = 0.0 - (rtb_N_calculator * rtb_Sum7 + rtb_MultiportSwitch *
                    rtb_Integrator_m);

  /* Sum: '<S110>/Sum' incorporates:
   *  DiscreteIntegrator: '<S101>/Integrator'
   *  Gain: '<S106>/Proportional Gain'
   */
  rtb_Integrator_g = 2.0 * rtb_Sum7 + rtDW.Integrator_DSTATE_k;

  /* Saturate: '<S108>/Saturation' */
  if (rtb_Integrator_g > 50.0) {
    rtb_Integrator_g = 50.0;
  } else if (rtb_Integrator_g < -50.0) {
    rtb_Integrator_g = -50.0;
  }

  /* End of Saturate: '<S108>/Saturation' */

  /* Fcn: '<S2>/Fcn' */
  rtb_Integrator_m = rtb_N_calculator * rtb_Integrator_g - rtb_MultiportSwitch *
    rtb_B;

  /* Fcn: '<S2>/Fcn1' */
  rtb_B = rtb_MultiportSwitch * rtb_Integrator_g + rtb_N_calculator * rtb_B;

  /* Fcn: '<S223>/N_calculator' incorporates:
   *  Fcn: '<S223>/Uref1'
   *  Fcn: '<S223>/Uref2'
   *  Fcn: '<S223>/Uref3'
   *  Switch: '<S223>/A'
   *  Switch: '<S223>/B'
   *  Switch: '<S223>/C'
   */
  rtb_N_calculator = (((1.7320508075688772 * rtb_Integrator_m - rtb_B) / 2.0 >
                       0.0) * (int32_T)2.0 + (rtb_B > 0.0)) + ((-rtb_B -
    1.7320508075688772 * rtb_Integrator_m) / 2.0 > 0.0) * (int32_T)4.0;

  /* MultiPortSwitch: '<S224>/Multiport Switch' incorporates:
   *  Constant: '<S1>/Constant10'
   *  Constant: '<S1>/Constant9'
   *  Fcn: '<S226>/X_Calculator'
   *  Fcn: '<S226>/Y_Calculator'
   *  Fcn: '<S226>/Z_Calculator'
   *  Gain: '<S224>/Gain'
   *  Gain: '<S224>/Gain1'
   *  Gain: '<S224>/Gain2'
   */
  switch ((int32_T)rtb_N_calculator) {
   case 1:
    rtb_MultiportSwitch = (-0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_B)
      * (1.7320508075688772 * Period) / Udc;

    /* MultiPortSwitch: '<S224>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S226>/Y_Calculator'
     *  Fcn: '<S226>/Z_Calculator'
     */
    rtb_MultiportSwitch1 = (0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_B)
      * (1.7320508075688772 * Period) / Udc;
    break;

   case 2:
    rtb_MultiportSwitch = (0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_B) *
      (1.7320508075688772 * Period) / Udc;

    /* MultiPortSwitch: '<S224>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S226>/X_Calculator'
     *  Fcn: '<S226>/Y_Calculator'
     *  Gain: '<S224>/Gain'
     */
    rtb_MultiportSwitch1 = -(1.7320508075688772 * rtb_B * Period / Udc);
    break;

   case 3:
    rtb_MultiportSwitch = -((-0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_B) * (1.7320508075688772 * Period) / Udc);

    /* MultiPortSwitch: '<S224>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S226>/X_Calculator'
     *  Fcn: '<S226>/Z_Calculator'
     *  Gain: '<S224>/Gain2'
     */
    rtb_MultiportSwitch1 = 1.7320508075688772 * rtb_B * Period / Udc;
    break;

   case 4:
    rtb_MultiportSwitch = -(1.7320508075688772 * rtb_B * Period / Udc);

    /* MultiPortSwitch: '<S224>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S226>/X_Calculator'
     *  Fcn: '<S226>/Z_Calculator'
     *  Gain: '<S224>/Gain'
     */
    rtb_MultiportSwitch1 = (-0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_B)
      * (1.7320508075688772 * Period) / Udc;
    break;

   case 5:
    rtb_MultiportSwitch = 1.7320508075688772 * rtb_B * Period / Udc;

    /* MultiPortSwitch: '<S224>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S226>/X_Calculator'
     *  Fcn: '<S226>/Y_Calculator'
     *  Gain: '<S224>/Gain1'
     */
    rtb_MultiportSwitch1 = -((0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_B) * (1.7320508075688772 * Period) / Udc);
    break;

   default:
    rtb_MultiportSwitch = -((0.8660254037844386 * rtb_Integrator_m + 0.5 * rtb_B)
      * (1.7320508075688772 * Period) / Udc);

    /* MultiPortSwitch: '<S224>/Multiport Switch1' incorporates:
     *  Constant: '<S1>/Constant10'
     *  Constant: '<S1>/Constant9'
     *  Fcn: '<S226>/Y_Calculator'
     *  Fcn: '<S226>/Z_Calculator'
     *  Gain: '<S224>/Gain1'
     *  Gain: '<S224>/Gain2'
     */
    rtb_MultiportSwitch1 = -((-0.8660254037844386 * rtb_Integrator_m + 0.5 *
      rtb_B) * (1.7320508075688772 * Period) / Udc);
    break;
  }

  /* End of MultiPortSwitch: '<S224>/Multiport Switch' */

  /* Switch: '<S224>/Switch' incorporates:
   *  Constant: '<S1>/Constant9'
   *  Fcn: '<S224>/T1_Calculator'
   *  Fcn: '<S224>/T2_Calculator'
   *  Fcn: '<S224>/T_Calculator'
   *  Switch: '<S224>/Switch1'
   */
  if ((Period - rtb_MultiportSwitch) - rtb_MultiportSwitch1 > 0.0) {
    rtb_Integrator_g = rtb_MultiportSwitch;
  } else {
    /* Fcn: '<S224>/T1_Calculator' incorporates:
     *  Fcn: '<S224>/T2_Calculator'
     */
    rtb_Integrator_d_tmp = rtb_MultiportSwitch + rtb_MultiportSwitch1;
    rtb_Integrator_g = rtb_MultiportSwitch * Period / rtb_Integrator_d_tmp;
    rtb_MultiportSwitch1 = rtb_MultiportSwitch1 * Period / rtb_Integrator_d_tmp;
  }

  /* End of Switch: '<S224>/Switch' */

  /* Sum: '<S225>/Tb' incorporates:
   *  Constant: '<S1>/Constant9'
   *  Sum: '<S225>/Tc'
   */
  rtb_Integrator_d_tmp = Period + rtb_Integrator_g;

  /* Gain: '<S225>/Gain1' incorporates:
   *  Sum: '<S225>/Tb'
   */
  rtb_MultiportSwitch = (rtb_Integrator_d_tmp - rtb_MultiportSwitch1) * 0.25;

  /* Gain: '<S225>/Gain' incorporates:
   *  Constant: '<S1>/Constant9'
   *  Sum: '<S225>/Ta'
   */
  rtb_Integrator_g = ((Period - rtb_Integrator_g) - rtb_MultiportSwitch1) * 0.25;

  /* Gain: '<S225>/Gain2' incorporates:
   *  Sum: '<S225>/Tc'
   */
  rtb_MultiportSwitch1 = (rtb_Integrator_d_tmp + rtb_MultiportSwitch1) * 0.25;

  /* MultiPortSwitch: '<S225>/1' */
  switch ((int32_T)rtb_N_calculator) {
   case 1:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S225>/2'
     */
    rtY.Tcm2 = rtb_Integrator_g;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S225>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch1;
    break;

   case 2:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_Integrator_g;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S225>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S225>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch;
    break;

   case 3:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_Integrator_g;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S225>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S225>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch1;
    break;

   case 4:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S225>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S225>/3'
     */
    rtY.Tcm3 = rtb_Integrator_g;
    break;

   case 5:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S225>/2'
     */
    rtY.Tcm2 = rtb_Integrator_g;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S225>/3'
     */
    rtY.Tcm3 = rtb_MultiportSwitch;
    break;

   default:
    /* Outport: '<Root>/Tcm1' */
    rtY.Tcm1 = rtb_MultiportSwitch;

    /* Outport: '<Root>/Tcm2' incorporates:
     *  MultiPortSwitch: '<S225>/2'
     */
    rtY.Tcm2 = rtb_MultiportSwitch1;

    /* Outport: '<Root>/Tcm3' incorporates:
     *  MultiPortSwitch: '<S225>/3'
     */
    rtY.Tcm3 = rtb_Integrator_g;
    break;
  }

  /* End of MultiPortSwitch: '<S225>/1' */

  /* Update for Delay: '<S1>/Delay1' */
  rtDW.Delay1_DSTATE = rtb_Integrator_m;

  /* Update for Delay: '<S1>/Delay' */
  rtDW.Delay_DSTATE = rtb_B;

  /* Update for DiscreteIntegrator: '<S205>/Integrator' incorporates:
   *  Gain: '<S202>/Integral Gain'
   */
  rtDW.Integrator_DSTATE += 5.0 * rtb_Sum3 * 0.0001;
  if (rtDW.Integrator_DSTATE > 500.0) {
    rtDW.Integrator_DSTATE = 500.0;
  } else if (rtDW.Integrator_DSTATE < -500.0) {
    rtDW.Integrator_DSTATE = -500.0;
  }

  /* End of Update for DiscreteIntegrator: '<S205>/Integrator' */

  /* Update for DiscreteIntegrator: '<S153>/Integrator' incorporates:
   *  Gain: '<S150>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_a += 20.0 * rtb_Mod1 * 0.0001;
  if (rtDW.Integrator_DSTATE_a > 100.0) {
    rtDW.Integrator_DSTATE_a = 100.0;
  } else if (rtDW.Integrator_DSTATE_a < -100.0) {
    rtDW.Integrator_DSTATE_a = -100.0;
  }

  /* End of Update for DiscreteIntegrator: '<S153>/Integrator' */

  /* Update for DiscreteIntegrator: '<S101>/Integrator' incorporates:
   *  Gain: '<S98>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_k += 20.0 * rtb_Sum7 * 0.0001;
  if (rtDW.Integrator_DSTATE_k > 100.0) {
    rtDW.Integrator_DSTATE_k = 100.0;
  } else if (rtDW.Integrator_DSTATE_k < -100.0) {
    rtDW.Integrator_DSTATE_k = -100.0;
  }

  /* End of Update for DiscreteIntegrator: '<S101>/Integrator' */
}

/* Model initialize function */
void Flux_Observer_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
