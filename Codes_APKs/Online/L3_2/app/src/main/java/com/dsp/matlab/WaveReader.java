//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;

public class WaveReader implements Runnable{
	
	private long nFrames;
	private long currentIndex;
	private File waveFile;
	private FileInputStream stream;
	private byte[] abuf_byte;
	private short[] abuf_short;
	private ByteBuffer buffer;
	private BlockingQueue<WaveFrame> output;
	private AtomicBoolean read;
	private Thread reader;
	
	public WaveReader(String waveFileName, BlockingQueue<WaveFrame> output) {
		this.output = output;
		read = new AtomicBoolean(true);
		waveFile = Utilities.getFile(waveFileName);
		nFrames = (waveFile.length())/(2*Settings.blockSize);
		currentIndex = 0;
		
		try {
			stream = new FileInputStream(waveFile);
			if(waveFile.getName().contains(".wav")){
				stream.skip(44);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		abuf_byte = new byte[2*Settings.blockSize];
		abuf_short = new short[Settings.blockSize];
		
		buffer = ByteBuffer.wrap(abuf_byte);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		
        reader = new Thread(this);
        reader.start();
	}
	
	public void stop(){
		read.set(false);
	}
	
	public boolean isReading(){
		return read.get();
	}
	
	public void run() {
		while (read.get()) {
			try {
				stream.read(abuf_byte);
			} catch (IOException e) { 
				e.printStackTrace(); 
			}
			for(int i=0;i<Settings.blockSize;i++) {
				abuf_short[i] = buffer.getShort(2*i);
			}
			
			try {
				output.put(new WaveFrame(abuf_short, currentIndex));
			} catch (InterruptedException e) {
				e.printStackTrace();
				Thread.currentThread().interrupt();
			}
			
			currentIndex++;
			if(currentIndex == nFrames){
				read.set(false);
			}
		}
		
		try {
			output.put(Settings.STOP);
		} catch (InterruptedException e) {
			e.printStackTrace();
			Thread.currentThread().interrupt();
		}
		
		try {
			stream.close();
		} catch (IOException e) { 
			e.printStackTrace(); 
		}
	}
}
