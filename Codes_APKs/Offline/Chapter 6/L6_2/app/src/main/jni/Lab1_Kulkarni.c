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
#include "L6_2.h"
#include "L6_2_terminate.h"
#include "L6_2_initialize.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float mode) {

    jfloat *pointer;
    jfloatArray result;
	//jfloat *s;
    int *yd_size = malloc(2 * sizeof(int));
    float *yd_data = malloc(10240 * sizeof(float));
    int *ya_size = malloc(2 * sizeof(int));
    float *ya_data = malloc(1024 * sizeof(int));
    float *xd = malloc(100 * sizeof(float));
    float *xa = malloc(980 * sizeof(float));



    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
	L6_2(mode, xa, xd, ya_data, ya_size, yd_data, yd_size);

    switch ((char)opvalue) {
        case 1:

            pointer = xa;
            result = (*env)->NewFloatArray(env,980);
            (*env)->SetFloatArrayRegion(env, result, 0, 980, pointer);

            break;

        case 2:
            pointer = xd;
            result = (*env)->NewFloatArray(env,100);
            (*env)->SetFloatArrayRegion(env, result, 0, 100, pointer);

            break;

        case 3:
            pointer = ya_data;
            result = (*env)->NewFloatArray(env,1024);
            (*env)->SetFloatArrayRegion(env, result, 0, 1024, pointer);

            break;

        case 4:
            pointer = yd_data;
            result = (*env)->NewFloatArray(env,1280);
            (*env)->SetFloatArrayRegion(env, result, 0, 1280, pointer);

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
