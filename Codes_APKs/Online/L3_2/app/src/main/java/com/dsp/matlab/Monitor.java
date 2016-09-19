//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

public interface Monitor {
	public void done();
	public void updateStats(float elapsed);
	public void notifySkips(long framesSkipped);
}
