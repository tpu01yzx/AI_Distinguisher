#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "rc4.c"

int block_size = 8192;//default block size
int quiet = 0;
char *input = "/dev/stdin";
int input_len = 256;
char *output = "/dev/stdout";
long long int output_len = 0;

int generate(){
	FILE *fp_src, *fp_des;
	fp_src = fopen(input, "rb");
    fp_des = fopen(output, "wb");
	if(!fp_src || !fp_des){
		perror("fopen");
		return 0;
	}
	//open file
	char *input_buf = malloc(input_len);
	char *output_buf = malloc(block_size);
	if(!input_buf || !output_buf){
		perror("malloc");
		return 0;
	}
	//malloc buf
	bzero(input_buf, input_len);
	bzero(output_buf, block_size);
	//erase buf
	if(!fread(input_buf, input_len, 1, fp_src)){
		perror("fread");
		return 0;
	}
	//read input
	unsigned char s[256];
	rc4_init(s, input_buf, input_len);
	//init cipher
	long long int len = output_len;
	//init loop env
	while(len > 0){
        int l = len < block_size ? len : block_size;
        bzero(output_buf, block_size);
        len -= block_size;
        //fill zero stream
        rc4_crypt(s, output_buf, l);
        //save key stream
        fwrite(output_buf, l, 1, fp_des);
	}

	free(input_buf);
    free(output_buf);
	//free buf
	fclose(fp_src);
    fclose(fp_des);
	//close file

	return 1;
}

void usage(const char *progname){
	fprintf(stderr, "RC4 stream generator\n"
		"Usage: %s [options] -L length\n"
			"\t-i   Input from file, default is /dev/stdin\n"
			"\t-l   Input lenght (byte), default is 256\n"
			"\t-o   Output to file, default is /dev/stdout\n"
			"\t-L   Output lenght (byte), not null\n"
			"\t-b   Block size (byte), default is 8192\n"
			"\t-q   Output other information\n"
			"\t-h   Show this message\n"
			"\n",
		progname);
}

int main(int argc, char *argv[]){
    int ch;
	while((ch = getopt(argc, argv, "i:l:o:L:b:qh")) != -1){
		switch(ch){
			case 'i':
				input = optarg;
				break;
			case 'l':
				input_len = atoi(optarg);
				break;
            case 'o':
				output = optarg;
				break;
			case 'L':
				output_len = atoll(optarg);
				break;
			case 'b':
				block_size = atoi(optarg);
				break;
			case 'q':
				quiet = 1;
				break;
			case '?':
            case 'h':
				usage(argv[0]);
				return 0;
				break;
			default:
				usage(argv[0]);
				return 0;
		}
	}
	
	if(!output_len){
        usage(argv[0]);
        return -1;
	}

	clock_t start, end;
	start = clock();
	//set start time

	int ret = generate();
	//start generate

	end = clock();
	double diff = (double)(end-start)/CLOCKS_PER_SEC;
	if(quiet && ret){
		fprintf(stderr, "Generate %d bytes (%.2fMB) in %f s, %.2f MB/s\n", output_len, (double)output_len/1024/1024, diff, output_len/1024/1024/diff);
	}
	//show end time

	return 1;
}
