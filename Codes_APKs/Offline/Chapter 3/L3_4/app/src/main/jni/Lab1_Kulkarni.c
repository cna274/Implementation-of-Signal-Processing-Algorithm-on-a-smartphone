//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L3_4.h"
#include "L3_4_terminate.h"
#include "L3_4_emxAPI.h"
#include "L3_4_initialize.h"


jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float dvalue, float opvalue) {

    jfloat *pointer;
    jfloatArray result;

    //initialize
  emxArray_real32_T *x;
  emxArray_real32_T *h1;
  emxArray_real32_T *h2;
  emxArray_real32_T *b_y1;
  emxArray_real32_T *y2;
  emxArray_real32_T *y3;
  emxArray_real32_T *y4;
  emxArray_real32_T *y5;
  emxArray_real32_T *y6;
  emxInitArray_real32_T(&x, 2);
  emxInitArray_real32_T(&h1, 2);
  emxInitArray_real32_T(&h2, 2);
  emxInitArray_real32_T(&b_y1, 2);
  emxInitArray_real32_T(&y2, 2);
  emxInitArray_real32_T(&y3, 2);
  emxInitArray_real32_T(&y4, 2);
  emxInitArray_real32_T(&y5, 2);
  emxInitArray_real32_T(&y6, 2);



    //initialize
    //L3_2_initialize();


    //main function call
    L3_4(dvalue, x, h1, h2, b_y1, y2, y3, y4, y5, y6);


    int i;
    if(opvalue == 1) {
        int size = b_y1->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        
        pointer = b_y1->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 2){
        int size = y2->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = y2->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
    else if (opvalue == 3){
        int size = y3->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = y3->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
	else if (opvalue == 4){
        int size = y4->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = y4->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
	else if (opvalue == 5){
        int size = y5->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = y5->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
	else if (opvalue == 6){
        int size = y6->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = y6->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
	else if (opvalue == 7){
        int size = x->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = x->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
	else if (opvalue == 8){
        int size = h1->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = h1->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }
	else if (opvalue == 9){
        int size = h2->size[1];
        float temp[size];
        result = (*env)->NewFloatArray(env,size);
        pointer = h2->data;
        for(i=0;i<size;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, size, temp);
    }

    //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }


  emxDestroyArray_real32_T(y6);
  emxDestroyArray_real32_T(y5);
  emxDestroyArray_real32_T(y4);
  emxDestroyArray_real32_T(y3);
  emxDestroyArray_real32_T(y2);
  emxDestroyArray_real32_T(b_y1);
  emxDestroyArray_real32_T(h2);
  emxDestroyArray_real32_T(h1);
  emxDestroyArray_real32_T(x);  
	return (result);
}
