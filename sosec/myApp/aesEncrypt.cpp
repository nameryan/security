#include   <stdio.h>
#include   <stdlib.h>
#include   <time.h>
#include   <string>
#include <assert.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "log.h"

/*
 *
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 *
 */

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())){
  	 //handleErrors();
  	}

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)){
    //handleErrors();
  }

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)){
    //handleErrors();
  }
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)){
  	//handleErrors();
  }
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())){
  	//handleErrors();
  }

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)){
    //handleErrors();
  }

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)){
    //handleErrors();
  }
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)){
  	//handleErrors();
  }
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

int aesencrypt(unsigned char* plaintext,unsigned char* key,unsigned char* ciphertext){
	
	int ciphertext_len;
	
	//LOGD("LIB plaintext:%s:len=%d\n",plaintext, strlen((char *)plaintext));
	//LOGD("LIB key:%s[0x%x,0x%x,0x%x,0x%x]\n",key,key[0],key[1],key[2],key[3]);
	
	unsigned char iv[32]={0};
	//unsigned char *iv = (unsigned char*)"01234567890123456";
	
	/* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Encrypt the plaintext */
  ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv,
    ciphertext);
   
	/* Do something useful with the ciphertext here */
  //printf("Ciphertext is:\n");  
  //BIO_dump_fp(stdout, (char *)ciphertext, ciphertext_len);
  //LOGD("#### %x%x%x%x",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();
  
  return ciphertext_len;
}

int aesdecrypt(unsigned char* ciphertext,int len,unsigned char* key,unsigned char* decryptedtext){
	
	int decryptedtext_len;
	//LOGD("LIB encrypttext:%s:len=%d\n",plaintext, strlen((char *)plaintext));
	//LOGD("LIB key:%s\n",key);
	
	unsigned char iv[32]={0};
	//memset(iv,0x00,sizeof(iv));
	//unsigned char *iv = (unsigned char*)"01234567890123456";
	
	/* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Decrypt the ciphertext */
  decryptedtext_len = decrypt(ciphertext, len, key, iv,
    decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  //printf("Decrypted text is:\n");
  //printf("%s\n", decryptedtext);
  //LOGD("Decrypted text is:\n%s\n",decryptedtext);

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();
  
  return decryptedtext_len;
}


//int main(int arc, char *argv[])
int main(void)
{
  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */

  /* A 256 bit key */
  unsigned char *key = (unsigned char*)"1234567812345678";

  /* A 128 bit IV */
  //unsigned char *iv = (unsigned char*)"01234567890123456";
  unsigned char iv[32] = { 0 };

  /* Message to be encrypted */
  unsigned char *plaintext =(unsigned char*)"1234567812345678";

  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  unsigned char ciphertext[512];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[512];

  int decryptedtext_len, ciphertext_len;

  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Encrypt the plaintext */
  ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv,
    ciphertext);

  /* Do something useful with the ciphertext here */
  //printf("Ciphertext is:\n");  
  //BIO_dump_fp(stdout, (char *)ciphertext, ciphertext_len);
  LOGD("Ciphertext is:\n%s\n",ciphertext);
  LOGD("#### %x%x%x%x",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
  //F6C382F6......
  
  /* Decrypt the ciphertext */
  decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
    decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  //printf("Decrypted text is:\n");
  //printf("%s\n", decryptedtext);
  LOGD("Decrypted text is:\n%s\n",decryptedtext);

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();

  return 0;
}