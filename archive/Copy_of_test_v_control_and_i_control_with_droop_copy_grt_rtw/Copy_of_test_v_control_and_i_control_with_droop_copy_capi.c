/*
 * Copy_of_test_v_control_and_i_control_with_droop_copy_capi.c
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

#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Copy_of_test_v_control_and_i_control_with_droop_copy_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "Copy_of_test_v_control_and_i_control_with_droop_copy.h"
#include "Copy_of_test_v_control_and_i_control_with_droop_copy_capi.h"
#include "Copy_of_test_v_control_and_i_control_with_droop_copy_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block output signal information */
static rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/From Workspace"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 1, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/From Workspace1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 2, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/From Workspace2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 3, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Relational Operator"),
    TARGET_STRING(""), 0, 1, 0, 0, 1 },

  { 4, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Gain"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 5, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Divide"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 6, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Sum"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 7, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Transfer Fcn1"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 8, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Transfer Fcn2"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 9, 0, TARGET_STRING("Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Gain"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 10, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Divide"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 11, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Sum"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 12, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Transfer Fcn2"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 13, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Gain"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 14, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Divide"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 15, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Sum"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 16, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Transfer Fcn2"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 17, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Sum"),
    TARGET_STRING(""), 0, 0, 0, 0, 2 },

  { 18, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Sum"),
    TARGET_STRING(""), 0, 0, 0, 0, 2 },

  { 19, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem1/S-R Flip-Flop/Logic"),
    TARGET_STRING(""), 0, 1, 1, 0, 1 },

  { 20, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem1/S-R Flip-Flop/Memory"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 21, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem2/S-R Flip-Flop/Logic"),
    TARGET_STRING(""), 0, 1, 1, 0, 1 },

  { 22, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem2/S-R Flip-Flop/Memory"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 23, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem3/S-R Flip-Flop/Logic"),
    TARGET_STRING(""), 0, 1, 1, 0, 1 },

  { 24, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem3/S-R Flip-Flop/Memory"),
    TARGET_STRING(""), 0, 1, 0, 0, 0 },

  { 25, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Repeating Sequence/startTime"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 26, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Repeating Sequence/startTime"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 27, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/State-Space"),
    TARGET_STRING(""), 0, 0, 2, 0, 0 },

  { 28, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/State-Space"),
    TARGET_STRING(""), 1, 0, 3, 0, 0 },

  { 29, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Breaker/Model/Timer/Derivative"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 30, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Breaker/Model/Timer/Look-Up Table"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 31, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost 1 /Mosfet/Ideal Switch/Model/Data Type Conversion"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 32, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost 2/Mosfet/Ideal Switch/Model/Data Type Conversion"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 33, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/boost_3/Mosfet/Ideal Switch/Model/Data Type Conversion"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

/* Individual block tuning is not valid when inline parameters is *
 * selected. An empty map is produced to provide a consistent     *
 * interface independent  of inlining parameters.                 *
 */
static rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Block states information */
static rtwCAPI_States rtBlockStates[] = {
  /* addrMapIndex, contStateStartIndex, blockPath,
   * stateName, pathAlias, dWorkIndex, dataTypeIndex, dimIndex,
   * fixPtIdx, sTimeIndex, isContinuous, hierInfoIdx, flatElemIdx
   */
  { 34, 2, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Transfer Fcn"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 35, 1, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Transfer Fcn1"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 36, 0, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem/Transfer Fcn2"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 37, 7, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Transfer Fcn"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 38, 4, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Transfer Fcn1"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 39, 3, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem4/Transfer Fcn2"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 40, 8, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Transfer Fcn"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 41, 6, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Transfer Fcn1"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 42, 5, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/Subsystem5/Transfer Fcn2"),
    TARGET_STRING(""),
    TARGET_STRING(""),
    0, 0, 0, 0, 1, 1, -1, 0 },

  { 43, -1, TARGET_STRING(
    "Copy_of_test_v_control_and_i_control_with_droop_copy/powergui/EquivalentModel1/State-Space"),
    TARGET_STRING(""), "", 0, 0, 4, 0, 0, 0, -1, 0 },

  {
    0, -1, (NULL), (NULL), (NULL), 0, 0, 0, 0, 0, 0, -1, 0
  }
};

/* Tunable variable parameters */
static rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void
  Copy_of_test_v_control_and_i_control_with_droop_copy_InitializeDataAddr
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M, void
   * dataAddr[], B_Copy_of_test_v_control_and__T
   *Copy_of_test_v_control_and_i__B, DW_Copy_of_test_v_control_and_T
   *Copy_of_test_v_control_and_i_DW, X_Copy_of_test_v_control_and__T
   *Copy_of_test_v_control_and_i__X)
{
  dataAddr[0] = (void*) (&Copy_of_test_v_control_and_i__B->FromWorkspace);
  dataAddr[1] = (void*) (&Copy_of_test_v_control_and_i__B->FromWorkspace1);
  dataAddr[2] = (void*) (&Copy_of_test_v_control_and_i__B->FromWorkspace2);
  dataAddr[3] = (void*) (&Copy_of_test_v_control_and_i__B->RelationalOperator);
  dataAddr[4] = (void*) (&Copy_of_test_v_control_and_i__B->Gain);
  dataAddr[5] = (void*) (&Copy_of_test_v_control_and_i__B->Divide);
  dataAddr[6] = (void*) (&Copy_of_test_v_control_and_i__B->Sum);
  dataAddr[7] = (void*) (&Copy_of_test_v_control_and_i__B->TransferFcn1);
  dataAddr[8] = (void*) (&Copy_of_test_v_control_and_i__B->TransferFcn2);
  dataAddr[9] = (void*) (&Copy_of_test_v_control_and_i__B->Gain_j);
  dataAddr[10] = (void*) (&Copy_of_test_v_control_and_i__B->Divide_b);
  dataAddr[11] = (void*) (&Copy_of_test_v_control_and_i__B->Sum_c);
  dataAddr[12] = (void*) (&Copy_of_test_v_control_and_i__B->TransferFcn2_i);
  dataAddr[13] = (void*) (&Copy_of_test_v_control_and_i__B->Gain_h);
  dataAddr[14] = (void*) (&Copy_of_test_v_control_and_i__B->Divide_l);
  dataAddr[15] = (void*) (&Copy_of_test_v_control_and_i__B->Sum_p);
  dataAddr[16] = (void*) (&Copy_of_test_v_control_and_i__B->TransferFcn2_o);
  dataAddr[17] = (void*) (&Copy_of_test_v_control_a_ConstB.Sum);
  dataAddr[18] = (void*) (&Copy_of_test_v_control_a_ConstB.Sum_k);
  dataAddr[19] = (void*) (&Copy_of_test_v_control_and_i__B->Logic[0]);
  dataAddr[20] = (void*) (&Copy_of_test_v_control_and_i__B->Memory);
  dataAddr[21] = (void*) (&Copy_of_test_v_control_and_i__B->Logic_p[0]);
  dataAddr[22] = (void*) (&Copy_of_test_v_control_and_i__B->Memory_n);
  dataAddr[23] = (void*) (&Copy_of_test_v_control_and_i__B->Logic_c[0]);
  dataAddr[24] = (void*) (&Copy_of_test_v_control_and_i__B->Memory_i);
  dataAddr[25] = (void*) (&Copy_of_test_v_control_and_i__B->startTime);
  dataAddr[26] = (void*) (&Copy_of_test_v_control_and_i__B->startTime_p);
  dataAddr[27] = (void*) (&Copy_of_test_v_control_and_i__B->StateSpace_o1[0]);
  dataAddr[28] = (void*) (&Copy_of_test_v_control_and_i__B->StateSpace_o2[0]);
  dataAddr[29] = (void*) (&Copy_of_test_v_control_and_i__B->Derivative);
  dataAddr[30] = (void*) (&Copy_of_test_v_control_and_i__B->LookUpTable);
  dataAddr[31] = (void*) (&Copy_of_test_v_control_and_i__B->DataTypeConversion);
  dataAddr[32] = (void*) (&Copy_of_test_v_control_and_i__B->DataTypeConversion_p);
  dataAddr[33] = (void*) (&Copy_of_test_v_control_and_i__B->DataTypeConversion_a);
  dataAddr[34] = (void*) (&Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE);
  dataAddr[35] = (void*) (&Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE);
  dataAddr[36] = (void*) (&Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE);
  dataAddr[37] = (void*) (&Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE_a);
  dataAddr[38] = (void*)
    (&Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_a);
  dataAddr[39] = (void*)
    (&Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_p);
  dataAddr[40] = (void*) (&Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE_o);
  dataAddr[41] = (void*)
    (&Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_d);
  dataAddr[42] = (void*)
    (&Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_f);
  dataAddr[43] = (void*) (&Copy_of_test_v_control_and_i_DW->StateSpace_DSTATE[0]);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void
  Copy_of_test_v_control_and_i_control_with_droop_copy_InitializeVarDimsAddr
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M,
   int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer */
  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0 },

  { "unsigned char", "boolean_T", 0, 0, sizeof(boolean_T), SS_BOOLEAN, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 },

  { rtwCAPI_VECTOR, 6, 2, 0 },

  { rtwCAPI_VECTOR, 8, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  2,                                   /* 2 */
  1,                                   /* 3 */
  25,                                  /* 4 */
  1,                                   /* 5 */
  10,                                  /* 6 */
  1,                                   /* 7 */
  7,                                   /* 8 */
  1                                    /* 9 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.01, 0.0
};

/* Fixed Point Map */
static rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    1, 0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[1],
    0, 0 },

  { (NULL), (NULL), -2, 0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 34,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 0,
    rtModelParameters, 0 },

  { rtBlockStates, 10 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 2236287798U,
    1058810221U,
    1335893452U,
    2682997678U },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  Copy_of_test_v_control_and_i_control_with_droop_copy_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void Copy_of_test_v_control_and_i_control_with_droop_copy_InitializeDataMapInfo
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M,
   B_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__B,
   DW_Copy_of_test_v_control_and_T *Copy_of_test_v_control_and_i_DW,
   X_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__X)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi,
                       &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi,
    (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  Copy_of_test_v_control_and_i_control_with_droop_copy_InitializeDataAddr
    (Copy_of_test_v_control_and_i_M,
     Copy_of_test_v_control_and_i_M->DataMapInfo.dataAddress,
     Copy_of_test_v_control_and_i_M->blockIO,
     Copy_of_test_v_control_and_i_M->dwork, (X_Copy_of_test_v_control_and__T *)
     Copy_of_test_v_control_and_i_M->contStates);
  rtwCAPI_SetDataAddressMap(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi,
    Copy_of_test_v_control_and_i_M->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  Copy_of_test_v_control_and_i_control_with_droop_copy_InitializeVarDimsAddr
    (Copy_of_test_v_control_and_i_M,
     Copy_of_test_v_control_and_i_M->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi,
    Copy_of_test_v_control_and_i_M->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi, (NULL));

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi,
    (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi,
    (NULL));
  rtwCAPI_SetChildMMIArrayLen(Copy_of_test_v_control_and_i_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C" {

#endif

  void
    Copy_of_test_v_control_and_i_control_with_droop_copy_host_InitializeDataMapInfo
    (Copy_of_test_v_control_and_i_control_with_droop_copy_host_DataMapInfo_T
     *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* EOF: Copy_of_test_v_control_and_i_control_with_droop_copy_capi.c */
