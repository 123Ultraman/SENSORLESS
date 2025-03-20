#ifndef based_FOC_h_
#define based_FOC_h_
#ifndef based_FOC_COMMON_INCLUDES_
#define based_FOC_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "based_FOC_types.h"
#include "rt_zcfcn.h"
#include "mwmathutil.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#include "zero_crossing_types.h"
#define MODEL_NAME based_FOC
#define NSAMPLE_TIMES (3) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (67) 
#define NUM_ZC_EVENTS (1) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T pveoae0rgk ; } mvoupavy5p ; typedef struct { real_T
lol2meeg5o ; real_T adakvlvgf4 ; int32_T kejdnwv5ef ; boolean_T epw5r2ybkp ;
boolean_T gkvboyiwt2 ; boolean_T ogzjxpnwsq ; } dqa3f0aosy ; typedef struct {
real_T bvmgpm2odd ; real_T i411d5wrsj ; real_T mxfho1lu3p ; real_T ddvi5ihagt
; real_T imi2lpdtr1 ; real_T jtbsnoer54 ; real_T h4vz5f5kaw ; real_T
bils2pe3o0 ; real_T o4d5sop3qe ; real_T ed2v4avx3x ; real_T ddnhwcdugb ;
real_T iybpytrzjw ; real_T bbct5xrocn ; real_T m22zcfn1ms ; real_T c3zvc1ql15
; real_T iydpuygsg3 ; real_T cng1w212ln ; real_T e2oy154v1u [ 9 ] ; real_T
ofmh5pmvcs [ 6 ] ; real_T adfbnhoe4d ; real_T kb4r4hmq10 ; real_T lac35nslzw
; real_T ckny4k4ajb ; real_T hlxa3tdq2m ; real_T bdgz0nrhdj ; real_T
nq0riy0nl0 ; real_T h5dgx5wmy1 ; real_T dvdx0svzcc ; real_T g1qadio5dk [ 6 ]
; real_T f4ynojnm2r ; real_T hgeuugh2cl ; real_T n0qw4xb12u ; real_T
ojdhbpltph ; real_T klllytdpmn ; real_T o3rovp4hg1 ; real_T eaaz53xwpc ;
real_T k4rsarzudt ; real_T brto0brqox ; real_T awrzvcwo5i ; real_T pyzaziws5o
; real_T kq5jwacnoy ; real_T i31yhmvgpf ; real_T oh3csxrczc ; real_T
ncz3ei0xyl ; real_T lezl4badfl ; real_T mmpoyjb255 ; real_T et115tvd5c ;
real_T icsedlrfmo ; real_T keu13zucmw ; real_T hlen4hvuex ; real_T maef41dty2
; real_T dvhqwvadlh [ 2 ] ; real_T fauyn5g1jz ; real_T edm5gwau3m ; real_T
d5igmkwwvg ; boolean_T g4x1kcgl20 ; mvoupavy5p kg410grc4m ; mvoupavy5p
jty1wsfjlj ; mvoupavy5p emmdqoheic ; } B ; typedef struct { real_T g2db00oyvj
; real_T lc2ze5kdtm ; real_T ki15zaj1gp ; real_T gymfqxh2cd ; real_T
dt2ijnggmb ; real_T byvsnyv5zr ; real_T cz435ihcu3 ; real_T ceat33yomo ;
real_T np4v4eaezh ; real_T nhi0bwiqwe ; real_T jpmcmrdt3a ; real_T ocgieankjr
; real_T j4bzixxmjs ; real_T ma3yw4utkh ; real_T mfjr5e14xs ; real_T
jnortiucxw ; real_T ocj52bygmn ; real_T pjxx0pj5ct ; struct { void * AS ;
void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL ; void *
TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } gbqvg1m3jx ; struct { void *
LoggedData ; } dattaamiez ; struct { void * LoggedData [ 4 ] ; } e1hczf4cdw ;
struct { void * AQHandles [ 3 ] ; } kczid045yc ; struct { void * AQHandles ;
} bud5p4ylzh ; struct { void * LoggedData [ 3 ] ; } c2q5edz2l4 ; struct {
void * LoggedData ; } kl40m4aiu1 ; struct { void * LoggedData ; } hbttiet0jp
; struct { void * LoggedData ; } dpspcviro2 ; struct { void * LoggedData ; }
cbcqpgn2wv ; struct { void * LoggedData [ 2 ] ; } mrkhfmmtjl ; struct { void
* AQHandles ; } o3vmxbgb5q ; struct { void * AQHandles ; } iy52gcogzn ;
struct { void * LoggedData [ 2 ] ; } absz4cicrc ; struct { void * LoggedData
[ 2 ] ; } ozhzy31iuu ; struct { void * LoggedData ; } kcoagubkix ; struct {
void * LoggedData [ 2 ] ; } meknrp2ozl ; struct { void * LoggedData [ 2 ] ; }
ind2n2fwfq ; struct { void * LoggedData [ 2 ] ; } aw4hejyc1j ; struct { void
* LoggedData [ 2 ] ; } hg3xctwmjf ; struct { void * LoggedData [ 2 ] ; }
kqu3zaaghu ; struct { void * LoggedData [ 2 ] ; } dhj4j2gsii ; struct { void
* LoggedData [ 2 ] ; } ef1bsau5gf ; struct { void * LoggedData [ 3 ] ; }
g4pjr2qd2l ; struct { void * AQHandles ; } f21icutcu2 ; struct { void *
AQHandles ; } an4rwyup45 ; struct { void * AQHandles ; } nigjqkrdgh ; struct
{ void * AQHandles ; } pqr5ti5djs ; struct { void * LoggedData [ 2 ] ; }
lrm1xxluc3 ; struct { void * LoggedData [ 2 ] ; } depn2qjdxo ; struct { void
* LoggedData [ 2 ] ; } cgbb10j21u ; struct { void * AQHandles ; } ink55qldzx
; struct { void * AQHandles ; } bhkkrlprsc ; struct { void * AQHandles ; }
kxwhg3dymm ; struct { void * AQHandles ; } gyf1oq3zs3 ; struct { void *
AQHandles ; } ipoiwfl4sg ; struct { void * AQHandles ; } kanxmkuey4 ; struct
{ void * LoggedData [ 2 ] ; } ezwmkd5spv ; struct { void * LoggedData [ 2 ] ;
} g31trfxw3l ; int32_T bwi4ak5yob ; int32_T bl3wth4gb4 ; int32_T d4deydkd2e ;
int32_T dy3zgavjvw ; int32_T hxmang4whi ; int32_T gmsb5tf0og ; int32_T
d0lzng0qrp ; uint32_T cv41it4amb [ 2 ] ; uint32_T pwmwjft1gn [ 2 ] ; int_T
fy0bl2dcyx [ 11 ] ; int8_T nnw34mmyux ; int8_T fih3gfro2h ; uint8_T
psfjb0nsls ; uint8_T pvevgoy3y3 ; uint8_T lni3dmfvjj ; uint8_T ifed2xuv2w ;
uint8_T nr4jtirdwo ; uint8_T ocwaun5q5s ; uint8_T mkoxzdqwi2 ; uint8_T
akjewdlwej ; boolean_T cuak05qrvl ; boolean_T ocbrfohdqu ; boolean_T
g5jwl0rrph ; boolean_T ftys1qypo0 ; boolean_T jl5a3sor32 ; boolean_T
k4luewptuo ; boolean_T obc0rz1ip3 ; boolean_T nghwbebn4m ; boolean_T
cflpbnskfq ; boolean_T h3rmilnlg1 ; boolean_T dntfct2nvq ; boolean_T
gkeivfk3do ; boolean_T dbxi1k3jk4 ; dqa3f0aosy kg410grc4m ; dqa3f0aosy
jty1wsfjlj ; dqa3f0aosy emmdqoheic ; } DW ; typedef struct { ZCSigState
orqtvo2unp ; } PrevZCX ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
DataMapInfo ; struct P_ { real_T F1 [ 5000 ] ; real_T U_ref [ 5000 ] ; real_T
_Ld2f2Based_FOC_Data_sldd_ ; real_T _Lq2f2Based_FOC_Data_sldd_ ; real_T
_PLL_P2f2Based_FOC_Data_sldd_ ; real_T _Period2f2Based_FOC_Data_sldd_ ;
real_T _Pn2f2Based_FOC_Data_sldd_ ; real_T _Rs2f2Based_FOC_Data_sldd_ ;
real_T _Ts2f2Based_FOC_Data_sldd_ ; real_T _Udc2f2Based_FOC_Data_sldd_ ;
real_T _flux2f2Based_FOC_Data_sldd_ ; real32_T _gamma2f2Based_FOC_Data_sldd_
; real_T DCVoltageSource1_Amplitude ; real_T
LowPassFilterDiscreteorContinuous_K ; real_T Subsystem3_Kd ; real_T
Subsystem_Kd ; real_T Subsystem2_Kd ; real_T Subsystem3_Kd_nwkkd3n4ya ;
real_T Subsystem3_Ki ; real_T Subsystem_Ki ; real_T Subsystem2_Ki ; real_T
Subsystem3_Ki_kehsee5auu ; real_T Subsystem_Kp ; real_T Subsystem2_Kp ;
real_T Subsystem3_Kp ; real_T LowPassFilterDiscreteorContinuous_T ; real_T
Subsystem3_Ts ; real_T Subsystem_Ts ; real_T Subsystem2_Ts ; real_T
Subsystem3_Ts_gafktesne5 ; real_T CompareToConstant_const ; real_T
CompareToConstant_const_fh44bbmvpu ; real_T CoulombViscousFriction_gain ;
real_T LowPassFilterDiscreteorContinuous_init_option ; real_T
Subsystem3_max_Integral ; real_T Subsystem_max_Integral ; real_T
Subsystem2_max_Integral ; real_T Subsystem3_max_Integral_pc1i5p255z ; real_T
Subsystem3_max_output ; real_T Subsystem_max_output ; real_T
Subsystem2_max_output ; real_T Subsystem3_max_output_fnwgdzd14e ; real_T
Subsystem3_min_Integral ; real_T Subsystem_min_Integral ; real_T
Subsystem2_min_Integral ; real_T Subsystem3_min_Integral_bhno53osaw ; real_T
Subsystem3_min_output ; real_T Subsystem_min_output ; real_T
Subsystem2_min_output ; real_T Subsystem3_min_output_k03ehr1wvd ; real_T
CoulombViscousFriction_offset ; real_T RepeatingSequence1_rep_seq_y [ 3 ] ;
real_T Constant_Value ; real_T Delay_InitialCondition ; real_T
Delay1_InitialCondition ; real_T DiscreteTimeIntegrator_gainval ; real_T
DiscreteTimeIntegrator_IC ; real_T Integrator_gainval ; real_T
Integrator_UpperSat ; real_T Integrator_LowerSat ; real_T Saturation_UpperSat
; real_T Saturation_LowerSat ; real_T Constant3_Value ; real_T Tcm1_Y0 ;
real_T Tcm2_Y0 ; real_T Tcm3_Y0 ; real_T Delay1_InitialCondition_d0okqqbyaz ;
real_T Delay_InitialCondition_b1lbjxwxpj ; real_T Gain1_Gain ; real_T
Constant_Value_eugrpqijcm ; real_T Id_ref_Value ; real_T Gain_Gain ; real_T
Gain_Gain_mk3bjbwrde ; real_T Gain_Gain_oivnklv25u ; real_T
Gain_Gain_cnjrb05lj0 ; real_T Gain_Gain_g1t15nmsmn ; real_T
Gain_Gain_bzsgmuimqy ; real_T DiscreteTimeIntegrator1_gainval ; real_T
DiscreteTimeIntegrator1_IC ; real_T DiscreteTimeIntegrator_gainval_paiswrmeqy
; real_T DiscreteTimeIntegrator_IC_mu4lei3aeq ; real_T
DiscreteTimeIntegrator_gainval_l5nc5jul3w ; real_T
DiscreteTimeIntegrator_IC_jlygup22ed ; real_T
DiscreteTimeIntegrator_gainval_ezgr3u4l02 ; real_T
DiscreteTimeIntegrator_IC_nkd2pr4ny4 ; real_T PulseGenerator_Amp ; real_T
PulseGenerator_Period ; real_T PulseGenerator_Duty ; real_T
PulseGenerator_PhaseDelay ; real_T LookUpTable1_bp01Data [ 3 ] ; real_T
Relay_OnVal ; real_T Relay_OffVal ; real_T Relay_YOn ; real_T Relay_YOff ;
real_T Relay1_OnVal ; real_T Relay1_OffVal ; real_T Relay1_YOn ; real_T
Relay1_YOff ; real_T Relay2_OnVal ; real_T Relay2_OffVal ; real_T Relay2_YOn
; real_T Relay2_YOff ; real_T Saturation_UpperSat_lvhbmvqtsm ; real_T
Saturation_LowerSat_mxekufxfq4 ; real_T UnitDelay5_InitialCondition ; real_T
Gain4_Gain ; real_T UnitDelay6_InitialCondition ; real_T
UnitDelay1_InitialCondition ; real_T StateSpace_DS_param [ 198 ] ; real_T
Switch_Threshold ; real_T Saturation_UpperSat_fsy5ziaufk ; real_T
Saturation_LowerSat_lcctrgol0c ; real_T Switch_Threshold_ejumnfp2iv ; real_T
Saturation_UpperSat_gahcyazdwu ; real_T Saturation_LowerSat_omyxtylrr2 ;
real_T Switch_Threshold_ckrsclarb5 ; real_T Saturation_UpperSat_dzgt10esff ;
real_T Saturation_LowerSat_fh1umgpwfe ; real_T Switch_Threshold_bxqw2aoic5 ;
real_T Saturation_UpperSat_maem4qlhjb ; real_T Saturation_LowerSat_bi44mm4520
; real_T Switch_Threshold_onyd2dtacm ; real_T Saturation_UpperSat_lfg1vg5xfs
; real_T Saturation_LowerSat_oaquejrj11 ; real_T Switch_Threshold_jaxwwid1sf
; real_T Saturation_UpperSat_ciqrhxjwb1 ; real_T
Saturation_LowerSat_l5rgpp0wbq ; real_T donotdeletethisgain_Gain ; real_T
uLd_Gain ; real_T Gain_Gain_anscm3fjqp ; real_T LqLd_Gain ; real_T RLd_Gain ;
real_T uLq_Gain ; real_T LdLq_Gain ; real_T RLq_Gain ; real_T lamLq_Gain ;
real_T Gain2_Gain ; real_T SwitchCurrents_Value [ 6 ] ; real_T u1_Value ;
real_T eee_Value ; real_T u1_Value_nreyg4opoj ; real_T eee_Value_ewdqtje3b0 ;
real_T u1_Value_ls0m5pykfy ; real_T eee_Value_h1qjq4lqkf ; real_T
u1_Value_jwxgunvume ; real_T eee_Value_bupr5ec5gd ; real_T
u1_Value_l2dpiazvzy ; real_T eee_Value_g1uo4tygcq ; real_T
u1_Value_gm2dshzm4f ; real_T eee_Value_jnqgmu1ji4 ; real_T Constant1_Value ;
real_T Constant8_Value ; real_T Constant_Value_geepaef2cb ; real_T
Constant1_Value_p1uxhfeofi ; uint8_T ManualSwitch1_CurrentSetting ; uint8_T
ManualSwitch_CurrentSetting ; } ; extern const char_T *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern DW rtDW ; extern PrevZCX
rtPrevZCX ; extern P rtP ; extern mxArray * mr_based_FOC_GetDWork ( ) ;
extern void mr_based_FOC_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_based_FOC_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * based_FOC_GetCAPIStaticMap ( void ) ; extern
SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ; extern
rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid )
; void MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T
tid ) ; void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
