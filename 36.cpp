#include <stdio.h>
#include <string.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void affineEncrypt(char *text, int a, int b, char *encryptedText) {
    int i = 0;
    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                encryptedText[i] = ((a * (ch - 'A') + b) % 26) + 'A';
            } else {
                encryptedText[i] = ((a * (ch - 'a') + b) % 26) + 'a';
            }
        } else {
            encryptedText[i] = ch;
        }
    }
    encryptedText[i] = '\0';
}

void affineDecrypt(char *text, int a, int b, char *decryptedText) {
    int i = 0;
    int m = 26;
    int aInv = modInverse(a, m);
    if (aInv == -1) {
        printf("Error: Modular inverse of 'a' does not exist.\n");
        return;
    }
    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                decryptedText[i] = ((aInv * ((ch - 'A' - b + m)) % 26) + 'A');
            } else {
                decryptedText[i] = ((aInv * ((ch - 'a' - b + m)) % 26) + 'a');
            }
        } else {
            decryptedText[i] = ch;
        }
    }
    decryptedText[i] = '\0';
}

int main() {
    char plainText[100];
    char encryptedText[100];
    char decryptedText[100];
    int a, b;
    printf("Enter the plaintext: ");
    gets(plainText);
    plainText[strcspn(plainText, "\n")] = '\0';
    printf("Enter the key 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the key 'b': ");
    scanf("%d", &b);
    affineEncrypt(plainText, a, b, encryptedText);
    printf("Encrypted text: %s\n", encryptedText);
    affineDecrypt(encryptedText, a, b, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);
    return 0;
}
