package io.agora.sample.agora;

import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.Window;

/**
 * Created by apple on 15/9/15.
 */
public class MainActivity extends BaseEngineHandlerActivity {

    @Override
    public void onCreate(Bundle savedInstance){

        super.requestWindowFeature(Window.FEATURE_NO_TITLE);

        super.onCreate(savedInstance);
        setContentView(R.layout.activity_main);

        initViews();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig){

        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onUserInteraction(View view){

        switch (view.getId()){

            default:

                super.onUserInteraction(view);
                break;

            case R.id.main_button_by_key:{

                if(TextUtils.isEmpty(((AgoraApplication)getApplication()).getVendorKey())){
                    Intent toLogin = new Intent(MainActivity.this, LoginActivity.class);
                    startActivity(toLogin);

                }else{
                    Intent toSelect = new Intent(MainActivity.this, SelectActivity.class);
                    startActivity(toSelect);
                }
            }
            break;

            case R.id.main_button_no_key:{

                Intent toWebView=new Intent(MainActivity.this,WebActivity.class);
                toWebView.putExtra(WebActivity.EXTRA_KEY_URL, WebActivity.AGORA_URL_GETKEY);
                startActivity(toWebView);
            }
            break;
        }
    }

    private void initViews(){

        findViewById(R.id.main_button_by_key).setOnClickListener(getViewClickListener());
        findViewById(R.id.main_button_no_key).setOnClickListener(getViewClickListener());
    }
}