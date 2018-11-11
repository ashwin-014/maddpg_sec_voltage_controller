/*
 * Copy_of_test_v_control_and_i_control_with_droop_copy.c
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

#include "rt_logging_mmi.h"
#include "Copy_of_test_v_control_and_i_control_with_droop_copy_capi.h"
#include "Copy_of_test_v_control_and_i_control_with_droop_copy.h"
#include "Copy_of_test_v_control_and_i_control_with_droop_copy_private.h"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M)
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Copy_of_test_v_control_and_i_control_with_droop_copy_derivatives
    (Copy_of_test_v_control_and_i_M);

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Copy_of_test_v_control_and_i_control_with_droop_copy_step
    (Copy_of_test_v_control_and_i_M);
  Copy_of_test_v_control_and_i_control_with_droop_copy_derivatives
    (Copy_of_test_v_control_and_i_M);

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Copy_of_test_v_control_and_i_control_with_droop_copy_step
    (Copy_of_test_v_control_and_i_M);
  Copy_of_test_v_control_and_i_control_with_droop_copy_derivatives
    (Copy_of_test_v_control_and_i_M);

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Copy_of_test_v_control_and_i_control_with_droop_copy_step
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M)
{
  B_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__B =
    ((B_Copy_of_test_v_control_and__T *) Copy_of_test_v_control_and_i_M->blockIO);
  DW_Copy_of_test_v_control_and_T *Copy_of_test_v_control_and_i_DW =
    ((DW_Copy_of_test_v_control_and_T *) Copy_of_test_v_control_and_i_M->dwork);
  X_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__X =
    ((X_Copy_of_test_v_control_and__T *)
     Copy_of_test_v_control_and_i_M->contStates);
  ExtY_Copy_of_test_v_control_a_T *Copy_of_test_v_control_and_i__Y =
    (ExtY_Copy_of_test_v_control_a_T *) Copy_of_test_v_control_and_i_M->outputs;

  /* local block i/o variables */
  real_T rtb_Product5;
  real_T rtb_Product4;
  real_T rtb_Product3;
  if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    /* set solver stop time */
    if (!(Copy_of_test_v_control_and_i_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(Copy_of_test_v_control_and_i_M->solverInfo,
                            ((Copy_of_test_v_control_and_i_M->Timing.clockTickH0
        + 1) * Copy_of_test_v_control_and_i_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(Copy_of_test_v_control_and_i_M->solverInfo,
                            ((Copy_of_test_v_control_and_i_M->Timing.clockTick0
        + 1) * Copy_of_test_v_control_and_i_M->Timing.stepSize0 +
        Copy_of_test_v_control_and_i_M->Timing.clockTickH0 *
        Copy_of_test_v_control_and_i_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Copy_of_test_v_control_and_i_M)) {
    Copy_of_test_v_control_and_i_M->Timing.t[0] = rtsiGetT
      (Copy_of_test_v_control_and_i_M->solverInfo);
  }

  {
    int32_T rowIdx;
    real_T *lastU;
    real_T rtb_Clock;
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
      /* S-Function (sfun_spssw_discc): '<S91>/State-Space' incorporates:
       *  Constant: '<S26>/DC'
       *  Constant: '<S27>/DC'
       *  Constant: '<S28>/DC'
       *  Constant: '<S46>/eee'
       *  Constant: '<S64>/eee'
       *  Constant: '<S82>/eee'
       *  Constant: '<S93>/SwitchCurrents'
       */

      /* S-Function block: <S91>/State-Space */
      {
        real_T accum;

        /* Circuit has switches */
        int_T *switch_status = (int_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS;
        int_T *switch_status_init = (int_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS_INIT;
        int_T *SwitchChange = (int_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SW_CHG;
        int_T *gState = (int_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.G_STATE;
        real_T *yswitch = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.Y_SWITCH;
        int_T *switchTypes = (int_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_TYPES;
        int_T *idxOutSw = (int_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.IDX_OUT_SW;
        real_T *DxCol = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DX_COL;
        real_T *tmp2 = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.TMP2;
        real_T *BDcol = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BD_COL;
        real_T *tmp1 = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.TMP1;
        real_T *uswlast = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.USWLAST;
        int_T newState;
        int_T swChanged = 0;
        int loopsToDo = 20;
        real_T temp;

        /* keep an initial copy of switch_status*/
        memcpy(switch_status_init, switch_status, 10 * sizeof(int_T));
        memcpy(uswlast, &Copy_of_test_v_control_and_i__B->StateSpace_o1[0], 10*
               sizeof(real_T));
        do {
          if (loopsToDo == 1) {        /* Need to reset some variables: */
            swChanged = 0;

            /* return to the original switch status*/
            {
              int_T i1;
              for (i1=0; i1 < 10; i1++) {
                swChanged = ((SwitchChange[i1] = switch_status_init[i1] -
                              switch_status[i1]) != 0) ? 1 : swChanged;
                switch_status[i1] = switch_status_init[i1];
              }
            }
          } else {
            /*
             * Compute outputs:
             * ---------------
             */
            real_T *Cs = (real_T*)
              Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.CS;
            real_T *Ds = (real_T*)
              Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DS;

            {
              int_T i1;
              real_T *y0 = &Copy_of_test_v_control_and_i__B->StateSpace_o1[0];
              for (i1=0; i1 < 25; i1++) {
                accum = 0.0;

                {
                  int_T i2;
                  real_T *xd =
                    &Copy_of_test_v_control_and_i_DW->StateSpace_DSTATE[0];
                  for (i2=0; i2 < 7; i2++) {
                    accum += *(Cs++) * xd[i2];
                  }
                }

                {
                  int_T i2;
                  const real_T *u0 =
                    Copy_of_test_v_control_a_ConstP.SwitchCurrents_Value;
                  for (i2=0; i2 < 10; i2++) {
                    accum += *(Ds++) * u0[i2];
                  }

                  accum += *(Ds++) * 200.0;
                  accum += *(Ds++) * 200.0;
                  accum += *(Ds++) * 200.0;
                  accum += *(Ds++) * 0.8;
                  accum += *(Ds++) * 0.8;
                  accum += *(Ds++) * 0.8;
                }

                y0[i1] = accum;
              }
            }

            swChanged = 0;

            {
              int_T i1;
              real_T *y0 = &Copy_of_test_v_control_and_i__B->StateSpace_o1[0];
              for (i1=0; i1 < 10; i1++) {
                switch (switchTypes[i1]) {
                 case 1 :              /* Ideal switch */
                  newState = gState[i1] > 0 ? 1 : 0;
                  break;

                 case 2 :              /* Breaker */
                  newState = (gState[i1] > 0) ? 1 : ((y0[i1]*uswlast[i1] < 0.0) ?
                    0 : switch_status[i1]);
                  break;

                 case 3 :              /* Diodes */
                  newState = y0[i1] > 0.0 ? 1 : ((y0[i1] < 0.0) ? 0 :
                    switch_status[i1]);
                  break;
                }

                swChanged = ((SwitchChange[i1] = newState - switch_status[i1])
                             != 0) ? 1 : swChanged;
                switch_status[i1] = newState;/* Keep new state */
              }
            }
          }

          /*
           * Compute new As, Bs, Cs and Ds matrixes:
           * --------------------------------------
           */
          if (swChanged) {
            real_T *As = (real_T*)
              Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.AS;
            real_T *Cs = (real_T*)
              Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.CS;
            real_T *Bs = (real_T*)
              Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BS;
            real_T *Ds = (real_T*)
              Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DS;
            real_T a1;

            {
              int_T i1;
              for (i1=0; i1 < 10; i1++) {
                if (SwitchChange[i1] != 0) {
                  a1 = yswitch[i1]*SwitchChange[i1];
                  temp = 1/(1-Ds[i1*17]*a1);

                  {
                    int_T i2;
                    for (i2=0; i2 < 25; i2++) {
                      DxCol[i2]= Ds[i2 * 16 + i1]*temp*a1;
                    }
                  }

                  DxCol[i1] = temp;

                  {
                    int_T i2;
                    for (i2=0; i2 < 7; i2++) {
                      BDcol[i2]= Bs[i2 * 16 + i1]*a1;
                    }
                  }

                  /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
                  memcpy(tmp1, &Cs[i1 * 7], 7 * sizeof(real_T));
                  memset(&Cs[i1 * 7], '\0', 7 * sizeof(real_T));

                  /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
                  memcpy(tmp2, &Ds[i1 * 16], 16 * sizeof(real_T));
                  memset(&Ds[i1 * 16], '\0', 16 * sizeof(real_T));

                  /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 25; i2++) {
                      a1 = DxCol[i2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 7; i3++) {
                          Cs[i2 * 7 + i3] += a1 * tmp1[i3];
                        }
                      }

                      {
                        int_T i3;
                        for (i3=0; i3 < 16; i3++) {
                          Ds[i2 * 16 + i3] += a1 * tmp2[i3];
                        }
                      }
                    }
                  }

                  /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 7; i2++) {
                      a1 = BDcol[i2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 7; i3++) {
                          As[i2 * 7 + i3] += a1 * Cs[i1 * 7 + i3];
                        }
                      }

                      {
                        int_T i3;
                        for (i3=0; i3 < 16; i3++) {
                          Bs[i2 * 16 + i3] += a1 * Ds[i1 * 16 + i3];
                        }
                      }
                    }
                  }
                }
              }
            }
          }                            /* if (swChanged) */
        } while (swChanged > 0 && --loopsToDo > 0);

        if (loopsToDo == 0) {
          real_T *Cs = (real_T*)
            Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.CS;
          real_T *Ds = (real_T*)
            Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DS;

          {
            int_T i1;
            real_T *y0 = &Copy_of_test_v_control_and_i__B->StateSpace_o1[0];
            for (i1=0; i1 < 25; i1++) {
              accum = 0.0;

              {
                int_T i2;
                real_T *xd = &Copy_of_test_v_control_and_i_DW->
                  StateSpace_DSTATE[0];
                for (i2=0; i2 < 7; i2++) {
                  accum += *(Cs++) * xd[i2];
                }
              }

              {
                int_T i2;
                const real_T *u0 =
                  Copy_of_test_v_control_a_ConstP.SwitchCurrents_Value;
                for (i2=0; i2 < 10; i2++) {
                  accum += *(Ds++) * u0[i2];
                }

                accum += *(Ds++) * 200.0;
                accum += *(Ds++) * 200.0;
                accum += *(Ds++) * 200.0;
                accum += *(Ds++) * 0.8;
                accum += *(Ds++) * 0.8;
                accum += *(Ds++) * 0.8;
              }

              y0[i1] = accum;
            }
          }
        }

        /* Output new switches states */
        {
          int_T i1;
          real_T *y1 = &Copy_of_test_v_control_and_i__B->StateSpace_o2[0];
          for (i1=0; i1 < 10; i1++) {
            y1[i1] = (real_T)switch_status[i1];
          }
        }
      }

      /* Outport: '<Root>/v_out0' */
      Copy_of_test_v_control_and_i__Y->v_out0 =
        Copy_of_test_v_control_and_i__B->StateSpace_o1[15];

      /* Outport: '<Root>/i_out0' */
      Copy_of_test_v_control_and_i__Y->i_out0 =
        Copy_of_test_v_control_and_i__B->StateSpace_o1[23];

      /* Outport: '<Root>/v_out1' */
      Copy_of_test_v_control_and_i__Y->v_out1 =
        Copy_of_test_v_control_and_i__B->StateSpace_o1[10];

      /* Outport: '<Root>/i_out1' */
      Copy_of_test_v_control_and_i__Y->i_out1 =
        Copy_of_test_v_control_and_i__B->StateSpace_o1[19];

      /* Outport: '<Root>/v_out2' */
      Copy_of_test_v_control_and_i__Y->v_out2 =
        Copy_of_test_v_control_and_i__B->StateSpace_o1[16];

      /* Outport: '<Root>/i_out2' */
      Copy_of_test_v_control_and_i__Y->i_out2 =
        Copy_of_test_v_control_and_i__B->StateSpace_o1[24];

      /* Scope: '<Root>/I_out_0' */
      if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
        StructLogVar *svar = (StructLogVar *)
          Copy_of_test_v_control_and_i_DW->I_out_0_PWORK.LoggedData;
        LogVar *var = svar->signals.values;

        /* time */
        {
          double locTime = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                              Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                              4294967296.0)) * 0.01);
          ;
          rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
        }

        /* signals */
        {
          real_T up0[1];
          up0[0] = Copy_of_test_v_control_and_i__B->StateSpace_o1[23];
          rt_UpdateLogVar((LogVar *)var, up0, 0);
        }
      }

      /* Scope: '<Root>/I_out_1' */
      if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
        StructLogVar *svar = (StructLogVar *)
          Copy_of_test_v_control_and_i_DW->I_out_1_PWORK.LoggedData;
        LogVar *var = svar->signals.values;

        /* time */
        {
          double locTime = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                              Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                              4294967296.0)) * 0.01);
          ;
          rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
        }

        /* signals */
        {
          real_T up0[1];
          up0[0] = Copy_of_test_v_control_and_i__B->StateSpace_o1[19];
          rt_UpdateLogVar((LogVar *)var, up0, 0);
        }
      }

      /* Scope: '<Root>/I_out_2' */
      if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
        StructLogVar *svar = (StructLogVar *)
          Copy_of_test_v_control_and_i_DW->I_out_2_PWORK.LoggedData;
        LogVar *var = svar->signals.values;

        /* time */
        {
          double locTime = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                              Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                              4294967296.0)) * 0.01);
          ;
          rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
        }

        /* signals */
        {
          real_T up0[1];
          up0[0] = Copy_of_test_v_control_and_i__B->StateSpace_o1[24];
          rt_UpdateLogVar((LogVar *)var, up0, 0);
        }
      }

      /* Product: '<Root>/Product' */
      rtb_Product5 = Copy_of_test_v_control_and_i__B->StateSpace_o1[22] *
        Copy_of_test_v_control_and_i__B->StateSpace_o1[14];

      /* Product: '<Root>/Product1' */
      rtb_Product4 = Copy_of_test_v_control_and_i__B->StateSpace_o1[21] *
        Copy_of_test_v_control_and_i__B->StateSpace_o1[13];

      /* Product: '<Root>/Product2' */
      rtb_Product3 = Copy_of_test_v_control_and_i__B->StateSpace_o1[20] *
        Copy_of_test_v_control_and_i__B->StateSpace_o1[12];

      /* Product: '<Root>/Product3' */
      rtb_Product3 = Copy_of_test_v_control_and_i__B->StateSpace_o1[15] *
        Copy_of_test_v_control_and_i__B->StateSpace_o1[23];

      /* Product: '<Root>/Product4' */
      rtb_Product4 = Copy_of_test_v_control_and_i__B->StateSpace_o1[10] *
        Copy_of_test_v_control_and_i__B->StateSpace_o1[19];

      /* Product: '<Root>/Product5' */
      rtb_Product5 = Copy_of_test_v_control_and_i__B->StateSpace_o1[16] *
        Copy_of_test_v_control_and_i__B->StateSpace_o1[24];

      /* Scope: '<Root>/V_out_0' */
      if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
        StructLogVar *svar = (StructLogVar *)
          Copy_of_test_v_control_and_i_DW->V_out_0_PWORK.LoggedData;
        LogVar *var = svar->signals.values;

        /* time */
        {
          double locTime = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                              Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                              4294967296.0)) * 0.01);
          ;
          rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
        }

        /* signals */
        {
          real_T up0[1];
          up0[0] = Copy_of_test_v_control_and_i__B->StateSpace_o1[15];
          rt_UpdateLogVar((LogVar *)var, up0, 0);
        }
      }

      /* Scope: '<Root>/V_out_1' */
      if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
        StructLogVar *svar = (StructLogVar *)
          Copy_of_test_v_control_and_i_DW->V_out_1_PWORK.LoggedData;
        LogVar *var = svar->signals.values;

        /* time */
        {
          double locTime = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                              Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                              4294967296.0)) * 0.01);
          ;
          rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
        }

        /* signals */
        {
          real_T up0[1];
          up0[0] = Copy_of_test_v_control_and_i__B->StateSpace_o1[10];
          rt_UpdateLogVar((LogVar *)var, up0, 0);
        }
      }

      /* Scope: '<Root>/V_out_2' */
      if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
        StructLogVar *svar = (StructLogVar *)
          Copy_of_test_v_control_and_i_DW->V_out_2_PWORK.LoggedData;
        LogVar *var = svar->signals.values;

        /* time */
        {
          double locTime = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                              Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                              4294967296.0)) * 0.01);
          ;
          rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
        }

        /* signals */
        {
          real_T up0[1];
          up0[0] = Copy_of_test_v_control_and_i__B->StateSpace_o1[16];
          rt_UpdateLogVar((LogVar *)var, up0, 0);
        }
      }

      /* FromWorkspace: '<Root>/From Workspace' */
      {
        real_T *pDataValues = (real_T *)
          Copy_of_test_v_control_and_i_DW->FromWorkspace_PWORK.DataPtr;
        real_T *pTimeValues = (real_T *)
          Copy_of_test_v_control_and_i_DW->FromWorkspace_PWORK.TimePtr;
        int_T currTimeIndex =
          Copy_of_test_v_control_and_i_DW->FromWorkspace_IWORK.PrevIndex;
        real_T t = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                      Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                      4294967296.0)) * 0.01);

        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[999]) {
          currTimeIndex = 998;
        } else {
          if (t < pTimeValues[currTimeIndex]) {
            while (t < pTimeValues[currTimeIndex]) {
              currTimeIndex--;
            }
          } else {
            while (t >= pTimeValues[currTimeIndex + 1]) {
              currTimeIndex++;
            }
          }
        }

        Copy_of_test_v_control_and_i_DW->FromWorkspace_IWORK.PrevIndex =
          currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              Copy_of_test_v_control_and_i__B->FromWorkspace =
                pDataValues[currTimeIndex];
            } else {
              Copy_of_test_v_control_and_i__B->FromWorkspace =
                pDataValues[currTimeIndex + 1];
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex= currTimeIndex;
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            Copy_of_test_v_control_and_i__B->FromWorkspace = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 1000;
          }
        }
      }

      /* FromWorkspace: '<Root>/From Workspace1' */
      {
        real_T *pDataValues = (real_T *)
          Copy_of_test_v_control_and_i_DW->FromWorkspace1_PWORK.DataPtr;
        real_T *pTimeValues = (real_T *)
          Copy_of_test_v_control_and_i_DW->FromWorkspace1_PWORK.TimePtr;
        int_T currTimeIndex =
          Copy_of_test_v_control_and_i_DW->FromWorkspace1_IWORK.PrevIndex;
        real_T t = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                      Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                      4294967296.0)) * 0.01);

        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[999]) {
          currTimeIndex = 998;
        } else {
          if (t < pTimeValues[currTimeIndex]) {
            while (t < pTimeValues[currTimeIndex]) {
              currTimeIndex--;
            }
          } else {
            while (t >= pTimeValues[currTimeIndex + 1]) {
              currTimeIndex++;
            }
          }
        }

        Copy_of_test_v_control_and_i_DW->FromWorkspace1_IWORK.PrevIndex =
          currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              Copy_of_test_v_control_and_i__B->FromWorkspace1 =
                pDataValues[currTimeIndex];
            } else {
              Copy_of_test_v_control_and_i__B->FromWorkspace1 =
                pDataValues[currTimeIndex + 1];
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex= currTimeIndex;
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            Copy_of_test_v_control_and_i__B->FromWorkspace1 = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 1000;
          }
        }
      }

      /* FromWorkspace: '<Root>/From Workspace2' */
      {
        real_T *pDataValues = (real_T *)
          Copy_of_test_v_control_and_i_DW->FromWorkspace2_PWORK.DataPtr;
        real_T *pTimeValues = (real_T *)
          Copy_of_test_v_control_and_i_DW->FromWorkspace2_PWORK.TimePtr;
        int_T currTimeIndex =
          Copy_of_test_v_control_and_i_DW->FromWorkspace2_IWORK.PrevIndex;
        real_T t = (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                      Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                      4294967296.0)) * 0.01);

        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[999]) {
          currTimeIndex = 998;
        } else {
          if (t < pTimeValues[currTimeIndex]) {
            while (t < pTimeValues[currTimeIndex]) {
              currTimeIndex--;
            }
          } else {
            while (t >= pTimeValues[currTimeIndex + 1]) {
              currTimeIndex++;
            }
          }
        }

        Copy_of_test_v_control_and_i_DW->FromWorkspace2_IWORK.PrevIndex =
          currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              Copy_of_test_v_control_and_i__B->FromWorkspace2 =
                pDataValues[currTimeIndex];
            } else {
              Copy_of_test_v_control_and_i__B->FromWorkspace2 =
                pDataValues[currTimeIndex + 1];
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex= currTimeIndex;
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            Copy_of_test_v_control_and_i__B->FromWorkspace2 = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 1000;
          }
        }
      }
    }

    /* TransferFcn: '<S8>/Transfer Fcn2' */
    Copy_of_test_v_control_and_i__B->TransferFcn2 = 0.0;
    Copy_of_test_v_control_and_i__B->TransferFcn2 += 188.0 *
      Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE;

    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<Root>/Vref 2'
     */
    Copy_of_test_v_control_and_i__B->Sum =
      (Copy_of_test_v_control_and_i__B->FromWorkspace -
       Copy_of_test_v_control_and_i__B->TransferFcn2) + 750.0;
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    }

    /* Gain: '<S8>/Gain' */
    Copy_of_test_v_control_and_i__B->Gain = 0.375 *
      Copy_of_test_v_control_and_i__B->Sum;

    /* TransferFcn: '<S8>/Transfer Fcn1' */
    Copy_of_test_v_control_and_i__B->TransferFcn1 = 0.0;
    Copy_of_test_v_control_and_i__B->TransferFcn1 += 0.078554595443833461 *
      Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE;
    Copy_of_test_v_control_and_i__B->TransferFcn1 += 0.74999999999999989 *
      Copy_of_test_v_control_and_i__B->Gain;

    /* Product: '<S8>/Divide' incorporates:
     *  Product: '<S8>/Product'
     */
    Copy_of_test_v_control_and_i__B->Divide =
      Copy_of_test_v_control_and_i__B->TransferFcn1 *
      Copy_of_test_v_control_and_i__B->StateSpace_o1[15] /
      Copy_of_test_v_control_and_i__B->StateSpace_o1[14];
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
      /* Memory: '<S29>/Memory' */
      Copy_of_test_v_control_and_i__B->Memory =
        Copy_of_test_v_control_and_i_DW->Memory_PreviousInput;
    }

    /* TransferFcn: '<S12>/Transfer Fcn2' */
    Copy_of_test_v_control_and_i__B->TransferFcn2_i = 0.0;
    Copy_of_test_v_control_and_i__B->TransferFcn2_i += 188.0 *
      Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_p;

    /* Sum: '<S12>/Sum' incorporates:
     *  Constant: '<Root>/Vref 2'
     */
    Copy_of_test_v_control_and_i__B->Sum_c =
      (Copy_of_test_v_control_and_i__B->FromWorkspace1 -
       Copy_of_test_v_control_and_i__B->TransferFcn2_i) + 750.0;

    /* Gain: '<S12>/Gain' */
    Copy_of_test_v_control_and_i__B->Gain_j = 0.375 *
      Copy_of_test_v_control_and_i__B->Sum_c;

    /* Product: '<S12>/Divide' incorporates:
     *  Product: '<S12>/Product'
     *  TransferFcn: '<S12>/Transfer Fcn1'
     */
    Copy_of_test_v_control_and_i__B->Divide_b = (0.078554595443833461 *
      Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_a +
      0.74999999999999989 * Copy_of_test_v_control_and_i__B->Gain_j) *
      Copy_of_test_v_control_and_i__B->StateSpace_o1[10] /
      Copy_of_test_v_control_and_i__B->StateSpace_o1[13];

    /* CombinatorialLogic: '<S29>/Logic' incorporates:
     *  Constant: '<S30>/Constant2'
     *  Constant: '<S9>/Constant2'
     *  RelationalOperator: '<S30>/Relational Operator'
     *  RelationalOperator: '<S30>/Relational Operator1'
     *  Sum: '<S30>/Sum'
     *  Sum: '<S30>/Sum1'
     *  Sum: '<S9>/Sum'
     *  Sum: '<S9>/Sum1'
     */
    rowIdx = (int32_T)(((((uint32_T)((Copy_of_test_v_control_and_i__B->Divide_b
      + 0.44444) - Copy_of_test_v_control_and_i__B->StateSpace_o1[21] >= 1.0) <<
                          1) + (Copy_of_test_v_control_and_i__B->StateSpace_o1
      [21] - (Copy_of_test_v_control_and_i__B->Divide_b - 0.44444) >= 1.0)) << 1)
                       + Copy_of_test_v_control_and_i__B->Memory);
    Copy_of_test_v_control_and_i__B->Logic[0U] =
      Copy_of_test_v_control_a_ConstP.pooled16[(uint32_T)rowIdx];
    Copy_of_test_v_control_and_i__B->Logic[1U] =
      Copy_of_test_v_control_a_ConstP.pooled16[rowIdx + 8U];
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
      /* Memory: '<S31>/Memory' */
      Copy_of_test_v_control_and_i__B->Memory_n =
        Copy_of_test_v_control_and_i_DW->Memory_PreviousInput_a;
    }

    /* CombinatorialLogic: '<S31>/Logic' incorporates:
     *  Constant: '<S10>/Constant2'
     *  Constant: '<S32>/Constant2'
     *  RelationalOperator: '<S32>/Relational Operator'
     *  RelationalOperator: '<S32>/Relational Operator1'
     *  Sum: '<S10>/Sum'
     *  Sum: '<S10>/Sum1'
     *  Sum: '<S32>/Sum'
     *  Sum: '<S32>/Sum1'
     */
    rowIdx = (int32_T)(((((uint32_T)((Copy_of_test_v_control_and_i__B->Divide +
      0.44444) - Copy_of_test_v_control_and_i__B->StateSpace_o1[22] >= 1.0) << 1)
                         + (Copy_of_test_v_control_and_i__B->StateSpace_o1[22] -
      (Copy_of_test_v_control_and_i__B->Divide - 0.44444) >= 1.0)) << 1) +
                       Copy_of_test_v_control_and_i__B->Memory_n);
    Copy_of_test_v_control_and_i__B->Logic_p[0U] =
      Copy_of_test_v_control_a_ConstP.pooled16[(uint32_T)rowIdx];
    Copy_of_test_v_control_and_i__B->Logic_p[1U] =
      Copy_of_test_v_control_a_ConstP.pooled16[rowIdx + 8U];
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
      /* Memory: '<S33>/Memory' */
      Copy_of_test_v_control_and_i__B->Memory_i =
        Copy_of_test_v_control_and_i_DW->Memory_PreviousInput_f;
    }

    /* TransferFcn: '<S13>/Transfer Fcn2' */
    Copy_of_test_v_control_and_i__B->TransferFcn2_o = 0.0;
    Copy_of_test_v_control_and_i__B->TransferFcn2_o += 188.0 *
      Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_f;

    /* Sum: '<S13>/Sum' incorporates:
     *  Constant: '<Root>/Vref 2'
     */
    Copy_of_test_v_control_and_i__B->Sum_p =
      (Copy_of_test_v_control_and_i__B->FromWorkspace2 -
       Copy_of_test_v_control_and_i__B->TransferFcn2_o) + 750.0;

    /* Gain: '<S13>/Gain' */
    Copy_of_test_v_control_and_i__B->Gain_h = 0.375 *
      Copy_of_test_v_control_and_i__B->Sum_p;

    /* Product: '<S13>/Divide' incorporates:
     *  Product: '<S13>/Product'
     *  TransferFcn: '<S13>/Transfer Fcn1'
     */
    Copy_of_test_v_control_and_i__B->Divide_l = (0.078554595443833461 *
      Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_d +
      0.74999999999999989 * Copy_of_test_v_control_and_i__B->Gain_h) *
      Copy_of_test_v_control_and_i__B->StateSpace_o1[16] /
      Copy_of_test_v_control_and_i__B->StateSpace_o1[12];

    /* CombinatorialLogic: '<S33>/Logic' incorporates:
     *  Constant: '<S11>/Constant2'
     *  Constant: '<S34>/Constant2'
     *  RelationalOperator: '<S34>/Relational Operator'
     *  RelationalOperator: '<S34>/Relational Operator1'
     *  Sum: '<S11>/Sum'
     *  Sum: '<S11>/Sum1'
     *  Sum: '<S34>/Sum'
     *  Sum: '<S34>/Sum1'
     */
    rowIdx = (int32_T)(((((uint32_T)((Copy_of_test_v_control_and_i__B->Divide_l
      + 0.44444) - Copy_of_test_v_control_and_i__B->StateSpace_o1[20] >= 1.0) <<
                          1) + (Copy_of_test_v_control_and_i__B->StateSpace_o1
      [20] - (Copy_of_test_v_control_and_i__B->Divide_l - 0.44444) >= 1.0)) << 1)
                       + Copy_of_test_v_control_and_i__B->Memory_i);
    Copy_of_test_v_control_and_i__B->Logic_c[0U] =
      Copy_of_test_v_control_a_ConstP.pooled16[(uint32_T)rowIdx];
    Copy_of_test_v_control_and_i__B->Logic_c[1U] =
      Copy_of_test_v_control_a_ConstP.pooled16[rowIdx + 8U];
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    }

    /* DataTypeConversion: '<S53>/Data Type Conversion' */
    Copy_of_test_v_control_and_i__B->DataTypeConversion =
      Copy_of_test_v_control_and_i__B->Logic_p[0];
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    }

    /* DataTypeConversion: '<S71>/Data Type Conversion' */
    Copy_of_test_v_control_and_i__B->DataTypeConversion_p =
      Copy_of_test_v_control_and_i__B->Logic[0];

    /* S-Function (sfun_tstart): '<S60>/startTime' */
    /* S-Function Block (sfun_tstart): <S60>/startTime */
    Copy_of_test_v_control_and_i__B->startTime = (0.0);
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    }

    /* DataTypeConversion: '<S89>/Data Type Conversion' */
    Copy_of_test_v_control_and_i__B->DataTypeConversion_a =
      Copy_of_test_v_control_and_i__B->Logic_c[0];

    /* S-Function (sfun_tstart): '<S78>/startTime' */
    /* S-Function Block (sfun_tstart): <S78>/startTime */
    Copy_of_test_v_control_and_i__B->startTime_p = (0.0);

    /* RelationalOperator: '<Root>/Relational Operator' incorporates:
     *  Clock: '<Root>/Clock'
     *  Constant: '<Root>/Constant1'
     */
    Copy_of_test_v_control_and_i__B->RelationalOperator =
      (Copy_of_test_v_control_and_i_M->Timing.t[0] <= 0.01);
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
      /* Assertion: '<Root>/Assertion' */
      utAssert(Copy_of_test_v_control_and_i__B->RelationalOperator);
    }

    /* Lookup: '<S22>/Look-Up Table' incorporates:
     *  Clock: '<S22>/Clock'
     */
    Copy_of_test_v_control_and_i__B->LookUpTable = rt_Lookup
      (Copy_of_test_v_control_a_ConstP.LookUpTable_XData, 5,
       Copy_of_test_v_control_and_i_M->Timing.t[0],
       Copy_of_test_v_control_a_ConstP.LookUpTable_YData);

    /* Derivative: '<S22>/Derivative' */
    if ((Copy_of_test_v_control_and_i_DW->TimeStampA >=
         Copy_of_test_v_control_and_i_M->Timing.t[0]) &&
        (Copy_of_test_v_control_and_i_DW->TimeStampB >=
         Copy_of_test_v_control_and_i_M->Timing.t[0])) {
      Copy_of_test_v_control_and_i__B->Derivative = 0.0;
    } else {
      rtb_Clock = Copy_of_test_v_control_and_i_DW->TimeStampA;
      lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeA;
      if (Copy_of_test_v_control_and_i_DW->TimeStampA <
          Copy_of_test_v_control_and_i_DW->TimeStampB) {
        if (Copy_of_test_v_control_and_i_DW->TimeStampB <
            Copy_of_test_v_control_and_i_M->Timing.t[0]) {
          rtb_Clock = Copy_of_test_v_control_and_i_DW->TimeStampB;
          lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeB;
        }
      } else {
        if (Copy_of_test_v_control_and_i_DW->TimeStampA >=
            Copy_of_test_v_control_and_i_M->Timing.t[0]) {
          rtb_Clock = Copy_of_test_v_control_and_i_DW->TimeStampB;
          lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeB;
        }
      }

      Copy_of_test_v_control_and_i__B->Derivative =
        (Copy_of_test_v_control_and_i__B->LookUpTable - *lastU) /
        (Copy_of_test_v_control_and_i_M->Timing.t[0] - rtb_Clock);
    }

    /* End of Derivative: '<S22>/Derivative' */
  }

  if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Copy_of_test_v_control_and_i_M->rtwLogInfo,
                        (Copy_of_test_v_control_and_i_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    real_T *lastU;
    if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
      /* Update for S-Function (sfun_spssw_discc): '<S91>/State-Space' incorporates:
       *  Constant: '<S26>/DC'
       *  Constant: '<S27>/DC'
       *  Constant: '<S28>/DC'
       *  Constant: '<S46>/eee'
       *  Constant: '<S64>/eee'
       *  Constant: '<S82>/eee'
       *  Constant: '<S93>/SwitchCurrents'
       */

      /* S-Function block: <S91>/State-Space */
      {
        const real_T *As = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.AS;
        const real_T *Bs = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BS;
        real_T *xtmp = (real_T*)
          Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.XTMP;
        real_T accum;

        /* Calculate new states... */
        {
          int_T i1;
          real_T *xd = &Copy_of_test_v_control_and_i_DW->StateSpace_DSTATE[0];
          for (i1=0; i1 < 7; i1++) {
            accum = 0.0;

            {
              int_T i2;
              real_T *xd = &Copy_of_test_v_control_and_i_DW->StateSpace_DSTATE[0];
              for (i2=0; i2 < 7; i2++) {
                accum += *(As++) * xd[i2];
              }
            }

            {
              int_T i2;
              const real_T *u0 =
                Copy_of_test_v_control_a_ConstP.SwitchCurrents_Value;
              for (i2=0; i2 < 10; i2++) {
                accum += *(Bs++) * u0[i2];
              }

              accum += *(Bs++) * 200.0;
              accum += *(Bs++) * 200.0;
              accum += *(Bs++) * 200.0;
              accum += *(Bs++) * 0.8;
              accum += *(Bs++) * 0.8;
              accum += *(Bs++) * 0.8;
            }

            xtmp[i1] = accum;
          }
        }

        {
          int_T i1;
          real_T *xd = &Copy_of_test_v_control_and_i_DW->StateSpace_DSTATE[0];
          for (i1=0; i1 < 7; i1++) {
            xd[i1] = xtmp[i1];
          }
        }

        {
          int_T *gState = (int_T*)
            Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.G_STATE;

          /* Store switch gates values for next step */
          *(gState++) = (int_T)
            Copy_of_test_v_control_and_i__B->DataTypeConversion_p;
          *(gState++) = (int_T)
            Copy_of_test_v_control_and_i__B->DataTypeConversion;
          *(gState++) = (int_T)
            Copy_of_test_v_control_and_i__B->DataTypeConversion_a;
          *(gState++) = (int_T) Copy_of_test_v_control_and_i__B->LookUpTable;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
        }
      }

      /* Update for Memory: '<S29>/Memory' */
      Copy_of_test_v_control_and_i_DW->Memory_PreviousInput =
        Copy_of_test_v_control_and_i__B->Logic[0];

      /* Update for Memory: '<S31>/Memory' */
      Copy_of_test_v_control_and_i_DW->Memory_PreviousInput_a =
        Copy_of_test_v_control_and_i__B->Logic_p[0];

      /* Update for Memory: '<S33>/Memory' */
      Copy_of_test_v_control_and_i_DW->Memory_PreviousInput_f =
        Copy_of_test_v_control_and_i__B->Logic_c[0];
    }

    /* Update for Derivative: '<S22>/Derivative' */
    if (Copy_of_test_v_control_and_i_DW->TimeStampA == (rtInf)) {
      Copy_of_test_v_control_and_i_DW->TimeStampA =
        Copy_of_test_v_control_and_i_M->Timing.t[0];
      lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeA;
    } else if (Copy_of_test_v_control_and_i_DW->TimeStampB == (rtInf)) {
      Copy_of_test_v_control_and_i_DW->TimeStampB =
        Copy_of_test_v_control_and_i_M->Timing.t[0];
      lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeB;
    } else if (Copy_of_test_v_control_and_i_DW->TimeStampA <
               Copy_of_test_v_control_and_i_DW->TimeStampB) {
      Copy_of_test_v_control_and_i_DW->TimeStampA =
        Copy_of_test_v_control_and_i_M->Timing.t[0];
      lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeA;
    } else {
      Copy_of_test_v_control_and_i_DW->TimeStampB =
        Copy_of_test_v_control_and_i_M->Timing.t[0];
      lastU = &Copy_of_test_v_control_and_i_DW->LastUAtTimeB;
    }

    *lastU = Copy_of_test_v_control_and_i__B->LookUpTable;

    /* End of Update for Derivative: '<S22>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Copy_of_test_v_control_and_i_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Copy_of_test_v_control_and_i_M)!=-1) &&
          !((rtmGetTFinal(Copy_of_test_v_control_and_i_M)-
             (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                Copy_of_test_v_control_and_i_M->Timing.clockTickH1* 4294967296.0))
              * 0.01)) > (((Copy_of_test_v_control_and_i_M->Timing.clockTick1+
                            Copy_of_test_v_control_and_i_M->Timing.clockTickH1*
                            4294967296.0)) * 0.01) * (DBL_EPSILON))) {
        rtmSetErrorStatus(Copy_of_test_v_control_and_i_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(Copy_of_test_v_control_and_i_M->solverInfo,
      Copy_of_test_v_control_and_i_M);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Copy_of_test_v_control_and_i_M->Timing.clockTick0)) {
      ++Copy_of_test_v_control_and_i_M->Timing.clockTickH0;
    }

    Copy_of_test_v_control_and_i_M->Timing.t[0] = rtsiGetSolverStopTime
      (Copy_of_test_v_control_and_i_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Copy_of_test_v_control_and_i_M->Timing.clockTick1++;
      if (!Copy_of_test_v_control_and_i_M->Timing.clockTick1) {
        Copy_of_test_v_control_and_i_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Copy_of_test_v_control_and_i_control_with_droop_copy_derivatives
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M)
{
  B_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__B =
    ((B_Copy_of_test_v_control_and__T *) Copy_of_test_v_control_and_i_M->blockIO);
  X_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__X =
    ((X_Copy_of_test_v_control_and__T *)
     Copy_of_test_v_control_and_i_M->contStates);
  XDot_Copy_of_test_v_control_a_T *_rtXdot;
  _rtXdot = ((XDot_Copy_of_test_v_control_a_T *)
             Copy_of_test_v_control_and_i_M->derivs);

  /* Derivatives for TransferFcn: '<S8>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE = 0.0;
  _rtXdot->TransferFcn2_CSTATE += -188.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE;
  _rtXdot->TransferFcn2_CSTATE += Copy_of_test_v_control_and_i__B->
    StateSpace_o1[15];

  /* Derivatives for TransferFcn: '<S8>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += -0.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += Copy_of_test_v_control_and_i__B->Gain;

  /* Derivatives for TransferFcn: '<S8>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -314.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE;

  /* Derivatives for TransferFcn: '<S12>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE_p = 0.0;
  _rtXdot->TransferFcn2_CSTATE_p += -188.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_p;
  _rtXdot->TransferFcn2_CSTATE_p +=
    Copy_of_test_v_control_and_i__B->StateSpace_o1[10];

  /* Derivatives for TransferFcn: '<S12>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE_a = 0.0;
  _rtXdot->TransferFcn1_CSTATE_a += -0.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_a;
  _rtXdot->TransferFcn1_CSTATE_a += Copy_of_test_v_control_and_i__B->Gain_j;

  /* Derivatives for TransferFcn: '<S13>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE_f = 0.0;
  _rtXdot->TransferFcn2_CSTATE_f += -188.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_f;
  _rtXdot->TransferFcn2_CSTATE_f +=
    Copy_of_test_v_control_and_i__B->StateSpace_o1[16];

  /* Derivatives for TransferFcn: '<S13>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE_d = 0.0;
  _rtXdot->TransferFcn1_CSTATE_d += -0.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_d;
  _rtXdot->TransferFcn1_CSTATE_d += Copy_of_test_v_control_and_i__B->Gain_h;

  /* Derivatives for TransferFcn: '<S12>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_a = 0.0;
  _rtXdot->TransferFcn_CSTATE_a += -314.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE_a;

  /* Derivatives for TransferFcn: '<S13>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_o = 0.0;
  _rtXdot->TransferFcn_CSTATE_o += -314.0 *
    Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE_o;
}

/* Model initialize function */
void Copy_of_test_v_control_and_i_control_with_droop_copy_initialize
  (RT_MODEL_Copy_of_test_v_contr_T *const Copy_of_test_v_control_and_i_M)
{
  DW_Copy_of_test_v_control_and_T *Copy_of_test_v_control_and_i_DW =
    ((DW_Copy_of_test_v_control_and_T *) Copy_of_test_v_control_and_i_M->dwork);
  X_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__X =
    ((X_Copy_of_test_v_control_and__T *)
     Copy_of_test_v_control_and_i_M->contStates);

  /* Start for S-Function (sfun_spssw_discc): '<S91>/State-Space' incorporates:
   *  Constant: '<S26>/DC'
   *  Constant: '<S27>/DC'
   *  Constant: '<S28>/DC'
   *  Constant: '<S46>/eee'
   *  Constant: '<S64>/eee'
   *  Constant: '<S82>/eee'
   *  Constant: '<S93>/SwitchCurrents'
   */

  /* S-Function block: <S91>/State-Space */
  {
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.AS = (real_T*)calloc(7 * 7,
      sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BS = (real_T*)calloc(7 *
      16, sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.CS = (real_T*)calloc(25 *
      7, sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DS = (real_T*)calloc(25 *
      16, sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DX_COL = (real_T*)calloc
      (25, sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.TMP2 = (real_T*)calloc(16,
      sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BD_COL = (real_T*)calloc(7,
      sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.TMP1 = (real_T*)calloc(7,
      sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.XTMP = (real_T*)calloc(7,
      sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS = (int_T*)
      calloc(10, sizeof(int_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SW_CHG = (int_T*)calloc(10,
      sizeof(int_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.G_STATE = (int_T*)calloc
      (10, sizeof(int_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.Y_SWITCH = (real_T*)calloc
      (10, sizeof(real_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_TYPES = (int_T*)
      calloc(10, sizeof(int_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.IDX_OUT_SW = (int_T*)
      calloc(10, sizeof(int_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS_INIT =
      (int_T*)calloc(10, sizeof(int_T));
    Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.USWLAST = (real_T*)calloc
      (10, sizeof(real_T));
  }

  /* Start for Scope: '<Root>/I_out_0' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] =
      "Copy_of_test_v_control_and_i_control_with_droop_copy/I_out_0";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    Copy_of_test_v_control_and_i_DW->I_out_0_PWORK.LoggedData =
      rt_CreateStructLogVar(
      Copy_of_test_v_control_and_i_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Copy_of_test_v_control_and_i_M),
      Copy_of_test_v_control_and_i_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)),
      "I_out_0",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (Copy_of_test_v_control_and_i_DW->I_out_0_PWORK.LoggedData == (NULL))
      return;
  }

  /* Start for Scope: '<Root>/I_out_1' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] =
      "Copy_of_test_v_control_and_i_control_with_droop_copy/I_out_1";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    Copy_of_test_v_control_and_i_DW->I_out_1_PWORK.LoggedData =
      rt_CreateStructLogVar(
      Copy_of_test_v_control_and_i_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Copy_of_test_v_control_and_i_M),
      Copy_of_test_v_control_and_i_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)),
      "I_out_1",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (Copy_of_test_v_control_and_i_DW->I_out_1_PWORK.LoggedData == (NULL))
      return;
  }

  /* Start for Scope: '<Root>/I_out_2' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] =
      "Copy_of_test_v_control_and_i_control_with_droop_copy/I_out_2";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    Copy_of_test_v_control_and_i_DW->I_out_2_PWORK.LoggedData =
      rt_CreateStructLogVar(
      Copy_of_test_v_control_and_i_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Copy_of_test_v_control_and_i_M),
      Copy_of_test_v_control_and_i_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)),
      "I_out_2",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (Copy_of_test_v_control_and_i_DW->I_out_2_PWORK.LoggedData == (NULL))
      return;
  }

  /* Start for Scope: '<Root>/V_out_0' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] =
      "Copy_of_test_v_control_and_i_control_with_droop_copy/V_out_0";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    Copy_of_test_v_control_and_i_DW->V_out_0_PWORK.LoggedData =
      rt_CreateStructLogVar(
      Copy_of_test_v_control_and_i_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Copy_of_test_v_control_and_i_M),
      Copy_of_test_v_control_and_i_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)),
      "V_out_0",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (Copy_of_test_v_control_and_i_DW->V_out_0_PWORK.LoggedData == (NULL))
      return;
  }

  /* Start for Scope: '<Root>/V_out_1' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] =
      "Copy_of_test_v_control_and_i_control_with_droop_copy/V_out_1";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    Copy_of_test_v_control_and_i_DW->V_out_1_PWORK.LoggedData =
      rt_CreateStructLogVar(
      Copy_of_test_v_control_and_i_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Copy_of_test_v_control_and_i_M),
      Copy_of_test_v_control_and_i_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)),
      "V_out_1",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (Copy_of_test_v_control_and_i_DW->V_out_1_PWORK.LoggedData == (NULL))
      return;
  }

  /* Start for Scope: '<Root>/V_out_2' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1 };

    BuiltInDTypeId dTypes[1] = { SS_DOUBLE };

    static char_T rt_ScopeBlockName[] =
      "Copy_of_test_v_control_and_i_control_with_droop_copy/V_out_2";
    static int_T rt_ScopeFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    Copy_of_test_v_control_and_i_DW->V_out_2_PWORK.LoggedData =
      rt_CreateStructLogVar(
      Copy_of_test_v_control_and_i_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Copy_of_test_v_control_and_i_M),
      Copy_of_test_v_control_and_i_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)),
      "V_out_2",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (Copy_of_test_v_control_and_i_DW->V_out_2_PWORK.LoggedData == (NULL))
      return;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
      21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0,
      45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0,
      69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0,
      81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0,
      93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0,
      104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0,
      114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 121.0, 122.0, 123.0,
      124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0,
      134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
      144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0, 152.0, 153.0,
      154.0, 155.0, 156.0, 157.0, 158.0, 159.0, 160.0, 161.0, 162.0, 163.0,
      164.0, 165.0, 166.0, 167.0, 168.0, 169.0, 170.0, 171.0, 172.0, 173.0,
      174.0, 175.0, 176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
      184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0,
      194.0, 195.0, 196.0, 197.0, 198.0, 199.0, 200.0, 201.0, 202.0, 203.0,
      204.0, 205.0, 206.0, 207.0, 208.0, 209.0, 210.0, 211.0, 212.0, 213.0,
      214.0, 215.0, 216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
      224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0, 232.0, 233.0,
      234.0, 235.0, 236.0, 237.0, 238.0, 239.0, 240.0, 241.0, 242.0, 243.0,
      244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0, 253.0,
      254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
      264.0, 265.0, 266.0, 267.0, 268.0, 269.0, 270.0, 271.0, 272.0, 273.0,
      274.0, 275.0, 276.0, 277.0, 278.0, 279.0, 280.0, 281.0, 282.0, 283.0,
      284.0, 285.0, 286.0, 287.0, 288.0, 289.0, 290.0, 291.0, 292.0, 293.0,
      294.0, 295.0, 296.0, 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0,
      304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0, 313.0,
      314.0, 315.0, 316.0, 317.0, 318.0, 319.0, 320.0, 321.0, 322.0, 323.0,
      324.0, 325.0, 326.0, 327.0, 328.0, 329.0, 330.0, 331.0, 332.0, 333.0,
      334.0, 335.0, 336.0, 337.0, 338.0, 339.0, 340.0, 341.0, 342.0, 343.0,
      344.0, 345.0, 346.0, 347.0, 348.0, 349.0, 350.0, 351.0, 352.0, 353.0,
      354.0, 355.0, 356.0, 357.0, 358.0, 359.0, 360.0, 361.0, 362.0, 363.0,
      364.0, 365.0, 366.0, 367.0, 368.0, 369.0, 370.0, 371.0, 372.0, 373.0,
      374.0, 375.0, 376.0, 377.0, 378.0, 379.0, 380.0, 381.0, 382.0, 383.0,
      384.0, 385.0, 386.0, 387.0, 388.0, 389.0, 390.0, 391.0, 392.0, 393.0,
      394.0, 395.0, 396.0, 397.0, 398.0, 399.0, 400.0, 401.0, 402.0, 403.0,
      404.0, 405.0, 406.0, 407.0, 408.0, 409.0, 410.0, 411.0, 412.0, 413.0,
      414.0, 415.0, 416.0, 417.0, 418.0, 419.0, 420.0, 421.0, 422.0, 423.0,
      424.0, 425.0, 426.0, 427.0, 428.0, 429.0, 430.0, 431.0, 432.0, 433.0,
      434.0, 435.0, 436.0, 437.0, 438.0, 439.0, 440.0, 441.0, 442.0, 443.0,
      444.0, 445.0, 446.0, 447.0, 448.0, 449.0, 450.0, 451.0, 452.0, 453.0,
      454.0, 455.0, 456.0, 457.0, 458.0, 459.0, 460.0, 461.0, 462.0, 463.0,
      464.0, 465.0, 466.0, 467.0, 468.0, 469.0, 470.0, 471.0, 472.0, 473.0,
      474.0, 475.0, 476.0, 477.0, 478.0, 479.0, 480.0, 481.0, 482.0, 483.0,
      484.0, 485.0, 486.0, 487.0, 488.0, 489.0, 490.0, 491.0, 492.0, 493.0,
      494.0, 495.0, 496.0, 497.0, 498.0, 499.0, 500.0, 501.0, 502.0, 503.0,
      504.0, 505.0, 506.0, 507.0, 508.0, 509.0, 510.0, 511.0, 512.0, 513.0,
      514.0, 515.0, 516.0, 517.0, 518.0, 519.0, 520.0, 521.0, 522.0, 523.0,
      524.0, 525.0, 526.0, 527.0, 528.0, 529.0, 530.0, 531.0, 532.0, 533.0,
      534.0, 535.0, 536.0, 537.0, 538.0, 539.0, 540.0, 541.0, 542.0, 543.0,
      544.0, 545.0, 546.0, 547.0, 548.0, 549.0, 550.0, 551.0, 552.0, 553.0,
      554.0, 555.0, 556.0, 557.0, 558.0, 559.0, 560.0, 561.0, 562.0, 563.0,
      564.0, 565.0, 566.0, 567.0, 568.0, 569.0, 570.0, 571.0, 572.0, 573.0,
      574.0, 575.0, 576.0, 577.0, 578.0, 579.0, 580.0, 581.0, 582.0, 583.0,
      584.0, 585.0, 586.0, 587.0, 588.0, 589.0, 590.0, 591.0, 592.0, 593.0,
      594.0, 595.0, 596.0, 597.0, 598.0, 599.0, 600.0, 601.0, 602.0, 603.0,
      604.0, 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0,
      614.0, 615.0, 616.0, 617.0, 618.0, 619.0, 620.0, 621.0, 622.0, 623.0,
      624.0, 625.0, 626.0, 627.0, 628.0, 629.0, 630.0, 631.0, 632.0, 633.0,
      634.0, 635.0, 636.0, 637.0, 638.0, 639.0, 640.0, 641.0, 642.0, 643.0,
      644.0, 645.0, 646.0, 647.0, 648.0, 649.0, 650.0, 651.0, 652.0, 653.0,
      654.0, 655.0, 656.0, 657.0, 658.0, 659.0, 660.0, 661.0, 662.0, 663.0,
      664.0, 665.0, 666.0, 667.0, 668.0, 669.0, 670.0, 671.0, 672.0, 673.0,
      674.0, 675.0, 676.0, 677.0, 678.0, 679.0, 680.0, 681.0, 682.0, 683.0,
      684.0, 685.0, 686.0, 687.0, 688.0, 689.0, 690.0, 691.0, 692.0, 693.0,
      694.0, 695.0, 696.0, 697.0, 698.0, 699.0, 700.0, 701.0, 702.0, 703.0,
      704.0, 705.0, 706.0, 707.0, 708.0, 709.0, 710.0, 711.0, 712.0, 713.0,
      714.0, 715.0, 716.0, 717.0, 718.0, 719.0, 720.0, 721.0, 722.0, 723.0,
      724.0, 725.0, 726.0, 727.0, 728.0, 729.0, 730.0, 731.0, 732.0, 733.0,
      734.0, 735.0, 736.0, 737.0, 738.0, 739.0, 740.0, 741.0, 742.0, 743.0,
      744.0, 745.0, 746.0, 747.0, 748.0, 749.0, 750.0, 751.0, 752.0, 753.0,
      754.0, 755.0, 756.0, 757.0, 758.0, 759.0, 760.0, 761.0, 762.0, 763.0,
      764.0, 765.0, 766.0, 767.0, 768.0, 769.0, 770.0, 771.0, 772.0, 773.0,
      774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0, 782.0, 783.0,
      784.0, 785.0, 786.0, 787.0, 788.0, 789.0, 790.0, 791.0, 792.0, 793.0,
      794.0, 795.0, 796.0, 797.0, 798.0, 799.0, 800.0, 801.0, 802.0, 803.0,
      804.0, 805.0, 806.0, 807.0, 808.0, 809.0, 810.0, 811.0, 812.0, 813.0,
      814.0, 815.0, 816.0, 817.0, 818.0, 819.0, 820.0, 821.0, 822.0, 823.0,
      824.0, 825.0, 826.0, 827.0, 828.0, 829.0, 830.0, 831.0, 832.0, 833.0,
      834.0, 835.0, 836.0, 837.0, 838.0, 839.0, 840.0, 841.0, 842.0, 843.0,
      844.0, 845.0, 846.0, 847.0, 848.0, 849.0, 850.0, 851.0, 852.0, 853.0,
      854.0, 855.0, 856.0, 857.0, 858.0, 859.0, 860.0, 861.0, 862.0, 863.0,
      864.0, 865.0, 866.0, 867.0, 868.0, 869.0, 870.0, 871.0, 872.0, 873.0,
      874.0, 875.0, 876.0, 877.0, 878.0, 879.0, 880.0, 881.0, 882.0, 883.0,
      884.0, 885.0, 886.0, 887.0, 888.0, 889.0, 890.0, 891.0, 892.0, 893.0,
      894.0, 895.0, 896.0, 897.0, 898.0, 899.0, 900.0, 901.0, 902.0, 903.0,
      904.0, 905.0, 906.0, 907.0, 908.0, 909.0, 910.0, 911.0, 912.0, 913.0,
      914.0, 915.0, 916.0, 917.0, 918.0, 919.0, 920.0, 921.0, 922.0, 923.0,
      924.0, 925.0, 926.0, 927.0, 928.0, 929.0, 930.0, 931.0, 932.0, 933.0,
      934.0, 935.0, 936.0, 937.0, 938.0, 939.0, 940.0, 941.0, 942.0, 943.0,
      944.0, 945.0, 946.0, 947.0, 948.0, 949.0, 950.0, 951.0, 952.0, 953.0,
      954.0, 955.0, 956.0, 957.0, 958.0, 959.0, 960.0, 961.0, 962.0, 963.0,
      964.0, 965.0, 966.0, 967.0, 968.0, 969.0, 970.0, 971.0, 972.0, 973.0,
      974.0, 975.0, 976.0, 977.0, 978.0, 979.0, 980.0, 981.0, 982.0, 983.0,
      984.0, 985.0, 986.0, 987.0, 988.0, 989.0, 990.0, 991.0, 992.0, 993.0,
      994.0, 995.0, 996.0, 997.0, 998.0, 999.0 } ;

    static real_T pDataValues0[] = { 0.040736184319658947, 0.045289596853780964,
      0.0063493408146753031, 0.045668792806950971, 0.031617962311270474,
      0.0048770202499704767, 0.013924910943352421, 0.027344075960249195,
      0.047875341771714881, 0.048244426759963828, 0.0078806540838774145,
      0.04852963908803079, 0.047858347412147284, 0.024268782436142063,
      0.040014023444440008, 0.007094316931360767, 0.021088064131313752,
      0.045786776259453356, 0.039610366477977721, 0.047974621319645153,
      0.032787034957829343, 0.0017855839287094777, 0.042456465293438855,
      0.046699662387877532, 0.033936757742888672, 0.037887006528916675,
      0.037156623406245808, 0.019611350976708408, 0.032773894508877834,
      0.008559334390578089, 0.035302304400980443, 0.0015916423188710338,
      0.013846149248044498, 0.0023085695315576971, 0.0048565890617923773,
      0.041172891416364633, 0.034741431148790851, 0.015854974003043028,
      0.047511102441917752, 0.0017223040251454381, 0.021937217982819914,
      0.019077922854650421, 0.038275839407450121, 0.03975999505685316,
      0.00934363022771893, 0.024488219789411556, 0.022279310035544977,
      0.032315650505563231, 0.035468241542903629, 0.037734334099118048,
      0.013801253849928918, 0.033985133842683743, 0.032754900198692032,
      0.0081305867597315281, 0.0059498840779188327, 0.02491820259910715,
      0.047987197925804054, 0.017019286333306662, 0.02926338754898887,
      0.011190596974556849, 0.037563352965282647, 0.012754755772963457,
      0.025297852583257119, 0.0349538361328343, 0.044545162626789925,
      0.047964571260272218, 0.027360776498190156, 0.0069312221414339573,
      0.0074647002779528737, 0.012875412706186824, 0.04203586279918313,
      0.012714108948576552, 0.040714241303440819, 0.012176248436249466,
      0.046463181159361391, 0.017499188299240437, 0.00982976252156041,
      0.012554192898801553, 0.03080223380733196, 0.023664442445136463,
      0.01758297535314984, 0.041541431394814546, 0.029263204557636216,
      0.027486180414556978, 0.0458596831914905, 0.014291950941018677,
      0.037860011455536066, 0.037686454713924768, 0.019022292348767834,
      0.028391082036261058, 0.0037927144781531811, 0.0026975059333303577,
      0.026539877650448636, 0.038958361505100562, 0.046700534211459151,
      0.0064953104236865067, 0.028441183043609639, 0.023469532052910292,
      0.00059510347506206991, 0.016856132219944076, 0.0081091154096621376,
      0.039714227034195353, 0.015560752102240245, 0.026426656775310638,
      0.008282436474989047, 0.030099097070081827, 0.013148564227007215,
      0.032703954923839117, 0.034460725157000389, 0.037407579641185476,
      0.022527079925124888, 0.0041910688998466287, 0.011448848435840943,
      0.04566686807508348, 0.0076189009484611495, 0.041290848874477371,
      0.026917121763002858, 0.049806735831344276, 0.0039087764376591842,
      0.022133913488772319, 0.00533263850902922, 0.048094904042752684,
      0.0002317112067033722, 0.038745523235575119, 0.040865161032671654,
      0.043434735268175484, 0.0042217922755455163, 0.019989132454944825,
      0.012993520142532711, 0.040003424011215379, 0.021570691373177232,
      0.045532379721476147, 0.0090923514151426254, 0.013190145826099503,
      0.0072769490192358512, 0.0068034279354331874, 0.04346461038200447,
      0.02898522936827851, 0.0274930100918166, 0.0072477399111863412,
      0.042651555886094684, 0.0311027565742533, 0.017547619044613546,
      0.025662476993352668, 0.020090401687597088, 0.0037983345845420957,
      0.011995807677682902, 0.0061659467417582775, 0.0091953894141208366,
      0.01199762628324514, 0.020863353454218476, 0.0024827215162871066,
      0.045135805495764056, 0.0472393594860823, 0.024543204623403998,
      0.024462631920000946, 0.016885970491068859, 0.0450026923208831,
      0.018462339056010753, 0.0055601377646893714, 0.0390126034160569,
      0.019486941848062673, 0.012084564295691637, 0.020195607279405739,
      0.00482272625841943, 0.0065986646303167534, 0.047102529538774258,
      0.047806727011490115, 0.028760429753923279, 0.0029889771473577912,
      0.011738995668620317, 0.017657928561103552, 0.041059702009897954,
      0.00077017188257775268, 0.0021511900828903919, 0.0084495014731352184,
      0.0324557737478226, 0.036586119282933517, 0.03238729815681534,
      0.022546185321547247, 0.027350444614317251, 0.014816040280388659,
      0.037234640353707812, 0.009447750751627227, 0.034338771668265752,
      0.0091755577868634867, 0.018424229824516827, 0.031280928036484516,
      0.039011371757568844, 0.0040562884432892637, 0.046469298548436504,
      0.038785633930420116, 0.024339581620158618, 0.021792929429045954,
      0.022339187471490315, 0.01531747360082787, 0.025425432769056351,
      0.025538578208605486, 0.040881385416113108, 0.039741570844172652,
      0.032215906509684582, 0.018930469133013425, 0.040579022914123859,
      0.026641279439972743, 0.017536355178844165, 0.046950078099994345,
      0.043797140574649195, 0.02750781714492111, 0.031123754300061375,
      0.029352235226570839, 0.010387114636651424, 0.015062316513974534,
      0.023546167425879533, 0.011524408010577926, 0.042215439634769453,
      0.0097382144783524638, 0.01129608904861994, 0.00853540235739293,
      0.011383214890827676, 0.021784934205194957, 0.015555114332520643,
      0.046168982105162196, 0.0215103695664792, 0.0092408160062068031,
      0.045244048433994648, 0.048987418917804261, 0.021943498656305162,
      0.0055559611720299388, 0.012903234795603347, 0.020435992305627607,
      0.029744803700430717, 0.013110587389042272, 0.030142154469104149,
      0.03556078902168415, 0.011087336700862005, 0.0058708825427902962,
      0.014833793660916346, 0.015938915096294116, 0.021208337985690363,
      0.02539291423305591, 0.0042757898545021994, 0.013124111734916634,
      0.040050731138486943, 0.0014610138781073147, 0.046442706973902237,
      0.036516543142772646, 0.02443044869017896, 0.028926253051171948,
      0.011864178988576075, 0.022942441408996556, 0.048154426964345652,
      0.0273402859369484, 0.026056791540200075, 0.011579719335426193,
      0.024444887196008347, 0.031203004408684478, 0.033956777043287388,
      0.019775760783429654, 0.018371832427223827, 0.049399100158081639,
      0.001886943311977607, 0.044258400410123772, 0.045664341381961952,
      0.039809193679260606, 0.0049356139327787155, 0.013093559193535803,
      0.016767841998139826, 0.0339863975688669, 0.0068276568677684835,
      0.036061374929087009, 0.0053380930803620724, 0.032687867433427983,
      0.024708696831963507, 0.03895258616156376, 0.035751853920034708,
      0.045186028027815822, 0.044546125216539466, 0.016708152636874814,
      0.034937291616739724, 0.00989049133429646, 0.0015270473152318332,
      0.037203713018373122, 0.025001121779510044, 0.023996107057303026,
      0.04523611190336814, 0.030493332421127922, 0.030883319479422734,
      0.042972115282310618, 0.040274471226484282, 0.028836075780734258,
      0.0091461234707456984, 0.011996600528435869, 0.044325596653805067,
      0.0014337076232053048, 0.024495069425611193, 0.0083963572841128375,
      0.048934032482057938, 0.035634723583945704, 0.025023581207742153,
      0.023554418727096967, 0.0029809433789819598, 0.034098595207453161,
      0.0021215568750370842, 0.0035722732300321192, 0.026082492123214188,
      0.0048365012890433491, 0.040907427692981238, 0.040877354603964321,
      0.036121979618342119, 0.0074932721238983426, 0.032980262645415363,
      0.025929747125526911, 0.048648727738193127, 0.03244957463561781,
      0.040016528767620074, 0.022689885436345977, 0.021619575189173085,
      0.041265689770102282, 0.0041734907429457017, 0.0066585503803580862,
      0.0086694306559502773, 0.01954689011618678, 0.041568987141953478,
      0.040168219580122011, 0.003023558958494682, 0.019962888530678787,
      0.026343791525414797, 0.020839973396539348, 0.032842994548685361,
      0.03139866795950521, 0.014599203998085748, 0.021582558512436012,
      0.00077435628180094751, 0.049203186218957695, 0.0083584204957327986,
      0.0053108172464331922, 0.01862048700277685, 0.0099059201271487329,
      0.024484381900801197, 0.016974670669537884, 0.047581523238886349,
      0.046016601991828193, 0.00263384988403963, 0.036892904775849826,
      0.013455971319927797, 0.021141780750440393, 0.027393545060742236,
      0.04713684921384672, 0.020887205215833111, 0.049152623323492808,
      0.015072747435603273, 0.035054937795046315, 0.033316942579221284,
      0.026956323252142835, 0.034905276009015419, 0.033326395670129343,
      0.0089066227200168876, 0.00640071998600863, 0.04995401973806804,
      0.0085560533178216051, 0.0016300410265264022, 0.028059989635483007,
      0.0440933250225905, 0.033458765226719693, 0.0095216633589977062,
      0.018445827303194745, 0.02303629686302058, 0.049081897548537486,
      0.0078202476113281745, 0.042776140292295567, 0.0322382268435044,
      0.018813610513941582, 0.0095461847618151519, 0.0214126496489693,
      0.024101103051592816, 0.0060305806648581154, 0.029475374234752952,
      0.011309383987633786, 0.019230956218470541, 0.029149319137383695,
      0.012590306123615641, 0.014522033213848968, 0.030854544219661169,
      0.01326404549050147, 0.041218813334441752, 0.049133169986097514,
      0.036512439613379882, 0.017193850205749157, 0.029203466663922602,
      0.0053884507621871532, 0.045315407532486647, 0.043982686224095242,
      0.040888027968532095, 0.013036399952773232, 0.029717812533216544,
      0.0011256296370115882, 0.021262966010706749, 0.015635944341030779,
      0.008074237215587499, 0.00893830933761841, 0.021144284455004228,
      0.004711466944386733, 0.029926183437837057, 0.023546212817916704,
      0.0347974656650804, 0.034994392496414582, 0.031926537913591894,
      0.0016801918033214737, 0.0034403049559025623, 0.015979986759024806,
      0.026543214034706327, 0.032722285387853316, 0.02038095985205763,
      0.040999061139097036, 0.035917947160294186, 0.048432466511554688,
      0.026566695328283724, 0.016257284091028, 0.0052814601664510968,
      0.030547932937310032, 0.038940112091204626, 0.021172645948136917,
      0.0045411642893719737, 0.013323574538953621, 0.007682835879565331,
      0.014050265126693546, 0.022004256950086044, 0.026357137088032612,
      0.0228712182843837, 0.043768579930209245, 0.025902605418055211,
      0.0471811312274194, 0.0318854549036087, 0.047884696992079166,
      0.012035351774008014, 0.033806115193187596, 0.014453228583723839,
      0.033590408270710762, 0.034757024977586863, 0.0033996384235005284,
      0.012739507829850267, 0.011202001541210939, 0.03339163635068583,
      0.04221960782636023, 0.017223120565052107, 0.039025982636567896,
      0.033766603287349976, 0.00033576571592387473, 0.030108524379089764,
      0.019338559726049233, 0.045799562206571269, 5.7552856455361791E-5,
      0.023122457962116434, 0.02121745199076876, 0.023045818301448202,
      0.038507986430430463, 0.01612359035933893, 0.039236964738037082,
      0.023567857685530581, 0.0017881366634558971, 0.0087937207841765463,
      0.036087901669555125, 0.02367429964826602, 0.00763606002191159,
      0.017056230352455466, 0.030369460688417373, 0.00958726277308989,
      0.036921341998847078, 0.012142479915908456, 0.045871217102469122,
      0.013453079334300917, 0.038275000831071923, 0.00943309883957455,
      0.014374908653306562, 0.0045556731843267471, 0.028810469033150349,
      0.034168162164732653, 0.02732965572951614, 0.021286442093559396,
      0.032222139071566826, 0.032380881508634218, 0.0339508377046601,
      0.031789335525704183, 0.047258705655470072, 0.010446746121301143,
      0.035464085135527242, 0.011811528849689829, 0.005969812389865276,
      0.030365197034281734, 0.0225068848482948, 0.022936274682443393,
      0.033097237595282596, 0.038514275740183013, 0.017510900672055251,
      0.033100479917956727, 0.020807929498489825, 0.042096457634565453,
      0.041645840953760789, 0.012822049611457366, 0.030673036840643764,
      0.029112458226361354, 0.027036966856220486, 0.043497051617900372,
      0.0132389513237815, 0.015903703774052959, 0.0059607270527095579,
      0.04699147351724603, 0.032277593748626175, 0.023973161247444391,
      0.031965848052005419, 0.027235805526338142, 0.032365574014656388,
      0.027194296699981954, 0.036052331028990574, 0.026124765288855108,
      0.0496852312060426, 0.010933831619981694, 0.0052899136625114088,
      0.0054848732261597094, 0.0031795685487552849, 0.020228999792881293,
      0.022418645603324766, 0.018290808841908562, 0.038175232042440672,
      0.031394818980708443, 0.038599019277712254, 0.04664267851394098,
      0.048637042700150693, 0.0096014174713887467, 0.0069437101414577653,
      0.034813316854149741, 0.0046910013387432784, 0.026270220192966789,
      0.02651721091964317, 0.043056990569666623, 0.024242666677605097,
      0.01967281806076332, 0.0335715569837013, 0.037062897172710323,
      0.026002623369519341, 0.017385633563876259, 0.0074998626915841532,
      0.029304603361573096, 0.013107265886390369, 0.0022227046139119246,
      0.037746663361558963, 0.012139267891048095, 0.022120115650097166,
      0.034389804256005359, 0.017961410520093032, 0.036817003715060088,
      0.01973537376393816, 0.034170793348398919, 0.0352023715167133,
      0.022115270669168543, 0.00097888117766593559, 0.016542894010703552,
      0.021215474841656874, 0.013513521171603267, 0.00985268990477279,
      0.041086059248065493, 0.021496070469163322, 0.044388547712817694,
      0.019559149773058167, 0.038455719369414783, 0.01983957585068083,
      0.040425704794367259, 0.037753854950354181, 0.018869777241755144,
      0.010800945798069717, 0.039520360898345673, 0.047465195592489851,
      0.016378271703760262, 0.033563218522586993, 0.021932249129347783,
      0.041675029779448765, 0.038442712621480746, 0.0083626772747360852,
      0.043099023935103613, 0.0494936076815752, 0.025721172825285223,
      0.044214051156347772, 0.029401302765424877, 0.0077376174328022355,
      0.0099931411428726032, 0.02034774185694534, 0.037435285910784571,
      0.041279190789307779, 0.039498151497226547, 0.01592621226994961,
      0.02670320636853632, 0.0044975339385290528, 0.0055852872096601724,
      0.0068146274469149341, 0.033932615240009414, 0.024758850954483033,
      0.0094855203008790082, 0.024750291249511044, 0.0073804110988344336,
      0.0027487073453094091, 0.042535633714450377, 0.028027976367744241,
      0.046480443337833161, 0.034833360027761377, 0.029139548258792003,
      0.04076986057387106, 0.043950695229858894, 0.049445580803979455,
      2.6118767847238547E-5, 0.043271929550651234, 0.030628323474199939,
      0.049497510285441547, 0.026384003466922119, 0.023976169260510938,
      0.040067380276097617, 0.011392146785302093, 0.024904714559819487,
      0.045042624426600245, 0.028733060956509383, 0.042258909252701836,
      0.036932014599770094, 0.029299351791323792, 0.012336726299298745,
      0.0333208108659734, 0.0041741406801311335, 0.031297989258579163,
      0.033047227897367117, 0.036487592765861054, 0.044537605816266118,
      0.049115161144180325, 0.038451454266794811, 0.029072324393769888,
      0.0464156531157094, 0.029004518287922082, 0.00084914691686306394,
      0.0060429785549279084, 0.043135535934983482, 0.024214825560605127,
      0.042242783728813162, 0.010470254201046737, 0.027614567076938754,
      0.031494169253221065, 0.0015995507881283455, 0.030735670955857025,
      0.018120573113652633, 0.0024766289521030607, 0.024478499458866088,
      0.0096255198031037388, 0.0061541873772972605, 0.010274708545383994,
      0.0073257455307444933, 0.0094536087236306923, 0.002132620545557168,
      0.0317598958429941, 0.014093342794021496, 0.026929833902267022,
      0.0347581519722166, 0.024955800674129475, 0.026790052787555665,
      0.022259158264802115, 0.0061966138799035069, 0.024517864673400908,
      0.042649907767040814, 0.043696370293086671, 0.013514716614634881,
      0.010423067937565689, 0.028248978536910059, 0.0320155912581379,
      0.0208514475821443, 0.010298775776612168, 0.047396656064658434,
      0.0041035603548862931, 0.0052854713290860725, 0.00710205609519991,
      0.0083230220438210382, 0.031047932196765417, 0.028685488242059909,
      0.0026038945142934813, 0.046560069230412483, 0.036433084083913561,
      0.036892082689879507, 0.0031702250346409113, 0.0430220281519116,
      0.046720255948060674, 0.049219915612048581, 0.042946940834193315,
      0.039277949463251527, 0.025668870929378747, 0.0088801230252932521,
      0.019929474836792156, 0.006696562549398561, 0.0015444774372475767,
      0.0469570853034774, 0.015065303229319611, 0.014776691723767822,
      0.016646814091808765, 0.023353409351442624, 0.032409920323307854,
      0.0012614090746518149, 0.042110330620966724, 0.027951627249434754,
      0.042704997463672158, 0.017393959716363056, 0.022301332402755142,
      0.0027119742220564793, 0.0088553766894554579, 0.033140403098048721,
      0.016541449760165229, 0.044924306891714977, 0.005907759922335532,
      0.049420896439249032, 0.02699910495189646, 0.035345870966138136,
      0.049974581004885235, 0.014392467240756863, 0.020726126944655421,
      0.023241997081256866, 0.038197853924597833, 0.040910201945383542,
      0.0050110770097745788, 0.0089058476943383209, 0.017981745674104016,
      0.0028352344534145592, 0.026094283683063962, 0.016792448733846228,
      0.0087834514837830391, 0.01044733369965677, 0.0452576779502232,
      0.033769558866812342, 0.02342340999519987, 0.045606623711981147,
      0.0052005787389689251, 0.037277303685085868, 0.036813372779831925,
      0.028093071264081872, 0.0092097048757763256, 0.029860567516892745,
      0.014996849504489446, 0.006706146641434119, 0.010630076667942146,
      0.044747083772040723, 0.0035726406393522259, 0.012124327946835973,
      0.0026877196104356906, 0.0220861028532212, 0.00066416002336262554,
      0.044859567548678606, 0.0098329095683816, 0.00466852583775465,
      0.015368344979396004, 0.022802883342187077, 0.0050834696812377574,
      0.049769486382754587, 0.016604641672624956, 0.014867340794396083,
      0.0031022610659816319, 0.014912198594388193, 0.0023175632449090378,
      0.025271407122885149, 0.038071294334505672, 0.03155349996067968,
      0.0044945825388045873, 0.0040431211565156834, 0.03886202682744716,
      0.045256737211178545, 0.026688597588350012, 0.0054577106021229289,
      0.041290442892779916, 0.016904885940108593, 0.014698652651324202,
      0.03731567138518397, 0.00051683091716981939, 0.0024223669626611045,
      0.033395806078681187, 0.030173399191538476, 0.026305123289778062,
      0.036485472411161388, 0.035362674265771075, 0.039068852589963864,
      0.014398848780708563, 0.034626599319325942, 0.027833491748200628,
      0.019826039629079629, 0.0030795333526982328, 0.03900877657455868,
      0.016879193202602255, 0.030393295363147291, 0.0370627024751109,
      0.0052406620986749815, 0.0063944189891497584, 0.0274770053507599,
      0.024261470429247967, 0.044523783959221915, 0.03994801394064397,
      0.036717054184798488, 0.0025665943056185528, 0.0036442649549488062,
      0.0044263729837360211, 0.039917543205697625, 0.047150406978535141,
      0.034185778620417905, 0.0066041477856781383, 0.0361362269828383,
      0.0055176740321174313, 0.0058746426075916465, 0.032035896148296279,
      0.016440710737840137, 0.032690601129788686, 0.037456573155175955,
      0.02915928657274381, 0.037001616399388884, 0.011741345737395215,
      0.036747877084802615, 0.048529926254330724, 0.0433465145875958,
      0.0043117264931748171, 0.018321830815959946, 0.018459940216500909,
      0.034251423633080466, 0.029897081769194457, 0.039468197182095273,
      0.018382645921893849, 0.010301392975259734, 0.0043333273697766126,
      0.038596695854955371, 0.010283726073237992, 0.019413581552390088,
      0.027588926597861375, 0.011447662601155002, 0.032097031019959366,
      0.024224018619909023, 0.00759227625581333, 0.0390965983294001,
      0.0050303161181210754, 0.014703316687931423, 0.011868650985278962,
      0.02654361285139642, 0.004574936566970611, 0.020265770994029566,
      0.0052423123557878261, 0.0056141981078013329, 0.039221394537195642,
      0.014578515895346545, 0.030176671937544343, 0.048221133360795067,
      0.021624249698518051, 0.034737609730897005, 0.037904963764472707,
      0.021632116307355027, 0.032774901990176873, 0.0054877525361525792,
      0.046687992419266626, 0.0093730403210843249, 0.013308941945381942,
      0.03989151301057986, 0.024380188771696183, 0.038447913202943461,
      0.019800337260893759, 0.013646939706184531, 0.0018617317035164007,
      0.03366474570543266, 0.021478222962592653, 0.022586961745236778,
      0.030492858464510803, 0.0029701648429138585, 0.015790571916943302,
      0.038636106543146739, 0.034821649450304741, 0.006266609055459,
      0.0065075725194711775, 0.0046176169359600783, 0.00039101467846674456,
      0.021155469258208326, 0.032778658746895721, 0.036146126234601221,
      0.026560464679121938, 0.0054408969136522716, 0.031588318676424441,
      0.0063249932664651461, 0.0067151652156787313, 0.0049297046355498871,
      0.0071013624215964192, 0.0084125649245763885, 0.0098124461128477683,
      0.015873988757471768, 0.015821449957314548, 0.010878165471141033,
      0.012552092300786806, 0.044646120264298851, 0.035161161227814555,
      0.027786897135969331, 0.0092216833878826631, 0.010601542126616037,
      0.0038673404056338402, 0.045690020538978394, 0.03533576088484653,
      0.027889448337743813, 0.015671449496829564, 0.0083101781451075333,
      0.031124862963994762, 0.049396736747624771, 0.0085216011528441663,
      0.012889612528600653, 0.019839965931657183, 0.0036997384788468981,
      0.03420480334810045, 0.020119416634808096, 0.049141760069697553,
      0.020109199261124235, 0.031033597359978921, 0.0077184902739636189,
      0.0190672602222236, 0.0080566985924680427, 0.03790562156637093,
      0.043555556095769464, 0.017538837244294631, 0.034276785437376861,
      0.014707431688392482, 0.026531465192844279, 0.041621169314259195,
      0.029874509593628969, 0.016765566535262306, 0.014961251166655332,
      0.022629627078466205, 0.021132282661023124, 0.017980315898611782,
      0.027915959993464856, 0.037127268285096958, 0.021216739181284534,
      0.021467789428810252, 0.0062436379359906424, 0.0012217008025186993,
      0.01450926325653636, 0.015876029144961317, 0.032684506698323755,
      0.047846796203534207, 0.046786543639244026, 0.022894316692718342,
      0.012023919841604232, 0.038194897214323918, 0.037966369156554818,
      0.037032403248930715, 0.0371844170743663, 0.0052960208366382659,
      0.034078021523515786, 0.023163028929685959, 0.010608160262746719,
      0.0049259368844054192, 0.041178723696391931, 0.00875048686910398,
      0.00817849548924966, 0.033299360820555533, 0.044719468767712142,
      0.025827910417563521, 0.035135115347523768, 0.0076795188309700113,
      0.047672853494312384, 0.027044204062073824, 0.033986694910523349,
      0.0018281509024226429, 0.040460192564689669, 0.037430943588809856,
      0.0060093508993540323, 0.02625225823813044, 0.01629168143816246,
      0.027322471995153426, 0.01994403761915995, 0.020754669330652332,
      0.0090368880127397189, 0.012769337024402539, 0.0010267887329092286,
      0.046183780631020362, 0.032684994450412647, 0.046630678602428206,
      0.00817561842637628, 0.04605486279460988, 0.039732894269437657,
      0.028869709835332436, 0.022001779788012682, 0.012880686835621886,
      0.0375973196933725, 0.011433474105275072, 0.0032093543695949304,
      0.038366475538828722, 0.033560109267826779, 0.035760625739292007,
      0.032103041421692617, 0.020952414681244154, 0.019538104110208728,
      0.040807005143766138, 0.015871393182792484, 0.040726988645032568,
      0.039453675746947914, 0.042613194517192282, 0.025281830878587808,
      0.03178306944306885, 0.047544720768906763, 0.022198207750940519,
      0.0030009409889737992, 0.043337494849965935 } ;

    Copy_of_test_v_control_and_i_DW->FromWorkspace_PWORK.TimePtr = (void *)
      pTimeValues0;
    Copy_of_test_v_control_and_i_DW->FromWorkspace_PWORK.DataPtr = (void *)
      pDataValues0;
    Copy_of_test_v_control_and_i_DW->FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
      21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0,
      45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0,
      69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0,
      81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0,
      93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0,
      104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0,
      114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 121.0, 122.0, 123.0,
      124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0,
      134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
      144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0, 152.0, 153.0,
      154.0, 155.0, 156.0, 157.0, 158.0, 159.0, 160.0, 161.0, 162.0, 163.0,
      164.0, 165.0, 166.0, 167.0, 168.0, 169.0, 170.0, 171.0, 172.0, 173.0,
      174.0, 175.0, 176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
      184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0,
      194.0, 195.0, 196.0, 197.0, 198.0, 199.0, 200.0, 201.0, 202.0, 203.0,
      204.0, 205.0, 206.0, 207.0, 208.0, 209.0, 210.0, 211.0, 212.0, 213.0,
      214.0, 215.0, 216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
      224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0, 232.0, 233.0,
      234.0, 235.0, 236.0, 237.0, 238.0, 239.0, 240.0, 241.0, 242.0, 243.0,
      244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0, 253.0,
      254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
      264.0, 265.0, 266.0, 267.0, 268.0, 269.0, 270.0, 271.0, 272.0, 273.0,
      274.0, 275.0, 276.0, 277.0, 278.0, 279.0, 280.0, 281.0, 282.0, 283.0,
      284.0, 285.0, 286.0, 287.0, 288.0, 289.0, 290.0, 291.0, 292.0, 293.0,
      294.0, 295.0, 296.0, 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0,
      304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0, 313.0,
      314.0, 315.0, 316.0, 317.0, 318.0, 319.0, 320.0, 321.0, 322.0, 323.0,
      324.0, 325.0, 326.0, 327.0, 328.0, 329.0, 330.0, 331.0, 332.0, 333.0,
      334.0, 335.0, 336.0, 337.0, 338.0, 339.0, 340.0, 341.0, 342.0, 343.0,
      344.0, 345.0, 346.0, 347.0, 348.0, 349.0, 350.0, 351.0, 352.0, 353.0,
      354.0, 355.0, 356.0, 357.0, 358.0, 359.0, 360.0, 361.0, 362.0, 363.0,
      364.0, 365.0, 366.0, 367.0, 368.0, 369.0, 370.0, 371.0, 372.0, 373.0,
      374.0, 375.0, 376.0, 377.0, 378.0, 379.0, 380.0, 381.0, 382.0, 383.0,
      384.0, 385.0, 386.0, 387.0, 388.0, 389.0, 390.0, 391.0, 392.0, 393.0,
      394.0, 395.0, 396.0, 397.0, 398.0, 399.0, 400.0, 401.0, 402.0, 403.0,
      404.0, 405.0, 406.0, 407.0, 408.0, 409.0, 410.0, 411.0, 412.0, 413.0,
      414.0, 415.0, 416.0, 417.0, 418.0, 419.0, 420.0, 421.0, 422.0, 423.0,
      424.0, 425.0, 426.0, 427.0, 428.0, 429.0, 430.0, 431.0, 432.0, 433.0,
      434.0, 435.0, 436.0, 437.0, 438.0, 439.0, 440.0, 441.0, 442.0, 443.0,
      444.0, 445.0, 446.0, 447.0, 448.0, 449.0, 450.0, 451.0, 452.0, 453.0,
      454.0, 455.0, 456.0, 457.0, 458.0, 459.0, 460.0, 461.0, 462.0, 463.0,
      464.0, 465.0, 466.0, 467.0, 468.0, 469.0, 470.0, 471.0, 472.0, 473.0,
      474.0, 475.0, 476.0, 477.0, 478.0, 479.0, 480.0, 481.0, 482.0, 483.0,
      484.0, 485.0, 486.0, 487.0, 488.0, 489.0, 490.0, 491.0, 492.0, 493.0,
      494.0, 495.0, 496.0, 497.0, 498.0, 499.0, 500.0, 501.0, 502.0, 503.0,
      504.0, 505.0, 506.0, 507.0, 508.0, 509.0, 510.0, 511.0, 512.0, 513.0,
      514.0, 515.0, 516.0, 517.0, 518.0, 519.0, 520.0, 521.0, 522.0, 523.0,
      524.0, 525.0, 526.0, 527.0, 528.0, 529.0, 530.0, 531.0, 532.0, 533.0,
      534.0, 535.0, 536.0, 537.0, 538.0, 539.0, 540.0, 541.0, 542.0, 543.0,
      544.0, 545.0, 546.0, 547.0, 548.0, 549.0, 550.0, 551.0, 552.0, 553.0,
      554.0, 555.0, 556.0, 557.0, 558.0, 559.0, 560.0, 561.0, 562.0, 563.0,
      564.0, 565.0, 566.0, 567.0, 568.0, 569.0, 570.0, 571.0, 572.0, 573.0,
      574.0, 575.0, 576.0, 577.0, 578.0, 579.0, 580.0, 581.0, 582.0, 583.0,
      584.0, 585.0, 586.0, 587.0, 588.0, 589.0, 590.0, 591.0, 592.0, 593.0,
      594.0, 595.0, 596.0, 597.0, 598.0, 599.0, 600.0, 601.0, 602.0, 603.0,
      604.0, 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0,
      614.0, 615.0, 616.0, 617.0, 618.0, 619.0, 620.0, 621.0, 622.0, 623.0,
      624.0, 625.0, 626.0, 627.0, 628.0, 629.0, 630.0, 631.0, 632.0, 633.0,
      634.0, 635.0, 636.0, 637.0, 638.0, 639.0, 640.0, 641.0, 642.0, 643.0,
      644.0, 645.0, 646.0, 647.0, 648.0, 649.0, 650.0, 651.0, 652.0, 653.0,
      654.0, 655.0, 656.0, 657.0, 658.0, 659.0, 660.0, 661.0, 662.0, 663.0,
      664.0, 665.0, 666.0, 667.0, 668.0, 669.0, 670.0, 671.0, 672.0, 673.0,
      674.0, 675.0, 676.0, 677.0, 678.0, 679.0, 680.0, 681.0, 682.0, 683.0,
      684.0, 685.0, 686.0, 687.0, 688.0, 689.0, 690.0, 691.0, 692.0, 693.0,
      694.0, 695.0, 696.0, 697.0, 698.0, 699.0, 700.0, 701.0, 702.0, 703.0,
      704.0, 705.0, 706.0, 707.0, 708.0, 709.0, 710.0, 711.0, 712.0, 713.0,
      714.0, 715.0, 716.0, 717.0, 718.0, 719.0, 720.0, 721.0, 722.0, 723.0,
      724.0, 725.0, 726.0, 727.0, 728.0, 729.0, 730.0, 731.0, 732.0, 733.0,
      734.0, 735.0, 736.0, 737.0, 738.0, 739.0, 740.0, 741.0, 742.0, 743.0,
      744.0, 745.0, 746.0, 747.0, 748.0, 749.0, 750.0, 751.0, 752.0, 753.0,
      754.0, 755.0, 756.0, 757.0, 758.0, 759.0, 760.0, 761.0, 762.0, 763.0,
      764.0, 765.0, 766.0, 767.0, 768.0, 769.0, 770.0, 771.0, 772.0, 773.0,
      774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0, 782.0, 783.0,
      784.0, 785.0, 786.0, 787.0, 788.0, 789.0, 790.0, 791.0, 792.0, 793.0,
      794.0, 795.0, 796.0, 797.0, 798.0, 799.0, 800.0, 801.0, 802.0, 803.0,
      804.0, 805.0, 806.0, 807.0, 808.0, 809.0, 810.0, 811.0, 812.0, 813.0,
      814.0, 815.0, 816.0, 817.0, 818.0, 819.0, 820.0, 821.0, 822.0, 823.0,
      824.0, 825.0, 826.0, 827.0, 828.0, 829.0, 830.0, 831.0, 832.0, 833.0,
      834.0, 835.0, 836.0, 837.0, 838.0, 839.0, 840.0, 841.0, 842.0, 843.0,
      844.0, 845.0, 846.0, 847.0, 848.0, 849.0, 850.0, 851.0, 852.0, 853.0,
      854.0, 855.0, 856.0, 857.0, 858.0, 859.0, 860.0, 861.0, 862.0, 863.0,
      864.0, 865.0, 866.0, 867.0, 868.0, 869.0, 870.0, 871.0, 872.0, 873.0,
      874.0, 875.0, 876.0, 877.0, 878.0, 879.0, 880.0, 881.0, 882.0, 883.0,
      884.0, 885.0, 886.0, 887.0, 888.0, 889.0, 890.0, 891.0, 892.0, 893.0,
      894.0, 895.0, 896.0, 897.0, 898.0, 899.0, 900.0, 901.0, 902.0, 903.0,
      904.0, 905.0, 906.0, 907.0, 908.0, 909.0, 910.0, 911.0, 912.0, 913.0,
      914.0, 915.0, 916.0, 917.0, 918.0, 919.0, 920.0, 921.0, 922.0, 923.0,
      924.0, 925.0, 926.0, 927.0, 928.0, 929.0, 930.0, 931.0, 932.0, 933.0,
      934.0, 935.0, 936.0, 937.0, 938.0, 939.0, 940.0, 941.0, 942.0, 943.0,
      944.0, 945.0, 946.0, 947.0, 948.0, 949.0, 950.0, 951.0, 952.0, 953.0,
      954.0, 955.0, 956.0, 957.0, 958.0, 959.0, 960.0, 961.0, 962.0, 963.0,
      964.0, 965.0, 966.0, 967.0, 968.0, 969.0, 970.0, 971.0, 972.0, 973.0,
      974.0, 975.0, 976.0, 977.0, 978.0, 979.0, 980.0, 981.0, 982.0, 983.0,
      984.0, 985.0, 986.0, 987.0, 988.0, 989.0, 990.0, 991.0, 992.0, 993.0,
      994.0, 995.0, 996.0, 997.0, 998.0, 999.0 } ;

    static real_T pDataValues0[] = { 0.031559436713450566, 0.017753682593942451,
      0.049850163580332389, 0.011208574949156358, 0.032622553648430745,
      0.030249532095412968, 0.01936227157415675, 0.0071093579645252038,
      0.001256749285510156, 0.021055612688262067, 0.0092050144713755611,
      0.036288763373472657, 0.018518134325759907, 0.042078004373410305,
      0.036711484559665657, 0.028551293641218944, 0.0088427528812651379,
      0.047869201129786168, 0.013266101809646004, 0.046229044761980052,
      0.011188520234852051, 0.01867819038213225, 0.0043750174788292854,
      0.032005827412335756, 0.0090308443876554179, 0.0022525553736787106,
      0.036158673959154765, 0.017371882279089507, 0.033030841225145192,
      0.019193430053598571, 0.031367325122173349, 0.0010824907315153231,
      0.045528499426151427, 0.040027932813940556, 0.037292374217136062,
      0.040655640680538035, 0.019165315931276461, 0.030863961615822461,
      0.028774742985140697, 0.026502585238250782, 0.013753487791096752,
      0.012431447983098521, 0.022581938522598641, 0.011385641301327382,
      0.040222479180653505, 0.04930521209479851, 0.0014995975134694973,
      0.026783209533361885, 0.0043538609950446172, 0.0401045720277902,
      0.049457245485017, 0.0033473129198875076, 0.046969918094226744,
      0.000908876681834786, 0.034191930687317768, 0.039186824004160931,
      0.026706878394136414, 0.044267972546557094, 0.044950244945307007,
      0.0312968813040248, 0.0068934496206279122, 0.01089007968560623,
      0.0091070537945216867, 0.002090993198647717, 0.0053470829275103493,
      0.030822174254284258, 0.046983050508053341, 0.017722786548366443,
      0.0205314545029757, 0.04921747084922258, 0.047278959451763136,
      0.03383223392167696, 0.049415113115664315, 0.038341569360829719,
      0.016834963219573808, 0.033119093019974059, 0.012208264339513964,
      0.01477536254157984, 0.0340089185615251, 0.026392341520939895,
      0.020579675670376732, 0.03013191090181986, 0.037526002796186786,
      0.029176658713097933, 0.027589625746798376, 0.029178530937885722,
      0.025590995997923763, 0.0041296363499349681, 0.035978506742974488,
      0.049807805564843474, 0.017726715247846091, 0.048562940759170288,
      0.017322438065017983, 0.044327193088015318, 0.022734743249595391,
      0.020671364451040765, 0.010886603417865022, 0.0062827293681313127,
      0.015445729678340764, 0.036305221583241593, 0.039143603648956166,
      0.034689380749344863, 0.00049011261315310415, 0.04216066690052548,
      0.046116599889813786, 0.038547711033696225, 0.0021329927967524364,
      0.018909306852510945, 0.03521698122416838, 0.036475652275232348,
      0.011213853533225722, 0.013452736588668253, 0.033651558250205951,
      0.023874609886343063, 0.031185820633372125, 0.01182224663204552,
      0.0088561877249158268, 0.041482169284879231, 0.038346083396763243,
      0.046723913655913482, 0.0053944452542181781, 0.0091113752800527862,
      0.0049547641211229237, 0.024488190096172348, 0.0096622665234435256,
      0.044794578689628411, 0.0049544824840907281, 0.0022082785881330559,
      0.027864757790238094, 0.0386247533593812, 0.015597002874813443,
      0.0089491239657167546, 0.016947783912385911, 0.010507281852177603,
      0.025507625988262513, 0.04531821616326074, 0.0314461969326159,
      0.00507669444061561, 0.019542737636317732, 0.0027308307611828789,
      0.025064145660160766, 0.021586058594212362, 0.049878017475609458,
      0.040580129049766149, 0.024282583494900884, 0.044722387778369663,
      0.0068773297383532385, 0.019500245722264272, 0.046367811249906243,
      0.045874691620805846, 0.03567870057971579, 0.030916869181097,
      0.017164394512067273, 0.046801366334488489, 0.0062387020330246295,
      0.036529268075285358, 0.03232387162129069, 0.041657599283464755,
      0.019914111410938774, 0.037491110468031795, 0.041761025523906529,
      0.016123019868112969, 0.027613080842917748, 0.048956456621694608,
      0.027465426650915139, 0.01652118048033014, 0.030973577758888995,
      0.018031828550110134, 0.037825477175097218, 0.020695037434509483,
      0.024617255219246889, 0.034737161656630509, 0.048636694253989206,
      0.016387748024670339, 0.041890159153928783, 0.036953611363676406,
      0.047708722818977159, 0.00159613147519892, 0.017843449309127103,
      0.033132691714360722, 0.014075077957424532, 0.011519153365873187,
      0.035556427559016258, 0.031228645849665428, 0.029530432645981798,
      0.033021898315630092, 0.0023777336556933038, 0.017439240425502944,
      0.022567029017787163, 0.012045249856005536, 0.035752250664808825,
      0.0428091146003144, 0.014075384755927667, 0.036552541486187078,
      0.0068881446259758177, 0.041836139087485874, 0.0069300857871180017,
      0.029410469269474684, 0.01830784002274689, 0.040337977233055287,
      0.025189039288807797, 0.024479716936167711, 0.0438524361692522,
      0.017657090646947777, 0.022472177828587417, 0.04817651434217135,
      0.00211488989572714, 0.048647916707031738, 0.009460342156118802,
      0.033356015002003747, 0.029321980733945898, 0.033755620820255766,
      0.018051102459733043, 0.031013921353554276, 0.040557544255014261,
      0.00096287387070707062, 0.0041936754141449926, 0.04874008335924452,
      0.032567476620767664, 0.011561890808217613, 0.020174557156229497,
      0.0061010259126064786, 0.013421941069864158, 0.012892308505630235,
      0.016583261937131468, 0.0076117006431473235, 0.017400382985805676,
      0.0060829227153863076, 0.044207652887483011, 0.0047139195032073035,
      0.046502031305374454, 0.019950998451727778, 0.0023700731014575371,
      0.01711867515803699, 0.036798307944008207, 0.039734107866690266,
      0.027245294912233577, 0.034311173149202047, 0.044681634796680081,
      0.0027395894959866222, 0.015183068985850796, 0.0023095778165773905,
      0.00977383818168992, 0.036008290125826285, 0.03608766367496484,
      0.043889953557576362, 0.029121648224370519, 0.0035342167693324989,
      0.046137228509454613, 0.040018604617555353, 0.014297342821018161,
      0.027183161642068094, 0.049238811848530489, 0.035783903356331075,
      0.041948479866500014, 0.021663028050397416, 0.023531235780327037,
      0.028035670552227804, 0.013454577176549876, 0.037450923382097309,
      0.025194388673024433, 0.032340483313639028, 0.015387279101547037,
      0.0069362318039072283, 0.023778646689878148, 0.0181229640409373,
      0.039405671419927367, 0.039014791042205482, 0.033425610712677245,
      0.006675192983065615, 0.0010777943601748498, 0.027992035293625483,
      0.015040950903474454, 0.046970485693672917, 0.049045181802342956,
      0.014331019444712968, 0.040041014347576731, 0.044805567571630192,
      0.029876328840891482, 0.044200836786190995, 0.04718657705978957,
      0.027457904370995136, 0.036419341229717836, 0.028837914892900492,
      0.0012928735541569815, 0.022326548914240719, 0.032315097867532776,
      0.026060147633620911, 0.018615633038975603, 0.046856733317078118,
      0.041476641226325744, 0.042454273997722759, 0.018626711994976976,
      0.029659228760924517, 0.043627628232377931, 0.046675080425355266,
      0.033423213718068778, 0.010338822896755251, 0.032692529603129405,
      0.0036025775610324939, 0.020336345754468188, 0.033346576660374931,
      0.046686282977296489, 0.040547501611913256, 0.024227413591749521,
      0.037837460503275612, 0.020852372687138351, 0.048589299649464707,
      0.049398735061541604, 0.043207376451560142, 0.019444188795621428,
      0.022737091401955591, 0.012334359881903963, 0.039221154651208859,
      0.044141880279152626, 0.045685584064650911, 0.027914246181113753,
      0.02994340513731027, 0.0074438360168774531, 0.044985674226786926,
      0.02251967903260578, 0.010283616973198174, 0.044982549525454045,
      0.038129276968661349, 0.044124315370014905, 0.014247510901241062,
      0.033661299322612886, 0.033213995220902535, 0.0061407496949762944,
      0.020365921152840645, 0.013764347565784502, 0.035833487031957087,
      0.014169219081446817, 0.044809942842474776, 0.041328944615678015,
      0.019501325640699885, 0.02489514714820933, 0.0347402596336247,
      0.041718450054996886, 0.030481484483786622, 0.028736858042820404,
      0.016302108546139567, 0.022821230042587348, 0.035689779161656728,
      0.044220252263799747, 0.036042783540846578, 0.00093063873631930589,
      0.033738823356414288, 0.021925441211825644, 0.0218910089583135,
      0.0058518409752828906, 0.040734084475929112, 0.016242771931525454,
      0.012311405711732072, 0.017135661056163976, 0.018784607000479417,
      0.027327689654147946, 0.028096007713298839, 0.019791111431200048,
      0.019906543976566795, 0.025768360960578621, 0.03287652710479555,
      0.047545759913247963, 0.0361174257163749, 0.02000398726811688,
      0.0415935669664905, 0.0067169170864354094, 0.0030233385969914207,
      0.0042123526157329784, 0.0081949159164854124, 0.016210996014702449,
      0.015086338860232352, 0.00058404955651698007, 0.026995254692481263,
      0.0047686346313910782, 0.0073257428221115755, 0.031557060350747755,
      0.042966020571439272, 0.048711081561935668, 0.028541921373609176,
      0.04984251072874743, 0.027677078674776631, 0.025772922742016292,
      0.016534103299513353, 0.021500089919669819, 0.024590312680187239,
      0.0035518541956476358, 0.044386960776635807, 0.0032316795525434206,
      0.021809247786572419, 0.041331475330944591, 0.019726734211651678,
      0.0306737440852631, 0.04093203675411046, 0.044311751953130328,
      0.046555581374361034, 0.0095392324004561109, 0.012929112570938617,
      0.044893284242014962, 0.029668093019305449, 0.025192004092342398,
      0.03064047944177796, 0.040971112111593794, 0.026594458474646289,
      0.01010375482742158, 0.022694673284026096, 0.021395545991008541,
      0.048302637480599958, 0.031002752706673686, 0.03476949759590018,
      0.036008230600898972, 0.017344759514380682, 0.025849521026265511,
      0.027834731600605095, 0.0078247609557022257, 0.028102802278088743,
      0.034740164455422815, 0.021322776785511872, 0.041813521033815707,
      0.036569353308096651, 0.018001552104288582, 0.022710618592669929,
      0.019319494929608619, 0.038777732112526775, 0.03671355528429697,
      0.02151389225370778, 0.034687628706695672, 0.047260674358423016,
      0.039211629911587047, 0.035278592906553441, 0.0054667119762172867,
      0.019496532857824253, 0.029545236520266822, 0.022969002398316271,
      0.0025169993369477065, 0.011434379201011043, 0.041709453052844979,
      0.00078223463482635092, 0.043185543252793286, 0.003903452651621714,
      0.03345212950407777, 0.025010566214055119, 0.01089968993750768,
      0.028580786270204456, 0.0061094575461709882, 0.033558311649432647,
      0.029979277406140693, 0.0027988078693895247, 0.0028171509271678386,
      0.007625031850123515, 0.000981053338279203, 0.021758777284847593,
      0.041611073764140888, 0.030869508572704214, 0.0260064707655371,
      0.043193411146680537, 0.0048848959080721567, 0.045402610159338462,
      0.0054008347068379486, 0.025849837904847246, 0.0071578011041788072,
      0.027968528620150198, 0.00022898119736617373, 0.038334099931074374,
      0.04243546132291412, 0.045841063512686908, 0.04934841373918291,
      0.025256655089941127, 0.013571081220875754, 0.0050375255960617817,
      0.02539244154147683, 0.029280456285093921, 0.038144354795537044,
      0.0041481324555271929, 0.033079809654135713, 0.025848950735310655,
      0.00855240087627236, 0.046927893216592124, 0.029524158857128585,
      0.022031734038042008, 0.047095946515564147, 0.032795691012857064,
      0.022597285463019291, 0.041984871035983452, 0.026631175123717318,
      0.027694353289563753, 0.034003276504168033, 0.018359495265868369,
      0.011964530309677269, 0.028946174622954679, 0.043344352733625392,
      0.020338838010761279, 0.0056307570512523393, 0.022192291836347869,
      0.015009220060695001, 0.020069342690724641, 0.041668178172656722,
      0.020181433138680357, 0.019508796906530332, 0.01802244466894723,
      0.0070127679634722166, 0.013006509705622005, 0.0043407550432916836,
      0.021469866854290268, 0.012864139238492995, 0.014877769207555919,
      0.021242920585231292, 0.0059603629710643542, 0.024753346190022958,
      0.035320361376878023, 0.01217866863404754, 0.039253504096700309,
      0.0037044788430463439, 0.019694171349084834, 0.00016970614821537058,
      0.0110338445966512, 6.5028435029806938E-5, 0.00945898354973676,
      0.0071242027410485746, 0.0134037999561688, 0.0087446032667891412,
      0.0069324485796297634, 0.029944280518393252, 0.04505289528413628,
      0.046968988294211915, 0.011059222796953894, 0.024133568769820691,
      0.018800555796237729, 0.026189001848293477, 0.013243629677429493,
      0.0034178610235414577, 0.021816353874005136, 0.0086926518682500509,
      0.0013053554077452458, 0.047733913704022475, 0.021529825992970864,
      0.048077928655183164, 0.038120724200149649, 0.0003674330551423466,
      0.034001932023006935, 0.03529753771244417, 0.032256439330369126,
      0.027615492225386496, 0.010905436489164, 0.038618310680652135,
      0.011401416180022512, 0.018543235948670262, 0.044546441051284746,
      0.042818845386413035, 0.020121677490672209, 0.015900955874836753,
      0.030431771531749481, 0.045509761334724091, 0.045454909390044117,
      0.029579720445371896, 0.016628570366777558, 0.042653181460495959,
      0.022119894652058256, 0.045217773910897187, 0.0016589702976063715,
      0.026621324125006632, 0.035824867325219091, 0.00896509219108947,
      0.016826646290053128, 0.0093856474287633673, 0.01609635915914619,
      0.020192835561510337, 0.027428314992848181, 0.0024369296391133334,
      0.027636606658947127, 0.013740570241875034, 0.012075087086705611,
      0.012157258970327529, 0.0077079724585037207, 0.047820818050401205,
      0.046783068775830008, 0.040935721860412194, 0.0364130923911417,
      0.0087905864137764866, 0.01801854885212268, 0.009439498632080252,
      5.9919842002170712E-5, 0.015820975686627155, 0.034980849319852778,
      0.031262759008952028, 0.027153108767192582, 0.021951860169383459,
      0.014371363374127134, 0.025082955337334512, 0.038077309283482345,
      0.038120402439435708, 0.028802795074827855, 0.037383141882085823,
      0.032276725299066077, 0.0061609759162253091, 0.025219893004638335,
      0.017363065636081681, 0.0046073842402552193, 0.0073924734016259375,
      0.0099084850533200878, 0.033613511872871434, 0.021575559145094542,
      0.034720195484227716, 0.012839228163507395, 0.00048793249425797548,
      0.026614153553044435, 0.013969598262648231, 0.047311507675996338,
      0.045322163325500112, 0.019634228798705577, 0.0012427616922436047,
      0.033571839828622989, 0.041858531768852729, 0.04857498191556317,
      0.0028466442717623996, 0.022516190636672651, 0.029123515086814357,
      0.034331890724815163, 0.035971637629799907, 0.032502037596269538,
      0.0363457275456326, 0.018692383291999081, 0.029079104160643288,
      0.0058059256389700166, 0.0028827180607436109, 0.048988261198799329,
      0.014241186343030888, 0.029748714940479815, 0.048108051550563,
      0.0092889131704289151, 0.00965199079885133, 0.017082205232257088,
      0.046644894790904029, 0.019533376830879814, 0.013660835399998173,
      0.0075973539923422095, 0.019855442137172587, 0.018736123347562129,
      0.0065557353521502664, 0.021752035894781342, 0.0045756583606305417,
      0.030731347900647295, 0.00054895461454058665, 0.028663019163168619,
      0.039486492901288091, 0.011768338657543471, 0.022400985673202548,
      0.028467909164246602, 0.0030700721145423496, 0.024814444281994242,
      0.032115761729264926, 0.011063286506355231, 0.041852822276594037,
      0.048553761572125681, 0.042318644384658675, 0.025299972794527417,
      0.013943780557261531, 0.037330861091410067, 0.011846519205643509,
      0.047867264080956165, 0.031013001803888541, 0.030013107275381392,
      0.00863022508238343, 0.0045173369071612292, 0.01276311013217944,
      0.0429285265629605, 0.045553352669889705, 0.034981688361288128,
      0.036259117751169377, 0.011494303942874824, 0.028802672816067722,
      0.04053140525039696, 0.020192168419203283, 0.049421963359987255,
      0.0044999407493444164, 0.016047051632388072, 0.025570446940958898,
      0.0030303183284121128, 0.0362843961772922, 0.0278277874280996,
      0.026467995124062834, 0.041499121601659771, 0.0429379517035902,
      0.039451446165697457, 0.015891652686311427, 0.02261037268814909,
      0.037611398502497118, 0.0054930852875342889, 0.0054871184296951814,
      0.013494183185220044, 0.026231867269815547, 0.048632553848874854,
      0.035520434263908475, 0.015592997257376645, 0.014572856382386368,
      0.042517866868731075, 0.045582371200392671, 0.031963807363803186,
      0.012768514897222173, 0.0044332920016141534, 0.041912779376861289,
      0.029235930963166019, 0.047405436769801107, 0.003051446459625462,
      0.02923206516775553, 0.014255404282932094, 0.041386608672413165,
      0.00954932203486989, 0.022126498110144183, 0.019670575318378819,
      0.041328698952138254, 0.033843554671920947, 0.010380151718999026,
      0.01590523630751316, 0.0066905492678063011, 0.033573144473901535,
      0.028549553773120285, 0.008488353301324426, 0.0073827888575868422,
      0.023803985913372818, 0.0454051208253475, 0.027608751335791739,
      0.0016469946374938317, 0.0026931463217778062, 0.040253161427945106,
      0.022568742735172412, 0.019132311477997929, 0.039482185184484542,
      0.018214343474989698, 0.02661749674994552, 0.03558283529906333,
      0.043573825899792334, 0.016434480583611449, 0.032505901269888858,
      0.048741807400137879, 0.003798368064706781, 0.02935095835413859,
      0.020694324888668004, 0.015456821323313353, 0.013191702076339762,
      0.0379383132540102, 0.0497607990564876, 0.0093285722070684581,
      0.03905726342673823, 0.0097898990513366, 0.049617948658996325,
      0.040113078488214438, 0.021211335495165309, 0.0364431934025687,
      0.024917679126177584, 0.040449513359952241, 0.017825446674052305,
      0.003662171724490371, 0.029549572763742468, 0.045509391536407068,
      0.0096882968083305161, 0.021618389576719882, 0.037457986453400462,
      0.0019592243323791505, 0.047316249490274132, 0.03818366618318806,
      0.027941027525478015, 0.0091921472232887325, 0.024897440750947349,
      0.025892280011702535, 0.049712150532202515, 0.042742584154533754,
      0.048120196985598544, 0.033947050448851664, 0.020175069440218036,
      0.046748954308902586, 0.023974227281624079, 0.011589580583155845,
      0.019814512425488776, 0.035253873755639445, 0.027927951728027506,
      0.037831535044718381, 0.049774052927762893, 0.0481215702183317,
      0.026753355262807851, 0.048193506498585725, 0.0057812939590629608,
      0.002572414661510264, 0.015217447281828674, 0.029009591657135621,
      0.026548222616914075, 0.045060404632657175, 0.027027521258512217,
      0.021599030542834137, 0.027133349371817078, 0.035620740289476087,
      0.00083373564701162424, 0.040046044102892413, 0.0071254662461895275,
      0.023923723645143159, 0.012841767708981678, 0.018454584441243028,
      0.033088245668270719, 0.0084804406727157222, 0.013939201021950938,
      0.0099110897256919472, 0.0097535766642130439, 0.016341982417498787,
      0.044016893018959981, 0.023555093250787425, 0.020198468608547057,
      0.0089615738211723372, 0.048446249807364596, 0.020372786890131014,
      0.042224369824172409, 0.030766254856542476, 0.018830553901636862,
      0.043859087466854858, 0.039242621364151187, 0.023247714165726713,
      0.0406988463410467, 0.044922206859006025, 0.02146192715574137,
      0.016716470981110988, 0.029832355222262314, 0.045099540435328107,
      0.03510332246798379, 0.018872755103543245, 0.036747796271500724,
      0.047705139323560686, 0.027140655655177561, 0.027005291617968292,
      0.015555481980200098, 0.0035617285962291859, 0.0090990233584510756,
      0.0046494463435338973, 0.02317446238811216, 0.00046662560138847068,
      0.045751295586789496, 0.0321370869566552, 7.0952910120147819E-5,
      0.0015192636247458868, 0.010423511165265987, 0.022748307250104863,
      0.0063633016662566714, 0.00043238439390451693, 0.036353980057426363,
      0.017705823302829323, 0.039022297304801237, 0.02183283208176456,
      0.02182773911861341, 0.0024606590178243184, 0.0024815950759695116,
      0.0045550087706526963, 0.029701851572206062, 0.012054202758451106,
      0.042068455098607183, 0.042860638204530281, 0.04818061004756774,
      0.0244449893080302, 0.011015505028431649, 0.011310432042064295,
      0.026839390225641292, 0.038105485460557371, 0.017378357522437965,
      0.02306158796957496, 0.031966188109967819, 0.045866802043342259,
      0.0080786286945165441, 0.035781770208373677, 0.028886943809620466,
      0.021664948860455946, 0.044212139131554695, 0.019652587768845643,
      0.0089487576313866061, 0.031666679016006082, 0.031200027715617203,
      0.016397079848662437, 0.04014826579791185, 0.049973892931794606,
      0.049048908046607317, 0.0063518471097428536, 0.011612007298089633,
      0.0011816233329112525, 0.030371630520092757, 0.0055404660643575028,
      0.020372975393919947, 0.044203840333098085, 0.027406638873829377,
      0.018450153835580862, 0.010417299140667342, 0.022047163826216177,
      0.047809807608793893, 0.00620129583240216, 0.023538162293347844,
      0.042844816389109669, 0.0021695235783476597, 0.034581257260065279,
      0.04894927333375193, 0.014163394924606844, 0.0066890249997211548,
      0.034263984220634362, 0.04547272778746974, 0.030543449119162167,
      0.044999139821643046, 0.0096716875969545986, 0.037721229074412506,
      0.01731303583323875, 0.020931270715135647, 0.0077859915177446119,
      0.040950029196342053, 0.031246176392313862, 0.036928021080532385,
      0.0402556210353477, 0.003361132878158929, 0.047539515825278308,
      0.024878850551108035, 0.037757295235026106, 0.03712025353384709,
      0.041556478785505661, 0.0078250923375100759, 0.022865436027570431,
      0.030905024804719045, 0.046609167752352527, 0.041754411777967571,
      0.044771175817117509, 0.029125926233401506, 0.029137340318089573,
      0.042746296948497749, 0.0017432850023965385, 0.044271004774240168,
      0.020386540567799091, 0.0018191015223916031, 0.037307397136886015,
      0.0077414385375552848, 0.0071954164337433959, 0.030297952666187358,
      0.012724042202568425, 0.016207710250291104, 0.02008954589234993,
      0.020318666070056359, 0.019309556928045618, 0.030490091191897741,
      0.0083445361333122914, 0.0094046036597624175, 0.0047314434931082731,
      0.016159313638063222, 0.038479846463616754, 0.011705900122949926,
      0.037018273481213115, 0.034640920691586467, 0.041203910668319021,
      0.041398877456974348, 0.014668396700419601, 0.01546846212113745,
      0.026151489922099654, 0.016264949624721303, 0.041592125524303407,
      0.040514739537192035, 0.027849913063930448, 0.013148201686507861,
      0.034028310115222511, 0.011682657272119246, 0.022821268230655598,
      0.019228344725576198, 0.02693007193490109, 0.049585186048097744,
      0.037761020083891511, 0.049022742471518721, 0.011739132033142386,
      0.026427954427633255, 0.0025718026783453918, 0.037843773549231116,
      0.030098988313775513, 0.042858435456110441, 0.049413856962905713,
      0.046474223621280876, 0.020475746671940766, 1.707311090694552E-5,
      0.027043916138152164, 0.010386531099802971, 0.010964179409121517,
      0.016290313136711095, 0.0047974708303792253, 0.037376683086915156,
      0.0374254478696646, 0.027164971654255445, 0.016906615826202658,
      0.041616683081026416, 0.027628608901297876, 0.047877155848101038,
      0.044641665965900079, 0.017825180856350219, 0.027320094649594364,
      0.017334087562747454, 0.03114013953295652, 0.039831234265419811,
      0.0372937450770325, 0.0062768115677409864, 0.041119700337951023,
      0.0012575250714251087, 0.020721444046201583, 0.036570373398646862,
      0.039068700013798141, 0.018364295756568449 } ;

    Copy_of_test_v_control_and_i_DW->FromWorkspace1_PWORK.TimePtr = (void *)
      pTimeValues0;
    Copy_of_test_v_control_and_i_DW->FromWorkspace1_PWORK.DataPtr = (void *)
      pDataValues0;
    Copy_of_test_v_control_and_i_DW->FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
      21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0,
      45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0,
      69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0,
      81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0,
      93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0,
      104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0,
      114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 121.0, 122.0, 123.0,
      124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0,
      134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
      144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0, 152.0, 153.0,
      154.0, 155.0, 156.0, 157.0, 158.0, 159.0, 160.0, 161.0, 162.0, 163.0,
      164.0, 165.0, 166.0, 167.0, 168.0, 169.0, 170.0, 171.0, 172.0, 173.0,
      174.0, 175.0, 176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
      184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0,
      194.0, 195.0, 196.0, 197.0, 198.0, 199.0, 200.0, 201.0, 202.0, 203.0,
      204.0, 205.0, 206.0, 207.0, 208.0, 209.0, 210.0, 211.0, 212.0, 213.0,
      214.0, 215.0, 216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
      224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0, 232.0, 233.0,
      234.0, 235.0, 236.0, 237.0, 238.0, 239.0, 240.0, 241.0, 242.0, 243.0,
      244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0, 253.0,
      254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
      264.0, 265.0, 266.0, 267.0, 268.0, 269.0, 270.0, 271.0, 272.0, 273.0,
      274.0, 275.0, 276.0, 277.0, 278.0, 279.0, 280.0, 281.0, 282.0, 283.0,
      284.0, 285.0, 286.0, 287.0, 288.0, 289.0, 290.0, 291.0, 292.0, 293.0,
      294.0, 295.0, 296.0, 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0,
      304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0, 313.0,
      314.0, 315.0, 316.0, 317.0, 318.0, 319.0, 320.0, 321.0, 322.0, 323.0,
      324.0, 325.0, 326.0, 327.0, 328.0, 329.0, 330.0, 331.0, 332.0, 333.0,
      334.0, 335.0, 336.0, 337.0, 338.0, 339.0, 340.0, 341.0, 342.0, 343.0,
      344.0, 345.0, 346.0, 347.0, 348.0, 349.0, 350.0, 351.0, 352.0, 353.0,
      354.0, 355.0, 356.0, 357.0, 358.0, 359.0, 360.0, 361.0, 362.0, 363.0,
      364.0, 365.0, 366.0, 367.0, 368.0, 369.0, 370.0, 371.0, 372.0, 373.0,
      374.0, 375.0, 376.0, 377.0, 378.0, 379.0, 380.0, 381.0, 382.0, 383.0,
      384.0, 385.0, 386.0, 387.0, 388.0, 389.0, 390.0, 391.0, 392.0, 393.0,
      394.0, 395.0, 396.0, 397.0, 398.0, 399.0, 400.0, 401.0, 402.0, 403.0,
      404.0, 405.0, 406.0, 407.0, 408.0, 409.0, 410.0, 411.0, 412.0, 413.0,
      414.0, 415.0, 416.0, 417.0, 418.0, 419.0, 420.0, 421.0, 422.0, 423.0,
      424.0, 425.0, 426.0, 427.0, 428.0, 429.0, 430.0, 431.0, 432.0, 433.0,
      434.0, 435.0, 436.0, 437.0, 438.0, 439.0, 440.0, 441.0, 442.0, 443.0,
      444.0, 445.0, 446.0, 447.0, 448.0, 449.0, 450.0, 451.0, 452.0, 453.0,
      454.0, 455.0, 456.0, 457.0, 458.0, 459.0, 460.0, 461.0, 462.0, 463.0,
      464.0, 465.0, 466.0, 467.0, 468.0, 469.0, 470.0, 471.0, 472.0, 473.0,
      474.0, 475.0, 476.0, 477.0, 478.0, 479.0, 480.0, 481.0, 482.0, 483.0,
      484.0, 485.0, 486.0, 487.0, 488.0, 489.0, 490.0, 491.0, 492.0, 493.0,
      494.0, 495.0, 496.0, 497.0, 498.0, 499.0, 500.0, 501.0, 502.0, 503.0,
      504.0, 505.0, 506.0, 507.0, 508.0, 509.0, 510.0, 511.0, 512.0, 513.0,
      514.0, 515.0, 516.0, 517.0, 518.0, 519.0, 520.0, 521.0, 522.0, 523.0,
      524.0, 525.0, 526.0, 527.0, 528.0, 529.0, 530.0, 531.0, 532.0, 533.0,
      534.0, 535.0, 536.0, 537.0, 538.0, 539.0, 540.0, 541.0, 542.0, 543.0,
      544.0, 545.0, 546.0, 547.0, 548.0, 549.0, 550.0, 551.0, 552.0, 553.0,
      554.0, 555.0, 556.0, 557.0, 558.0, 559.0, 560.0, 561.0, 562.0, 563.0,
      564.0, 565.0, 566.0, 567.0, 568.0, 569.0, 570.0, 571.0, 572.0, 573.0,
      574.0, 575.0, 576.0, 577.0, 578.0, 579.0, 580.0, 581.0, 582.0, 583.0,
      584.0, 585.0, 586.0, 587.0, 588.0, 589.0, 590.0, 591.0, 592.0, 593.0,
      594.0, 595.0, 596.0, 597.0, 598.0, 599.0, 600.0, 601.0, 602.0, 603.0,
      604.0, 605.0, 606.0, 607.0, 608.0, 609.0, 610.0, 611.0, 612.0, 613.0,
      614.0, 615.0, 616.0, 617.0, 618.0, 619.0, 620.0, 621.0, 622.0, 623.0,
      624.0, 625.0, 626.0, 627.0, 628.0, 629.0, 630.0, 631.0, 632.0, 633.0,
      634.0, 635.0, 636.0, 637.0, 638.0, 639.0, 640.0, 641.0, 642.0, 643.0,
      644.0, 645.0, 646.0, 647.0, 648.0, 649.0, 650.0, 651.0, 652.0, 653.0,
      654.0, 655.0, 656.0, 657.0, 658.0, 659.0, 660.0, 661.0, 662.0, 663.0,
      664.0, 665.0, 666.0, 667.0, 668.0, 669.0, 670.0, 671.0, 672.0, 673.0,
      674.0, 675.0, 676.0, 677.0, 678.0, 679.0, 680.0, 681.0, 682.0, 683.0,
      684.0, 685.0, 686.0, 687.0, 688.0, 689.0, 690.0, 691.0, 692.0, 693.0,
      694.0, 695.0, 696.0, 697.0, 698.0, 699.0, 700.0, 701.0, 702.0, 703.0,
      704.0, 705.0, 706.0, 707.0, 708.0, 709.0, 710.0, 711.0, 712.0, 713.0,
      714.0, 715.0, 716.0, 717.0, 718.0, 719.0, 720.0, 721.0, 722.0, 723.0,
      724.0, 725.0, 726.0, 727.0, 728.0, 729.0, 730.0, 731.0, 732.0, 733.0,
      734.0, 735.0, 736.0, 737.0, 738.0, 739.0, 740.0, 741.0, 742.0, 743.0,
      744.0, 745.0, 746.0, 747.0, 748.0, 749.0, 750.0, 751.0, 752.0, 753.0,
      754.0, 755.0, 756.0, 757.0, 758.0, 759.0, 760.0, 761.0, 762.0, 763.0,
      764.0, 765.0, 766.0, 767.0, 768.0, 769.0, 770.0, 771.0, 772.0, 773.0,
      774.0, 775.0, 776.0, 777.0, 778.0, 779.0, 780.0, 781.0, 782.0, 783.0,
      784.0, 785.0, 786.0, 787.0, 788.0, 789.0, 790.0, 791.0, 792.0, 793.0,
      794.0, 795.0, 796.0, 797.0, 798.0, 799.0, 800.0, 801.0, 802.0, 803.0,
      804.0, 805.0, 806.0, 807.0, 808.0, 809.0, 810.0, 811.0, 812.0, 813.0,
      814.0, 815.0, 816.0, 817.0, 818.0, 819.0, 820.0, 821.0, 822.0, 823.0,
      824.0, 825.0, 826.0, 827.0, 828.0, 829.0, 830.0, 831.0, 832.0, 833.0,
      834.0, 835.0, 836.0, 837.0, 838.0, 839.0, 840.0, 841.0, 842.0, 843.0,
      844.0, 845.0, 846.0, 847.0, 848.0, 849.0, 850.0, 851.0, 852.0, 853.0,
      854.0, 855.0, 856.0, 857.0, 858.0, 859.0, 860.0, 861.0, 862.0, 863.0,
      864.0, 865.0, 866.0, 867.0, 868.0, 869.0, 870.0, 871.0, 872.0, 873.0,
      874.0, 875.0, 876.0, 877.0, 878.0, 879.0, 880.0, 881.0, 882.0, 883.0,
      884.0, 885.0, 886.0, 887.0, 888.0, 889.0, 890.0, 891.0, 892.0, 893.0,
      894.0, 895.0, 896.0, 897.0, 898.0, 899.0, 900.0, 901.0, 902.0, 903.0,
      904.0, 905.0, 906.0, 907.0, 908.0, 909.0, 910.0, 911.0, 912.0, 913.0,
      914.0, 915.0, 916.0, 917.0, 918.0, 919.0, 920.0, 921.0, 922.0, 923.0,
      924.0, 925.0, 926.0, 927.0, 928.0, 929.0, 930.0, 931.0, 932.0, 933.0,
      934.0, 935.0, 936.0, 937.0, 938.0, 939.0, 940.0, 941.0, 942.0, 943.0,
      944.0, 945.0, 946.0, 947.0, 948.0, 949.0, 950.0, 951.0, 952.0, 953.0,
      954.0, 955.0, 956.0, 957.0, 958.0, 959.0, 960.0, 961.0, 962.0, 963.0,
      964.0, 965.0, 966.0, 967.0, 968.0, 969.0, 970.0, 971.0, 972.0, 973.0,
      974.0, 975.0, 976.0, 977.0, 978.0, 979.0, 980.0, 981.0, 982.0, 983.0,
      984.0, 985.0, 986.0, 987.0, 988.0, 989.0, 990.0, 991.0, 992.0, 993.0,
      994.0, 995.0, 996.0, 997.0, 998.0, 999.0 } ;

    static real_T pDataValues0[] = { 0.037243392812083637, 0.044613359411555371,
      0.012130169313983486, 0.0064798487918770135, 0.011253394106395665,
      0.017500695950038309, 0.014354230657308804, 0.0463744003589714,
      0.0025656878408397755, 0.029633337760319331, 0.0081449450108866169,
      0.041920288483651515, 0.0083780465105635412, 0.025110030770473635,
      0.049966473951285971, 0.017770357563394065, 0.0023538854774416973,
      0.010683029256039957, 0.019891956205135265, 0.016683409019014741,
      0.011480126598409879, 0.046806008875103416, 0.034159439234999138,
      0.048105689786143171, 0.021898658881639905, 0.047016832721045357,
      0.00029171622861854377, 0.030515351503493767, 0.040053787848305981,
      0.011649076670682407, 0.046623433796048934, 0.038163138766687095,
      0.041322476985134082, 0.028673179430243306, 0.0396290832060113,
      0.016452059791962376, 0.011173098806292626, 0.015619317100962676,
      0.029226173926427779, 0.041495707051076143, 0.014523124577363405,
      0.020127719603156125, 0.043102864921657311, 0.030736977510819982,
      0.049559389416489644, 0.010184943759281107, 0.041360454247332749,
      0.033793080947638714, 0.012447473501990403, 0.02378928132847663,
      0.019953761336339595, 0.029971912454570607, 0.040026138290192553,
      0.005253438564558538, 0.041072109706319596, 0.042054316502271129,
      0.017725312220021956, 0.021503473130791675, 0.028611960920634234,
      0.035041236538561837, 0.037123487849364006, 0.037894207531039274,
      0.019456438178461346, 0.021465124249991877, 0.047817232875032936,
      0.028648568363524213, 0.042486102710933685, 0.013817265814911174,
      0.031116180757622521, 0.029418084230676947, 0.048173423290349578,
      0.0042951347483625507, 0.025024944580197529, 0.026079483824902744,
      0.0045083001084481765, 0.04523332398450626, 0.044219446925493025,
      0.021949483340279515, 0.039086130645858315, 0.0074232511471704239,
      0.030990796363043551, 0.013031183969721034, 0.022282810571978763,
      0.042199975573746808, 0.0098102459365626, 0.015192581138882623,
      0.024164728386714282, 0.016890602193551187, 0.039924291476077456,
      0.049374378759467652, 0.007952377736119726, 0.011843989161302738,
      0.03511183163339452, 0.01877358313487737, 0.0486852451337492,
      0.048615277784422851, 0.03218490247107024, 0.043004943842708032,
      0.020094169900404281, 0.031596539898872858, 0.049261831970741521,
      0.027973870299363775, 0.046679595792110451, 0.036017160300037404,
      0.024201925840617089, 0.031951554634061512, 0.044381843294480208,
      0.0099368375049460611, 0.019768313697760512, 0.049608765124765267,
      0.020117580846797406, 0.032942824053646562, 0.045067406151725581,
      0.049769088825894314, 0.032658164054734519, 0.0054218213927757393,
      0.0018057015397678013, 0.030904561952348687, 0.028357218094899779,
      0.0480982328902663, 0.037305273470944388, 0.033125804921754091,
      0.026165665920600479, 0.012994714074219871, 0.04809968834580864,
      0.027010201875676005, 0.0015135081709884369, 0.034815723170556361,
      0.025985807896043905, 0.0029515277832242062, 0.044501811661410658,
      0.016510112125701026, 0.011485059893555978, 0.005697432099759459,
      0.015546135672680289, 0.01142161610678687, 0.032599858360850158,
      0.0033080062299163382, 0.013771568993045847, 0.014091011878043342,
      0.044003312986302813, 0.022216517934961735, 0.037795706045398059,
      0.030164818790767423, 0.039163296870201814, 0.0056965319339212957,
      0.0489281942579989, 0.042429833773977452, 0.0025323248835271706,
      0.023310091689531798, 0.016282663747401678, 0.031510256249987482,
      0.01151495818888369, 0.02899424866406445, 0.030157816021994827,
      0.029993954791642852, 0.022421394019195764, 0.0017711730341394229,
      0.025690741751913826, 0.020386508088631849, 0.0054023018307779447,
      0.022993781447115696, 0.022544137683791522, 0.027557016790220941,
      0.040270215850399887, 0.03504250363930303, 0.043611775196079894,
      0.0026096076214450481, 0.010984065570267305, 0.022982100505568329,
      0.047926679806450483, 0.039502267848971914, 0.022593730452125045,
      0.016671409323043323, 0.002954765634004031, 0.03704526514467938,
      0.025339726202775126, 0.0099962706569677318, 0.021359677555064405,
      0.0084345139356135582, 0.037584729542734369, 0.018417542081440027,
      0.047090889761994215, 0.00085862704553586473, 0.041452795438940038,
      0.0313295487477638, 0.02693732575786096, 0.032525381769003027,
      0.036331476615325708, 0.0047244281960289241, 0.043878696715383,
      0.00071810719729928927, 0.01471513134231186, 0.0089957439252120082,
      0.046314713409897505, 0.0034090218413517282, 0.029054661378924575,
      0.031857561126261237, 0.032563463238247117, 0.043231100626677649,
      0.0027976264703510447, 0.040842758688692513, 0.026446123316421429,
      0.034717528031122082, 0.010620244814091701, 0.027163997312492555,
      0.035126013607673194, 0.047821727863023446, 0.022227108143673568,
      0.0042698915406322478, 0.0028670073770628748, 0.031472524304973964,
      0.039808953324922909, 0.034559566642907179, 0.017265393110758278,
      0.047340833358079731, 0.026009515910573863, 0.047690651259896348,
      0.0036797817904099975, 0.010351597403653701, 0.038751390699098373,
      0.04570939106218868, 0.039127532385514981, 0.014776709808243799,
      0.007592286115724229, 0.042395526115689114, 0.039242729554657484,
      0.013541575107565868, 0.011390535240806687, 0.016051160854447556,
      0.04147809021995838, 0.0411091097300488, 0.028534142524093916,
      0.028591481811442377, 0.014300913624969014, 0.034956677965060454,
      0.039812897164078855, 0.022079452807561142, 0.022310780584561082,
      0.023283120418255532, 0.013951959363730743, 0.033768765920829738,
      0.045183226318177, 0.045426294942418732, 0.037359847206535651,
      0.013025575354177305, 0.034481892003705453, 0.0065915332737756186,
      0.006175041615990029, 0.00954514266222456, 0.0072866049748145706,
      0.029252180763435776, 0.003668084504023339, 0.041116311109265308,
      0.036145148663423263, 0.046292901900874289, 0.02463192992308906,
      0.032744144922483426, 0.044506173898084346, 0.026926278723451061,
      0.014110258227911116, 0.048797875893998206, 0.0018212757762740063,
      0.016312228653015622, 0.048650681194641027, 0.018251631265287373,
      0.015457480944795866, 0.0060456192290314131, 0.04578828520203948,
      0.006773910284075097, 0.016605894591417036, 0.044873994619994216,
      0.024982438892363668, 0.030764412110752839, 0.029156648404432411,
      0.034912696331370695, 0.0014666171377181016, 0.026394134386932368,
      0.0016036423209992712, 0.041357116141815732, 0.016999310324108431,
      0.042335547944026511, 0.012303478355304921, 0.02907456261840663,
      0.04688384395373877, 0.0023893646192533094, 0.0026988829585119279,
      0.001030901705999543, 0.034073925709810625, 0.029931426331661733,
      0.0057015017257827927, 0.039812267536292266, 0.030892529356963939,
      0.0035106761993479174, 0.0034639486284000656, 0.0068003694310044827,
      0.039444565982850441, 0.0046199228961914807, 0.011893439600365319,
      0.012182395630839239, 0.00524111063294474, 0.042917638011437893,
      0.034909988308978311, 0.036687106663164062, 0.032526531222745632,
      0.02581352828870645, 0.0163194067544441, 0.033088809838925065,
      0.0058782742310878157, 0.0073908707090803161, 0.000988233186440851,
      0.048214586514977974, 0.048518645100665614, 0.0061930253573409871,
      0.023370501338722982, 0.032834700165223683, 0.014509278331643356,
      0.037726831985814745, 0.027905902567948577, 0.021389629777422803,
      0.013359702863710006, 0.037686803706653067, 0.044918816250281553,
      0.0364222016978893, 0.020341506732724418, 0.046915792012684865,
      0.012771372746890126, 0.026658162030441131, 0.047737743518818515,
      0.013387376822004811, 0.012504231029479474, 0.046383636011967377,
      0.0034291174277727822, 0.014970019328043245, 0.029579176707818358,
      0.010164957267816816, 0.031794159944344369, 0.039918512891512929,
      0.025085052618210913, 0.032540606797457093, 0.039797749277806348,
      0.011668688403578365, 0.030041946921739622, 0.0056231189191643218,
      0.025788282659795721, 0.041892034543511716, 0.046039505399935232,
      0.024911396472767796, 0.013880556113219417, 0.032625998037414707,
      0.045864940190033378, 0.025491972675736774, 0.048709574190129896,
      0.0098639471048656956, 0.00555924918944668, 0.0148677146684311,
      0.019820926778086334, 0.021037784167424606, 0.015573767882522627,
      0.034692158546611306, 0.0045935916635749755, 0.020104430951852322,
      0.014759040201498109, 0.01532483895131896, 0.0052780565367637425,
      0.02969138022821341, 0.014136375812237917, 0.0077610810469750163,
      3.2933379305616353E-5, 0.014179770853919072, 0.02754054374897999,
      0.0435451095751842, 0.0021126712666246386, 0.045236099073316348,
      0.00654870431825832, 0.041686447406153286, 0.040023418744953125,
      0.045894004599931967, 0.0068651829222938559, 0.025236615877872431,
      0.020247924005864865, 0.0086786080767358616, 0.028759180623392673,
      0.030310896628639162, 0.01072228702079891, 0.025996612752821908,
      0.049459290481969329, 0.024495758120669727, 0.034743660559354128,
      0.020571091369388245, 0.0017388370049873315, 0.014641577798426742,
      0.040072086888876736, 0.017325099528153871, 0.0041657972411936082,
      0.025555318547142991, 0.018341670392614334, 0.036973975244374339,
      0.026237008197099745, 0.040226043872936559, 0.040845558952476574,
      0.0094735740842719473, 0.0061846728432181589, 0.041049823949551083,
      0.0318948810005718, 0.000805990094110759, 0.044797731381986672,
      0.025768752855998944, 0.027226096917312339, 0.030322110412426346,
      0.03802181089200897, 0.042767343593845021, 0.019143422416588115,
      0.0042324594308612686, 0.036693664939063592, 0.016599466631221527,
      0.041987476743732245, 0.018586165400827866, 0.04141076350168147,
      0.0088259314480780126, 0.0064759930517333366, 0.043994179120893935,
      0.0022039564233848285, 0.034336000924040141, 0.036688645246679606,
      0.021858621862232926, 0.01899194584538141, 0.048982871992328723,
      0.019949671130581471, 0.022009345713468381, 0.0078403943772197785,
      0.016301714203320963, 0.015703096433673243, 0.044725033195212774,
      0.012351208963201988, 0.015533950795632462, 0.020443445402108552,
      0.035400544703202655, 0.007181879752974624, 0.043566103328651094,
      0.0041577948376729955, 0.023086891918406568, 0.0015194511830575687,
      0.037660026635442712, 0.035002133476480977, 0.010725612308199552,
      0.033995234276170933, 0.02786463403449644, 0.042533945129505146,
      0.027928274590144284, 0.045088683202378153, 0.020975885200659256,
      0.017906417639451815, 0.024449375868974318, 0.012798107050109543,
      0.046458463449619826, 0.023337840710521786, 0.012700392527847243,
      0.021560922363903695, 0.035126500562617145, 0.020116493399330072,
      0.00909200393328441, 0.042812555807334104, 0.029210061226829925,
      0.018678939133994883, 0.011084727338419892, 0.010949705885591687,
      0.026111622151275, 0.021671135674388078, 0.037065199414927655,
      0.00352248161642057, 0.042366671819859092, 0.033994011727895367,
      0.0068325760949289882, 0.042920109428934337, 0.009991706233353749,
      0.030366996088210602, 0.027152249182719409, 0.0081162346016251611,
      0.00028265340634227586, 0.038574257358270463, 0.038239377812767,
      0.021053467618094096, 0.002840659048681621, 0.029287349761711393,
      0.0087077622217015659, 0.036430533028315504, 0.026714552497051458,
      0.012653214387570633, 0.045852837414279243, 0.03790972648577081,
      0.044351536611400656, 0.0034399085551858333, 0.0091764097763919975,
      0.036853632729329441, 0.034835742632486087, 0.038849645285301437,
      0.025095170957687186, 0.021274841400131334, 0.030561856538715067,
      0.042788594568086813, 0.033539855449011162, 0.026179602235558031,
      0.014940770505351109, 0.035198453932559735, 0.019080543799444117,
      0.028384249890074334, 0.044393047765561383, 0.042147464449764437,
      0.044939927791609491, 0.046950154572327756, 0.040771757796937376,
      6.7891439301553946E-5, 0.00015453487787325804, 0.0043734408159375737,
      0.013036367560215985, 0.001139933532046672, 0.021204240940293974,
      0.017053248445461439, 0.027067696665385221, 0.046308454129153645,
      0.014924972352961981, 0.016904239692564094, 0.042974005360339483,
      0.017023915538271629, 0.0069060201525043222, 0.02538994776763014,
      0.0428328238445845, 0.019215680894130685, 0.034784546341438467,
      0.031395208889527439, 0.022519407717596276, 0.023680897104944223,
      0.047485317675176629, 0.0041748780894665443, 0.013991446000010628,
      0.022350365466735217, 0.029378563199765673, 0.043881706920726092,
      0.023455026011450959, 0.021870923785086035, 0.037309246998742267,
      0.023395523290387306, 0.043041367552893749, 0.023325600619074367,
      0.024905224356135465, 0.024371532720772273, 0.011473438737400844,
      0.004277611620452859, 0.0033691656804453298, 0.0444195467402289,
      0.011658384283482993, 0.043079787999218362, 0.035586754650395951,
      0.043640649652142691, 0.046900100345981521, 0.0069844639273750238,
      0.019695007242550175, 0.0490281414857527, 0.032239701299268807,
      0.044820488972696693, 0.024111520271839926, 0.00070465375945116262,
      0.031144017221739775, 0.011554768155556739, 0.026371698138831702,
      0.036249598067861946, 0.030370789557246772, 0.029418322289762534,
      0.0216717420016529, 0.012208644675351255, 0.021448017688900374,
      0.0005088727760888534, 0.030441072452218006, 0.0478987594098679,
      0.00477232617748003, 0.0017795281690073828, 0.044311755566287574,
      0.012347068252874828, 0.00044575281266684977, 0.040746013572401957,
      0.007024971827438331, 0.043993322014200135, 0.0047688393045262345,
      0.017628005062431978, 0.029671028389374566, 0.029259081923929627,
      0.033384088209225164, 0.032401355752785237, 0.0216684533669296,
      0.0069879379549628758, 0.037596475398754187, 0.012089339679360928,
      0.032522966123903117, 0.042868703041723334, 0.0042185235522574473,
      0.048604458085642087, 0.001572996777955793, 0.041770227522242936,
      0.041785667408543031, 0.0024928750672796487, 0.027294310444541493,
      0.047158491982773942, 0.016073653493499453, 0.040323340189666684,
      0.030069937762640459, 0.039481023256151923, 0.039959251752215784,
      0.00247823827891055, 0.014159931692047279, 0.032672841198998229,
      0.024482767266423556, 0.048642611850540148, 0.0374244954988541,
      0.028392057486940365, 0.014948208172859856, 0.012805489053091907,
      0.044328189720577352, 0.022340043139140026, 0.040799362664810372,
      0.0049168650872318869, 0.042979672673763625, 0.0013814504080587543,
      0.044957821712818223, 0.044996775026308777, 0.026205300480868152,
      0.0060099756323567406, 0.008889704591113946, 0.03530537972543072,
      0.041567987819352469, 0.0017416910283864495, 0.037891935519296628,
      0.047855608900058209, 0.017143525749842382, 0.031912185471235296,
      0.017150290598516256, 0.010823569809127043, 0.039310031351527226,
      0.036154497977273575, 0.013941945239372861, 0.029121571435224005,
      0.02105028906841401, 0.0046034353377183866, 0.0012013662503374267,
      0.024557290200568273, 0.013913351007593956, 0.016987858207553237,
      0.014367480475753798, 0.0085451617624739181, 0.019963165714071474,
      0.034882478422894915, 0.010183821856450748, 0.0333163244244755,
      0.022153304470413655, 0.021664763278784818, 0.0087619721197297554,
      0.0096601155880195189, 0.030821066582338054, 0.013450530393669342,
      0.027983896580795382, 0.0472391995877153, 0.035723581787447382,
      0.033960982769700353, 0.047969029065354316, 0.038766715597949329,
      0.030386348316105274, 0.047400117966667557, 0.0029820811792682922,
      0.013435617262139677, 0.049334002199014154, 0.038610336604701326,
      0.023767714997889738, 0.034044977777697653, 0.020846737746571087,
      0.019007460144659063, 0.01066351945376044, 0.019146899456707157,
      0.0014833875755051907, 0.023616053254203673, 0.016668634342189358,
      0.048792240205499465, 0.027772176930987859, 0.042315181889178627,
      0.020403174720095542, 0.023100908188694619, 0.041315336042321585,
      0.049560159993437262, 0.026197382463180444, 0.046271844481572413,
      0.036951093076096245, 0.028371502808596044, 0.048438883147145388,
      0.0412249709909461, 0.0479804639498942, 0.032317303272201135,
      0.01897867427201444, 0.023828734044016465, 0.045594490625035941,
      0.00074269278839367292, 0.00783469236169812, 0.023578393826492419,
      0.027149584742262829, 0.0029845516192904156, 0.032901515281404128,
      0.044481765168952137, 0.0054816303057605934, 0.021888655710905688,
      0.014011504480366194, 0.04926231562256015, 0.030437935366720181,
      0.012687460345922314, 0.0066307363424181259, 0.027250244560921157,
      0.041390196573546117, 0.041850313551141209, 0.04166743235172115,
      0.010185771714695813, 0.027220884962438671, 0.043747136077117429,
      0.006050004308483365, 0.042817538426863304, 0.044988800948116386,
      0.01089325619682352, 0.003848954246744596, 0.023710758024093604,
      0.041751373286733146, 0.023469675102091737, 0.020688496962474764,
      0.025137313192499934, 0.0062719979999827594, 0.006614266271396935,
      0.043523768257054292, 0.030147509065094349, 0.01326508630268996,
      0.043240129002846739, 0.002905472911198781, 0.022887694255104309,
      0.03611048220497589, 0.016949957579803995, 0.020060992846315628,
      0.026348987609741355, 0.044711785723225719, 0.038918032915665535,
      0.0034683801334501221, 0.013939226431052248, 0.018968491734303268,
      0.043233627319151868, 0.020998018470534958, 0.011993873674594159,
      0.029882725820683926, 0.023970220180099616, 0.044927375091760077,
      0.046735461895690514, 0.040894341690555877, 0.035445448945091045,
      0.037161028520225389, 0.044985489125827477, 0.0032619902419846027,
      0.016795558567292951, 0.00021675363043991425, 0.041404780157469304,
      0.025371768865158809, 0.018308121807453111, 0.011331985882218516,
      0.026741585479844857, 0.014474243319478254, 0.0034185448722601933,
      0.004248537278346321, 0.0034169734067001026, 0.020490824957525106,
      0.0061690691154690338, 0.022150829633111813, 0.044946986848214993,
      0.017681950089283034, 0.0060089059776264, 0.028455551272185416,
      0.043751636318274584, 0.0174287488551946, 0.00209605024543848,
      0.0071169859694195821, 0.0038296417438208556, 0.037026329465044333,
      0.02282625636595001, 0.033412465765776458, 0.034962303780156377,
      0.028567860619537908, 0.031434667097722087, 0.043888196254502562,
      0.033117586981401943, 0.043770680593740077, 0.023375850941911375,
      0.0070668014168332356, 0.0034067228616294245, 0.035712120345993595,
      0.015399301409149347, 0.033558198585578125, 0.032621041771113211,
      0.026552441917255087, 0.035755351588115263, 0.025240531151154079,
      0.024399967925261418, 0.02489191545150006, 0.0467987776662214,
      0.019464084139826272, 0.0058572582863788136, 0.012021177698561942,
      0.034245424731457308, 0.041962680752979806, 0.048507231644901734,
      0.010758480640201674, 0.038017167320911871, 0.02920514249290164,
      0.02014757887856207, 0.025502016887878357, 0.024782210954252412,
      0.032568417126585689, 0.037185307231147179, 0.0150976734563616,
      0.0044805967601061923, 0.0412982741242122, 0.019479350446084662,
      0.038765242663441973, 0.0089684547641988247, 0.0054680604858894036,
      0.045257916904581856, 0.04381755019612503, 0.049989628222237584,
      0.043212734302854182, 0.0018438761141936323, 0.027234122100362357,
      0.049880809109178664, 0.025550407712302315, 0.043675608796786086,
      0.0035110736168269432, 0.049376936841399828, 0.04613567147733532,
      0.028213045979988895, 0.021573102683717239, 0.016892228262824587,
      0.036036171392362572, 0.00068277833316675589, 0.01870300963879119,
      0.0461342610196084, 0.027323982401463623, 0.023694343487606268,
      0.024826865922009736, 0.015448554060969621, 0.047541877942045396,
      0.049099664043651, 0.025678155177128917, 0.049629490923603609,
      0.022792185103262537, 0.021302044044604937, 0.010660738939895553,
      0.0096624740214637586, 0.041637712298516684, 0.036331854980248039,
      0.02648728469528875, 0.041454036874966488, 0.025593721566912687,
      0.027598092312727321, 0.010664244700794807, 0.02939103131613649,
      0.0071381612674070284, 0.0026111763912575249, 0.034165395765296751,
      0.0304279739205964, 0.010982796739058043, 0.020313997115067248,
      0.031495397238124015, 0.02776538123627267, 0.0063789531019131374,
      0.0084599165827806862, 4.9970905837670726E-5, 0.020908123559856176,
      0.02442428394382223, 0.0079934421576235148, 0.033341928861187933,
      0.00089601845256277464, 0.0059837678259620948, 0.047606265443899641,
      0.048792698546609614, 0.0015457269334202884, 0.024694092187671837,
      0.043136106406941488, 0.012143808314655497, 0.041713508185939954,
      0.040679559620143413, 0.031448655203781539, 0.00011190992804166466,
      0.018986196986346723, 0.045220284824621759, 0.034017583253234236,
      0.018941156536308491, 0.03159773553511671, 0.012163476123529499,
      0.028570653580194835, 0.049086438688821135, 0.042484100945275841,
      0.01417220928445303, 0.034122883222510905, 0.01790622654910002,
      0.049346338498092515, 0.0041993147878094383, 0.012515294318085025,
      0.040567330765750288, 0.0042211551939042692, 0.026562698187092854,
      0.040031148957397511, 0.036941162096053179, 0.0070831490151229476,
      0.021894712895251148, 0.017519018620673461, 0.023924874859884478,
      0.0293701700062047, 0.0072902847609760679, 0.0452665303622182,
      0.0320097124166111, 0.0081469785720334927, 0.028295529550082868,
      0.046580806848859735, 0.039155094184231555, 0.03428435684894944,
      0.023310964249137114, 0.013015904783326482, 0.028463408553850957,
      0.012438533144403841, 0.015965079576044851, 0.045540111610847034,
      0.044261002049720527, 0.039729471208292608, 0.046290490358343858,
      0.0089419975387939, 0.025877057411823258, 0.031350265820465475,
      0.045659117295045223, 0.0331984126919404, 0.019459641149630655,
      0.0370003790708076, 0.040881742985436544, 0.030017239658824652,
      0.0042498532251351419, 0.046117900054502711, 0.0026798907658279083,
      0.0263512476338683, 0.005942663830987383, 0.019007149512050243,
      0.040641626650755464, 0.0122047957785845, 0.044221132954678749,
      0.035632339737957486, 0.018907421904107165, 0.01244598054979666,
      0.012642687261963654, 0.038362179726346757, 0.0024930942523620162,
      0.034264428380445459, 0.031013906107550067, 0.037334231498436253,
      0.048862782417283472, 0.019195675633030769, 0.013010280115686119,
      0.0438734768007062, 0.040304799175532334, 0.02305605398898497,
      0.0045480843962110605, 0.028213441263659905, 0.00936914445743034,
      0.026584479294736632, 0.017751666088669134, 0.0157391752377747,
      0.036337073442134687, 0.025788642906676915, 0.0395322448956239,
      0.010224629067947822, 0.033905303877989783, 0.0026242771319011818,
      0.040058618118124945, 0.033928431940965696, 0.047300447254203112,
      0.0045779071437415057, 0.045421918528908908, 0.025497651852660203,
      0.030745178257002754, 0.015803560044297987, 0.0038743740757710868,
      0.042530703300185338, 0.0072263453474256008, 0.018524289632700596,
      0.031119571654062553, 0.049877595121568516, 0.025867206662284634,
      0.049525560757515769, 0.011326723127791934, 0.0199002593210107,
      0.034828434475581996, 0.0032320379726761329, 0.03738307911891818,
      0.021020021561640657, 0.040565871011901171 } ;

    Copy_of_test_v_control_and_i_DW->FromWorkspace2_PWORK.TimePtr = (void *)
      pTimeValues0;
    Copy_of_test_v_control_and_i_DW->FromWorkspace2_PWORK.DataPtr = (void *)
      pDataValues0;
    Copy_of_test_v_control_and_i_DW->FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S91>/State-Space' incorporates:
   *  Constant: '<S26>/DC'
   *  Constant: '<S27>/DC'
   *  Constant: '<S28>/DC'
   *  Constant: '<S46>/eee'
   *  Constant: '<S64>/eee'
   *  Constant: '<S82>/eee'
   *  Constant: '<S93>/SwitchCurrents'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&Copy_of_test_v_control_and_i_DW->StateSpace_DSTATE[0];
    for (i = 0; i < 7; i++) {
      X0[i] = (Copy_of_test_v_control_a_ConstP.StateSpace_X0_param[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<7; i++) {
      for (j=0; j<7; j++)
        As[i*7 + j] = (Copy_of_test_v_control_a_ConstP.StateSpace_AS_param[i + j*
                       7]);
      for (j=0; j<16; j++)
        Bs[i*16 + j] = (Copy_of_test_v_control_a_ConstP.StateSpace_BS_param[i +
                        j*7]);
    }

    /* Copy and transpose C */
    for (i=0; i<25; i++) {
      for (j=0; j<7; j++)
        Cs[i*7 + j] = (Copy_of_test_v_control_a_ConstP.StateSpace_CS_param[i + j*
                       25]);
    }

    /* Copy and transpose D */
    for (i=0; i<25; i++) {
      for (j=0; j<16; j++)
        Ds[i*16 + j] = (Copy_of_test_v_control_a_ConstP.StateSpace_DS_param[i +
                        j*25]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*)
        Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS;
      int_T *gState = (int_T*)
        Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.G_STATE;
      real_T *yswitch = (real_T*)
        Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.Y_SWITCH;
      int_T *switchTypes = (int_T*)
        Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)
        Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS_INIT;

      /* Initialize work vectors */
      switch_status[0] = 0;
      switch_status_init[0] = 0;
      gState[0] = (int_T) 0.0;
      yswitch[0] = 1/0.1;
      switchTypes[0] = (int_T)1.0;
      idxOutSw[0] = ((int_T)0.0) - 1;
      switch_status[1] = 0;
      switch_status_init[1] = 0;
      gState[1] = (int_T) 0.0;
      yswitch[1] = 1/0.1;
      switchTypes[1] = (int_T)1.0;
      idxOutSw[1] = ((int_T)0.0) - 1;
      switch_status[2] = 0;
      switch_status_init[2] = 0;
      gState[2] = (int_T) 0.0;
      yswitch[2] = 1/0.1;
      switchTypes[2] = (int_T)1.0;
      idxOutSw[2] = ((int_T)0.0) - 1;
      switch_status[3] = 0;
      switch_status_init[3] = 0;
      gState[3] = (int_T) 0.0;
      yswitch[3] = 1/0.01;
      switchTypes[3] = (int_T)2.0;
      idxOutSw[3] = ((int_T)0.0) - 1;
      switch_status[4] = 0;
      switch_status_init[4] = 0;
      gState[4] = (int_T) 0.0;
      yswitch[4] = 1/0.001;
      switchTypes[4] = (int_T)3.0;
      idxOutSw[4] = ((int_T)0.0) - 1;
      switch_status[5] = 0;
      switch_status_init[5] = 0;
      gState[5] = (int_T) 0.0;
      yswitch[5] = 1/0.001;
      switchTypes[5] = (int_T)3.0;
      idxOutSw[5] = ((int_T)0.0) - 1;
      switch_status[6] = 0;
      switch_status_init[6] = 0;
      gState[6] = (int_T) 0.0;
      yswitch[6] = 1/0.001;
      switchTypes[6] = (int_T)3.0;
      idxOutSw[6] = ((int_T)0.0) - 1;
      switch_status[7] = 0;
      switch_status_init[7] = 0;
      gState[7] = (int_T) 0.0;
      yswitch[7] = 1/0.01;
      switchTypes[7] = (int_T)3.0;
      idxOutSw[7] = ((int_T)0.0) - 1;
      switch_status[8] = 0;
      switch_status_init[8] = 0;
      gState[8] = (int_T) 0.0;
      yswitch[8] = 1/0.01;
      switchTypes[8] = (int_T)3.0;
      idxOutSw[8] = ((int_T)0.0) - 1;
      switch_status[9] = 0;
      switch_status_init[9] = 0;
      gState[9] = (int_T) 0.0;
      yswitch[9] = 1/0.01;
      switchTypes[9] = (int_T)3.0;
      idxOutSw[9] = ((int_T)0.0) - 1;
    }
  }

  /* InitializeConditions for TransferFcn: '<S8>/Transfer Fcn2' */
  Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S8>/Transfer Fcn1' */
  Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S8>/Transfer Fcn' */
  Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Transfer Fcn2' */
  Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Transfer Fcn1' */
  Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_a = 0.0;

  /* InitializeConditions for Memory: '<S29>/Memory' */
  Copy_of_test_v_control_and_i_DW->Memory_PreviousInput = false;

  /* InitializeConditions for Memory: '<S31>/Memory' */
  Copy_of_test_v_control_and_i_DW->Memory_PreviousInput_a = false;

  /* InitializeConditions for TransferFcn: '<S13>/Transfer Fcn2' */
  Copy_of_test_v_control_and_i__X->TransferFcn2_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S13>/Transfer Fcn1' */
  Copy_of_test_v_control_and_i__X->TransferFcn1_CSTATE_d = 0.0;

  /* InitializeConditions for Memory: '<S33>/Memory' */
  Copy_of_test_v_control_and_i_DW->Memory_PreviousInput_f = false;

  /* InitializeConditions for TransferFcn: '<S12>/Transfer Fcn' */
  Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S13>/Transfer Fcn' */
  Copy_of_test_v_control_and_i__X->TransferFcn_CSTATE_o = 0.0;

  /* InitializeConditions for Derivative: '<S22>/Derivative' */
  Copy_of_test_v_control_and_i_DW->TimeStampA = (rtInf);
  Copy_of_test_v_control_and_i_DW->TimeStampB = (rtInf);
}

/* Model terminate function */
void Copy_of_test_v_control_and_i_control_with_droop_copy_terminate
  (RT_MODEL_Copy_of_test_v_contr_T * Copy_of_test_v_control_and_i_M)
{
  DW_Copy_of_test_v_control_and_T *Copy_of_test_v_control_and_i_DW =
    ((DW_Copy_of_test_v_control_and_T *) Copy_of_test_v_control_and_i_M->dwork);

  /* Terminate for S-Function (sfun_spssw_discc): '<S91>/State-Space' incorporates:
   *  Constant: '<S26>/DC'
   *  Constant: '<S27>/DC'
   *  Constant: '<S28>/DC'
   *  Constant: '<S46>/eee'
   *  Constant: '<S64>/eee'
   *  Constant: '<S82>/eee'
   *  Constant: '<S93>/SwitchCurrents'
   */

  /* S-Function block: <S91>/State-Space */
  {
    /* Free memory */
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.AS);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BS);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.CS);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DS);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.DX_COL);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.TMP2);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.BD_COL);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.TMP1);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.XTMP);

    /*
     * Circuit has switches*/
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.G_STATE);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SW_CHG);
    free(Copy_of_test_v_control_and_i_DW->StateSpace_PWORK.SWITCH_STATUS_INIT);
  }

  rt_FREE(Copy_of_test_v_control_and_i_M->solverInfo);

  /* model code */
  rt_FREE(Copy_of_test_v_control_and_i_M->blockIO);
  rt_FREE(Copy_of_test_v_control_and_i_M->contStates);
  rt_FREE(Copy_of_test_v_control_and_i_M->outputs);
  rt_FREE(Copy_of_test_v_control_and_i_M->dwork);

  {
    void *xptr = (void *) rtliGetLogXSignalPtrs
      (Copy_of_test_v_control_and_i_M->rtwLogInfo);
    void *yptr = (void *) rtliGetLogYSignalPtrs
      (Copy_of_test_v_control_and_i_M->rtwLogInfo);
    rt_FREE(xptr);
    rt_FREE(yptr);
  }

  rt_FREE(Copy_of_test_v_control_and_i_M->rtwLogInfo);
  rt_FREE(Copy_of_test_v_control_and_i_M);
}

/* Model data allocation function */
RT_MODEL_Copy_of_test_v_contr_T
  *Copy_of_test_v_control_and_i_control_with_droop_copy(void)
{
  RT_MODEL_Copy_of_test_v_contr_T *Copy_of_test_v_control_and_i_M;
  Copy_of_test_v_control_and_i_M = (RT_MODEL_Copy_of_test_v_contr_T *) malloc
    (sizeof(RT_MODEL_Copy_of_test_v_contr_T));
  if (Copy_of_test_v_control_and_i_M == NULL) {
    return NULL;
  }

  (void) memset((char *)Copy_of_test_v_control_and_i_M, 0,
                sizeof(RT_MODEL_Copy_of_test_v_contr_T));

  {
    /* Setup solver object */
    RTWSolverInfo *rt_SolverInfo = (RTWSolverInfo *) malloc(sizeof(RTWSolverInfo));
    rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,rt_SolverInfo);
    Copy_of_test_v_control_and_i_M->solverInfo = (rt_SolverInfo);
    rtsiSetSimTimeStepPtr(Copy_of_test_v_control_and_i_M->solverInfo,
                          &Copy_of_test_v_control_and_i_M->Timing.simTimeStep);
    rtsiSetTPtr(Copy_of_test_v_control_and_i_M->solverInfo, &rtmGetTPtr
                (Copy_of_test_v_control_and_i_M));
    rtsiSetStepSizePtr(Copy_of_test_v_control_and_i_M->solverInfo,
                       &Copy_of_test_v_control_and_i_M->Timing.stepSize0);
    rtsiSetdXPtr(Copy_of_test_v_control_and_i_M->solverInfo,
                 &Copy_of_test_v_control_and_i_M->derivs);
    rtsiSetContStatesPtr(Copy_of_test_v_control_and_i_M->solverInfo, (real_T **)
                         &Copy_of_test_v_control_and_i_M->contStates);
    rtsiSetNumContStatesPtr(Copy_of_test_v_control_and_i_M->solverInfo,
      &Copy_of_test_v_control_and_i_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(Copy_of_test_v_control_and_i_M->solverInfo,
      &Copy_of_test_v_control_and_i_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (Copy_of_test_v_control_and_i_M->solverInfo,
       &Copy_of_test_v_control_and_i_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(Copy_of_test_v_control_and_i_M->solverInfo,
      &Copy_of_test_v_control_and_i_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(Copy_of_test_v_control_and_i_M->solverInfo,
                          (&rtmGetErrorStatus(Copy_of_test_v_control_and_i_M)));
    rtsiSetRTModelPtr(Copy_of_test_v_control_and_i_M->solverInfo,
                      Copy_of_test_v_control_and_i_M);
  }

  rtsiSetSolverName(Copy_of_test_v_control_and_i_M->solverInfo,"ode3");

  /* Setup for data logging */
  {
    RTWLogInfo *rt_DataLoggingInfo = (RTWLogInfo *) malloc(sizeof(RTWLogInfo));
    rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,rt_DataLoggingInfo);
    rt_DataLoggingInfo->loggingInterval = NULL;
    Copy_of_test_v_control_and_i_M->rtwLogInfo = rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Copy_of_test_v_control_and_i_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Copy_of_test_v_control_and_i_M->rtwLogInfo, (NULL));

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      void **rt_LoggedOutputSignalPtrs = (void **)malloc(6*sizeof(void*));
      rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,
                         rt_LoggedOutputSignalPtrs);
      rtliSetLogYSignalPtrs(Copy_of_test_v_control_and_i_M->rtwLogInfo,
                            ((LogSignalPtrsType)rt_LoggedOutputSignalPtrs));
    }
  }

  /* block I/O */
  {
    B_Copy_of_test_v_control_and__T *b = (B_Copy_of_test_v_control_and__T *)
      malloc(sizeof(B_Copy_of_test_v_control_and__T));
    rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,b);
    Copy_of_test_v_control_and_i_M->blockIO = (b);
  }

  /* states (continuous) */
  {
    X_Copy_of_test_v_control_and__T *x = (X_Copy_of_test_v_control_and__T *)
      malloc(sizeof(X_Copy_of_test_v_control_and__T));
    rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,x);
    Copy_of_test_v_control_and_i_M->contStates = (x);
  }

  /* states (dwork) */
  {
    DW_Copy_of_test_v_control_and_T *dwork = (DW_Copy_of_test_v_control_and_T *)
      malloc(sizeof(DW_Copy_of_test_v_control_and_T));
    rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,dwork);
    Copy_of_test_v_control_and_i_M->dwork = (dwork);
  }

  /* external outputs */
  {
    ExtY_Copy_of_test_v_control_a_T *Copy_of_test_v_control_and_i__Y =
      (ExtY_Copy_of_test_v_control_a_T *) malloc(sizeof
      (ExtY_Copy_of_test_v_control_a_T));
    rt_VALIDATE_MEMORY(Copy_of_test_v_control_and_i_M,
                       Copy_of_test_v_control_and_i__Y);
    Copy_of_test_v_control_and_i_M->outputs = (Copy_of_test_v_control_and_i__Y);
  }

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  Copy_of_test_v_control_and_i_control_with_droop_copy_InitializeDataMapInfo
    (Copy_of_test_v_control_and_i_M, Copy_of_test_v_control_and_i_M->blockIO,
     Copy_of_test_v_control_and_i_M->dwork, (X_Copy_of_test_v_control_and__T *)
     Copy_of_test_v_control_and_i_M->contStates);

  {
    B_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__B =
      ((B_Copy_of_test_v_control_and__T *)
       Copy_of_test_v_control_and_i_M->blockIO);
    DW_Copy_of_test_v_control_and_T *Copy_of_test_v_control_and_i_DW =
      ((DW_Copy_of_test_v_control_and_T *) Copy_of_test_v_control_and_i_M->dwork);
    X_Copy_of_test_v_control_and__T *Copy_of_test_v_control_and_i__X =
      ((X_Copy_of_test_v_control_and__T *)
       Copy_of_test_v_control_and_i_M->contStates);
    ExtY_Copy_of_test_v_control_a_T *Copy_of_test_v_control_and_i__Y =
      (ExtY_Copy_of_test_v_control_a_T *)
      Copy_of_test_v_control_and_i_M->outputs;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
    rtsiSetSimTimeStep(Copy_of_test_v_control_and_i_M->solverInfo,
                       MAJOR_TIME_STEP);
    Copy_of_test_v_control_and_i_M->intgData.y =
      Copy_of_test_v_control_and_i_M->odeY;
    Copy_of_test_v_control_and_i_M->intgData.f[0] =
      Copy_of_test_v_control_and_i_M->odeF[0];
    Copy_of_test_v_control_and_i_M->intgData.f[1] =
      Copy_of_test_v_control_and_i_M->odeF[1];
    Copy_of_test_v_control_and_i_M->intgData.f[2] =
      Copy_of_test_v_control_and_i_M->odeF[2];
    Copy_of_test_v_control_and_i_M->contStates =
      ((X_Copy_of_test_v_control_and__T *) Copy_of_test_v_control_and_i__X);
    rtsiSetSolverData(Copy_of_test_v_control_and_i_M->solverInfo, (void *)
                      &Copy_of_test_v_control_and_i_M->intgData);
    rtmSetTPtr(Copy_of_test_v_control_and_i_M,
               &Copy_of_test_v_control_and_i_M->Timing.tArray[0]);
    rtmSetTFinal(Copy_of_test_v_control_and_i_M, 10.0);
    Copy_of_test_v_control_and_i_M->Timing.stepSize0 = 0.01;

    /* Setup for data logging */
    {
      rtliSetLogT(Copy_of_test_v_control_and_i_M->rtwLogInfo, "tout");
      rtliSetLogX(Copy_of_test_v_control_and_i_M->rtwLogInfo, "");
      rtliSetLogXFinal(Copy_of_test_v_control_and_i_M->rtwLogInfo, "");
      rtliSetLogVarNameModifier(Copy_of_test_v_control_and_i_M->rtwLogInfo,
        "rt_");
      rtliSetLogFormat(Copy_of_test_v_control_and_i_M->rtwLogInfo, 2);
      rtliSetLogMaxRows(Copy_of_test_v_control_and_i_M->rtwLogInfo, 0);
      rtliSetLogDecimation(Copy_of_test_v_control_and_i_M->rtwLogInfo, 1);

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        ((void **) rtliGetLogYSignalPtrs
          (Copy_of_test_v_control_and_i_M->rtwLogInfo))[0] =
          &Copy_of_test_v_control_and_i__Y->v_out0;
        ((void **) rtliGetLogYSignalPtrs
          (Copy_of_test_v_control_and_i_M->rtwLogInfo))[1] =
          &Copy_of_test_v_control_and_i__Y->i_out0;
        ((void **) rtliGetLogYSignalPtrs
          (Copy_of_test_v_control_and_i_M->rtwLogInfo))[2] =
          &Copy_of_test_v_control_and_i__Y->v_out1;
        ((void **) rtliGetLogYSignalPtrs
          (Copy_of_test_v_control_and_i_M->rtwLogInfo))[3] =
          &Copy_of_test_v_control_and_i__Y->i_out1;
        ((void **) rtliGetLogYSignalPtrs
          (Copy_of_test_v_control_and_i_M->rtwLogInfo))[4] =
          &Copy_of_test_v_control_and_i__Y->v_out2;
        ((void **) rtliGetLogYSignalPtrs
          (Copy_of_test_v_control_and_i_M->rtwLogInfo))[5] =
          &Copy_of_test_v_control_and_i__Y->i_out2;
      }

      {
        static int_T rt_LoggedOutputWidths[] = {
          1,
          1,
          1,
          1,
          1,
          1
        };

        static int_T rt_LoggedOutputNumDimensions[] = {
          1,
          1,
          1,
          1,
          1,
          1
        };

        static int_T rt_LoggedOutputDimensions[] = {
          1,
          1,
          1,
          1,
          1,
          1
        };

        static boolean_T rt_LoggedOutputIsVarDims[] = {
          0,
          0,
          0,
          0,
          0,
          0
        };

        static void* rt_LoggedCurrentSignalDimensions[] = {
          (NULL),
          (NULL),
          (NULL),
          (NULL),
          (NULL),
          (NULL)
        };

        static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
          4,
          4,
          4,
          4,
          4,
          4
        };

        static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
          SS_DOUBLE,
          SS_DOUBLE,
          SS_DOUBLE,
          SS_DOUBLE,
          SS_DOUBLE,
          SS_DOUBLE
        };

        static int_T rt_LoggedOutputComplexSignals[] = {
          0,
          0,
          0,
          0,
          0,
          0
        };

        static RTWPreprocessingFcnPtr rt_LoggingPreprocessingFcnPtrs[] = {
          (NULL),
          (NULL),
          (NULL),
          (NULL),
          (NULL),
          (NULL)
        };

        static const char_T *rt_LoggedOutputLabels_0[] = { "" };

        static const char_T *rt_LoggedOutputBlockNames_0[] = {
          "Copy_of_test_v_control_and_i_control_with_droop_copy/v_out0" };

        static const char_T *rt_LoggedOutputLabels_1[] = { "" };

        static const char_T *rt_LoggedOutputBlockNames_1[] = {
          "Copy_of_test_v_control_and_i_control_with_droop_copy/i_out0" };

        static const char_T *rt_LoggedOutputLabels_2[] = { "" };

        static const char_T *rt_LoggedOutputBlockNames_2[] = {
          "Copy_of_test_v_control_and_i_control_with_droop_copy/v_out1" };

        static const char_T *rt_LoggedOutputLabels_3[] = { "" };

        static const char_T *rt_LoggedOutputBlockNames_3[] = {
          "Copy_of_test_v_control_and_i_control_with_droop_copy/i_out1" };

        static const char_T *rt_LoggedOutputLabels_4[] = { "" };

        static const char_T *rt_LoggedOutputBlockNames_4[] = {
          "Copy_of_test_v_control_and_i_control_with_droop_copy/v_out2" };

        static const char_T *rt_LoggedOutputLabels_5[] = { "" };

        static const char_T *rt_LoggedOutputBlockNames_5[] = {
          "Copy_of_test_v_control_and_i_control_with_droop_copy/i_out2" };

        static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
          { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

          { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

          { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

          { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

          { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

          { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
        };

        static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
          {
            1,
            rt_LoggedOutputWidths,
            rt_LoggedOutputNumDimensions,
            rt_LoggedOutputDimensions,
            rt_LoggedOutputIsVarDims,
            rt_LoggedCurrentSignalDimensions,
            rt_LoggedCurrentSignalDimensionsSize,
            rt_LoggedOutputDataTypeIds,
            rt_LoggedOutputComplexSignals,
            (NULL),
            rt_LoggingPreprocessingFcnPtrs,

            { rt_LoggedOutputLabels_0 },
            (NULL),
            (NULL),
            (NULL),

            { rt_LoggedOutputBlockNames_0 },

            { (NULL) },
            (NULL),
            rt_RTWLogDataTypeConvert
          },

          {
            1,
            rt_LoggedOutputWidths+1,
            rt_LoggedOutputNumDimensions+1,
            rt_LoggedOutputDimensions+1,
            rt_LoggedOutputIsVarDims+1,
            rt_LoggedCurrentSignalDimensions+1,
            rt_LoggedCurrentSignalDimensionsSize+1,
            rt_LoggedOutputDataTypeIds+1,
            rt_LoggedOutputComplexSignals+1,
            (NULL),
            rt_LoggingPreprocessingFcnPtrs+1,

            { rt_LoggedOutputLabels_1 },
            (NULL),
            (NULL),
            (NULL),

            { rt_LoggedOutputBlockNames_1 },

            { (NULL) },
            (NULL),
            rt_RTWLogDataTypeConvert+1
          },

          {
            1,
            rt_LoggedOutputWidths+2,
            rt_LoggedOutputNumDimensions+2,
            rt_LoggedOutputDimensions+2,
            rt_LoggedOutputIsVarDims+2,
            rt_LoggedCurrentSignalDimensions+2,
            rt_LoggedCurrentSignalDimensionsSize+2,
            rt_LoggedOutputDataTypeIds+2,
            rt_LoggedOutputComplexSignals+2,
            (NULL),
            rt_LoggingPreprocessingFcnPtrs+2,

            { rt_LoggedOutputLabels_2 },
            (NULL),
            (NULL),
            (NULL),

            { rt_LoggedOutputBlockNames_2 },

            { (NULL) },
            (NULL),
            rt_RTWLogDataTypeConvert+2
          },

          {
            1,
            rt_LoggedOutputWidths+3,
            rt_LoggedOutputNumDimensions+3,
            rt_LoggedOutputDimensions+3,
            rt_LoggedOutputIsVarDims+3,
            rt_LoggedCurrentSignalDimensions+3,
            rt_LoggedCurrentSignalDimensionsSize+3,
            rt_LoggedOutputDataTypeIds+3,
            rt_LoggedOutputComplexSignals+3,
            (NULL),
            rt_LoggingPreprocessingFcnPtrs+3,

            { rt_LoggedOutputLabels_3 },
            (NULL),
            (NULL),
            (NULL),

            { rt_LoggedOutputBlockNames_3 },

            { (NULL) },
            (NULL),
            rt_RTWLogDataTypeConvert+3
          },

          {
            1,
            rt_LoggedOutputWidths+4,
            rt_LoggedOutputNumDimensions+4,
            rt_LoggedOutputDimensions+4,
            rt_LoggedOutputIsVarDims+4,
            rt_LoggedCurrentSignalDimensions+4,
            rt_LoggedCurrentSignalDimensionsSize+4,
            rt_LoggedOutputDataTypeIds+4,
            rt_LoggedOutputComplexSignals+4,
            (NULL),
            rt_LoggingPreprocessingFcnPtrs+4,

            { rt_LoggedOutputLabels_4 },
            (NULL),
            (NULL),
            (NULL),

            { rt_LoggedOutputBlockNames_4 },

            { (NULL) },
            (NULL),
            rt_RTWLogDataTypeConvert+4
          },

          {
            1,
            rt_LoggedOutputWidths+5,
            rt_LoggedOutputNumDimensions+5,
            rt_LoggedOutputDimensions+5,
            rt_LoggedOutputIsVarDims+5,
            rt_LoggedCurrentSignalDimensions+5,
            rt_LoggedCurrentSignalDimensionsSize+5,
            rt_LoggedOutputDataTypeIds+5,
            rt_LoggedOutputComplexSignals+5,
            (NULL),
            rt_LoggingPreprocessingFcnPtrs+5,

            { rt_LoggedOutputLabels_5 },
            (NULL),
            (NULL),
            (NULL),

            { rt_LoggedOutputBlockNames_5 },

            { (NULL) },
            (NULL),
            rt_RTWLogDataTypeConvert+5
          }
        };

        rtliSetLogYSignalInfo(Copy_of_test_v_control_and_i_M->rtwLogInfo,
                              rt_LoggedOutputSignalInfo);

        /* set currSigDims field */
        rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
        rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
        rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[2];
        rt_LoggedCurrentSignalDimensions[3] = &rt_LoggedOutputWidths[3];
        rt_LoggedCurrentSignalDimensions[4] = &rt_LoggedOutputWidths[4];
        rt_LoggedCurrentSignalDimensions[5] = &rt_LoggedOutputWidths[5];
      }

      rtliSetLogY(Copy_of_test_v_control_and_i_M->rtwLogInfo,
                  "v_out1,i_out1,v_out2,i_out2,v_out3,i_out3");
    }

    Copy_of_test_v_control_and_i_M->Timing.stepSize = (0.01);

    /* block I/O */
    (void) memset(((void *) Copy_of_test_v_control_and_i__B), 0,
                  sizeof(B_Copy_of_test_v_control_and__T));

    /* states (continuous) */
    {
      (void) memset((void *)Copy_of_test_v_control_and_i__X, 0,
                    sizeof(X_Copy_of_test_v_control_and__T));
    }

    /* states (dwork) */
    (void) memset((void *)Copy_of_test_v_control_and_i_DW, 0,
                  sizeof(DW_Copy_of_test_v_control_and_T));

    /* external outputs */
    (void) memset((void *)Copy_of_test_v_control_and_i__Y, 0,
                  sizeof(ExtY_Copy_of_test_v_control_a_T));
  }

  return Copy_of_test_v_control_and_i_M;
}
