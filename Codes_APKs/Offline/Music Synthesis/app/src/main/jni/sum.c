/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sum.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 26-Apr-2016 16:20:33
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const float x_data[]
 *                const int x_size[2]
 * Return Type  : float
 */
float sum(const float x_data[], const int x_size[2])
{
  float y;
  int k;
  if (x_size[1] == 0) {
    y = 0.0F;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[1]; k++) {
      y += x_data[k - 1];
    }
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
