//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L6_3.h"
#include "L6_3_terminate.h"
#include "L6_3_emxAPI.h"
#include "L6_3_initialize.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, const float *k, float tone) {

    jfloat *pointer;
    jfloatArray result;
	jfloat *s;
    emxArray_real32_T *y;
    emxArray_real32_T *signal;
    //jfloat *x;
    jfloat * x = malloc(1025*sizeof(float));
    //jfloat tone;
    //const float *k;
	//jfloat xa[2001];
	emxInitArray_real32_T(&y, 2);
    //s = &xa;
	int i,size;

    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);

    L6_3(k, tone, x, y );

    switch ((char)opvalue) {
        case 1:

            result = (*env)->NewFloatArray(env,1025);

            (*env)->SetFloatArrayRegion(env, result, 0, 1025, x);

            pointer = x;
            break;

        case 2:
            
			signal = y;
            size = signal->size[1];

            result = (*env)->NewFloatArray(env,size);
            pointer = signal->data;

            (*env)->SetFloatArrayRegion(env, result, 0, size, pointer);

            break;
    }

    


        //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

    //L5_1_terminate();
	emxDestroyArray_real32_T(y);

    return (result);
}
