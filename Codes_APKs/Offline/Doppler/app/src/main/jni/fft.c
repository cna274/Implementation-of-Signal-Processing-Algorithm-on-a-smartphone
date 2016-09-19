/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fft.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 26-Apr-2016 16:15:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Doppler.h"
#include "fft.h"

/* Function Definitions */

/*
 * Arguments    : const float x[101]
 *                creal32_T y[128]
 * Return Type  : void
 */
void fft(const float x[101], creal32_T y[128])
{
  creal32_T b_y1[128];
  int i;
  int ix;
  int ju;
  int iy;
  boolean_T tst;
  float temp_re;
  float temp_im;
  int iheight;
  int istart;
  int j;
  static const float fv1[65] = { 1.0F, 0.99879545F, 0.99518472F, 0.989176512F,
    0.980785251F, 0.970031261F, 0.956940353F, 0.941544056F, 0.923879504F,
    0.903989315F, 0.881921232F, 0.857728601F, 0.831469595F, 0.803207517F,
    0.773010433F, 0.740951121F, 0.707106769F, 0.671559F, 0.634393334F,
    0.59569931F, 0.555570245F, 0.514102757F, 0.471396744F, 0.427555084F,
    0.382683456F, 0.336889863F, 0.290284663F, 0.242980197F, 0.195090324F,
    0.146730468F, 0.0980171412F, 0.0490676761F, 0.0F, -0.0490676761F,
    -0.0980171412F, -0.146730468F, -0.195090324F, -0.242980197F, -0.290284663F,
    -0.336889863F, -0.382683456F, -0.427555084F, -0.471396744F, -0.514102757F,
    -0.555570245F, -0.59569931F, -0.634393334F, -0.671559F, -0.707106769F,
    -0.740951121F, -0.773010433F, -0.803207517F, -0.831469595F, -0.857728601F,
    -0.881921232F, -0.903989315F, -0.923879504F, -0.941544056F, -0.956940353F,
    -0.970031261F, -0.980785251F, -0.989176512F, -0.99518472F, -0.99879545F,
    -1.0F };

  float twid_re;
  static const float fv2[65] = { 0.0F, -0.0490676761F, -0.0980171412F,
    -0.146730468F, -0.195090324F, -0.242980197F, -0.290284663F, -0.336889863F,
    -0.382683456F, -0.427555084F, -0.471396744F, -0.514102757F, -0.555570245F,
    -0.59569931F, -0.634393334F, -0.671559F, -0.707106769F, -0.740951121F,
    -0.773010433F, -0.803207517F, -0.831469595F, -0.857728601F, -0.881921232F,
    -0.903989315F, -0.923879504F, -0.941544056F, -0.956940353F, -0.970031261F,
    -0.980785251F, -0.989176512F, -0.99518472F, -0.99879545F, -1.0F,
    -0.99879545F, -0.99518472F, -0.989176512F, -0.980785251F, -0.970031261F,
    -0.956940353F, -0.941544056F, -0.923879504F, -0.903989315F, -0.881921232F,
    -0.857728601F, -0.831469595F, -0.803207517F, -0.773010433F, -0.740951121F,
    -0.707106769F, -0.671559F, -0.634393334F, -0.59569931F, -0.555570245F,
    -0.514102757F, -0.471396744F, -0.427555084F, -0.382683456F, -0.336889863F,
    -0.290284663F, -0.242980197F, -0.195090324F, -0.146730468F, -0.0980171412F,
    -0.0490676761F, -0.0F };

  float twid_im;
  int ihi;
  for (i = 0; i < 128; i++) {
    b_y1[i].re = 0.0F;
    b_y1[i].im = 0.0F;
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 100; i++) {
    b_y1[iy].re = x[ix];
    b_y1[iy].im = 0.0F;
    iy = 128;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  b_y1[iy].re = x[ix];
  b_y1[iy].im = 0.0F;
  for (i = 0; i <= 127; i += 2) {
    temp_re = b_y1[i + 1].re;
    temp_im = b_y1[i + 1].im;
    b_y1[i + 1].re = b_y1[i].re - b_y1[i + 1].re;
    b_y1[i + 1].im = b_y1[i].im - b_y1[i + 1].im;
    b_y1[i].re += temp_re;
    b_y1[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 32;
  iheight = 125;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = b_y1[i + iy].re;
      temp_im = b_y1[i + iy].im;
      b_y1[i + iy].re = b_y1[i].re - temp_re;
      b_y1[i + iy].im = b_y1[i].im - temp_im;
      b_y1[i].re += temp_re;
      b_y1[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 64; j += ju) {
      twid_re = fv1[j];
      twid_im = fv2[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * b_y1[i + iy].re - twid_im * b_y1[i + iy].im;
        temp_im = twid_re * b_y1[i + iy].im + twid_im * b_y1[i + iy].re;
        b_y1[i + iy].re = b_y1[i].re - temp_re;
        b_y1[i + iy].im = b_y1[i].im - temp_im;
        b_y1[i].re += temp_re;
        b_y1[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix <<= 1;
    iheight -= iy;
  }

  memcpy(&y[0], &b_y1[0], sizeof(creal32_T) << 7);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
