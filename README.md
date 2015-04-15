#aes encrypt with Android Jni based by openssl evp api
this is a project process aes encrypt and decrpty , JNI packed, and use OPENSSL EVP api.

##folder tree:

**|**<br />
**|-sosec**  (the root folder of ndk build) <br />
**|--myApp**  (main cpp folder) <br />
**|--libs**  (the output armeabi/armeabi-v7a so files folder)<br />
**|--...**<br />

**|**<br />
**|-testAES**  (the root folder of android project)<br />
**|--src**  (the source folder contains test main function) <br />
**|--libs**  (the so files created by sosec/libs)<br />
**|--...**<br />


##QuickStart:
1.  download the latest NDK from developer.google.com and install it on path /home/NDK , in this example ,the ndk version is r10d-linux64, so after installed ,the NDK path is /home/NDK/android-ndk-r10d
2.  to check NDK installed ,entry the ndk path ,type ndk-build cmd in bash .
3.  copy sosec folder to path /home/sosec ,in this example ,the path is /home/sosec
4.  entry the sosec path in your bash (cd home/sosec)
5.  :~/sosec$../NDK/android-ndk-r10d/ndk-build
6.  it will notice ": libsosec.so => libs/armeabi/libsosec.so" , copy this libsosec.so to libs path in your android project, then use JniHelp.java in the example code to use this so library.

the main source code is in path sosec/myApp/, pls modify the code under this path ,don't modify the code outside myApp
