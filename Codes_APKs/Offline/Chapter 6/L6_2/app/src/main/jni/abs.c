/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: abs.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 03:17:05
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_2.h"
#include "abs.h"

/* Function Declarations */
static float rt_hypotf_snf(float u0, float u1);

/* Function Definitions */

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = (float)fabs(u0);
  b = (float)fabs(u1);
  if (a < b) {
    a /= b;
    y = b * (float)sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * (float)sqrt(b * b + 1.0F);
  } else if (rtIsNaNF(b)) {
    y = b;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 * Arguments    : const creal32_T x_data[]
 *                const int x_size[2]
 *                float y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void b_abs(const creal32_T x_data[], const int x_size[2], float y_data[], int
           y_size[2])
{
  int k;
  y_size[0] = 1;
  y_size[1] = (short)x_size[1];
  for (k = 0; k + 1 <= x_size[1]; k++) {
    y_data[k] = rt_hypotf_snf(x_data[k].re, x_data[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
