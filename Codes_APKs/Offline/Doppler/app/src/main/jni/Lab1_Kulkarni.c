//
// Created by Srinivas on 1/18/2016.
//
/*                float xa[980]
*                float xd[100]
*                float ya_data[]
*                int ya_size[2]
*                float yd_data[]
*                int yd_size[2]
*/
#include <jni.h>
#include <android/log.h>
#include "rt_nonfinite.h"
#include "Doppler.h"
#include "Doppler_terminate.h"
#include "Doppler_initialize.h"
#include "rtwtypes.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float a, float b, float freq) {

    float *pointer;
    pointer = malloc(101* sizeof(float));
    real32_T *ptr_freq ;
    ptr_freq = malloc(128* sizeof(float));
    jfloatArray result;
    //jfloat *s;
    float *decre = malloc(128* sizeof(float));
    float *incre = malloc(128* sizeof(float));
    float *input = malloc(128* sizeof(float));
    float *y2 = malloc(101* sizeof(float));
    float *b_y1 = malloc(101* sizeof(float));
    float *x = malloc(101* sizeof(float));

    int i;
    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
    Doppler(a,b,freq, x, b_y1, y2, input, incre, decre);

    switch ((char)opvalue) {
        case 1:

            pointer = x;
            result = (*env)->NewFloatArray(env,101);
            (*env)->SetFloatArrayRegion(env, result, 0, 101, pointer);

            break;

        case 2:
            pointer = b_y1;
            result = (*env)->NewFloatArray(env,101);
            (*env)->SetFloatArrayRegion(env, result, 0, 101, pointer);

            break;

        case 3:
            pointer = y2;
            result = (*env)->NewFloatArray(env,101);
            (*env)->SetFloatArrayRegion(env, result, 0, 101, pointer);

            break;


        case 4:

            ptr_freq = input;
            result = (*env)->NewFloatArray(env,128);
            (*env)->SetFloatArrayRegion(env, result, 0, 128, ptr_freq);

        case 5:

                ptr_freq = incre;

            result = (*env)->NewFloatArray(env,128);
            (*env)->SetFloatArrayRegion(env, result, 0, 128, ptr_freq);

            break;

        case 6:

            ptr_freq = decre;
            result = (*env)->NewFloatArray(env,128);
            (*env)->SetFloatArrayRegion(env, result, 0, 128, ptr_freq);

            break;

    }


//int i;
  //  for (i=0;i<19;i++) {

    //    __android_log_print(ANDROID_LOG_ERROR,
      //                      "HelloWorld", "%e", pointer[i]);
    //}

    //L5_1_terminate();
	//emxDestroyArray_real32_T(x_recon);

    return (result);
}
