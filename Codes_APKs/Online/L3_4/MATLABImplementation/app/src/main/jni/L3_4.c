/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_4.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 09:54:06
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_4.h"
#include "L3_4_emxutil.h"
#include "conv.h"

/* Variable Definitions */
static emxArray_real32_T *buffer;
static boolean_T buffer_not_empty;

/* Function Definitions */

/*
 * Arguments    : const float input[256]
 *                float fs
 *                float option
 *                float output[256]
 * Return Type  : void
 */
void L3_4(const float *input, float fs, float option, float *output)
{
  float dt;
  int n;
  float anew;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *h2;
  int i0;
  int nm1d2;
  int k;
  float kd;
  double absb;
  emxArray_real32_T *y;
  emxArray_real32_T *h1;
  emxArray_real32_T *r0;
  emxArray_real32_T *fcnOutput;
  emxArray_real32_T *b_dt;
  dt = 1.0F / fs;
  if (rtIsNaNF(dt) || rtIsNaNF(0.5F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 0.5F - dt;
  } else if ((dt == 0.0F) || ((0.0F < 0.5F - dt) && (dt < 0.0F)) || ((0.5F - dt <
    0.0F) && (dt > 0.0F))) {
    n = 0;
    anew = 0.0F;
    bnew = 0.5F - dt;
  } else if (rtIsInfF(0.5F - dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = 0.5F - dt;
  } else if (rtIsInfF(dt)) {
    n = 1;
    anew = 0.0F;
    bnew = 0.5F - dt;
  } else {
    anew = 0.0F;
    ndbl = floor((double)(0.5F - dt) / dt + 0.5);
    apnd = ndbl * dt;
    if (dt > 0.0F) {
      cdiff = apnd - (0.5F - dt);
    } else {
      cdiff = (0.5F - dt) - apnd;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)fabs(0.5F - dt)) {
      ndbl++;
      bnew = 0.5F - dt;
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

  emxInit_real32_T(&h2, 2);
  i0 = h2->size[0] * h2->size[1];
  h2->size[0] = 1;
  h2->size[1] = n;
  emxEnsureCapacity((emxArray__common *)h2, i0, (int)sizeof(float));
  if (n > 0) {
    h2->data[0] = anew;
    if (n > 1) {
      h2->data[n - 1] = bnew;
      i0 = n - 1;
      nm1d2 = i0 / 2;
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

  if (rtIsNaNF(-dt) || rtIsNaNF(dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = dt;
  } else if ((-dt == 0.0F) || (0.5F < dt) || ((dt < 0.5F) && (-dt > 0.0F))) {
    n = 0;
    anew = 0.5F;
    bnew = dt;
  } else if (rtIsInfF(dt)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = dt;
  } else if (rtIsInfF(-dt)) {
    n = 1;
    anew = 0.5F;
    bnew = dt;
  } else {
    anew = 0.5F;
    ndbl = floor((dt - 0.5) / -dt + 0.5);
    apnd = 0.5 + ndbl * -dt;
    if (-dt > 0.0F) {
      cdiff = apnd - dt;
    } else {
      cdiff = dt - apnd;
    }

    absb = fabs(dt);
    if ((0.5 >= absb) || rtIsNaN(absb)) {
      absb = 0.5;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
      ndbl++;
      bnew = dt;
    } else if (cdiff > 0.0) {
      bnew = (float)(0.5 + (ndbl - 1.0) * -dt);
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

  emxInit_real32_T(&y, 2);
  i0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
  if (n > 0) {
    y->data[0] = anew;
    if (n > 1) {
      y->data[n - 1] = bnew;
      i0 = n - 1;
      nm1d2 = i0 / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * -dt;
        y->data[k] = anew + kd;
        y->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * -dt;
        y->data[nm1d2] = anew + kd;
        y->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  emxInit_real32_T(&h1, 2);
  i0 = h1->size[0] * h1->size[1];
  h1->size[0] = 1;
  h1->size[1] = h2->size[1] + y->size[1];
  emxEnsureCapacity((emxArray__common *)h1, i0, (int)sizeof(float));
  nm1d2 = h2->size[1];
  for (i0 = 0; i0 < nm1d2; i0++) {
    h1->data[h1->size[0] * i0] = h2->data[h2->size[0] * i0];
  }

  nm1d2 = y->size[1];
  for (i0 = 0; i0 < nm1d2; i0++) {
    h1->data[h1->size[0] * (i0 + h2->size[1])] = y->data[y->size[0] * i0];
  }

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

  i0 = h2->size[0] * h2->size[1];
  h2->size[0] = 1;
  h2->size[1] = n;
  emxEnsureCapacity((emxArray__common *)h2, i0, (int)sizeof(float));
  if (n > 0) {
    h2->data[0] = anew;
    if (n > 1) {
      h2->data[n - 1] = bnew;
      i0 = n - 1;
      nm1d2 = i0 / 2;
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

  if (!buffer_not_empty) {
    i0 = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = (int)(256.0F + (float)h1->size[1]);
    emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
    nm1d2 = (int)(256.0F + (float)h1->size[1]);
    for (i0 = 0; i0 < nm1d2; i0++) {
      buffer->data[i0] = 0.0F;
    }

    buffer_not_empty = true;
  }

  anew = (float)buffer->size[1] - (float)h1->size[1];
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
    r0->data[r0->size[0] * ((n + k) - i0)] = input[n];
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
  emxInit_real32_T(&fcnOutput, 2);
  switch ((int)option) {
   case 1:
    emxInit_real32_T(&b_dt, 2);
    conv(h1, buffer, fcnOutput);
    i0 = b_dt->size[0] * b_dt->size[1];
    b_dt->size[0] = 1;
    b_dt->size[1] = fcnOutput->size[1];
    emxEnsureCapacity((emxArray__common *)b_dt, i0, (int)sizeof(float));
    nm1d2 = fcnOutput->size[0] * fcnOutput->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      b_dt->data[i0] = dt * fcnOutput->data[i0];
    }

    conv(b_dt, h2, y);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    nm1d2 = y->size[0];
    k = y->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&b_dt);
    for (i0 = 0; i0 < nm1d2; i0++) {
      y->data[i0] *= dt;
    }
    break;

   case 2:
    emxInit_real32_T(&b_dt, 2);
    conv(h2, buffer, fcnOutput);
    i0 = b_dt->size[0] * b_dt->size[1];
    b_dt->size[0] = 1;
    b_dt->size[1] = fcnOutput->size[1];
    emxEnsureCapacity((emxArray__common *)b_dt, i0, (int)sizeof(float));
    nm1d2 = fcnOutput->size[0] * fcnOutput->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      b_dt->data[i0] = dt * fcnOutput->data[i0];
    }

    conv(b_dt, h1, y);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    nm1d2 = y->size[0];
    k = y->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&b_dt);
    for (i0 = 0; i0 < nm1d2; i0++) {
      y->data[i0] *= dt;
    }
    break;

   case 3:
    emxInit_real32_T(&b_dt, 2);
    conv(buffer, h1, fcnOutput);
    i0 = b_dt->size[0] * b_dt->size[1];
    b_dt->size[0] = 1;
    b_dt->size[1] = fcnOutput->size[1];
    emxEnsureCapacity((emxArray__common *)b_dt, i0, (int)sizeof(float));
    nm1d2 = fcnOutput->size[0] * fcnOutput->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      b_dt->data[i0] = dt * fcnOutput->data[i0];
    }

    conv(b_dt, h2, y);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    nm1d2 = y->size[0];
    k = y->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&b_dt);
    for (i0 = 0; i0 < nm1d2; i0++) {
      y->data[i0] *= dt;
    }
    break;

   case 4:
    emxInit_real32_T(&b_dt, 2);
    conv(h1, h2, fcnOutput);
    i0 = b_dt->size[0] * b_dt->size[1];
    b_dt->size[0] = 1;
    b_dt->size[1] = fcnOutput->size[1];
    emxEnsureCapacity((emxArray__common *)b_dt, i0, (int)sizeof(float));
    nm1d2 = fcnOutput->size[0] * fcnOutput->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      b_dt->data[i0] = dt * fcnOutput->data[i0];
    }

    conv(b_dt, buffer, y);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    nm1d2 = y->size[0];
    k = y->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&b_dt);
    for (i0 = 0; i0 < nm1d2; i0++) {
      y->data[i0] *= dt;
    }
    break;

   case 5:
    emxInit_real32_T(&b_dt, 2);
    i0 = b_dt->size[0] * b_dt->size[1];
    b_dt->size[0] = 1;
    b_dt->size[1] = h1->size[1];
    emxEnsureCapacity((emxArray__common *)b_dt, i0, (int)sizeof(float));
    nm1d2 = h1->size[0] * h1->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      b_dt->data[i0] = h1->data[i0] + h2->data[i0];
    }

    conv(buffer, b_dt, y);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    nm1d2 = y->size[0];
    k = y->size[1];
    nm1d2 *= k;
    emxFree_real32_T(&b_dt);
    for (i0 = 0; i0 < nm1d2; i0++) {
      y->data[i0] *= dt;
    }
    break;

   case 6:
    conv(buffer, h1, y);
    conv(buffer, h2, fcnOutput);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    nm1d2 = y->size[0];
    k = y->size[1];
    nm1d2 *= k;
    for (i0 = 0; i0 < nm1d2; i0++) {
      y->data[i0] = dt * y->data[i0] + dt * fcnOutput->data[i0];
    }
    break;

   default:
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(float));
    y->data[0] = 0.0F;
    break;
  }

  emxFree_real32_T(&fcnOutput);
  emxFree_real32_T(&h2);
  emxFree_real32_T(&h1);
  for (i0 = 0; i0 < 256; i0++) {
    output[i0] = y->data[y->size[0] * (256 + i0)];
  }

  emxFree_real32_T(&y);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_4_free(void)
{
  emxFree_real32_T(&buffer);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_4_init(void)
{
  emxInit_real32_T(&buffer, 2);
  buffer_not_empty = false;
}

/*
 * File trailer for L3_4.c
 *
 * [EOF]
 */
