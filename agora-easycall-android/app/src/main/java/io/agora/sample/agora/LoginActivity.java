package io.agora.sample.agora;

import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.Toast;

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
}