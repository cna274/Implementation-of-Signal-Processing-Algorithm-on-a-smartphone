//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L5_1.h"
#include "L5_1_terminate.h"
#include "L5_1_initialize.h"
#include "L5_1_emxAPI.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float a, float a1, float a2, float del1, float del2, float d1, float d2,
        float mode1, float mode2, float mode3, float mode4) {

    jfloat *pointer;
    jfloatArray result;

    //initialize

    //initialize
    //L5_1_initialize();
    emxArray_real32_T *signal;
    emxArray_real32_T *x1;
    emxArray_real32_T *x2;
    emxArray_real32_T *x;
    emxArray_creal32_T *b_y1;
    emxArray_creal32_T *y2;
    emxArray_creal32_T *y;
    emxArray_creal32_T *y3;
    emxArray_real32_T *x3;
    emxArray_real32_T *y1_mag;
    emxArray_real32_T *y1_phase;
    emxArray_real32_T *y2_mag;
    emxArray_real32_T *y2_phase;
    emxArray_real32_T *y3_mag;
    emxArray_real32_T *y3_phase;
    emxArray_real32_T *y_mag;
    emxArray_real32_T *y_phase;
    emxArray_real32_T *f;
    //float a;
    emxInitArray_real32_T(&x1, 2);
    emxInitArray_real32_T(&x2, 2);
    emxInitArray_real32_T(&x, 2);
    emxInitArray_real32_T(&x3, 2);
    emxInitArray_real32_T(&y1_mag, 2);
    emxInitArray_real32_T(&y1_phase, 2);
    emxInitArray_real32_T(&y2_mag, 2);
    emxInitArray_real32_T(&y2_phase, 2);
    emxInitArray_real32_T(&y3_mag, 2);
    emxInitArray_real32_T(&y3_phase, 2);
    emxInitArray_real32_T(&y_mag, 2);
    emxInitArray_real32_T(&y_phase, 2);


    //main function call
    L5_1(a, a1, a2, del1, del2, d1, d2, mode1, mode2, mode3, mode4, x1, x2, x, x3, y1_mag, y1_phase,
         y2_mag, y2_phase, y3_mag, y3_phase, y_mag, y_phase);

    switch ((char)opvalue) {
        case 1:
            signal = x;
            break;

        case 2:
            signal = x1;
            break;

        case 3:
            signal = x2;
            break;

        case 4:
            signal = x3;
            break;

        case 5:
            signal = y1_mag;
            break;

        case 6:
            signal = y1_phase;
            break;

        case 7:
            signal = y2_mag;
            break;

        case 8:
            signal = y2_phase;
            break;

        case 9:
            signal = y3_mag;
            break;

        case 10:
            signal = y3_phase;
            break;

        case 11:
            signal = y_mag;
            break;

        case 12:
            signal = y_phase;
            break;
    }

    int i;
    int size = signal->size[1];
    result = (*env)->NewFloatArray(env,size);
    pointer = signal->data;

    (*env)->SetFloatArrayRegion(env, result, 0, size, signal->data);


        //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

    //L5_1_terminate();
    emxDestroyArray_real32_T(y_phase);
    emxDestroyArray_real32_T(y_mag);
    emxDestroyArray_real32_T(y3_phase);
    emxDestroyArray_real32_T(y3_mag);
    emxDestroyArray_real32_T(y2_phase);
    emxDestroyArray_real32_T(y2_mag);
    emxDestroyArray_real32_T(y1_phase);
    emxDestroyArray_real32_T(y1_mag);
    emxDestroyArray_real32_T(x3);
    emxDestroyArray_real32_T(x);
    emxDestroyArray_real32_T(x2);
    emxDestroyArray_real32_T(x1);

    return (result);
}
