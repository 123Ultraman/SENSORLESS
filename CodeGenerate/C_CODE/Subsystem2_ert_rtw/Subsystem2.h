/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem2.h
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

#ifndef Subsystem2_h_
#define Subsystem2_h_
#ifndef Subsystem2_COMMON_INCLUDES_
#define Subsystem2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Subsystem2_COMMON_INCLUDES_ */

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
  real_T The;                          /* '<Root>/The' */
  real_T Ia;                           /* '<Root>/Ia' */
  real_T Ib;                           /* '<Root>/Ib' */
  real_T Ic;                           /* '<Root>/Ic' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T I_q;                          /* '<Root>/I_q' */
  real_T I_d;                          /* '<Root>/I_d' */
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
extern void Subsystem2_initialize(void);
extern void Subsystem2_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/N2' : Unused code path elimination
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
 * hilite_system('based_FOC/Subsystem2')    - opens subsystem based_FOC/Subsystem2
 * hilite_system('based_FOC/Subsystem2/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'based_FOC'
 * '<S1>'   : 'based_FOC/Subsystem2'
 * '<S2>'   : 'based_FOC/Subsystem2/Clark'
 * '<S3>'   : 'based_FOC/Subsystem2/Park'
 */
#endif                                 /* Subsystem2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
