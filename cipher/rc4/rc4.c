#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <time.h>

int len;
unsigned char *key=NULL;
char *output=NULL;

void rc4_crypt(unsigned char *data, int data_len, unsigned char *key, int key_len)
{
	int i, j, k;
	unsigned char a, b, s[256];

	for (i = 0; i < 256; i++){
		s[i] = i;
	}

	for (i = j = k = 0; i < 256; i++){
		a = s[i];
		j = (j + a + key[k]) % 256;
		s[i] = s[j];
		s[j] = a;
		if (++k >= key_len) k = 0;
	}

	for (i = j = k = 0; i < data_len; i++){
		j = (j + 1) % 256;
		a = s[j];
		k = (k + a) % 256;
		s[j] = b = s[k];
		s[k] = a;
		data[i] ^= s[(a + b) % 256];
	}
}

int generate(){
	clock_t start, end;
	start = clock();
	//set start time
	srand(time(0));
	//set srand
	char *buf = malloc(len);
	if(buf == NULL){
		perror("malloc");
		return -1;
	}
	//malloc buf
	int i;
	for(i=0;i<len;i++){
		buf[i] = rand()%256;
	}
	//fill buf
	rc4_crypt(buf, len, key, strlen(key));
	//enc
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
	fprintf(stdout, "Generate %d bytes (%.2fMB) in %f s, %.2f MB/s\n", len, (double)len/1024/1024, diff, len/1024/1024/diff);
	return 0;
}

void usage(const char *progname){
	fprintf(stderr, "Usage: %s"
			" -l lenght(byte)"
			" -k key"
			" -o output"
			"\n",
		progname);
}

int main(int argc, char *argv[]){
	int ch;

	if(argc == 1){
		usage(argv[0]);
		return -1;
	}

	while((ch = getopt(argc, argv, "l:k:o:")) != -1){
		switch(ch){
			case 'l':
				len = atoi(optarg);
				break;
			case 'k':
				key = optarg;
				break;
			case 'o':
				output = optarg;
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
