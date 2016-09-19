//
// Created by Srinivas on 1/18/2016.
//

#include <jni.h>
#include <android/log.h>
#include "L4_2.h"
#include "L4_2_terminate.h"
#include "L4_2_emxAPI.h"
#include "L4_2_initialize.h"

jfloatArray Java_com_dsp_helloworld_MainActivity_getArray (
        JNIEnv *env, jobject thiz, float opvalue, float A, float T, float N, float w, float R, float C) {

    jfloat *pointer;
    jfloatArray result;

	emxArray_real32_T *XT;
	emxArray_real32_T *an;
	emxArray_real32_T *bn;
	emxArray_real32_T *VCcos_m;
	emxArray_real32_T *VCcos_a;
	emxArray_real32_T *VCsin_m;
	emxArray_real32_T *VCsin_a;
	emxArray_real32_T *signal;
	float VCdc;
	float a0;
	emxInitArray_real32_T(&XT, 2);
	emxInitArray_real32_T(&an, 2);
	emxInitArray_real32_T(&bn, 2);
	emxInitArray_real32_T(&VCcos_m, 2);
	emxInitArray_real32_T(&VCcos_a, 2);
	emxInitArray_real32_T(&VCsin_m, 2);
	emxInitArray_real32_T(&VCsin_a, 2);
	emxInitArray_real32_T(&signal, 2);


	int i,size;

    //main function call
    //L4_1(fc, b_y1, y2, y3, y4, z1, z2, z3, z4);
	L4_2(A, T, N, w, R, C, XT, an, bn, &a0, &VCdc, VCcos_m, VCcos_a, VCsin_m, VCsin_a);

    switch ((char)opvalue) {
        case 1:
            
			signal = XT;
            break;

        case 2:
            
			signal = an;
			break;

        case 3:

			signal = bn;
            break;

        case 4:
			signal = VCcos_m;
			break;

		case 5:
			signal = VCcos_a;
			break;

		case 6:
			signal = VCsin_m;
			break;

		case 7:
			signal = VCsin_a;
			break;

    }

	size = signal->size[1];

	result = (*env)->NewFloatArray(env,size);
	pointer = signal->data;
    
    (*env)->SetFloatArrayRegion(env, result, 0, size, pointer);


        //int i;
    for (i=0;i<19;i++) {

        __android_log_print(ANDROID_LOG_ERROR,
                            "HelloWorld", "%e", pointer[i]);
    }

	emxDestroyArray_real32_T(VCsin_a);
	emxDestroyArray_real32_T(VCsin_m);
	emxDestroyArray_real32_T(VCcos_a);
	emxDestroyArray_real32_T(VCcos_m);
	emxDestroyArray_real32_T(bn);
	emxDestroyArray_real32_T(an);
	emxDestroyArray_real32_T(XT);

    return (result);
}
