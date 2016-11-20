#include <stdio.h>
#include <string.h>
#include "getopt.h"
#include "crypto.h"

// prints string as hex
void phex(unsigned char* str)
{
	unsigned char i;
	for (i = 0; i < 16; ++i)
		printf("%.2X", str[i]);
	printf("\n");
}

static void print_usage(char *self)
{
	printf("Usage: %s [-t] [-h] [-k KEY] [-i IV] [-s STRING] [-o STRING]\n", self);
	printf("	-t:		����\n");
	printf("	-h:		��ʾ����\n");
	printf("	-k KEY:		������Կ��32λ��Ĭ��Ϊ\"000000000000\"\n");
	printf("	-i IV:		����IV��32λ��Ĭ��Ϊ\"000000000000\"\n");
	printf("	-s STRING:	�����ַ�����Ĭ��Ϊ\"Tech otakus save the world!\"\n");
	printf("	-o STRING:	������ļ���\"\n");
}

int main(int argc, char **argv) {
    if (argc == 1) {
		print_usage(argv[0]);
		getchar();
		return 0;
	}

	CRYPTOSOCKET *socket;
	unsigned char key[32] = "000000000000";
	unsigned char iv[32] = "000000000000";
	unsigned char buf1[1024] = "";
	unsigned char buf2[1024] = "";
	unsigned char buf3[1024] = "";
	char *target = "Tech otakus save the world!";
	char *output = "out.bin";
	int opt;
	while ((opt = getopt(argc, argv, "thi:k:s:")) != -1) {
		switch (opt) {
		case 't':
			break;
		case 'k':
			if (strlen(optarg) == 32)
				strncpy((char *)key, optarg, 32);
			else
			{
				printf("IV���ȴ���������32λ��IV");
				return 0;
			}
			break;
		case 'i':
			if (strlen(optarg) == 32)
				strncpy((char *)iv, optarg, 32);
			else
			{
				printf("IV���ȴ���������32λ��IV");
				return 0;
			}
			break;
		case 's':
			target = optarg;
			break;
		case 'o':
			output = optarg;
			break;
		case 'h':
		default:
			print_usage(argv[0]);
			return 0;
		}
	}
	// Generate a random key
	//generateRandom(key, 32);

	// Generate a random IV
	//generateRandom(iv, 32);

	// Create a new cryptosocket with that key and iv.
	socket = new CRYPTOSOCKET(0, key, iv);

	// Copy teststring into buffer 1
	sprintf((char*)buf1, target);

	// Encrypt buffer 1 and placed the encrypted contents into buffer 2.
	socket->encrypt(buf1, strlen(target), buf2);
	
	printf("���ܺ�");
	phex(buf2);
	// Decrypt buffer 2 into buffer 3.
	//socket->decrypt(buf2, strlen(target), buf3);

	// Print out whats in buffer 3.
	//printf("���ܺ�%s\n", (char*)buf3);
	
	FILE *fp;
	fp = fopen(output, "w");
	if(fp == NULL){
		printf("fopen error");
		return -1;
	}
	fwrite(buf2, strlen(target), 1, fp);
	fclose(fp);
	
	getchar();
}