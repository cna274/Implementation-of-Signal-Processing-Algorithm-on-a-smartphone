/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: angle.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Apr-2016 15:44:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_1.h"
#include "angle.h"
#include "L5_1_emxutil.h"

/* Function Declarations */
static float rt_atan2f_snf(float u0, float u1);

/* Function Definitions */

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_atan2f_snf(float u0, float u1)
{
  float y;
  int b_u0;
  int b_u1;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = ((real32_T)rtNaN);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    if (u0 > 0.0F) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0F) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = (float)atan2((float)b_u0, (float)b_u1);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = (float)atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : const emxArray_creal32_T *x
 *                emxArray_real32_T *y
 * Return Type  : void
 */
void angle(const emxArray_creal32_T *x, emxArray_real32_T *y)
{
  int k;
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
  for (k = 0; k + 1 <= x->size[1]; k++) {
    y->data[k] = rt_atan2f_snf(x->data[k].im, x->data[k].re);
  }
}

/*
 * File trailer for angle.c
 *
 * [EOF]
 */
