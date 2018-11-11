/*
 * rt_look1d.h
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

#ifndef RTW_HEADER_rt_look1d_h_
#define RTW_HEADER_rt_look1d_h_
#include "rtwtypes.h"
#include "rt_look.h"

extern real_T rt_Lookup(const real_T *x, int_T xlen, real_T u, const real_T *y);

#endif                                 /* RTW_HEADER_rt_look1d_h_ */
