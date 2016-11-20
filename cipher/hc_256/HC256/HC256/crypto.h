
#ifndef CRYPTO_H
#define CRYPTO_H

#include "ecrypt-sync.h"

class CRYPTOSOCKET {
public:
	/**
	* Creates and initializes the structures required for encryption.
	*
	* @param[in] socket
	* The socket to send and receive data on. This should already be connected.
	* @param[in] key
	* The key used for encryption and decryption.
	* @param[in] iv
	* The initialization vector used by AES256 CBC mode. This can just be random bytes.
	*
	* @see generateRandom
	*/
	CRYPTOSOCKET(int socket, unsigned char *key, unsigned char *iv);

	~CRYPTOSOCKET();

	/**
	* A wrapper for sending data across the connection.
	*
	* This encrypts the data into an intermediate buffer
	* prior to sending it across the wire.
	*
	* @see man send
	*/
	size_t send(const void *buf, size_t len, int flags);

	/**
	* A wrapper for receiving data across the connection.
	*
	* This receives the encrypted data into an intermediate buffer,
	* then decrypts it, and writes it to the output buffer.
	*
	* @see man recv
	*/
	size_t recv(void *buf, size_t len, int flags);

	/**
	* Encrypts the specified data and places the encrypted data in the specified buffer.
	*
	* @param len Used as input for how long the plaintext is, then for output of how long the cipher text is.
	* @param[in] plaintext The unencrypted data to encrypt.
	* @param[out] ciphertext Where to place the encrypted data.
	*
	* @returns A pointer to the ciphertext.
	*
	* @see unsigned char *decrypt(unsigned char *ciphertext, unsigned int len, unsigned char *plaintext)
	*/
	unsigned char *encrypt(unsigned char *plaintext, unsigned int len, unsigned char *ciphertext);

	/**
	* Decrypts the specified data and places the unencrypted data into the specified buffer.
	*
	* @param len Used as input for how long the ciphertext is and as output for how long the plaintext is.
	* @param[in] ciphertext The encrypted data to unencrypt.
	* @param[out] plaintext The buffer to place the unencrypted data in.
	*
	* @returns A pointer to the plaintext.
	*
	* @see unsigned char *encrypt(unsigned char *plaintext, unsigned int len, unsigned char *ciphertext)
	*/
	unsigned char *decrypt(unsigned char *ciphertext, unsigned int len, unsigned char *plaintext);

	int sock; /**< The underlying socket that this sends and receives on. */

private:
	ECRYPT_ctx e_ctx; /**< The ctx used for encryption. */
	ECRYPT_ctx d_ctx; /**< The ctx used for decryption. */
};

#endif