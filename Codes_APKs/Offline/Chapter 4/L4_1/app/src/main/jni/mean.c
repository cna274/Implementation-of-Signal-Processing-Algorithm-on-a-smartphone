/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mean.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L4_1.h"
#include "mean.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real32_T *x
 * Return Type  : float
 */
float mean(const emxArray_real32_T *x)
{
  float y;
  int k;
  if (x->size[1] == 0) {
    y = 0.0F;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[1]; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (float)x->size[1];
  return y;
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
