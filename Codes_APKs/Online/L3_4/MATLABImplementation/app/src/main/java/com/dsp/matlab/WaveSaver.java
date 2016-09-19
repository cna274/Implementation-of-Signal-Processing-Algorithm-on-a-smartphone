//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.concurrent.BlockingQueue;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

public class WaveSaver implements Runnable{
	
	private FileOutputStream audioWriter, debugWriter;
	private BlockingQueue<WaveFrame> outputQueue;
	private boolean saveData, debugData;
	private long framecount;
	private String outputName;
	private Thread writer;
	private Monitor main;
	private WaveFrame outputFrame;
	private AudioTrack sound;
	private int updateRate;
	
	public WaveSaver(Monitor main, String outputName, BlockingQueue<WaveFrame> outputQueue) {
		this.main = main;
		this.outputName = outputName;
		this.outputQueue = outputQueue;
		framecount = 0;
		updateRate = Settings.secondConstant;
		
		switch(Settings.debugLevel){
			case(1): {
						enablePCMOutput();
			}
			case(2): {	enableDebugOutput();
						break;
			}
			case(3): {	enablePCMOutput();
						break;
			}
			case(4): break;
			default: break;
			
		}
		
		if(Settings.playback){
			int size = 5 * AudioTrack.getMinBufferSize(Settings.Fs, AudioFormat.CHANNEL_OUT_MONO, Settings.FORMAT);
			sound = new AudioTrack(AudioManager.STREAM_MUSIC, Settings.Fs, AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT, size, AudioTrack.MODE_STREAM);
		}
		
        writer = new Thread(this);
        writer.start();
	}
	
	public long getFrameCount(){
		return framecount;
	}
	
	public String getOutputName(){
		return outputName;
	}
	
	private void enablePCMOutput() {
		try {
			audioWriter = new FileOutputStream (Utilities.getFile(outputName + ".pcm"));
			saveData = true;
		} catch (Exception e){
			saveData = false;
		}
	}
	
	private void enableDebugOutput() {
		try {
			debugWriter = new FileOutputStream (Utilities.getFile(outputName + ".txt"));
			debugData = true;
		} catch (IOException e){
			debugData = false;
			e.printStackTrace();
		}
	}

	public void run() {
		long elapsed = 0;
		if(Settings.playback) {
			sound.play();
		}
		
		Log.e("Test", saveData+ "");
		
		loop:while(true) {
			outputFrame = null;
			
			try {
				outputFrame = outputQueue.take();
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
				e.printStackTrace();
			}
			
			if(outputFrame != null){
				
				if(outputFrame == Settings.STOP){
					break loop;
				}
				
				framecount = outputFrame.getFrameNumber() % updateRate;
				
				if(saveData){
					try {
						audioWriter.write(Utilities.getByteArray(outputFrame.getShorts()));
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				
				if(debugData){
					try {
						debugWriter.write((Arrays.toString(outputFrame.getFiltered())+"\n").getBytes());
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				
				if(Settings.playback) {
					if(Settings.output){
						sound.write(outputFrame.getShorts(), 0, Settings.blockSize);
					} else {
						sound.write(outputFrame.getSFiltered(), 0, Settings.blockSize);
					}
				}
				
				if(framecount == 0){
					elapsed = outputFrame.getElapsed();
				} else if(framecount == (updateRate-1)){
					main.updateStats(((elapsed+outputFrame.getElapsed())/1000000.0f)/framecount);
				} else {
					elapsed += outputFrame.getElapsed();
				}
			}
		}
		
		if((framecount > 0) && (framecount  < (updateRate-1))) {
			main.updateStats((elapsed/1000000.0f)/framecount);
		}

		main.done();
		
		if(sound != null){
			sound.pause();
			sound.flush();
			sound.release();
		}
		
		if(saveData){
			try {
				audioWriter.flush();
				audioWriter.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		if(debugData){
			try {
				debugWriter.flush();
				debugWriter.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}