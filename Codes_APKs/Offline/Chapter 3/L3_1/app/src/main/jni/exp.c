/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: exp.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 15-Apr-2016 18:32:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_1.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real32_T *x
 * Return Type  : void
 */
void b_exp(emxArray_real32_T *x)
{
  int nx;
  int k;
  nx = x->size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = (float)exp(x->data[k]);
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
