/*
 * File: round.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 27-Apr-2016 13:23:03
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_1.h"
#include "round.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void b_round(emxArray_real_T *x)
{
  int i1;
  int k;
  i1 = x->size[1];
  for (k = 0; k < i1; k++) {
    x->data[k] = rt_roundd_snf(x->data[k]);
  }
}

/*
 * File trailer for round.c
 *
 * [EOF]
 */
