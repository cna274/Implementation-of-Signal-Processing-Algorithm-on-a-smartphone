/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_1.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 15-Apr-2016 18:32:29
 */

#ifndef __L3_1_H__
#define __L3_1_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "L3_1_types.h"

/* Function Declarations */
extern void L3_1(float a, float b, float Delta, emxArray_real32_T *y,
                 emxArray_real32_T *y_ac, float *MSE, emxArray_real32_T *x1,
                 emxArray_real32_T *x2);

#endif

/*
 * File trailer for L3_1.h
 *
 * [EOF]
 */
