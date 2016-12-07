void rc4_init(unsigned char *s, unsigned char *key, unsigned long len){
	unsigned int i, j;
	unsigned char tmp;
	
	for (i = 0; i < 256; i++){
		s[i] = i;
	}

	for (i = j = 0; i < 256; i++){
		j = (j + s[i] + key[i%len]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		//swap s[i] and s[j]
	}
}

void rc4_crypt(unsigned char *s, unsigned char *data, unsigned long len)
{
	static unsigned int i = 0, j = 0;
	unsigned int t;
	unsigned long k;
	unsigned char tmp;

	for (k = 0; k < len; k++){
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		//swap s[i] and s[j]
		t = (s[i] + s[j]) % 256;
		data[k] ^= s[t];
	}
}
