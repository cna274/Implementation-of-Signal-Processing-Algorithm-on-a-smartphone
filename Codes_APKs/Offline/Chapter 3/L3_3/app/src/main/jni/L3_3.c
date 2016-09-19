/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_3.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 15:11:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_3.h"
#include "L3_3_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : float dt
 *                emxArray_real32_T *y
 *                emxArray_real32_T *x1
 *                emxArray_real32_T *x2
 * Return Type  : void
 */
void L3_3(float dt, emxArray_real32_T *y, emxArray_real32_T *x1,
          emxArray_real32_T *x2)
{
  int jA2;
  float s;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *a;
  int k;
  int nm1d2;
  float kd;
  int nA;
  int nB;
  int nApnB;
  if (rtIsNaNF(dt)) {
    jA2 = 1;
    s = ((real32_T)rtNaN);
    bnew = 1.0F;
  } else if ((dt == 0.0F) || (dt < 0.0F)) {
    jA2 = 0;
    s = 0.0F;
    bnew = 1.0F;
  } else if (rtIsInfF(dt)) {
    jA2 = 1;
    s = 0.0F;
    bnew = 1.0F;
  } else {
    s = 0.0F;
    ndbl = floor(1.0 / dt + 0.5);
    apnd = ndbl * dt;
    if (dt > 0.0F) {
      cdiff = apnd - 1.0;
    } else {
      cdiff = 1.0 - apnd;
    }

    if (fabs(cdiff) < 2.384185791015625E-7) {
      ndbl++;
      bnew = 1.0F;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * dt);
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

  emxInit_real32_T(&a, 2);
  k = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = jA2;
  emxEnsureCapacity((emxArray__common *)a, k, (int)sizeof(float));
  if (jA2 > 0) {
    a->data[0] = s;
    if (jA2 > 1) {
      a->data[jA2 - 1] = bnew;
      k = jA2 - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * dt;
        a->data[k] = s + kd;
        a->data[(jA2 - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == jA2 - 1) {
        a->data[nm1d2] = (s + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * dt;
        a->data[nm1d2] = s + kd;
        a->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  s = 4.0F / dt;
  k = x1->size[0] * x1->size[1];
  x1->size[0] = 1;
  x1->size[1] = a->size[1] + (int)s;
  emxEnsureCapacity((emxArray__common *)x1, k, (int)sizeof(float));
  nm1d2 = a->size[1];
  for (k = 0; k < nm1d2; k++) {
    x1->data[x1->size[0] * k] = a->data[a->size[0] * k];
  }

  nm1d2 = (int)s;
  for (k = 0; k < nm1d2; k++) {
    x1->data[x1->size[0] * (k + a->size[1])] = 1.0F;
  }

  emxFree_real32_T(&a);
  if (rtIsNaNF(dt)) {
    jA2 = 1;
    s = ((real32_T)rtNaN);
    bnew = 2.0F;
  } else if ((dt == 0.0F) || (dt < 0.0F)) {
    jA2 = 0;
    s = 0.0F;
    bnew = 2.0F;
  } else if (rtIsInfF(dt)) {
    jA2 = 1;
    s = 0.0F;
    bnew = 2.0F;
  } else {
    s = 0.0F;
    ndbl = floor(2.0 / dt + 0.5);
    apnd = ndbl * dt;
    if (dt > 0.0F) {
      cdiff = apnd - 2.0;
    } else {
      cdiff = 2.0 - apnd;
    }

    if (fabs(cdiff) < 4.76837158203125E-7) {
      ndbl++;
      bnew = 2.0F;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * dt);
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

  k = x2->size[0] * x2->size[1];
  x2->size[0] = 1;
  x2->size[1] = jA2;
  emxEnsureCapacity((emxArray__common *)x2, k, (int)sizeof(float));
  if (jA2 > 0) {
    x2->data[0] = s;
    if (jA2 > 1) {
      x2->data[jA2 - 1] = bnew;
      k = jA2 - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * dt;
        x2->data[k] = s + kd;
        x2->data[(jA2 - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == jA2 - 1) {
        x2->data[nm1d2] = (s + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * dt;
        x2->data[nm1d2] = s + kd;
        x2->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

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
    y->data[k] *= dt;
  }
}

/*
 * File trailer for L3_3.c
 *
 * [EOF]
 */
