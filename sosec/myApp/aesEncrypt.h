#ifndef _Included_AESENCRYPT_H
#define _Included_AESENCRYPT_H

int aesencrypt(unsigned char* plaintext,unsigned char* key,unsigned char* ciphertext);
int aesdecrypt(unsigned char* ciphertext,int len,unsigned char* key,unsigned char* decryptedtext);

#endif
