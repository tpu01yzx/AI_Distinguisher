#include "stdafx.h"

CRYPTOSOCKET::CRYPTOSOCKET(int socket, unsigned char *key, unsigned char *iv) {
	// Initialize the encryptor.
	ECRYPT_keysetup(&e_ctx, key, 128, 128);
	ECRYPT_ivsetup(&e_ctx, iv);

	// Initialize the decryptor.
	ECRYPT_keysetup(&d_ctx, key, 128, 128);
	ECRYPT_ivsetup(&d_ctx, iv);

	sock = socket;
};

CRYPTOSOCKET::~CRYPTOSOCKET() {
	// Nothing to do.
};

unsigned char *CRYPTOSOCKET::encrypt(unsigned char *plaintext, unsigned int len, unsigned char *ciphertext) {
	ECRYPT_process_bytes(0, &e_ctx, plaintext, ciphertext, len);
	return ciphertext;
}

unsigned char *CRYPTOSOCKET::decrypt(unsigned char *ciphertext, unsigned int len, unsigned char *plaintext) {
	ECRYPT_process_bytes(1, &d_ctx, ciphertext, plaintext, len);
	return plaintext;
}
