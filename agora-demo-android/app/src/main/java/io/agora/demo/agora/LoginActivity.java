package io.agora.demo.agora;

import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.Toast;

/**
 * Created by apple on 15/9/9.
 */
public class LoginActivity extends BaseActivity {

    private EditText mVendorKey;
    private EditText mChannelID;

    @Override
    public void onCreate(Bundle savedInstance) {

        super.requestWindowFeature(Window.FEATURE_NO_TITLE);

        super.onCreate(savedInstance);
        setContentView(R.layout.activity_login);

        initViews();
    }

    private void initViews() {

        // bind listeners
        findViewById(R.id.action_video_calling).setOnClickListener(getViewClickListener());
        findViewById(R.id.action_voice_calling).setOnClickListener(getViewClickListener());

        this.mVendorKey = (EditText) findViewById(R.id.input_vendor_key);
        this.mChannelID = (EditText) findViewById(R.id.input_room_number);


        this.mVendorKey.setText(getSharedPreferences(getClass().getName(),Context.MODE_PRIVATE).getString(ChannelActivity.EXTRA_VENDOR_KEY, "6D7A26A1D3554A54A9F43BE6797FE3E2"));
        this.mChannelID.setText(getSharedPreferences(getClass().getName(),Context.MODE_PRIVATE).getString(ChannelActivity.EXTRA_CHANNEL_ID, ""));

    }


    @Override
    public void onUserInteraction(View view) {


        // Ensure inputs are valid;
        if(!validateInput()){
            return ;
        }


        switch (view.getId()) {
            default:
                super.onUserInteraction(view);

                // Voice calling
            case R.id.action_voice_calling: {

                Intent intent = new Intent(LoginActivity.this, ChannelActivity.class);
                intent.putExtra(ChannelActivity.EXTRA_CALLING_TYPE, ChannelActivity.CALLING_TYPE_VOICE);
                intent.putExtra(ChannelActivity.EXTRA_VENDOR_KEY, mVendorKey.getText().toString());
                intent.putExtra(ChannelActivity.EXTRA_CHANNEL_ID, mChannelID.getText().toString());
                startActivity(intent);
//                finish();

            }
            break;

            // Video calling
            case R.id.action_video_calling: {

                Intent intent = new Intent(LoginActivity.this, ChannelActivity.class);
                intent.putExtra(ChannelActivity.EXTRA_CALLING_TYPE, ChannelActivity.CALLING_TYPE_VIDEO);
                intent.putExtra(ChannelActivity.EXTRA_VENDOR_KEY, mVendorKey.getText().toString());
                intent.putExtra(ChannelActivity.EXTRA_CHANNEL_ID, mChannelID.getText().toString());
                startActivity(intent);
//                finish();

            }
            break;

        }



        // remember the vendor key and channel ID
        getSharedPreferences(getClass().getName(), Context.MODE_PRIVATE)
                .edit()
                .putString(ChannelActivity.EXTRA_VENDOR_KEY, mVendorKey.getText().toString())
                .putString(ChannelActivity.EXTRA_CHANNEL_ID, mChannelID.getText().toString())
                .apply();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {

        super.onConfigurationChanged(newConfig);
    }


    boolean validateInput() {

        String vendorKey = mVendorKey.getText().toString();
        String roomNumber = mChannelID.getText().toString();

        // validate vendor key
        if (TextUtils.isEmpty(vendorKey)) {
            Toast.makeText(getApplicationContext(), R.string.key_required, Toast.LENGTH_SHORT).show();
            return false;
        }

        // validate room number - cannot be empty
        if (TextUtils.isEmpty(roomNumber)) {
            Toast.makeText(getApplicationContext(), R.string.room_required, Toast.LENGTH_SHORT).show();
            return false;
        }


        // validate room number - should be digits only
        if(!TextUtils.isDigitsOnly(roomNumber)){
            Toast.makeText(getApplicationContext(), R.string.room_required, Toast.LENGTH_SHORT).show();
            return false;
        }

        return true;
    }

}
