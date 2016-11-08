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
