//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L3_2.h"
#include "L3_2_terminate.h"
#include "L3_2_emxAPI.h"
#include "L3_2_initialize.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float dvalue, float opvalue) {

    jfloat *pointer;
    jfloatArray result;

    //initialize
  emxArray_real32_T *con;
  emxArray_real32_T *x;
  emxArray_real32_T *h;
  emxInitArray_real32_T(&con, 2);
  emxInitArray_real32_T(&x, 2);
  emxInitArray_real32_T(&h, 2);

    //initialize
    //L3_2_initialize();


    //main function call
    L3_2(dvalue, con, x, h);


    int i;
    if(opvalue == 1) {
        int size = con->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        
        pointer = con->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 2){
        int size = x->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = x->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 3){
        int size = h->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = h->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }

    //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", *con->data++);
    }


  emxDestroyArray_real32_T(h);
  emxDestroyArray_real32_T(x);
  emxDestroyArray_real32_T(con);

    return (result);
}
