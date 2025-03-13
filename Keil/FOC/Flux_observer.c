/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flux_observer.c
 *
 * Code generated for Simulink model 'Flux_observer'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Mar 10 19:54:51 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Flux_observer.h"
#include "rtwtypes.h"
#include <math.h>
#include <float.h>
#include "math.h"

#define L                              0.00045                  /* Referenced by:
                                                                  * '<S2>/Gain2'
                                                                  * '<S2>/Gain3'
                                                                  * '<S2>/Gain6'
                                                                  * '<S2>/Gain7'
                                                                  */
#define PLL_I                          1.0                    /* Referenced by: '<S38>/Integral Gain' */
#define PLL_P                          1.0                    /* Referenced by: '<S46>/Proportional Gain' */
#define Rs                             0.60                      /* Referenced by:
                                                                  * '<S2>/Gain'
                                                                  * '<S2>/Gain1'
                                                                  */
#define Ts                             1.0E-4                    /* Referenced by:
                                                                  * '<S2>/Gain4'
                                                                  * '<S2>/Gain5'
                                                                  *//* PWMÖÜÆÚ */
#define flux                           0.0058                   /* Referenced by:
                                                                  * '<S2>/Constant'
                                                                  * '<S2>/Gain8'
                                                                  * '<S2>/Gain9'
                                                                  */
#define gamma                          10000.0                  /* Referenced by: '<S2>/Constant1' */


/* Exported block signals */
real_T cos_theta;                      /* '<S2>/Gain8' */
real_T sin_theta;                      /* '<S2>/Gain9' */

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
void Flux_observer_step(void)
{
  real_T frac;
  real_T rtb_DiscreteTimeIntegrator;
  real_T rtb_Integrator;
  real_T rtb_Mod1;
  real_T rtb_Sum;
  real_T rtb_Sum_k;
  real_T uVarTmp;
  real_T yVarTmp;
  uint32_T bpIdx;
  boolean_T negFlag;
  static const real_T tableData_c[16] = { 0.0, 0.10452846326765346,
    0.20791169081775931, 0.3090169943749474, 0.40673664307580015,
    0.49999999999999994, 0.58778525229247314, 0.66913060635885824,
    0.74314482547739424, 0.80901699437494745, 0.8660254037844386,
    0.91354545764260087, 0.95105651629515353, 0.97814760073380569,
    0.99452189536827329, 1.0 };

  /* Outputs for Atomic SubSystem: '<Root>/Flux_observer' */
  /* Gain: '<S2>/Gain3' incorporates:
   *  Gain: '<S2>/Gain6'
   *  Inport: '<Root>/Ialpha'
   */
  rtb_Mod1 = L * rtU.Ialpha;

  /* Sum: '<S2>/Sum3' incorporates:
   *  Delay: '<S2>/Delay'
   *  Gain: '<S2>/Gain3'
   */
  rtb_DiscreteTimeIntegrator = rtDW.Delay_DSTATE - rtb_Mod1;

  /* Gain: '<S2>/Gain2' incorporates:
   *  Gain: '<S2>/Gain7'
   *  Inport: '<Root>/Ibeta'
   */
  rtb_Sum = L * rtU.Ibeta;

  /* Sum: '<S2>/Sum2' incorporates:
   *  Delay: '<S2>/Delay1'
   *  Gain: '<S2>/Gain2'
   */
  rtb_Integrator = rtDW.Delay1_DSTATE - rtb_Sum;

  /* Sum: '<S2>/Sum6' incorporates:
   *  Constant: '<S2>/Constant'
   *  Math: '<S2>/Square1'
   *  Math: '<S2>/Square2'
   *  Math: '<S2>/Square3'
   *  Sum: '<S2>/Sum4'
   */
  rtb_Sum_k = flux * flux - (rtb_DiscreteTimeIntegrator *
    rtb_DiscreteTimeIntegrator + rtb_Integrator * rtb_Integrator);

  /* Sum: '<S2>/Sum8' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Delay: '<S2>/Delay'
   *  Gain: '<S2>/Gain'
   *  Gain: '<S2>/Gain4'
   *  Inport: '<Root>/Ialpha'
   *  Inport: '<Root>/Ualpha'
   *  Product: '<S2>/Product'
   *  Sum: '<S2>/Sum'
   *  Sum: '<S2>/Sum7'
   */
  rtb_DiscreteTimeIntegrator = (rtb_DiscreteTimeIntegrator * rtb_Sum_k * gamma +
    (rtU.Ualpha - Rs * rtU.Ialpha)) * Ts + rtDW.Delay_DSTATE;

  /* Gain: '<S2>/Gain8' incorporates:
   *  Sum: '<S2>/Sum9'
   */
  cos_theta = (rtb_DiscreteTimeIntegrator - rtb_Mod1) * (1.0 / flux);

  /* Math: '<S3>/Mod1' incorporates:
   *  Constant: '<S3>/Constant3'
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   */
  rtb_Mod1 = rt_modd_snf(rtDW.DiscreteTimeIntegrator_DSTATE, 6.2831853071795862);

  /* Trigonometry: '<S3>/Sin' */
  uVarTmp = rtb_Mod1 / 6.2831853071795862;
  if (uVarTmp > 0.5) {
    uVarTmp -= 0.5;
    negFlag = true;
  } else {
    negFlag = false;
  }

  if (uVarTmp > 0.25) {
    uVarTmp = 0.5 - uVarTmp;
  }

  bpIdx = plook_evenc(uVarTmp, 0.0, 0.016666666666666666, 15U, &frac);
  yVarTmp = intrp1d_l(bpIdx, frac, tableData_c);
  if (negFlag) {
    yVarTmp = -yVarTmp;
  }

  /* End of Trigonometry: '<S3>/Sin' */

  /* Sum: '<S2>/Sum10' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Delay: '<S2>/Delay1'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S2>/Gain5'
   *  Inport: '<Root>/Ibeta'
   *  Inport: '<Root>/Ubeta'
   *  Product: '<S2>/Product1'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S2>/Sum5'
   */
  rtb_Integrator = (rtb_Sum_k * rtb_Integrator * gamma + (rtU.Ubeta - Rs *
    rtU.Ibeta)) * Ts + rtDW.Delay1_DSTATE;

  /* Gain: '<S2>/Gain9' incorporates:
   *  Sum: '<S2>/Sum11'
   */
  sin_theta = (rtb_Integrator - rtb_Sum) * (1.0 / flux);

  /* Trigonometry: '<S3>/Cos' */
  uVarTmp = rtb_Mod1 / 6.2831853071795862 + 0.25;
  if (uVarTmp >= 1.0) {
    uVarTmp--;
  }

  if (uVarTmp > 0.5) {
    uVarTmp -= 0.5;
    negFlag = true;
  } else {
    negFlag = false;
  }

  if (uVarTmp > 0.25) {
    uVarTmp = 0.5 - uVarTmp;
  }

  bpIdx = plook_evenc(uVarTmp, 0.0, 0.016666666666666666, 15U, &frac);
  rtb_Sum = intrp1d_l(bpIdx, frac, tableData_c);
  if (negFlag) {
    rtb_Sum = -rtb_Sum;
  }

  /* End of Trigonometry: '<S3>/Cos' */

  /* Sum: '<S3>/Sum' incorporates:
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   */
  rtb_Sum_k = sin_theta * rtb_Sum - cos_theta * yVarTmp;

  /* Sum: '<S50>/Sum' incorporates:
   *  DiscreteIntegrator: '<S41>/Integrator'
   *  Gain: '<S46>/Proportional Gain'
   */
  rtb_Sum = PLL_P * rtb_Sum_k + rtDW.Integrator_DSTATE;

  /* S-Function (sdspbiquad): '<S4>/Digital Filter' */
  yVarTmp = (0.073801721165179412 * rtb_Sum - -1.2505164308487404 *
             rtDW.DigitalFilter_FILT_STATES[0]) - 0.54572331550945785 *
    rtDW.DigitalFilter_FILT_STATES[1];
  uVarTmp = (2.0 * rtDW.DigitalFilter_FILT_STATES[0] + yVarTmp) +
    rtDW.DigitalFilter_FILT_STATES[1];
  rtDW.DigitalFilter_FILT_STATES[1] = rtDW.DigitalFilter_FILT_STATES[0];
  rtDW.DigitalFilter_FILT_STATES[0] = yVarTmp;
  yVarTmp = (0.24523727525278555 * uVarTmp - -0.50952544949442879 *
             rtDW.DigitalFilter_FILT_STATES[2]) - 0.0 *
    rtDW.DigitalFilter_FILT_STATES[3];

  /* Outport: '<Root>/We_sensorless' incorporates:
   *  S-Function (sdspbiquad): '<S4>/Digital Filter'
   */
  rtY.We_sensorless = (yVarTmp + rtDW.DigitalFilter_FILT_STATES[2]) + 0.0 *
    rtDW.DigitalFilter_FILT_STATES[3];

  /* S-Function (sdspbiquad): '<S4>/Digital Filter' */
  rtDW.DigitalFilter_FILT_STATES[3] = rtDW.DigitalFilter_FILT_STATES[2];
  rtDW.DigitalFilter_FILT_STATES[2] = yVarTmp;

  /* Update for Delay: '<S2>/Delay' */
  rtDW.Delay_DSTATE = rtb_DiscreteTimeIntegrator;

  /* Update for Delay: '<S2>/Delay1' */
  rtDW.Delay1_DSTATE = rtb_Integrator;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE += 0.0001 * rtb_Sum;

  /* Update for DiscreteIntegrator: '<S41>/Integrator' incorporates:
   *  Gain: '<S38>/Integral Gain'
   */
  rtDW.Integrator_DSTATE += PLL_I * rtb_Sum_k * 0.0001;

  /* End of Outputs for SubSystem: '<Root>/Flux_observer' */

  /* Outport: '<Root>/Theta_e_sensorless' */
  rtY.Theta_e_sensorless = rtb_Mod1;
}

/* Model initialize function */
void Flux_observer_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
