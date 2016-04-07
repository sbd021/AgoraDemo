package io.agora.sample.agora;

import android.content.Intent;
import android.content.res.Configuration;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

/**
 * Created by apple on 15/9/15.
 */
public class LoginActivity extends BaseEngineHandlerActivity {

    private EditText mVendorKeyInput;
    private EditText mUsernameInput;

    @Override
    public void onCreate(Bundle savedInstance) {

        super.requestWindowFeature(Window.FEATURE_NO_TITLE);

        super.onCreate(savedInstance);

        new RequestTask().execute("http://192.168.99.253:8970/agora.inner.test.key.txt");
        setContentView(R.layout.activity_login);

        ((AgoraApplication) getApplication()).setEngineHandlerActivity(this);

        initViews();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {

        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onUserInteraction(View view) {

        switch (view.getId()) {

            default:

                super.onUserInteraction(view);
                break;

            //go to MainActivity
            case R.id.login_back: {

                finish();
            }
            break;

            //go to SelectActivity
            case R.id.login_login: {

                if (!validateInput()) {
                    return;
                }

                ((AgoraApplication) getApplication()).setUserInformation(mVendorKeyInput.getText().toString(), mUsernameInput.getText().toString());

                Intent toSelect = new Intent(LoginActivity.this, SelectActivity.class);

                startActivity(toSelect);

                finish();
            }
            break;
        }
    }

    private void initViews() {

        mVendorKeyInput = (EditText) findViewById(R.id.login_key_input);
        mUsernameInput = (EditText) findViewById(R.id.login_user_input);

        findViewById(R.id.login_back).setOnClickListener(getViewClickListener());
        findViewById(R.id.login_login).setOnClickListener(getViewClickListener());
    }

    private boolean validateInput() {

        if (TextUtils.isEmpty(mVendorKeyInput.getText().toString())) {

            Toast.makeText(getApplicationContext(), R.string.login_key_required, Toast.LENGTH_SHORT).show();
            return false;

        }

        if (TextUtils.isEmpty(mUsernameInput.getText().toString())) {

            Toast.makeText(getApplicationContext(), R.string.login_user_required, Toast.LENGTH_SHORT).show();
            return false;

        }

        return true;

    }



    class RequestTask extends AsyncTask<String, String, String> {


        String responseString = null;

        @Override
        protected String doInBackground(String... uri) {
            HttpClient httpclient = new DefaultHttpClient();
            HttpResponse response;
            try {
                response = httpclient.execute(new HttpGet(uri[0]));
                StatusLine statusLine = response.getStatusLine();
                if(statusLine.getStatusCode() == HttpStatus.SC_OK){
                    ByteArrayOutputStream out = new ByteArrayOutputStream();
                    response.getEntity().writeTo(out);
                    responseString = out.toString();
                    out.close();
                } else{
                    //Closes the connection.
                    response.getEntity().getContent().close();
                    throw new IOException(statusLine.getReasonPhrase());
                }
            } catch (ClientProtocolException e) {
                //TODO Handle problems..
            } catch (IOException e) {
                //TODO Handle problems..
            }
            return responseString;
        }

        @Override
        protected void onPostExecute(String result) {
            super.onPostExecute(result);
            //Do anything with response..
            if (responseString != null) {
                mVendorKeyInput.setText(responseString.replaceAll("\\s+",""), TextView.BufferType.EDITABLE);
            }
        }
    }

}