package com.dsp.helloworld;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.app.Activity;
import android.graphics.DashPathEffect;
import android.os.Bundle;
import java.util.Arrays;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.common.api.GoogleApiClient;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button btncompute, buttonSetPreference;
    private TextView tvresult, settingList;
    private EditText etavalue,eta1value,eta2value,etdel1value,
            etdel2value, etd1value,etd2value;

    //public final String TAG = "HelloWorld";
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;

    @SuppressWarnings("JniMissingFunction")
    //public native String getString();

    public native float[] getArray(float opvalue, float a, float a1, float a2, float del1, float del2, float d1, float d2,
                                   float mode1, float mode2, float mode3, float mode4);

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

        etavalue = (EditText) findViewById(R.id.etavalue);
        eta1value = (EditText) findViewById(R.id.eta1value);
        eta2value = (EditText) findViewById(R.id.eta2value);
        etdel1value = (EditText) findViewById(R.id.etdel1value);
        etdel2value = (EditText) findViewById(R.id.etdel2value);
        etd1value = (EditText) findViewById(R.id.etd1value);
        etd2value = (EditText) findViewById(R.id.etd2value);
        /*etmode1value = (EditText) findViewById(R.id.etmode1value);
        etmode2value = (EditText) findViewById(R.id.etmode2value);
        etmode3value = (EditText) findViewById(R.id.etmode3value);
        etmode4value = (EditText) findViewById(R.id.etmode4value);
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
        float opvalue,a,a1,a2,del1,del2,d1,d2,mode1,mode2,mode3,mode4;

        String a_val = etavalue.getText().toString();
        String a1_val = eta1value.getText().toString();
        String a2_val = eta2value.getText().toString();
        String del1_val = etdel1value.getText().toString();
        String del2_val = etdel2value.getText().toString();
        String d1_val = etd1value.getText().toString();
        String d2_val = etd2value.getText().toString();
        /*String mode1_val = etmode1value.getText().toString();
        String mode2_val = etmode2value.getText().toString();
        String mode3_val = etmode3value.getText().toString();
        String mode4_val = etmode4value.getText().toString();
*/
        //String option = etoption.getText().toString();
        //Settings.setBlockSize(Integer.parseInt(preferences.getString(getString(R.string.prefBlockSize), "256")));

        SharedPreferences SP = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        String PREF_LIST = SP.getString("PREF_LIST", "1");
        String mode1_val = SP.getString("Input_comb", "1");
        String mode2_val = SP.getString("Output_comb", "1");
        String mode3_val = SP.getString("input_type", "1");
        String mode4_val = SP.getString("input_type_2", "1");
        //String PREF_LIST_1 = SP.getString("PREF_LIST_1", "1");

        /*String R_val = SP.getString("R", "1");
        String L_val = SP.getString("L", "1");
        String C_val = SP.getString("C", "1");
        String A_val = SP.getString("A", "1");*/


        //dvalue = Float.parseFloat(delta);
        opvalue = Float.parseFloat(PREF_LIST);
        a = Float.parseFloat(a_val);
        a1 = Float.parseFloat(a1_val);
        a2 = Float.parseFloat(a2_val);
        del1 = Float.parseFloat(del1_val);
        del2 = Float.parseFloat(del2_val);
        d1 = Float.parseFloat(d1_val);
        d2 = Float.parseFloat(d2_val);
        mode1 = Float.parseFloat(mode1_val);
        mode2 = Float.parseFloat(mode2_val);
        mode3 = Float.parseFloat(mode3_val);
        mode4 = Float.parseFloat(mode4_val);

        if (v.getId() == R.id.btncompute) {

            var = getArray(opvalue, a, a1, a2, del1, del2, d1, d2, mode1, mode2, mode3, mode4);

            main_2.graph_var = new Float[var.length];

            for (int i = 0; i < var.length; i++) {
                main_2.graph_var[i] = var[i];
            }

            Intent graph = new Intent(MainActivity.this, SimpleXYPlotActivity.class);
            startActivity(graph);


            tvresult.setText((Arrays.toString(var)));
            //tvresult.setText((String.valueOf(var[0])));
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
