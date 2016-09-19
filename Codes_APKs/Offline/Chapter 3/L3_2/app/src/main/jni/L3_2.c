/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 15:04:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_2.h"
#include "L3_2_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : float Delta
 *                emxArray_real32_T *con
 *                emxArray_real32_T *x
 *                emxArray_real32_T *h
 * Return Type  : void
 */
void L3_2(float Delta, emxArray_real32_T *con, emxArray_real32_T *x,
          emxArray_real32_T *h)
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
  int nA;
  int nB;
  int nApnB;
  if (rtIsNaNF(Delta)) {
    jA2 = 1;
    s = ((real32_T)rtNaN);
    bnew = 10.0F;
  } else if ((Delta == 0.0F) || (Delta < 0.0F)) {
    jA2 = 0;
    s = 0.0F;
    bnew = 10.0F;
  } else if (rtIsInfF(Delta)) {
    jA2 = 1;
    s = 0.0F;
    bnew = 10.0F;
  } else {
    s = 0.0F;
    ndbl = floor(10.0 / Delta + 0.5);
    apnd = ndbl * Delta;
    if (Delta > 0.0F) {
      cdiff = apnd - 10.0;
    } else {
      cdiff = 10.0 - apnd;
    }

    if (fabs(cdiff) < 2.384185791015625E-6) {
      ndbl++;
      bnew = 10.0F;
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

  k = t->size[0] * t->size[1];
  t->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
  nm1d2 = t->size[0];
  jA2 = t->size[1];
  nm1d2 *= jA2;
  for (k = 0; k < nm1d2; k++) {
    t->data[k] *= -2.0F;
  }

  k = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)x, k, (int)sizeof(float));
  nm1d2 = t->size[0] * t->size[1];
  for (k = 0; k < nm1d2; k++) {
    x->data[k] = t->data[k];
  }

  for (k = 0; k + 1 <= t->size[1]; k++) {
    x->data[k] = (float)exp(x->data[k]);
  }

  emxFree_real32_T(&t);
  s = 1.0F / Delta;
  bnew = 2.0F / Delta;
  kd = 7.0F / Delta;
  k = h->size[0] * h->size[1];
  h->size[0] = 1;
  h->size[1] = ((int)s + (int)bnew) + (int)kd;
  emxEnsureCapacity((emxArray__common *)h, k, (int)sizeof(float));
  nm1d2 = (int)s;
  for (k = 0; k < nm1d2; k++) {
    h->data[h->size[0] * k] = 0.0F;
  }

  nm1d2 = (int)bnew;
  for (k = 0; k < nm1d2; k++) {
    h->data[h->size[0] * (k + (int)s)] = 1.0F;
  }

  nm1d2 = (int)kd;
  for (k = 0; k < nm1d2; k++) {
    h->data[h->size[0] * ((k + (int)s) + (int)bnew)] = 0.0F;
  }

  nA = x->size[1];
  nB = h->size[1];
  nApnB = x->size[1] + h->size[1];
  if ((x->size[1] == 0) || (h->size[1] == 0)) {
  } else {
    nApnB--;
  }

  k = con->size[0] * con->size[1];
  con->size[0] = 1;
  con->size[1] = nApnB;
  emxEnsureCapacity((emxArray__common *)con, k, (int)sizeof(float));
  if ((x->size[1] == 0) || (h->size[1] == 0) || (nApnB == 0)) {
    k = con->size[0] * con->size[1];
    con->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)con, k, (int)sizeof(float));
    nm1d2 = con->size[1];
    for (k = 0; k < nm1d2; k++) {
      con->data[con->size[0] * k] = 0.0F;
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
        s += x->data[k - 1] * h->data[nm1d2 - k];
        k++;
      }

      con->data[nm1d2 - 1] = s;
    }
  }

  k = con->size[0] * con->size[1];
  con->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)con, k, (int)sizeof(float));
  nm1d2 = con->size[0];
  jA2 = con->size[1];
  nm1d2 *= jA2;
  for (k = 0; k < nm1d2; k++) {
    con->data[k] *= Delta;
  }
}

/*
 * File trailer for L3_2.c
 *
 * [EOF]
 */
