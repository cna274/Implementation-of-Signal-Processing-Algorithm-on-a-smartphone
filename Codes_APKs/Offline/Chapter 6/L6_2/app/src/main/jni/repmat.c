/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: repmat.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Apr-2016 03:17:05
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L6_2.h"
#include "repmat.h"

/* Function Definitions */

/*
 * Arguments    : const float a_data[]
 *                const int a_size[2]
 *                float b_data[]
 *                int b_size[2]
 * Return Type  : void
 */
void repmat(const float a_data[], const int a_size[2], float b_data[], int
            b_size[2])
{
  int ncols;
  int jtilecol;
  int ibtile;
  int jcol;
  b_size[0] = 1;
  b_size[1] = (short)(a_size[1] * 10);
  ncols = a_size[1];
  for (jtilecol = 0; jtilecol < 10; jtilecol++) {
    ibtile = jtilecol * ncols;
    for (jcol = 1; jcol <= ncols; jcol++) {
      b_data[(ibtile + jcol) - 1] = a_data[jcol - 1];
    }
  }
}

/*
 * File trailer for repmat.c
 *
 * [EOF]
 */
