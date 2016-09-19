/*
 * File: L6_1_emxutil.h
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 27-Apr-2016 13:23:03
 */

#ifndef __L6_1_EMXUTIL_H__
#define __L6_1_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "L6_1_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for L6_1_emxutil.h
 *
 * [EOF]
 */
