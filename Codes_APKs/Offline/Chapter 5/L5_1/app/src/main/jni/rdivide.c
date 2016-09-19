/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rdivide.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Apr-2016 15:44:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_1.h"
#include "rdivide.h"
#include "L5_1_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real32_T *x
 *                float y
 *                emxArray_real32_T *z
 * Return Type  : void
 */
void rdivide(const emxArray_real32_T *x, float y, emxArray_real32_T *z)
{
  int i0;
  int loop_ub;
  i0 = z->size[0] * z->size[1];
  z->size[0] = 1;
  z->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)z, i0, (int)sizeof(float));
  loop_ub = x->size[0] * x->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    z->data[i0] = x->data[i0] / y;
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
