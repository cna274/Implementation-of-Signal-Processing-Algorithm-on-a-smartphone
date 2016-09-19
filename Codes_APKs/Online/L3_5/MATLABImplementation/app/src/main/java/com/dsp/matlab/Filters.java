//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

public class Filters {

	static {
		System.loadLibrary("matlabNative");
	}

	//JNI Method Calls	
	public static native float[] compute(float[] in, float fs, float w2, float R, float L, float C);
	public static native void initialize();
	public static native void finish();
}
