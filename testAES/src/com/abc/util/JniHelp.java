package com.abc.util;

import android.content.Context;

public class JniHelp {
    
    static {
        System.loadLibrary("sosec");
    }

    public static native String aesEncrypt(String plainText, String key);
    public static native String aesDecrypt(String cipherText, String key);
    public static native String test(String cipherText, String key);
}
