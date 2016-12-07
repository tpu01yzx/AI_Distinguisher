#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "rc4.c"

int block_size = 8192;//default block size
int quiet = 1;
char *input_keys = "/dev/zero";
int key_len = 256;
char *input_dats = "/dev/zero";
long long int output_len = 0;
char *output_dats = "/dev/stdout";
char *output_keys = "/dev/null";

int generate(){
	FILE *keys_src, *dats_src, *fp_keys, *fp_dats;
	keys_src = fopen(input_keys, "rb");
	dats_src = fopen(input_dats, "rb");
    fp_dats = fopen(output_dats, "wb");
    fp_keys = fopen(output_keys, "wb");
	if(!keys_src || !dats_src || !fp_dats || !fp_keys){
		perror("fopen");
		return 0;
	}
	//open file
	char *key = malloc(key_len);
	char *buf = malloc(block_size);
	char *mbuf = malloc(block_size);
	if(!key || !buf || !mbuf){
		perror("malloc");
		return 0;
	}
	//malloc buf
	if(!fread(key, key_len, 1, keys_src)){
		perror("fread");
		return 0;
	}
	//read key
	unsigned char s[256];
	rc4_init(s, key, key_len);
	//init cipher
	long long int len = output_len;
	int i, ret = 1;
	while(len > 0 && ret){
        int l = len < block_size ? len : block_size;
        ret = fread(buf, 1, l, dats_src);
        len -= ret;
        memcpy(mbuf, buf, l);
        //fill buf
        rc4_crypt(s, buf, l);
        //enc
        for(i=0;i<l;i++){
            mbuf[i] = buf[i] ^ mbuf[i];
        }
        //get key stream
        fwrite(buf, ret, 1, fp_dats);
        fwrite(mbuf, ret, 1, fp_keys);
	}

	free(key);
    free(buf);
    free(mbuf);

	fclose(keys_src);
    fclose(dats_src);
	fclose(fp_keys);
	fclose(fp_dats);
	//close file

	return 1;
}

void usage(const char *progname){
	fprintf(stderr, "RC4 stream generator\n"
		"Usage: %s [options] -L length\n"
  			"\t-k   Key source from file, default is /dev/zero\n"
			"\t-l   Key source lenght (byte), default is 256\n"
			"\t-i   Data source from file, default is /dev/zero\n"
			"\t-L   Data source lenght (byte)\n"
			"\t-o   Cipher stream to file, default is /dev/stdout\n"
			"\t-O   Key stream to file, default is /dev/null\n"
			"\t-b   Block size (byte), default is 8192\n"
			"\t-q   Not output other information\n"
			"\t-h   Show this message\n"
			"\n",
		progname);
}

int main(int argc, char *argv[]){
    int ch;
	while((ch = getopt(argc, argv, "k:l:i:L:o:O:b:qh")) != -1){
		switch(ch){
			case 'k':
				input_keys = optarg;
				break;
			case 'l':
				key_len = atoi(optarg);
				break;
			case 'i':
				input_dats = optarg;
				break;
			case 'L':
				output_len = atoll(optarg);
				break;
            case 'o':
				output_keys = optarg;
				break;
			case 'O':
				output_dats = optarg;
				break;
			case 'b':
				block_size = atoi(optarg);
				break;
			case 'q':
				quiet = 0;
				break;
			case '?':
            case 'h':
				usage(argv[0]);
				return 0;
				break;
			default:
				usage(argv[0]);
				return -1;
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

	return 0;
}
