/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: music.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 26-Apr-2016 16:20:33
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music.h"
#include "sum.h"
#include "sin.h"
#include "cos.h"
#include "mean.h"

/* Function Definitions */

/*
 * Arguments    : float A1
 *                float A2
 *                float A3
 *                float A4
 *                float A5
 *                float A6
 *                float freq1
 *                float freq2
 *                float freq3
 *                float freq4
 *                float freq5
 *                float freq6
 *                float option
 *                float y_data[]
 *                int y_size[2]
 *                float an[120]
 *                float bn[120]
 *                float *a0
 * Return Type  : void
 */
void music(float A1, float A2, float A3, float A4, float A5, float A6, float
           freq1, float freq2, float freq3, float freq4, float freq5, float
           freq6, float option, float *y_data, int *y_size, float *an,
           float *bn, float *a0)
{
  float w1;
  float w2;
  float w3;
  float w4;
  float w5;
  float w6;
  float vec_data[101];
  int k;
  static const float b[101] = { 0.0F, 0.01F, 0.02F, 0.03F, 0.04F, 0.049999997F,
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

  float b_y_data[101];
  float fv0[101];
  float fv1[101];
  int varargin_2;
  int n;
  float fcnOutput;
  int i;
  int ndbl;
  int apnd;
  int cdiff;
  int vec_size[2];
  int b_y_size[2];
  int c_y_size[2];

  /* A1 = 1;A2 = 1;A3 = 1;A4 = 1;A5 = 1;A6 = 1; */
  /*  freq1 = 20; */
  /*  freq2 = 30; */
  /*  freq3 = 40; */
  /*  freq4 = 50; */
  /*  freq5 = 60; */
  /*  freq6 = 70; */
  w1 = 6.28318548F * freq1;
  w2 = 6.28318548F * freq2;
  w3 = 6.28318548F * freq3;
  w4 = 6.28318548F * freq4;
  w5 = 6.28318548F * freq5;
  w6 = 6.28318548F * freq6;

  /* option = 2; */
  switch ((int)option) {
   case 1:
    /* ------------------% */
    for (k = 0; k < 101; k++) {
      vec_data[k] = w3 * b[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w2 * b[k] + A3 * vec_data[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w1 * b[k] + A2 * vec_data[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w4 * b[k];
    }

    b_sin(b_y_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w6 * b[k] + A4 * b_y_data[k];
    }

    b_sin(b_y_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w5 * b[k] + A6 * b_y_data[k];
    }

    b_sin(b_y_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w4 * b[k] + A5 * b_y_data[k];
    }

    b_sin(b_y_data);
    y_size[0] = 1;
    y_size[1] = 101;
    for (k = 0; k < 101; k++) {
      y_data[k] = A1 * vec_data[k] + A4 * b_y_data[k];
    }
    break;

   case 2:
    /* -----------------% */
    /* ---------------% */
    /* ---------------% */
    for (k = 0; k < 101; k++) {
      vec_data[k] = w6 * b[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w5 * b[k] + A6 * vec_data[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w4 * b[k];
    }

    b_sin(b_y_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w3 * b[k] + A4 * b_y_data[k];
    }

    b_sin(b_y_data);
    for (k = 0; k < 101; k++) {
      fv0[k] = w2 * b[k];
    }

    b_sin(fv0);
    for (k = 0; k < 101; k++) {
      fv0[k] = w2 * b[k] + A2 * fv0[k];
    }

    b_sin(fv0);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w1 * b[k] + ((A5 * vec_data[k] + A3 * b_y_data[k]) + A2 *
        fv0[k]);
    }

    b_sin(vec_data);
    y_size[0] = 1;
    y_size[1] = 101;
    for (k = 0; k < 101; k++) {
      y_data[k] = A1 * vec_data[k];
    }
    break;

   case 3:
    /* ----------------% */
    for (k = 0; k < 101; k++) {
      vec_data[k] = w5 * b[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w5 * b[k] + A5 * vec_data[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w4 * b[k] + A5 * vec_data[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      vec_data[k] = w3 * b[k] + A4 * vec_data[k];
    }

    b_sin(vec_data);
    for (k = 0; k < 101; k++) {
      b_y_data[k] = w2 * b[k];
    }

    b_sin(b_y_data);
    for (k = 0; k < 101; k++) {
      fv0[k] = w1 * b[k];
    }

    b_sin(fv0);
    for (k = 0; k < 101; k++) {
      fv1[k] = w6 * b[k];
    }

    b_sin(fv1);
    y_size[0] = 1;
    y_size[1] = 101;
    for (k = 0; k < 101; k++) {
      y_data[k] = ((A3 * vec_data[k] + A2 * b_y_data[k]) + A1 * fv0[k]) + A6 *
        fv1[k];
    }
    break;

   default:
    y_size[0] = 1;
    y_size[1] = 1;
    y_data[0] = 0.0F;
    break;
  }

  varargin_2 = y_size[1];
  n = y_size[1];
  fcnOutput = mean(y_data, y_size);
  *a0 = fcnOutput;
  for (k = 0; k < 120; k++) {
    an[k] = 0.0F;
    bn[k] = 0.0F;
  }

  for (i = 0; i < 5; i++) {
    fcnOutput = 6.28318548F * ((1.0F + (float)i) / (float)n);
    ndbl = (int)floor(((double)varargin_2 - 1.0) + 0.5);
    apnd = ndbl + 1;
    cdiff = (ndbl - n) + 1;
    if (fabs(cdiff) < 2.38418579E-7F * (float)varargin_2) {
      ndbl++;
      apnd = n;
    } else if (cdiff > 0) {
      apnd = ndbl;
    } else {
      ndbl++;
    }

    vec_size[1] = ndbl;
    if (ndbl > 0) {
      vec_data[0] = 1.0F;
      if (ndbl > 1) {
        vec_data[ndbl - 1] = (float)apnd;
        k = ndbl - 1;
        cdiff = k / 2;
        for (k = 1; k < cdiff; k++) {
          vec_data[k] = 1.0F + (float)k;
          vec_data[(ndbl - k) - 1] = (float)(apnd - k);
        }

        if (cdiff << 1 == ndbl - 1) {
          vec_data[cdiff] = (1.0F + (float)apnd) / 2.0F;
        } else {
          vec_data[cdiff] = 1.0F + (float)cdiff;
          vec_data[cdiff + 1] = (float)(apnd - cdiff);
        }
      }
    }

    vec_size[0] = 1;
    for (k = 0; k < ndbl; k++) {
      vec_data[k] *= fcnOutput;
    }

    b_cos(vec_data, vec_size);
    b_y_size[0] = 1;
    b_y_size[1] = y_size[1];
    cdiff = y_size[1];
    for (k = 0; k < cdiff; k++) {
      b_y_data[k] = y_data[k] * vec_data[k];
    }

    fcnOutput = sum(b_y_data, b_y_size);
    an[i] = 2.0F / (float)n * fcnOutput;
    fcnOutput = 6.28318548F * ((1.0F + (float)i) / (float)n);
    ndbl = (int)floor(((double)varargin_2 - 1.0) + 0.5);
    apnd = ndbl + 1;
    cdiff = (ndbl - n) + 1;
    if (fabs(cdiff) < 2.38418579E-7F * (float)varargin_2) {
      ndbl++;
      apnd = n;
    } else if (cdiff > 0) {
      apnd = ndbl;
    } else {
      ndbl++;
    }

    vec_size[1] = ndbl;
    if (ndbl > 0) {
      vec_data[0] = 1.0F;
      if (ndbl > 1) {
        vec_data[ndbl - 1] = (float)apnd;
        k = ndbl - 1;
        cdiff = k / 2;
        for (k = 1; k < cdiff; k++) {
          vec_data[k] = 1.0F + (float)k;
          vec_data[(ndbl - k) - 1] = (float)(apnd - k);
        }

        if (cdiff << 1 == ndbl - 1) {
          vec_data[cdiff] = (1.0F + (float)apnd) / 2.0F;
        } else {
          vec_data[cdiff] = 1.0F + (float)cdiff;
          vec_data[cdiff + 1] = (float)(apnd - cdiff);
        }
      }
    }

    vec_size[0] = 1;
    for (k = 0; k < ndbl; k++) {
      vec_data[k] *= fcnOutput;
    }

    c_sin(vec_data, vec_size);
    c_y_size[0] = 1;
    c_y_size[1] = y_size[1];
    cdiff = y_size[1];
    for (k = 0; k < cdiff; k++) {
      b_y_data[k] = y_data[k] * vec_data[k];
    }

    fcnOutput = sum(b_y_data, c_y_size);
    bn[i] = 2.0F / (float)n * fcnOutput;
  }

  /*  plot(y); figure; */
  /*  stem(an); figure; */
  /*  stem(bn); */
}

/*
 * File trailer for music.c
 *
 * [EOF]
 */
