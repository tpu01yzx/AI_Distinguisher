#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#include "crypto.h"

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

size_t CRYPTOSOCKET::send(const void *buf, size_t len, int flags) {
	unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char)*len);
	encrypt((unsigned char*)buf, len, buffer);
	return ::send(sock, (char *)buffer, len, MSG_WAITALL);
};

size_t CRYPTOSOCKET::recv(void *buf, size_t len, int flags) {
	unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char)*len);
	int data = ::recv(sock, (char *)buffer, len, MSG_WAITALL);

	if (data > 0)
		decrypt(buffer, len, (unsigned char *)buf);

	return data;
};