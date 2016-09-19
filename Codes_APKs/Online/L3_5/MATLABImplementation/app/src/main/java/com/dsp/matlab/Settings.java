//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import android.media.AudioFormat;
import android.media.MediaRecorder;

public class Settings {
	
	public static final WaveFrame STOP = new WaveFrame(new float[1], -32768);

	//recorder settings
	public static final int FORMAT = AudioFormat.ENCODING_PCM_16BIT;
	public static final int SOURCE = MediaRecorder.AudioSource.DEFAULT;
	public static int Fs = 8000;
	public static int blockSize = 256;
	public static int delay = 100;
	public static int option = 0;
	public static float Resistance = 750;
	public static float Inductance = (float) 0.01;
	public static float Capacitance = (float) 0.000001;
	public static boolean playback = false;
	public static boolean output = false;
	public static int debugLevel = 4;
	public static int secondConstant = Fs/blockSize;
	
	public static CharSequence[] samplingRates = {"8000 Hz"};
	public static CharSequence[] samplingRateValues = {"8000"};
	
	public static void setDelay(int time){
		delay = time;
	}

	public static void setBlockSize(int size){
		blockSize = size;
	}

	public static void setResistance(float r){
		Resistance = r;
	}

	public static void setInductance(float l){
		Inductance = l;
	}

	public static void setCapacitance(float c){
		Capacitance = c;
	}

	public static void setOption(int choice){
		option = choice;
	}
	
	public static void setSamplingFrequency(int freq){
		Fs = freq;
		secondConstant = Fs/blockSize;
	}
	
	public static void setPlayback(boolean flag){
		playback = flag;
	}
	
	public static void setOutput(int stream){
		output = false; //filtered signal
		if(stream == 1){
			output = true; //original signal
		}
	}
	
	public static String getOutput(){
		if(playback == false){
			return "None";
		} else if (output == true){
			return "Original";
		} else {
			return "Filtered";
		}
	}
	
	public static void setDebugLevel(int level){
		debugLevel = level;
	}
	
	public static void setRates(CharSequence[] rates){
		samplingRates = rates;
	}
	
	public static void setRateValues(CharSequence[] rateValues){
		samplingRateValues = rateValues;
	}
}
