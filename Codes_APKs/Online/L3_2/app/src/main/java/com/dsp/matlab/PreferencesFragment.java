//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import android.os.Bundle;
import android.preference.ListPreference;
import android.preference.PreferenceFragment;

public class PreferencesFragment extends PreferenceFragment {

public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
 		addPreferencesFromResource(R.xml.prefs);
        final ListPreference listPreference = (ListPreference) findPreference("samplingfreq");
        listPreference.setEntries(Settings.samplingRates);
        listPreference.setEntryValues(Settings.samplingRateValues);
        listPreference.setDefaultValue("8000");
	}
}