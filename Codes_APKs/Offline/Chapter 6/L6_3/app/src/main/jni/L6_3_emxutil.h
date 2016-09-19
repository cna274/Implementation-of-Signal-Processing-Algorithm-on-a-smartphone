/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L6_3_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 21-Apr-2016 03:13:11
 */

#ifndef __L6_3_EMXUTIL_H__
#define __L6_3_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "L6_3_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);
extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for L6_3_emxutil.h
 *
 * [EOF]
 */
