/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_4_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 09:54:06
 */

#ifndef __L3_4_EMXUTIL_H__
#define __L3_4_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "L3_4_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for L3_4_emxutil.h
 *
 * [EOF]
 */
