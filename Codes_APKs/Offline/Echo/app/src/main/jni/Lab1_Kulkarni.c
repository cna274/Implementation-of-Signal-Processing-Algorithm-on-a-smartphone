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
#include <malloc.h>
#include "Echo.h"
#include "Echo_terminate.h"
#include "Echo_initialize.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float mode, float delay) {

    jfloat *pointer;
    jfloatArray result;
	//jfloat *s;
    float *Q = malloc(999 * sizeof(float));
    float *x_delay = malloc(999* sizeof(float));
    float *x = malloc(999 * sizeof(float));

    /*int *yd_size = malloc(2 * sizeof(int));
    float *yd_data = malloc(10240 * sizeof(float));
    int *ya_size = malloc(2 * sizeof(int));
    float *ya_data = malloc(1024 * sizeof(int));
    float *xd = malloc(100 * sizeof(float));
    float *xa = malloc(980 * sizeof(float));
*/


    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
    Echo(mode, delay, x, x_delay, Q);

    switch ((char)opvalue) {
        case 1:

            pointer = x;
            result = (*env)->NewFloatArray(env,999);
            (*env)->SetFloatArrayRegion(env, result, 0, 999, pointer);

            break;

        case 2:
            pointer = x_delay;
            result = (*env)->NewFloatArray(env,999);
            (*env)->SetFloatArrayRegion(env, result, 0, 999, pointer);

            break;

        case 3:
            pointer = Q;
            result = (*env)->NewFloatArray(env,999);
            (*env)->SetFloatArrayRegion(env, result, 0, 999, pointer);

            break;

    }




    int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

    //L5_1_terminate();
	//emxDestroyArray_real32_T(x_recon);

    return (result);
}
