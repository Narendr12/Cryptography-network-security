#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 16
void xor_encrypt_decrypt(const unsigned char *input, const unsigned char *key, unsigned char
*output, size_t length) {
 for (size_t i = 0; i < length; ++i) {
 output[i] = input[i] ^ key[i % BLOCK_SIZE];
 }
}
void print_hex(const char *label, const unsigned char *data, size_t len) {
 printf("%s: ", label);
 for (size_t i = 0; i < len; ++i) {
 printf("%02x", data[i]);
 }
 printf("\n");
}
int main() {
 const unsigned char key[BLOCK_SIZE] = {'0', '1', '2', '3', '4', '5', '6', '7',
 '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
 const unsigned char plaintext[] = "This is a test123";
 size_t length = strlen((const char*)plaintext);
 unsigned char ciphertext[length];
 unsigned char decryptedtext[length];
 xor_encrypt_decrypt(plaintext, key, ciphertext, length);
 print_hex("Ciphertext", ciphertext, length);
 xor_encrypt_decrypt(ciphertext, key, decryptedtext, length);
 decryptedtext[length] = '\0';
 printf("Decrypted text: %s\n", decryptedtext);
 return 0;
}
