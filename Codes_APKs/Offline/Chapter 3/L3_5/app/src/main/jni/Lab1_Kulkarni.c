//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L3_5.h"
#include "L3_5_terminate.h"
#include "L3_5_initialize.h"


jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float w1, float w2, float A, float R, float L, float C) {

    jfloat *pointer;
    jfloatArray result;

    //initialize
    jfloatArray y[1000] = {0};

    //initialize
    L3_5_initialize();


    //main function call
    L3_5( w1, w2, A, R, L, C, &y);


    int i;

        jfloat temp[1000];
        pointer = y;
		result = (*env)->NewFloatArray(env,1000);
        for(i=0;i<1000;i++){
            temp[i] = pointer[i];
        }
        (*env)->SetFloatArrayRegion(env, result, 0, 1000, temp);

    if (result == NULL) {
        //LOGE("Cannot allocate JNI Byte Array");
        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%d", i);
        return NULL; /* out of memory error thrown */
    }

        //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

    L3_5_terminate();
  	return (result);
}
