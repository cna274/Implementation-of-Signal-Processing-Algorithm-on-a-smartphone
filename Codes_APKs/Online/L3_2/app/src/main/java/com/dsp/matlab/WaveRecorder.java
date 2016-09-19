//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

import android.media.AudioFormat;
import android.media.AudioRecord;

public class WaveRecorder implements Runnable{

	private short[] abuf_short;
	private AtomicBoolean isRecording;
	private BlockingQueue<WaveFrame> output;
	private AudioRecord recorder;
	private int recBufLen;
	private long currentFrame, skipCount;
	private long timeout;
	private Thread recThread;
	private boolean noSkips;
	private Monitor main;
	
	public WaveRecorder(Monitor main, BlockingQueue<WaveFrame> output){
		this.output = output;
		this.main = main;
		isRecording = new AtomicBoolean();
		currentFrame = 0;
		skipCount = 0;
		
		timeout = (Settings.blockSize*100000)/Settings.Fs;
		
		recBufLen = 5 * AudioRecord.getMinBufferSize(Settings.Fs, AudioFormat.CHANNEL_IN_MONO, Settings.FORMAT);
		recorder = new AudioRecord(Settings.SOURCE, Settings.Fs, AudioFormat.CHANNEL_IN_MONO, Settings.FORMAT, recBufLen);
		
		recThread = new Thread(this);
		recThread.start();
	}
	
	public void stopRecording(){
		isRecording.set(false);
	}
	
	public boolean isRecording(){
		return isRecording.get();
	}

	public void run() {
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
        
        try{
        	if(recorder != null){
        		recorder.stop();
        		recorder.startRecording();
        		isRecording.set(true);
        	}
        } catch (IllegalStateException e){
        	isRecording.set(false);
        }
        
		try {
			loop:while(true){
				if(isRecording.get()) {
					abuf_short = new short[Settings.blockSize];
					recorder.read(abuf_short, 0, Settings.blockSize);
					noSkips = output.offer(new WaveFrame(abuf_short, currentFrame), timeout, TimeUnit.MICROSECONDS);
					currentFrame++;
					if(!noSkips) {
						skipCount++;
					}
					if((skipCount != 0) && (currentFrame % Settings.secondConstant == 0)){
						main.notifySkips(skipCount);
						skipCount = 0;
					}
				} else {
					output.put(Settings.STOP);
					break loop;
				}
			}
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
			e.printStackTrace();
		}
		
		try{
			if(recorder != null){
				recorder.stop();
	        	recorder.release();
	        	recorder = null;
			}
        } catch (IllegalStateException e){
        	e.printStackTrace();
        }
		
	}
	
    public static void checkSamplingRate(){
    	
    	int[] rates =  {8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000, 96000, 192000};
    	List<String> listRateValues = new ArrayList<String>();
    	List<String> listRates = new ArrayList<String>();
    	AudioRecord testRecorder = null;
    	boolean good = false;
    	
    	for (int rate : rates) {
    	    int bufferSize = AudioRecord.getMinBufferSize(rate, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);
	    	if (bufferSize != AudioRecord.ERROR || bufferSize != AudioRecord.ERROR_BAD_VALUE) {
	    		//Sampling rate should be supported
	    		
	    		try{
	    			good = true;
	    			testRecorder = new AudioRecord(Settings.SOURCE, rate, AudioFormat.CHANNEL_IN_MONO, Settings.FORMAT, bufferSize);
	    			testRecorder.stop();
	    			testRecorder.release();
		    		testRecorder = null;
	    		}catch(Exception e){
	    			good = false;
	    		}
	    		
	    		if(good){
		    		listRateValues.add(Integer.toString(rate));
		    		listRates.add(rate + " Hz");
	    		}
	    	}
    	}
    	Settings.setRates(listRates.toArray(new CharSequence[listRates.size()]));
    	Settings.setRateValues(listRateValues.toArray(new CharSequence[listRateValues.size()]));
	}
}
