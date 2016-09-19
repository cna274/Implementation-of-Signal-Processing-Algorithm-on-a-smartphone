/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ipermute.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Apr-2016 15:44:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_1.h"
#include "ipermute.h"
#include "L5_1_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal32_T *b
 *                emxArray_creal32_T *a
 * Return Type  : void
 */
void ipermute(const emxArray_creal32_T *b, emxArray_creal32_T *a)
{
  int i2;
  int loop_ub;
  i2 = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = b->size[0];
  emxEnsureCapacity((emxArray__common *)a, i2, (int)sizeof(creal32_T));
  loop_ub = b->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    a->data[a->size[0] * i2] = b->data[i2];
  }
}

/*
 * File trailer for ipermute.c
 *
 * [EOF]
 */
