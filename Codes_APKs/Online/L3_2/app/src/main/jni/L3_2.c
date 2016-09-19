/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 27-Apr-2016 17:57:54
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_2.h"
#include "L3_2_emxutil.h"

/* Variable Definitions */
static emxArray_real32_T *buffer;
static boolean_T buffer_not_empty;

/* Function Definitions */

/*
 * Arguments    : const float input_data[]
 *                const int input_size[2]
 *                float fs
 *                float frameSize
 *                emxArray_real32_T *output
 * Return Type  : void
 */
void L3_2(const float *input_data, const int input_size[], float fs, float
          frameSize, emxArray_real32_T *output)
{
  emxArray_real32_T *h;
  float Delta;
  float s;
  float c;
  float b_c;
  int i0;
  int jA2;
  int jC;
  emxArray_real32_T *r0;
  int k;
  int nA;
  int nB;
  int nApnB;
  emxArray_real32_T *conv_output;
  emxInit_real32_T(&h, 2);
  Delta = 1.0F / fs;

  /* length(input); */
  s = 0.25F * frameSize;
  c = 0.5F * frameSize;
  b_c = 0.25F * frameSize;
  i0 = h->size[0] * h->size[1];
  h->size[0] = 1;
  h->size[1] = ((int)s + (int)c) + (int)b_c;
  emxEnsureCapacity((emxArray__common *)h, i0, (int)sizeof(float));
  jA2 = (int)s;
  for (i0 = 0; i0 < jA2; i0++) {
    h->data[h->size[0] * i0] = 0.0F;
  }

  jA2 = (int)c;
  for (i0 = 0; i0 < jA2; i0++) {
    h->data[h->size[0] * (i0 + (int)s)] = 1.0F;
  }

  jA2 = (int)b_c;
  for (i0 = 0; i0 < jA2; i0++) {
    h->data[h->size[0] * ((i0 + (int)s) + (int)c)] = 0.0F;
  }

  if (!buffer_not_empty) {
    s = (float)input_size[1] + (float)h->size[1];
    i0 = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = (int)s;
    emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
    jA2 = (int)s;
    for (i0 = 0; i0 < jA2; i0++) {
      buffer->data[i0] = 0.0F;
    }

    buffer_not_empty = !(buffer->size[1] == 0);
  }

  s = (float)buffer->size[1] - (float)h->size[1];
  if (s + 1.0F > buffer->size[1]) {
    i0 = 1;
    jC = 1;
  } else {
    i0 = (int)(s + 1.0F);
    jC = (int)(float)buffer->size[1] + 1;
  }

  emxInit_real32_T(&r0, 2);
  k = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = (jC - i0) + input_size[1];
  emxEnsureCapacity((emxArray__common *)r0, k, (int)sizeof(float));
  jA2 = jC - i0;
  for (k = 0; k < jA2; k++) {
    r0->data[r0->size[0] * k] = buffer->data[buffer->size[0] * ((i0 + k) - 1)];
  }

  jA2 = input_size[1];
  for (k = 0; k < jA2; k++) {
    r0->data[r0->size[0] * ((k + jC) - i0)] = input_data[input_size[0] * k];
  }

  i0 = buffer->size[0] * buffer->size[1];
  buffer->size[0] = 1;
  buffer->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)buffer, i0, (int)sizeof(float));
  jA2 = r0->size[1];
  for (i0 = 0; i0 < jA2; i0++) {
    buffer->data[buffer->size[0] * i0] = r0->data[r0->size[0] * i0];
  }

  emxFree_real32_T(&r0);
  buffer_not_empty = !(buffer->size[1] == 0);
  nA = buffer->size[1];
  nB = h->size[1];
  nApnB = buffer->size[1] + h->size[1];
  if ((buffer->size[1] == 0) || (h->size[1] == 0)) {
  } else {
    nApnB--;
  }

  emxInit_real32_T(&conv_output, 2);
  i0 = conv_output->size[0] * conv_output->size[1];
  conv_output->size[0] = 1;
  conv_output->size[1] = nApnB;
  emxEnsureCapacity((emxArray__common *)conv_output, i0, (int)sizeof(float));
  if ((buffer->size[1] == 0) || (h->size[1] == 0) || (nApnB == 0)) {
    i0 = conv_output->size[0] * conv_output->size[1];
    conv_output->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)conv_output, i0, (int)sizeof(float));
    jA2 = conv_output->size[1];
    for (i0 = 0; i0 < jA2; i0++) {
      conv_output->data[conv_output->size[0] * i0] = 0.0F;
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
        s += buffer->data[k - 1] * h->data[jC - k];
        k++;
      }

      conv_output->data[jC - 1] = s;
    }
  }

  i0 = conv_output->size[0] * conv_output->size[1];
  conv_output->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)conv_output, i0, (int)sizeof(float));
  jA2 = conv_output->size[0];
  jC = conv_output->size[1];
  jA2 *= jC;
  for (i0 = 0; i0 < jA2; i0++) {
    conv_output->data[i0] *= Delta;
  }

  s = (float)h->size[1] + frameSize;
  if ((float)h->size[1] + 1.0F > s) {
    i0 = 0;
    jC = 0;
  } else {
    i0 = (int)((float)h->size[1] + 1.0F) - 1;
    jC = (int)s;
  }

  emxFree_real32_T(&h);
  k = output->size[0] * output->size[1];
  output->size[0] = 1;
  output->size[1] = jC - i0;
  emxEnsureCapacity((emxArray__common *)output, k, (int)sizeof(float));
  jA2 = jC - i0;
  for (jC = 0; jC < jA2; jC++) {
    output->data[output->size[0] * jC] = conv_output->data[conv_output->size[0] *
      (i0 + jC)];
  }

  emxFree_real32_T(&conv_output);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_2_free(void)
{
  emxFree_real32_T(&buffer);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_2_init(void)
{
  emxInit_real32_T(&buffer, 2);
  buffer_not_empty = false;
}

/*
 * File trailer for L3_2.c
 *
 * [EOF]
 */
