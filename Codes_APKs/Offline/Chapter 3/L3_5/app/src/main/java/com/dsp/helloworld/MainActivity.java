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
    private EditText etdelta;
    //public final String TAG = "HelloWorld";
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;

    @SuppressWarnings("JniMissingFunction")
    //public native String getString();

    public native float[] getArray(float w1, float w2, float A, float Resistance, float L, float C);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /*TextView cna = (TextView) findViewById(R.id.log);
        float[] var;
        float A=1,Resistance=1,L=1,C=1, opvalue = 1,w1=1,w2=1;

        //TextView cna = (TextView) findViewById(R.id.log);
        //float[] var = new float[20];
        //Log.i(TAG, "Output");
        System.out.println("Hi");
        A = 1;
        Resistance = 1;
        L = 1;
        C = 1;
        opvalue = 1;
        if(opvalue == 1){
            w1 = 0;
            w2 = 1;
        }
        else{
            w1 = 1;
            w2 = 0;
        }

        var = getArray(w1, w2, A, Resistance, L, C);

        if (var == null) {
            throw new RuntimeException("native getData failed");
        }
        //var = getArray();
        cna.setText((Arrays.toString(var)));*/
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
        //etavalue = (EditText) findViewById(R.id.etavalue);
        //etbvalue = (EditText) findViewById(R.id.etbvalue);
        //etdelta = (EditText) findViewById(R.id.etdelta);
       // etoption = (EditText) findViewById(R.id.etoption);
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
        float A=1,Resistance=1,L=1,C=1, opvalue = 1,w1=1,w2=1;
        //String delta = etdelta.getText().toString();
//        String option = etoption.getText().toString();
        //Settings.setBlockSize(Integer.parseInt(preferences.getString(getString(R.string.prefBlockSize), "256")));
        SharedPreferences SP = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        String PREF_LIST = SP.getString("PREF_LIST", "1");
        String R_val = SP.getString("R", "1");
        String L_val = SP.getString("L", "1");
        String C_val = SP.getString("C", "1");
        String A_val = SP.getString("A", "1");



        //dvalue = Float.parseFloat(delta);
        opvalue = Float.parseFloat(PREF_LIST);
        A = Float.parseFloat(A_val);
        Resistance = Float.parseFloat(R_val);
        L = Float.parseFloat(L_val);
        C = Float.parseFloat(C_val);

        /*A = 1;
        Resistance = 1;
        L = 1;
        C = 1;
        */
        switch((int) opvalue){
            case 1:
                w1 = 0; w2 = 0;
                break;
            case 2:
                w1 = 0; w2 = 1;
                break;
            case 3:
                w1 = 1; w2 = 0;
                break;
            case 4:
                w1 = 1; w2 = 1;
                break;
            default:
                w1 = 0; w2 = 0;

        }

        if (v.getId() == R.id.btncompute) {

            var = getArray(w1, w2, A, Resistance, L, C);

            main_2.graph_var = new Float[var.length];

            for (int i = 1; i < var.length; i++) {
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
