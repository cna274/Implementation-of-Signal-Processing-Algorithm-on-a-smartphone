/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L5_1_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Apr-2016 15:44:34
 */

#ifndef __L5_1_EMXUTIL_H__
#define __L5_1_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "L5_1_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_creal32_T(emxArray_creal32_T **pEmxArray);
extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
extern void emxInit_creal32_T(emxArray_creal32_T **pEmxArray, int numDimensions);
extern void emxInit_creal32_T1(emxArray_creal32_T **pEmxArray, int numDimensions);
extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);
extern void emxInit_real32_T1(emxArray_real32_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for L5_1_emxutil.h
 *
 * [EOF]
 */
