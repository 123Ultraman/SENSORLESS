/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.h
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

#ifndef Subsystem_h_
#define Subsystem_h_
#ifndef Subsystem_COMMON_INCLUDES_
#define Subsystem_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Subsystem_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define Period                         8500.0                    /* Referenced by: '<S1>/Constant9' *//* SVPWM周期，中心堆成模式，定时器周期乘以二 */
#define Pn                             2.0                       /* Referenced by: '<S1>/Gain3' */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S149>/Integrator' */
  real_T UD_DSTATE;                    /* '<S142>/UD' */
  real_T Integrator_DSTATE_a;          /* '<S95>/Integrator' */
  real_T Integrator_DSTATE_k;          /* '<S43>/Integrator' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T In1;                          /* '<Root>/In1' */
  real_T Theta;                        /* '<Root>/In2' */
  real_T ias;                          /* '<Root>/ias' */
  real_T ibs;                          /* '<Root>/ibs' */
  real_T ics;                          /* '<Root>/ics' */
  real_T Theta_b;                      /* '<Root>/The' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Tcm1;                         /* '<Root>/Tcm1' */
  real_T Tcm2;                         /* '<Root>/Tcm2' */
  real_T Tcm3;                         /* '<Root>/Tcm3' */
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
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T Udc;                     /* Variable: Udc
                                        * Referenced by: '<S1>/Constant10'
                                        */

/* Model entry point functions */
extern void Subsystem_initialize(void);
extern void Subsystem_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Nr' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S142>/DTDup' : Unused code path elimination
 * Block '<S8>/Scope1' : Unused code path elimination
 * Block '<S8>/Scope2' : Unused code path elimination
 * Block '<S8>/Scope3' : Unused code path elimination
 * Block '<S8>/Scope4' : Unused code path elimination
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
 * hilite_system('based_FOC/Subsystem')    - opens subsystem based_FOC/Subsystem
 * hilite_system('based_FOC/Subsystem/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'based_FOC'
 * '<S1>'   : 'based_FOC/Subsystem'
 * '<S2>'   : 'based_FOC/Subsystem/Anti_Park1'
 * '<S3>'   : 'based_FOC/Subsystem/Clark'
 * '<S4>'   : 'based_FOC/Subsystem/Id'
 * '<S5>'   : 'based_FOC/Subsystem/Iq'
 * '<S6>'   : 'based_FOC/Subsystem/Park'
 * '<S7>'   : 'based_FOC/Subsystem/Speed1'
 * '<S8>'   : 'based_FOC/Subsystem/Subsystem1'
 * '<S9>'   : 'based_FOC/Subsystem/Id/Anti-windup'
 * '<S10>'  : 'based_FOC/Subsystem/Id/D Gain'
 * '<S11>'  : 'based_FOC/Subsystem/Id/External Derivative'
 * '<S12>'  : 'based_FOC/Subsystem/Id/Filter'
 * '<S13>'  : 'based_FOC/Subsystem/Id/Filter ICs'
 * '<S14>'  : 'based_FOC/Subsystem/Id/I Gain'
 * '<S15>'  : 'based_FOC/Subsystem/Id/Ideal P Gain'
 * '<S16>'  : 'based_FOC/Subsystem/Id/Ideal P Gain Fdbk'
 * '<S17>'  : 'based_FOC/Subsystem/Id/Integrator'
 * '<S18>'  : 'based_FOC/Subsystem/Id/Integrator ICs'
 * '<S19>'  : 'based_FOC/Subsystem/Id/N Copy'
 * '<S20>'  : 'based_FOC/Subsystem/Id/N Gain'
 * '<S21>'  : 'based_FOC/Subsystem/Id/P Copy'
 * '<S22>'  : 'based_FOC/Subsystem/Id/Parallel P Gain'
 * '<S23>'  : 'based_FOC/Subsystem/Id/Reset Signal'
 * '<S24>'  : 'based_FOC/Subsystem/Id/Saturation'
 * '<S25>'  : 'based_FOC/Subsystem/Id/Saturation Fdbk'
 * '<S26>'  : 'based_FOC/Subsystem/Id/Sum'
 * '<S27>'  : 'based_FOC/Subsystem/Id/Sum Fdbk'
 * '<S28>'  : 'based_FOC/Subsystem/Id/Tracking Mode'
 * '<S29>'  : 'based_FOC/Subsystem/Id/Tracking Mode Sum'
 * '<S30>'  : 'based_FOC/Subsystem/Id/Tsamp - Integral'
 * '<S31>'  : 'based_FOC/Subsystem/Id/Tsamp - Ngain'
 * '<S32>'  : 'based_FOC/Subsystem/Id/postSat Signal'
 * '<S33>'  : 'based_FOC/Subsystem/Id/preInt Signal'
 * '<S34>'  : 'based_FOC/Subsystem/Id/preSat Signal'
 * '<S35>'  : 'based_FOC/Subsystem/Id/Anti-windup/Passthrough'
 * '<S36>'  : 'based_FOC/Subsystem/Id/D Gain/Disabled'
 * '<S37>'  : 'based_FOC/Subsystem/Id/External Derivative/Disabled'
 * '<S38>'  : 'based_FOC/Subsystem/Id/Filter/Disabled'
 * '<S39>'  : 'based_FOC/Subsystem/Id/Filter ICs/Disabled'
 * '<S40>'  : 'based_FOC/Subsystem/Id/I Gain/Internal Parameters'
 * '<S41>'  : 'based_FOC/Subsystem/Id/Ideal P Gain/Passthrough'
 * '<S42>'  : 'based_FOC/Subsystem/Id/Ideal P Gain Fdbk/Disabled'
 * '<S43>'  : 'based_FOC/Subsystem/Id/Integrator/Discrete'
 * '<S44>'  : 'based_FOC/Subsystem/Id/Integrator ICs/Internal IC'
 * '<S45>'  : 'based_FOC/Subsystem/Id/N Copy/Disabled wSignal Specification'
 * '<S46>'  : 'based_FOC/Subsystem/Id/N Gain/Disabled'
 * '<S47>'  : 'based_FOC/Subsystem/Id/P Copy/Disabled'
 * '<S48>'  : 'based_FOC/Subsystem/Id/Parallel P Gain/Internal Parameters'
 * '<S49>'  : 'based_FOC/Subsystem/Id/Reset Signal/Disabled'
 * '<S50>'  : 'based_FOC/Subsystem/Id/Saturation/Enabled'
 * '<S51>'  : 'based_FOC/Subsystem/Id/Saturation Fdbk/Disabled'
 * '<S52>'  : 'based_FOC/Subsystem/Id/Sum/Sum_PI'
 * '<S53>'  : 'based_FOC/Subsystem/Id/Sum Fdbk/Disabled'
 * '<S54>'  : 'based_FOC/Subsystem/Id/Tracking Mode/Disabled'
 * '<S55>'  : 'based_FOC/Subsystem/Id/Tracking Mode Sum/Passthrough'
 * '<S56>'  : 'based_FOC/Subsystem/Id/Tsamp - Integral/TsSignalSpecification'
 * '<S57>'  : 'based_FOC/Subsystem/Id/Tsamp - Ngain/Passthrough'
 * '<S58>'  : 'based_FOC/Subsystem/Id/postSat Signal/Forward_Path'
 * '<S59>'  : 'based_FOC/Subsystem/Id/preInt Signal/Internal PreInt'
 * '<S60>'  : 'based_FOC/Subsystem/Id/preSat Signal/Forward_Path'
 * '<S61>'  : 'based_FOC/Subsystem/Iq/Anti-windup'
 * '<S62>'  : 'based_FOC/Subsystem/Iq/D Gain'
 * '<S63>'  : 'based_FOC/Subsystem/Iq/External Derivative'
 * '<S64>'  : 'based_FOC/Subsystem/Iq/Filter'
 * '<S65>'  : 'based_FOC/Subsystem/Iq/Filter ICs'
 * '<S66>'  : 'based_FOC/Subsystem/Iq/I Gain'
 * '<S67>'  : 'based_FOC/Subsystem/Iq/Ideal P Gain'
 * '<S68>'  : 'based_FOC/Subsystem/Iq/Ideal P Gain Fdbk'
 * '<S69>'  : 'based_FOC/Subsystem/Iq/Integrator'
 * '<S70>'  : 'based_FOC/Subsystem/Iq/Integrator ICs'
 * '<S71>'  : 'based_FOC/Subsystem/Iq/N Copy'
 * '<S72>'  : 'based_FOC/Subsystem/Iq/N Gain'
 * '<S73>'  : 'based_FOC/Subsystem/Iq/P Copy'
 * '<S74>'  : 'based_FOC/Subsystem/Iq/Parallel P Gain'
 * '<S75>'  : 'based_FOC/Subsystem/Iq/Reset Signal'
 * '<S76>'  : 'based_FOC/Subsystem/Iq/Saturation'
 * '<S77>'  : 'based_FOC/Subsystem/Iq/Saturation Fdbk'
 * '<S78>'  : 'based_FOC/Subsystem/Iq/Sum'
 * '<S79>'  : 'based_FOC/Subsystem/Iq/Sum Fdbk'
 * '<S80>'  : 'based_FOC/Subsystem/Iq/Tracking Mode'
 * '<S81>'  : 'based_FOC/Subsystem/Iq/Tracking Mode Sum'
 * '<S82>'  : 'based_FOC/Subsystem/Iq/Tsamp - Integral'
 * '<S83>'  : 'based_FOC/Subsystem/Iq/Tsamp - Ngain'
 * '<S84>'  : 'based_FOC/Subsystem/Iq/postSat Signal'
 * '<S85>'  : 'based_FOC/Subsystem/Iq/preInt Signal'
 * '<S86>'  : 'based_FOC/Subsystem/Iq/preSat Signal'
 * '<S87>'  : 'based_FOC/Subsystem/Iq/Anti-windup/Passthrough'
 * '<S88>'  : 'based_FOC/Subsystem/Iq/D Gain/Disabled'
 * '<S89>'  : 'based_FOC/Subsystem/Iq/External Derivative/Disabled'
 * '<S90>'  : 'based_FOC/Subsystem/Iq/Filter/Disabled'
 * '<S91>'  : 'based_FOC/Subsystem/Iq/Filter ICs/Disabled'
 * '<S92>'  : 'based_FOC/Subsystem/Iq/I Gain/Internal Parameters'
 * '<S93>'  : 'based_FOC/Subsystem/Iq/Ideal P Gain/Passthrough'
 * '<S94>'  : 'based_FOC/Subsystem/Iq/Ideal P Gain Fdbk/Disabled'
 * '<S95>'  : 'based_FOC/Subsystem/Iq/Integrator/Discrete'
 * '<S96>'  : 'based_FOC/Subsystem/Iq/Integrator ICs/Internal IC'
 * '<S97>'  : 'based_FOC/Subsystem/Iq/N Copy/Disabled wSignal Specification'
 * '<S98>'  : 'based_FOC/Subsystem/Iq/N Gain/Disabled'
 * '<S99>'  : 'based_FOC/Subsystem/Iq/P Copy/Disabled'
 * '<S100>' : 'based_FOC/Subsystem/Iq/Parallel P Gain/Internal Parameters'
 * '<S101>' : 'based_FOC/Subsystem/Iq/Reset Signal/Disabled'
 * '<S102>' : 'based_FOC/Subsystem/Iq/Saturation/Enabled'
 * '<S103>' : 'based_FOC/Subsystem/Iq/Saturation Fdbk/Disabled'
 * '<S104>' : 'based_FOC/Subsystem/Iq/Sum/Sum_PI'
 * '<S105>' : 'based_FOC/Subsystem/Iq/Sum Fdbk/Disabled'
 * '<S106>' : 'based_FOC/Subsystem/Iq/Tracking Mode/Disabled'
 * '<S107>' : 'based_FOC/Subsystem/Iq/Tracking Mode Sum/Passthrough'
 * '<S108>' : 'based_FOC/Subsystem/Iq/Tsamp - Integral/TsSignalSpecification'
 * '<S109>' : 'based_FOC/Subsystem/Iq/Tsamp - Ngain/Passthrough'
 * '<S110>' : 'based_FOC/Subsystem/Iq/postSat Signal/Forward_Path'
 * '<S111>' : 'based_FOC/Subsystem/Iq/preInt Signal/Internal PreInt'
 * '<S112>' : 'based_FOC/Subsystem/Iq/preSat Signal/Forward_Path'
 * '<S113>' : 'based_FOC/Subsystem/Speed1/Anti-windup'
 * '<S114>' : 'based_FOC/Subsystem/Speed1/D Gain'
 * '<S115>' : 'based_FOC/Subsystem/Speed1/External Derivative'
 * '<S116>' : 'based_FOC/Subsystem/Speed1/Filter'
 * '<S117>' : 'based_FOC/Subsystem/Speed1/Filter ICs'
 * '<S118>' : 'based_FOC/Subsystem/Speed1/I Gain'
 * '<S119>' : 'based_FOC/Subsystem/Speed1/Ideal P Gain'
 * '<S120>' : 'based_FOC/Subsystem/Speed1/Ideal P Gain Fdbk'
 * '<S121>' : 'based_FOC/Subsystem/Speed1/Integrator'
 * '<S122>' : 'based_FOC/Subsystem/Speed1/Integrator ICs'
 * '<S123>' : 'based_FOC/Subsystem/Speed1/N Copy'
 * '<S124>' : 'based_FOC/Subsystem/Speed1/N Gain'
 * '<S125>' : 'based_FOC/Subsystem/Speed1/P Copy'
 * '<S126>' : 'based_FOC/Subsystem/Speed1/Parallel P Gain'
 * '<S127>' : 'based_FOC/Subsystem/Speed1/Reset Signal'
 * '<S128>' : 'based_FOC/Subsystem/Speed1/Saturation'
 * '<S129>' : 'based_FOC/Subsystem/Speed1/Saturation Fdbk'
 * '<S130>' : 'based_FOC/Subsystem/Speed1/Sum'
 * '<S131>' : 'based_FOC/Subsystem/Speed1/Sum Fdbk'
 * '<S132>' : 'based_FOC/Subsystem/Speed1/Tracking Mode'
 * '<S133>' : 'based_FOC/Subsystem/Speed1/Tracking Mode Sum'
 * '<S134>' : 'based_FOC/Subsystem/Speed1/Tsamp - Integral'
 * '<S135>' : 'based_FOC/Subsystem/Speed1/Tsamp - Ngain'
 * '<S136>' : 'based_FOC/Subsystem/Speed1/postSat Signal'
 * '<S137>' : 'based_FOC/Subsystem/Speed1/preInt Signal'
 * '<S138>' : 'based_FOC/Subsystem/Speed1/preSat Signal'
 * '<S139>' : 'based_FOC/Subsystem/Speed1/Anti-windup/Passthrough'
 * '<S140>' : 'based_FOC/Subsystem/Speed1/D Gain/Internal Parameters'
 * '<S141>' : 'based_FOC/Subsystem/Speed1/External Derivative/Error'
 * '<S142>' : 'based_FOC/Subsystem/Speed1/Filter/Differentiator'
 * '<S143>' : 'based_FOC/Subsystem/Speed1/Filter/Differentiator/Tsamp'
 * '<S144>' : 'based_FOC/Subsystem/Speed1/Filter/Differentiator/Tsamp/Internal Ts'
 * '<S145>' : 'based_FOC/Subsystem/Speed1/Filter ICs/Internal IC - Differentiator'
 * '<S146>' : 'based_FOC/Subsystem/Speed1/I Gain/Internal Parameters'
 * '<S147>' : 'based_FOC/Subsystem/Speed1/Ideal P Gain/Passthrough'
 * '<S148>' : 'based_FOC/Subsystem/Speed1/Ideal P Gain Fdbk/Disabled'
 * '<S149>' : 'based_FOC/Subsystem/Speed1/Integrator/Discrete'
 * '<S150>' : 'based_FOC/Subsystem/Speed1/Integrator ICs/Internal IC'
 * '<S151>' : 'based_FOC/Subsystem/Speed1/N Copy/Disabled wSignal Specification'
 * '<S152>' : 'based_FOC/Subsystem/Speed1/N Gain/Passthrough'
 * '<S153>' : 'based_FOC/Subsystem/Speed1/P Copy/Disabled'
 * '<S154>' : 'based_FOC/Subsystem/Speed1/Parallel P Gain/Internal Parameters'
 * '<S155>' : 'based_FOC/Subsystem/Speed1/Reset Signal/Disabled'
 * '<S156>' : 'based_FOC/Subsystem/Speed1/Saturation/Enabled'
 * '<S157>' : 'based_FOC/Subsystem/Speed1/Saturation Fdbk/Disabled'
 * '<S158>' : 'based_FOC/Subsystem/Speed1/Sum/Sum_PID'
 * '<S159>' : 'based_FOC/Subsystem/Speed1/Sum Fdbk/Disabled'
 * '<S160>' : 'based_FOC/Subsystem/Speed1/Tracking Mode/Disabled'
 * '<S161>' : 'based_FOC/Subsystem/Speed1/Tracking Mode Sum/Passthrough'
 * '<S162>' : 'based_FOC/Subsystem/Speed1/Tsamp - Integral/TsSignalSpecification'
 * '<S163>' : 'based_FOC/Subsystem/Speed1/Tsamp - Ngain/Passthrough'
 * '<S164>' : 'based_FOC/Subsystem/Speed1/postSat Signal/Forward_Path'
 * '<S165>' : 'based_FOC/Subsystem/Speed1/preInt Signal/Internal PreInt'
 * '<S166>' : 'based_FOC/Subsystem/Speed1/preSat Signal/Forward_Path'
 * '<S167>' : 'based_FOC/Subsystem/Subsystem1/Sector Calculator'
 * '<S168>' : 'based_FOC/Subsystem/Subsystem1/T1T2_Calculator1'
 * '<S169>' : 'based_FOC/Subsystem/Subsystem1/Tcm_Calculator2'
 * '<S170>' : 'based_FOC/Subsystem/Subsystem1/XYZ_Calculator'
 */
#endif                                 /* Subsystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
