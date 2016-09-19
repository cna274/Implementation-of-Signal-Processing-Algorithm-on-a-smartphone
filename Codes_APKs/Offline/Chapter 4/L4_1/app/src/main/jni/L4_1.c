/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L4_1.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 00:35:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L4_1.h"
#include "sum.h"
#include "L4_1_emxutil.h"
#include "sin.h"
#include "cos.h"
#include "abs.h"
#include "mean.h"
#include "repmat.h"
#include "exp.h"

/* Function Definitions */

/*
 * T = 2;
 *  w = 3;
 *  A = 1;
 * Arguments    : float A
 *                float T
 *                float N
 *                float w
 *                emxArray_real32_T *XT
 *                emxArray_real32_T *x_hat
 *                emxArray_real32_T *an
 *                emxArray_real32_T *bn
 *                float *a0
 *                emxArray_real32_T *error
 *                float *max_error
 *                float *avg_error
 * Return Type  : void
 */
void L4_1(float A, float T, float N, float w, emxArray_real32_T *XT,
          emxArray_real32_T *x_hat, emxArray_real32_T *an, emxArray_real32_T *bn,
          float *a0, emxArray_real32_T *error, float *max_error, float
          *avg_error)
{
  int n;
  float anew;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *t;
  int k;
  int nm1d2;
  float kd;
  emxArray_real32_T *y;
  emxArray_real32_T *vec;
  float c;
  emxArray_real32_T *b_y;
  double absa;
  double absb;
  int varargin_2;
  int i;
  emxArray_real32_T *b_t;
  emxArray_real32_T *c_t;
  int b_n;
  unsigned int b_absb;
  unsigned int b_ndbl;
  unsigned int b_apnd;
  emxArray_real32_T *b_XT;
  emxArray_real32_T *c_XT;
  boolean_T exitg1;
  emxArray_real32_T *d_XT;

  /*  N= 10; */
  if (rtIsNaNF(T)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = T;
  } else if (T < 0.0F) {
    n = 0;
    anew = 0.0F;
    bnew = T;
  } else if (rtIsInfF(T)) {
    n = 1;
    anew = ((real32_T)rtNaN);
    bnew = T;
  } else {
    anew = 0.0F;
    ndbl = floor(T / 0.0010000000474974513 + 0.5);
    apnd = ndbl * 0.0010000000474974513;
    cdiff = apnd - T;
    if (fabs(cdiff) < 2.38418579E-7F * T) {
      ndbl++;
      bnew = T;
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

  emxInit_real32_T(&t, 2);
  k = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = n;
  emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
  if (n > 0) {
    t->data[0] = anew;
    if (n > 1) {
      t->data[n - 1] = bnew;
      k = n - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * 0.001F;
        t->data[k] = anew + kd;
        t->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        t->data[nm1d2] = (anew + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * 0.001F;
        t->data[nm1d2] = anew + kd;
        t->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  emxInit_real32_T(&y, 2);
  emxInit_real32_T(&vec, 2);
  switch ((int)w) {
   case 0:
    c = 6.28318548F * (1.0F / T);
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
    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = vec->size[1] + (int)anew;
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      t->data[t->size[0] * k] = A * vec->data[vec->size[0] * k];
    }

    nm1d2 = (int)anew;
    for (k = 0; k < nm1d2; k++) {
      t->data[t->size[0] * (k + vec->size[1])] = 0.0F;
    }
    break;

   case 1:
    /* Y=A*square(2*pi*f*t); */
    /* plot(Y); */
    /* figure; */
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
    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = b_y->size[1];
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = b_y->size[1];
    for (k = 0; k < nm1d2; k++) {
      t->data[t->size[0] * k] = A * b_y->data[b_y->size[0] * k];
    }

    emxFree_real32_T(&b_y);

    /*  plot(X); */
    /*  figure; */
    /*  square_1 = 0; */
    /*  for i = 1:(1/dt) */
    /*      if mod(i,2)==0 */
    /*          square_1 = [square_1 x]; */
    /*      else */
    /*          square_1 = [square_1 y]; */
    /*      end */
    /*  end */
    /*  X = A.*square_1(1:floor(T*(1/dt))); */
    /* plot(X); figure; */
    break;

   case 2:
    /* Y=A*sawtooth(2*pi*f*t) */
    /* plot(Y, 'r'); hold on; */
    c = 0.002F / T;
    if (rtIsNaNF(-A) || rtIsNaNF(c) || rtIsNaNF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else if ((c == 0.0F) || ((-A < A - 0.001F) && (c < 0.0F)) || ((A - 0.001F <
      -A) && (c > 0.0F))) {
      n = 0;
      anew = -A;
      bnew = A - 0.001F;
    } else if (rtIsInfF(-A) || rtIsInfF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else if (rtIsInfF(c)) {
      n = 1;
      anew = -A;
      bnew = A - 0.001F;
    } else {
      anew = -A;
      ndbl = floor(((double)(A - 0.001F) - (-A)) / c + 0.5);
      apnd = -A + ndbl * c;
      if (c > 0.0F) {
        cdiff = apnd - (A - 0.001F);
      } else {
        cdiff = (A - 0.001F) - apnd;
      }

      absa = fabs(-A);
      absb = fabs(A - 0.001F);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
        ndbl++;
        bnew = A - 0.001F;
      } else if (cdiff > 0.0) {
        bnew = (float)(-A + (ndbl - 1.0) * c);
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
          kd = (float)k * c;
          vec->data[k] = anew + kd;
          vec->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * c;
          vec->data[nm1d2] = anew + kd;
          vec->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = vec->size[1] + 1;
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      t->data[t->size[0] * k] = vec->data[vec->size[0] * k];
    }

    t->data[t->size[0] * vec->size[1]] = -A;

    /* plot(X); */
    /* figure; */
    break;

   case 3:
    /* Y=A*sawtooth(2*pi*f*t, 0.5); */
    /* plot(Y, 'r'); hold on; */
    c = 0.004F / T;
    if (rtIsNaNF(-A) || rtIsNaNF(c) || rtIsNaNF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else if ((c == 0.0F) || ((-A < A - 0.001F) && (c < 0.0F)) || ((A - 0.001F <
      -A) && (c > 0.0F))) {
      n = 0;
      anew = -A;
      bnew = A - 0.001F;
    } else if (rtIsInfF(-A) || rtIsInfF(A - 0.001F)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = A - 0.001F;
    } else if (rtIsInfF(c)) {
      n = 1;
      anew = -A;
      bnew = A - 0.001F;
    } else {
      anew = -A;
      ndbl = floor(((double)(A - 0.001F) - (-A)) / c + 0.5);
      apnd = -A + ndbl * c;
      if (c > 0.0F) {
        cdiff = apnd - (A - 0.001F);
      } else {
        cdiff = (A - 0.001F) - apnd;
      }

      absa = fabs(-A);
      absb = fabs(A - 0.001F);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
        ndbl++;
        bnew = A - 0.001F;
      } else if (cdiff > 0.0) {
        bnew = (float)(-A + (ndbl - 1.0) * c);
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
          kd = (float)k * c;
          vec->data[k] = anew + kd;
          vec->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * c;
          vec->data[nm1d2] = anew + kd;
          vec->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    c = 0.004F / T;
    anew = -(0.004F / T);
    if (rtIsNaNF(A) || rtIsNaNF(anew) || rtIsNaNF(-A)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = -A;
    } else if ((-c == 0.0F) || ((A < -A) && (-c < 0.0F)) || ((-A < A) && (-c >
                 0.0F))) {
      n = 0;
      anew = A;
      bnew = -A;
    } else if (rtIsInfF(A) || rtIsInfF(-A)) {
      n = 1;
      anew = ((real32_T)rtNaN);
      bnew = -A;
    } else if (rtIsInfF(anew)) {
      n = 1;
      anew = A;
      bnew = -A;
    } else {
      anew = A;
      ndbl = floor(((double)-A - A) / -c + 0.5);
      apnd = A + ndbl * -c;
      if (-c > 0.0F) {
        cdiff = apnd - (-A);
      } else {
        cdiff = -A - apnd;
      }

      absa = fabs(A);
      absb = fabs(-A);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)absb) {
        ndbl++;
        bnew = -A;
      } else if (cdiff > 0.0) {
        bnew = (float)(A + (ndbl - 1.0) * -c);
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
          kd = (float)k * -c;
          y->data[k] = anew + kd;
          y->data[(n - k) - 1] = bnew - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (anew + bnew) / 2.0F;
        } else {
          kd = (float)nm1d2 * -c;
          y->data[nm1d2] = anew + kd;
          y->data[nm1d2 + 1] = bnew - kd;
        }
      }
    }

    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = vec->size[1] + y->size[1];
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      t->data[t->size[0] * k] = vec->data[vec->size[0] * k];
    }

    nm1d2 = y->size[1];
    for (k = 0; k < nm1d2; k++) {
      t->data[t->size[0] * (k + vec->size[1])] = y->data[y->size[0] * k];
    }

    /* one tooth in a row */
    /* plot(X); */
    break;

   case 4:
    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = t->size[0];
    k = t->size[1];
    nm1d2 *= k;
    for (k = 0; k < nm1d2; k++) {
      t->data[k] *= -4.0F;
    }

    b_exp(t);
    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = t->size[0];
    k = t->size[1];
    nm1d2 *= k;
    for (k = 0; k < nm1d2; k++) {
      t->data[k] *= A;
    }
    break;

   default:
    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    t->data[0] = 0.0F;
    break;
  }

  repmat(t, XT);

  /* plot(XT); */
  varargin_2 = t->size[1];
  n = t->size[1];
  kd = mean(t);
  *a0 = kd;
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
  emxInit_real32_T(&b_t, 2);
  emxInit_real32_T(&c_t, 2);
  while (i <= (int)N - 1) {
    c = 6.28318548F * ((1.0F + (float)i) / (float)n);
    if (n < 1.0F) {
      b_n = 0;
      bnew = 0.0F;
    } else {
      ndbl = floor(((float)varargin_2 - 1.0) + 0.5);
      apnd = 1.0 + ndbl;
      cdiff = (1.0 + ndbl) - (float)n;
      b_absb = (unsigned int)fabs((float)varargin_2);
      if (1U >= b_absb) {
        b_absb = 1U;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)b_absb) {
        ndbl++;
        bnew = (float)n;
      } else if (cdiff > 0.0) {
        bnew = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        bnew = (float)apnd;
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

    b_cos(vec);
    k = c_t->size[0] * c_t->size[1];
    c_t->size[0] = 1;
    c_t->size[1] = t->size[1];
    emxEnsureCapacity((emxArray__common *)c_t, k, (int)sizeof(float));
    nm1d2 = t->size[0] * t->size[1];
    for (k = 0; k < nm1d2; k++) {
      c_t->data[k] = t->data[k] * vec->data[k];
    }

    anew = sum(c_t);
    an->data[(int)(1.0F + (float)i) - 1] = 2.0F / (float)n * anew;
    c = 6.28318548F * ((1.0F + (float)i) / (float)n);
    if (n < 1.0F) {
      b_n = 0;
      bnew = 0.0F;
    } else {
      ndbl = floor(((float)varargin_2 - 1.0) + 0.5);
      apnd = 1.0 + ndbl;
      cdiff = (1.0 + ndbl) - (float)n;
      b_absb = (unsigned int)fabs((float)varargin_2);
      if (1U >= b_absb) {
        b_absb = 1U;
      }

      if (fabs(cdiff) < 2.38418579E-7F * (float)b_absb) {
        ndbl++;
        bnew = (float)n;
      } else if (cdiff > 0.0) {
        bnew = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        bnew = (float)apnd;
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
    k = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = t->size[1];
    emxEnsureCapacity((emxArray__common *)b_t, k, (int)sizeof(float));
    nm1d2 = t->size[0] * t->size[1];
    for (k = 0; k < nm1d2; k++) {
      b_t->data[k] = t->data[k] * vec->data[k];
    }

    anew = sum(b_t);
    bn->data[(int)(1.0F + (float)i) - 1] = 2.0F / (float)n * anew;
    i++;
  }

  emxFree_real32_T(&c_t);
  emxFree_real32_T(&b_t);
  if (XT->size[1] < 1.0F) {
    b_n = 0;
    bnew = 0.0F;
  } else {
    b_ndbl = (unsigned int)floor(((float)XT->size[1] - 1.0) + 0.5);
    b_apnd = b_ndbl + 1U;
    cdiff = (1.0 + (double)b_ndbl) - (float)XT->size[1];
    b_absb = (unsigned int)(float)XT->size[1];
    if (fabs(cdiff) < 2.38418579E-7F * (float)b_absb) {
      b_ndbl++;
      bnew = (float)XT->size[1];
    } else if (cdiff > 0.0) {
      bnew = (float)(1.0 + ((double)b_ndbl - 1.0));
    } else {
      b_ndbl++;
      bnew = (float)b_apnd;
    }

    b_n = (int)b_ndbl;
  }

  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = b_n;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(float));
  if (b_n > 0) {
    y->data[0] = 1.0F;
    if (b_n > 1) {
      y->data[b_n - 1] = bnew;
      k = b_n - 1;
      nm1d2 = k / 2;
      for (k = 1; k < nm1d2; k++) {
        y->data[k] = 1.0F + (float)k;
        y->data[(b_n - k) - 1] = bnew - (float)k;
      }

      if (nm1d2 << 1 == b_n - 1) {
        y->data[nm1d2] = (1.0F + bnew) / 2.0F;
      } else {
        y->data[nm1d2] = 1.0F + (float)nm1d2;
        y->data[nm1d2 + 1] = bnew - (float)nm1d2;
      }
    }
  }

  k = x_hat->size[0] * x_hat->size[1];
  x_hat->size[0] = 1;
  x_hat->size[1] = (int)(float)XT->size[1];
  emxEnsureCapacity((emxArray__common *)x_hat, k, (int)sizeof(float));
  nm1d2 = (int)(float)XT->size[1];
  for (k = 0; k < nm1d2; k++) {
    x_hat->data[k] = kd;
  }

  for (i = 0; i < (int)N; i++) {
    c = 6.28318548F * ((1.0F + (float)i) / (float)n);
    k = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = y->size[1];
    emxEnsureCapacity((emxArray__common *)t, k, (int)sizeof(float));
    nm1d2 = y->size[0] * y->size[1];
    for (k = 0; k < nm1d2; k++) {
      t->data[k] = c * y->data[k];
    }

    b_cos(t);
    c = 6.28318548F * ((1.0F + (float)i) / (float)n);
    k = vec->size[0] * vec->size[1];
    vec->size[0] = 1;
    vec->size[1] = y->size[1];
    emxEnsureCapacity((emxArray__common *)vec, k, (int)sizeof(float));
    nm1d2 = y->size[0] * y->size[1];
    for (k = 0; k < nm1d2; k++) {
      vec->data[k] = c * y->data[k];
    }

    b_sin(vec);
    k = x_hat->size[0] * x_hat->size[1];
    x_hat->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)x_hat, k, (int)sizeof(float));
    nm1d2 = x_hat->size[0];
    k = x_hat->size[1];
    anew = an->data[(int)(1.0F + (float)i) - 1];
    kd = bn->data[(int)(1.0F + (float)i) - 1];
    nm1d2 *= k;
    for (k = 0; k < nm1d2; k++) {
      x_hat->data[k] = (x_hat->data[k] + anew * t->data[k]) + kd * vec->data[k];
    }
  }

  emxFree_real32_T(&vec);
  emxFree_real32_T(&y);
  emxInit_real32_T(&b_XT, 2);

  /*  stem(an); figure; stem(bn); figure; */
  /*   figure; */
  /*   plot(x_hat,'r');  */
  /*   hold on; plot(XT);  */
  /* figure; plot(X); */
  k = b_XT->size[0] * b_XT->size[1];
  b_XT->size[0] = 1;
  b_XT->size[1] = XT->size[1];
  emxEnsureCapacity((emxArray__common *)b_XT, k, (int)sizeof(float));
  nm1d2 = XT->size[0] * XT->size[1];
  for (k = 0; k < nm1d2; k++) {
    b_XT->data[k] = XT->data[k] - x_hat->data[k];
  }

  emxInit_real32_T(&c_XT, 2);
  b_abs(b_XT, error);
  k = c_XT->size[0] * c_XT->size[1];
  c_XT->size[0] = 1;
  c_XT->size[1] = XT->size[1];
  emxEnsureCapacity((emxArray__common *)c_XT, k, (int)sizeof(float));
  nm1d2 = XT->size[0] * XT->size[1];
  emxFree_real32_T(&b_XT);
  for (k = 0; k < nm1d2; k++) {
    c_XT->data[k] = XT->data[k] - x_hat->data[k];
  }

  b_abs(c_XT, t);
  nm1d2 = 1;
  n = t->size[1];
  anew = t->data[0];
  emxFree_real32_T(&c_XT);
  if (t->size[1] > 1) {
    if (rtIsNaNF(t->data[0])) {
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= n)) {
        nm1d2 = k;
        if (!rtIsNaNF(t->data[k - 1])) {
          anew = t->data[k - 1];
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (nm1d2 < t->size[1]) {
      while (nm1d2 + 1 <= n) {
        if (t->data[nm1d2] > anew) {
          anew = t->data[nm1d2];
        }

        nm1d2++;
      }
    }
  }

  emxInit_real32_T(&d_XT, 2);
  *max_error = anew;
  k = d_XT->size[0] * d_XT->size[1];
  d_XT->size[0] = 1;
  d_XT->size[1] = XT->size[1];
  emxEnsureCapacity((emxArray__common *)d_XT, k, (int)sizeof(float));
  nm1d2 = XT->size[0] * XT->size[1];
  for (k = 0; k < nm1d2; k++) {
    d_XT->data[k] = XT->data[k] - x_hat->data[k];
  }

  b_abs(d_XT, t);
  kd = sum(t);
  *avg_error = kd / (float)XT->size[1];
  emxFree_real32_T(&d_XT);
  emxFree_real32_T(&t);
}

/*
 * File trailer for L4_1.c
 *
 * [EOF]
 */
