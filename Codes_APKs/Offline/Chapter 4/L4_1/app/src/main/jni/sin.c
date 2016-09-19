/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sin.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L4_1.h"
#include "sin.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real32_T *x
 * Return Type  : void
 */
void b_sin(emxArray_real32_T *x)
{
  int nx;
  int k;
  nx = x->size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = (float)sin(x->data[k]);
  }
}

/*
 * File trailer for sin.c
 *
 * [EOF]
 */
