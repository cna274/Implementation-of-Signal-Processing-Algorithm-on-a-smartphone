//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
#include <jni.h>
#include <stdio.h>
#include "L3_2.h"
#include "L3_2_initialize.h"
#include "L3_2_terminate.h"
#include "L3_2_emxAPI.h"

jfloatArray
Java_com_dsp_matlab_Filters_compute(JNIEnv *env, jobject thiz, jfloatArray input, int fs, int framesize)
{
	jfloatArray output = (*env)->NewFloatArray(env,framesize);
	emxArray_real32_T *outputfromC;
	emxInitArray_real32_T(&outputfromC, 2);

	//float *_output = (*env)->GetFloatArrayElements(env, output, NULL);
	float *_in = (*env)->GetFloatArrayElements(env, input, NULL);

	//float fs = 256;
	jint size[2];
	size[0] = 1; size[1] = framesize;

	//compute
	L3_2(_in, size, fs, framesize, outputfromC);

	//_output = (*env)->NewFloatArray(env,framesize);
	(*env)->SetFloatArrayRegion(env, output, 0, framesize, outputfromC->data);

	(*env)->ReleaseFloatArrayElements(env, input, _in, 0);
	//(*env)->ReleaseFloatArrayElements(env, output, _output, 0);
	emxDestroyArray_real32_T(outputfromC);
	return output;

}

void
Java_com_dsp_matlab_Filters_initialize(JNIEnv *env, jobject thiz)
{
	L3_2_initialize();
}

void
Java_com_dsp_matlab_Filters_finish(JNIEnv *env, jobject thiz)
{
	L3_2_terminate();
}
