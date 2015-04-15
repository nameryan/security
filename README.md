#aes encrypt on Jni based by openssl evp api
this is a project process aes encrypt and decrpty , JNI packed, and use OPENSSL EVP api

STEP:
1.download the latest NDK from developer.google.com and install it on path /home/NDK , in this example ,the ndk version is r10d-linux64, so after installed ,the NDK path is /home/NDK/android-ndk-r10d
2.to check NDK installed ,entry the ndk path ,type ndk-build cmd in bash .
3.put this project security on path /home/security ,in this example ,the path is /home/security
4.entry the security path in your bash (cd home/security)
5.:~/security$../NDK/android-ndk-r10d/ndk-build
6.it will notice ": libsec.so => libs/armeabi/libsec.so" , copy this libsec.so to libs path in your android project, then use JniHelp.java in the example code to use this so library.

the main source code is in path security/myApp/, pls modify the code under this path ,don't modify the code outside myApp

-----------------
           Ryan.C @ gvtv
           contact email:name.ryan@gmail.com