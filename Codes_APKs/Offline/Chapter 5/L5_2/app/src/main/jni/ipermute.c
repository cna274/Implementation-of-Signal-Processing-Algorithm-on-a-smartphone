/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ipermute.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 17:09:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_2.h"
#include "ipermute.h"
#include "L5_2_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal32_T *b
 *                emxArray_creal32_T *a
 * Return Type  : void
 */
void ipermute(const emxArray_creal32_T *b, emxArray_creal32_T *a)
{
  int i3;
  int loop_ub;
  i3 = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = b->size[0];
  emxEnsureCapacity((emxArray__common *)a, i3, (int)sizeof(creal32_T));
  loop_ub = b->size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    a->data[a->size[0] * i3] = b->data[i3];
  }
}

/*
 * File trailer for ipermute.c
 *
 * [EOF]
 */
