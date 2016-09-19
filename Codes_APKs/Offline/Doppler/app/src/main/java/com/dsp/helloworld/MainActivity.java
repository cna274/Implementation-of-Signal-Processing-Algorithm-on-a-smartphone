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
    private EditText etAvalue, etBvalue, etFvalue;
    //public final String TAG = "HelloWorld";
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;

    @SuppressWarnings("JniMissingFunction")
    //public native String getString();

    public native float[] getArray(float opvalue, float a, float b, float freq);

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

        etAvalue = (EditText) findViewById(R.id.etAvalue);
        etFvalue = (EditText) findViewById(R.id.etFvalue);
        etBvalue = (EditText) findViewById(R.id.etBvalue);
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
        float opvalue, a, b, freq;

        String A_val = etAvalue.getText().toString();
        String B_val = etBvalue.getText().toString();
        String freq_val = etFvalue.getText().toString();

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
        a = Float.parseFloat(A_val);
        b = Float.parseFloat(B_val);
        freq = Float.parseFloat(freq_val);

        if (v.getId() == R.id.btncompute) {

            var = getArray(opvalue, a, b, freq);

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
