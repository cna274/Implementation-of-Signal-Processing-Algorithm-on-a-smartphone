/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sin.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 26-Apr-2016 16:20:33
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music.h"
#include "sin.h"

/* Function Definitions */

/*
 * Arguments    : float x[101]
 * Return Type  : void
 */
void b_sin(float x[101])
{
  int k;
  for (k = 0; k < 101; k++) {
    x[k] = (float)sin(x[k]);
  }
}

/*
 * Arguments    : float x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void c_sin(float x_data[], int x_size[2])
{
  int nx;
  int k;
  nx = x_size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x_data[k] = (float)sin(x_data[k]);
  }
}

/*
 * File trailer for sin.c
 *
 * [EOF]
 */
