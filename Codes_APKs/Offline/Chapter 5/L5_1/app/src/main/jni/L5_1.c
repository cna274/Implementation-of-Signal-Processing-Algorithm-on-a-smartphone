/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L5_1.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Apr-2016 15:44:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_1.h"
#include "L5_1_emxutil.h"
#include "angle.h"
#include "abs.h"
#include "ipermute.h"
#include "fftshift.h"
#include "fft.h"
#include "conv.h"
#include "exp.h"
#include "rdivide.h"
#include "L5_1_rtwutil.h"

/* Function Declarations */
static void b_eml_fft(const emxArray_creal32_T *x, int n, emxArray_creal32_T *y);
static float rt_powf_snf(float u0, float u1);

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal32_T *x
 *                int n
 *                emxArray_creal32_T *y
 * Return Type  : void
 */
static void b_eml_fft(const emxArray_creal32_T *x, int n, emxArray_creal32_T *y)
{
  int ju;
  int nd2;
  int minval;
  int ixDelta;
  emxArray_real32_T *costab1q;
  int nRowsD2;
  int nRowsD4;
  int lastChan;
  float e;
  int k;
  emxArray_real32_T *costab;
  emxArray_real32_T *sintab;
  int b_n;
  int ix;
  int chanStart;
  int i;
  boolean_T tst;
  float temp_re;
  float temp_im;
  int ihi;
  int istart;
  int j;
  float twid_im;
  ju = y->size[0];
  y->size[0] = n;
  emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal32_T));
  if (n > x->size[0]) {
    nd2 = y->size[0];
    ju = y->size[0];
    y->size[0] = nd2;
    emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal32_T));
    for (ju = 0; ju < nd2; ju++) {
      y->data[ju].re = 0.0F;
      y->data[ju].im = 0.0F;
    }
  }

  if (x->size[0] == 0) {
  } else {
    if (x->size[0] <= n) {
      minval = x->size[0];
    } else {
      minval = n;
    }

    nd2 = (x->size[0] - minval) + 1;
    if (1 >= nd2) {
      ixDelta = 1;
    } else {
      ixDelta = nd2;
    }

    emxInit_real32_T(&costab1q, 2);
    nRowsD2 = n / 2;
    nRowsD4 = nRowsD2 / 2;
    lastChan = n * (div_s32(x->size[0], x->size[0]) - 1);
    e = 6.28318548F / (float)n;
    ju = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = nRowsD4 + 1;
    emxEnsureCapacity((emxArray__common *)costab1q, ju, (int)sizeof(float));
    costab1q->data[0] = 1.0F;
    nd2 = nRowsD4 / 2;
    for (k = 1; k <= nd2; k++) {
      costab1q->data[k] = (float)cos(e * (float)k);
    }

    for (k = nd2 + 1; k < nRowsD4; k++) {
      costab1q->data[k] = (float)sin(e * (float)(nRowsD4 - k));
    }

    emxInit_real32_T(&costab, 2);
    emxInit_real32_T(&sintab, 2);
    costab1q->data[nRowsD4] = 0.0F;
    b_n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    ju = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity((emxArray__common *)costab, ju, (int)sizeof(float));
    ju = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity((emxArray__common *)sintab, ju, (int)sizeof(float));
    costab->data[0] = 1.0F;
    sintab->data[0] = 0.0F;
    for (k = 1; k <= b_n; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = costab1q->data[b_n - k];
    }

    for (k = costab1q->size[1]; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = costab1q->data[k - b_n];
    }

    emxFree_real32_T(&costab1q);
    ix = 0;
    chanStart = 0;
    while ((n > 0) && (chanStart <= lastChan)) {
      ju = 0;
      nd2 = chanStart;
      for (i = 1; i < minval; i++) {
        y->data[nd2] = x->data[ix];
        b_n = n;
        tst = true;
        while (tst) {
          b_n >>= 1;
          ju ^= b_n;
          tst = ((ju & b_n) == 0);
        }

        nd2 = chanStart + ju;
        ix++;
      }

      y->data[nd2] = x->data[ix];
      ix += ixDelta;
      nd2 = (chanStart + n) - 2;
      if (n > 1) {
        for (i = chanStart; i <= nd2; i += 2) {
          temp_re = y->data[i + 1].re;
          temp_im = y->data[i + 1].im;
          y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
          y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }
      }

      nd2 = 2;
      ju = 4;
      k = nRowsD4;
      b_n = 1 + ((nRowsD4 - 1) << 2);
      while (k > 0) {
        i = chanStart;
        ihi = chanStart + b_n;
        while (i < ihi) {
          temp_re = y->data[i + nd2].re;
          temp_im = y->data[i + nd2].im;
          y->data[i + nd2].re = y->data[i].re - temp_re;
          y->data[i + nd2].im = y->data[i].im - temp_im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
          i += ju;
        }

        istart = chanStart + 1;
        for (j = k; j < nRowsD2; j += k) {
          e = costab->data[j];
          twid_im = sintab->data[j];
          i = istart;
          ihi = istart + b_n;
          while (i < ihi) {
            temp_re = e * y->data[i + nd2].re - twid_im * y->data[i + nd2].im;
            temp_im = e * y->data[i + nd2].im + twid_im * y->data[i + nd2].re;
            y->data[i + nd2].re = y->data[i].re - temp_re;
            y->data[i + nd2].im = y->data[i].im - temp_im;
            y->data[i].re += temp_re;
            y->data[i].im += temp_im;
            i += ju;
          }

          istart++;
        }

        k /= 2;
        nd2 = ju;
        ju <<= 1;
        b_n -= nd2;
      }

      chanStart += n;
    }

    emxFree_real32_T(&sintab);
    emxFree_real32_T(&costab);
    if (y->size[0] > 1) {
      e = 1.0F / (float)y->size[0];
      ju = y->size[0];
      emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal32_T));
      nd2 = y->size[0];
      for (ju = 0; ju < nd2; ju++) {
        y->data[ju].re *= e;
        y->data[ju].im *= e;
      }
    }
  }
}

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_powf_snf(float u0, float u1)
{
  float y;
  float f0;
  float f1;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = ((real32_T)rtNaN);
  } else {
    f0 = (float)fabs(u0);
    f1 = (float)fabs(u1);
    if (rtIsInfF(u1)) {
      if (f0 == 1.0F) {
        y = ((real32_T)rtNaN);
      } else if (f0 > 1.0F) {
        if (u1 > 0.0F) {
          y = ((real32_T)rtInf);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = ((real32_T)rtInf);
      }
    } else if (f1 == 0.0F) {
      y = 1.0F;
    } else if (f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (float)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (float)floor(u1))) {
      y = ((real32_T)rtNaN);
    } else {
      y = (float)pow(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : float a
 *                float a1
 *                float a2
 *                float del1
 *                float del2
 *                float d1
 *                float d2
 *                float mode1
 *                float mode2
 *                float mode3
 *                float mode4
 *                emxArray_real32_T *x1
 *                emxArray_real32_T *x2
 *                emxArray_real32_T *x
 *                emxArray_real32_T *x3
 *                emxArray_real32_T *y1_mag
 *                emxArray_real32_T *y1_phase
 *                emxArray_real32_T *y2_mag
 *                emxArray_real32_T *y2_phase
 *                emxArray_real32_T *y3_mag
 *                emxArray_real32_T *y3_phase
 *                emxArray_real32_T *y_mag
 *                emxArray_real32_T *y_phase
 * Return Type  : void
 */
void L5_1(float a, float a1, float a2, float del1, float del2, float d1, float
          d2, float mode1, float mode2, float mode3, float mode4,
          emxArray_real32_T *x1, emxArray_real32_T *x2, emxArray_real32_T *x,
          emxArray_real32_T *x3, emxArray_real32_T *y1_mag, emxArray_real32_T
          *y1_phase, emxArray_real32_T *y2_mag, emxArray_real32_T *y2_phase,
          emxArray_real32_T *y3_mag, emxArray_real32_T *y3_phase,
          emxArray_real32_T *y_mag, emxArray_real32_T *y_phase)
{
  emxArray_creal32_T *y3;
  emxArray_real32_T *a11;
  int k;
  float b_x;
  float c_x;
  float d_x;
  float absn;
  int nm1d2;
  emxArray_real32_T *a12;
  float c;
  emxArray_real32_T *a21;
  emxArray_real32_T *a22;
  emxArray_real32_T *vec;
  emxArray_real32_T *fcnOutput;
  int n;
  float s_im;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real32_T *b_vec;
  emxArray_real32_T *c_vec;
  int nA;
  int nB;
  emxArray_creal32_T *b_y1;
  int nApnB;
  emxArray_creal32_T *y2;
  int eint;
  emxArray_creal32_T *y;
  emxArray_creal32_T *C;
  emxArray_creal32_T *b_C;
  emxArray_creal32_T *c_y1;
  emxArray_creal32_T *e_x;
  emxInit_creal32_T(&y3, 2);
  emxInit_real32_T(&a11, 2);
  k = x1->size[0] * x1->size[1];
  x1->size[0] = 1;
  x1->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)x1, k, (int)sizeof(float));
  x1->data[0] = 0.0F;
  k = x2->size[0] * x2->size[1];
  x2->size[0] = 1;
  x2->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)x2, k, (int)sizeof(float));
  x2->data[0] = 0.0F;
  k = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)x, k, (int)sizeof(float));
  x->data[0] = 0.0F;
  k = y3->size[0] * y3->size[1];
  y3->size[0] = 1;
  y3->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)y3, k, (int)sizeof(creal32_T));
  y3->data[0].re = 0.0F;
  y3->data[0].im = 0.0F;
  b_x = (float)floor(1.0F / (a * 0.001F));
  c_x = (float)floor(del1 / 0.001F);
  d_x = (float)floor(del2 / 0.001F);
  absn = (float)floor(d1 / 0.001F);
  k = a11->size[0] * a11->size[1];
  a11->size[0] = 1;
  a11->size[1] = (int)absn;
  emxEnsureCapacity((emxArray__common *)a11, k, (int)sizeof(float));
  nm1d2 = (int)absn;
  for (k = 0; k < nm1d2; k++) {
    a11->data[k] = 0.0F;
  }

  emxInit_real32_T(&a12, 2);
  c = b_x - c_x;
  k = a12->size[0] * a12->size[1];
  a12->size[0] = 1;
  a12->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)a12, k, (int)sizeof(float));
  nm1d2 = (int)c;
  for (k = 0; k < nm1d2; k++) {
    a12->data[k] = 0.0F;
  }

  emxInit_real32_T(&a21, 2);
  absn = (float)floor(d2 / 0.001F);
  k = a21->size[0] * a21->size[1];
  a21->size[0] = 1;
  a21->size[1] = (int)absn;
  emxEnsureCapacity((emxArray__common *)a21, k, (int)sizeof(float));
  nm1d2 = (int)absn;
  for (k = 0; k < nm1d2; k++) {
    a21->data[k] = 0.0F;
  }

  emxInit_real32_T(&a22, 2);
  c = b_x - d_x;
  k = a22->size[0] * a22->size[1];
  a22->size[0] = 1;
  a22->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)a22, k, (int)sizeof(float));
  nm1d2 = (int)c;
  for (k = 0; k < nm1d2; k++) {
    a22->data[k] = 0.0F;
  }

  emxInit_real32_T(&vec, 2);
  emxInit_real32_T(&fcnOutput, 2);
  switch ((int)mode3) {
   case 0:
    k = x1->size[0] * x1->size[1];
    x1->size[0] = 1;
    x1->size[1] = (a11->size[1] + (int)c_x) + a12->size[1];
    emxEnsureCapacity((emxArray__common *)x1, k, (int)sizeof(float));
    nm1d2 = a11->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * k] = a11->data[a11->size[0] * k];
    }

    nm1d2 = (int)c_x;
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * (k + a11->size[1])] = 1.0F;
    }

    nm1d2 = a12->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * ((k + a11->size[1]) + (int)c_x)] = a12->data
        [a12->size[0] * k];
    }
    break;

   case 1:
    if (rtIsNaNF(c_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = c_x;
    } else if (c_x < 1.0F) {
      n = 0;
      absn = 1.0F;
      s_im = c_x;
    } else if (rtIsInfF(c_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = c_x;
    } else {
      absn = 1.0F;
      ndbl = floor((c_x - 1.0) + 0.5);
      apnd = 1.0 + ndbl;
      cdiff = (1.0 + ndbl) - c_x;
      if (fabs(cdiff) < 2.38418579E-7F * c_x) {
        ndbl++;
        s_im = c_x;
      } else if (cdiff > 0.0) {
        s_im = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        s_im = (float)apnd;
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
      vec->data[0] = absn;
      if (n > 1) {
        vec->data[n - 1] = s_im;
        k = n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          vec->data[k] = absn + (float)k;
          vec->data[(n - k) - 1] = s_im - (float)k;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (absn + s_im) / 2.0F;
        } else {
          vec->data[nm1d2] = absn + (float)nm1d2;
          vec->data[nm1d2 + 1] = s_im - (float)nm1d2;
        }
      }
    }

    rdivide(vec, c_x, fcnOutput);
    k = x1->size[0] * x1->size[1];
    x1->size[0] = 1;
    x1->size[1] = (a11->size[1] + fcnOutput->size[1]) + a12->size[1];
    emxEnsureCapacity((emxArray__common *)x1, k, (int)sizeof(float));
    nm1d2 = a11->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * k] = a11->data[a11->size[0] * k];
    }

    nm1d2 = fcnOutput->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * (k + a11->size[1])] = fcnOutput->data
        [fcnOutput->size[0] * k];
    }

    nm1d2 = a12->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * ((k + a11->size[1]) + fcnOutput->size[1])] =
        a12->data[a12->size[0] * k];
    }
    break;

   case 2:
    if (rtIsNaNF(c_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = c_x;
    } else if (c_x < 1.0F) {
      n = 0;
      absn = 1.0F;
      s_im = c_x;
    } else if (rtIsInfF(c_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = c_x;
    } else {
      absn = 1.0F;
      ndbl = floor((c_x - 1.0) + 0.5);
      apnd = 1.0 + ndbl;
      cdiff = (1.0 + ndbl) - c_x;
      if (fabs(cdiff) < 2.38418579E-7F * c_x) {
        ndbl++;
        s_im = c_x;
      } else if (cdiff > 0.0) {
        s_im = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        s_im = (float)apnd;
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
      vec->data[0] = absn;
      if (n > 1) {
        vec->data[n - 1] = s_im;
        k = n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          vec->data[k] = absn + (float)k;
          vec->data[(n - k) - 1] = s_im - (float)k;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (absn + s_im) / 2.0F;
        } else {
          vec->data[nm1d2] = absn + (float)nm1d2;
          vec->data[nm1d2 + 1] = s_im - (float)nm1d2;
        }
      }
    }

    emxInit_real32_T(&b_vec, 2);
    k = b_vec->size[0] * b_vec->size[1];
    b_vec->size[0] = 1;
    b_vec->size[1] = vec->size[1];
    emxEnsureCapacity((emxArray__common *)b_vec, k, (int)sizeof(float));
    nm1d2 = vec->size[0] * vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      b_vec->data[k] = -vec->data[k];
    }

    rdivide(b_vec, c_x, fcnOutput);
    b_exp(fcnOutput);
    k = x1->size[0] * x1->size[1];
    x1->size[0] = 1;
    x1->size[1] = (a11->size[1] + fcnOutput->size[1]) + a12->size[1];
    emxEnsureCapacity((emxArray__common *)x1, k, (int)sizeof(float));
    nm1d2 = a11->size[1];
    emxFree_real32_T(&b_vec);
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * k] = a11->data[a11->size[0] * k];
    }

    nm1d2 = fcnOutput->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * (k + a11->size[1])] = fcnOutput->data
        [fcnOutput->size[0] * k];
    }

    nm1d2 = a12->size[1];
    for (k = 0; k < nm1d2; k++) {
      x1->data[x1->size[0] * ((k + a11->size[1]) + fcnOutput->size[1])] =
        a12->data[a12->size[0] * k];
    }
    break;
  }

  emxFree_real32_T(&a12);
  emxFree_real32_T(&a11);
  switch ((int)mode4) {
   case 0:
    k = x2->size[0] * x2->size[1];
    x2->size[0] = 1;
    x2->size[1] = (a21->size[1] + (int)d_x) + a22->size[1];
    emxEnsureCapacity((emxArray__common *)x2, k, (int)sizeof(float));
    nm1d2 = a21->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * k] = a21->data[a21->size[0] * k];
    }

    nm1d2 = (int)d_x;
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * (k + a21->size[1])] = 1.0F;
    }

    nm1d2 = a22->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * ((k + a21->size[1]) + (int)d_x)] = a22->data
        [a22->size[0] * k];
    }
    break;

   case 1:
    if (rtIsNaNF(d_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = d_x;
    } else if (d_x < 1.0F) {
      n = 0;
      absn = 1.0F;
      s_im = d_x;
    } else if (rtIsInfF(d_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = d_x;
    } else {
      absn = 1.0F;
      ndbl = floor((d_x - 1.0) + 0.5);
      apnd = 1.0 + ndbl;
      cdiff = (1.0 + ndbl) - d_x;
      if (fabs(cdiff) < 2.38418579E-7F * d_x) {
        ndbl++;
        s_im = d_x;
      } else if (cdiff > 0.0) {
        s_im = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        s_im = (float)apnd;
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
      vec->data[0] = absn;
      if (n > 1) {
        vec->data[n - 1] = s_im;
        k = n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          vec->data[k] = absn + (float)k;
          vec->data[(n - k) - 1] = s_im - (float)k;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (absn + s_im) / 2.0F;
        } else {
          vec->data[nm1d2] = absn + (float)nm1d2;
          vec->data[nm1d2 + 1] = s_im - (float)nm1d2;
        }
      }
    }

    rdivide(vec, d_x, fcnOutput);
    k = x2->size[0] * x2->size[1];
    x2->size[0] = 1;
    x2->size[1] = (a21->size[1] + fcnOutput->size[1]) + a22->size[1];
    emxEnsureCapacity((emxArray__common *)x2, k, (int)sizeof(float));
    nm1d2 = a21->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * k] = a21->data[a21->size[0] * k];
    }

    nm1d2 = fcnOutput->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * (k + a21->size[1])] = fcnOutput->data
        [fcnOutput->size[0] * k];
    }

    nm1d2 = a22->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * ((k + a21->size[1]) + fcnOutput->size[1])] =
        a22->data[a22->size[0] * k];
    }
    break;

   case 2:
    if (rtIsNaNF(d_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = d_x;
    } else if (d_x < 1.0F) {
      n = 0;
      absn = 1.0F;
      s_im = d_x;
    } else if (rtIsInfF(d_x)) {
      n = 1;
      absn = ((real32_T)rtNaN);
      s_im = d_x;
    } else {
      absn = 1.0F;
      ndbl = floor((d_x - 1.0) + 0.5);
      apnd = 1.0 + ndbl;
      cdiff = (1.0 + ndbl) - d_x;
      if (fabs(cdiff) < 2.38418579E-7F * d_x) {
        ndbl++;
        s_im = d_x;
      } else if (cdiff > 0.0) {
        s_im = (float)(1.0 + (ndbl - 1.0));
      } else {
        ndbl++;
        s_im = (float)apnd;
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
      vec->data[0] = absn;
      if (n > 1) {
        vec->data[n - 1] = s_im;
        k = n - 1;
        nm1d2 = k / 2;
        for (k = 1; k < nm1d2; k++) {
          vec->data[k] = absn + (float)k;
          vec->data[(n - k) - 1] = s_im - (float)k;
        }

        if (nm1d2 << 1 == n - 1) {
          vec->data[nm1d2] = (absn + s_im) / 2.0F;
        } else {
          vec->data[nm1d2] = absn + (float)nm1d2;
          vec->data[nm1d2 + 1] = s_im - (float)nm1d2;
        }
      }
    }

    emxInit_real32_T(&c_vec, 2);
    k = c_vec->size[0] * c_vec->size[1];
    c_vec->size[0] = 1;
    c_vec->size[1] = vec->size[1];
    emxEnsureCapacity((emxArray__common *)c_vec, k, (int)sizeof(float));
    nm1d2 = vec->size[0] * vec->size[1];
    for (k = 0; k < nm1d2; k++) {
      c_vec->data[k] = -vec->data[k];
    }

    rdivide(c_vec, d_x, fcnOutput);
    b_exp(fcnOutput);
    k = x2->size[0] * x2->size[1];
    x2->size[0] = 1;
    x2->size[1] = (a21->size[1] + fcnOutput->size[1]) + a22->size[1];
    emxEnsureCapacity((emxArray__common *)x2, k, (int)sizeof(float));
    nm1d2 = a21->size[1];
    emxFree_real32_T(&c_vec);
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * k] = a21->data[a21->size[0] * k];
    }

    nm1d2 = fcnOutput->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * (k + a21->size[1])] = fcnOutput->data
        [fcnOutput->size[0] * k];
    }

    nm1d2 = a22->size[1];
    for (k = 0; k < nm1d2; k++) {
      x2->data[x2->size[0] * ((k + a21->size[1]) + fcnOutput->size[1])] =
        a22->data[a22->size[0] * k];
    }
    break;
  }

  emxFree_real32_T(&fcnOutput);
  emxFree_real32_T(&vec);
  emxFree_real32_T(&a22);
  emxFree_real32_T(&a21);
  if (1.0F > b_x) {
    k = 0;
  } else {
    k = (int)b_x;
  }

  nA = x1->size[0] * x1->size[1];
  x1->size[1] = k;
  emxEnsureCapacity((emxArray__common *)x1, nA, (int)sizeof(float));
  if (1.0F > b_x) {
    nA = 0;
  } else {
    nA = (int)b_x;
  }

  n = x2->size[0] * x2->size[1];
  x2->size[1] = nA;
  emxEnsureCapacity((emxArray__common *)x2, n, (int)sizeof(float));
  switch ((int)mode1) {
   case 0:
    n = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = x1->size[1];
    emxEnsureCapacity((emxArray__common *)x, n, (int)sizeof(float));
    nm1d2 = x1->size[0] * x1->size[1];
    for (n = 0; n < nm1d2; n++) {
      x->data[n] = a1 * x1->data[n] + a2 * x2->data[n];
    }
    break;

   case 1:
    conv(x1, x2, x);
    n = x->size[0] * x->size[1];
    if (1.0F > b_x) {
      x->size[1] = 0;
    } else {
      x->size[1] = (int)b_x;
    }

    emxEnsureCapacity((emxArray__common *)x, n, (int)sizeof(float));
    break;

   case 2:
    n = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = x1->size[1];
    emxEnsureCapacity((emxArray__common *)x, n, (int)sizeof(float));
    nm1d2 = x1->size[0] * x1->size[1];
    for (n = 0; n < nm1d2; n++) {
      x->data[n] = x1->data[n] * x2->data[n];
    }
    break;
  }

  c = 1.0F / b_x;
  absn = (float)frexp((float)fabs((float)k), &nB);
  s_im = (float)nB;
  if (absn == 0.5F) {
    s_im = (float)nB - 1.0F;
  }

  emxInit_creal32_T(&b_y1, 2);
  fft(x1, rt_powf_snf(2.0F, s_im), b_y1);
  fftshift(b_y1);
  k = b_y1->size[0] * b_y1->size[1];
  b_y1->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)b_y1, k, (int)sizeof(creal32_T));
  nm1d2 = b_y1->size[0];
  n = b_y1->size[1];
  nm1d2 *= n;
  for (k = 0; k < nm1d2; k++) {
    b_y1->data[k].re *= c;
    b_y1->data[k].im *= c;
  }

  c = 1.0F / b_x;
  absn = (float)frexp((float)fabs((float)nA), &nApnB);
  s_im = (float)nApnB;
  if (absn == 0.5F) {
    s_im = (float)nApnB - 1.0F;
  }

  emxInit_creal32_T(&y2, 2);
  fft(x2, rt_powf_snf(2.0F, s_im), y2);
  fftshift(y2);
  k = y2->size[0] * y2->size[1];
  y2->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y2, k, (int)sizeof(creal32_T));
  nm1d2 = y2->size[0];
  n = y2->size[1];
  nm1d2 *= n;
  for (k = 0; k < nm1d2; k++) {
    y2->data[k].re *= c;
    y2->data[k].im *= c;
  }

  c = 1.0F / b_x;
  absn = (float)fabs((float)x->size[1]);
  absn = (float)frexp(absn, &eint);
  s_im = (float)eint;
  if (absn == 0.5F) {
    s_im = (float)eint - 1.0F;
  }

  emxInit_creal32_T(&y, 2);
  fft(x, rt_powf_snf(2.0F, s_im), y);
  fftshift(y);
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(creal32_T));
  nm1d2 = y->size[0];
  n = y->size[1];
  nm1d2 *= n;
  for (k = 0; k < nm1d2; k++) {
    y->data[k].re *= c;
    y->data[k].im *= c;
  }

  emxInit_creal32_T(&C, 2);
  switch ((int)mode2) {
   case 0:
    k = y3->size[0] * y3->size[1];
    y3->size[0] = 1;
    y3->size[1] = b_y1->size[1];
    emxEnsureCapacity((emxArray__common *)y3, k, (int)sizeof(creal32_T));
    nm1d2 = b_y1->size[0] * b_y1->size[1];
    for (k = 0; k < nm1d2; k++) {
      y3->data[k].re = a1 * b_y1->data[k].re + a2 * y2->data[k].re;
      y3->data[k].im = a1 * b_y1->data[k].im + a2 * y2->data[k].im;
    }
    break;

   case 1:
    nA = b_y1->size[1];
    nB = y2->size[1];
    nApnB = b_y1->size[1] + y2->size[1];
    if ((b_y1->size[1] == 0) || (y2->size[1] == 0)) {
    } else {
      nApnB--;
    }

    k = C->size[0] * C->size[1];
    C->size[0] = 1;
    C->size[1] = nApnB;
    emxEnsureCapacity((emxArray__common *)C, k, (int)sizeof(creal32_T));
    if ((b_y1->size[1] == 0) || (y2->size[1] == 0) || (nApnB == 0)) {
      k = C->size[0] * C->size[1];
      C->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)C, k, (int)sizeof(creal32_T));
      nm1d2 = C->size[1];
      for (k = 0; k < nm1d2; k++) {
        C->data[C->size[0] * k].re = 0.0F;
        C->data[C->size[0] * k].im = 0.0F;
      }
    } else {
      for (n = 1; n <= nApnB; n++) {
        if (nA <= n) {
          nm1d2 = nA;
        } else {
          nm1d2 = n;
        }

        absn = 0.0F;
        s_im = 0.0F;
        if (nB < n + 1) {
          k = (n - nB) + 1;
        } else {
          k = 1;
        }

        while (k <= nm1d2) {
          c_x = b_y1->data[k - 1].re * y2->data[n - k].re - b_y1->data[k - 1].im
            * y2->data[n - k].im;
          d_x = b_y1->data[k - 1].re * y2->data[n - k].im + b_y1->data[k - 1].im
            * y2->data[n - k].re;
          absn += c_x;
          s_im += d_x;
          k++;
        }

        C->data[n - 1].re = absn;
        C->data[n - 1].im = s_im;
      }
    }

    c = b_x / 2.0F;
    absn = 3.0F * b_x / 2.0F;
    if (c + 1.0F > absn) {
      k = 0;
      nA = 0;
    } else {
      k = (int)(c + 1.0F) - 1;
      nA = (int)absn;
    }

    n = y3->size[0] * y3->size[1];
    y3->size[0] = 1;
    y3->size[1] = nA - k;
    emxEnsureCapacity((emxArray__common *)y3, n, (int)sizeof(creal32_T));
    nm1d2 = nA - k;
    for (nA = 0; nA < nm1d2; nA++) {
      y3->data[y3->size[0] * nA] = C->data[k + nA];
    }
    break;

   case 2:
    k = y3->size[0] * y3->size[1];
    y3->size[0] = 1;
    y3->size[1] = b_y1->size[1];
    emxEnsureCapacity((emxArray__common *)y3, k, (int)sizeof(creal32_T));
    nm1d2 = b_y1->size[0] * b_y1->size[1];
    for (k = 0; k < nm1d2; k++) {
      absn = b_x * b_y1->data[k].re;
      s_im = b_x * b_y1->data[k].im;
      c_x = y2->data[k].re;
      d_x = y2->data[k].im;
      y3->data[k].re = absn * c_x - s_im * d_x;
      y3->data[k].im = absn * d_x + s_im * c_x;
    }
    break;
  }

  k = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = y3->size[1];
  emxEnsureCapacity((emxArray__common *)C, k, (int)sizeof(creal32_T));
  nm1d2 = y3->size[0] * y3->size[1];
  for (k = 0; k < nm1d2; k++) {
    C->data[k] = y3->data[k];
  }

  emxInit_creal32_T1(&b_C, 1);
  fftshift(C);
  k = b_C->size[0];
  b_C->size[0] = C->size[1];
  emxEnsureCapacity((emxArray__common *)b_C, k, (int)sizeof(creal32_T));
  nm1d2 = C->size[1];
  for (k = 0; k < nm1d2; k++) {
    b_C->data[k] = C->data[C->size[0] * k];
  }

  emxInit_creal32_T1(&c_y1, 1);
  emxInit_creal32_T(&e_x, 2);
  b_eml_fft(b_C, C->size[1], c_y1);
  ipermute(c_y1, C);
  k = e_x->size[0] * e_x->size[1];
  e_x->size[0] = 1;
  e_x->size[1] = C->size[1];
  emxEnsureCapacity((emxArray__common *)e_x, k, (int)sizeof(creal32_T));
  nm1d2 = C->size[0] * C->size[1];
  emxFree_creal32_T(&b_C);
  emxFree_creal32_T(&c_y1);
  for (k = 0; k < nm1d2; k++) {
    e_x->data[k].re = b_x * C->data[k].re;
    e_x->data[k].im = b_x * C->data[k].im;
  }

  emxFree_creal32_T(&C);
  b_abs(e_x, x3);
  b_abs(b_y1, y1_mag);
  angle(b_y1, y1_phase);
  b_abs(y2, y2_mag);
  angle(y2, y2_phase);
  b_abs(y3, y3_mag);
  angle(y3, y3_phase);
  b_abs(y, y_mag);
  angle(y, y_phase);
  emxFree_creal32_T(&e_x);
  emxFree_creal32_T(&y);
  emxFree_creal32_T(&y2);
  emxFree_creal32_T(&b_y1);
  emxFree_creal32_T(&y3);
}

/*
 * File trailer for L5_1.c
 *
 * [EOF]
 */
