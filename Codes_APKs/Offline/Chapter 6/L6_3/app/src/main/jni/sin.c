/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sin.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 21-Apr-2016 03:13:11
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_3.h"
#include "sin.h"

/* Function Definitions */

/*
 * Arguments    : float x[1025]
 * Return Type  : void
 */
void b_sin(float x[1025])
{
  int k;
  for (k = 0; k < 1025; k++) {
    x[k] = (float)sin(x[k]);
  }
}

/*
 * Arguments    : float x[16385]
 * Return Type  : void
 */
void c_sin(float x[16385])
{
  int k;
  for (k = 0; k < 16385; k++) {
    x[k] = (float)sin(x[k]);
  }
}

/*
 * File trailer for sin.c
 *
 * [EOF]
 */
