#include <jni.h>

#ifndef _Included_AESUtil_H
#define _Included_AESUtil_H

#ifdef __cplusplus
extern "C" {
#endif

jstring Java_com_abc_util_JniHelp_aesEncrypt(JNIEnv *, jobject, jstring, jstring);
jstring Java_com_abc_util_JniHelp_aesDecrypt(JNIEnv *, jobject, jstring, jstring);
jstring Java_com_abc_util_JniHelp_test(JNIEnv *, jobject, jstring, jstring);

#ifdef __cplusplus
}
#endif

#endif
