/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Anti_Park.h
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

#ifndef Anti_Park_h_
#define Anti_Park_h_
#ifndef Anti_Park_COMMON_INCLUDES_
#define Anti_Park_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Anti_Park_COMMON_INCLUDES_ */

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
  real_T Uq;                           /* '<Root>/Uq' */
  real_T Vd;                           /* '<Root>/Vd' */
  real_T The;                          /* '<Root>/The' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T U_alpha;                      /* '<Root>/U_alpha' */
  real_T U_beta;                       /* '<Root>/U_beta' */
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
extern void Anti_Park_initialize(void);
extern void Anti_Park_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * hilite_system('based_FOC/Anti_Park')    - opens subsystem based_FOC/Anti_Park
 * hilite_system('based_FOC/Anti_Park/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'based_FOC'
 * '<S1>'   : 'based_FOC/Anti_Park'
 */
#endif                                 /* Anti_Park_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
