/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L4_2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 22-Apr-2016 14:01:51
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L4_2.h"
#include "sum.h"
#include "L4_2_emxutil.h"
#include "sin.h"
#include "angle.h"
#include "abs.h"

/* Function Definitions */

/*
 * T = 6.28;
 * Arguments    : float A
 *                float T
 *                float N
 *                float w
 *                float R
 *                float C
 *                emxArray_real32_T *XT
 *                emxArray_real32_T *an
 *                emxArray_real32_T *bn
 *                float *a0
 *                float *VCdc
 *                emxArray_real32_T *VCcos_m
 *                emxArray_real32_T *VCcos_a
 *                emxArray_real32_T *VCsin_m
 *                emxArray_real32_T *VCsin_a
 * Return Type  : void
 */
void L4_2(float A, float T, float N, float w, float R, float C,
          emxArray_real32_T *XT, emxArray_real32_T *an, emxArray_real32_T *bn,
          float *a0, float *VCdc, emxArray_real32_T *VCcos_m, emxArray_real32_T *
          VCcos_a, emxArray_real32_T *VCsin_m, emxArray_real32_T *VCsin_a)
{
  float f;
  emxArray_real32_T *X;
  emxArray_real32_T *y;
  emxArray_real32_T *vec;
  float c;
  float bnew;
  int n;
  float anew;
  double ndbl;
  double apnd;
  double cdiff;
  int k;
  int nm1d2;
  float kd;
  emxArray_real32_T *b_y;
  double absa;
  double absb;
  int varargin_2;
  float c_y;
  int i;
  emxArray_real32_T *b_X;
  emxArray_real32_T *c_X;
  int b_n;
  unsigned int b_apnd;
  unsigned int u1;
  emxArray_creal32_T *VCcos;
  emxArray_creal32_T *VCsin;
  float an_re;
  f = 1.0F / T;

  /* R = 1; */
  /* C = 1; */
  /* N = 5; */
  /* w=1; */
  emxInit_real32_T(&X, 2);
  emxInit_real32_T(&y, 2);
  emxInit_real32_T(&vec, 2);
  switch ((int)w) {
   case 0:
    c = 6.28318548F * f;
    bnew = T / 2.0F;
    if (rtIsNaNF(bnew)) {
      n = 1;
      anew = ((real32_T)rtNaN);
    } else if (bnew < 0.0F) {
      n = 0;
      anew = 0.0F;
    } else if (rtIsInfF(bnew)) {
      n = 1;
      anew = ((real32_T)rtNaN);
    } else {
      anew = 0.0F;
      ndbl = floor(bnew / 0.0010000000474974513 + 0.5);
      apnd = ndbl * 0.0010000000474974513;
      cdiff = apnd - bnew;
      if (fabs(cdiff) < 2.38418579E-7F * bnew) {
        ndbl++;
      } else if (cdiff > 0.0) {
        bnew = (float)((ndbl - 1.0) * 0.0010000000474974513);
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
          kd = (float)k * 0.001F;
          vec->data[k] = anew + kd;
          vec->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * 0.001F;
          vec->data[nm1d2] = anew + kd;
          vec->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    k = vec->size[0] * vec->size[1];
    vec->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
    nm1d2 = vec->size[0];
    k = vec->size[1];
    nm1d2 *= k;
    for (k = 0; k < nm1d2; k++) {
      vec->data[k] *= c;
    }

    b_sin(vec);
    anew = (float)floor(T / 0.002F);
    k = X->size[0] * X->size[1];
    X->size[0] = 1;
    X->size[1] = vec->size[1] + (int)anew;
    emxEnsureCapacity((emxArray__common *)X, k, (int)sizeof(float));
    nm1d2 = vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      X->data[X->size[0] * k] = A * vec->data[vec->size[0] * k];
    }

    nm1d2 = (int)anew;
    for (k = 0; k < nm1d2; k++) {
      X->data[X->size[0] * (k + vec->size[1])] = 0.0F;
    }
    break;

   case 1:
    /* X=A*square(2*pi*f*t) */
    /*  plot(X_1,'r');hold on; */
    /* x = zeros(1,1000); */
    anew = (float)floor(T / 2.0F * 999.999939F);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)anew;
    emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
    nm1d2 = (int)anew;
    for (k = 0; k < nm1d2; k++) {
      y->data[k] = 1.0F;
    }

    emxInit_real32_T(&b_y, 2);
    k = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = (y->size[1] + y->size[1]) + 1;
    emxEnsureCapacity((emxArray__common *)b_y, k, (int)sizeof(float));
    nm1d2 = y->size[1];
    for (k = 0; k < nm1d2; k++) {
      b_y->data[b_y->size[0] * k] = -y->data[y->size[0] * k];
    }

    nm1d2 = y->size[1];
    for (k = 0; k < nm1d2; k++) {
      b_y->data[b_y->size[0] * (k + y->size[1])] = y->data[y->size[0] * k];
    }

    b_y->data[b_y->size[0] * (y->size[1] + y->size[1])] = -1.0F;
    k = X->size[0] * X->size[1];
    X->size[0] = 1;
    X->size[1] = b_y->size[1];
    emxEnsureCapacity((emxArray__common *)X, k, (int)sizeof(float));
    nm1d2 = b_y->size[1];
    for (k = 0; k < nm1d2; k++) {
      X->data[X->size[0] * k] = A * b_y->data[b_y->size[0] * k];
    }

    emxFree_real32_T(&b_y);
    break;

   case 2:
    /* X=A*sawtooth(2*pi*f*t) */
    if (rtIsNaNF(-A) || rtIsNaNF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else if (A - 0.001F < -A) {
      n = 0;
      anew = -A;
      bnew = A - 0.001F;
    } else if (rtIsInfF(-A) || rtIsInfF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else {
      anew = -A;
      ndbl = floor(((double)(A - 0.001F) - (-A)) / 0.0010000000474974513 + 0.5);
      apnd = -A + ndbl * 0.0010000000474974513;
      cdiff = apnd - (A - 0.001F);
      absa = fabs(-A);
      absb = fabs(A - 0.001F);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
        ndbl++;
        bnew = A - 0.001F;
      } else if (cdiff > 0.0) {
        bnew = (float)(-A + (ndbl - 1.0) * 0.0010000000474974513);
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
          kd = (float)k * 0.001F;
          vec->data[k] = anew + kd;
          vec->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * 0.001F;
          vec->data[nm1d2] = anew + kd;
          vec->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    k = X->size[0] * X->size[1];
    X->size[0] = 1;
    X->size[1] = vec->size[1] + 1;
    emxEnsureCapacity((emxArray__common *)X, k, (int)sizeof(float));
    nm1d2 = vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      X->data[X->size[0] * k] = vec->data[vec->size[0] * k];
    }

    X->data[X->size[0] * vec->size[1]] = -A;
    break;

   case 3:
    /* X=A*sawtooth(2*pi*f*t, 0.5) */
    if (rtIsNaNF(-A) || rtIsNaNF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else if (A - 0.001F < -A) {
      n = 0;
      anew = -A;
      bnew = A - 0.001F;
    } else if (rtIsInfF(-A) || rtIsInfF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else {
      anew = -A;
      ndbl = floor(((double)(A - 0.001F) - (-A)) / 0.0020000000949949026 + 0.5);
      apnd = -A + ndbl * 0.0020000000949949026;
      cdiff = apnd - (A - 0.001F);
      absa = fabs(-A);
      absb = fabs(A - 0.001F);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
        ndbl++;
        bnew = A - 0.001F;
      } else if (cdiff > 0.0) {
        bnew = (float)(-A + (ndbl - 1.0) * 0.0020000000949949026);
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
          kd = (float)k * 0.002F;
          vec->data[k] = anew + kd;
          vec->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * 0.002F;
          vec->data[nm1d2] = anew + kd;
          vec->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    if (rtIsNaNF(A) || rtIsNaNF(-A)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = -A;
    } else if (A < -A) {
      n = 0;
      anew = A;
      bnew = -A;
    } else if (rtIsInfF(A) || rtIsInfF(-A)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = -A;
    } else {
      anew = A;
      ndbl = floor(((double)-A - A) / -0.0020000000949949026 + 0.5);
      apnd = A + ndbl * -0.0020000000949949026;
      cdiff = -A - apnd;
      absa = fabs(A);
      absb = fabs(-A);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
        ndbl++;
        bnew = -A;
      } else if (cdiff > 0.0) {
        bnew = (float)(A + (ndbl - 1.0) * -0.0020000000949949026);
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

    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
    if (n > 0) {
      y->data[0] = anew;
      if (n > 1) {
        y->data[n - 1] = bnew;
        k = n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          kd = (float)k * -0.002F;
          y->data[k] = anew + kd;
          y->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * -0.002F;
          y->data[nm1d2] = anew + kd;
          y->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    k = X->size[0] * X->size[1];
    X->size[0] = 1;
    X->size[1] = vec->size[1] + y->size[1];
    emxEnsureCapacity((emxArray__common *)X, k, (int)sizeof(float));
    nm1d2 = vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      X->data[X->size[0] * k] = vec->data[vec->size[0] * k];
    }

    nm1d2 = y->size[1];
    for (k = 0; k < nm1d2; k++) {
      X->data[X->size[0] * (k + vec->size[1])] = y->data[y->size[0] * k];
    }

    /* plot(X); figure; */
    break;

   default:
    k = X->size[0] * X->size[1];
    X->size[0] = 1;
    X->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)X, k, (int)sizeof(float));
    X->data[0] = 0.0F;
    break;
  }

  k = XT->size[0] * XT->size[1];
  XT->size[0] = 1;
  XT->size[1] = (X->size[1] + X->size[1]) + X->size[1];
  emxEnsureCapacity((emxArray__common *)XT, k, (int)sizeof(float));
  nm1d2 = X->size[1];
  for (k = 0; k < nm1d2; k++) {
    XT->data[XT->size[0] * k] = X->data[X->size[0] * k];
  }

  nm1d2 = X->size[1];
  for (k = 0; k < nm1d2; k++) {
    XT->data[XT->size[0] * (k + X->size[1])] = X->data[X->size[0] * k];
  }

  nm1d2 = X->size[1];
  for (k = 0; k < nm1d2; k++) {
    XT->data[XT->size[0] * ((k + X->size[1]) + X->size[1])] = X->data[X->size[0]
      * k];
  }

  varargin_2 = X->size[1];
  n = X->size[1];
  if (X->size[1] == 0) {
    c_y = 0.0F;
  } else {
    c_y = X->data[0];
    for (k = 2; k <= X->size[1]; k++) {
      c_y += X->data[k - 1];
    }
  }

  c_y /= (float)X->size[1];
  *a0 = c_y;
  k = an->size[0] * an->size[1];
  an->size[0] = 1;
  an->size[1] = (int)N;
  emxEnsureCapacity((emxArray__common *)an, k, (int)sizeof(float));
  nm1d2 = (int)N;
  for (k = 0; k < nm1d2; k++) {
    an->data[k] = 0.0F;
  }

  k = bn->size[0] * bn->size[1];
  bn->size[0] = 1;
  bn->size[1] = (int)N;
  emxEnsureCapacity((emxArray__common *)bn, k, (int)sizeof(float));
  nm1d2 = (int)N;
  for (k = 0; k < nm1d2; k++) {
    bn->data[k] = 0.0F;
  }

  i = 0;
  emxInit_real32_T(&b_X, 2);
  emxInit_real32_T(&c_X, 2);
  while (i <= (int)N - 1) {
    c = 6.28318548F * ((1.0F + (float)i) / (float)n);
    if (n < 1.0F) {
      b_n = 0;
      bnew = 0.0F;
    } else {
      ndbl = floor(((float)varargin_2 - 1.0) + 0.5);
      b_apnd = (unsigned int)(1.0 + ndbl);
      cdiff = (1.0 + ndbl) - (float)n;
      u1 = (unsigned int)(float)varargin_2;
      if (1U >= u1) {
        u1 = 1U;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)u1) {
        ndbl++;
        bnew = (float)n;
      } else if (cdiff > 0.0) {
        bnew = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        bnew = (float)b_apnd;
      }

      b_n = (int)ndbl;
    }

    k = vec->size[0] * vec->size[1];
    vec->size[0] = 1;
    vec->size[1] = b_n;
    emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
    if (b_n > 0) {
      vec->data[0] = 1.0F;
      if (b_n > 1) {
        vec->data[b_n - 1] = bnew;
        k = b_n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          vec->data[k] = 1.0F + (float)k;
          vec->data[(b_n - k) - 1] = bnew - (float)k;
        }

        if (nm1d2 << 1 == b_n - 1) {
          vec->data[nm1d2] = (1.0F + bnew) / 2.0F;
        } else {
          vec->data[nm1d2] = 1.0F + (float)nm1d2;
          vec->data[nm1d2 + 1] = bnew - (float)nm1d2;
        }
      }
    }

    k = vec->size[0] * vec->size[1];
    vec->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
    nm1d2 = vec->size[0];
    k = vec->size[1];
    nm1d2 *= k;
    for (k = 0; k < nm1d2; k++) {
      vec->data[k] *= c;
    }

    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = vec->size[1];
    emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
    nm1d2 = vec->size[0] * vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      y->data[k] = vec->data[k];
    }

    for (k = 0; k + 1 <= vec->size[1]; k++) {
      y->data[k] = (float)cos(y->data[k]);
    }

    k = c_X->size[0] * c_X->size[1];
    c_X->size[0] = 1;
    c_X->size[1] = X->size[1];
    emxEnsureCapacity((emxArray__common *)c_X, k, (int)sizeof(float));
    nm1d2 = X->size[0] * X->size[1];
    for (k = 0; k < nm1d2; k++) {
      c_X->data[k] = X->data[k] * y->data[k];
    }

    anew = sum(c_X);
    an->data[(int)(1.0F + (float)i) - 1] = 2.0F / (float)n * anew;
    c = 6.28318548F * ((1.0F + (float)i) / (float)n);
    if (n < 1.0F) {
      b_n = 0;
      bnew = 0.0F;
    } else {
      ndbl = floor(((float)varargin_2 - 1.0) + 0.5);
      b_apnd = (unsigned int)(1.0 + ndbl);
      cdiff = (1.0 + ndbl) - (float)n;
      u1 = (unsigned int)(float)varargin_2;
      if (1U >= u1) {
        u1 = 1U;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)u1) {
        ndbl++;
        bnew = (float)n;
      } else if (cdiff > 0.0) {
        bnew = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        bnew = (float)b_apnd;
      }

      b_n = (int)ndbl;
    }

    k = vec->size[0] * vec->size[1];
    vec->size[0] = 1;
    vec->size[1] = b_n;
    emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
    if (b_n > 0) {
      vec->data[0] = 1.0F;
      if (b_n > 1) {
        vec->data[b_n - 1] = bnew;
        k = b_n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          vec->data[k] = 1.0F + (float)k;
          vec->data[(b_n - k) - 1] = bnew - (float)k;
        }

        if (nm1d2 << 1 == b_n - 1) {
          vec->data[nm1d2] = (1.0F + bnew) / 2.0F;
        } else {
          vec->data[nm1d2] = 1.0F + (float)nm1d2;
          vec->data[nm1d2 + 1] = bnew - (float)nm1d2;
        }
      }
    }

    k = vec->size[0] * vec->size[1];
    vec->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
    nm1d2 = vec->size[0];
    k = vec->size[1];
    nm1d2 *= k;
    for (k = 0; k < nm1d2; k++) {
      vec->data[k] *= c;
    }

    b_sin(vec);
    k = b_X->size[0] * b_X->size[1];
    b_X->size[0] = 1;
    b_X->size[1] = X->size[1];
    emxEnsureCapacity((emxArray__common *)b_X, k, (int)sizeof(float));
    nm1d2 = X->size[0] * X->size[1];
    for (k = 0; k < nm1d2; k++) {
      b_X->data[k] = X->data[k] * vec->data[k];
    }

    anew = sum(b_X);
    bn->data[(int)(1.0F + (float)i) - 1] = 2.0F / (float)n * anew;
    i++;
  }

  emxFree_real32_T(&c_X);
  emxFree_real32_T(&b_X);
  emxFree_real32_T(&vec);
  emxFree_real32_T(&y);
  emxFree_real32_T(&X);
  emxInit_creal32_T(&VCcos, 2);

  /* stem(an); figure; stem(bn);figure; */
  /* j = sqrt(-1); */
  k = VCcos->size[0] * VCcos->size[1];
  VCcos->size[0] = 1;
  VCcos->size[1] = (int)N;
  emxEnsureCapacity((emxArray__common *)VCcos, k, (int)sizeof(creal32_T));
  nm1d2 = (int)N;
  for (k = 0; k < nm1d2; k++) {
    VCcos->data[k].re = 0.0F;
    VCcos->data[k].im = 0.0F;
  }

  emxInit_creal32_T(&VCsin, 2);
  k = VCsin->size[0] * VCsin->size[1];
  VCsin->size[0] = 1;
  VCsin->size[1] = (int)N;
  emxEnsureCapacity((emxArray__common *)VCsin, k, (int)sizeof(creal32_T));
  nm1d2 = (int)N;
  for (k = 0; k < nm1d2; k++) {
    VCsin->data[k].re = 0.0F;
    VCsin->data[k].im = 0.0F;
  }

  for (i = 0; i < (int)N; i++) {
    an_re = an->data[(int)(1.0F + (float)i) - 1];
    kd = 1.0F + R * (f * (3.14159274F * (2.0F * ((1.0F + (float)i) * 0.0F)))) *
      C;
    bnew = R * (f * (3.14159274F * (2.0F * (1.0F + (float)i)))) * C;
    if (bnew == 0.0F) {
      VCcos->data[(int)(1.0F + (float)i) - 1].re = an_re / kd;
      VCcos->data[(int)(1.0F + (float)i) - 1].im = 0.0F;
    } else {
      anew = (float)fabs(bnew);
      if (kd > anew) {
        c = bnew / kd;
        anew = kd + c * bnew;
        VCcos->data[(int)(1.0F + (float)i) - 1].re = (an_re + c * 0.0F) / anew;
        VCcos->data[(int)(1.0F + (float)i) - 1].im = (0.0F - c * an_re) / anew;
      } else if (anew == kd) {
        if (kd > 0.0F) {
          kd = 0.5F;
        } else {
          kd = -0.5F;
        }

        if (bnew > 0.0F) {
          anew = 0.5F;
        } else {
          anew = -0.5F;
        }

        VCcos->data[(int)(1.0F + (float)i) - 1].re = an_re * kd + 0.0F * anew;
        VCcos->data[(int)(1.0F + (float)i) - 1].im = 0.0F * kd - an_re * anew;
      } else {
        c = kd / bnew;
        anew = bnew + c * kd;
        VCcos->data[(int)(1.0F + (float)i) - 1].re = c * an_re / anew;
        VCcos->data[(int)(1.0F + (float)i) - 1].im = (c * 0.0F - an_re) / anew;
      }
    }

    an_re = bn->data[(int)(1.0F + (float)i) - 1];
    kd = 1.0F + R * (f * (3.14159274F * (2.0F * ((1.0F + (float)i) * 0.0F)))) *
      C;
    bnew = R * (f * (3.14159274F * (2.0F * (1.0F + (float)i)))) * C;
    if (bnew == 0.0F) {
      VCsin->data[(int)(1.0F + (float)i) - 1].re = an_re / kd;
      VCsin->data[(int)(1.0F + (float)i) - 1].im = 0.0F;
    } else {
      anew = (float)fabs(bnew);
      if (kd > anew) {
        c = bnew / kd;
        anew = kd + c * bnew;
        VCsin->data[(int)(1.0F + (float)i) - 1].re = (an_re + c * 0.0F) / anew;
        VCsin->data[(int)(1.0F + (float)i) - 1].im = (0.0F - c * an_re) / anew;
      } else if (anew == kd) {
        if (kd > 0.0F) {
          kd = 0.5F;
        } else {
          kd = -0.5F;
        }

        if (bnew > 0.0F) {
          anew = 0.5F;
        } else {
          anew = -0.5F;
        }

        VCsin->data[(int)(1.0F + (float)i) - 1].re = an_re * kd + 0.0F * anew;
        VCsin->data[(int)(1.0F + (float)i) - 1].im = 0.0F * kd - an_re * anew;
      } else {
        c = kd / bnew;
        anew = bnew + c * kd;
        VCsin->data[(int)(1.0F + (float)i) - 1].re = c * an_re / anew;
        VCsin->data[(int)(1.0F + (float)i) - 1].im = (c * 0.0F - an_re) / anew;
      }
    }
  }

  *VCdc = c_y;
  b_abs(VCcos, VCcos_m);
  angle(VCcos, VCcos_a);
  k = VCcos_a->size[0] * VCcos_a->size[1];
  VCcos_a->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)VCcos_a, k, (int)sizeof(float));
  nm1d2 = VCcos_a->size[0];
  k = VCcos_a->size[1];
  nm1d2 *= k;
  emxFree_creal32_T(&VCcos);
  for (k = 0; k < nm1d2; k++) {
    VCcos_a->data[k] = VCcos_a->data[k] * 180.0F / 3.14159274F;
  }

  b_abs(VCsin, VCsin_m);
  angle(VCsin, VCsin_a);
  k = VCsin_a->size[0] * VCsin_a->size[1];
  VCsin_a->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)VCsin_a, k, (int)sizeof(float));
  nm1d2 = VCsin_a->size[0];
  k = VCsin_a->size[1];
  nm1d2 *= k;
  emxFree_creal32_T(&VCsin);
  for (k = 0; k < nm1d2; k++) {
    VCsin_a->data[k] = VCsin_a->data[k] * 180.0F / 3.14159274F;
  }

  /*  plot(VCcos_m); figure; */
  /*  plot(VCcos_a); figure; */
  /*  plot(VCsin_m); figure; */
  /*  plot(VCsin_a); */
}

/*
 * File trailer for L4_2.c
 *
 * [EOF]
 */
