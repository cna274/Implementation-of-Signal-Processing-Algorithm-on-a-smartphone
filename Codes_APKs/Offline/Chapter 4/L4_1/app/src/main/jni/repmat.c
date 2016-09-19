/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: repmat.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L4_1.h"
#include "repmat.h"
#include "L4_1_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real32_T *a
 *                emxArray_real32_T *b
 * Return Type  : void
 */
void repmat(const emxArray_real32_T *a, emxArray_real32_T *b)
{
  int outsize_idx_1;
  int jtilecol;
  int ibtile;
  int jcol;
  outsize_idx_1 = a->size[1] * 3;
  jtilecol = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = outsize_idx_1;
  emxEnsureCapacity((emxArray__common *)b, jtilecol, (int)sizeof(float));
  if ((!(a->size[1] == 0)) && (!(outsize_idx_1 == 0))) {
    outsize_idx_1 = a->size[1];
    for (jtilecol = 0; jtilecol < 3; jtilecol++) {
      ibtile = jtilecol * outsize_idx_1;
      for (jcol = 1; jcol <= outsize_idx_1; jcol++) {
        b->data[(ibtile + jcol) - 1] = a->data[jcol - 1];
      }
    }
  }
}

/*
 * File trailer for repmat.c
 *
 * [EOF]
 */
