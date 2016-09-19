//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import java.util.concurrent.BlockingQueue;

public class Filter implements Runnable{
	
	private BlockingQueue<WaveFrame> input;
	private BlockingQueue<WaveFrame> output;
	private Thread filter;
	
	public Filter(BlockingQueue<WaveFrame> input, BlockingQueue<WaveFrame> output) {
		this.input = input;
		this.output = output;
        filter = new Thread(this);
        filter.start();
	}

	public void run() {
		try {
			Filters.initialize();
			loop:while(true) {
				WaveFrame currentFrame = null;
				currentFrame = input.take();
				if(currentFrame == Settings.STOP){
					Filters.finish();
					output.put(currentFrame);
					break loop;
				}
				
				long then = System.nanoTime();
				currentFrame.setFiltered(Filters.compute(currentFrame.getFloats(), Settings.Fs, Settings.blockSize));
				currentFrame.setElapsed(System.nanoTime()-then);
				output.put(currentFrame);
			}
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
			e.printStackTrace();
		}
	}
}