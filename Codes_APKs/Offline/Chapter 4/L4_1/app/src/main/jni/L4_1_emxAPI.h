/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L4_1_emxAPI.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

#ifndef __L4_1_EMXAPI_H__
#define __L4_1_EMXAPI_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "L4_1_types.h"

/* Function Declarations */
extern emxArray_real32_T *emxCreateND_real32_T(int numDimensions, int *size);
extern emxArray_real32_T *emxCreateWrapperND_real32_T(float *data, int
  numDimensions, int *size);
extern emxArray_real32_T *emxCreateWrapper_real32_T(float *data, int rows, int
  cols);
extern emxArray_real32_T *emxCreate_real32_T(int rows, int cols);
extern void emxDestroyArray_real32_T(emxArray_real32_T *emxArray);
extern void emxInitArray_real32_T(emxArray_real32_T **pEmxArray, int
  numDimensions);

#endif

/*
 * File trailer for L4_1_emxAPI.h
 *
 * [EOF]
 */
