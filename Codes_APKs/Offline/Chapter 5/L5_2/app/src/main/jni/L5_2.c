/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L5_2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 17:09:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_2.h"
#include "L5_2_emxutil.h"
#include "abs.h"
#include "fftshift.h"
#include "ipermute.h"
#include "fft.h"
#include "rand.h"
#include "sin.h"
#include "L5_2_rtwutil.h"

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
 * Arguments    : float fc
 *                emxArray_real32_T *b_y1
 *                emxArray_real32_T *y2
 *                emxArray_real32_T *y3
 *                emxArray_real32_T *y4
 *                emxArray_real32_T *z1
 *                emxArray_real32_T *z2
 *                emxArray_real32_T *z3
 *                emxArray_creal32_T *z4
 * Return Type  : void
 */
void L5_2(float fc, emxArray_real32_T *b_y1, emxArray_real32_T *y2,
          emxArray_real32_T *y3, emxArray_real32_T *y4, emxArray_real32_T *z1,
          emxArray_real32_T *z2, emxArray_real32_T *z3, emxArray_creal32_T *z4)
{
  float c;
  int n;
  float absn;
  float bnew;
  double ndbl;
  double apnd;
  double cdiff;
  int i0;
  int nm1d2;
  int k;
  float kd;
  int loop_ub;
  emxArray_real32_T *vec;
  emxArray_real_T *fcnOutput;
  int eint;
  emxArray_real32_T *r0;
  emxArray_real32_T *r1;
  int b_eint;
  emxArray_real32_T *r2;
  emxArray_real32_T *r3;
  int c_eint;
  emxArray_real32_T *r4;
  emxArray_real32_T *r5;
  emxArray_creal32_T *b_y3;
  emxArray_creal32_T *b_fcnOutput;
  emxArray_creal32_T *c_fcnOutput;
  emxArray_creal32_T *d_fcnOutput;
  emxArray_creal32_T *b_y4;
  emxArray_creal32_T *c_y3;
  int d_eint;
  emxArray_real32_T *r6;
  emxArray_creal32_T *r7;
  emxArray_creal32_T *c_y4;
  emxArray_creal32_T *c_y1;
  c = 1.0F / (5.0F * fc);
  if (rtIsNaNF(c)) {
    n = 1;
    absn = ((real32_T)rtNaN);
    bnew = 0.1F;
  } else if ((c == 0.0F) || (c < 0.0F)) {
    n = 0;
    absn = 0.0F;
    bnew = 0.1F;
  } else if (rtIsInfF(c)) {
    n = 1;
    absn = 0.0F;
    bnew = 0.1F;
  } else {
    absn = 0.0F;
    ndbl = floor(0.10000000149011612 / c + 0.5);
    apnd = ndbl * c;
    if (c > 0.0F) {
      cdiff = apnd - 0.10000000149011612;
    } else {
      cdiff = 0.10000000149011612 - apnd;
    }

    if (fabs(cdiff) < 2.3841858265427618E-8) {
      ndbl++;
      bnew = 0.1F;
    } else if (cdiff > 0.0) {
      bnew = (float)((ndbl - 1.0) * c);
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

  i0 = z2->size[0] * z2->size[1];
  z2->size[0] = 1;
  z2->size[1] = n;
  emxEnsureCapacity((emxArray__common *)z2, i0, (int)sizeof(float));
  if (n > 0) {
    z2->data[0] = absn;
    if (n > 1) {
      z2->data[n - 1] = bnew;
      i0 = n - 1;
      nm1d2 = i0 / 2;
      for (k = 1; k < nm1d2; k++) {
        kd = (float)k * c;
        z2->data[k] = absn + kd;
        z2->data[(n - k) - 1] = bnew - kd;
      }

      if (nm1d2 << 1 == n - 1) {
        z2->data[nm1d2] = (absn + bnew) / 2.0F;
      } else {
        kd = (float)nm1d2 * c;
        z2->data[nm1d2] = absn + kd;
        z2->data[nm1d2 + 1] = bnew - kd;
      }
    }
  }

  i0 = z1->size[0] * z1->size[1];
  z1->size[0] = 1;
  z1->size[1] = z2->size[1];
  emxEnsureCapacity((emxArray__common *)z1, i0, (int)sizeof(float));
  loop_ub = z2->size[0] * z2->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    z1->data[i0] = 3895.57495F * z2->data[i0];
  }

  emxInit_real32_T(&vec, 2);
  b_sin(z1);
  i0 = vec->size[0] * vec->size[1];
  vec->size[0] = 1;
  vec->size[1] = z2->size[1];
  emxEnsureCapacity((emxArray__common *)vec, i0, (int)sizeof(float));
  loop_ub = z2->size[0] * z2->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    vec->data[i0] = 628.318542F * z2->data[i0];
  }

  b_sin(vec);
  i0 = z1->size[0] * z1->size[1];
  z1->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)z1, i0, (int)sizeof(float));
  nm1d2 = z1->size[0];
  k = z1->size[1];
  loop_ub = nm1d2 * k;
  for (i0 = 0; i0 < loop_ub; i0++) {
    z1->data[i0] += vec->data[i0];
  }

  emxFree_real32_T(&vec);
  c = 6.28318548F * fc;
  i0 = z2->size[0] * z2->size[1];
  z2->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)z2, i0, (int)sizeof(float));
  nm1d2 = z2->size[0];
  k = z2->size[1];
  loop_ub = nm1d2 * k;
  for (i0 = 0; i0 < loop_ub; i0++) {
    z2->data[i0] *= c;
  }

  b_sin(z2);
  i0 = z2->size[0] * z2->size[1];
  z2->size[0] = 1;
  z2->size[1] = z1->size[1];
  emxEnsureCapacity((emxArray__common *)z2, i0, (int)sizeof(float));
  loop_ub = z1->size[0] * z1->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    z2->data[i0] *= z1->data[i0];
  }

  emxInit_real_T(&fcnOutput, 2);
  b_rand((float)z2->size[1], fcnOutput);
  i0 = z3->size[0] * z3->size[1];
  z3->size[0] = 1;
  z3->size[1] = z2->size[1];
  emxEnsureCapacity((emxArray__common *)z3, i0, (int)sizeof(float));
  loop_ub = z2->size[0] * z2->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    z3->data[i0] = z2->data[i0] + 0.1F * (float)fcnOutput->data[i0];
  }

  emxFree_real_T(&fcnOutput);
  n = z1->size[1];
  absn = (float)fabs((float)z1->size[1]);
  absn = (float)frexp(absn, &eint);
  bnew = (float)eint;
  if (absn == 0.5F) {
    bnew = (float)eint - 1.0F;
  }

  emxInit_real32_T(&r0, 2);
  c = rt_powf_snf(2.0F, bnew) - (float)z1->size[1];
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(float));
  loop_ub = (int)c;
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = 0.0F;
  }

  emxInit_real32_T(&r1, 2);
  nm1d2 = z1->size[1];
  k = r0->size[1];
  i0 = z1->size[0] * z1->size[1];
  z1->size[1] = nm1d2 + k;
  emxEnsureCapacity((emxArray__common *)z1, i0, (int)sizeof(float));
  i0 = r1->size[0] * r1->size[1];
  r1->size[0] = 1;
  r1->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)r1, i0, (int)sizeof(float));
  loop_ub = (int)c;
  emxFree_real32_T(&r0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    r1->data[r1->size[0] * i0] = 0.0F;
  }

  for (i0 = 0; i0 < k; i0++) {
    z1->data[nm1d2 + i0] = r1->data[i0];
  }

  emxFree_real32_T(&r1);
  absn = (float)frexp((float)fabs((float)n), &b_eint);
  bnew = (float)b_eint;
  if (absn == 0.5F) {
    bnew = (float)b_eint - 1.0F;
  }

  emxInit_real32_T(&r2, 2);
  c = rt_powf_snf(2.0F, bnew) - (float)n;
  i0 = r2->size[0] * r2->size[1];
  r2->size[0] = 1;
  r2->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)r2, i0, (int)sizeof(float));
  loop_ub = (int)c;
  for (i0 = 0; i0 < loop_ub; i0++) {
    r2->data[i0] = 0.0F;
  }

  emxInit_real32_T(&r3, 2);
  nm1d2 = z2->size[1];
  k = r2->size[1];
  i0 = z2->size[0] * z2->size[1];
  z2->size[1] = nm1d2 + k;
  emxEnsureCapacity((emxArray__common *)z2, i0, (int)sizeof(float));
  i0 = r3->size[0] * r3->size[1];
  r3->size[0] = 1;
  r3->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)r3, i0, (int)sizeof(float));
  loop_ub = (int)c;
  emxFree_real32_T(&r2);
  for (i0 = 0; i0 < loop_ub; i0++) {
    r3->data[r3->size[0] * i0] = 0.0F;
  }

  for (i0 = 0; i0 < k; i0++) {
    z2->data[nm1d2 + i0] = r3->data[i0];
  }

  emxFree_real32_T(&r3);
  absn = (float)frexp((float)fabs((float)n), &c_eint);
  bnew = (float)c_eint;
  if (absn == 0.5F) {
    bnew = (float)c_eint - 1.0F;
  }

  emxInit_real32_T(&r4, 2);
  c = rt_powf_snf(2.0F, bnew) - (float)n;
  i0 = r4->size[0] * r4->size[1];
  r4->size[0] = 1;
  r4->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)r4, i0, (int)sizeof(float));
  loop_ub = (int)c;
  for (i0 = 0; i0 < loop_ub; i0++) {
    r4->data[i0] = 0.0F;
  }

  emxInit_real32_T(&r5, 2);
  nm1d2 = z3->size[1];
  k = r4->size[1];
  i0 = z3->size[0] * z3->size[1];
  z3->size[1] = nm1d2 + k;
  emxEnsureCapacity((emxArray__common *)z3, i0, (int)sizeof(float));
  i0 = r5->size[0] * r5->size[1];
  r5->size[0] = 1;
  r5->size[1] = (int)c;
  emxEnsureCapacity((emxArray__common *)r5, i0, (int)sizeof(float));
  loop_ub = (int)c;
  emxFree_real32_T(&r4);
  for (i0 = 0; i0 < loop_ub; i0++) {
    r5->data[r5->size[0] * i0] = 0.0F;
  }

  for (i0 = 0; i0 < k; i0++) {
    z3->data[nm1d2 + i0] = r5->data[i0];
  }

  emxFree_real32_T(&r5);
  emxInit_creal32_T(&b_y3, 2);
  emxInit_creal32_T(&b_fcnOutput, 2);
  emxInit_creal32_T(&c_fcnOutput, 2);
  c = 1.0F / (float)n;
  fft(z1, b_fcnOutput);
  kd = 1.0F / (float)n;
  fft(z2, c_fcnOutput);
  absn = 1.0F / (float)n;
  fft(z3, b_y3);
  i0 = b_y3->size[0] * b_y3->size[1];
  b_y3->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)b_y3, i0, (int)sizeof(creal32_T));
  nm1d2 = b_y3->size[0];
  k = b_y3->size[1];
  loop_ub = nm1d2 * k;
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_y3->data[i0].re *= absn;
    b_y3->data[i0].im *= absn;
  }

  emxInit_creal32_T(&d_fcnOutput, 2);
  i0 = d_fcnOutput->size[0] * d_fcnOutput->size[1];
  d_fcnOutput->size[0] = 1;
  d_fcnOutput->size[1] = (int)(float)n;
  emxEnsureCapacity((emxArray__common *)d_fcnOutput, i0, (int)sizeof(creal32_T));
  loop_ub = (int)(float)n;
  for (i0 = 0; i0 < loop_ub; i0++) {
    d_fcnOutput->data[i0].re = 0.0F;
    d_fcnOutput->data[i0].im = 0.0F;
  }

  emxInit_creal32_T(&b_y4, 2);
  i0 = b_y4->size[0] * b_y4->size[1];
  b_y4->size[0] = 1;
  b_y4->size[1] = d_fcnOutput->size[1];
  emxEnsureCapacity((emxArray__common *)b_y4, i0, (int)sizeof(creal32_T));
  loop_ub = d_fcnOutput->size[0] * d_fcnOutput->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_y4->data[i0] = d_fcnOutput->data[i0];
  }

  absn = fc * 0.1F;
  bnew = fc * 0.1F;
  if (absn + 1.0F > bnew + 200.0F) {
    i0 = 0;
    k = 0;
  } else {
    i0 = (int)(absn + 1.0F) - 1;
    k = (int)(bnew + 200.0F);
  }

  emxInit_creal32_T(&c_y3, 2);
  nm1d2 = c_y3->size[0] * c_y3->size[1];
  c_y3->size[0] = 1;
  c_y3->size[1] = k - i0;
  emxEnsureCapacity((emxArray__common *)c_y3, nm1d2, (int)sizeof(creal32_T));
  loop_ub = k - i0;
  for (k = 0; k < loop_ub; k++) {
    c_y3->data[c_y3->size[0] * k] = b_y3->data[i0 + k];
  }

  emxFree_creal32_T(&d_fcnOutput);
  for (i0 = 0; i0 < 200; i0++) {
    b_y4->data[i0] = c_y3->data[i0];
  }

  emxFree_creal32_T(&c_y3);
  absn = (float)frexp((float)fabs((float)n), &d_eint);
  bnew = (float)d_eint;
  if (absn == 0.5F) {
    bnew = (float)d_eint - 1.0F;
  }

  emxInit_real32_T(&r6, 2);
  absn = rt_powf_snf(2.0F, bnew) - (float)n;
  i0 = r6->size[0] * r6->size[1];
  r6->size[0] = 1;
  r6->size[1] = (int)absn;
  emxEnsureCapacity((emxArray__common *)r6, i0, (int)sizeof(float));
  loop_ub = (int)absn;
  for (i0 = 0; i0 < loop_ub; i0++) {
    r6->data[i0] = 0.0F;
  }

  emxInit_creal32_T(&r7, 2);
  nm1d2 = b_y4->size[1];
  k = r6->size[1];
  i0 = b_y4->size[0] * b_y4->size[1];
  b_y4->size[1] = nm1d2 + k;
  emxEnsureCapacity((emxArray__common *)b_y4, i0, (int)sizeof(creal32_T));
  i0 = r7->size[0] * r7->size[1];
  r7->size[0] = 1;
  r7->size[1] = (int)absn;
  emxEnsureCapacity((emxArray__common *)r7, i0, (int)sizeof(creal32_T));
  loop_ub = (int)absn;
  emxFree_real32_T(&r6);
  for (i0 = 0; i0 < loop_ub; i0++) {
    r7->data[r7->size[0] * i0].re = 0.0F;
    r7->data[r7->size[0] * i0].im = 0.0F;
  }

  for (i0 = 0; i0 < k; i0++) {
    b_y4->data[nm1d2 + i0] = r7->data[i0];
  }

  emxFree_creal32_T(&r7);
  emxInit_creal32_T1(&c_y4, 1);
  i0 = c_y4->size[0];
  c_y4->size[0] = b_y4->size[1];
  emxEnsureCapacity((emxArray__common *)c_y4, i0, (int)sizeof(creal32_T));
  loop_ub = b_y4->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    c_y4->data[i0] = b_y4->data[b_y4->size[0] * i0];
  }

  emxInit_creal32_T1(&c_y1, 1);
  b_eml_fft(c_y4, b_y4->size[1], c_y1);
  ipermute(c_y1, z4);
  i0 = z4->size[0] * z4->size[1];
  z4->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)z4, i0, (int)sizeof(creal32_T));
  nm1d2 = z4->size[0];
  k = z4->size[1];
  loop_ub = nm1d2 * k;
  emxFree_creal32_T(&c_y4);
  emxFree_creal32_T(&c_y1);
  for (i0 = 0; i0 < loop_ub; i0++) {
    z4->data[i0].re *= (float)n;
    z4->data[i0].im *= (float)n;
  }

  i0 = b_fcnOutput->size[0] * b_fcnOutput->size[1];
  b_fcnOutput->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)b_fcnOutput, i0, (int)sizeof(creal32_T));
  nm1d2 = b_fcnOutput->size[0];
  k = b_fcnOutput->size[1];
  loop_ub = nm1d2 * k;
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_fcnOutput->data[i0].re *= c;
    b_fcnOutput->data[i0].im *= c;
  }

  fftshift(b_fcnOutput);
  b_abs(b_fcnOutput, b_y1);
  i0 = c_fcnOutput->size[0] * c_fcnOutput->size[1];
  c_fcnOutput->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)c_fcnOutput, i0, (int)sizeof(creal32_T));
  nm1d2 = c_fcnOutput->size[0];
  k = c_fcnOutput->size[1];
  loop_ub = nm1d2 * k;
  emxFree_creal32_T(&b_fcnOutput);
  for (i0 = 0; i0 < loop_ub; i0++) {
    c_fcnOutput->data[i0].re *= kd;
    c_fcnOutput->data[i0].im *= kd;
  }

  fftshift(c_fcnOutput);
  b_abs(c_fcnOutput, y2);
  fftshift(b_y3);
  b_abs(b_y3, y3);
  fftshift(b_y4);
  b_abs(b_y4, y4);
  emxFree_creal32_T(&c_fcnOutput);
  emxFree_creal32_T(&b_y4);
  emxFree_creal32_T(&b_y3);
}

/*
 * File trailer for L5_2.c
 *
 * [EOF]
 */
