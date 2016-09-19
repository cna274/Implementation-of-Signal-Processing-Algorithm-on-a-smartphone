/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_1.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 15-Apr-2016 18:32:29
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_1.h"
#include "L3_1_emxutil.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : float a
 *                float b
 *                float Delta
 *                emxArray_real32_T *y
 *                emxArray_real32_T *y_ac
 *                float *MSE
 *                emxArray_real32_T *x1
 *                emxArray_real32_T *x2
 * Return Type  : void
 */
void L3_1(float a, float b, float Delta, emxArray_real32_T *y, emxArray_real32_T
          *y_ac, float *MSE, emxArray_real32_T *x1, emxArray_real32_T *x2)
{
  int jA2;
  float s;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *t;
  int k;
  int nm1d2;
  float kd;
  float Lt;
  int nA;
  int nB;
  int nApnB;
  emxArray_real32_T *fcnOutput;
  emxArray_real32_T *b_y;
  int b_k;
  int c_k;

  /* Function to convolute the signal generated  */
  /* using matlab command. */
  if (rtIsNaNF(Delta)) {
    jA2 = 1;
    s = ((real32_T)rtNaN);
    bnew = 8.0F;
  } else if ((Delta == 0.0F) || (Delta < 0.0F)) {
    jA2 = 0;
    s = 0.0F;
    bnew = 8.0F;
  } else if (rtIsInfF(Delta)) {
    jA2 = 1;
    s = 0.0F;
    bnew = 8.0F;
  } else {
    s = 0.0F;
    ndbl = floor(8.0 / Delta + 0.5);
    apnd = ndbl * Delta;
    if (Delta > 0.0F) {
      cdiff = apnd - 8.0;
    } else {
      cdiff = 8.0 - apnd;
    }

    if (fabs(cdiff) < 1.9073486328125E-6) {
      ndbl++;
      bnew = 8.0F;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * Delta);
    } else {
      ndbl++;
      bnew = (float)apnd;
    }

    if (ndbl >= 0.0) {
      jA2 = (int)ndbl;
    } else {
      jA2 = 0;
    }
  }

  emxInit_real32_T(&t, 2);
  k = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = jA2;
  emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
  if (jA2 > 0) {
    t->data[0] = s;
    if (jA2 > 1) {
      t->data[jA2 - 1] = bnew;
      k = jA2 - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * Delta;
        t->data[k] = s + kd;
        t->data[(jA2 - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == jA2 - 1) {
        t->data[nm1d2] = (s + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * Delta;
        t->data[nm1d2] = s + kd;
        t->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  Lt = (float)t->size[1];

  /* First Signal  */
  k = x1->size[0] * x1->size[1];
  x1->size[0] = 1;
  x1->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)x1, k, (int)sizeof(float));
  nm1d2 = t->size[0] * t->size[1];
  for (k = 0; k < nm1d2; k++) {
    x1->data[k] = -a * t->data[k];
  }

  b_exp(x1);

  /* Second Signal */
  k = x2->size[0] * x2->size[1];
  x2->size[0] = 1;
  x2->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)x2, k, (int)sizeof(float));
  nm1d2 = t->size[0] * t->size[1];
  for (k = 0; k < nm1d2; k++) {
    x2->data[k] = -b * t->data[k];
  }

  b_exp(x2);

  /* Convolution by direct method using matlab command */
  nA = x1->size[1];
  nB = x2->size[1];
  nApnB = x1->size[1] + x2->size[1];
  if ((x1->size[1] == 0) || (x2->size[1] == 0)) {
  } else {
    nApnB--;
  }

  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = nApnB;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
  if ((x1->size[1] == 0) || (x2->size[1] == 0) || (nApnB == 0)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
    nm1d2 = y->size[1];
    for (k = 0; k < nm1d2; k++) {
      y->data[y->size[0] * k] = 0.0F;
    }
  } else {
    for (nm1d2 = 1; nm1d2 <= nApnB; nm1d2++) {
      if (nA <= nm1d2) {
        jA2 = nA;
      } else {
        jA2 = nm1d2;
      }

      s = 0.0F;
      if (nB < nm1d2 + 1) {
        k = (nm1d2 - nB) + 1;
      } else {
        k = 1;
      }

      while (k <= jA2) {
        s += x1->data[k - 1] * x2->data[nm1d2 - k];
        k++;
      }

      y->data[nm1d2 - 1] = s;
    }
  }

  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
  nm1d2 = y->size[0];
  jA2 = y->size[1];
  nm1d2 *= jA2;
  for (k = 0; k < nm1d2; k++) {
    y->data[k] *= Delta;
  }

  /* Convolution by Analytical method */
  s = 1.0F / (a - b);
  k = y_ac->size[0] * y_ac->size[1];
  y_ac->size[0] = 1;
  y_ac->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)y_ac, k, (int)sizeof(float));
  nm1d2 = t->size[0] * t->size[1];
  for (k = 0; k < nm1d2; k++) {
    y_ac->data[k] = -b * t->data[k];
  }

  emxInit_real32_T(&fcnOutput, 2);
  b_exp(y_ac);
  k = fcnOutput->size[0] * fcnOutput->size[1];
  fcnOutput->size[0] = 1;
  fcnOutput->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)fcnOutput, k, (int)sizeof(float));
  nm1d2 = t->size[0] * t->size[1];
  for (k = 0; k < nm1d2; k++) {
    fcnOutput->data[k] = -a * t->data[k];
  }

  b_exp(fcnOutput);
  k = y_ac->size[0] * y_ac->size[1];
  y_ac->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y_ac, k, (int)sizeof(float));
  nm1d2 = y_ac->size[0];
  jA2 = y_ac->size[1];
  nm1d2 *= jA2;
  for (k = 0; k < nm1d2; k++) {
    y_ac->data[k] = s * (y_ac->data[k] - fcnOutput->data[k]);
  }

  /* Mean Sqaure Error between two methods of convolution */
  if (1.0F > t->size[1]) {
    nm1d2 = 0;
  } else {
    nm1d2 = (int)(float)t->size[1];
  }

  k = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = nm1d2;
  emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
  for (k = 0; k < nm1d2; k++) {
    t->data[t->size[0] * k] = y->data[k] - y_ac->data[y_ac->size[0] * k];
  }

  k = fcnOutput->size[0] * fcnOutput->size[1];
  fcnOutput->size[0] = 1;
  fcnOutput->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)fcnOutput, k, (int)sizeof(float));
  nm1d2 = t->size[0] * t->size[1];
  for (k = 0; k < nm1d2; k++) {
    fcnOutput->data[k] = t->data[k];
  }

  emxInit_real32_T(&b_y, 2);
  k = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)b_y, k, (int)sizeof(float));
  jA2 = t->size[1];
  emxFree_real32_T(&t);

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(c_k)

  for (b_k = 1; b_k <= jA2; b_k++) {
    c_k = b_k;
    b_y->data[c_k - 1] = fcnOutput->data[c_k - 1] * fcnOutput->data[c_k - 1];
  }

  emxFree_real32_T(&fcnOutput);
  if (b_y->size[1] == 0) {
    s = 0.0F;
  } else {
    s = b_y->data[0];
    for (k = 2; k <= b_y->size[1]; k++) {
      s += b_y->data[k - 1];
    }
  }

  emxFree_real32_T(&b_y);
  *MSE = s / Lt;
}

/*
 * File trailer for L3_1.c
 *
 * [EOF]
 */
