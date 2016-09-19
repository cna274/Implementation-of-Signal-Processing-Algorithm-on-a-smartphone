/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filter.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 12:21:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Echo.h"
#include "filter.h"
#include "rdivide.h"
#include "isfinite.h"

/* Function Definitions */

/*
 * Arguments    : float b[1997]
 *                float a[999]
 *                const double x[999]
 *                float y[999]
 *                float zf[1996]
 * Return Type  : void
 */
void filter(float b[1997], float a[999], const double x[999], float y[999],
            float zf[1996])
{
  float a1;
  int k;
  float dbuffer[1997];
  int j;
  a1 = a[0];
  if ((!b_isfinite(a[0])) || (a[0] == 0.0F) || (!(a[0] != 1.0F))) {
  } else {
    for (k = 0; k < 1997; k++) {
      b[k] = rdivide(b[k], a1);
    }

    for (k = 0; k < 998; k++) {
      a[k + 1] = rdivide(a[k + 1], a1);
    }

    a[0] = 1.0F;
  }

  memset(&dbuffer[1], 0, 1996U * sizeof(float));
  for (j = 0; j < 999; j++) {
    for (k = 0; k < 1996; k++) {
      dbuffer[k] = dbuffer[k + 1];
    }

    dbuffer[1996] = 0.0F;
    for (k = 0; k < 1997; k++) {
      dbuffer[k] += (float)x[j] * b[k];
    }

    for (k = 0; k < 998; k++) {
      dbuffer[k + 1] -= dbuffer[0] * a[k + 1];
    }

    y[j] = dbuffer[0];
  }

  memcpy(&zf[0], &dbuffer[1], 1996U * sizeof(float));
}

/*
 * File trailer for filter.c
 *
 * [EOF]
 */
