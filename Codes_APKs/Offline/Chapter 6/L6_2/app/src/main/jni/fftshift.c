/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fftshift.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 03:17:05
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_2.h"
#include "fftshift.h"

/* Function Definitions */

/*
 * Arguments    : creal32_T x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void fftshift(creal32_T x_data[], int x_size[2])
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
    a = x_size[dim];
    if (x_size[dim] <= 1) {
    } else {
      vlend2 = x_size[dim];
      vlend2 /= 2;
      npages = 1;
      k = dim + 2;
      while (k < 3) {
        npages *= x_size[1];
        k = 3;
      }

      if (vlend2 << 1 == x_size[dim]) {
        i2 = 0;
        for (i = 1; i <= npages; i++) {
          i1 = i2;
          i2 += a;
          ib = i1 + vlend2;
          for (k = 1; k <= vlend2; k++) {
            xtmp_re = x_data[i1].re;
            xtmp_im = x_data[i1].im;
            x_data[i1] = x_data[ib];
            x_data[ib].re = xtmp_re;
            x_data[ib].im = xtmp_im;
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
          xtmp_re = x_data[ib].re;
          xtmp_im = x_data[ib].im;
          for (k = 1; k <= vlend2; k++) {
            x_data[ib] = x_data[i1];
            x_data[i1] = x_data[ib + 1];
            i1++;
            ib++;
          }

          x_data[ib].re = xtmp_re;
          x_data[ib].im = xtmp_im;
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
