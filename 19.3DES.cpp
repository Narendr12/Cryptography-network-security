#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8

void encrypt_block(unsigned char *block, unsigned char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i % 8];
    }
}

void cbc_encrypt(unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len, unsigned char *key, unsigned char *iv) {
    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned char temp_block[BLOCK_SIZE];

    for (int i = 0; i < num_blocks; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp_block[j] = plaintext[i * BLOCK_SIZE + j] ^ iv[j];
        }
        encrypt_block(temp_block, key);
        memcpy(ciphertext + i * BLOCK_SIZE, temp_block, BLOCK_SIZE);
        memcpy(iv, temp_block, BLOCK_SIZE);
    }
}

void print_hex(unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char plaintext[] = "This is a secret message";
    unsigned char key[] = "my_secret_key";
    unsigned char iv[] = "initialization";

    int plaintext_len = strlen((const char*)plaintext);
    unsigned char ciphertext[plaintext_len + BLOCK_SIZE];

    cbc_encrypt(plaintext, ciphertext, plaintext_len, key, iv);

    printf("Ciphertext: ");
    print_hex(ciphertext, plaintext_len + BLOCK_SIZE);

    return 0;
}

