/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_4.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 15:24:14
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_4.h"
#include "L3_4_emxutil.h"
#include "conv.h"

/* Function Definitions */

/*
 * Arguments    : float dt
 *                emxArray_real32_T *x
 *                emxArray_real32_T *h1
 *                emxArray_real32_T *h2
 *                emxArray_real32_T *b_y1
 *                emxArray_real32_T *y2
 *                emxArray_real32_T *y3
 *                emxArray_real32_T *y4
 *                emxArray_real32_T *y5
 *                emxArray_real32_T *y6
 * Return Type  : void
 */
void L3_4(float dt, emxArray_real32_T *x, emxArray_real32_T *h1,
          emxArray_real32_T *h2, emxArray_real32_T *b_y1, emxArray_real32_T *y2,
          emxArray_real32_T *y3, emxArray_real32_T *y4, emxArray_real32_T *y5,
          emxArray_real32_T *y6)
{
  float anew;
  float bnew;
  int k;
  int nm1d2;
  int n;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *vec;
  float kd;
  double absb;
  emxArray_real32_T *b_vec;
  emxArray_real32_T *b_dt;
  emxArray_real32_T *c_dt;
  emxArray_real32_T *d_dt;
  emxArray_real32_T *e_dt;
  emxArray_real32_T *b_h1;
  anew = 2.0F / dt;
  bnew = 2.0F / dt;
  k = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = (int)anew + (int)bnew;
  emxEnsureCapacity((emxArray__common *)x, k, (int)sizeof(float));
  nm1d2 = (int)anew;
  for (k = 0; k < nm1d2; k++) {
    x->data[x->size[0] * k] = 1.0F;
  }

  nm1d2 = (int)bnew;
  for (k = 0; k < nm1d2; k++) {
    x->data[x->size[0] * (k + (int)anew)] = -1.0F;
  }

  if (rtIsNaNF(dt) || rtIsNaNF(2.0F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 2.0F - dt;
  } else if ((dt == 0.0F) || ((0.0F < 2.0F - dt) && (dt < 0.0F)) || ((2.0F - dt <
    0.0F) && (dt > 0.0F))) {
    n = 0;
    anew = 0.0F;
    bnew = 2.0F - dt;
  } else if (rtIsInfF(2.0F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 2.0F - dt;
  } else if (rtIsInfF(dt)) {
    n = 1;
    anew = 0.0F;
    bnew = 2.0F - dt;
  } else {
    anew = 0.0F;
    ndbl = floor((double)(2.0F - dt) / dt + 0.5);
    apnd = ndbl * dt;
    if (dt > 0.0F) {
      cdiff = apnd - (2.0F - dt);
    } else {
      cdiff = (2.0F - dt) - apnd;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)fabs(2.0F - dt)) {
      ndbl++;
      bnew = 2.0F - dt;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * dt);
    } else {
      ndbl++;
      bnew = (float)apnd;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real32_T(&vec, 2);
  k = vec->size[0] * vec->size[1];
  vec->size[0] = 1;
  vec->size[1] = n;
  emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
  if (n > 0) {
    vec->data[0] = anew;
    if (n > 1) {
      vec->data[n - 1] = bnew;
      k = n - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * dt;
        vec->data[k] = anew + kd;
        vec->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        vec->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * dt;
        vec->data[nm1d2] = anew + kd;
        vec->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  if (rtIsNaNF(-dt) || rtIsNaNF(dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = dt;
  } else if ((-dt == 0.0F) || (2.0F < dt) || ((dt < 2.0F) && (-dt > 0.0F))) {
    n = 0;
    anew = 2.0F;
    bnew = dt;
  } else if (rtIsInfF(dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = dt;
  } else if (rtIsInfF(-dt)) {
    n = 1;
    anew = 2.0F;
    bnew = dt;
  } else {
    anew = 2.0F;
    ndbl = floor((dt - 2.0) / -dt + 0.5);
    apnd = 2.0 + ndbl * -dt;
    if (-dt > 0.0F) {
      cdiff = apnd - dt;
    } else {
      cdiff = dt - apnd;
    }

    absb = fabs(dt);
    if ((2.0 >= absb) || rtIsNaN(absb)) {
      absb = 2.0;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
      ndbl++;
      bnew = dt;
    } else if (cdiff > 0.0) {
      bnew = (float)(2.0 + (ndbl - 1.0) * -dt);
    } else {
      ndbl++;
      bnew = (float)apnd;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real32_T(&b_vec, 2);
  k = b_vec->size[0] * b_vec->size[1];
  b_vec->size[0] = 1;
  b_vec->size[1] = n;
  emxEnsureCapacity((emxArray__common *)b_vec, k, (int)sizeof(float));
  if (n > 0) {
    b_vec->data[0] = anew;
    if (n > 1) {
      b_vec->data[n - 1] = bnew;
      k = n - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * -dt;
        b_vec->data[k] = anew + kd;
        b_vec->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        b_vec->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * -dt;
        b_vec->data[nm1d2] = anew + kd;
        b_vec->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  k = h1->size[0] * h1->size[1];
  h1->size[0] = 1;
  h1->size[1] = vec->size[1] + b_vec->size[1];
  emxEnsureCapacity((emxArray__common *)h1, k, (int)sizeof(float));
  nm1d2 = vec->size[1];
  for (k = 0; k < nm1d2; k++) {
    h1->data[h1->size[0] * k] = vec->data[vec->size[0] * k];
  }

  nm1d2 = b_vec->size[1];
  for (k = 0; k < nm1d2; k++) {
    h1->data[h1->size[0] * (k + vec->size[1])] = b_vec->data[b_vec->size[0] * k];
  }

  emxFree_real32_T(&b_vec);
  if (rtIsNaNF(dt) || rtIsNaNF(4.0F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 4.0F - dt;
  } else if ((dt == 0.0F) || ((0.0F < 4.0F - dt) && (dt < 0.0F)) || ((4.0F - dt <
    0.0F) && (dt > 0.0F))) {
    n = 0;
    anew = 0.0F;
    bnew = 4.0F - dt;
  } else if (rtIsInfF(4.0F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 4.0F - dt;
  } else if (rtIsInfF(dt)) {
    n = 1;
    anew = 0.0F;
    bnew = 4.0F - dt;
  } else {
    anew = 0.0F;
    ndbl = floor((double)(4.0F - dt) / dt + 0.5);
    apnd = ndbl * dt;
    if (dt > 0.0F) {
      cdiff = apnd - (4.0F - dt);
    } else {
      cdiff = (4.0F - dt) - apnd;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)fabs(4.0F - dt)) {
      ndbl++;
      bnew = 4.0F - dt;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * dt);
    } else {
      ndbl++;
      bnew = (float)apnd;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  k = h2->size[0] * h2->size[1];
  h2->size[0] = 1;
  h2->size[1] = n;
  emxEnsureCapacity((emxArray__common *)h2, k, (int)sizeof(float));
  if (n > 0) {
    h2->data[0] = anew;
    if (n > 1) {
      h2->data[n - 1] = bnew;
      k = n - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * dt;
        h2->data[k] = anew + kd;
        h2->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        h2->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * dt;
        h2->data[nm1d2] = anew + kd;
        h2->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  emxInit_real32_T(&b_dt, 2);
  conv(h1, x, vec);
  k = b_dt->size[0] * b_dt->size[1];
  b_dt->size[0] = 1;
  b_dt->size[1] = vec->size[1];
  emxEnsureCapacity((emxArray__common *)b_dt, k, (int)sizeof(float));
  nm1d2 = vec->size[0] * vec->size[1];
  for (k = 0; k < nm1d2; k++) {
    b_dt->data[k] = dt * vec->data[k];
  }

  conv(b_dt, h2, b_y1);
  k = b_y1->size[0] * b_y1->size[1];
  b_y1->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)b_y1, k, (int)sizeof(float));
  nm1d2 = b_y1->size[0];
  k = b_y1->size[1];
  nm1d2 *= k;
  emxFree_real32_T(&b_dt);
  for (k = 0; k < nm1d2; k++) {
    b_y1->data[k] *= dt;
  }

  emxInit_real32_T(&c_dt, 2);
  conv(h2, x, vec);
  k = c_dt->size[0] * c_dt->size[1];
  c_dt->size[0] = 1;
  c_dt->size[1] = vec->size[1];
  emxEnsureCapacity((emxArray__common *)c_dt, k, (int)sizeof(float));
  nm1d2 = vec->size[0] * vec->size[1];
  for (k = 0; k < nm1d2; k++) {
    c_dt->data[k] = dt * vec->data[k];
  }

  conv(c_dt, h1, y2);
  k = y2->size[0] * y2->size[1];
  y2->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y2, k, (int)sizeof(float));
  nm1d2 = y2->size[0];
  k = y2->size[1];
  nm1d2 *= k;
  emxFree_real32_T(&c_dt);
  for (k = 0; k < nm1d2; k++) {
    y2->data[k] *= dt;
  }

  emxInit_real32_T(&d_dt, 2);
  conv(x, h1, vec);
  k = d_dt->size[0] * d_dt->size[1];
  d_dt->size[0] = 1;
  d_dt->size[1] = vec->size[1];
  emxEnsureCapacity((emxArray__common *)d_dt, k, (int)sizeof(float));
  nm1d2 = vec->size[0] * vec->size[1];
  for (k = 0; k < nm1d2; k++) {
    d_dt->data[k] = dt * vec->data[k];
  }

  conv(d_dt, h2, y3);
  k = y3->size[0] * y3->size[1];
  y3->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y3, k, (int)sizeof(float));
  nm1d2 = y3->size[0];
  k = y3->size[1];
  nm1d2 *= k;
  emxFree_real32_T(&d_dt);
  for (k = 0; k < nm1d2; k++) {
    y3->data[k] *= dt;
  }

  emxInit_real32_T(&e_dt, 2);
  conv(h1, h2, vec);
  k = e_dt->size[0] * e_dt->size[1];
  e_dt->size[0] = 1;
  e_dt->size[1] = vec->size[1];
  emxEnsureCapacity((emxArray__common *)e_dt, k, (int)sizeof(float));
  nm1d2 = vec->size[0] * vec->size[1];
  for (k = 0; k < nm1d2; k++) {
    e_dt->data[k] = dt * vec->data[k];
  }

  conv(e_dt, x, y4);
  k = y4->size[0] * y4->size[1];
  y4->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y4, k, (int)sizeof(float));
  nm1d2 = y4->size[0];
  k = y4->size[1];
  nm1d2 *= k;
  emxFree_real32_T(&e_dt);
  for (k = 0; k < nm1d2; k++) {
    y4->data[k] *= dt;
  }

  emxInit_real32_T(&b_h1, 2);
  k = b_h1->size[0] * b_h1->size[1];
  b_h1->size[0] = 1;
  b_h1->size[1] = h1->size[1];
  emxEnsureCapacity((emxArray__common *)b_h1, k, (int)sizeof(float));
  nm1d2 = h1->size[0] * h1->size[1];
  for (k = 0; k < nm1d2; k++) {
    b_h1->data[k] = h1->data[k] + h2->data[k];
  }

  conv(x, b_h1, y5);
  k = y5->size[0] * y5->size[1];
  y5->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y5, k, (int)sizeof(float));
  nm1d2 = y5->size[0];
  k = y5->size[1];
  nm1d2 *= k;
  emxFree_real32_T(&b_h1);
  for (k = 0; k < nm1d2; k++) {
    y5->data[k] *= dt;
  }

  conv(x, h1, y6);
  conv(x, h2, vec);
  k = y6->size[0] * y6->size[1];
  y6->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y6, k, (int)sizeof(float));
  nm1d2 = y6->size[0];
  k = y6->size[1];
  nm1d2 *= k;
  for (k = 0; k < nm1d2; k++) {
    y6->data[k] = dt * y6->data[k] + dt * vec->data[k];
  }

  emxFree_real32_T(&vec);
}

/*
 * File trailer for L3_4.c
 *
 * [EOF]
 */
