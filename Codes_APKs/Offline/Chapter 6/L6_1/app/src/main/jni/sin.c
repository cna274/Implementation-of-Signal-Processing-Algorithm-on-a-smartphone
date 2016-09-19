/*
 * File: sin.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 27-Apr-2016 13:23:03
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_1.h"
#include "sin.h"

/* Function Definitions */

/*
 * Arguments    : double x[2001]
 * Return Type  : void
 */
void b_sin(double x[2001])
{
  int k;
  for (k = 0; k < 2001; k++) {
    x[k] = sin(x[k]);
  }
}

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void c_sin(emxArray_real_T *x)
{
  int i0;
  int k;
  i0 = x->size[1];
  for (k = 0; k < i0; k++) {
    x->data[k] = sin(x->data[k]);
  }
}

/*
 * File trailer for sin.c
 *
 * [EOF]
 */
