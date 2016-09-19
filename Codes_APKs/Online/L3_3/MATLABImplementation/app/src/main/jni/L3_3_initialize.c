/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_3_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 27-Apr-2016 23:43:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L3_3.h"
#include "L3_3_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void L3_3_initialize(void)
{
  rt_InitInfAndNaN(8U);
  L3_3_init();
}

/*
 * File trailer for L3_3_initialize.c
 *
 * [EOF]
 */
