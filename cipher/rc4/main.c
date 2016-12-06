#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include "rc4.c"

int block_size = 8192;//default block size
long long int output_len = 0;
unsigned char *key = "000000";//default key 000000
char *input_dats = "/dev/urandom";
char *output_dats = "/dev/stdout";
char *output_keys = "/dev/null";

int generate(){
	clock_t start, end;
	start = clock();
	//set start time
	FILE *dats_src, *fp_dats, *fp_keys;
	dats_src = fopen(input_dats, "rb");
    	fp_dats = fopen(output_dats, "wb");
    	fp_keys = fopen(output_keys, "wb");
	if(!dats_src || !fp_dats || !fp_keys){
		perror("fopen");
		return -1;
	}
	//open file
	char *buf = malloc(block_size);
	char *mbuf = malloc(block_size);
	if(!buf || !mbuf){
		perror("malloc");
		return -1;
	}
	//malloc buf
	long long int len = output_len;
	int i, ret = 1;
	while(len > 0 && ret){
        int l = len < block_size ? len : block_size;
        ret = fread(buf, 1, l, dats_src);
        len -= ret;
        memcpy(mbuf, buf, l);
        //fill buf
        rc4_crypt(buf, l, key, strlen(key));
        //enc
        for(i=0;i<l;i++){
            mbuf[i] = buf[i] ^ mbuf[i];
        }
        //get key stream
        fwrite(buf, ret, 1, fp_dats);
        fwrite(mbuf, ret, 1, fp_keys);
	}

    free(buf);
    free(mbuf);

    fclose(dats_src);
	fclose(fp_dats);
	fclose(fp_keys);
	//close file
	return 0;
}

void usage(const char *progname){
	fprintf(stderr, "RC4 stream generator\n"
  "Usage: %s [options] -l length\n"
			"\t-l   Output lenght (byte)\n"
			"\t-b   Block size (byte), default is 8192\n"
			"\t-k   Encryption key, default is 000000 (ASCII)\n"
			"\t-o   Cipher stream to file, default is /dev/stdout\n"
			"\t-s   Secret key stream to file, default is /dev/null\n"
			"\t-i   Encrypted stream from file, default is /dev/urandom\n"
			"\t-h   Show this message\n"
			"\n",
		progname);
}

int main(int argc, char *argv[]){
    int ch;
	while((ch = getopt(argc, argv, "l:b:k:o:s:i:h")) != -1){
		switch(ch){
			case 'l':
				output_len = atoll(optarg);
				break;
            case 'b':
				block_size = atoi(optarg);
				break;
			case 'k':
				key = optarg;
				break;
            case 'i':
				input_dats = optarg;
				break;
			case 'o':
				output_dats = optarg;
				break;
			case 's':
				output_keys = optarg;
				break;
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

	generate();

	return 0;
}
