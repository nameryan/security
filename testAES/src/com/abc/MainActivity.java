
package com.abc;


import com.abc.util.JniHelp;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        final String srouce = "12374488";
        final String key = "abcdefg12345";
        Log.d("", "+++++++++++++++start encrypt+++++++++++++++");
        String ciphterText = JniHelp.aesEncrypt(srouce, key);
        Log.d("testAES", "ciphterText="+ciphterText);
        
        Log.d("", "---------------start decrypt---------------");
        String plaintText = JniHelp.aesDecrypt(ciphterText, key);
        Log.d("testAES", "plaintText="+plaintText);
    }
}
