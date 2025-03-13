/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SVPWM.h
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

#ifndef SVPWM_h_
#define SVPWM_h_
#ifndef SVPWM_COMMON_INCLUDES_
#define SVPWM_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* SVPWM_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T alpha;                      /* '<Root>/alpha' */
  real32_T beta;                       /* '<Root>/beta' */
  real32_T Period;                     /* '<Root>/Period' */
  real32_T Udc;                        /* '<Root>/Udc' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Tcm1;                       /* '<Root>/Tcm1' */
  real32_T Tcm2;                       /* '<Root>/Tcm2' */
  real32_T Tcm3;                       /* '<Root>/Tcm3' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void SVPWM_initialize(void);
extern void SVPWM_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 * Block '<S1>/Scope4' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('based_FOC/Subsystem1/SVPWM')    - opens subsystem based_FOC/Subsystem1/SVPWM
 * hilite_system('based_FOC/Subsystem1/SVPWM/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'based_FOC/Subsystem1'
 * '<S1>'   : 'based_FOC/Subsystem1/SVPWM'
 * '<S2>'   : 'based_FOC/Subsystem1/SVPWM/Sector Calculator'
 * '<S3>'   : 'based_FOC/Subsystem1/SVPWM/T1T2_Calculator1'
 * '<S4>'   : 'based_FOC/Subsystem1/SVPWM/Tcm_Calculator2'
 * '<S5>'   : 'based_FOC/Subsystem1/SVPWM/XYZ_Calculator'
 */
#endif                                 /* SVPWM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
