/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fftshift.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 26-Apr-2016 16:15:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Doppler.h"
#include "fftshift.h"

/* Function Definitions */

/*
 * Arguments    : creal32_T x[128]
 * Return Type  : void
 */
void fftshift(creal32_T x[128])
{
  int dim;
  int a;
  int vlend2;
  int npages;
  int k;
  int i2;
  int i;
  int i1;
  int ib;
  float xtmp_re;
  float xtmp_im;
  for (dim = 0; dim < 2; dim++) {
    a = 1 + 127 * dim;
    if (a <= 1) {
    } else {
      vlend2 = a / 2;
      npages = 1;
      k = dim + 2;
      while (k < 3) {
        npages <<= 7;
        k = 3;
      }

      if (vlend2 << 1 == a) {
        i2 = 0;
        for (i = 1; i <= npages; i++) {
          i1 = i2;
          i2 += a;
          ib = i1 + vlend2;
          for (k = 1; k <= vlend2; k++) {
            xtmp_re = x[i1].re;
            xtmp_im = x[i1].im;
            x[i1] = x[ib];
            x[ib].re = xtmp_re;
            x[ib].im = xtmp_im;
            i1++;
            ib++;
          }
        }
      } else {
        i2 = 0;
        for (i = 1; i <= npages; i++) {
          i1 = i2;
          i2 += a;
          ib = i1 + vlend2;
          xtmp_re = x[ib].re;
          xtmp_im = x[ib].im;
          for (k = 1; k <= vlend2; k++) {
            x[ib] = x[i1];
            x[i1] = x[ib + 1];
            i1++;
            ib++;
          }

          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for fftshift.c
 *
 * [EOF]
 */
