//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L4_1.h"
#include "L4_1_terminate.h"
#include "L4_1_emxAPI.h"
#include "L4_1_initialize.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float A, float T, float N, float w) {

    jfloat *pointer;
    jfloatArray result;
	
	emxArray_real32_T *signal;
	emxArray_real32_T *XT;
	emxArray_real32_T *x_hat;
	emxArray_real32_T *an;
	emxArray_real32_T *bn;
	emxArray_real32_T *error;
	float avg_error;
	float max_error;
	float a0;
	emxInitArray_real32_T(&XT, 2);
	emxInitArray_real32_T(&x_hat, 2);
	emxInitArray_real32_T(&an, 2);
	emxInitArray_real32_T(&bn, 2);
	emxInitArray_real32_T(&error, 2);

	emxInitArray_real32_T(&signal, 2);

	int i,size;

    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
	L4_1(A, T, N, w, XT, x_hat, an, bn, &a0, error, &max_error, &avg_error);

    switch ((char)opvalue) {
        case 1:
            
			signal = XT;
			

			size = signal->size[1];

			result = (*env)->NewFloatArray(env,size+3);
			pointer = signal->data;
			i = size;

			pointer[i+1] = a0;
			pointer[i+2] = avg_error;
			pointer[i+3] = max_error;

            break;

        case 2:
            
			signal = x_hat;
            i = size;
			size = signal->size[1];

			result = (*env)->NewFloatArray(env,size+3);
			pointer = signal->data;
	
			pointer[i+1] = a0;

			pointer[i+2] = avg_error;
			pointer[i+3] = max_error;
			
			break;

        case 3:

			signal = error;

			size = signal->size[1];
			i = size;

			result = (*env)->NewFloatArray(env,size+3);
			pointer = signal->data;

			pointer[i+1] = a0;

			pointer[i+2] = avg_error;
			pointer[i+3] = max_error;

            break;

        case 4:


			signal = an;

			size = signal->size[1];
			i = size;

			result = (*env)->NewFloatArray(env,size+3);
			pointer = signal->data;

			pointer[i+1] = a0;

			pointer[i+2] = avg_error;
			pointer[i+3] = max_error;

			break;

		case 5:


			signal = bn;

			size = signal->size[1];
			i = size;

			result = (*env)->NewFloatArray(env,size+3);
			pointer = signal->data;

			pointer[i+1] = a0;

			pointer[i+2] = avg_error;
			pointer[i+3] = max_error;

			break;

	}

    
    (*env)->SetFloatArrayRegion(env, result, 0, size+3, pointer);


        //int i;
    for (i=signal->size[1]+3;i<(signal->size[1]);i--) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

    //L5_1_terminate();
	emxDestroyArray_real32_T(error);
	emxDestroyArray_real32_T(bn);
	emxDestroyArray_real32_T(an);
	emxDestroyArray_real32_T(x_hat);
	emxDestroyArray_real32_T(XT);

	return (result);
}
