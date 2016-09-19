/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: abs.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L4_1.h"
#include "abs.h"
#include "L4_1_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real32_T *x
 *                emxArray_real32_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_real32_T *x, emxArray_real32_T *y)
{
  int k;
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
  for (k = 0; k + 1 <= x->size[1]; k++) {
    y->data[k] = (float)fabs(x->data[k]);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
