/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L5_2_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Apr-2016 17:09:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "L5_2.h"
#include "L5_2_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void L5_2_initialize(void)
{
  rt_InitInfAndNaN(8U);
  c_eml_rand_mt19937ar_stateful_i();
}

/*
 * File trailer for L5_2_initialize.c
 *
 * [EOF]
 */
