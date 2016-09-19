/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: conv.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 09:54:06
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_4.h"
#include "conv.h"
#include "L3_4_emxutil.h"

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
  int jA2;
  int jC;
  float s;
  int k;
  nA = A->size[1];
  nB = B->size[1];
  nApnB = A->size[1] + B->size[1];
  if ((A->size[1] == 0) || (B->size[1] == 0)) {
  } else {
    nApnB--;
  }

  jA2 = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = nApnB;
  emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(float));
  if ((A->size[1] == 0) || (B->size[1] == 0) || (nApnB == 0)) {
    jA2 = C->size[0] * C->size[1];
    C->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(float));
    jC = C->size[1];
    for (jA2 = 0; jA2 < jC; jA2++) {
      C->data[C->size[0] * jA2] = 0.0F;
    }
  } else {
    for (jC = 1; jC <= nApnB; jC++) {
      if (nA <= jC) {
        jA2 = nA;
      } else {
        jA2 = jC;
      }

      s = 0.0F;
      if (nB < jC + 1) {
        k = (jC - nB) + 1;
      } else {
        k = 1;
      }

      while (k <= jA2) {
        s += A->data[k - 1] * B->data[jC - k];
        k++;
      }

      C->data[jC - 1] = s;
    }
  }
}

/*
 * File trailer for conv.c
 *
 * [EOF]
 */
