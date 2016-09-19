/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_5.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 10:24:10
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_5.h"
#include "L3_5_emxutil.h"
#include "conv.h"
#include "exp.h"

/* Variable Definitions */
static emxArray_real32_T *buffer;
static boolean_T buffer_not_empty;

/* Function Definitions */

/*
 * Arguments    : const float x[256]
 *                float fs
 *                float w2
 *                float R
 *                float L
 *                float C
 *                float output[256]
 * Return Type  : void
 */
void L3_5(const float *x, float fs, float w2, float R, float L, float C,
          float *output)
{
  float dt;
  int n;
  float anew;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *t;
  int i0;
  int nm1d2;
  int k;
  float kd;
  emxArray_real32_T *r0;
  emxArray_real32_T *c;
  dt = 1.0F / fs;
  if (rtIsNaNF(dt) || rtIsNaNF(1.0F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 1.0F - dt;
  } else if ((dt == 0.0F) || ((0.0F < 1.0F - dt) && (dt < 0.0F)) || ((1.0F - dt <
    0.0F) && (dt > 0.0F))) {
    n = 0;
    anew = 0.0F;
    bnew = 1.0F - dt;
  } else if (rtIsInfF(1.0F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 1.0F - dt;
  } else if (rtIsInfF(dt)) {
    n = 1;
    anew = 0.0F;
    bnew = 1.0F - dt;
  } else {
    anew = 0.0F;
    ndbl = floor((double)(1.0F - dt) / dt + 0.5);
    apnd = ndbl * dt;
    if (dt > 0.0F) {
      cdiff = apnd - (1.0F - dt);
    } else {
      cdiff = (1.0F - dt) - apnd;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)fabs(1.0F - dt)) {
      ndbl++;
      bnew = 1.0F - dt;
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

  emxInit_real32_T(&t, 2);
  i0 = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = n;
  emxEnsureCapacity((emxArray__common *)t, i0, (int)sizeof(float));
  if (n > 0) {
    t->data[0] = anew;
    if (n > 1) {
      t->data[n - 1] = bnew;
      i0 = n - 1;
      nm1d2 = i0 / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * dt;
        t->data[k] = anew + kd;
        t->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        t->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * dt;
        t->data[nm1d2] = anew + kd;
        t->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  if (!buffer_not_empty) {
    i0 = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = (int)(256.0F + (float)t->size[1]);
    emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
    nm1d2 = (int)(256.0F + (float)t->size[1]);
    for (i0 = 0; i0 < nm1d2; i0++) {
      buffer->data[i0] = 0.0F;
    }

    buffer_not_empty = true;
  }

  anew = (float)buffer->size[1] - (float)t->size[1];
  if (anew + 1.0F > buffer->size[1]) {
    i0 = 0;
    k = 0;
  } else {
    i0 = (int)(anew + 1.0F) - 1;
    k = (int)(float)buffer->size[1];
  }

  emxInit_real32_T(&r0, 2);
  n = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = (k - i0) + 256;
  emxEnsureCapacity((emxArray__common *)r0, n, (int)sizeof(float));
  nm1d2 = k - i0;
  for (n = 0; n < nm1d2; n++) {
    r0->data[r0->size[0] * n] = buffer->data[buffer->size[0] * (i0 + n)];
  }

  for (n = 0; n < 256; n++) {
    r0->data[r0->size[0] * ((n + k) - i0)] = x[n];
  }

  i0 = buffer->size[0] * buffer->size[1];
  buffer->size[0] = 1;
  buffer->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
  nm1d2 = r0->size[1];
  for (i0 = 0; i0 < nm1d2; i0++) {
    buffer->data[buffer->size[0] * i0] = r0->data[r0->size[0] * i0];
  }

  emxFree_real32_T(&r0);
  buffer_not_empty = true;
  if (w2 == 0.0F) {
    /*  RL response */
    anew = R / L;
    bnew = -R / L;
    i0 = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, i0, (int)sizeof(float));
    nm1d2 = t->size[0];
    k = t->size[1];
    nm1d2 *= k;
    for (i0 = 0; i0 < nm1d2; i0++) {
      t->data[i0] *= bnew;
    }

    emxInit_real32_T(&c, 2);
    b_exp(t);
    i0 = c->size[0] * c->size[1];
    c->size[0] = 1;
    c->size[1] = t->size[1];
    emxEnsureCapacity((emxArray__common *)c, i0, (int)sizeof(float));
    nm1d2 = t->size[0] * t->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      c->data[i0] = anew * t->data[i0];
    }

    conv(buffer, c, t);
    i0 = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, i0, (int)sizeof(float));
    nm1d2 = t->size[0];
    k = t->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&c);
    for (i0 = 0; i0 < nm1d2; i0++) {
      t->data[i0] *= dt;
    }
  } else {
    /*  RC response */
    anew = 1.0F / (R * C);
    bnew = R * C;
    i0 = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, i0, (int)sizeof(float));
    nm1d2 = t->size[0];
    k = t->size[1];
    nm1d2 *= k;
    for (i0 = 0; i0 < nm1d2; i0++) {
      t->data[i0] = -t->data[i0] / bnew;
    }

    emxInit_real32_T(&c, 2);
    b_exp(t);
    bnew = 1.0F / (R * C);
    i0 = c->size[0] * c->size[1];
    c->size[0] = 1;
    c->size[1] = t->size[1];
    emxEnsureCapacity((emxArray__common *)c, i0, (int)sizeof(float));
    nm1d2 = t->size[0] * t->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      c->data[i0] = anew * t->data[i0];
    }

    conv(buffer, c, t);
    i0 = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, i0, (int)sizeof(float));
    nm1d2 = t->size[0];
    k = t->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&c);
    for (i0 = 0; i0 < nm1d2; i0++) {
      t->data[i0] = bnew - dt * t->data[i0];
    }
  }

  for (i0 = 0; i0 < 256; i0++) {
    output[i0] = t->data[t->size[0] * (256 + i0)];
  }

  emxFree_real32_T(&t);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_5_free(void)
{
  emxFree_real32_T(&buffer);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_5_init(void)
{
  emxInit_real32_T(&buffer, 2);
  buffer_not_empty = false;
}

/*
 * File trailer for L3_5.c
 *
 * [EOF]
 */
