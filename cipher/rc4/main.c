#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <time.h>

#include "rc4.c"

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
	char *buf = malloc(len);
	char *mbuf = malloc(len);
	if(buf == NULL){
		perror("malloc");
		return -1;
	}
	//malloc buf
	int i;
	for(i=0;i<len;i++){
		buf[i] = rand()%256;
	}
	memcpy(mbuf, buf, len);
	//fill buf
	rc4_crypt(mbuf, len, key, strlen(key));
	//enc
	for(i=0;i<len;i++){
		buf[i] = buf[i] ^ mbuf[i];
	}
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
	fprintf(stderr, "Rc4 generator\n"
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
				key = optarg;
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
