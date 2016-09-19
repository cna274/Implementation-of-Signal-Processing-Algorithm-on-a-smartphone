/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mod.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 21-Apr-2016 03:13:11
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_3.h"
#include "mod.h"

/* Function Definitions */

/*
 * Arguments    : float x
 * Return Type  : float
 */
float b_mod(float x)
{
  return x - (float)floor(x / 10.0F) * 10.0F;
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
