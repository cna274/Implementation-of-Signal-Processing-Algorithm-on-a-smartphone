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
#include "music.h"
#include "music_terminate.h"
#include "music_initialize.h"


jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float A1, float A2, float A3, float A4, float A5, float A6, float freq1,
        float freq2,float freq3,float freq4,float freq5,float freq6,float option) {

    float *pointer = malloc(101*sizeof(float));
    jfloatArray result;
    //jfloat *s;
    float *bn = malloc(5*sizeof(float));;
    float *an = malloc(5*sizeof(float));;
    float *a0 = malloc(1*sizeof(float));;
    int *y_size = malloc(2*sizeof(float));;
    float *y_data = malloc(101*sizeof(float));;
    int i;
    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
    music(A1, A2, A3, A4, A5, A6, freq1, freq2, freq3, freq4, freq5, freq6, option, y_data, y_size, an, bn, a0);

    switch ((char)opvalue) {
        case 1:

            pointer = an;
            result = (*env)->NewFloatArray(env,5);
            (*env)->SetFloatArrayRegion(env, result, 0, 5, pointer);

            break;

        case 2:
            pointer = bn;
            result = (*env)->NewFloatArray(env,5);
            (*env)->SetFloatArrayRegion(env, result, 0, 5, pointer);

            break;

        case 3:
            pointer = y_data;
            result = (*env)->NewFloatArray(env,101);
            (*env)->SetFloatArrayRegion(env, result, 0, 101, pointer);

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
