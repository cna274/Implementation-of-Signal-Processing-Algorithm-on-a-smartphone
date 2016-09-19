/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filter.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 28-Apr-2016 12:21:36
 */

#ifndef __FILTER_H__
#define __FILTER_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Echo_types.h"

/* Function Declarations */
extern void filter(float b[1997], float a[999], const double x[999], float y[999],
                   float zf[1996]);

#endif

/*
 * File trailer for filter.h
 *
 * [EOF]
 */
