#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <time.h>

// Enable both ECB and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DECB=1
#define CBC 1
#define ECB 1

#include "aes.h"

void phex(uint8_t* str);
void encrypt_ecb_verbose(uint8_t *plain_text,int len);

int len;
unsigned char *key=NULL;
char *output=NULL;
int output_key = 0;

int generate(){
	clock_t start, end;
	start = clock();
	//set start time
	srand(time(0));
	//set srand
	uint8_t *buf = malloc(len);
	if(buf == NULL){
		perror("malloc");
		return -1;
	}
	//malloc buf
	int i;
	for(i=0;i<len;i++){
		buf[i] = rand()%256;
	}
    encrypt_ecb_verbose(buf,len);
	//
	FILE *fp;
	fp = fopen(output, "w");
	if(fp == NULL){
		perror("fopen");
		return -1;
	}
	fwrite(buf, len, 1, fp);
	fclose(fp);
	//saveto file
	end = clock();
	double diff = (double)(end-start)/CLOCKS_PER_SEC;
	if(output_key){
		fwrite(buf, len, 1, stdout);
	}else{
		fprintf(stdout, "Generate %d bytes (%.2fMB) in %f s, %.2f MB/s\n", len, (double)len/1024/1024, diff, len/1024/1024/diff);
	}
	return 0;
}

void usage(const char *progname){
	fprintf(stderr, "AES generator\n"
  "Usage: %s\n"
			"\t-l lenght(byte)\n"
			"\t-k key\n"
			"\t-o output cipher stream to file\n"
			"\t-q output key stream to stdout\n"
			"\n",
		progname);
}

int main(int argc, char *argv[]){
	int ch;

	if(argc == 1){
		usage(argv[0]);
		return -1;
	}

	while((ch = getopt(argc, argv, "l:k:o:q")) != -1){
		switch(ch){
			case 'l':
				len = atoi(optarg);
				break;
			case 'k':
				key = (unsigned char *)optarg;
				break;
			case 'o':
				output = optarg;
				break;
			case 'q':
				output_key = 1;
				break;
			default:
				usage(argv[0]);
				return -1;
		}
	}

	if(output == NULL || key == NULL || len == 0){
		usage(argv[0]);
		return -1;
	}

	generate();

	return 0;
}

// prints string as hex
void phex(uint8_t* str)
{
	unsigned char i;
	for (i = 0; i < 16; ++i)
		printf("%.2X", str[i]);
	printf("\n");
}

// 128bit key
void encrypt_ecb_verbose(uint8_t *plain_text,int len)
{
	// Example of more verbose verification

	uint8_t i;
	uint8_t *buf = malloc(len);
	memset(buf, 0, len);

	if(!output_key){
	    // print text to encrypt, key and IV
	    printf("ECB encrypt verbose:\n\n");
	    printf("plain text:\n");
	    for (i = (uint8_t)0; i < (uint8_t)4; ++i)
	    {
	    	phex(plain_text + i * (uint8_t)16);
	    }
	    printf("\n");
    
	    printf("key:");
	    phex(key);
	    printf("\n");
		// print the resulting cipher as 4 x 16 byte strings
	    printf("ciphertext:\n");
	}
	for (i = 0; i < (len/16); ++i)
	{
		AES128_ECB_encrypt(plain_text + (i * 16), key, buf + (i * 16));
		memcpy(plain_text + (i * 16),(buf + (i * 16)),16);
	}
	if(!output_key)
		phex(plain_text);
}

