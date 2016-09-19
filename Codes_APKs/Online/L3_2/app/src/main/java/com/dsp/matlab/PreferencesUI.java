//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import android.os.Bundle;
import android.preference.PreferenceActivity;

public class PreferencesUI extends PreferenceActivity{
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		getFragmentManager().beginTransaction().replace(android.R.id.content, new PreferencesFragment()).commit();
	}
}
