/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flux_Observer.h
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

#ifndef Flux_Observer_h_
#define Flux_Observer_h_
#ifndef Flux_Observer_COMMON_INCLUDES_
#define Flux_Observer_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Flux_Observer_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define L                              0.002075F                 /* Referenced by:
                                                                  * '<S10>/Gain2'
                                                                  * '<S10>/Gain3'
                                                                  * '<S10>/Gain6'
                                                                  * '<S10>/Gain7'
                                                                  */
#define PLL_I                          5000.0                    /* Referenced by: '<S46>/Integral Gain' */
#define PLL_P                          1000.0                    /* Referenced by: '<S54>/Proportional Gain' */
#define Period                         8500.0                    /* Referenced by: '<S1>/Constant9' *//* SVPWM周期，中心堆成模式，定时器周期乘以二 */
#define Pn                             4.0                       /* Referenced by: '<S1>/Gain3' */
#define Rs                             0.62F                     /* Referenced by:
                                                                  * '<S10>/Gain'
                                                                  * '<S10>/Gain1'
                                                                  */
#define Ts                             5.0E-5F                   /* Referenced by:
                                                                  * '<S10>/Gain4'
                                                                  * '<S10>/Gain5'
                                                                  *//* PWM周期 */
#define Udc                            300.0                     /* Referenced by: '<S1>/Constant10' */
#define flux                           0.08627F                  /* Referenced by:
                                                                  * '<S10>/Constant'
                                                                  * '<S10>/Gain8'
                                                                  * '<S10>/Gain9'
                                                                  */
#define gamma                          100000.0F                 /* Referenced by: '<S10>/Constant1' */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T DigitalFilter_FILT_STATES[4]; /* '<S12>/Digital Filter' */
  real_T Delay1_DSTATE;                /* '<S1>/Delay1' */
  real_T Delay_DSTATE;                 /* '<S1>/Delay' */
  real_T Integrator_DSTATE;            /* '<S205>/Integrator' */
  real_T Integrator_DSTATE_a;          /* '<S153>/Integrator' */
  real_T Integrator_DSTATE_k;          /* '<S101>/Integrator' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S11>/Discrete-Time Integrator' */
  real_T Integrator_DSTATE_m;          /* '<S49>/Integrator' */
  real32_T Delay_DSTATE_k;             /* '<S10>/Delay' */
  real32_T Delay1_DSTATE_f;            /* '<S10>/Delay1' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T SpeedRef;                     /* '<Root>/SpeedRef' */
  real_T ias;                          /* '<Root>/ias' */
  real_T ibs;                          /* '<Root>/ibs' */
  real_T ics;                          /* '<Root>/ics' */
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
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T cos_theta;             /* '<S10>/Gain8' */
extern real32_T sin_theta;             /* '<S10>/Gain9' */

/* Model entry point functions */
extern void Flux_Observer_initialize(void);
extern void Flux_Observer_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S14>/Check Signal Attributes' : Unused code path elimination
 * Block '<S11>/Scope1' : Unused code path elimination
 * Block '<S4>/Scope6' : Unused code path elimination
 * Block '<S1>/Nr' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 * Block '<S1>/Scope4' : Unused code path elimination
 * Block '<S1>/Scope5' : Unused code path elimination
 * Block '<S9>/Scope1' : Unused code path elimination
 * Block '<S9>/Scope2' : Unused code path elimination
 * Block '<S9>/Scope3' : Unused code path elimination
 * Block '<S9>/Scope4' : Unused code path elimination
 * Block '<S1>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion5' : Eliminate redundant data type conversion
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
 * hilite_system('based_FOC/Flux_Observer')    - opens subsystem based_FOC/Flux_Observer
 * hilite_system('based_FOC/Flux_Observer/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'based_FOC'
 * '<S1>'   : 'based_FOC/Flux_Observer'
 * '<S2>'   : 'based_FOC/Flux_Observer/Anti_Park1'
 * '<S3>'   : 'based_FOC/Flux_Observer/Clark'
 * '<S4>'   : 'based_FOC/Flux_Observer/Flux_observer'
 * '<S5>'   : 'based_FOC/Flux_Observer/Id'
 * '<S6>'   : 'based_FOC/Flux_Observer/Iq'
 * '<S7>'   : 'based_FOC/Flux_Observer/Park'
 * '<S8>'   : 'based_FOC/Flux_Observer/Speed1'
 * '<S9>'   : 'based_FOC/Flux_Observer/Subsystem1'
 * '<S10>'  : 'based_FOC/Flux_Observer/Flux_observer/OBSERVER'
 * '<S11>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL'
 * '<S12>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/Digital Filter Design'
 * '<S13>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller'
 * '<S14>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/Digital Filter Design/Check Signal Attributes'
 * '<S15>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Anti-windup'
 * '<S16>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/D Gain'
 * '<S17>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/External Derivative'
 * '<S18>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter'
 * '<S19>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter ICs'
 * '<S20>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/I Gain'
 * '<S21>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain'
 * '<S22>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain Fdbk'
 * '<S23>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator'
 * '<S24>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator ICs'
 * '<S25>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Copy'
 * '<S26>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Gain'
 * '<S27>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/P Copy'
 * '<S28>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Parallel P Gain'
 * '<S29>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Reset Signal'
 * '<S30>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation'
 * '<S31>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation Fdbk'
 * '<S32>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum'
 * '<S33>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum Fdbk'
 * '<S34>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode'
 * '<S35>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode Sum'
 * '<S36>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Integral'
 * '<S37>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Ngain'
 * '<S38>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/postSat Signal'
 * '<S39>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preInt Signal'
 * '<S40>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preSat Signal'
 * '<S41>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Anti-windup/Passthrough'
 * '<S42>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/D Gain/Disabled'
 * '<S43>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/External Derivative/Disabled'
 * '<S44>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter/Disabled'
 * '<S45>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Filter ICs/Disabled'
 * '<S46>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/I Gain/Internal Parameters'
 * '<S47>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain/Passthrough'
 * '<S48>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S49>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator/Discrete'
 * '<S50>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Integrator ICs/Internal IC'
 * '<S51>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S52>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/N Gain/Disabled'
 * '<S53>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/P Copy/Disabled'
 * '<S54>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S55>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Reset Signal/Disabled'
 * '<S56>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation/Passthrough'
 * '<S57>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Saturation Fdbk/Disabled'
 * '<S58>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum/Sum_PI'
 * '<S59>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Sum Fdbk/Disabled'
 * '<S60>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode/Disabled'
 * '<S61>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S62>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S63>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S64>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/postSat Signal/Forward_Path'
 * '<S65>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preInt Signal/Internal PreInt'
 * '<S66>'  : 'based_FOC/Flux_Observer/Flux_observer/PLL/PID Controller/preSat Signal/Forward_Path'
 * '<S67>'  : 'based_FOC/Flux_Observer/Id/Anti-windup'
 * '<S68>'  : 'based_FOC/Flux_Observer/Id/D Gain'
 * '<S69>'  : 'based_FOC/Flux_Observer/Id/External Derivative'
 * '<S70>'  : 'based_FOC/Flux_Observer/Id/Filter'
 * '<S71>'  : 'based_FOC/Flux_Observer/Id/Filter ICs'
 * '<S72>'  : 'based_FOC/Flux_Observer/Id/I Gain'
 * '<S73>'  : 'based_FOC/Flux_Observer/Id/Ideal P Gain'
 * '<S74>'  : 'based_FOC/Flux_Observer/Id/Ideal P Gain Fdbk'
 * '<S75>'  : 'based_FOC/Flux_Observer/Id/Integrator'
 * '<S76>'  : 'based_FOC/Flux_Observer/Id/Integrator ICs'
 * '<S77>'  : 'based_FOC/Flux_Observer/Id/N Copy'
 * '<S78>'  : 'based_FOC/Flux_Observer/Id/N Gain'
 * '<S79>'  : 'based_FOC/Flux_Observer/Id/P Copy'
 * '<S80>'  : 'based_FOC/Flux_Observer/Id/Parallel P Gain'
 * '<S81>'  : 'based_FOC/Flux_Observer/Id/Reset Signal'
 * '<S82>'  : 'based_FOC/Flux_Observer/Id/Saturation'
 * '<S83>'  : 'based_FOC/Flux_Observer/Id/Saturation Fdbk'
 * '<S84>'  : 'based_FOC/Flux_Observer/Id/Sum'
 * '<S85>'  : 'based_FOC/Flux_Observer/Id/Sum Fdbk'
 * '<S86>'  : 'based_FOC/Flux_Observer/Id/Tracking Mode'
 * '<S87>'  : 'based_FOC/Flux_Observer/Id/Tracking Mode Sum'
 * '<S88>'  : 'based_FOC/Flux_Observer/Id/Tsamp - Integral'
 * '<S89>'  : 'based_FOC/Flux_Observer/Id/Tsamp - Ngain'
 * '<S90>'  : 'based_FOC/Flux_Observer/Id/postSat Signal'
 * '<S91>'  : 'based_FOC/Flux_Observer/Id/preInt Signal'
 * '<S92>'  : 'based_FOC/Flux_Observer/Id/preSat Signal'
 * '<S93>'  : 'based_FOC/Flux_Observer/Id/Anti-windup/Passthrough'
 * '<S94>'  : 'based_FOC/Flux_Observer/Id/D Gain/Disabled'
 * '<S95>'  : 'based_FOC/Flux_Observer/Id/External Derivative/Disabled'
 * '<S96>'  : 'based_FOC/Flux_Observer/Id/Filter/Disabled'
 * '<S97>'  : 'based_FOC/Flux_Observer/Id/Filter ICs/Disabled'
 * '<S98>'  : 'based_FOC/Flux_Observer/Id/I Gain/Internal Parameters'
 * '<S99>'  : 'based_FOC/Flux_Observer/Id/Ideal P Gain/Passthrough'
 * '<S100>' : 'based_FOC/Flux_Observer/Id/Ideal P Gain Fdbk/Disabled'
 * '<S101>' : 'based_FOC/Flux_Observer/Id/Integrator/Discrete'
 * '<S102>' : 'based_FOC/Flux_Observer/Id/Integrator ICs/Internal IC'
 * '<S103>' : 'based_FOC/Flux_Observer/Id/N Copy/Disabled wSignal Specification'
 * '<S104>' : 'based_FOC/Flux_Observer/Id/N Gain/Disabled'
 * '<S105>' : 'based_FOC/Flux_Observer/Id/P Copy/Disabled'
 * '<S106>' : 'based_FOC/Flux_Observer/Id/Parallel P Gain/Internal Parameters'
 * '<S107>' : 'based_FOC/Flux_Observer/Id/Reset Signal/Disabled'
 * '<S108>' : 'based_FOC/Flux_Observer/Id/Saturation/Enabled'
 * '<S109>' : 'based_FOC/Flux_Observer/Id/Saturation Fdbk/Disabled'
 * '<S110>' : 'based_FOC/Flux_Observer/Id/Sum/Sum_PI'
 * '<S111>' : 'based_FOC/Flux_Observer/Id/Sum Fdbk/Disabled'
 * '<S112>' : 'based_FOC/Flux_Observer/Id/Tracking Mode/Disabled'
 * '<S113>' : 'based_FOC/Flux_Observer/Id/Tracking Mode Sum/Passthrough'
 * '<S114>' : 'based_FOC/Flux_Observer/Id/Tsamp - Integral/TsSignalSpecification'
 * '<S115>' : 'based_FOC/Flux_Observer/Id/Tsamp - Ngain/Passthrough'
 * '<S116>' : 'based_FOC/Flux_Observer/Id/postSat Signal/Forward_Path'
 * '<S117>' : 'based_FOC/Flux_Observer/Id/preInt Signal/Internal PreInt'
 * '<S118>' : 'based_FOC/Flux_Observer/Id/preSat Signal/Forward_Path'
 * '<S119>' : 'based_FOC/Flux_Observer/Iq/Anti-windup'
 * '<S120>' : 'based_FOC/Flux_Observer/Iq/D Gain'
 * '<S121>' : 'based_FOC/Flux_Observer/Iq/External Derivative'
 * '<S122>' : 'based_FOC/Flux_Observer/Iq/Filter'
 * '<S123>' : 'based_FOC/Flux_Observer/Iq/Filter ICs'
 * '<S124>' : 'based_FOC/Flux_Observer/Iq/I Gain'
 * '<S125>' : 'based_FOC/Flux_Observer/Iq/Ideal P Gain'
 * '<S126>' : 'based_FOC/Flux_Observer/Iq/Ideal P Gain Fdbk'
 * '<S127>' : 'based_FOC/Flux_Observer/Iq/Integrator'
 * '<S128>' : 'based_FOC/Flux_Observer/Iq/Integrator ICs'
 * '<S129>' : 'based_FOC/Flux_Observer/Iq/N Copy'
 * '<S130>' : 'based_FOC/Flux_Observer/Iq/N Gain'
 * '<S131>' : 'based_FOC/Flux_Observer/Iq/P Copy'
 * '<S132>' : 'based_FOC/Flux_Observer/Iq/Parallel P Gain'
 * '<S133>' : 'based_FOC/Flux_Observer/Iq/Reset Signal'
 * '<S134>' : 'based_FOC/Flux_Observer/Iq/Saturation'
 * '<S135>' : 'based_FOC/Flux_Observer/Iq/Saturation Fdbk'
 * '<S136>' : 'based_FOC/Flux_Observer/Iq/Sum'
 * '<S137>' : 'based_FOC/Flux_Observer/Iq/Sum Fdbk'
 * '<S138>' : 'based_FOC/Flux_Observer/Iq/Tracking Mode'
 * '<S139>' : 'based_FOC/Flux_Observer/Iq/Tracking Mode Sum'
 * '<S140>' : 'based_FOC/Flux_Observer/Iq/Tsamp - Integral'
 * '<S141>' : 'based_FOC/Flux_Observer/Iq/Tsamp - Ngain'
 * '<S142>' : 'based_FOC/Flux_Observer/Iq/postSat Signal'
 * '<S143>' : 'based_FOC/Flux_Observer/Iq/preInt Signal'
 * '<S144>' : 'based_FOC/Flux_Observer/Iq/preSat Signal'
 * '<S145>' : 'based_FOC/Flux_Observer/Iq/Anti-windup/Passthrough'
 * '<S146>' : 'based_FOC/Flux_Observer/Iq/D Gain/Disabled'
 * '<S147>' : 'based_FOC/Flux_Observer/Iq/External Derivative/Disabled'
 * '<S148>' : 'based_FOC/Flux_Observer/Iq/Filter/Disabled'
 * '<S149>' : 'based_FOC/Flux_Observer/Iq/Filter ICs/Disabled'
 * '<S150>' : 'based_FOC/Flux_Observer/Iq/I Gain/Internal Parameters'
 * '<S151>' : 'based_FOC/Flux_Observer/Iq/Ideal P Gain/Passthrough'
 * '<S152>' : 'based_FOC/Flux_Observer/Iq/Ideal P Gain Fdbk/Disabled'
 * '<S153>' : 'based_FOC/Flux_Observer/Iq/Integrator/Discrete'
 * '<S154>' : 'based_FOC/Flux_Observer/Iq/Integrator ICs/Internal IC'
 * '<S155>' : 'based_FOC/Flux_Observer/Iq/N Copy/Disabled wSignal Specification'
 * '<S156>' : 'based_FOC/Flux_Observer/Iq/N Gain/Disabled'
 * '<S157>' : 'based_FOC/Flux_Observer/Iq/P Copy/Disabled'
 * '<S158>' : 'based_FOC/Flux_Observer/Iq/Parallel P Gain/Internal Parameters'
 * '<S159>' : 'based_FOC/Flux_Observer/Iq/Reset Signal/Disabled'
 * '<S160>' : 'based_FOC/Flux_Observer/Iq/Saturation/Enabled'
 * '<S161>' : 'based_FOC/Flux_Observer/Iq/Saturation Fdbk/Disabled'
 * '<S162>' : 'based_FOC/Flux_Observer/Iq/Sum/Sum_PI'
 * '<S163>' : 'based_FOC/Flux_Observer/Iq/Sum Fdbk/Disabled'
 * '<S164>' : 'based_FOC/Flux_Observer/Iq/Tracking Mode/Disabled'
 * '<S165>' : 'based_FOC/Flux_Observer/Iq/Tracking Mode Sum/Passthrough'
 * '<S166>' : 'based_FOC/Flux_Observer/Iq/Tsamp - Integral/TsSignalSpecification'
 * '<S167>' : 'based_FOC/Flux_Observer/Iq/Tsamp - Ngain/Passthrough'
 * '<S168>' : 'based_FOC/Flux_Observer/Iq/postSat Signal/Forward_Path'
 * '<S169>' : 'based_FOC/Flux_Observer/Iq/preInt Signal/Internal PreInt'
 * '<S170>' : 'based_FOC/Flux_Observer/Iq/preSat Signal/Forward_Path'
 * '<S171>' : 'based_FOC/Flux_Observer/Speed1/Anti-windup'
 * '<S172>' : 'based_FOC/Flux_Observer/Speed1/D Gain'
 * '<S173>' : 'based_FOC/Flux_Observer/Speed1/External Derivative'
 * '<S174>' : 'based_FOC/Flux_Observer/Speed1/Filter'
 * '<S175>' : 'based_FOC/Flux_Observer/Speed1/Filter ICs'
 * '<S176>' : 'based_FOC/Flux_Observer/Speed1/I Gain'
 * '<S177>' : 'based_FOC/Flux_Observer/Speed1/Ideal P Gain'
 * '<S178>' : 'based_FOC/Flux_Observer/Speed1/Ideal P Gain Fdbk'
 * '<S179>' : 'based_FOC/Flux_Observer/Speed1/Integrator'
 * '<S180>' : 'based_FOC/Flux_Observer/Speed1/Integrator ICs'
 * '<S181>' : 'based_FOC/Flux_Observer/Speed1/N Copy'
 * '<S182>' : 'based_FOC/Flux_Observer/Speed1/N Gain'
 * '<S183>' : 'based_FOC/Flux_Observer/Speed1/P Copy'
 * '<S184>' : 'based_FOC/Flux_Observer/Speed1/Parallel P Gain'
 * '<S185>' : 'based_FOC/Flux_Observer/Speed1/Reset Signal'
 * '<S186>' : 'based_FOC/Flux_Observer/Speed1/Saturation'
 * '<S187>' : 'based_FOC/Flux_Observer/Speed1/Saturation Fdbk'
 * '<S188>' : 'based_FOC/Flux_Observer/Speed1/Sum'
 * '<S189>' : 'based_FOC/Flux_Observer/Speed1/Sum Fdbk'
 * '<S190>' : 'based_FOC/Flux_Observer/Speed1/Tracking Mode'
 * '<S191>' : 'based_FOC/Flux_Observer/Speed1/Tracking Mode Sum'
 * '<S192>' : 'based_FOC/Flux_Observer/Speed1/Tsamp - Integral'
 * '<S193>' : 'based_FOC/Flux_Observer/Speed1/Tsamp - Ngain'
 * '<S194>' : 'based_FOC/Flux_Observer/Speed1/postSat Signal'
 * '<S195>' : 'based_FOC/Flux_Observer/Speed1/preInt Signal'
 * '<S196>' : 'based_FOC/Flux_Observer/Speed1/preSat Signal'
 * '<S197>' : 'based_FOC/Flux_Observer/Speed1/Anti-windup/Passthrough'
 * '<S198>' : 'based_FOC/Flux_Observer/Speed1/D Gain/Disabled'
 * '<S199>' : 'based_FOC/Flux_Observer/Speed1/External Derivative/Disabled'
 * '<S200>' : 'based_FOC/Flux_Observer/Speed1/Filter/Disabled'
 * '<S201>' : 'based_FOC/Flux_Observer/Speed1/Filter ICs/Disabled'
 * '<S202>' : 'based_FOC/Flux_Observer/Speed1/I Gain/Internal Parameters'
 * '<S203>' : 'based_FOC/Flux_Observer/Speed1/Ideal P Gain/Passthrough'
 * '<S204>' : 'based_FOC/Flux_Observer/Speed1/Ideal P Gain Fdbk/Disabled'
 * '<S205>' : 'based_FOC/Flux_Observer/Speed1/Integrator/Discrete'
 * '<S206>' : 'based_FOC/Flux_Observer/Speed1/Integrator ICs/Internal IC'
 * '<S207>' : 'based_FOC/Flux_Observer/Speed1/N Copy/Disabled wSignal Specification'
 * '<S208>' : 'based_FOC/Flux_Observer/Speed1/N Gain/Disabled'
 * '<S209>' : 'based_FOC/Flux_Observer/Speed1/P Copy/Disabled'
 * '<S210>' : 'based_FOC/Flux_Observer/Speed1/Parallel P Gain/Internal Parameters'
 * '<S211>' : 'based_FOC/Flux_Observer/Speed1/Reset Signal/Disabled'
 * '<S212>' : 'based_FOC/Flux_Observer/Speed1/Saturation/Enabled'
 * '<S213>' : 'based_FOC/Flux_Observer/Speed1/Saturation Fdbk/Disabled'
 * '<S214>' : 'based_FOC/Flux_Observer/Speed1/Sum/Sum_PI'
 * '<S215>' : 'based_FOC/Flux_Observer/Speed1/Sum Fdbk/Disabled'
 * '<S216>' : 'based_FOC/Flux_Observer/Speed1/Tracking Mode/Disabled'
 * '<S217>' : 'based_FOC/Flux_Observer/Speed1/Tracking Mode Sum/Passthrough'
 * '<S218>' : 'based_FOC/Flux_Observer/Speed1/Tsamp - Integral/TsSignalSpecification'
 * '<S219>' : 'based_FOC/Flux_Observer/Speed1/Tsamp - Ngain/Passthrough'
 * '<S220>' : 'based_FOC/Flux_Observer/Speed1/postSat Signal/Forward_Path'
 * '<S221>' : 'based_FOC/Flux_Observer/Speed1/preInt Signal/Internal PreInt'
 * '<S222>' : 'based_FOC/Flux_Observer/Speed1/preSat Signal/Forward_Path'
 * '<S223>' : 'based_FOC/Flux_Observer/Subsystem1/Sector Calculator'
 * '<S224>' : 'based_FOC/Flux_Observer/Subsystem1/T1T2_Calculator1'
 * '<S225>' : 'based_FOC/Flux_Observer/Subsystem1/Tcm_Calculator2'
 * '<S226>' : 'based_FOC/Flux_Observer/Subsystem1/XYZ_Calculator'
 */
#endif                                 /* Flux_Observer_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
