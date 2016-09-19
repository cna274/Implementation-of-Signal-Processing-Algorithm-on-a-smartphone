/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: exp.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 15:32:08
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_5.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : float x[1001]
 * Return Type  : void
 */
void b_exp(float* x)
{
  int k;
  for (k = 0; k < 1001; k++) {
    x[k] = (float)exp(x[k]);
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
