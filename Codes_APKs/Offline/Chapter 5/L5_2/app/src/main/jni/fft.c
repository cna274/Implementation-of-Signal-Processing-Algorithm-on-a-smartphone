/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fft.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 17:09:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_2.h"
#include "fft.h"
#include "L5_2_emxutil.h"
#include "ipermute.h"
#include "L5_2_rtwutil.h"

/* Function Declarations */
static void eml_fft(const emxArray_real32_T *x, int n, emxArray_creal32_T *y);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real32_T *x
 *                int n
 *                emxArray_creal32_T *y
 * Return Type  : void
 */
static void eml_fft(const emxArray_real32_T *x, int n, emxArray_creal32_T *y)
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
      sintab->data[k] = -costab1q->data[b_n - k];
    }

    for (k = costab1q->size[1]; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - b_n];
    }

    emxFree_real32_T(&costab1q);
    ix = 0;
    chanStart = 0;
    while ((n > 0) && (chanStart <= lastChan)) {
      ju = 0;
      nd2 = chanStart;
      for (i = 1; i < minval; i++) {
        y->data[nd2].re = x->data[ix];
        y->data[nd2].im = 0.0F;
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

      y->data[nd2].re = x->data[ix];
      y->data[nd2].im = 0.0F;
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
  }
}

/*
 * Arguments    : const emxArray_real32_T *x
 *                emxArray_creal32_T *y
 * Return Type  : void
 */
void fft(const emxArray_real32_T *x, emxArray_creal32_T *y)
{
  emxArray_real32_T *b_x;
  int i2;
  int loop_ub;
  emxArray_creal32_T *b_y1;
  emxInit_real32_T1(&b_x, 1);
  i2 = b_x->size[0];
  b_x->size[0] = x->size[1];
  emxEnsureCapacity((emxArray__common *)b_x, i2, (int)sizeof(float));
  loop_ub = x->size[1];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_x->data[i2] = x->data[x->size[0] * i2];
  }

  emxInit_creal32_T1(&b_y1, 1);
  eml_fft(b_x, x->size[1], b_y1);
  ipermute(b_y1, y);
  emxFree_real32_T(&b_x);
  emxFree_creal32_T(&b_y1);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
