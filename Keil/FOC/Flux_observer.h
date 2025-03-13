/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flux_observer.h
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

#ifndef Flux_observer_h_
#define Flux_observer_h_
#ifndef Flux_observer_COMMON_INCLUDES_
#define Flux_observer_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Flux_observer_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T DigitalFilter_FILT_STATES[4]; /* '<S4>/Digital Filter' */
  real_T Delay_DSTATE;                 /* '<S2>/Delay' */
  real_T Delay1_DSTATE;                /* '<S2>/Delay1' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real_T Integrator_DSTATE;            /* '<S41>/Integrator' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Ialpha;                       /* '<Root>/Ialpha' */
  real_T Ibeta;                        /* '<Root>/Ibeta' */
  real_T Ualpha;                       /* '<Root>/Ualpha' */
  real_T Ubeta;                        /* '<Root>/Ubeta' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T We_sensorless;                /* '<Root>/We_sensorless' */
  real_T Theta_e_sensorless;           /* '<Root>/Theta_e_sensorless' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T cos_theta;               /* '<S2>/Gain8' */
extern real_T sin_theta;               /* '<S2>/Gain9' */

/* Model entry point functions */
extern void Flux_observer_initialize(void);
extern void Flux_observer_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S6>/Check Signal Attributes' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope6' : Unused code path elimination
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
 * hilite_system('based_FOC/Flux_Observer/Flux_observer')    - opens subsystem based_FOC/Flux_Observer/Flux_observer
 * hilite_system('based_FOC/Flux_Observer/Flux_observer/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'based_FOC/Flux_Observer'
 * '<S1>'   : 'based_FOC/Flux_Observer/Flux_observer'
 * '<S2>'   : 'based_FOC/Flux_Observer/Flux_observer/OBSERVER'
 * '<S3>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL'
 * '<S4>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL/Digital Filter Design'
 * '<S5>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller'
 * '<S6>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL/Digital Filter Design/Check Signal Attributes'
 * '<S7>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Anti-windup'
 * '<S8>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/D Gain'
 * '<S9>'   : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/External Derivative'
 * '<S10>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter'
 * '<S11>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter ICs'
 * '<S12>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/I Gain'
 * '<S13>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain'
 * '<S14>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain Fdbk'
 * '<S15>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator'
 * '<S16>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator ICs'
 * '<S17>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Copy'
 * '<S18>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Gain'
 * '<S19>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/P Copy'
 * '<S20>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Parallel P Gain'
 * '<S21>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Reset Signal'
 * '<S22>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation'
 * '<S23>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation Fdbk'
 * '<S24>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum'
 * '<S25>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum Fdbk'
 * '<S26>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode'
 * '<S27>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode Sum'
 * '<S28>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Integral'
 * '<S29>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Ngain'
 * '<S30>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/postSat Signal'
 * '<S31>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preInt Signal'
 * '<S32>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preSat Signal'
 * '<S33>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Anti-windup/Passthrough'
 * '<S34>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/D Gain/Disabled'
 * '<S35>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/External Derivative/Disabled'
 * '<S36>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter/Disabled'
 * '<S37>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter ICs/Disabled'
 * '<S38>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/I Gain/Internal Parameters'
 * '<S39>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain/Passthrough'
 * '<S40>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S41>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator/Discrete'
 * '<S42>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator ICs/Internal IC'
 * '<S43>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S44>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Gain/Disabled'
 * '<S45>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/P Copy/Disabled'
 * '<S46>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S47>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Reset Signal/Disabled'
 * '<S48>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation/Passthrough'
 * '<S49>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation Fdbk/Disabled'
 * '<S50>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum/Sum_PI'
 * '<S51>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum Fdbk/Disabled'
 * '<S52>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode/Disabled'
 * '<S53>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S54>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S55>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S56>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/postSat Signal/Forward_Path'
 * '<S57>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preInt Signal/Internal PreInt'
 * '<S58>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* Flux_observer_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
