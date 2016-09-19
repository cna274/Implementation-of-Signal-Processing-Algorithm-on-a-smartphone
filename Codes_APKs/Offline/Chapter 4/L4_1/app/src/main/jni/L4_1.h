/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L4_1.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

#ifndef __L4_1_H__
#define __L4_1_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "L4_1_types.h"

/* Function Declarations */
extern void L4_1(float A, float T, float N, float w, emxArray_real32_T *XT,
                 emxArray_real32_T *x_hat, emxArray_real32_T *an,
                 emxArray_real32_T *bn, float *a0, emxArray_real32_T *error,
                 float *max_error, float *avg_error);

#endif

/*
 * File trailer for L4_1.h
 *
 * [EOF]
 */
