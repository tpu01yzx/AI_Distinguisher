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
	fprintf(stderr, "Rc4 generator\n"
  "Usage: %s\n"
			" -l lenght(byte)\n"
			" -k key\n"
			" -o output\n"
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
