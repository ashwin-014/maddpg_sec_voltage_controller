/*
 * Copy_of_test_v_control_and_i_control_with_droop_copy.h
 *
 * Code generation for model "Copy_of_test_v_control_and_i_control_with_droop_copy".
 *
 * Model version              : 1.181
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C source code generated on : Sun Sep  9 21:28:53 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objective: Execution efficiency
 * Validation result: Passed (6), Warnings (6), Error (0)
 */

#ifndef RTW_HEADER_Copy_of_test_v_control_and_i_control_with_droop_copy_h_
#define RTW_HEADER_Copy_of_test_v_control_and_i_control_with_droop_copy_h_
#include <math.h>
#include <stddef.h>
#include <float.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef Copy_of_test_v_control_and_i_control_with_droop_copy_COMMON_INCLUDES_
# define Copy_of_test_v_control_and_i_control_with_droop_copy_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* Copy_of_test_v_control_and_i_control_with_droop_copy_COMMON_INCLUDES_ */

#include "Copy_of_test_v_control_and_i_control_with_droop_copy_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_assert.h"
#include "rt_look.h"
#include "rt_look1d.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#define Copy_of_test_v_control_and_i_control_with_droop_copy_M_TYPE RT_MODEL_Copy_of_test_v_contr_T

/* Block signals (auto storage) */
typedef struct {
  real_T StateSpace_o1[25];            /* '<S91>/State-Space' */
  real_T StateSpace_o2[10];            /* '<S91>/State-Space' */
  real_T FromWorkspace;                /* '<Root>/From Workspace' */
  real_T FromWorkspace1;               /* '<Root>/From Workspace1' */
  real_T FromWorkspace2;               /* '<Root>/From Workspace2' */
  real_T TransferFcn2;                 /* '<S8>/Transfer Fcn2' */
  real_T Sum;                          /* '<S8>/Sum' */
  real_T Gain;                         /* '<S8>/Gain' */
  real_T TransferFcn1;                 /* '<S8>/Transfer Fcn1' */
  real_T Divide;                       /* '<S8>/Divide' */
  real_T TransferFcn2_i;               /* '<S12>/Transfer Fcn2' */
  real_T Sum_c;                        /* '<S12>/Sum' */
  real_T Gain_j;                       /* '<S12>/Gain' */
  real_T Divide_b;                     /* '<S12>/Divide' */
  real_T TransferFcn2_o;               /* '<S13>/Transfer Fcn2' */
  real_T Sum_p;                        /* '<S13>/Sum' */
  real_T Gain_h;                       /* '<S13>/Gain' */
  real_T Divide_l;                     /* '<S13>/Divide' */
  real_T DataTypeConversion;           /* '<S53>/Data Type Conversion' */
  real_T DataTypeConversion_p;         /* '<S71>/Data Type Conversion' */
  real_T startTime;                    /* '<S60>/startTime' */
  real_T DataTypeConversion_a;         /* '<S89>/Data Type Conversion' */
  real_T startTime_p;                  /* '<S78>/startTime' */
  real_T LookUpTable;                  /* '<S22>/Look-Up Table' */
  real_T Derivative;                   /* '<S22>/Derivative' */
  boolean_T Memory;                    /* '<S29>/Memory' */
  boolean_T Logic[2];                  /* '<S29>/Logic' */
  boolean_T Memory_n;                  /* '<S31>/Memory' */
  boolean_T Logic_p[2];                /* '<S31>/Logic' */
  boolean_T Memory_i;                  /* '<S33>/Memory' */
  boolean_T Logic_c[2];                /* '<S33>/Logic' */
  boolean_T RelationalOperator;        /* '<Root>/Relational Operator' */
} B_Copy_of_test_v_control_and__T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[7];         /* '<S91>/State-Space' */
  real_T TimeStampA;                   /* '<S22>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S22>/Derivative' */
  real_T TimeStampB;                   /* '<S22>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S22>/Derivative' */
  struct {
    void *AS;
    void *BS;
    void *CS;
    void *DS;
    void *DX_COL;
    void *BD_COL;
    void *TMP1;
    void *TMP2;
    void *XTMP;
    void *SWITCH_STATUS;
    void *SWITCH_STATUS_INIT;
    void *SW_CHG;
    void *G_STATE;
    void *USWLAST;
    void *XKM12;
    void *XKP12;
    void *XLAST;
    void *ULAST;
    void *IDX_SW_CHG;
    void *Y_SWITCH;
    void *SWITCH_TYPES;
    void *IDX_OUT_SW;
    void *SWITCH_TOPO_SAVED_IDX;
    void *SWITCH_MAP;
  } StateSpace_PWORK;                  /* '<S91>/State-Space' */

  struct {
    void *LoggedData;
  } I_out_0_PWORK;                     /* '<Root>/I_out_0' */

  struct {
    void *LoggedData;
  } I_out_1_PWORK;                     /* '<Root>/I_out_1' */

  struct {
    void *LoggedData;
  } I_out_2_PWORK;                     /* '<Root>/I_out_2' */

  struct {
    void *LoggedData;
  } Iin1_PWORK;                        /* '<Root>/Iin 1' */

  struct {
    void *LoggedData;
  } Iin2_PWORK;                        /* '<Root>/Iin 2' */

  struct {
    void *LoggedData;
  } Iin3_PWORK;                        /* '<Root>/Iin 3' */

  struct {
    void *LoggedData;
  } Pin_combined_PWORK;                /* '<Root>/Pin_combined' */

  struct {
    void *LoggedData;
  } Pout_combined1_PWORK;              /* '<Root>/Pout_combined1' */

  struct {
    void *LoggedData;
  } V_out_0_PWORK;                     /* '<Root>/V_out_0' */

  struct {
    void *LoggedData;
  } V_out_1_PWORK;                     /* '<Root>/V_out_1' */

  struct {
    void *LoggedData;
  } V_out_2_PWORK;                     /* '<Root>/V_out_2' */

  struct {
    void *LoggedData;
  } Vin1_PWORK;                        /* '<Root>/Vin 1' */

  struct {
    void *LoggedData;
  } Vin2_PWORK;                        /* '<Root>/Vin 2' */

  struct {
    void *LoggedData;
  } Vin3_PWORK;                        /* '<Root>/Vin 3' */

  struct {
    void *LoggedData;
  } final1_PWORK;                      /* '<Root>/final1' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace_PWORK;               /* '<Root>/From Workspace' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace1_PWORK;              /* '<Root>/From Workspace1' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace2_PWORK;              /* '<Root>/From Workspace2' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S8>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S8>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<S8>/Scope3' */

  struct {
    void *LoggedData;
  } Scope4_PWORK;                      /* '<S8>/Scope4' */

  struct {
    void *LoggedData;
  } Scope5_PWORK;                      /* '<S8>/Scope5' */

  struct {
    void *LoggedData;
  } Scope6_PWORK;                      /* '<S8>/Scope6' */

  struct {
    void *LoggedData;
  } Scope1_PWORK_e;                    /* '<S10>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_k;                    /* '<S10>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK_p;                    /* '<S10>/Scope3' */

  struct {
    void *LoggedData;
  } Scope1_PWORK_c;                    /* '<S12>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_b;                    /* '<S12>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK_g;                    /* '<S12>/Scope3' */

  struct {
    void *LoggedData;
  } Scope4_PWORK_m;                    /* '<S12>/Scope4' */

  struct {
    void *LoggedData;
  } Scope5_PWORK_e;                    /* '<S12>/Scope5' */

  struct {
    void *LoggedData;
  } Scope1_PWORK_p;                    /* '<S13>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_n;                    /* '<S13>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK_m;                    /* '<S13>/Scope3' */

  struct {
    void *LoggedData;
  } Scope4_PWORK_c;                    /* '<S13>/Scope4' */

  struct {
    void *LoggedData;
  } Scope5_PWORK_k;                    /* '<S13>/Scope5' */

  struct {
    void *LoggedData[2];
  } Scope1_PWORK_m;                    /* '<S17>/Scope1' */

  struct {
    void *LoggedData[2];
  } Scope2_PWORK_c;                    /* '<S17>/Scope2' */

  struct {
    void *LoggedData[2];
  } Scope1_PWORK_h;                    /* '<S18>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_o;                    /* '<S18>/Scope2' */

  struct {
    void *LoggedData[2];
  } Scope1_PWORK_p3;                   /* '<S19>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK_g;                    /* '<S19>/Scope2' */

  void* Assertion_slioAccessor;        /* '<Root>/Assertion' */
  int_T StateSpace_IWORK[11];          /* '<S91>/State-Space' */
  struct {
    int_T PrevIndex;
  } FromWorkspace_IWORK;               /* '<Root>/From Workspace' */

  struct {
    int_T PrevIndex;
  } FromWorkspace1_IWORK;              /* '<Root>/From Workspace1' */

  struct {
    int_T PrevIndex;
  } FromWorkspace2_IWORK;              /* '<Root>/From Workspace2' */

  boolean_T Memory_PreviousInput;      /* '<S29>/Memory' */
  boolean_T Memory_PreviousInput_a;    /* '<S31>/Memory' */
  boolean_T Memory_PreviousInput_f;    /* '<S33>/Memory' */
} DW_Copy_of_test_v_control_and_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn2_CSTATE;          /* '<S8>/Transfer Fcn2' */
  real_T TransferFcn1_CSTATE;          /* '<S8>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE;           /* '<S8>/Transfer Fcn' */
  real_T TransferFcn2_CSTATE_p;        /* '<S12>/Transfer Fcn2' */
  real_T TransferFcn1_CSTATE_a;        /* '<S12>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE_f;        /* '<S13>/Transfer Fcn2' */
  real_T TransferFcn1_CSTATE_d;        /* '<S13>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE_a;         /* '<S12>/Transfer Fcn' */
  real_T TransferFcn_CSTATE_o;         /* '<S13>/Transfer Fcn' */
} X_Copy_of_test_v_control_and__T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn2_CSTATE;          /* '<S8>/Transfer Fcn2' */
  real_T TransferFcn1_CSTATE;          /* '<S8>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE;           /* '<S8>/Transfer Fcn' */
  real_T TransferFcn2_CSTATE_p;        /* '<S12>/Transfer Fcn2' */
  real_T TransferFcn1_CSTATE_a;        /* '<S12>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE_f;        /* '<S13>/Transfer Fcn2' */
  real_T TransferFcn1_CSTATE_d;        /* '<S13>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE_a;         /* '<S12>/Transfer Fcn' */
  real_T TransferFcn_CSTATE_o;         /* '<S13>/Transfer Fcn' */
} XDot_Copy_of_test_v_control_a_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn2_CSTATE;       /* '<S8>/Transfer Fcn2' */
  boolean_T TransferFcn1_CSTATE;       /* '<S8>/Transfer Fcn1' */
  boolean_T TransferFcn_CSTATE;        /* '<S8>/Transfer Fcn' */
  boolean_T TransferFcn2_CSTATE_p;     /* '<S12>/Transfer Fcn2' */
  boolean_T TransferFcn1_CSTATE_a;     /* '<S12>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE_f;     /* '<S13>/Transfer Fcn2' */
  boolean_T TransferFcn1_CSTATE_d;     /* '<S13>/Transfer Fcn1' */
  boolean_T TransferFcn_CSTATE_a;      /* '<S12>/Transfer Fcn' */
  boolean_T TransferFcn_CSTATE_o;      /* '<S13>/Transfer Fcn' */
} XDis_Copy_of_test_v_control_a_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const real_T Sum;                    /* '<S18>/Sum' */
  const real_T Sum_k;                  /* '<S19>/Sum' */
} ConstB_Copy_of_test_v_control_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: zeros(10,1)
   * Referenced by: '<S93>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[10];

  /* Expression: S.A
   * Referenced by: '<S91>/State-Space'
   */
  real_T StateSpace_AS_param[49];

  /* Expression: S.B
   * Referenced by: '<S91>/State-Space'
   */
  real_T StateSpace_BS_param[112];

  /* Expression: S.C
   * Referenced by: '<S91>/State-Space'
   */
  real_T StateSpace_CS_param[175];

  /* Expression: S.D
   * Referenced by: '<S91>/State-Space'
   */
  real_T StateSpace_DS_param[400];

  /* Expression: S.x0
   * Referenced by: '<S91>/State-Space'
   */
  real_T StateSpace_X0_param[7];

  /* Expression: tv
   * Referenced by: '<S22>/Look-Up Table'
   */
  real_T LookUpTable_XData[5];

  /* Expression: opv
   * Referenced by: '<S22>/Look-Up Table'
   */
  real_T LookUpTable_YData[5];

  /* Pooled Parameter (Expression: [0 1;1 0;0 1;0 1;1 0;1 0;0 0;0 0])
   * Referenced by:
   *   '<S29>/Logic'
   *   '<S31>/Logic'
   *   '<S33>/Logic'
   */
  boolean_T pooled16[16];
} ConstP_Copy_of_test_v_control_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T v_out0;                       /* '<Root>/v_out0' */
  real_T i_out0;                       /* '<Root>/i_out0' */
  real_T v_out1;                       /* '<Root>/v_out1' */
  real_T i_out1;                       /* '<Root>/i_out1' */
  real_T v_out2;                       /* '<Root>/v_out2' */
  real_T i_out2;                       /* '<Root>/i_out2' */
} ExtY_Copy_of_test_v_control_a_T;

/* Real-time Model Data Structure */
struct tag_RTM_Copy_of_test_v_contro_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo *solverInfo;
  B_Copy_of_test_v_control_and__T *blockIO;
  X_Copy_of_test_v_control_and__T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  ExtY_Copy_of_test_v_control_a_T *outputs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[9];
  real_T odeF[3][9];
  ODE3_IntgData intgData;
  DW_Copy_of_test_v_control_and_T *dwork;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[44];
    int32_T* vardimsAddress[44];
  } DataMapInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern const ConstB_Copy_of_test_v_control_T Copy_of_test_v_control_a_ConstB;/* constant block i/o */

/* Constant parameters (auto storage) */
extern const ConstP_Copy_of_test_v_control_T Copy_of_test_v_control_a_ConstP;

/* Model entry point functions */
extern RT_MODEL_Copy_of_test_v_contr_T
  *Copy_of_test_v_control_and_i_control_with_droop_copy(void);
extern void Copy_of_test_v_control_and_i_control_with_droop_copy_initialize
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M);
extern void Copy_of_test_v_control_and_i_control_with_droop_copy_step
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M);
extern void Copy_of_test_v_control_and_i_control_with_droop_copy_terminate
  (RT_MODEL_Copy_of_test_v_contr_T * Copy_of_test_v_control_and_i_M);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  Copy_of_test_v_control_and_i_control_with_droop_copy_GetCAPIStaticMap(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S8>/Saturation1' : Unused code path elimination
 * Block '<S10>/Constant1' : Unused code path elimination
 * Block '<S12>/Saturation1' : Unused code path elimination
 * Block '<S13>/Saturation1' : Unused code path elimination
 * Block '<S46>/0 1' : Unused code path elimination
 * Block '<S46>/Gain' : Unused code path elimination
 * Block '<S46>/Saturation' : Unused code path elimination
 * Block '<S46>/Sum' : Unused code path elimination
 * Block '<S46>/Switch' : Unused code path elimination
 * Block '<S42>/Add' : Unused code path elimination
 * Block '<S51>/0 1' : Unused code path elimination
 * Block '<S51>/Gain' : Unused code path elimination
 * Block '<S51>/Saturation' : Unused code path elimination
 * Block '<S51>/Sum' : Unused code path elimination
 * Block '<S51>/Switch' : Unused code path elimination
 * Block '<S51>/eee' : Unused code path elimination
 * Block '<S53>/0 1' : Unused code path elimination
 * Block '<S53>/1//Rsw' : Unused code path elimination
 * Block '<S53>/Switch' : Unused code path elimination
 * Block '<S64>/0 1' : Unused code path elimination
 * Block '<S64>/Gain' : Unused code path elimination
 * Block '<S64>/Saturation' : Unused code path elimination
 * Block '<S64>/Sum' : Unused code path elimination
 * Block '<S64>/Switch' : Unused code path elimination
 * Block '<S59>/Add' : Unused code path elimination
 * Block '<S69>/0 1' : Unused code path elimination
 * Block '<S69>/Gain' : Unused code path elimination
 * Block '<S69>/Saturation' : Unused code path elimination
 * Block '<S69>/Sum' : Unused code path elimination
 * Block '<S69>/Switch' : Unused code path elimination
 * Block '<S69>/eee' : Unused code path elimination
 * Block '<S71>/0 1' : Unused code path elimination
 * Block '<S71>/1//Rsw' : Unused code path elimination
 * Block '<S71>/Switch' : Unused code path elimination
 * Block '<S18>/Relational Operator' : Unused code path elimination
 * Block '<S60>/Clock' : Unused code path elimination
 * Block '<S60>/Constant' : Unused code path elimination
 * Block '<S60>/Look-Up Table1' : Unused code path elimination
 * Block '<S60>/Math Function' : Unused code path elimination
 * Block '<S60>/Output' : Unused code path elimination
 * Block '<S60>/Sum' : Unused code path elimination
 * Block '<S82>/0 1' : Unused code path elimination
 * Block '<S82>/Gain' : Unused code path elimination
 * Block '<S82>/Saturation' : Unused code path elimination
 * Block '<S82>/Sum' : Unused code path elimination
 * Block '<S82>/Switch' : Unused code path elimination
 * Block '<S77>/Add' : Unused code path elimination
 * Block '<S87>/0 1' : Unused code path elimination
 * Block '<S87>/Gain' : Unused code path elimination
 * Block '<S87>/Saturation' : Unused code path elimination
 * Block '<S87>/Sum' : Unused code path elimination
 * Block '<S87>/Switch' : Unused code path elimination
 * Block '<S87>/eee' : Unused code path elimination
 * Block '<S89>/0 1' : Unused code path elimination
 * Block '<S89>/1//Rsw' : Unused code path elimination
 * Block '<S89>/Switch' : Unused code path elimination
 * Block '<S19>/Relational Operator' : Unused code path elimination
 * Block '<S78>/Clock' : Unused code path elimination
 * Block '<S78>/Constant' : Unused code path elimination
 * Block '<S78>/Look-Up Table1' : Unused code path elimination
 * Block '<S78>/Math Function' : Unused code path elimination
 * Block '<S78>/Output' : Unused code path elimination
 * Block '<S78>/Sum' : Unused code path elimination
 * Block '<S21>/Data Type  Conversion' : Eliminate redundant data type conversion
 * Block '<S21>/Switch3' : Eliminated due to constant selection input
 * Block '<S2>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S3>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S4>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<Root>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<Root>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<Root>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S9>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S10>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S10>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S11>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S11>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S14>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S15>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S16>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S38>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S39>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S40>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S55>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S56>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S57>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S73>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S74>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S75>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S21>/C4' : Unused code path elimination
 * Block '<S1>/c' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Copy_of_test_v_control_and_i_control_with_droop_copy'
 * '<S1>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Breaker'
 * '<S2>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Current Measurement'
 * '<S3>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Current Measurement2'
 * '<S4>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Current Measurement4'
 * '<S5>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/DC Voltage Source'
 * '<S6>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/DC Voltage Source1'
 * '<S7>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/DC Voltage Source2'
 * '<S8>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem'
 * '<S9>'   : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem1'
 * '<S10>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem2'
 * '<S11>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem3'
 * '<S12>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4'
 * '<S13>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5'
 * '<S14>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Voltage Measurement'
 * '<S15>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Voltage Measurement1'
 * '<S16>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Voltage Measurement2'
 * '<S17>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 '
 * '<S18>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2'
 * '<S19>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3'
 * '<S20>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/powergui'
 * '<S21>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Breaker/Model'
 * '<S22>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Breaker/Model/Timer'
 * '<S23>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Current Measurement/Model'
 * '<S24>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Current Measurement2/Model'
 * '<S25>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Current Measurement4/Model'
 * '<S26>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/DC Voltage Source/Model'
 * '<S27>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/DC Voltage Source1/Model'
 * '<S28>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/DC Voltage Source2/Model'
 * '<S29>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem1/S-R Flip-Flop'
 * '<S30>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem1/sub '
 * '<S31>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem2/S-R Flip-Flop'
 * '<S32>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem2/sub '
 * '<S33>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem3/S-R Flip-Flop'
 * '<S34>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem3/sub '
 * '<S35>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Voltage Measurement/Model'
 * '<S36>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Voltage Measurement1/Model'
 * '<S37>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/Voltage Measurement2/Model'
 * '<S38>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /  '
 * '<S39>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 / Measurement'
 * '<S40>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Current Measurement'
 * '<S41>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Diode'
 * '<S42>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet'
 * '<S43>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /  /Model'
 * '<S44>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 / Measurement/Model'
 * '<S45>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Current Measurement/Model'
 * '<S46>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Diode/Model'
 * '<S47>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Diode/Model/Measurement list'
 * '<S48>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Diode'
 * '<S49>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Ideal Switch'
 * '<S50>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Measurement list'
 * '<S51>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Diode/Model'
 * '<S52>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Diode/Model/Measurement list'
 * '<S53>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Ideal Switch/Model'
 * '<S54>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Ideal Switch/Model/Measurement list'
 * '<S55>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/  '
 * '<S56>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/ Measurement'
 * '<S57>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Current Measurement'
 * '<S58>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Diode'
 * '<S59>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet'
 * '<S60>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Repeating Sequence'
 * '<S61>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/  /Model'
 * '<S62>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/ Measurement/Model'
 * '<S63>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Current Measurement/Model'
 * '<S64>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Diode/Model'
 * '<S65>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Diode/Model/Measurement list'
 * '<S66>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Diode'
 * '<S67>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Ideal Switch'
 * '<S68>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Measurement list'
 * '<S69>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Diode/Model'
 * '<S70>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Diode/Model/Measurement list'
 * '<S71>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Ideal Switch/Model'
 * '<S72>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Ideal Switch/Model/Measurement list'
 * '<S73>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/  '
 * '<S74>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/ Measurement'
 * '<S75>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Current Measurement'
 * '<S76>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Diode'
 * '<S77>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet'
 * '<S78>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Repeating Sequence'
 * '<S79>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/  /Model'
 * '<S80>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/ Measurement/Model'
 * '<S81>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Current Measurement/Model'
 * '<S82>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Diode/Model'
 * '<S83>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Diode/Model/Measurement list'
 * '<S84>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Diode'
 * '<S85>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Ideal Switch'
 * '<S86>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Measurement list'
 * '<S87>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Diode/Model'
 * '<S88>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Diode/Model/Measurement list'
 * '<S89>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Ideal Switch/Model'
 * '<S90>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Ideal Switch/Model/Measurement list'
 * '<S91>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1'
 * '<S92>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/Gates'
 * '<S93>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/Sources'
 * '<S94>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/Status'
 * '<S95>'  : 'Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_Copy_of_test_v_control_and_i_control_with_droop_copy_h_ */
