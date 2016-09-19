//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L5_2.h"
#include "L5_2_terminate.h"
#include "L5_2_initialize.h"
#include "L5_2_emxAPI.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float fc) {

    jfloat *pointer;
    jfloatArray result;

    emxArray_real32_T *signal;
    emxArray_real32_T *b_y1;
    emxArray_real32_T *y2;
    emxArray_real32_T *y3;
    emxArray_real32_T *y4;
    emxArray_real32_T *z1;
    emxArray_real32_T *z2;
    emxArray_real32_T *z3;
    emxArray_creal32_T *z4;

    //initialize
    emxInitArray_real32_T(&b_y1, 2);
    emxInitArray_real32_T(&y2, 2);
    emxInitArray_real32_T(&y3, 2);
    emxInitArray_real32_T(&y4, 2);
    emxInitArray_real32_T(&z1, 2);
    emxInitArray_real32_T(&z2, 2);
    emxInitArray_real32_T(&z3, 2);
    emxInitArray_creal32_T(&z4, 2);



    //main function call
    L5_2(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);

    switch ((char)opvalue) {
        case 1:
            signal = z1;
            break;

        case 2:
            signal = z2;
            break;

        case 3:
            signal = z3;
            break;

        case 4:
            signal = z1;
            break;

        case 5:
            signal = b_y1;
            break;

        case 6:
            signal = y2;
            break;

        case 7:
            signal = y3;
            break;

        case 8:
            signal = y4;
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
    emxDestroyArray_creal32_T(z4);
    emxDestroyArray_real32_T(z3);
    emxDestroyArray_real32_T(z2);
    emxDestroyArray_real32_T(z1);
    emxDestroyArray_real32_T(y4);
    emxDestroyArray_real32_T(y3);
    emxDestroyArray_real32_T(y2);
    emxDestroyArray_real32_T(b_y1);

    return (result);
}
