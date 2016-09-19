/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: conv.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 15:32:08
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_5.h"
#include "conv.h"

/* Function Definitions */

/*
 * Arguments    : const float A[1001]
 *                const float B[1001]
 *                float C[2001]
 * Return Type  : void
 */
void conv(const float* A, const float* B, float* C)
{
  int jC;
  int jA2;
  float s;
  int k;
  for (jC = 0; jC < 2001; jC++) {
    if (1001 < jC + 1) {
      jA2 = 1000;
    } else {
      jA2 = jC;
    }

    s = 0.0F;
    if (1001 < jC + 2) {
      k = jC - 1000;
    } else {
      k = 0;
    }

    while (k + 1 <= jA2 + 1) {
      s += A[k] * B[jC - k];
      k++;
    }

    C[jC] = s;
  }
}

/*
 * File trailer for conv.c
 *
 * [EOF]
 */
