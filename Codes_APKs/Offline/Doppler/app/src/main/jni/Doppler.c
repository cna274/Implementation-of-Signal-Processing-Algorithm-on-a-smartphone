/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Doppler.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 26-Apr-2016 16:15:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Doppler.h"
#include "fftshift.h"
#include "fft.h"

/* Function Declarations */
static float rt_hypotf_snf(float u0, float u1);

/* Function Definitions */

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = (float)fabs(u0);
  b = (float)fabs(u1);
  if (a < b) {
    a /= b;
    y = b * (float)sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * (float)sqrt(b * b + 1.0F);
  } else if (rtIsNaNF(b)) {
    y = b;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 * Arguments    : float a
 *                float b
 *                float freq
 *                float x[101]
 *                float b_y1[101]
 *                float y2[101]
 *                float input[128]
 *                float incre[128]
 *                float decre[128]
 * Return Type  : void
 */
void Doppler(float a, float b, float freq, float *x, float *b_y1, float *y2, float *input, float *incre, float *decre)
{
  float c;
  float b_c;
  float c_c;
  int k;
  static const float b_b[101] = { 0.0F, 0.01F, 0.02F, 0.03F, 0.04F, 0.049999997F,
    0.06F, 0.07F, 0.08F, 0.0899999961F, 0.099999994F, 0.11F, 0.12F, 0.13F, 0.14F,
    0.149999991F, 0.16F, 0.17F, 0.179999992F, 0.19F, 0.199999988F, 0.21F, 0.22F,
    0.229999989F, 0.24F, 0.25F, 0.26F, 0.269999981F, 0.28F, 0.29F, 0.299999982F,
    0.31F, 0.32F, 0.329999983F, 0.34F, 0.35F, 0.359999985F, 0.37F, 0.38F, 0.39F,
    0.399999976F, 0.41F, 0.42F, 0.429999977F, 0.44F, 0.45F, 0.459999979F, 0.47F,
    0.48F, 0.48999998F, 0.5F, 0.51F, 0.52F, 0.53F, 0.54F, 0.55F, 0.56F,
    0.570000052F, 0.580000043F, 0.590000033F, 0.6F, 0.61F, 0.62F, 0.63F, 0.64F,
    0.65F, 0.659999967F, 0.67F, 0.68F, 0.69F, 0.700000048F, 0.710000038F, 0.72F,
    0.73F, 0.74F, 0.75F, 0.76F, 0.77F, 0.78F, 0.79F, 0.8F, 0.81F, 0.82F, 0.83F,
    0.840000033F, 0.85F, 0.86F, 0.87F, 0.88F, 0.89F, 0.9F, 0.91F, 0.92F, 0.93F,
    0.94F, 0.95F, 0.96F, 0.97F, 0.98F, 0.99F, 1.0F };

  static const float fv0[101] = { 1.0F, 0.99F, 0.98F, 0.97F, 0.96F, 0.95F, 0.94F,
    0.93F, 0.92F, 0.91F, 0.9F, 0.89F, 0.88F, 0.87F, 0.86F, 0.85F, 0.840000033F,
    0.83F, 0.82F, 0.81F, 0.8F, 0.79F, 0.78F, 0.77F, 0.76F, 0.75F, 0.74F, 0.73F,
    0.72F, 0.710000038F, 0.700000048F, 0.69F, 0.68F, 0.67F, 0.659999967F, 0.65F,
    0.64F, 0.63F, 0.62F, 0.61F, 0.6F, 0.590000033F, 0.580000043F, 0.570000052F,
    0.56F, 0.55F, 0.54F, 0.53F, 0.52F, 0.51F, 0.5F, 0.49F, 0.480000019F,
    0.470000029F, 0.459999979F, 0.45F, 0.44F, 0.429999948F, 0.419999957F,
    0.409999967F, 0.399999976F, 0.39F, 0.38F, 0.37F, 0.36F, 0.350000024F,
    0.340000033F, 0.329999983F, 0.32F, 0.31F, 0.299999952F, 0.289999962F,
    0.279999971F, 0.269999981F, 0.26F, 0.25F, 0.24000001F, 0.230000019F,
    0.220000029F, 0.209999979F, 0.199999988F, 0.19F, 0.18F, 0.170000017F,
    0.159999967F, 0.149999976F, 0.139999986F, 0.13F, 0.120000005F, 0.110000014F,
    0.100000024F, 0.0899999738F, 0.0799999833F, 0.0699999928F, 0.0600000024F,
    0.0500000119F, 0.0400000215F, 0.0299999714F, 0.0199999809F, 0.00999999F,
    0.0F };

  creal32_T fcnOutput[128];
  c = 6.28318548F * freq;

  /* a = 1.2; */
  /* b = 0.8; */
  /*  Time increment function */
  /* Time Decrement function */
  /* Doppler Effect Vehicle approaching */
  b_c = 6.28318548F * a * freq;

  /* Doppler Effect Vehicle passes by */
  c_c = 6.28318548F * b * freq;
  for (k = 0; k < 101; k++) {
    x[k] = (float)sin(c * b_b[k]);
    b_y1[k] = b_b[k] * (float)sin(b_c * b_b[k]);
    y2[k] = fv0[k] * (float)sin(c_c * b_b[k]);
  }

  /* figure; */
  /* input = fft(x); plot(input);  */
  fft(x, fcnOutput);
  fftshift(fcnOutput);
  for (k = 0; k < 128; k++) {
    fcnOutput[k].re *= 0.01F;
    fcnOutput[k].im *= 0.01F;
    input[k] = rt_hypotf_snf(fcnOutput[k].re, fcnOutput[k].im);
  }

  /* figure; */
  /* figure; */
  fft(b_y1, fcnOutput);
  fftshift(fcnOutput);
  for (k = 0; k < 128; k++) {
    fcnOutput[k].re *= 0.01F;
    fcnOutput[k].im *= 0.01F;
    incre[k] = rt_hypotf_snf(fcnOutput[k].re, fcnOutput[k].im);
  }

  /* figure; */
  /* figure; */
  fft(y2, fcnOutput);
  fftshift(fcnOutput);
  for (k = 0; k < 128; k++) {
    fcnOutput[k].re *= 0.01F;
    fcnOutput[k].im *= 0.01F;
    decre[k] = rt_hypotf_snf(fcnOutput[k].re, fcnOutput[k].im);
  }
}

/*
 * File trailer for Doppler.c
 *
 * [EOF]
 */
