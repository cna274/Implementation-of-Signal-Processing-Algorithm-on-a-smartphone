//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L3_1_types.h"
#include "L3_1_terminate.h"
#include "L3_1_emxAPI.h"
#include "L3_1_initialize.h"
#include "L3_1.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float avalue, float bvalue, float dvalue, float opvalue) {

    jfloat *pointer;
    jfloatArray result;

    //initialize
    emxArray_real32_T *y;
    emxArray_real32_T *y_ac;
    emxArray_real32_T *x1;
    emxArray_real32_T *x2;
    float MSE;
    emxInitArray_real32_T(&y, 2);
    emxInitArray_real32_T(&y_ac, 2);
    emxInitArray_real32_T(&x1, 2);
    emxInitArray_real32_T(&x2, 2);

    //initialize
    //L3_1_initialize();


    //main function call
    L3_1(avalue,  bvalue, dvalue, y, y_ac, &MSE ,x1,x2);


    int i;
    if(opvalue == 1) {
        int size = y->size[1]+1;
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        temp[0] = MSE;
        pointer = y->data;
        for(i=1;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 2){
        int size = y_ac->size[1]+1;
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        temp[0] = MSE;
        pointer = y_ac->data;
        for(i=1;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 3){
        int size = x1->size[1]+1;
        float temp[size];
        result = (*env)->NewFloatArray(env,size);

        temp[0] = MSE;
        pointer = x1->data;
        for(i=1;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 4){
        int size = x2->size[1]+1;
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        temp[0] = MSE;
        pointer = x2->data;
        for(i=1;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }

    //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", *y->data++);
    }


    emxDestroyArray_real32_T(x2);
    emxDestroyArray_real32_T(x1);
    emxDestroyArray_real32_T(y_ac);
    emxDestroyArray_real32_T(y);

    return (result);
}
