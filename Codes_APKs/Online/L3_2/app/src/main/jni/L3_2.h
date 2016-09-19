/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: L3_2.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 27-Apr-2016 17:57:54
 */

#ifndef __L3_2_H__
#define __L3_2_H__

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "L3_2_types.h"

/* Function Declarations */
extern void L3_2(const float *input_data, const int input_size[], float fs,
                 float frameSize, emxArray_real32_T *output);
extern void L3_2_free(void);
extern void L3_2_init(void);

#endif

/*
 * File trailer for L3_2.h
 *
 * [EOF]
 */
