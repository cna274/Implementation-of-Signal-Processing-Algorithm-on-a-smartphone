//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L3_3.h"
#include "L3_3_terminate.h"
#include "L3_3_emxAPI.h"
#include "L3_3_initialize.h"


jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float dvalue, float opvalue) {

    jfloat *pointer;
    jfloatArray result;

    //initialize
  emxArray_real32_T *y;
  emxArray_real32_T *x1;
  emxArray_real32_T *x2;
  emxInitArray_real32_T(&y, 2);
  emxInitArray_real32_T(&x1, 2);
  emxInitArray_real32_T(&x2, 2);


    //initialize
    //L3_2_initialize();


    //main function call
    L3_3(dvalue, y, x1, x2);


    int i;
    if(opvalue == 1) {
        int size = y->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        
        pointer = y->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 2){
        int size = x1->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = x1->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 3){
        int size = x2->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = x2->data;
        for(i=0;i<size;i++){
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
  emxDestroyArray_real32_T(y);
    
	return (result);
}
