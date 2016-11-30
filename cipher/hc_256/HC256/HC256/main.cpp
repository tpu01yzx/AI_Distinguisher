#include "stdafx.h"
#include "getopt.h"
#include <malloc.h>


// prints string as hex
void phex(unsigned char* str,int len)
{
	if (len > 32)
		len = 16;
	unsigned char i;
	for (i = 0; i < len; ++i)
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
	printf("	-l NUMBER:	�������������(byte)��Ĭ��Ϊ1024\n");
	printf("	-o STRING:	������ļ���\"\n");
	printf("	-q bool:	ֻ���������\"\n");
}

int main(int argc, char **argv) {
    if (argc == 1) {
		print_usage(argv[0]);
		getchar();
		return 0;
	}
	bool quite = false;
	int len = 1024;
	CRYPTOSOCKET *socket;
	unsigned char key[32] = "000000000000";
	unsigned char iv[32] = "000000000000";
	unsigned char buf2[1024] = "";
	char *output = "out.bin";
	int opt;
	while ((opt = getopt(argc, argv, "thi:k:l:")) != -1) {
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
			//target = optarg;
			break;
		case 'o':
			output = optarg;
			break;
		case 'l':
			len = atoi(optarg);
			break;
		case 'q':
			quite = true;
			break;
		case 'h':
		default:
			print_usage(argv[0]);
			return 0;
		}
	}
	unsigned char * buf1 = (unsigned char *)malloc(len);
	for (int i = 0; i<len; i++) {
		buf1[i] = rand() % 256;
	}
	// Generate a random key
	//generateRandom(key, 32);

	// Generate a random IV
	//generateRandom(iv, 32);

	// Create a new cryptosocket with that key and iv.
	socket = new CRYPTOSOCKET(0, key, iv);

	// Copy teststring into buffer 1
	//sprintf((char*)buf1, target);

	// Encrypt buffer 1 and placed the encrypted contents into buffer 2.
	socket->encrypt(buf1, len, buf2);
	
	if (!quite) {
		printf("���ܺ�");
		phex(buf2,len);
	}
	
	// Decrypt buffer 2 into buffer 3.
	//socket->decrypt(buf2, strlen(target), buf3);

	// Print out whats in buffer 3.
	//printf("���ܺ�%s\n", (char*)buf3);
	
	FILE *fp;
	fp = fopen(output, "w");
	if(fp == NULL){
		if (!quite)
		printf("fopen error");
		return -1;
	}
	fwrite(buf2, len, 1, fp);
	fclose(fp);
}