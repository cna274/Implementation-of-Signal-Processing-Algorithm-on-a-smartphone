/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: isfinite.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 12:21:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Echo.h"
#include "isfinite.h"

/* Function Definitions */

/*
 * Arguments    : float x
 * Return Type  : boolean_T
 */
boolean_T b_isfinite(float x)
{
  return (!rtIsInfF(x)) && (!rtIsNaNF(x));
}

/*
 * File trailer for isfinite.c
 *
 * [EOF]
 */
