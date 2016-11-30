#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

// Enable both ECB and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DECB=1
#define CBC 1
#define ECB 1

#include "aes.h"

static void phex(uint8_t* str);
static void test_encrypt_ecb_verbose(void);
static void test_Decrypt_ecb_verbose(void);


int main(void)
{
	test_encrypt_ecb_verbose();
	test_Decrypt_ecb_verbose();

	return 0;
}



// prints string as hex
static void phex(uint8_t* str)
{
	unsigned char i;
	for (i = 0; i < 16; ++i)
		printf("%.2X", str[i]);
	printf("\n");
}

void HexStrToByte(const char* source, unsigned char* dest, int sourceLen)
{
	short i;
	unsigned char highByte, lowByte;

	for (i = 0; i < sourceLen; i += 2)
	{
		highByte = toupper(source[i]);
		lowByte = toupper(source[i + 1]);

		if (highByte > 0x39)
			highByte -= 0x37;
		else
			highByte -= 0x30;

		if (lowByte > 0x39)
			lowByte -= 0x37;
		else
			lowByte -= 0x30;

		dest[i / 2] = (highByte << 4) | lowByte;
	}
	return;
}

static void test_encrypt_ecb_verbose(void)
{
	// Example of more verbose verification

	uint8_t i, buf[320];

	// 128bit key
	uint8_t key[16] = { (uint8_t)0x5A,  (uint8_t)0x3C,  (uint8_t)0x6F,  (uint8_t)0x5C,  (uint8_t)0x53,  (uint8_t)0x49,  (uint8_t)0x76,  (uint8_t)0x70,  (uint8_t)0x69,  (uint8_t)0x3A,  (uint8_t)0x73,  (uint8_t)0x66,  (uint8_t)0x56,  (uint8_t)0x45, (uint8_t)0x22, (uint8_t)0x28};
	// 512bit text
	uint8_t *plain_text = (uint8_t *)" ";

	memset(buf, 0, 320);

	// print text to encrypt, key and IV
	printf("ECB encrypt verbose:\n\n");
	printf("plain text:\n");
	for (i = (uint8_t)0; i < (uint8_t)4; ++i)
	{
		phex(plain_text + i * (uint8_t)16);
	}
	printf("\n");

	printf("key:\n");
	phex(key);
	printf("\n");

	// print the resulting cipher as 4 x 16 byte strings
	printf("ciphertext:\n");
	for (i = 0; i < 19; ++i)
	{
		AES128_ECB_encrypt(plain_text + (i * 16), key, buf + (i * 16));
		phex(buf + (i * 16));
	}
	printf("\n");
}

static void test_Decrypt_ecb_verbose(void)
{
	// Example of more verbose verification

	uint8_t i, buf[640], buf2[640];

	// 128bit key
	uint8_t key[16] = { (uint8_t)0x5A,  (uint8_t)0x3C,  (uint8_t)0x6F,  (uint8_t)0x5C,  (uint8_t)0x53,  (uint8_t)0x49,  (uint8_t)0x76,  (uint8_t)0x70,  (uint8_t)0x69,  (uint8_t)0x3A,  (uint8_t)0x73,  (uint8_t)0x66,  (uint8_t)0x56,  (uint8_t)0x45, (uint8_t)0x22, (uint8_t)0x28 };
	// 512bit text
	uint8_t *plain_text = (uint8_t *)" ";

	memset(buf, 0, 640);
	memset(buf2, 0, 640);

	// print text to encrypt, key and IV
	printf("ECB encrypt verbose:\n\n");
	printf("plain text:\n");
	printf((char *)plain_text);
	printf("\n");

	printf("key:\n");
	phex(key);
	printf("\n");

	// print the resulting cipher as 4 x 16 byte strings
	printf("ciphertext:\n");
	HexStrToByte((char *)plain_text, buf2, 640-1);
	for (i = 0; i < 19; ++i)
	{
		AES128_ECB_decrypt(buf2 + (i * 16), key, buf + (i * 16));
		printf("%s",buf + (i * 16));
	}
	printf("\n");
}



