/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: abs.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 17:09:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_2.h"
#include "abs.h"
#include "L5_2_emxutil.h"

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
 * Arguments    : const emxArray_creal32_T *x
 *                emxArray_real32_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_creal32_T *x, emxArray_real32_T *y)
{
  int k;
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
  for (k = 0; k + 1 <= x->size[1]; k++) {
    y->data[k] = rt_hypotf_snf(x->data[k].re, x->data[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
