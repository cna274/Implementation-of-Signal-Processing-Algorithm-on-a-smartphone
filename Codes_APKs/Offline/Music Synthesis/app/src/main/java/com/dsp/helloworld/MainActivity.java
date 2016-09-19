package com.dsp.helloworld;
import android.content.Intent;
import android.net.Uri;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;

import java.util.Arrays;

import android.preference.PreferenceManager;
import android.content.SharedPreferences;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.common.api.GoogleApiClient;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button btncompute, buttonSetPreference;
    private TextView tvresult, settingList;
    private EditText etA1value, etA2value,etA3value,etA4value,etA5value,etA6value,
            etB1value, etB2value,etB3value,etB4value,etB5value,etB6value,etFvalue;
    //public final String TAG = "HelloWorld";
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;

    @SuppressWarnings("JniMissingFunction")
    //public native String getString();

    public native float[] getArray (float opvalue, float A1, float A2, float A3, float A4, float A5, float A6, float freq1,
            float freq2,float freq3,float freq4,float freq5,float freq6,float option);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView cna = (TextView) findViewById(R.id.log);
        float[] var;

        //TextView cna = (TextView) findViewById(R.id.log);
        //float[] var = new float[20];
        //Log.i(TAG, "Output");

        init();

        //Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        //setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();
    }
    private void init() {

        btncompute = (Button) findViewById(R.id.btncompute);

        etA1value = (EditText) findViewById(R.id.etA1value);
        etA2value = (EditText) findViewById(R.id.etA2value);
        etA3value = (EditText) findViewById(R.id.etA3value);
        etA4value = (EditText) findViewById(R.id.etA4value);
        etA5value = (EditText) findViewById(R.id.etA5value);
        etA6value = (EditText) findViewById(R.id.etA6value);
        etFvalue = (EditText) findViewById(R.id.etFvalue);
        etB1value = (EditText) findViewById(R.id.etB1value);
        etB2value = (EditText) findViewById(R.id.etB2value);
        etB3value = (EditText) findViewById(R.id.etB3value);
        etB4value = (EditText) findViewById(R.id.etB4value);
        etB5value = (EditText) findViewById(R.id.etB5value);
        etB6value = (EditText) findViewById(R.id.etB6value);
       /* etwvalue = (EditText) findViewById(R.id.etwvalue);
        etqvalue = (EditText) findViewById(R.id.etqvalue);
*/
        tvresult = (TextView) findViewById(R.id.tvresult);
        buttonSetPreference = (Button)findViewById(R.id.setpreference);
        //settingCheckBox = (TextView)findViewById(R.id.setting_checkbox);
        settingList = (TextView)findViewById(R.id.setting_list);


        btncompute.setOnClickListener(this);
        buttonSetPreference.setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {

        TextView cna = (TextView) findViewById(R.id.log);
        float[] var;
        float opvalue, A1,A2,A3,A4,A5,A6,freq1,freq2,freq3,freq4,freq5,freq6,option;

        String A1_val = etA1value.getText().toString();
        String A2_val = etA2value.getText().toString();
        String A3_val = etA3value.getText().toString();
        String A4_val = etA4value.getText().toString();
        String A5_val = etA5value.getText().toString();
        String A6_val = etA6value.getText().toString();
        String B1_val = etB1value.getText().toString();
        String B2_val = etB2value.getText().toString();
        String B3_val = etB3value.getText().toString();
        String B4_val = etB4value.getText().toString();
        String B5_val = etB5value.getText().toString();
        String B6_val = etB6value.getText().toString();
        String option_val = etFvalue.getText().toString();

        //String option = etoption.getText().toString();
        //Settings.setBlockSize(Integer.parseInt(preferences.getString(getString(R.string.prefBlockSize), "256")));

        SharedPreferences SP = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        String PREF_LIST = SP.getString("PREF_LIST", "1");
        //String PREF_LIST_1 = SP.getString("PREF_LIST_1", "1");

        /*String R_val = SP.getString("R", "1");
        String L_val = SP.getString("L", "1");
        String C_val = SP.getString("C", "1");
        String A_val = SP.getString("A", "1");*/


        //dvalue = Float.parseFloat(delta);
        opvalue = Float.parseFloat(PREF_LIST);
        A1 = Float.parseFloat(A1_val);
        A2 = Float.parseFloat(A2_val);
        A3 = Float.parseFloat(A3_val);
        A4 = Float.parseFloat(A4_val);
        A5 = Float.parseFloat(A5_val);
        A6 = Float.parseFloat(A6_val);
        freq1 = Float.parseFloat(B1_val);
        freq2 = Float.parseFloat(B2_val);
        freq3 = Float.parseFloat(B3_val);
        freq4 = Float.parseFloat(B4_val);
        freq5 = Float.parseFloat(B5_val);
        freq6 = Float.parseFloat(B6_val);
        option = Float.parseFloat(option_val);

        if (v.getId() == R.id.btncompute) {

            var = getArray(opvalue, A1, A2, A3, A4, A5, A6, freq1, freq2, freq3, freq4, freq5, freq6, option);

            main_2.graph_var = new Float[var.length];

            for (int i = 0; i < var.length; i++) {
                main_2.graph_var[i] = var[i];
            }

            Intent graph = new Intent(MainActivity.this, SimpleXYPlotActivity.class);
            startActivity(graph);


            tvresult.setText((Arrays.toString(var)));
            //tvresult.setText((String.valueOf(var)));
            //tvresult.setText(PREF_LIST);

        } else if (v.getId() == R.id.setpreference) {
            Intent intentSetPref = new Intent(getApplicationContext(), PrefActivity.class);
            startActivityForResult(intentSetPref, 0);


        }
    }


    static {
        System.loadLibrary("HelloWorld");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        //Boolean prefCheckBox = sharedPreferences.getBoolean("PREF_CHECKBOX", false);
        //settingCheckBox.setText("CHECKBOX preference = " + prefCheckBox.toString());
        String prefList = sharedPreferences.getString("PREF_LIST", "no selection");
        settingList.setText("LIST preference = " + prefList);
        }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "Main Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app deep link URI is correct.
                Uri.parse("android-app://com.dsp.helloworld/http/host/path")
        );
        AppIndex.AppIndexApi.start(client, viewAction);
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "Main Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app deep link URI is correct.
                Uri.parse("android-app://com.dsp.helloworld/http/host/path")
        );
        AppIndex.AppIndexApi.end(client, viewAction);
        client.disconnect();
    }

}
