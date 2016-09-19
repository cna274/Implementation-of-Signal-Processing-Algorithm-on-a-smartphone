//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
#include <jni.h>
#include <stdio.h>
#include "L3_4_terminate.h"
#include "L3_4_initialize.h"
#include "L3_4.h"

jfloatArray
Java_com_dsp_matlab_Filters_compute(JNIEnv *env, jobject thiz, jfloatArray input, jint choice)
{
	jfloatArray output = (*env)->NewFloatArray(env, 256);
	float *_output = (*env)->GetFloatArrayElements(env, output, NULL);
	float *_in = (*env)->GetFloatArrayElements(env, input, NULL);
	int fs = 256;
	//compute
	L3_4(_in, fs, choice, _output);

	(*env)->ReleaseFloatArrayElements(env, input, _in, 0);
	(*env)->ReleaseFloatArrayElements(env, output, _output, 0);
	return output;
}

void
Java_com_dsp_matlab_Filters_initialize(JNIEnv *env, jobject thiz)
{
	L3_4_initialize();
}

void
Java_com_dsp_matlab_Filters_finish(JNIEnv *env, jobject thiz)
{
	L3_4_terminate();
}
