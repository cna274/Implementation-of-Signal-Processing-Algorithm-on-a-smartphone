//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L6_1.h"
#include "L6_1_terminate.h"
#include "L6_1_emxAPI.h"
#include "L6_1_initialize.h"

jdoubleArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float b, float fs, float f, float A, float q) {

    jdouble *pointer;
    jdoubleArray result;
	jfloat *s;
    emxArray_real_T *xd1;
    emxArray_real_T *x_recon;
    emxArray_real_T *signal;
	jdouble *xa;
    xa = malloc(2001*sizeof(double));
    emxInitArray_real_T(&xd1, 2);
    emxInitArray_real_T(&x_recon, 2);
    emxInitArray_real_T(&signal, 2);

    //s = &xa;
	int i,size;

    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
	L6_1(b, fs, f, A, q, xa, xd1, x_recon);

    switch ((char)opvalue) {
        case 1:

            pointer = xa;

            result = (*env)->NewDoubleArray(env,2001);

            (*env)->SetDoubleArrayRegion(env, result, 0, 2001, xa);

            break;

        case 2:
            
			//signal->data = xd1->data;
            //size = signal->size[1];

            result = (*env)->NewDoubleArray(env,401);
            //pointer = signal->data;

            (*env)->SetDoubleArrayRegion(env, result, 0, 401, xd1->data);

            break;

        case 3:

            //signal->data = x_recon->data;
            //size = signal->size[1];

            result = (*env)->NewDoubleArray(env,2001);
            //pointer = signal->data;

            (*env)->SetDoubleArrayRegion(env, result, 0, 2001, x_recon->data);

            break;

    }

    


        //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

    //L5_1_terminate();
    //emxDestroyArray_real_T(x_recon);
    //emxDestroyArray_real_T(xd1);

    return (result);
}
