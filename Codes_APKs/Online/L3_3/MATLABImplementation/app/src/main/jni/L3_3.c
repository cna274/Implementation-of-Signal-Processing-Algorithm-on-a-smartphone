/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_3.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 27-Apr-2016 23:43:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_3.h"
#include "L3_3_emxutil.h"

/* Variable Definitions */
static emxArray_real32_T *buffer;
static boolean_T buffer_not_empty;

/* Function Definitions */

/*
 * Arguments    : const float input_data[]
 *                const int input_size[2]
 *                float fs
 *                emxArray_real32_T *output
 * Return Type  : void
 */
void L3_3(const float *input_data, const int input_size[], float fs,
          emxArray_real32_T *output)
{
  float delta;
  int ndbuffer;
  float anew;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *x2;
  int i0;
  int nm1d2;
  int k;
  float kd;
  emxArray_real32_T *r0;
  int nb;
  emxArray_real32_T *conv_output;
  int nx;
  emxArray_real32_T *dbuffer;
  delta = 1.0F / fs;

  /* a=0:dt:1; */
  /* b=ones(1,4/dt); */
  /* x1=[a b]; */
  if (rtIsNaNF(delta) || rtIsNaNF(1.0F - delta)) {
    ndbuffer = 1;
    anew = ((real32_T)rtNaN);
    bnew = 1.0F - delta;
  } else if ((delta == 0.0F) || ((0.0F < 1.0F - delta) && (delta < 0.0F)) ||
             ((1.0F - delta < 0.0F) && (delta > 0.0F))) {
    ndbuffer = 0;
    anew = 0.0F;
    bnew = 1.0F - delta;
  } else if (rtIsInfF(1.0F - delta)) {
    ndbuffer = 1;
    anew = ((real32_T)rtNaN);
    bnew = 1.0F - delta;
  } else if (rtIsInfF(delta)) {
    ndbuffer = 1;
    anew = 0.0F;
    bnew = 1.0F - delta;
  } else {
    anew = 0.0F;
    ndbl = floor((double)(1.0F - delta) / delta + 0.5);
    apnd = ndbl * delta;
    if (delta > 0.0F) {
      cdiff = apnd - (1.0F - delta);
    } else {
      cdiff = (1.0F - delta) - apnd;
    }

    if (fabs(cdiff) < 2.38418579E-7F * (float)fabs(1.0F - delta)) {
      ndbl++;
      bnew = 1.0F - delta;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * delta);
    } else {
      ndbl++;
      bnew = (float)apnd;
    }

    if (ndbl >= 0.0) {
      ndbuffer = (int)ndbl;
    } else {
      ndbuffer = 0;
    }
  }

  emxInit_real32_T(&x2, 2);
  i0 = x2->size[0] * x2->size[1];
  x2->size[0] = 1;
  x2->size[1] = ndbuffer;
  emxEnsureCapacity((emxArray__common *)x2, i0, (int)sizeof(float));
  if (ndbuffer > 0) {
    x2->data[0] = anew;
    if (ndbuffer > 1) {
      x2->data[ndbuffer - 1] = bnew;
      i0 = ndbuffer - 1;
      nm1d2 = i0 / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * delta;
        x2->data[k] = anew + kd;
        x2->data[(ndbuffer - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == ndbuffer - 1) {
        x2->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * delta;
        x2->data[nm1d2] = anew + kd;
        x2->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  /* plot(x2); */
  if (!buffer_not_empty) {
    anew = (float)x2->size[1] + (float)input_size[1];
    i0 = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = (int)anew;
    emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
    k = (int)anew;
    for (i0 = 0; i0 < k; i0++) {
      buffer->data[i0] = 0.0F;
    }

    buffer_not_empty = !(buffer->size[1] == 0);
  }

  anew = (float)buffer->size[1] - (float)x2->size[1];
  if (anew + 1.0F > buffer->size[1]) {
    i0 = 1;
    nm1d2 = 1;
  } else {
    i0 = (int)(anew + 1.0F);
    nm1d2 = (int)(float)buffer->size[1] + 1;
  }

  emxInit_real32_T(&r0, 2);
  ndbuffer = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = (nm1d2 - i0) + input_size[1];
  emxEnsureCapacity((emxArray__common *)r0, ndbuffer, (int)sizeof(float));
  k = nm1d2 - i0;
  for (ndbuffer = 0; ndbuffer < k; ndbuffer++) {
    r0->data[r0->size[0] * ndbuffer] = buffer->data[buffer->size[0] * ((i0 +
      ndbuffer) - 1)];
  }

  k = input_size[1];
  for (ndbuffer = 0; ndbuffer < k; ndbuffer++) {
    r0->data[r0->size[0] * ((ndbuffer + nm1d2) - i0)] = input_data[input_size[0]
      * ndbuffer];
  }

  i0 = buffer->size[0] * buffer->size[1];
  buffer->size[0] = 1;
  buffer->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
  k = r0->size[1];
  for (i0 = 0; i0 < k; i0++) {
    buffer->data[buffer->size[0] * i0] = r0->data[r0->size[0] * i0];
  }

  emxFree_real32_T(&r0);
  buffer_not_empty = !(buffer->size[1] == 0);
  nb = x2->size[1];
  if (1 >= x2->size[1]) {
    ndbuffer = 0;
  } else {
    ndbuffer = x2->size[1] - 1;
  }

  emxInit_real32_T(&conv_output, 2);
  i0 = conv_output->size[0] * conv_output->size[1];
  conv_output->size[0] = 1;
  conv_output->size[1] = buffer->size[1];
  emxEnsureCapacity((emxArray__common *)conv_output, i0, (int)sizeof(float));
  nx = buffer->size[1];
  if (buffer->size[1] >= (x2->size[1] << 1)) {
    i0 = conv_output->size[0] * conv_output->size[1];
    conv_output->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)conv_output, i0, (int)sizeof(float));
    k = conv_output->size[1];
    for (i0 = 0; i0 < k; i0++) {
      conv_output->data[conv_output->size[0] * i0] = 0.0F;
    }

    for (k = 1; k <= nb; k++) {
      for (nm1d2 = k; nm1d2 <= nx; nm1d2++) {
        conv_output->data[nm1d2 - 1] += x2->data[k - 1] * buffer->data[nm1d2 - k];
      }
    }
  } else {
    emxInit_real32_T1(&dbuffer, 1);
    i0 = dbuffer->size[0];
    dbuffer->size[0] = ndbuffer + 1;
    emxEnsureCapacity((emxArray__common *)dbuffer, i0, (int)sizeof(float));
    for (k = 1; k <= ndbuffer; k++) {
      dbuffer->data[k] = 0.0F;
    }

    for (nm1d2 = 0; nm1d2 + 1 <= nx; nm1d2++) {
      for (k = 1; k <= ndbuffer; k++) {
        dbuffer->data[k - 1] = dbuffer->data[k];
      }

      dbuffer->data[ndbuffer] = 0.0F;
      for (k = 0; k + 1 <= nb; k++) {
        dbuffer->data[k] += buffer->data[nm1d2] * x2->data[k];
      }

      conv_output->data[nm1d2] = dbuffer->data[0];
    }

    emxFree_real32_T(&dbuffer);
  }

  i0 = conv_output->size[0] * conv_output->size[1];
  conv_output->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)conv_output, i0, (int)sizeof(float));
  nm1d2 = conv_output->size[0];
  ndbuffer = conv_output->size[1];
  k = nm1d2 * ndbuffer;
  for (i0 = 0; i0 < k; i0++) {
    conv_output->data[i0] *= delta;
  }

  if ((float)x2->size[1] + 1.0 > (float)conv_output->size[1]) {
    i0 = 0;
    nm1d2 = 0;
  } else {
    i0 = (int)((float)x2->size[1] + 1.0F) - 1;
    nm1d2 = (int)(float)conv_output->size[1];
  }

  emxFree_real32_T(&x2);
  ndbuffer = output->size[0] * output->size[1];
  output->size[0] = 1;
  output->size[1] = nm1d2 - i0;
  emxEnsureCapacity((emxArray__common *)output, ndbuffer, (int)sizeof(float));
  k = nm1d2 - i0;
  for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
    output->data[output->size[0] * nm1d2] = conv_output->data[conv_output->size
      [0] * (i0 + nm1d2)];
  }

  emxFree_real32_T(&conv_output);

  /* output */
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_3_free(void)
{
  emxFree_real32_T(&buffer);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_3_init(void)
{
  emxInit_real32_T(&buffer, 2);
  buffer_not_empty = false;
}

/*
 * File trailer for L3_3.c
 *
 * [EOF]
 */
