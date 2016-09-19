/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: conv.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 10:24:10
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_5.h"
#include "conv.h"
#include "L3_5_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real32_T *A
 *                const emxArray_real32_T *B
 *                emxArray_real32_T *C
 * Return Type  : void
 */
void conv(const emxArray_real32_T *A, const emxArray_real32_T *B,
          emxArray_real32_T *C)
{
  int nA;
  int nB;
  int nApnB;
  int nC;
  int jA2;
  float s;
  int k;
  nA = A->size[1];
  nB = B->size[1];
  nApnB = A->size[1] + B->size[1];
  if (B->size[1] == 0) {
    nC = nApnB;
  } else {
    nC = nApnB - 1;
  }

  jA2 = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = nC;
  emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(float));
  if (B->size[1] == 0) {
    jA2 = C->size[0] * C->size[1];
    C->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(float));
    nApnB = C->size[1];
    for (jA2 = 0; jA2 < nApnB; jA2++) {
      C->data[C->size[0] * jA2] = 0.0F;
    }
  } else {
    for (nApnB = 1; nApnB <= nC; nApnB++) {
      if (nA <= nApnB) {
        jA2 = nA;
      } else {
        jA2 = nApnB;
      }

      s = 0.0F;
      if (nB < nApnB + 1) {
        k = nApnB - nB;
      } else {
        k = 0;
      }

      while (k + 1 <= jA2) {
        s += A->data[k] * B->data[(nApnB - k) - 1];
        k++;
      }

      C->data[nApnB - 1] = s;
    }
  }
}

/*
 * File trailer for conv.c
 *
 * [EOF]
 */
