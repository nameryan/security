#include "aesUtil.h"

#include   <stdio.h>
#include   <stdlib.h>
#include   <string>
#include "log.h"
#include "aesEncrypt.h"

#define CBUFF_LEN 1024
#define CPUID_LEN 16
#define KEY_LEN 32

int main(void);

char ASCI_16(char a){
	char b;
	
	if(a>=0x30&&a<=0x39){
		b=a-0x30;
	}else if (a>=0x41&&a<=0x46){
		b=a-0x41+10;
	}else if (a>=0x61&&a<=0x66){
		b=a-0x61+10;
	}
	return b;
}


/*
 * 
*/
void generateKey(JNIEnv *env,unsigned char *salt1,unsigned char *dstKey){
	int salt1_len = strlen((char *)salt1);
	
	strcpy((char *)dstKey,(char *)salt1);
	
	LOGD("****dstKey len=%d,string=%s",strlen((char *)dstKey),dstKey);
}

jstring Java_com_abc_util_JniHelp_aesEncrypt(JNIEnv *env,
		jobject obj, jstring s, jstring k) {
	
	LOGD("===Java_com_yoha_vpayplugin_util_JniHelp_aesEncrypt===");
	
	if (s == NULL || k == NULL){
  	LOGE("***aesEecrypt input s = null or k = null");
  	return NULL;
  }
  
	//将需要加密的字符串转化为const char*类型
	const char* str = env->GetStringUTFChars(s, 0);
	//unsigned char *deb_plaintext =(unsigned char*)"1234567812345678";
	
	//密钥字符串转化成char*
	const char* key = env->GetStringUTFChars(k, 0);
	unsigned char deb_key[KEY_LEN+1] ="";
	generateKey(env,(unsigned char*)key,deb_key);
	//LOGD("****deb_key=%s",deb_key);
	
	unsigned char dst[CBUFF_LEN];
	//memset((char*) source, 0, CBUFF_LEN);
	memset((char*) dst, 0, sizeof(dst));
	int cipher_len = 0;
	
	cipher_len = aesencrypt((unsigned char*)str,deb_key,dst);
	
	LOGD("****cipher_len=%d",cipher_len);
	
	//将加密后的字符串，转换成hex string返回
	char retStr[(cipher_len+1)*2];
	char tmpStr[3];
	memset(retStr,0x00,sizeof(retStr));
	for (int i =0;i<(cipher_len);i++){
		memset(tmpStr,0x00,sizeof(tmpStr));
		sprintf(tmpStr, "%X", dst[i]);
		//LOGD("****tmpStr=%s",tmpStr);
		if (dst[i] <= 0x0F){
			strcat(retStr,"0");
		}
		strcat(retStr,tmpStr);		
	}
	//LOGD("****retStr=%s",retStr);
	
	env->ReleaseStringUTFChars(s,str);
	env->ReleaseStringUTFChars(k,key);
	
	return env->NewStringUTF(retStr); //通过JNI提供的转化方法将char*转化为jstring作为结果返回

}

jstring Java_com_abc_util_JniHelp_aesDecrypt(JNIEnv *env,
		jobject obj, jstring s, jstring k) {
	
  //将需要解密的字符串转化为const char*类型

  if (s == NULL || k == NULL){
  	LOGE("***aesDecrypt input s = null or k = null");
  	return NULL;
  }
	const char* ciphter_str = env->GetStringUTFChars(s, 0);
	
	//密钥字符串转化成char*
	const char* key = env->GetStringUTFChars(k, 0);
	unsigned char deb_key[KEY_LEN+1] ="";
	generateKey(env,(unsigned char*)key,deb_key);
	
	unsigned char plaint_str[CBUFF_LEN];
	memset((char*) plaint_str, 0, sizeof(plaint_str));
	int cipher_len = strlen(ciphter_str)/2;
	LOGD("****cipher_len=%d",cipher_len);
	
	//将加密后的字符串，16进制转换成unsigned char*
	char tempStr[(cipher_len+1)*2];
	memset(tempStr,0x00,sizeof(tempStr));
	strcpy(tempStr,ciphter_str);
	//LOGD("****tempStr=%s",tempStr);
	char data[cipher_len+1];
	memset(data,0x00,sizeof(data));
	
	int i=0,j=0;
	char tmph,tmpl;
	for (i=0;i<sizeof(tempStr);i+=2){
		tmph = ASCI_16(tempStr[i])<<4;
		tmpl = ASCI_16(tempStr[i+1]);
		//LOGD("**tmpstr=0x%x+0x%x",tmph,tmpl);
		data[j] = tmph+tmpl;
		//LOGD("****data=0x%x",data[j]);
		j++;
	}

	//LOGD("****data=0x%x,0x%x,0x%x,0x%x",data[0],data[1],data[2],data[3]);

	
	unsigned char dst[CBUFF_LEN];
	int plaint_len;
	//LOGD("--1--- dst=%x,%x,%x,%x",dst[0],dst[1],dst[2],dst[3]);
	plaint_len = aesdecrypt((unsigned char*)data,cipher_len,deb_key,dst);
	//LOGD("--2--- dst=%s",dst);
	LOGD("****plaint_len=%d",plaint_len);
	char retStr[plaint_len+1];
	memset(retStr,0x00,sizeof(retStr));
	strcpy(retStr,(char *)dst);
	
	env->ReleaseStringUTFChars(s,ciphter_str);
	env->ReleaseStringUTFChars(k,key);
	
	return env->NewStringUTF(retStr); //通过JNI提供的转化方法将char*转化为jstring作为结果返回
	
}

