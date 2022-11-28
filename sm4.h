#ifndef _SM4_H_

#define _SM4_H_

#define BLOCK_LEN 16
#define KEY_LEN 16

void SM4_KeySchedule(const unsigned char MK[], unsigned int rk[]);
// SM4 Enc & SM4 Dec with master key, standard interface
void SM4_Encrypt(const unsigned char MK[], const unsigned char PlainText[], unsigned char CipherText[]);
void SM4_Decrypt(const unsigned char MK[], const unsigned char CipherText[], unsigned char PlainText[]);

/**
 * @brief 加密一个分组
 *
 * @param cipher 输出
 * @param plain 明文
 * @param mk 密钥
 */
void SM4_Enc(unsigned char cipher[16], const unsigned char plain[16], const unsigned char mk[16]);
void SM4_Dec(unsigned char plain[16], const unsigned char cipher[16], const unsigned char mk[16]);

int Crypt_Enc_Block(unsigned char intput[], int inlen, unsigned char output[], int *outlen, unsigned char key[], int keylen);
int Crypt_Dec_Block(unsigned char intput[], int inlen, unsigned char output[], int *outlen, unsigned char key[], int keylen);

void reverse_U8(unsigned char *src, unsigned char *dst, int byteLen);
unsigned char bigIntModMul2(unsigned char *src, int byteLen);

int sm4_mac(unsigned char *input, int in_len, unsigned char *IV, unsigned char *output, int *out_len, unsigned char *key, int keylen);

#endif